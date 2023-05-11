/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetworkingServiceMock.cpp
 * \brief
 *
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"
#include "NetworkingService.h"

using namespace Mplane;


std::shared_ptr<INetworkingService> INetworkingService::singleton(const std::string& interface)
{
	static std::shared_ptr<INetworkingService> instance(std::make_shared<NetworkingService>(interface)) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetworkingService::NetworkingService(const std::string& interface) :
	TaskPeriodicEvent(SERVICE_PERIOD,
			Task::PRIORITY_DEFAULT, Task::SMALL_STACK,
            "NetworkService",
            "NetAddr"),
	mNetInterface(interface),
	mNetPolicy(INetAddrPolicy::factory(mNetInterface)),
	mPaused(false)
{
	mNetPolicy->start() ;
}

//-------------------------------------------------------------------------------------------------------------
NetworkingService::~NetworkingService()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetAddrPolicy> NetworkingService::getNetAddrPolicy()
{
	return mNetPolicy ;
}

//-------------------------------------------------------------------------------------------------------------
void NetworkingService::restart()
{
	mNetPolicy->start() ;
	mPaused = false ;
}

//-------------------------------------------------------------------------------------------------------------
void NetworkingService::pause()
{
	mPaused = true ;
}

//-------------------------------------------------------------------------------------------------------------
void NetworkingService::startEnable(const std::string& name, bool enable)
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetworkingService::addAllocator(std::shared_ptr<INetAddr> addrAllocator)
{
	mNetPolicy->addAllocator(addrAllocator) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetworkingService::netInterface() const
{
	return mNetInterface ;
}

//-------------------------------------------------------------------------------------------------------------
void NetworkingService::checkMac(const std::string &macEnvVarName)
{
}


//=============================================================================================================
// PROTECTED HOOK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetworkingService::runEvent()
{
	if (mPaused)
		return true ;

	mNetPolicy->runCycle() ;

	if (mNetPolicy->status() == INetAddr::NET_ERROR)
	{
		eventError("NetWorkService: ERROR %s", mNetPolicy->error().c_str()) ;
		return false ;
	}
	return true ;
}
