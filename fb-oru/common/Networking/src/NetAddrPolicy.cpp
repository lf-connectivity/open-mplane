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
#include "INetStatus.h"
//#include "IHighSpeedEthernet.h"
#include "IAppOptions.h"
#include "IBootEnv.h"

#include "Task.h"
#include "stringfunc.hpp"
#include "NetDevice.h"

#include "NetAddrPolicy.h"

using namespace Mplane;


//=============================================================================================================
// CONST
//=============================================================================================================
//#define DEBUG_POLICY
const std::string ENV_ETH0MAC{"ethaddr"} ;
const std::string ENV_ETH1MAC{"ethaddr1"} ;

//-------------------------------------------------------------------------------------------------------------
std::map<NetAddrPolicy::PolicyState, std::string> NetAddrPolicy::mPolicyStateStrings{
	{ NetAddrPolicy::POLICY_WAIT_CONNECT, "POLICY_WAIT_CONNECT" },
	{ NetAddrPolicy::POLICY_WAIT_CONNECT_TIMER, "POLICY_WAIT_CONNECT_TIMER" },
	{ NetAddrPolicy::POLICY_START_ALLOCATE, "POLICY_START_ALLOCATE" },
	{ NetAddrPolicy::POLICY_ALLOCATE, "POLICY_ALLOCATE" },
	{ NetAddrPolicy::POLICY_ALLOCATED, "POLICY_ALLOCATED" },
	{ NetAddrPolicy::POLICY_ALLOCATED_TIMER, "POLICY_ALLOCATED_TIMER" },
	{ NetAddrPolicy::POLICY_CONNECTED, "POLICY_CONNECTED" },
	{ NetAddrPolicy::POLICY_CONNECTED_TIMER, "POLICY_CONNECTED_TIMER" },

} ;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetAddrPolicy> INetAddrPolicy::factory(const std::string& interface)
{
	return std::make_shared<NetAddrPolicy>(interface) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetAddrPolicy::NetAddrPolicy(const std::string& interface) :
	Loggable("Policy", "NetAddr"),

	mState(POLICY_WAIT_CONNECT),
	mConnected(false),
	mAllocatorIndex(0),
	mNetworkInUse(false),
	mAllocators(),
	mError(),
	mInterface(interface),
	mIfDesc(),
	mIfSpeed(NET_SPEED_NULL),
	mIfPort(0),
	mStatus(INetAddr::NET_INACTIVE),
	mIpAddress(),
	mMacAddress(),
	mTimer(),
	mDownFunc(),
	mUpFunc(),
	mAllocatedFunc()
{
	std::shared_ptr<IAppOptions> appOptions(IAppOptions::getInstance()) ;

	// Determine description, port number, speed and MAC
	int64_t speed = NET_SPEED_NULL;
	uint8_t portNumber = 0;
	bool validPortNum = false;
	std::string descName;
	std::string ethMac;
	if(mInterface == appOptions->getOption("ethcdi").toString())
	{
		// CDI interface
		speed = (int64_t)NetSpeed::SPEED_1G;
		descName = "CDI";
		portNumber = extractInt(mInterface, validPortNum);
#ifdef OFF_TARGET
		ethMac = "00:11:22:33:44:55" ;
#endif
	}
	else if(mInterface == appOptions->getOption("ethbb").toString())
	{
#if 0
		// Is highspeed 25G ethernet available?
		std::shared_ptr<IHighSpeedEthernet> highSpeedEth(IHighSpeedEthernet::singleton());
		if (highSpeedEth->is25G())
			speed = (int64_t)NetSpeed::SPEED_25G;
		else
#endif
			speed = (int64_t)NetSpeed::SPEED_10G;
		descName = "Baseband";
		portNumber = extractInt(mInterface, validPortNum);
#ifdef OFF_TARGET
		ethMac = "00:22:33:44:55:66" ;
#endif
	}

	if (ethMac.empty())
	{
		std::string ethMacKey;
		if(portNumber == 0)
			ethMacKey = ENV_ETH0MAC;
		else if(portNumber == 1)
			ethMacKey = ENV_ETH1MAC;
		if (!ethMacKey.empty())
		{
			std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance());
			ethMac = bootEnv->getVar(ethMacKey);
		}
	}
	setMacAddress(ethMac);
	setInterfaceSpeed(speed);
	setInterfaceDescription(descName);
	setInterfacePort(portNumber);
}

