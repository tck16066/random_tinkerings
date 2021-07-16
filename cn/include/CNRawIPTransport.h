#ifndef __CN_RAW_IP_TRANS_H__
#define __CN_RAW_IP_TRANS_H__

/**
* @file CNRawIPTransport.h
*
* @brief Interface for using raw IP socket.
*/

#include <list>

#include "CNTransport.h"
#include "CNContext.h"
#include "CNProtocol.h"

/**
* @class CNRawIPTransport
* @brief A transport that uses a raw IP socket as the underlying comms mechanism
*/
class CNRawIPTransport : public CNTransport
{
public:
  CNRawIPTransport();
  virtual ~CNRawIPTransport();

  virtual CNErrorCode txData(CNMessage *msg);
  virtual CNErrorCode rxData(CNMessage **msg);
  virtual CNErrorCode shutdown();
  virtual CNMessage *messageFactory();
  virtual void returnToFactory(CNMessage *msg);

  /// @param protoNum   The IP protocol number to use
  CNErrorCode init(uint8_t protoNum = RAW_PROTO_NUM);

private:
  std::list<CNMessage *> outstandingMessages;
};

#endif
