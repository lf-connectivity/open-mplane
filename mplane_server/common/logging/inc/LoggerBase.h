/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerBase.h
 * \brief     Basic ILogger class
 *
 *
 * \details   Provides generic functionality that all ILogger classes must
 * implement
 *
 */

#ifndef LOGGERBASE_H_
#define LOGGERBASE_H_

#include "ILoggable.h"
#include "ILogger.h"

namespace Mplane {

class LoggerBase : public ILogger {
 public:
  LoggerBase(
      ILoggable* parent,
      const std::string& instanceName,
      const std::string& groupName);

  virtual ~LoggerBase();

  /**
   * Get the object's unique instance name
   * @return instance name
   */
  virtual std::string
  getInstanceName(void) const {
    return mInstanceName;
  }

  /**
   * Get the name of the group this object belongs to
   * @return group name
   */
  virtual std::string
  getGroupName(void) const override {
    return mGroupName;
  }

 protected:
  /**
   * Get the object's parent
   * @return An ILoggable object which contains this ILogger
   */
  ILoggable*
  getParent() const {
    return mParent;
  }

 private:
  ILoggable* mParent;
  std::string mInstanceName;
  std::string mGroupName;
};

} // namespace Mplane

#endif /* LOGGERBASE_H_ */
