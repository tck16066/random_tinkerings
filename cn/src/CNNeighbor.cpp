#include <vector>
#include <poll.h>
#include <unordered_set>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>

#include "CNNeighbor.h"
#include "utility.h"

CNNeighborStateManager::CNNeighborStateManager() :
  ctx(NULL), rawTrans(NULL)
{

}

CNNeighborStateManager::~CNNeighborStateManager()
{

}

void CNNeighborStateManager::init(CNContext *ctx, CNRawIPTransport *raw)
{
  this->ctx = ctx;
  rawTrans = raw;
  transports[raw->fd()] = raw;
}

bool CNNeighborStateManager::neighborPresent(CNID *neighbor)
{
  return neighbors.find(*neighbor) != neighbors.end();
}

CNErrorCode CNNeighborStateManager::addNeighbor(CNID *neighbor, CNTransport *trans)
{
  CNErrorCode ret = CN_SUCCESS;
  CNNeighborState state;

  try {
    transports[trans->fd()] = trans;
    state.pingSent = 0;
    state.pingArrived = 0;
    neighbors[*neighbor] = state;
    idToTransports[*neighbor] = trans;
  }
  catch (...) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_INTERNAL, 1);
    goto error;
  }
  std::cout << "Meet new neighbor, " << neighbor->strVal() << "!" << std::endl;

error:
  return ret;
}

CNErrorCode CNNeighborStateManager::listenNeighbors(uint32_t secDelay)
{

  CNErrorCode ret = CN_SUCCESS;
  std::vector<pollfd> fds;
  std::unordered_set<int> tmp_fds;
  int pollRet = 0;

  if (ctx == NULL || rawTrans == NULL) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_NOT_READY, 1);
    goto error;
  }

  // First, we get all file descriptors from all transports. Then, we narrow
  // it down to only the unique file descriptors (since transports might use
  // the same file descriptor). Then we pass these to poll().

  // Notes, this following section has potential to favor certain transports
  // for servicing more often than others. This depends on how busy transports
  // are and the order they are returned by these collections, which is likely
  // a fixed order.
  try {
    for (CNTransCollection::iterator iter = transports.begin();
      iter != transports.end(); ++iter) {
      tmp_fds.insert(iter->second->fd());
    }

    tmp_fds.insert(rawTrans->fd());

    for (std::unordered_set<int>::iterator iter = tmp_fds.begin();
      iter != tmp_fds.end(); ++iter) {
      pollfd pfd;
      pfd.fd = *iter;
      pfd.events = POLLIN;
      fds.push_back(pfd);
    }
  }
  catch (...) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_OOM, 1);
    goto error;
  }

  if (fds.size() == 0)
    goto error;

  pollRet = poll(&fds[0], fds.size(), secDelay);
  if (pollRet < 0) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_INTERNAL, 2);
    goto error;
  }

  for (int i = 0; i < pollRet; ++i) {
    CNMessage *msg = NULL;
    if (!(fds[i].revents & POLLIN))
      continue;
    ret = transports[fds[i].fd]->rxData(&msg);
    if (ret != CN_SUCCESS) {
      // Squashing the other outstanding messages is inefficent but should be safe.
      if (msg)
        transports[fds[i].fd]->returnToFactory(msg);
      goto error;
    }

    if (msg) {
      ret = handleRxMessage(msg, transports[fds[i].fd]);
      transports[fds[i].fd]->returnToFactory(msg);
    }

    if (ret != CN_SUCCESS)
      goto error;
  }

error:
  return ret;
}

CNErrorCode CNNeighborStateManager::pingNeighbors()
{
  CNErrorCode ret = CN_SUCCESS;
  CNMessage *msg;
  CNID tmpID(CNID::broadcastID);
  uint64_t pingTime = 0;

  if (ctx == NULL || rawTrans == NULL) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_ID_NOT_FOUND, 1);
    goto error;
  }

  // For now, we just use the Raw IP transport and broadcast to all nodes.
  msg = rawTrans->messageFactory();
  if (msg == NULL) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_OOM, 2);
    goto error;
  }

  fillTxMessage(msg, CN_MSG_PING, &tmpID);

  if ((ret = monoMSecs(&pingTime))) {
    rawTrans->returnToFactory(msg);
    goto error;
  }

  for (CNNeighborCollection::iterator iter = neighbors.begin();
    iter != neighbors.end(); ++iter) {
    iter->second.pingSent = pingTime;
    iter->second.pingArrived = 0;
  }

  ret = rawTrans->txData(msg);
  rawTrans->returnToFactory(msg);

