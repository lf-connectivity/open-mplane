/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerSysrepo.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <functional>

#include "stringfunc.hpp"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"

#include "YangParamSysrepo.h"
#include "YangHandlerSysrepo.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangHandlerSysrepo::YangHandlerSysrepo(const std::string & moduleName, std::shared_ptr<IYangModuleMgr> moduleMgr, const std::string & logInstanceName) :
	YangHandlerSysrepoUnlogged(moduleName, moduleMgr),
	Loggable(logInstanceName, "YANG")
{
#ifdef OFF_TARGET
	Loggable::setLevel(ILoggable::LogDebugLevel::LOG_DEBUG_NORMAL);
#endif
}

//-------------------------------------------------------------------------------------------------------------
YangHandlerSysrepo::~YangHandlerSysrepo()
{
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void YangHandlerSysrepo::logInfo(const std::string &info)
{
	eventInfo(info) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string YangHandlerSysrepo::groupName() const
{
	return Loggable::getGroupName() ;
}
