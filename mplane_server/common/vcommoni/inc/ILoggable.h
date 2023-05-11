/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILoggable.h
 * \brief     Interface for any loggable object
 *
 *
 * \details   Provides the methods for loggable objects. Also provides the
 * ILogger log methods
 *
 */

#ifndef ILOGGABLE_H_
#define ILOGGABLE_H_

#include <memory>
#include <ostream>

#include "ILogData.h"
#include "ILogDebug.h"
#include "ILogEvent.h"

namespace Mplane {

class ILoggable : public virtual ILogEvent,
                  public virtual ILogDebug,
                  public virtual ILogData {
 public:
  ILoggable() {}
  virtual ~ILoggable() {}

  // Debug logging levels
  enum LogDebugLevel {
    LOG_DEBUG_NONE = 0,
    LOG_DEBUG_NORMAL = 1,
    LOG_DEBUG_VERBOSE = 2,
  };

  // General logging levels
  // sorted in order of priority
  enum LogLevel {
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_DEBUG = 1,
    LOG_LEVEL_INFO = 2,
    LOG_LEVEL_DATA = 3,
    LOG_LEVEL_WARNING = 4,
    LOG_LEVEL_ERROR = 5,
    LOG_LEVEL_FATAL = 6,
  };

  /**
   * Variable names used to set/save logging settings in the environment
   */
  static std::string GROUP_LOG_ENV_VARNAME;
  static std::string INST_LOG_ENV_VARNAME;

  // Object Interface

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

  /**
   * All loggable objects must be able to display themselves in the test
   * interface (this may also be used for debug output)
   */
  virtual void show(std::ostream& os) const = 0;

  /**
   * All loggable objects must be able to provide a string of information
   * suitable for storing in a log
   */
  virtual std::string info() const = 0;

  /**
   * Compares the specified level with this instance's level. If the specified
   * level is greater than or equal to the instance's level then returns true
   * @param level
   * @return true if instance exists and specified level >= instance's level;
   * otherwise false
   */
  virtual bool isDebug(LogDebugLevel level) const = 0;

  // Add formatted version of standard log methods

  // Debug

  /**
   * Log the string if debug log level is greater than or equal to "normal"
   * setting, with string formatting
   * @param fmt Format string
   */
  virtual void logDebugNormal(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * Log the string if debug log level is greater than or equal to "verbose"
   * setting, with string formatting
   * @param fmt Format string
   */
  virtual void logDebugVerbose(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  // Event

  /**
   * log a data event (e.g. an ARD command)
   */
  virtual void eventData(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * log informational event
   */
  virtual void eventInfo(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * log a warning
   */
  virtual void eventWarning(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * log a non-fatal error
   */
  virtual void eventError(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * log a fatal error (and terminate)
   */
  virtual void eventFatal(char const* fmt, ...) const
      __attribute__((format(printf, 2, 3))) = 0;

  /**
   * log a fatal error with extra debug information (and terminate)
   */
  virtual void eventFatal(
      char const* filename,
      int line,
      unsigned long errNumber,
      char const* fmt,
      ...) const __attribute__((format(printf, 5, 6))) = 0;

  // Accessors

  /**
   * Accessor used to change the current log level on this instance
   * @param level
   */
  virtual void setLevel(ILoggable::LogDebugLevel level) = 0;

  /**
   * Accessor used to change the current log level on this instance
   * @param level
   */
  virtual ILoggable::LogDebugLevel getLevel() const = 0;

  // Static Interface

  /**
   * Stop registering any new objects (i.e. once application has initialised).
   * Any subsequent objects attempting to register will cause an application
   * error
   */
  static void closeRegistration();

  /**
   * Show the list of registered ILogger objects
   * @param os
   */
  static void showList(std::ostream& os);

  /**
   * Convert the level value into a string
   * @param level
   * @return string representation of level
   */
  static std::string levelStr(LogDebugLevel level);

  /**
   * Convert the string into a level value
   * @param levelStr string representation of level
   * @return level (or 'off' if string does not represent any level)
   */
  static LogDebugLevel strToLevel(const std::string& levelStr);

  /**
   * Set the level of debug logging for all loggable objects
   * @param level Level of logging - if the requested log is at or greater than
   * this level then it will be logged
   */
  static void setLogDebugLevel(LogDebugLevel level);

  /**
   * Set the level of debug logging for the specified group of loggable objects
   * @param level Level of logging - if the requested log is at or greater than
   * this level then it will be logged
   * @param groupName Name of the group of objects to change
   * @return false if unable to find group
   */
  static bool setGroupLogDebugLevel(
      LogDebugLevel level, const std::string& groupName);

  /**
   * Set the level of debug logging for the specified loggable object instance
   * @param level Level of logging - if the requested log is at or greater than
   * this level then it will be logged
   * @param instanceName Name of the object to change
   * @return false if unable to find instance
   */
  static bool setInstanceLogDebugLevel(
      LogDebugLevel level, const std::string& instanceName);

  /**
   * Write the message to the stream
   * @param os    Output stream
   * @param msg    Message
   */
  static void logStream(std::ostream& os, const std::string& msg);

  /**
   * Write the message to the stream with formatting
   * @param os    Output stream
   * @param fmt    Format string
   */
  static void logStream(std::ostream& os, char const* fmt, ...)
      __attribute__((format(printf, 2, 3)));

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

  /**
   * Make the current debug logging settings persistent across reboots (relies
   * on u-boot environment)
   * @return
   */
  static bool saveSettings();

  // Static event interface

  /**
   * log a data event (e.g. an ARD command)
   */
  static void logEventData(const std::string& eventStr);

  /**
   * log informational event
   */
  static void logEventInfo(const std::string& eventStr);

  /**
   * log a warning
   */
  static void logEventWarning(const std::string& eventStr);

  /**
   * log a non-fatal error
   */
  static void logEventError(const std::string& eventStr);

  /**
   * log a fatal error (and terminate)
   */
  static void logEventFatal(const std::string& eventStr);

  /**
   * log a data event (e.g. an ARD command)
   */
  static void logEventData(char const* fmt, ...)
      __attribute__((format(printf, 1, 2)));

  /**
   * log informational event
   */
  static void logEventInfo(char const* fmt, ...)
      __attribute__((format(printf, 1, 2)));

  /**
   * log a warning
   */
  static void logEventWarning(char const* fmt, ...)
      __attribute__((format(printf, 1, 2)));

  /**
   * log a non-fatal error
   */
  static void logEventError(char const* fmt, ...)
      __attribute__((format(printf, 1, 2)));

  /**
   * log a fatal error (and terminate)
   */
  static void logEventFatal(char const* fmt, ...)
      __attribute__((format(printf, 1, 2)));

  /**
   * log a fatal error with extra debug information (and terminate)
   */
  static void logEventFatal(
      char const* filename,
      int line,
      unsigned long errNumber,
      char const* fmt,
      ...) __attribute__((format(printf, 4, 5)));

  // Static data interface

  /**
   * log an hourly data event
   * @param dataSource    Name of data source
   * @param dataStr        String to log
   */
  static void logDataHourly(
      const std::string& dataSource, const std::string& dataStr);

  /**
   * log a daily data event
   * @param dataSource    Name of data source
   * @param dataStr        String to log
   */
  static void logDataDaily(
      const std::string& dataSource, const std::string& dataStr);

 protected:
  /**
   * Get a local singleton instance (used for the static event/data logging
   */
  static std::shared_ptr<ILoggable> staticInstance();
};

} // namespace Mplane

#endif /* ILOGGABLE_H_ */
