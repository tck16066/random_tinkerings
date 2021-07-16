#ifndef __CN_TRANSPORT_H__
#define __CN_TRANSPORT_H__

/**
* @file CNTransport.h
*
* @brief An interface for communicating with nodes on the CN Network.
*/

#include <stdint.h>
#include <stdlib.h>

#include "CNError.h"
#include "CNContext.h"
#include "CNID.h"
#include "CNProtocol.h"

/**
 * @class CNTransport
 * @brief A Transport is used to send/receive data. Different connection types
 * (raw socket, udp socket, named pipe, etc.) need different communication
 * semantics. This class abstracts those semantics.
 *
 * @details To transmit or receive messages, they must be allocated by the correct
 * transport type. Subclasses must return the transport to free/de-allocate the message.
 */
class CNTransport
{
public:
  CNTransport();
  virtual ~CNTransport();

  /// Transmit a message that the caller has set up for transmission.
  virtual CNErrorCode txData(CNMessage *msg) = 0;
  /// Receive data off the CN network. This call will block indefinitely if no message is available.
  virtual CNErrorCode rxData(CNMessage **msg) = 0;
  /// Uninitialize the transport for destruction.
  virtual CNErrorCode shutdown() = 0;
  /// Allocate a message and return to caller.
  virtual CNMessage *messageFactory() = 0;
  /// De-allocate a message that has been allocated by this transport.
  virtual void returnToFactory(CNMessage *msg) = 0;

  /// Retrive the file descriptor used by this transport.
  int fd();
  /// Set the global state to be used by this transport.
  void setCtx(CNContext *ctx);

protected:
  int fileDesc;
  CNContext *ctx;
  CNID remoteCNID;

private:
};


#endif
