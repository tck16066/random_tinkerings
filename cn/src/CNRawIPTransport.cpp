#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <netinet/in.h>

#include "CNRawIPTransport.h"

#define CN_RAW_MAX_TX_BYTES 512 //Keep it small, but below the 576 min IP len

// Implement the concerete message appropriate for the Raw IP transport.
class CNRawIPTransMessage : public CNMessage
{
public:
  CNRawIPTransMessage();
  ~CNRawIPTransMessage();
  virtual CNProtoHdr *rxHeader();
  virtual CNProtoHdr *txHeader();
  virtual CNMessageDerived derivedType();
  virtual size_t payloadRoom();
  size_t rxIPOffset();
  bool isIP4();
  uint32_t hdrOff;
  std::vector<uint8_t> buffer;
  bool isRx;
};

CNRawIPTransMessage::CNRawIPTransMessage() :
  hdrOff(0), isRx(false)
{
  buffer.resize(CN_RAW_MAX_TX_BYTES);
}

CNRawIPTransMessage::~CNRawIPTransMessage()
{

}

CNProtoHdr *CNRawIPTransMessage::rxHeader()
{
  CNProtoHdr *ret = NULL;

  if (isRx)
    ret = reinterpret_cast<CNProtoHdr *>
      ((&buffer[0]) + rxIPOffset()); //adjust for IP header.
  return ret;
}

CNProtoHdr *CNRawIPTransMessage::txHeader()
{
  return reinterpret_cast<CNProtoHdr *>(&buffer[0]);
}

CNMessageDerived CNRawIPTransMessage::derivedType()
{
  return CN_DER_RAW;
}

size_t CNRawIPTransMessage::payloadRoom()
{
  return buffer.size() - protoHdrWireSize();
}

size_t CNRawIPTransMessage::rxIPOffset()
{
  return ((buffer[0] & 0xF) << 2);
}

bool CNRawIPTransMessage::isIP4()
{
  return (buffer[0] & 0xF0) == 4; //4 is IPv4
}

CNRawIPTransport::CNRawIPTransport() : CNTransport()
{

}

CNRawIPTransport::~CNRawIPTransport()
{
  while (outstandingMessages.begin() != outstandingMessages.end()) {
    returnToFactory(*(outstandingMessages.begin()));
    outstandingMessages.pop_front();
  }
}

CNErrorCode CNRawIPTransport::txData(CNMessage *msg)
{
  CNErrorCode ret = CN_SUCCESS;
  CNRawIPTransMessage *concreteMsg = static_cast<CNRawIPTransMessage*>(msg);
  CNMessage *tmpMsg = NULL;
  sockaddr_in sockAddr;
  size_t txLen = protoHdrWireSize();

  memset(&sockAddr, 0 , sizeof(sockAddr));

  if (fileDesc < 0) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_NOT_READY, 1);
    goto error;
  }

  if (ctx == NULL) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_NOT_READY, 4);
    goto error;
  }

  if (msg->derivedType() != CN_DER_RAW) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_WRONG_MSG_DER, 1);
    goto error;
  }

  if (inet_pton(AF_INET, "255.255.255.255", (in_addr *)&sockAddr.sin_addr) != 1) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_INTERNAL, 4);
    goto error;
  }
  sockAddr.sin_family = AF_INET;

  txLen += concreteMsg->txHeader()->dataLen;
  if (concreteMsg->buffer.size() < txLen) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_BUF_TOO_SMALL, 1);
    goto error;
  }

  concreteMsg->txHeader()->magic = htonl(CN_PROTO_MAGIC);
  memcpy(concreteMsg->txHeader()->src, ctx->id.strVal().c_str(), CNID::length);

  if (sendto(fileDesc, &concreteMsg->buffer[0],
        txLen, 0, (sockaddr *)&sockAddr,
    sizeof(sockaddr)) != (int)txLen) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_INTERNAL, 5);
    goto error;
  }

  // Raw sockets face a kind of "echo," so we need to grab the frame we just sent.
  // If it's not the one we just sent, we stash it away for the next Rx.
  // XXX: This probably needs more work. If we don't rx often enough, we can cause
  // a "soft" memory leak.
  ret = rxData(&tmpMsg);
  if (ret != CN_SUCCESS) {
    goto error;
  }
  if (tmpMsg) {
    try {
      outstandingMessages.push_back(tmpMsg);
    }
    catch (...) {
      ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_OOM, 1);
      goto error;
    }
  }

error:
  return ret;
}

CNErrorCode CNRawIPTransport::rxData(CNMessage **msg)
{
  CNErrorCode ret = CN_SUCCESS;
  CNRawIPTransMessage *concreteMsg = NULL;
  CNProtoHdr *hdr = NULL;

  *msg = NULL;

  if (fileDesc < 0) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_NOT_READY, 2);
    goto error;
  }

  if (ctx == NULL) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_NOT_READY, 3);
    goto error;
  }

  if (outstandingMessages.size() > 0) {
    *msg = *outstandingMessages.begin();
    outstandingMessages.pop_front();
    goto error;
  }

  concreteMsg = static_cast<CNRawIPTransMessage *>(messageFactory());
  if (concreteMsg == NULL) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_MSG_ALLOCATE, 1);
    goto error;
  }

  if (read(fileDesc, &concreteMsg->buffer[0],
        concreteMsg->buffer.size()) == -1) {
    returnToFactory(concreteMsg);
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_INTERNAL, 6);
    goto error;
  }

  hdr = ((CNProtoHdr*)((&concreteMsg->buffer[0]) +
         concreteMsg->rxIPOffset()));
  if (ntohl(hdr->magic) == CN_PROTO_MAGIC &&
    memcmp(hdr->src, ctx->id.strVal().c_str(), CNID::length) &&
    (memcmp(hdr->dst, ctx->id.strVal().c_str(), CNID::length) == 0 ||
     memcmp(hdr->dst, CNID::broadcastID.c_str(), CNID::length) == 0)) {
    concreteMsg->isRx = true;
    *msg = concreteMsg;
  }
  else {
    returnToFactory(concreteMsg);
  }

error:
  return ret;
}

CNErrorCode CNRawIPTransport::shutdown()
{
  CNErrorCode ret = CN_SUCCESS;

  if (fileDesc > -1)
    close(fileDesc);

  fileDesc = -1;
  ctx = NULL;

  return ret;
}

CNMessage * CNRawIPTransport::messageFactory()
{
  CNMessage *ret = NULL;

  /*
   * We could set up a pool of these to have at the ready in order to
   * speed access and reduce memory fragmentation. For now, just pull
   * a new one from the heap each time.
   */
  ret = new (std::nothrow)CNRawIPTransMessage;

  return ret;
}

void CNRawIPTransport::returnToFactory(CNMessage *msg)
{
  /*
   * If we were to set up a pool of these, we'd just return it
   * to the pool. Instead, we just delete.
   */
  delete msg;
}

CNErrorCode CNRawIPTransport::init(uint8_t protoNum)
{
  CNErrorCode ret = CN_SUCCESS;
  int broadcast = 1;

  fileDesc = socket(AF_INET, SOCK_RAW, protoNum);
  if (fileDesc < 0) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_INTERNAL, 2);
    goto error;
  }

  if (setsockopt(fileDesc, SOL_SOCKET, SO_BROADCAST, &broadcast,
    sizeof(broadcast)) ==-1) {
    ret = CN_BUILD_ERROR(CN_TRANSPORT, CN_INTERNAL, 3);
    goto error;
  }

error:
  return ret;
}
