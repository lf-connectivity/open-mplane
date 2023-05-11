/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddr.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "SystemTask.h"
#include "NetDevice.h"

#include "NetAddr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddr::NetAddr(const std::string& name, INetChange::NetState netState, const std::string& interface, unsigned timeoutMs) :
	Loggable(name, "NetAddr"),
	mName(name),
	mNetStateType(netState),
	mInterface(interface),
	mMutex(),
	mIsTimed(timeoutMs > 0),
	mTimeoutMs(timeoutMs),
	mStatus(INetAddr::NET_INACTIVE),
	mIpAddress(),
	mError(),
	mTimeoutTime()
{
}

//-------------------------------------------------------------------------------------------------------------
NetAddr::~NetAddr()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddr::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
INetChange::NetState NetAddr::netStateType() const
{
	return mNetStateType ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddr::interface() const
{
	return mInterface ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddr::isTimed() const
{
	return mIsTimed ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned NetAddr::timeoutTimeMs() const
{
	return mTimeoutMs ;
}

//-------------------------------------------------------------------------------------------------------------
INetAddr::NetAddrStatus NetAddr::status() const
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddr::ipAddress() const
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	return mIpAddress ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddr::error()
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	std::string error ;
	std::swap(error, mError) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
INetAddr::NetAddrStatus NetAddr::start()
{
	setStatus(INetAddr::NET_RUNNING) ;
	if (isTimed())
	{
		mTimeoutTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(mTimeoutMs) ;
	}

	// run the derived class
	doStart() ;

	// return status
	return status() ;
}

//-------------------------------------------------------------------------------------------------------------
INetAddr::NetAddrStatus NetAddr::allocate()
{
	// run the derived class
	doAllocate() ;

	// return status
	return status() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddr::stopOnAllocate() const
{
	// default is always stop
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddr::setError(const std::string& error)
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	if (!mError.empty())
		mError += "\r" ;
	mError += error ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddr::setStatus(INetAddr::NetAddrStatus status)
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mStatus = status ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddr::setIpAddress(const std::string& ipAddress)
{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mIpAddress = ipAddress ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddr::timedOut()
{
	if (!isTimed())
		return false ;

	if (std::chrono::steady_clock::now() >= mTimeoutTime)
	{
		setStatus(INetAddr::NET_TIMED_OUT) ;
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddr::setInterfaceIp(const std::string& ipAddr, const std::string& netmask)
{
#ifndef OFF_TARGET

	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>(interface())) ;
	nd->setAddr("0.0.0.0") ;
	nd->setUp(true) ;
	nd->setAddr(ipAddr, netmask) ;

#endif

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::NetAddr::setInterfaceIp(const std::string& ipAddr, const std::string& netmask, const std::string& gateway)
{
#ifndef OFF_TARGET

	if (!setInterfaceIp(ipAddr, netmask))
		return false ;

	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>(interface())) ;
	nd->addDefaultGateway(gateway) ;

#endif

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddr::interfaceUp() const
{
	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>()) ;
	nd->open(interface()) ;

	// If interface isn't up with a valid IP address at this stage then there's been an error so stop
	if (!nd->isUp())
		return "" ;

	if (nd->getAddr() == "0.0.0.0")
		return "" ;

	if (nd->getAddr().empty())
		return "" ;

	return nd->getAddr() ;
}
