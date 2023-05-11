/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      XpathUtils.h
 * \brief     Various static xpath utilities
 *
 *
 * \details   Various static xpath utilities
 *
 */

#ifndef YANG_HANDLERS_INC_XPATHUTILS_H_
#define YANG_HANDLERS_INC_XPATHUTILS_H_

#include <string>

namespace Mplane {

/*!
 * \class  XpathUtils
 * \brief
 * \details
 *
 */
class XpathUtils {
 public:
  XpathUtils() {}
  virtual ~XpathUtils() {}

  /**
   * Extract the leaf name of this xpath
   *
   * e.g. /path/to/a/leaf would return leaf
   */
  static std::string leafName(const std::string& xpath);

  /**
   * Remove the leaf name of this xpath and return just the path part.
   *
   * e.g. /path/to/a/leaf would return /path/to/a
   */
  static std::string leafPath(const std::string& xpath);

  /**
   * Get the *first* index (i.e. in "[]") contained in the xpath. Sets key and
   * value when xpath is of the form:
   *   /o-ran-uplane-conf:user-plane-configuration/rx-array-carriers[name='rxcco']/name
   *
   *   This will set: listName=rx-array-carriers, key=name, value=rxcc0
   *
   * will only set value when xpath is of the form:
   *   /o-ran-uplane-conf:user-plane-configuration/rx-array-carriers['rxcco']/name
   *
   *   This will set: listName=rx-array-carriers, key=, value=rxcc0
   *
   * Value will have the '' stripped off
   *
   * @return true if found
   */
  static bool listIndex(
      const std::string& xpath,
      std::string& listName,
      std::string& key,
      std::string& value);

  /**
   * Get the *first* index (i.e. in "[]") contained in the xpath. Value string
   * is converted into an integer
   */
  static bool listIndex(
      const std::string& xpath,
      std::string& listName,
      std::string& key,
      int& value);

  /**
   * Get the Nth index (i.e. in "[]") contained in the xpath. Uses the above
   * listIndex function, but uses the excludes the beginning portion of the
   * xpath containing N-1 occruences of "]".
   */
  static bool listIndexN(
      const std::string& xpath,
      std::string& listName,
      std::string& key,
      std::string& value,
      int n);
};

} // namespace Mplane

#endif /* YANG_HANDLERS_INC_XPATHUTILS_H_ */
