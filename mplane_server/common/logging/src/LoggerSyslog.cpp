/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerSyslog.cpp
 * \brief     Syslog variant of ILogger
 *
 *
 * \details   Provides the ILogger interface, logging to Linux syslog
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <syslog.h>

#include <cstdarg>
#include <cstdio>
#include <iostream>

#ifdef OFF_TARGET
#include "AnsiEsc.h"
#endif

#include "LoggerSyslog.h"

using namespace Mplane;

//=============================================================================================================
// PROTECTED STATIC DATA
//=============================================================================================================
Mutex LoggerSyslog::mMutex;
std::string LoggerSyslog::mForwardHost("");

#ifdef OFF_TARGET
bool LoggerSyslog::mConsoleLogging(true);
#else
bool LoggerSyslog::mConsoleLogging(false);
#endif

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
ILogger::getLogConsole() {
  Mutex::Lock lock(LoggerSyslog::mMutex);
  return LoggerSyslog::mConsoleLogging;
}

//-------------------------------------------------------------------------------------------------------------
void
ILogger::setLogConsole(bool consoleLogging) {
  Mutex::Lock lock(LoggerSyslog::mMutex);
  LoggerSyslog::mConsoleLogging = consoleLogging;
}

//-------------------------------------------------------------------------------------------------------------
bool
ILogger::setForwarding(const std::string& host) {
  Mutex::Lock lock(LoggerSyslog::mMutex);

  std::string cmd("/bin/sh /etc/init.d/01_syslog.sh forward " + host);
#ifdef OFF_TARGET
  std::cerr << "ILogger::setForwarding() CMD: " << cmd << std::endl;
#else
  int rc = ::system(cmd.c_str());
  if (rc != 0)
    return false;
#endif

  LoggerSyslog::mForwardHost = host;
  return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string
ILogger::getForwarding() {
  Mutex::Lock lock(LoggerSyslog::mMutex);
  return LoggerSyslog::mForwardHost;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LoggerSyslog::LoggerSyslog(
    ILoggable* parent,
    const std::string& instanceName,
    const std::string& groupName)
    : LoggerBase(parent, instanceName, groupName) {}

//-------------------------------------------------------------------------------------------------------------
LoggerSyslog::~LoggerSyslog() {}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::eventData(const std::string& eventStr) const {
  std::string str(std::string("[data] ") + eventStr);
  ::syslog(LOG_NOTICE, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout << str << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::eventInfo(const std::string& eventStr) const {
  std::string str(std::string("[info] ") + eventStr);
  ::syslog(LOG_INFO, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("Dark Blue") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::eventWarning(const std::string& eventStr) const {
  std::string str(std::string("[warn] ") + eventStr);
  ::syslog(LOG_WARNING, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("Black", "Yellow") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::eventError(const std::string& eventStr) const {
  std::string str(std::string("[error] ") + eventStr);
  ::syslog(LOG_ERR, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("White", "Red") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::eventFatal(const std::string& eventStr) const {
  std::string str(std::string("[fatal] ") + eventStr);
  ::syslog(LOG_CRIT, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("Yellow", "Red") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::dataHourly(
    const std::string& dataSource, const std::string& dataStr) const {
  std::string str(std::string("[hour] ") + dataSource + ":" + dataStr);
  ::syslog(LOG_INFO, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout << str << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::dataDaily(
    const std::string& dataSource, const std::string& dataStr) const {
  std::string str(std::string("[day] ") + dataSource + ":" + dataStr);
  ::syslog(LOG_INFO, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout << str << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::logDebugNormal(const std::string& debugStr) const {
  std::string str(std::string("[debug] ") + debugStr);
  ::syslog(LOG_DEBUG, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("Dark Cyan") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
LoggerSyslog::logDebugVerbose(const std::string& debugStr) const {
  std::string str(std::string("[DEBUG] ") + debugStr);
  ::syslog(LOG_DEBUG, "%s", str.c_str());

  Mutex::Lock lock(LoggerSyslog::mMutex);
  if (LoggerSyslog::mConsoleLogging)
    std::cout <<
#ifdef OFF_TARGET
        AnsiEsc::setColour("Dark Cyan") <<
#endif
        str <<
#ifdef OFF_TARGET
        AnsiEsc::resetColour() <<
#endif
        std::endl;
}
