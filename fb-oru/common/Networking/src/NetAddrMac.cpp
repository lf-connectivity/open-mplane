/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrMac.cpp
 * \brief     Just checks the MAC id and moves on
 *
 *
 * \details   Will set the MAC if it doesn't match the expected value. Useful for automatically setting the MAC
 * 				from a UBOOT env variable before networking starts
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NetDevice.h"
#include "NetAddrMac.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrMac::NetAddrMac(const std::string& interface, const std::string &mac) :
	NetAddr("MAC", INetChange::NET_DISCONNECTED, interface),
	mMac(mac)
{
}

//-------------------------------------------------------------------------------------------------------------
NetAddrMac::~NetAddrMac()
{
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrMac::doStart()
{
	logDebugVerbose("[MAC:%s] Start expected MAC=%s", interface().c_str(), mMac.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrMac::doAllocate()
{
	if (mMac.empty())
	{
		setStatus(INetAddr::NET_TIMED_OUT) ;
		return ;
	}

	// Check the current mac and set it if not already set
	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>(interface())) ;
	std::string ndMac(nd->getMac()) ;

	logDebugVerbose("[MAC:%s] Checking expected MAC=%s against actual=%s", interface().c_str(), mMac.c_str(), ndMac.c_str()) ;

	if (mMac != ndMac)
		nd->setMac(mMac) ;

	// can stop now
	setStatus(INetAddr::NET_TIMED_OUT) ;
}
