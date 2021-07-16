#include "CNTransport.h"

CNTransport::CNTransport()
{
  fileDesc = -1;
  ctx = NULL;
}

CNTransport::~CNTransport() {}

int CNTransport::fd()
{
  return fileDesc;
}

void CNTransport::setCtx(CNContext *ctx)
{
  this->ctx = ctx;
}
