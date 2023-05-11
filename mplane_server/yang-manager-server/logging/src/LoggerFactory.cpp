/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LoggerFactory.cpp
 * \brief     Create the instance of ILogger used for this application
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LoggerHistorySyslog.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILogger>
ILogger::factory(
    ILoggable* loggableParent,
    const std::string& instanceName,
    const std::string& groupName) {
  return std::shared_ptr<ILogger>(
      new LoggerHistorySyslog(loggableParent, instanceName, groupName));
}
