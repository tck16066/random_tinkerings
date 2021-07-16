#ifndef __UTILITY_H__
#define __UTILITY_H__

/**
* @file utility.h
*
* @brief Contains misc. various functions.
*/

#include "CNError.h"

#define NANO_PER_MILLI 1000000
#define MILLI_PER_SEC  1000

/**
* Retrive msec conversation of monotonic clock.
*/
CNErrorCode monoMSecs(uint64_t *msecs);

#endif
