/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTrace.cpp
 * \brief     O-RAN radio trace module handler
 *
 *
 * \details   O-RAN radio trace module handler
 *
 * This module defines the operations for the trace logs.
 *
 * module: o-ran-trace
 *
 *   rpcs:
 *     +--x start-trace-logs
 *     |  +--ro output
 *     |     +--ro status?         enumeration
 *     |     +--ro failure-reason? string
 *     +--x stop-trace-logs
 *        +--ro output
 *           +--ro status?         enumeration
 *           +--ro failure-reason? string
 *
 *   notifications:
 *     +--n trace-log-generated
 *        +--ro log-file-name*        string
 *        +--ro is-notification-last? boolean
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITraceMgr.h"

#include "Zcu111FbcOranrrhHandlerORanTrace.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanTrace::Zcu111FbcOranrrhHandlerORanTrace(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: Zcu111FbcOranrrhHandlerORanLog(moduleMgr,
	                                 "o-ran-trace",
	                                 "Zcu111FbcOranrrhHandlerORanTrace",
	                                 "start-trace-logs",
	                                 "stop-trace-logs",
	                                 "trace-log-generated")
{
	fileManager()->setFileCompression(false);
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanTrace::~Zcu111FbcOranrrhHandlerORanTrace()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IORanLogFileMgr> Zcu111FbcOranrrhHandlerORanTrace::fileManager()
{
	return ITraceMgr::singleton();
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
