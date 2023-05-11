/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetworkingService.cpp
 * \brief
 *
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"
#include "NetDevice.h"
#include "NetworkingService.h"

using namespace Mplane;


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
	mPaused(false),
    mEnable(true),
    mStartEnables()
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
void NetworkingService::startEnable(const std::string &name, bool enable)
{
	if (mStartEnables.find(name) == mStartEnables.end())
		mStartEnables[name] = true ;

	mStartEnables[name] = enable ;
	if (!enable)
	{
		logDebugVerbose("NetworkingService[%s] DISABLE", mNetInterface.c_str()) ;

		mEnable = false ;
		return ;
	}

	// see if we are now all TRUE
	for (auto entry : mStartEnables)
	{
		if (!entry.second)
			return ;
	}

	logDebugVerbose("NetworkingService[%s] ENABLING", mNetInterface.c_str()) ;

	// if we're going from disabled to enabled then restart the policy
	if (!mEnable)
		mNetPolicy->start() ;

	mEnable = true ;
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
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	if (!bootEnv->isVar(macEnvVarName))
		return ;

    std::string envMac(bootEnv->getVar(macEnvVarName)) ;

	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>(mNetInterface)) ;
	std::string ndMac(nd->getMac()) ;

	if (envMac == ndMac)
		return ;

	// need to set the interface MAC to match the environment variable
	nd->setMac(envMac) ;
}


//=============================================================================================================
// PROTECTED HOOK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetworkingService::runEvent()
{
	if (mPaused)
		return true ;

	if (!mEnable)
		return true ;

	mNetPolicy->runCycle() ;

	if (mNetPolicy->status() == INetAddr::NET_ERROR)
	{
		eventError("NetWorkService: ERROR %s", mNetPolicy->error().c_str()) ;
		return false ;
	}
	return true ;
}
