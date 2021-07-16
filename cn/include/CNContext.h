#ifndef __CN_CTX_H__
#define __CN_CTX_H__

/**
* @file CNContext.h
*
* @brief Types to maintain instance-specific configuration and state
*/

#include "CNID.h"

/**
* @struct CNContext
* @brief Globally-applicable state, config, etc.
*/
struct CNContext
{
  CNID id; /// The instance program's id.
};

#endif