//-------------------------------------------------------------------------------------------------------------
NetAddrPolicy::~NetAddrPolicy()
{
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::addAllocator(std::shared_ptr<INetAddr> allocator)
{
#ifdef DEBUG_POLICY
	logDebugVerbose("NetAddrPolicy[%s:%s] addAllocator %s", mInterface.c_str(), mPolicyStateStrings.at(mState).c_str(), allocator->name().c_str()) ;
#endif

	mAllocators.push_back(allocator) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetAddr> NetAddrPolicy::getAllocator(const std::string &name)
{
	for (auto alloc : mAllocators)
	{
		if (alloc->name() == name)
			return alloc ;
	}

	return std::shared_ptr<INetAddr>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicy::interface() const
{
	return mInterface ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicy::interfaceDescription()
{
	return mIfDesc;
}

//-------------------------------------------------------------------------------------------------------------
int64_t NetAddrPolicy::interfaceSpeed()
{
	return mIfSpeed;
}

//-------------------------------------------------------------------------------------------------------------
int8_t NetAddrPolicy::interfacePort()
{
	return mIfPort;
}

//-------------------------------------------------------------------------------------------------------------
INetAddr::NetAddrStatus NetAddrPolicy::status() const
{
	return mStatus ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicy::ipAddress() const
{
	return mIpAddress ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicy::macAddress() const
{
	return mMacAddress;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetAddrPolicy::error()
{
	std::string error ;
	std::swap(error, mError) ;
	return mError ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::run()
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
void NetAddrPolicy::start()
{
	mState = POLICY_WAIT_CONNECT ;
	mConnected = false ;
	mAllocatorIndex = 0 ;
//	mNetworkInUse(false),
	mError.clear() ;
	mStatus = INetAddr::NET_RUNNING ;
	mIpAddress.clear() ;

	// ensure interface is up first - otherwise you don't get valid readings from the carrier or address etc
	{
		std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>(mInterface)) ;
		nd->setUp(true) ;
	}

	eventInfo("Networking[%s]: waiting for connection...", mInterface.c_str()) ;

	logDebugVerbose("NetAddrPolicy[%s:%s] START", mInterface.c_str(), mPolicyStateStrings.at(mState).c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::runCycle()
{
#ifdef DEBUG_POLICY
	logDebugVerbose("NetAddrPolicy[%s:%s] RUN allocator %u", mInterface.c_str(), mPolicyStateStrings.at(mState).c_str(), mAllocatorIndex) ;
#endif

	if (mAllocators.empty())
		return ;

	std::shared_ptr<INetStatus> netStatus(INetStatus::getInstance()) ;

	INetAddr::NetAddrStatus status ;

	switch (mState)
	{
	case POLICY_WAIT_CONNECT:

		mError.clear() ;
		mStatus = INetAddr::NET_RUNNING ;
		mIpAddress.clear() ;
		mAllocatorIndex = 0 ;

		if (!isConnected())
		{
			// sleep 1 sec then try again
			startTimer(1000) ;
			mState = POLICY_WAIT_CONNECT_TIMER ;
			return ;
		}

		// start allocating
		mState = POLICY_START_ALLOCATE ;

		break ;

	case POLICY_WAIT_CONNECT_TIMER:
		if (timerExpired())
		{
			mState = POLICY_WAIT_CONNECT ;
			return ;
		}

		break ;

	case POLICY_START_ALLOCATE:
		// check for disconnect - resets to waiting for connection
		if (!isConnected())
			return ;

		mAllocators[mAllocatorIndex]->start() ;
		eventInfo("Networking[%s]: running %s ip allocator...", mInterface.c_str(), mAllocators[mAllocatorIndex]->name().c_str()) ;
		mState = POLICY_ALLOCATE ;

		break ;

	case POLICY_ALLOCATE:
		// check for disconnect - resets to waiting for connection
		if (!isConnected())
			return ;

		// check for networking activity (assume this will only be the case after allocating an ip address!)
		// if there's a valid connection on the current ip address then we need to stop allocating
		if (isStopAllocating())
			return ;

		// run next allocation
		status = mAllocators[mAllocatorIndex]->allocate() ;

		// handle error
		if (status == INetAddr::NET_ERROR)
		{
			setError(mAllocators[mAllocatorIndex]->error()) ;
			return ;
		}

		// If allocator still running then run again
		if (status == INetAddr::NET_RUNNING)
		{
			return ;
		}

		// check allocated
		if (status == INetAddr::NET_IP_ALLOCATED)
		{
			// Allocated
			auto netAddr(mAllocators[mAllocatorIndex]) ;
			mIpAddress = netAddr->ipAddress() ;
			eventInfo("Networking[%s]: ip address '%s' allocated (by %s) [MAC: %s]",
					mInterface.c_str(), mIpAddress.c_str(), netAddr->name().c_str(),
					mMacAddress.c_str()) ;

			// notify the NetStatus monitor
			netStatus->setState(mInterface, netAddr->netStateType(), mIpAddress) ;

			// notify any callbacks
			for (auto func : mAllocatedFunc)
			{
				if (!func)
					continue ;

				func(netAddr->interface(), netAddr->ipAddress(), macAddress(), netAddr->name(), netAddr->netStateType()) ;
			}

			// does the allocator want us to stop now or carry on with the list?
			if (netAddr->stopOnAllocate())
			{
				mState = POLICY_ALLOCATED ;
				return ;
			}

			// need to carry on with the next allocator...
		}

		// Any other reason, move to next allocator
		if (++mAllocatorIndex >= mAllocators.size())
		{
			// run out of allocators - start again
			mAllocatorIndex = 0 ;
			mState = POLICY_WAIT_CONNECT ;
			return ;
		}

		// next allocator
		mState = POLICY_START_ALLOCATE ;

		break ;

	case POLICY_ALLOCATED:
		mStatus = INetAddr::NET_IP_ALLOCATED ;

		// check for disconnect - resets to waiting for connection
		if (!isConnected())
			return ;

		// check for networking activity (assume this will only be the case after allocating an ip address!)
		// if there's a valid connection on the current ip address then we need to stop allocating
		if (isStopAllocating())
			return ;

		// sleep 1 sec then check again
		startTimer(1000) ;
		mState = POLICY_ALLOCATED_TIMER ;

		break ;

	case POLICY_ALLOCATED_TIMER:
		if (timerExpired())
		{
			mState = POLICY_ALLOCATED ;
			return ;
		}
		break ;

	case POLICY_CONNECTED:
		// check for disconnect - resets to waiting for connection
		if (!isConnected())
			return ;

		// sleep 10 sec then check again
		startTimer(10000) ;
		mState = POLICY_CONNECTED_TIMER ;

		break ;

	case POLICY_CONNECTED_TIMER:
		if (timerExpired())
		{
			mState = POLICY_CONNECTED ;
			return ;
		}
		break ;

	default:
		setError("Internal error") ;
		break ;
	}

}



//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::networkInUse()
{
	mNetworkInUse = true ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::registerDownFunc(INetAddrPolicy::InterfaceDownFunc func)
{
	mDownFunc.push_back(func) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::registerUpFunc(INetAddrPolicy::InterfaceUpFunc func)
{
	mUpFunc.push_back(func) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::registerAllocatedFunc(INetAddrPolicy::InterfaceAllocatedFunc func)
{
	mAllocatedFunc.push_back(func) ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::dump() const
{
	std::cerr << "NetAddrPolicy::dump()" << mState << std::endl;
#ifdef DEBUG_POLICY
	std::cerr << "\tState: " << mPolicyStateStrings.at(mState) << std::endl;
#else
	std::cerr << "\tState: " << mState << std::endl;
#endif
	if (!mError.empty())
		std::cerr << "\tError: " << mError << std::endl;
	std::cerr << "\tConnected: " << mConnected << std::endl;
	std::cerr << "\tAllocatorIndex: " << mAllocatorIndex << std::endl;
	std::cerr << "\tNetworkInUse: " << mNetworkInUse << std::endl;
	//std::vector<std::shared_ptr<INetAddr>> mAllocators ;
	std::cerr << "\tNetStatus: " << mStatus << std::endl;
	std::cerr << "\tInterface: " << mInterface << std::endl;
	std::cerr << "\t\tDescription: " << mIfDesc << std::endl;
	std::cerr << "\t\tSpeed: " << mIfSpeed << std::endl;
	std::cerr << "\t\tPort: " << std::to_string(mIfPort) << std::endl;
	std::cerr << "\t\tIP Address: " << mIpAddress << std::endl;
	std::cerr << "\t\tMAC: " << mMacAddress << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::setMacAddress(const std::string & macAddress)
{
	bool validAddress = !macAddress.empty();

	if (validAddress)
	{
		std::cerr << "NetAddrPolicy::setMacAddress() [" << macAddress << "]" << std::endl ;
		mMacAddress = macAddress;
	}
	else
	{
		std::cerr << "NetAddrPolicy::setMacAddress() - invalid MAC address [" << macAddress << "]" << std::endl ;
	}

	return validAddress;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::setInterfaceSpeed(int64_t speed)
{
	if (speed < 0)
	{
		mIfSpeed = NET_SPEED_NULL;
	}
	else
	{
		mIfSpeed = speed;
	}

	std::cerr << "NetAddrPolicy::setInterfaceSpeed() - " << mIfSpeed << "bps" << std::endl ;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::setInterfaceDescription(const std::string & descName)
{
	std::string desc;

	if (descName.empty())
	{
		desc = mInterface;
	}
	else
	{
		desc = descName;
	}

	/* Set interface description */
	if (mIfSpeed > 0)
	{
		int64_t speed = mIfSpeed;
		std::vector<std::string> ethSuffixes { "bps", "Kbps", "Mbps", "Gbps", "Tbps" };
		int64_t mult = NET_SPEED_1K;
		uint32_t idx = 0;

		for (auto suffix : ethSuffixes)
		{
			if (speed < mult)
			{
				break;
			}
			speed /= mult;
			idx++;
		}
		desc += " " + std::to_string(speed) + ethSuffixes[idx];
	}
	mIfDesc = desc + " ethernet port";

	//std::cerr << "NetAddrPolicy::setInterfaceDescription - " << mIfDesc << std::endl ;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::setInterfacePort(uint8_t portNumber)
{
	/* Set interface port number */
	mIfPort = portNumber;

	//std::cerr << "NetAddrPolicy::setInterfacePort - " << mIfPort << std::endl ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::setError(const std::string& error)
{
	if (!mError.empty())
		mError += "\r" ;
	mError += error ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::isConnected()
{
	std::shared_ptr<NetDevice> ethDevice(std::make_shared<NetDevice>()) ;
	ethDevice->open(mInterface) ;

	// check for currently connected
	if (ethDevice->isConnected())
	{
		if (!mConnected)
		{
			eventInfo("Networking[%s]: plug in detected", mInterface.c_str()) ;
			for (auto func : mUpFunc)
				func() ;
		}
		mConnected = true ;
		return true ;
	}

	// currently not connected

	// check to see if we were connected and this is a state change
	if (mConnected)
	{
		eventInfo("Networking[%s]: unplug detected", mInterface.c_str()) ;
		for (auto func : mDownFunc)
			func() ;

		mConnected = false ;
		mState = POLICY_WAIT_CONNECT ;
		eventInfo("Networking[%s]: waiting for connection...", mInterface.c_str()) ;

		// notify the NetStatus monitor
		std::shared_ptr<INetStatus> netStatus(INetStatus::getInstance()) ;
		netStatus->setState(mInterface, INetChange::NET_DISCONNECTED, "0.0.0.0") ;
	}
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::isStopAllocating()
{
	if (!mNetworkInUse)
		return false ;

	mState = POLICY_CONNECTED ;
	eventInfo("Networking[%s]: ip address %s now in use, allocation stopped", mInterface.c_str(), mIpAddress.c_str()) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void NetAddrPolicy::startTimer(unsigned timeoutMs)
{
	mTimer = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeoutMs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetAddrPolicy::timerExpired() const
{
	if (std::chrono::steady_clock::now() >= mTimer)
		return true ;

	return false ;
}
