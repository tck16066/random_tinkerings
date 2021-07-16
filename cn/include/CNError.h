#ifndef __CN_ERROR_H__
#define __CN_ERROR_H__

/**
* @file CNError.h
*
* @brief Types and macros for system return codes.
*/

#include <stdint.h>

/// A return code in the Connection Node system
typedef uint32_t CNErrorCode;

/**
* @enum CNErrorVal
* @brief Error/Return codes for CN program and framework. Error codes are composed of
* a subsystem, code, and subcode.
*/
enum CNErrorVal
{
  // No need to number each one individually, but we do so for ease of
  // human lookups.

  /// No error
  CN_SUCCESS        = 0,
  /// Out of Memory
  CN_OOM            = 1,
  /// Interal (system) error
  CN_INTERNAL       = 2,
  /// Supplied buffer is too small for the operation
  CN_BUF_TOO_SMALL  = 3,
  /// The message is too large to transmit on this transport
  CN_MSG_TOO_BIG    = 4,
  /// The object is has not been fully initialized
  CN_NOT_READY      = 5,
  /// Wrong derived message type passed to transport
  CN_WRONG_MSG_DER  = 6,
  /// Could not allocate message
  CN_MSG_ALLOCATE   = 7,
  /// ID not found in index
  CN_ID_NOT_FOUND  =  8,
  /// Bad argument supplied
  CN_BAD_ARG,

  /// The function has not been implemented
  CN_NOT_IMPLEMENTED
};

/**
* @enum CNSubsysCode
* @brief A subsystem of an error code, gives hints as to where the error happened. The name
* corresponds to a named part of the system, or derived class.
*/
enum CNSubsysCode
{
  CN_TRANSPORT   = 1,
  CN_UID         = 2,
  CN_MAIN        = 3,
  CN_NEIGHBOR    = 4,
  CN_UTILITY     = 5,
};

/**
* Construct an error code
*
* @param sys__       Subsystem the error occured in
* @param code__      The error that occured
* @param subcode__   The instance of the error in the subsystem
*/
#define CN_BUILD_ERROR(sys__, code__, subcode__)                               \
  ((((uint32_t)sys__) << 24) | (((uint32_t)code__) << 16)                      \
  | ((uint32_t)subcode__))

/// Extract the subsystem from a CNErrorCode
#define CN_SYS_DECODE(error__) (error__ >> 24)

/// Extract the error from a CNErrorCode
#define CN_CODE_DECODE(error__) ((error__ & 0x00FF0000) >> 16)

/// Extract the subcode from a CNErrorCode
#define CN_SUB_DECODE(error__) (error__ & 0x0000FFFF)

#endif
