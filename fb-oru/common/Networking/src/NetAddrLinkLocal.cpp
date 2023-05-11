/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrLinkLocal.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SystemTask.h"
#include "NetDevice.h"
#include "NetAddrLinkLocal.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

const std::string LL_IP("169.254.") ;

//-------------------------------------------------------------------------------------------------------------
// The first and last 256 addresses of 169.254.0.0/16 are reserved
const unsigned SUBNET_START(1) ;
const unsigned SUBNET_END(254) ;

// reserve .0 and .255 as they tend to be special (not really necessary but I'm doing it anyway!)
const unsigned IP_START(1) ;
const unsigned IP_END(254) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrLinkLocal::NetAddrLinkLocal(const std::string& interface, unsigned timeoutMs) :
	NetAddr("Link-Local", INetChange::NET_LINK_LOCAL, interface, timeoutMs),
	mArping(std::make_shared<SystemTask>()),
	mRandGen( ::time(0) ),
	mRandIp(IP_START, IP_END),
	mHistory(),
	mSubnet(SUBNET_START),
	mFirst(true)
{
	mArping->start() ;
}

//-------------------------------------------------------------------------------------------------------------
NetAddrLinkLocal::~NetAddrLinkLocal()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrLinkLocal::doStart()
{
	// restart
	init() ;

	// Revert interface to 0.0.0.0 ip and UP
	setInterfaceIp("0.0.0.0") ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrLinkLocal::doAllocate()
{
	// get the next ip address
	unsigned ip ;
	if (!nextRandom(mSubnet, ip))
	{
		setStatus(INetAddr::NET_ERROR) ;
		return ;
	}

	// create ip address
	std::string ipAddr(LL_IP + std::to_string(mSubnet) + "." + std::to_string(ip)) ;
	if (!addressUsed(ipAddr))
	{
		// We've done
		setIpAddress(ipAddr) ;
		setInterfaceIp(ipAddr, "255.255.0.0") ;
		setStatus(INetAddr::NET_IP_ALLOCATED) ;
		return ;
	}

	// check to see if we've timed out yet
	if (timedOut())
		return ;
}


//-------------------------------------------------------------------------------------------------------------
bool NetAddrLinkLocal::stopOnAllocate() const
{
	// usually keep trying to get an ip address via other means
	return false ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrLinkLocal::init()
{
	mFirst = true ;
	mHistory.clear() ;
	mSubnet = SUBNET_START ;

	// reserve the first and last addresses
	for (unsigned subnet=0; subnet < SUBNET_START; ++subnet)
	{
		addHistory(subnet) ;
		for (unsigned ip=0; ip < 256; ++ip)
			mHistory[subnet].set(ip, true) ;
	}
	for (unsigned subnet=SUBNET_END; subnet < 256; ++subnet)
	{
		addHistory(subnet) ;
		for (unsigned ip=0; ip < 256; ++ip)
			mHistory[subnet].set(ip, true) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrLinkLocal::isTried(unsigned subnet, unsigned ip)
{
	logDebugVerbose("[Link Local:%s] Is Tried? %u.%u", interface().c_str(), subnet, ip) ;

	if (mHistory.find(subnet) == mHistory.end())
		addHistory(subnet) ;

	if (mHistory[subnet].test(ip))
		return true ;

	// not used so save
	mHistory[subnet].set(ip, true) ;

	logDebugVerbose("[Link Local:%s] Is Tried? %u.%u - UNTRIED", interface().c_str(), subnet, ip) ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrLinkLocal::nextRandom(unsigned &subnet, unsigned &ip)
{
	logDebugVerbose("[Link Local:%s] nextRandom", interface().c_str()) ;

	// first allocation uses the MAC to determine the subnet/ip
	if (mFirst)
	{
		mFirst = false ;

		std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>()) ;
		nd->open(interface()) ;
		std::string mac(nd->getMac()) ;
		logDebugVerbose("[Link Local:%s] MAC %s", interface().c_str(), nd->getMac().c_str()) ;

		// check we've got a valid MAC, otherwise revert to "random" walk
		if (!mac.empty() && (mac.size() == 12) )
		{
			std::string subnetOctet(mac.substr(8, 2)) ;
			std::string ipOctet(mac.substr(10, 2)) ;

			subnet = (unsigned)std::stoi(subnetOctet, 0, 16) ;
			ip = (unsigned)std::stoi(ipOctet, 0, 16) ;

			return true ;
		}
	}


	// random walk through the ip's unused in this subnet - move to next subnet until find an unused ip
	// Only exit when we find an unused ip
    while (mSubnet < 255)
    {
    	// see if we've used up all the ip addresses in this subnet
    	if (mHistory.find(subnet) != mHistory.end())
			if (mHistory[subnet].all())
				++mSubnet ;

        // get the subnet number
        subnet = mSubnet ;

        // get ip
    	ip = mRandIp(mRandGen) ;

    	logDebugVerbose("[Link Local:%s] nextRandom %u.%u", interface().c_str(), subnet, ip) ;

    	// stop when we find an untried ip
    	if (!isTried(subnet, ip))
    		return true ;

    	logDebugVerbose("[Link Local:%s] nextRandom %u.%u ** TRIED **", interface().c_str(), subnet, ip) ;
    }

    // run out
    return false ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrLinkLocal::addHistory(unsigned subnet)
{
	mHistory[subnet] = std::bitset<256>() ;
	for (unsigned ip=0; ip < IP_START; ++ip)
		mHistory[subnet].set(ip, true) ;
	for (unsigned ip=IP_END; ip < 256; ++ip)
		mHistory[subnet].set(ip, true) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrLinkLocal::addressUsed(const std::string& ipAddr)
{
	const unsigned TIMEOUT_SECS(3) ;
	bool timedOut(false) ;

	logDebugVerbose("[Link Local:%s] Is Allocated? %s", interface().c_str(), ipAddr.c_str()) ;

	int rc = mArping->runCmd("arping -I " + interface() + " -w 1 -D " + ipAddr, TIMEOUT_SECS, timedOut) ;

	// rc will be 256 is arping gets a response so that the address is allocated
	if (rc > 0)
	{
		logDebugVerbose("[Link Local:%s] Is Allocated? %s ** ALLOCATED **", interface().c_str(), ipAddr.c_str()) ;
		return true ;
	}

	// any other failure - treat as ip not allocated
	logDebugVerbose("[Link Local:%s] Is Allocated? %s - Not ALLOCATED", interface().c_str(), ipAddr.c_str()) ;
	return false ;
}
