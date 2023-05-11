/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanTroubleshooting.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITroubleshootMgr.h"

#include "Zcu111FbcOranrrhHandlerORanTroubleshooting.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

Zcu111FbcOranrrhHandlerORanTroubleshooting::Zcu111FbcOranrrhHandlerORanTroubleshooting(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: Zcu111FbcOranrrhHandlerORanLog(moduleMgr,
	                                 "o-ran-troubleshooting",
	                                 "Zcu111FbcOranrrhHandlerORanTroubleshooting",
	                                 "start-troubleshooting-logs",
	                                 "stop-troubleshooting-logs",
	                                 "troubleshooting-log-generated")
{
	fileManager()->setFileCompression(false);
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanTroubleshooting::~Zcu111FbcOranrrhHandlerORanTroubleshooting()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
std::shared_ptr<IORanLogFileMgr> Zcu111FbcOranrrhHandlerORanTroubleshooting::fileManager()
{
	return ITroubleshootMgr::singleton();
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================
