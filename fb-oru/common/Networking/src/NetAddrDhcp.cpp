/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrDhcp.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NetAddrDhcp.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrDhcp::NetAddrDhcp(const std::string& interface, const std::string& hostname, const std::string& dhcpScript, unsigned timeoutMs) :
	NetAddr("DHCP", INetChange::NET_DHCP, interface),
	mHostname(hostname),
	mScript(dhcpScript),
	mDhcp(std::make_shared<SystemTask>()),
	mCurrentIp()
{
	mDhcp->start() ;
}

//-------------------------------------------------------------------------------------------------------------
NetAddrDhcp::~NetAddrDhcp()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrDhcp::doStart()
{
	// save the current ip address (if any)
	mCurrentIp = interfaceUp() ;

	logDebugVerbose("[DHCP:%s] Start IP=%s", interface().c_str(), mCurrentIp.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrDhcp::doAllocate()
{
	// Attempt DHCP
	if (runDhcp())
	{
		// All done
		setIpAddress(interfaceUp()) ;
		setStatus(INetAddr::NET_IP_ALLOCATED) ;
		return ;
	}

	// check to see if we've timed out yet
	if (timedOut())
		return ;

//	// If we previously had an ip address then ensure it's still set
//	if (mCurrentIp.empty())
//		return ;
//
//	logDebugVerbose("[DHCP:%s] Restore IP=%s", interface().c_str(), mCurrentIp.c_str()) ;
//	setInterfaceIp(mCurrentIp) ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetAddrDhcp::runDhcp()
{
	logDebugVerbose("[DHCP:%s] Run DHCP ... ", interface().c_str()) ;

	int rc(0) ;

	std::string dhcpCmd("udhcpc -n -i " + interface()) ;
	if (!mHostname.empty())
	{
		dhcpCmd += " -x hostname:" + mHostname ;
	}
	if (!mScript.empty())
	{
		dhcpCmd += " -s " + mScript ;
	}
	dhcpCmd += " >/dev/null 2>&1" ;

	logDebugVerbose("[DHCP:%s] CMD: ", dhcpCmd.c_str()) ;

#ifndef OFF_TARGET
	if (isTimed())
	{
		bool timedOut(false) ;
		unsigned timeout(timeoutTimeMs() / 1000) ;
		if (timeout == 0) ++timeout ;
		rc = mDhcp->runCmd(dhcpCmd, timeout, timedOut) ;
	}
	else
	{
		rc = mDhcp->runCmd(dhcpCmd) ;
	}
#endif

	// rc will be 0 if the address is allocated
	if (rc == 0)
	{
		logDebugVerbose("[DHCP:%s] ** ALLOCATED **", interface().c_str()) ;
		return true ;
	}

	// any other failure - treat as ip not allocated
	logDebugVerbose("[DHCP:%s] - Not ALLOCATED", interface().c_str()) ;
	return false ;

}
