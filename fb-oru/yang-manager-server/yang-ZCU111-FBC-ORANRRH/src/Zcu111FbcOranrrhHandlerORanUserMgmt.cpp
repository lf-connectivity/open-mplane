/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanUserMgmt.cpp
 * \brief      ORAN user management Model module handler
 *
 *
 * \details   ORAN user management Model module handler
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "stringfunc.hpp"
#include "ILeafContainer.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanUserMgmt.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanUserMgmt::Zcu111FbcOranrrhHandlerORanUserMgmt(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-usermgmt", moduleMgr, "Zcu111FbcOranrrhHandlerORanUserMgmt")
{
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanUserMgmt::~Zcu111FbcOranrrhHandlerORanUserMgmt()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUserMgmt::initialise()
{
	// ------------------------------------------------------------------------
	// daisychain the initialisations
	// ------------------------------------------------------------------------
	if (!this->YangHandlerSysrepo::initialise())
		return false;


	// NOTE: We can't load this module until there is at least one enabled user, and that needs to be set up
	// on the start up data BEFORE any sysrepo connections. In other words it needs to be done in a start up script.
	// This code then has nothing to do!

	// NOTE2: This code's main reason for existing then is to provide rpc support. Thing is, the ietf-netconf-acm
	// access table shows that only sudo can access this module, and even then sudo can't do "exec" operations
	// so we never get to the point of being able to run the rpc!

	// register RPC callbacks
//	REGISTER_RPC("chg-password", Zcu111FbcOranrrhHandlerORanUserMgmt::rpcChgPassword) ;

	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanUserMgmt::rpcChgPassword(std::shared_ptr<sysrepo::Session> session,
		const std::string &rpcXpath, std::shared_ptr<YangParams> callList,
		std::shared_ptr<YangParams> retList)
{
	// NOT IMPLEMENTED BECAUSE ACM PREVENTS RPC FROM BEING RUN!
	return true ;
}
