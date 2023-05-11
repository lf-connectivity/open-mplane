/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanLog.cpp
 * \brief     ORAN log module handler base class
 *
 *
 * \details   ORAN log module handler base class
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "stringfunc.hpp"
#include "Path.h"
#include "ILoggable.h"

#include "XpathUtils.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"

#include "Zcu111FbcOranrrhHandlerORanLog.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanLog::Zcu111FbcOranrrhHandlerORanLog(std::shared_ptr<IYangModuleMgr> moduleMgr,
                                                             const std::string & moduleName,
                                                             const std::string & taskName,
                                                             const std::string & pathRpcStart,
                                                             const std::string & pathRpcStop,
                                                             const std::string & pathNotify)
	: YangHandlerSysrepoUnlogged(moduleName, moduleMgr)
	, TaskEvent(Task::PRIORITY_DEFAULT, Task::DEFAULT_STACK, taskName, "YANG")
	, mPathRpcStart(pathRpcStart)
	, mPathRpcStop(pathRpcStop)
	, mPathNotify(pathNotify)
	, mEnabled(false)
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanLog::~Zcu111FbcOranrrhHandlerORanLog()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanLog::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepoUnlogged::initialise())
		return false;

	// ------------------------------------------------------------------------
	// Initialise state data
	// ------------------------------------------------------------------------
	// No state data

	// ------------------------------------------------------------------------
	// Initialise configuration data
	// ------------------------------------------------------------------------
	// No configuration data

	// ------------------------------------------------------------------------
	// Register RPC callbacks
	// ------------------------------------------------------------------------
	REGISTER_RPC(mPathRpcStart, Zcu111FbcOranrrhHandlerORanLog::rpcStart);
	REGISTER_RPC(mPathRpcStop,  Zcu111FbcOranrrhHandlerORanLog::rpcStop);

	// ------------------------------------------------------------------------
	// Register callback for each top level container
	// ------------------------------------------------------------------------
	// No top level containers

	return true;

}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLog::logInfo(const std::string & info)
{
	eventInfo(info);
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanLog::rpcStart(std::shared_ptr<sysrepo::Session> session,
                                              const std::string & rpcXpath,
                                              std::shared_ptr<YangParams> callList,
                                              std::shared_ptr<YangParams> retList)
{
	mEnabled = true;
	event();

	// Scheduled ok
	statusOk(mPathRpcStart, retList);
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanLog::rpcStop(std::shared_ptr<sysrepo::Session> session,
                                             const std::string & rpcXpath,
                                             std::shared_ptr<YangParams> callList,
                                             std::shared_ptr<YangParams> retList)
{
	mEnabled = false;

	// Scheduled ok
	statusOk(mPathRpcStop, retList);
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLog::statusOk(const std::string & rpc,
                                              std::shared_ptr<YangParams> retList)
{
	retList->addParam("SUCCESS", path(rpc + "/status"));
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLog::statusFail(const std::string & rpc,
                                                std::shared_ptr<YangParams> retList,
                                                const std::string & reason)
{
	retList->addParam("FAILURE", path(rpc + "/status"));
	retList->addParam(reason, path(rpc + "/reject-reason"));
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanLog::notify(const std::vector<std::string> & paths)
{
	// Can't notify if there are no files
	if (paths.empty())
		return;

	std::shared_ptr<YangParams> params(std::make_shared<YangParams>());
	for (auto p : paths)
		params->addParam(p, mPathNotify + "/log-file-name");

	sendNotification(mPathNotify, params);
}

//=============================================================================================================
// PROTECTED THREAD
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanLog::runEvent()
{
	std::cerr << Task::getName() << "::runEvent - START" << std::endl;

	// Grab the log file data
	std::shared_ptr<IORanLogFileMgr> mgr = fileManager();
	if (!mgr->startLog())
		return true;

	while (!mgr->doneLog())
	{
		// Check to see if we've been stopped
		if (!mEnabled)
			return true;

		// Next file
		if (!mgr->nextLog())
			return true;
	}

	// Check to see if we've been stopped
	if (!mEnabled)
		return true;

	// Send notification
	std::vector<std::string> paths(mgr->paths());
	notify(paths);

	return true;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanLog::groupName() const
{
	return getGroupName();
}
