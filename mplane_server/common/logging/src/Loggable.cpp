/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Loggable.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdarg>
#include <cstdio>
#include <map>
#include <sstream>

#include "Loggable.h"
#include "stringfunc.hpp"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================
namespace {
std::string
formatStr(const char* fmt, va_list& args) {
  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), fmt, args);

  return buffer;
}
} // namespace

//=============================================================================================================
// STATIC DATA
//=============================================================================================================
LogList Loggable::mLogList;

std::map<ILoggable::LogDebugLevel, std::string> LogLevelMap{
    {ILoggable::LOG_DEBUG_NONE, "Off"},
    {ILoggable::LOG_DEBUG_NORMAL, "Normal"},
    {ILoggable::LOG_DEBUG_VERBOSE, "Verbose"},
};

//=============================================================================================================
// PUBLIC - ILoggable
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Loggable::Loggable(
    const std::string& instanceName, const std::string& groupName)
    : mLogger(ILogger::factory(
          this,
          Loggable::mLogList.uniqueInstanceName(instanceName),
          Loggable::mLogList.validGroupName(groupName))),
      mLevel(ILoggable::LOG_DEBUG_NONE) {
  // Register object with list
  Loggable::mLogList.add(this);
}

//-------------------------------------------------------------------------------------------------------------
Loggable::Loggable(
    const std::string& instanceName,
    unsigned instanceNum,
    const std::string& groupName)
    : mLogger(ILogger::factory(
          this,
          Loggable::mLogList.uniqueInstanceName(
              instanceName + ":" + std::to_string(instanceNum)),
          Loggable::mLogList.validGroupName(groupName))),
      mLevel(ILoggable::LOG_DEBUG_NONE) {
  // Register object with list
  Loggable::mLogList.add(this);
}

//-------------------------------------------------------------------------------------------------------------
Loggable::~Loggable() {
  // Un-register object with list
  Loggable::mLogList.del(this);
}

//-------------------------------------------------------------------------------------------------------------
std::string
Loggable::getInstanceName(void) const {
  return mLogger->getInstanceName();
}

