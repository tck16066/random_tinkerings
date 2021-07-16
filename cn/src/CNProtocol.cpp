#include "CNProtocol.h"

size_t protoHdrWireSize()
{
  return sizeof(CNProtoHdr) - 1;
}
