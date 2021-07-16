#include <uuid/uuid.h>
#include <new>

#include "CNID.h"

//From manpage for uuid_unparse()
#define UUID_CSTR_LEN  (this->length + 1)

std::string CNID::broadcastID = "ffffffff-ffff-ffff-ffff-ffffffffffff";

CNID::CNID(){}

CNID::CNID(const std::string &str)
{
  ctxID = str;
}

CNID::~CNID() {}

bool CNID::operator==(const CNID &other) const
{
  return ctxID.compare(other.ctxID) == 0;
}

bool CNID::operator<(const CNID &other) const
{
  return ctxID.compare(other.ctxID) < 0;
}

CNErrorCode CNID::generate()
{
  uuid_t id;
  char *tmp_arr = new (std::nothrow) char[UUID_CSTR_LEN];
  CNErrorCode ret = CN_SUCCESS;

  if (!tmp_arr) {
    ret = CN_BUILD_ERROR(CN_UID, CN_OOM, 1);
    goto error;
  }

  uuid_generate(id);
  uuid_unparse(id, tmp_arr);

  try {
    ctxID.assign(tmp_arr, UUID_CSTR_LEN);
  }
  catch (...) {
    ret = CN_BUILD_ERROR(CN_UID, CN_INTERNAL, 1);
    goto error;
  }


error:
  if (tmp_arr)
    delete tmp_arr;

  return ret;
}

const std::string & CNID::strVal()
{
  return ctxID;
}

CNErrorCode CNID::fromStr(const std::string &str)
{
  CNErrorCode ret = CN_SUCCESS;
  try {
    ctxID = str;
  }
  catch (...) {
    ret = CN_BUILD_ERROR(CN_UID, CN_OOM, 2);
    goto error;
  }

error:
  return ret;
}
