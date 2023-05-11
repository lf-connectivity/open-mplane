/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Loggable.h
 * \brief     Implementation of ILoggable interface
 *
 *
 * \details   Implements the ILoggable interface using the ILogger factory to
 * provide actual logging support
 *
 */

#ifndef LOGGABLE_H_
#define LOGGABLE_H_

#include <cstdarg>
#include <memory>
#include <string>

#include "ILoggable.h"
#include "ILogger.h"
#include "LogList.h"

namespace Mplane {

class Loggable : public ILoggable {
 public:
  using LogDebugLevel = ILoggable::LogDebugLevel;

  /**
   * Constructor - set the instance name and group name
   */
  Loggable(const std::string& instanceName, const std::string& groupName);

  /**
   * Constructor - alternative which also sets the instance number where more
   * than one instance is expected (e.g. RX ports, TX ports etc)
   */
  Loggable(
      const std::string& instanceName,
      unsigned instanceNum,
      const std::string& groupName);

  virtual ~Loggable();

  // ILoggable

  /**
   * Get the object's unique instance name
   * @return instance name
   */
  virtual std::string getInstanceName(void) const override;

  /**
   * Get the name of the group this object belongs to
   * @return group name
   */
  virtual std::string getGroupName(void) const override;

  /**
   * All loggable objects must be able to display themselves in the test
   * interface (this may also be used for debug output)
   */
  virtual void show(std::ostream& os) const override;

  /**
   * All loggable objects must be able to provide a string of information
   * suitable for storing in a log
   */
  virtual std::string info() const override;

  /**
   * Compares the specified level with this instance's level. If the specified
   * level is greater than or equal to the instance's level then returns true
   * @param level
   * @return true if instance exists and specified level >= instance's level;
   * otherwise false
   */
  virtual bool isDebug(ILoggable::LogDebugLevel level) const override;

  /**
   * Accessor used to change the current log level on this instance
   * @param level
   */
  virtual void setLevel(ILoggable::LogDebugLevel level) override;

  /**
   * Accessor used to change the current log level on this instance
   * @param level
   */
  virtual ILoggable::LogDebugLevel getLevel() const override;

  // ILogEvent

  /**
   * log a data event (e.g. an ARD command)
   */
  virtual void eventData(const std::string& eventStr) const override;

  /**
   * log informational event
   */
  virtual void eventInfo(const std::string& eventStr) const override;

  /**
   * log a warning
   */
  virtual void eventWarning(const std::string& eventStr) const override;

  /**
   * log a non-fatal error
   */
  virtual void eventError(const std::string& eventStr) const override;

  /**
   * log a fatal error (and terminate)
   */
  virtual void eventFatal(const std::string& eventStr) const override;

  /**
   * log a data event (e.g. an ARD command)
   */
  virtual void eventData(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * log informational event
   */
  virtual void eventInfo(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * log a warning
   */
  virtual void eventWarning(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * log a non-fatal error
   */
  virtual void eventError(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * log a fatal error (and terminate)
   */
  virtual void eventFatal(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * log a fatal error with extra debug information (and terminate)
   */
  virtual void eventFatal(
      char const* filename,
      int line,
      unsigned long errNumber,
      char const* fmt,
      ...) const override __attribute__((format(printf, 5, 6)));

  // ILogDebug

  /**
   * Log the string if debug log level is greater than or equal to "normal"
   * setting
   * @param debugStr String to log
   */
  virtual void logDebugNormal(const std::string& debugStr) const override;

  /**
   * Log the string if debug log level is greater than or equal to "normal"
   * setting, with string formatting
   * @param fmt Format string
   */
  virtual void logDebugNormal(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  /**
   * Log the string if debug log level is greater than or equal to "verbose"
   * setting
   * @param debugStr String to log
   */
  virtual void logDebugVerbose(const std::string& debugStr) const override;

  /**
   * Log the string if debug log level is greater than or equal to "verbose"
   * setting, with string formatting
   * @param fmt Format string
   */
  virtual void logDebugVerbose(char const* fmt, ...) const override
      __attribute__((format(printf, 2, 3)));

  // ILogData

  /**
   * log an hourly data event
   * @param dataSource    Name of data source
   * @param dataStr        String to log
   */
  virtual void dataHourly(
      const std::string& dataSource, const std::string& dataStr) const override;

  /**
   * log a daily data event
   * @param dataSource    Name of data source
   * @param dataStr        String to log
   */
  virtual void dataDaily(
      const std::string& dataSource, const std::string& dataStr) const override;

 protected:
  friend class ILoggable;

 protected:
  // Log list
  static LogList mLogList;

 private:
  // Logger instance
  std::shared_ptr<ILogger> mLogger;

  // Current log level of this instance
  ILoggable::LogDebugLevel mLevel;
};

} // namespace Mplane

#endif /* LOGGABLE_H_ */