error:
  return ret;
}

CNErrorCode CNNeighborStateManager::advertise()
{
  CNErrorCode ret = CN_SUCCESS;
  CNMessage *msg;
  CNID tmpID(CNID::broadcastID);

  if (ctx == NULL || rawTrans == NULL) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_NOT_READY, 2);
    goto error;
  }

  // Broadcast to all nodes on the raw IP transport.
  msg = rawTrans->messageFactory();
  if (msg == NULL) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_OOM, 3);
    goto error;
  }

  fillTxMessage(msg, CN_MSG_ADVERT, &tmpID);
  ret = rawTrans->txData(msg);
  rawTrans->returnToFactory(msg);

error:
  return ret;
}

CNErrorCode CNNeighborStateManager::handleRxMessage(CNMessage *msg,
  CNTransport *trans)
{
  CNErrorCode ret = CN_SUCCESS;
  CNID id(std::string((const char *)msg->rxHeader()->src, CNID::length));

  // TODO: replace this ugly thing with a lookup to member function pointer
  // or lookup to functor.
  switch (msg->rxHeader()->type) {
  case CN_MSG_ADVERT:
    {
      if (!neighborPresent(&id)) {
        ret = addNeighbor(&id, trans);
        if (ret)
          goto error;
      }
    }
  break;
  case CN_MSG_PING: //Rx's a ping
    {
      CNMessage *txMsg;
      if (!neighborPresent(&id)) {
        ret = addNeighbor(&id, trans);
      }
      if (ret != CN_SUCCESS)
        goto error;

      txMsg = trans->messageFactory();
      if (txMsg == NULL) {
        ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_OOM, 5);
        goto error;
      }
      fillTxMessage(txMsg, CN_MSG_PONG, &id);
      ret = trans->txData(txMsg);
      trans->returnToFactory(txMsg);
      if (ret)
        goto error;
    }
  break;
  case CN_MSG_PONG: //Rx'd a response to a ping
    {
      uint64_t pingTime;
      if (!neighborPresent(&id)) {
        ret = addNeighbor(&id, trans);
        // Not necessarily an error, but we're done processing.
        goto error;
      }
      else if ((ret = monoMSecs(&pingTime))) {
        goto error;
      }
      neighbors[id].pingArrived = pingTime;
    }
  break;
  default:
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_NOT_IMPLEMENTED, 1);
  }

error:
  return ret;
}

void CNNeighborStateManager::fillTxMessage(CNMessage *msg, CNMessageType type,
  CNID *dst)
{
  CNProtoHdr *hdr = msg->txHeader();

  hdr->type = type;
  hdr->dataLen = 0;
  memcpy(hdr->dst, dst->strVal().c_str(), CNID::length);
  memcpy(hdr->src, ctx->id.strVal().c_str(), CNID::length);
}


CNErrorCode CNNeighborStateManager::knownNeighbors(CNNeighborList *list)
{
  CNErrorCode ret = CN_SUCCESS;

  list->clear();

  for (CNNeighborCollection::iterator iter = neighbors.begin();
    iter != neighbors.end(); ++iter) {
    try {
      list->push_back(iter->first);
    }
    catch (...) {
      ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_OOM, 4);
      goto error;
    }
  }

error:
  return ret;
}

CNErrorCode CNNeighborStateManager::neighborState(CNID *id, CNNeighborState **state)
{
  CNErrorCode ret = CN_SUCCESS;
  *state = NULL;

  if (!neighborPresent(id)) {
    ret = CN_BUILD_ERROR(CN_NEIGHBOR, CN_ID_NOT_FOUND, 2);
    goto error;
  }

  *state = &(neighbors[*id]);

error:
  return ret;
}
