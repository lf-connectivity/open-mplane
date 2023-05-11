/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrPolicy.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "NetAddrPolicyMock.h"

#include "INetStatus.h"

#include "Task.h"
#include "NetDevice.h"


using namespace Mplane;


//=============================================================================================================
// CONST
//=============================================================================================================

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetAddrPolicy> INetAddrPolicy::factory(const std::string& interface)
{
	return std::make_shared<NetAddrPolicyMock>(interface) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrPolicyMock::NetAddrPolicyMock(const std::string& interface) :
	Loggable("Policy", "NetAddr"),

	mInterfaceUp(false),
	mPrevInterfaceUp(false),
	mInterface(interface),
	mStatus(INetAddr::NET_INACTIVE),
	mDownFunc(),
	mUpFunc()
{
}

//-------------------------------------------------------------------------------------------------------------
NetAddrPolicyMock::~NetAddrPolicyMock()
{
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::addAllocator(std::shared_ptr<INetAddr> allocator)
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetAddr> NetAddrPolicyMock::getAllocator(const std::string &name)
{
	return std::shared_ptr<INetAddr>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicyMock::interface() const
{
	return mInterface ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicyMock::interfaceDescription()
{
	return "Baseband";
}

//-------------------------------------------------------------------------------------------------------------
int64_t NetAddrPolicyMock::interfaceSpeed()
{
	return 1000L;
}

//-------------------------------------------------------------------------------------------------------------
int8_t NetAddrPolicyMock::interfacePort()
{
	return 1;
}

//-------------------------------------------------------------------------------------------------------------
INetAddr::NetAddrStatus NetAddrPolicyMock::status() const
{
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicyMock::ipAddress() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicyMock::macAddress() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicyMock::error()
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::run()
{
	// initialise
	start() ;

	while (true)
	{
		// run an allocation
		runCycle() ;

		Task::msSleep(100) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::start()
{
	mStatus = INetAddr::NET_RUNNING ;

	eventInfo("Networking[%s]: waiting for connection...", mInterface.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::runCycle()
{
	// Call callback functions if interface state changes

	if (mInterfaceUp != mPrevInterfaceUp)
	{
		if (mInterfaceUp)
		{
			for (auto func : mUpFunc)
				func() ;
		}
		else
		{
			for (auto func : mDownFunc)
				func() ;
		}

		mPrevInterfaceUp = mInterfaceUp;
	}
}



//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::networkInUse()
{
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::registerDownFunc(INetAddrPolicy::InterfaceDownFunc func)
{
	mDownFunc.push_back(func) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::registerUpFunc(INetAddrPolicy::InterfaceUpFunc func)
{
	mUpFunc.push_back(func) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::registerAllocatedFunc(INetAddrPolicy::InterfaceAllocatedFunc func)
{
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicyMock::dump() const
{
}