//-------------------------------------------------------------------------------------------------------------
std::string
Loggable::getGroupName(void) const {
  return mLogger->getGroupName();
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::show(std::ostream& os) const {
  os << getInstanceName() << " (" << getGroupName() << ")" << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
std::string
Loggable::info() const {
  std::stringstream ss;
  show(ss);
  return ss.str();
}

//-------------------------------------------------------------------------------------------------------------
bool
Loggable::isDebug(ILoggable::LogDebugLevel level) const {
  return mLevel >= level;
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::setLevel(ILoggable::LogDebugLevel level) {
  mLevel = level;
}

//-------------------------------------------------------------------------------------------------------------
ILoggable::LogDebugLevel
Loggable::getLevel() const {
  return mLevel;
}

//=============================================================================================================
// PUBLIC - ILogEvent
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventData(const std::string& eventStr) const {
  mLogger->eventData(eventStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventInfo(const std::string& eventStr) const {
  mLogger->eventInfo(eventStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventWarning(const std::string& eventStr) const {
  mLogger->eventWarning(eventStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventError(const std::string& eventStr) const {
  mLogger->eventError(eventStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventFatal(const std::string& eventStr) const {
  mLogger->eventFatal(eventStr);

  // TODO: Sort out this
  ::abort();
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventData(const char* fmt, ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  eventData(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventInfo(const char* fmt, ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  eventInfo(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventWarning(const char* fmt, ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  eventWarning(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventError(const char* fmt, ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  eventError(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventFatal(const char* fmt, ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  eventFatal(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::eventFatal(
    char const* filename,
    int line,
    unsigned long errNumber,
    const char* fmt,
    ...) const {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  std::stringstream ss;
  ss << filename << ":" << line << " error=" << errNumber << " " << str;
  eventFatal(ss.str());
}

//=============================================================================================================
// PUBLIC - ILogData
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
Loggable::dataHourly(
    const std::string& dataSource, const std::string& dataStr) const {
  mLogger->dataHourly(dataSource, dataStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::dataDaily(
    const std::string& dataSource, const std::string& dataStr) const {
  mLogger->dataDaily(dataSource, dataStr);
}

//=============================================================================================================
// PUBLIC - ILogDebug
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
Loggable::logDebugNormal(const std::string& debugStr) const {
  if (mLevel < LOG_DEBUG_NORMAL)
    return;

  mLogger->logDebugNormal(debugStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::logDebugNormal(const char* fmt, ...) const {
  if (mLevel < LOG_DEBUG_NORMAL)
    return;

  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  mLogger->logDebugNormal(str);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::logDebugVerbose(const std::string& debugStr) const {
  if (mLevel < LOG_DEBUG_VERBOSE)
    return;

  mLogger->logDebugVerbose(debugStr);
}

//-------------------------------------------------------------------------------------------------------------
void
Loggable::logDebugVerbose(const char* fmt, ...) const {
  if (mLevel < LOG_DEBUG_VERBOSE)
    return;

  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  mLogger->logDebugVerbose(str);
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::closeRegistration() {
  Loggable::mLogList.closeRegistration();
}

//-------------------------------------------------------------------------------------------------------------
std::string
ILoggable::levelStr(ILoggable::LogDebugLevel level) {
  return LogLevelMap.at(level);
}

//-------------------------------------------------------------------------------------------------------------
ILoggable::LogDebugLevel
ILoggable::strToLevel(const std::string& levelStr) {
  std::string levelStrLower(toLower(levelStr));
  for (auto entry : LogLevelMap) {
    if (toLower(entry.second) == levelStrLower)
      return entry.first;
  }
  return ILoggable::LOG_DEBUG_NONE;
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::showList(std::ostream& os) {
  Loggable::mLogList.show(os);
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::setLogDebugLevel(LogDebugLevel level) {
  Loggable::mLogList.setLevel(level);
}

//-------------------------------------------------------------------------------------------------------------
bool
ILoggable::setGroupLogDebugLevel(
    LogDebugLevel level, const std::string& groupName) {
  return Loggable::mLogList.setGroupLevel(level, groupName);
}

//-------------------------------------------------------------------------------------------------------------
bool
ILoggable::setInstanceLogDebugLevel(
    LogDebugLevel level, const std::string& instanceName) {
  return Loggable::mLogList.setInstanceLevel(level, instanceName);
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::logStream(std::ostream& os, const std::string& msg) {
  os << msg << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::logStream(std::ostream& os, char const* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  logStream(os, str);
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::setLogConsole(bool consoleLogging) {
  ILogger::setLogConsole(consoleLogging);
}

//-------------------------------------------------------------------------------------------------------------
bool
ILoggable::getLogConsole() {
  return ILogger::getLogConsole();
}

//-------------------------------------------------------------------------------------------------------------
bool
ILoggable::setForwarding(const std::string& host) {
  return ILogger::setForwarding(host);
}

//-------------------------------------------------------------------------------------------------------------
std::string
ILoggable::getForwarding() {
  return ILogger::getForwarding();
}

//=============================================================================================================
// STATIC ILoggable event interface
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#define ILOG_EVENT(nm)                                                   \
  void ILoggable::logEvent##nm(const std::string& eventStr) {            \
    std::shared_ptr<ILoggable> loggable(ILoggable::staticInstance());    \
    std::dynamic_pointer_cast<ILogEvent>(loggable)->event##nm(eventStr); \
  }                                                                      \
  void ILoggable::logEvent##nm(char const* fmt, ...) {                   \
    va_list args;                                                        \
    va_start(args, fmt);                                                 \
    std::string str(formatStr(fmt, args));                               \
    va_end(args);                                                        \
                                                                         \
    std::shared_ptr<ILoggable> loggable(ILoggable::staticInstance());    \
    std::dynamic_pointer_cast<ILogEvent>(loggable)->event##nm(str);      \
  }

ILOG_EVENT(Data)
ILOG_EVENT(Info)
ILOG_EVENT(Warning)
ILOG_EVENT(Error)
ILOG_EVENT(Fatal)

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::logEventFatal(
    char const* filename,
    int line,
    unsigned long errNumber,
    char const* fmt,
    ...) {
  va_list args;
  va_start(args, fmt);
  std::string str(formatStr(fmt, args));
  va_end(args);

  std::stringstream ss;
  ss << filename << ":" << line << " error=" << errNumber << " " << str;

  std::shared_ptr<ILoggable> loggable(ILoggable::staticInstance());
  std::dynamic_pointer_cast<ILogEvent>(loggable)->eventFatal(ss.str());
}

//=============================================================================================================
// STATIC ILoggable data interface
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::logDataHourly(
    const std::string& dataSource, const std::string& dataStr) {
  std::shared_ptr<ILoggable> loggable(ILoggable::staticInstance());
  std::dynamic_pointer_cast<ILogData>(loggable)->dataHourly(
      dataSource, dataStr);
}

//-------------------------------------------------------------------------------------------------------------
void
ILoggable::logDataDaily(
    const std::string& dataSource, const std::string& dataStr) {
  std::shared_ptr<ILoggable> loggable(ILoggable::staticInstance());
  std::dynamic_pointer_cast<ILogData>(loggable)->dataDaily(dataSource, dataStr);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILoggable>
ILoggable::staticInstance() {
  static std::shared_ptr<ILoggable> instance(
      std::make_shared<Loggable>(".STATIC", ".LOG"));
  return instance;
}
