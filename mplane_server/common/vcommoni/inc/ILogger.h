/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILogger.h
 * \brief     Logger interface
 *
 *
 * \details   Interface to class that provides log support
 *
 */

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <memory>

#include "ILogData.h"
#include "ILogDebug.h"
#include "ILogEvent.h"

namespace Mplane {

// Forward
class ILoggable;

class ILogger : public ILogEvent, public ILogDebug, public ILogData {
 public:
  ILogger() {}
  virtual ~ILogger() {}

  /**
   * A factory for creating instances of ILogger
   * @param loggableParent    Pointer to the parent object (so ILogger can
   * call it's ILoggable methods)
   * @param instanceName        An instance name for the parent
   * @param groupName            A group name for the parent
   * @return shared pointer to an ILogger object
   */
  static std::shared_ptr<ILogger> factory(
      ILoggable* loggableParent,
      const std::string& instanceName,
      const std::string& groupName);

  /**
   * Get the object's unique instance name
   * @return instance name
   */
  virtual std::string getInstanceName(void) const = 0;

  /**
   * Get the name of the group this object belongs to
   * @return group name
   */
  virtual std::string getGroupName(void) const = 0;

  // Static interface

  /**
   * Is logging to console enabled?
   * @return true if console logging enabled
   */
  static bool getLogConsole();

  /**
   * Change console logging setting
   * @param consoleLogging New setting
   */
  static void setLogConsole(bool consoleLogging);

  /**
   * Set log forwarding to specified host name or ip
   * @param host    Name or ip of host to forward logs to. If empty then
   * disables forwarding
   * @return true if enabled/disabled forwarding ok
   */
  static bool setForwarding(const std::string& host);

  /**
   * Get the current log forwarding destination
   * @return
   */
  static std::string getForwarding();
};

} // namespace Mplane

#endif /* ILOGGER_H_ */
