/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIloggerFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LoggerSyslog.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILogger> ILogger::factory(ILoggable* loggableParent, const std::string& instanceName, const std::string& groupName)
{
	return std::shared_ptr<ILogger>(new LoggerSyslog(loggableParent, instanceName, groupName)) ;
}
