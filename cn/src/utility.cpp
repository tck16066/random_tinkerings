#include <time.h>

#include "utility.h"

CNErrorCode monoMSecs(uint64_t *msecs)
{
  CNErrorCode ret = CN_SUCCESS;
  timespec t;

  if (clock_gettime(CLOCK_MONOTONIC, &t) < 0) {
    ret = CN_BUILD_ERROR(CN_UTILITY, CN_INTERNAL, 1);
    goto error;
  }

  *msecs = (t.tv_sec * MILLI_PER_SEC) + (t.tv_nsec / NANO_PER_MILLI);

error:
  return ret;
}
