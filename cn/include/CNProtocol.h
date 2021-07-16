#ifndef __CN_PROTOCOL_H__
#define __CN_PROTOCOL_H__

/**
* @file CNProtocol.h
*
* @brief Types and definitions for protocol implementation
*/

#include <stdint.h>

#include "CNID.h"

#define CN_PROTO_MAGIC  0xC0FFEE

/**
* @enum CNMessageType
* @brief Commands/message values on the wire.
*/
enum __attribute__((__packed__)) CNMessageType
{
  /// Advertise program instance on the CN network
  CN_MSG_ADVERT = 1,
  /// Ask this node to respond to this message
  CN_MSG_PING,
  /// Response to a ping message
  CN_MSG_PONG,
};

/**
* @enum CNProtoHdr
* @brief A wire-format header for a message.
*/
struct __attribute__((__packed__)) CNProtoHdr
{
  /// Magic sequence to indicate this is our protocol
  uint32_t magic;
  /// Command/response to type
  enum CNMessageType type;
  /// Source ID of message
  uint8_t src[CNID::length];
  /// Destination ID of message
  uint8_t dst[CNID::length];
  /// Length of data section
  uint16_t dataLen;
  /// Does not get transmitted on to wire. Address of this member indicates start of data in memory.
  uint8_t payload;
};

/**
* Retrieve the size of a message header as seen on the wire.
*
* @return    Length of the fixed-sized header.
*/
size_t protoHdrWireSize();

/**
 * @enum CNMessageDerived
 * @brief A clunky way to ensure that a derived CNMessage type can be safely cast to a
 * concrete type in the CNTransport instances, but faster than a dynamic cast.
 */
enum CNMessageDerived
{
  CN_DER_RAW = 1,
};

/**
 * @class CNMessage
 *
 * @brief A communications abstraction class. Derived by internal CNTransport implementations.
 *
 * @details An adaptor class, so each CNTransport can correctly relay messages. Each transport
 * type may or may not have special rules for parsing messages rx'd on this transport.
 * for instance, raw sockets shouldn't make the caller care that the rx'd
 * message comes with an IP header.
 *
 * A message must be accessed differently based on whether it is to be transmitted or
 * received. Functions are provided.
 *
 * In the interest of time, we assume a fixed-size buffer that each transport
 * decides is appropriate. Perhaps wasteful, but can be remedied later in this class.
 */
class CNMessage
{
public:
  CNMessage(){}
  virtual ~CNMessage(){}
  /// Retrieve header from an Rx.
  virtual CNProtoHdr* rxHeader() = 0;
  /// Retrieve header for message to be Tx'd
  virtual CNProtoHdr* txHeader() = 0;
  /// What is our derived type?
  virtual CNMessageDerived derivedType() = 0;
  /// How much payload can this message type support in one buffer/message?
  virtual size_t payloadRoom() = 0;

private:
  CNMessage(const CNMessage &){}
};

#endif
