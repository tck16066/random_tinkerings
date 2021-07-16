#ifndef __CN_NEIGHBOR_H__
#define __CN_NEIGHBOR_H__

/**
* @file CNNeighbor.h
*
* @brief Neighbor state management.
*/

#include <map>
#include <list>
#include <stdint.h>

#include "CNRawIPTransport.h"
#include "CNContext.h"
#include "CNTransport.h"

/**
* @struct CNNeighborState
* @brief Maintains information about neighbors on the CN network.
*/
struct CNNeighborState
{
  /// Time a ping was sent to a CN. Set by the CNNeighborStateManager.
  uint64_t pingSent;
  /// Time a ping response arrived. Set by the CNNeighborStateManager.
  uint64_t pingArrived;
};

/**
* @class CNNeighborStateManager
* @brief Used to maintain interactions between Connection Nodes. Makes calls to transport
* interfaces to receive and transmit to the wire. Maintains "connection" information between
* neighboring nodes.
*/
class CNNeighborStateManager
{
private:
  typedef std::map<CNID, CNNeighborState> CNNeighborCollection;
  typedef std::map<CNID, CNTransport *> CNIDTransportCollection;
  typedef std::map<int, CNTransport *> CNTransCollection;

public:
  typedef std::list<CNID> CNNeighborList;

  CNNeighborStateManager();
  ~CNNeighborStateManager();

  /**
  * Initialization routine. Caller retains ownership of arguments.
  *
  * @param ctx     Global program context/config
  * @param raw     Raw IP socket transport. Used for global comms.
  */
  void init(CNContext *ctx, CNRawIPTransport *raw);

  /**
  * Do we already know about this neighbor?
  */
  bool neighborPresent(CNID *neighbor);

  /**
  * Add neighbor to internal index, along with the transport it uses. This will typically
  * be called internally to the CNNeighborManager but is exposed for manual manipulation
  * of the indexes.
  *
  * @param neighbor    The neighbor to add
  * @param transport   The transport used by the neighbor.
  */
  CNErrorCode addNeighbor(CNID *neighbor, CNTransport *transport);

  /**
  * Block for a designated number of milliseconds, until a transport is ready for
  * a read operation.
  *
  * @param mSecDelay    milliseconds to block when no input available.
  */
  CNErrorCode listenNeighbors(uint32_t mSecDelay);

  /**
  * Send a ping message to all known nodes on the network on their own transports.
  */
  CNErrorCode pingNeighbors();

  /**
  * Advertise this program instance's presence on the CN network. Broadcasts over the
  * raw IP transport.
  */
  CNErrorCode advertise();

  /**
  * Retrieve a list of the neighbors that this instance knows about.
  *
  * @param list    Where the neighbors are stored.
  */
  CNErrorCode knownNeighbors(CNNeighborList *list);

  /**
  * Retrieve the state for a specific neighbor.
  *
  * @param id       The neighbor whose state we want to see.
  * @param state    Set on output to the state of the neighber, if found.
  */
  CNErrorCode neighborState(CNID *id, CNNeighborState **state);

private:
  CNContext *ctx;
  CNRawIPTransport *rawTrans;
  CNNeighborCollection neighbors;
  CNTransCollection transports;
  CNIDTransportCollection idToTransports;

  CNErrorCode handleRxMessage(CNMessage *msg, CNTransport *trans);
  void fillTxMessage(CNMessage *msg, CNMessageType type, CNID *dst);

  CNNeighborStateManager(const CNNeighborStateManager &) {}
};

#endif
