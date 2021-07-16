#ifndef __CN_ID_H__
#define __CN_ID_H__

/**
* @file CNID.h
*
* @brief A means for abstracting unique ID generation and comparison.
*/

#include <string>

#include "CNError.h"

/**
* @class CNID
* @brief A unique identifer in the Connection System. Internally stored as a string since
* most operations will require conversion to/from string, including comparisons.
*
* @details This class is used to uniquely identify instances in a CN network. This means that
* it is used for addressing nodes. Uniqueness is provided by libuuid.
*/
class CNID {
public:

  CNID();
  CNID(const std::string &str);
  ~CNID();
  bool operator==(const CNID &other) const;
  bool operator<(const CNID &other) const;
  CNErrorCode fromStr(const std::string &str);
  /// This will generate a unqiue ID and store it in this object.
  CNErrorCode generate();

  const std::string & strVal();

  //From manpage for uuid_unparse()
  /// The length of an ID as it is shown on the wire.
  static const size_t length = 36;
  /// The ID used to refer to "all nodes."
  static std::string broadcastID;
private:
  std::string ctxID;
};

#endif
