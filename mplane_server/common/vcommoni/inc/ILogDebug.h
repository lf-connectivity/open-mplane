/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILogDebug.h
 * \brief     Debug logging methods
 *
 *
 * \details   Interface to the methods used for debug logging
 *
 */

#ifndef ILOGDEBUG_H_
#define ILOGDEBUG_H_

namespace Mplane {

class ILogDebug {
 public:
  ILogDebug() {}
  virtual ~ILogDebug() {}

  /**
   * Log the string if debug log level is greater than or equal to "normal"
   * setting
   * @param debugStr String to log
   */
  virtual void logDebugNormal(const std::string& debugStr) const = 0;

  /**
   * Log the string if debug log level is greater than or equal to "verbose"
   * setting
   * @param debugStr String to log
   */
  virtual void logDebugVerbose(const std::string& debugStr) const = 0;
};

} // namespace Mplane

#endif /* ILOGDEBUG_H_ */
