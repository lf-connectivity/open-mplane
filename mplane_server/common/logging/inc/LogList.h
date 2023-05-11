/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LogList.h
 * \brief     Maintain a list of registered logger objects
 *
 *
 * \details
 *
 */

#ifndef LOGLIST_H_
#define LOGLIST_H_

#include <map>

#include "ILoggable.h"
#include "Mutex.h"

namespace Mplane {

class LogList {
 public:
  LogList();
  virtual ~LogList();

  /**
   * Register an ILoggable object by adding it to the list
   * @param logger
   * @return true if added to list
   */
  bool add(ILoggable* logger);

  /**
   * Un-register an ILoggable object by removing it from the list
   * @param logger
   * @return true if removed from list
   */
  bool del(ILoggable* logger);

  /**
   * Display the list for debug
   * @param os    Output stream
   */
  void show(std::ostream& os) const;

  /**
   * Set the log level for all current entries
   * @param level
   */
  void setLevel(ILoggable::LogDebugLevel level);

  /**
   * Set the log level for every entry in the same group
   * @param level
   * @param groupName
   * @return true if found any names in the group
   */
  bool setGroupLevel(
      ILoggable::LogDebugLevel level, const std::string& groupName);

  /**
   * Set the log level for the single entry
   * @param level
   * @param instanceName
   * @return true if found an entry with this name
   */
  bool setInstanceLevel(
      ILoggable::LogDebugLevel level, const std::string& instanceName);

  /**
   * Given an instance name, ensures it is unique in the list
   * @param name    Instance name
   * @return unique version of name (or the original name if already unique)
   */
  std::string uniqueInstanceName(const std::string& name);

  /**
   * Given a group name, ensures it is valid (i.e. set to something and has no
   * spaces)
   * @param name    Group name
   * @return valid group name
   */
  std::string validGroupName(const std::string& name) const;

  /**
   * Given a group name, ensures it is valid (i.e. set to something and has no
   * spaces)
   * @param name    name
   * @param defaultName    default name
   * @return valid name
   */
  std::string validName(
      const std::string& name, const std::string& defaultName) const;

  /**
   * Stop registering any new objects (i.e. once application has initialised).
   * Any subsequent objects attempting to register will cause an application
   * error
   */
  void closeRegistration();

 public:
  // Display formatting - provided here for test purposes
  static const unsigned NAME_WIDTH;
  static const unsigned GROUP_WIDTH;
  static const unsigned LEVEL_WIDTH;

 private:
  /**
   * Get the current group level using a case-insensitive match on the name. If
   * there is no current setting then create one using the default value
   * specified
   * @param groupName
   * @param defaultLevel
   * @return group level
   */
  ILoggable::LogDebugLevel getGroupLevel(
      const std::string& groupName,
      ILoggable::LogDebugLevel defaultLevel = ILoggable::LOG_DEBUG_NONE);

  /**
   * Set the group level
   * @param groupName
   * @param level
   */
  void setGroupLevel(
      const std::string& groupName, ILoggable::LogDebugLevel level);

  /**
   * Get the current instance level using a case-insensitive match on the name.
   * If there is no current setting then create one using the default value
   * specified
   * @param instanceName
   * @param defaultLevel
   * @return instance level
   */
  ILoggable::LogDebugLevel getInstanceLevel(
      const std::string& instanceName,
      ILoggable::LogDebugLevel defaultLevel = ILoggable::LOG_DEBUG_NONE);

  /**
   * Set the instance level
   * @param instanceName
   * @param level
   */
  void setInstanceLevel(
      const std::string& instanceName, ILoggable::LogDebugLevel level);

 private:
  // Thread protection
  mutable Mutex mMutex;

  // map of names - used to create unique name
  std::map<std::string, unsigned> mUniqueNames;

  // map instance name to original name
  std::map<std::string, std::string> mUniqueMap;

  // map instance name to log level
  std::map<std::string, ILoggable::LogDebugLevel> mInstanceLevels;

  // map group name to log level
  std::map<std::string, ILoggable::LogDebugLevel> mGroupLevels;

  // List of all currently created Loggable instances
  std::map<std::string, ILoggable*> mList;

  // allow new objects to register
  bool mAllowRegistration;
};

} // namespace Mplane

#endif /* LOGLIST_H_ */
