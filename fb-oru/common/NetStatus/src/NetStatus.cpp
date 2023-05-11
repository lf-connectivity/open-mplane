/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetStatus.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <mutex>
#include <fstream>
#include <sstream>

#include "xstringfunc.hpp"

#include "NetStatus.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string IP_LOG_FILE{"/var/log/ip.log"} ;
const unsigned UPDATE_RATE_MS{1000} ;

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string NetStatus::mTestIpLogPath(IP_LOG_FILE) ;
unsigned NetStatus::mTestUpdateRateMs(UPDATE_RATE_MS) ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<INetStatus> NetStatus::getInstance()
{
	static std::shared_ptr<INetStatus> instance(std::make_shared<NetStatus>(mTestIpLogPath, mTestUpdateRateMs)) ;
	return instance ;
}


//=============================================================================================================
// INetChange
//=============================================================================================================
const std::map<INetChange::NetState, std::string> STATE_STRINGS{
	{ INetChange::NetState::NET_DISCONNECTED,	"DISCONNECTED" },
	{ INetChange::NetState::NET_STATIC,			"STATIC" },
	{ INetChange::NetState::NET_DHCP,			"DHCP" },
	{ INetChange::NetState::NET_LINK_LOCAL,		"LINK-LOCAL" },
} ;

//-------------------------------------------------------------------------------------------------------------
std::string INetChange::stateStr(NetState state)
{
	return STATE_STRINGS.at(state) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NetStatus::NetStatus() :
	TaskPeriodicEvent(UPDATE_RATE_MS, Task::PRIORITY_LOW, Task::SMALL_STACK, "NetStatus", "NET"),
	mIpLogFile(IP_LOG_FILE),
	mMutex(),
	mFileMutex(),
	mStates(),
	mLastChangedInterface()
{
}

//-------------------------------------------------------------------------------------------------------------
NetStatus::NetStatus(const std::string& ipLogPath, unsigned updateRateMs) :
	TaskPeriodicEvent(updateRateMs, Task::PRIORITY_LOW, Task::SMALL_STACK, "NetStatus", "NET"),
	mIpLogFile(ipLogPath),
	mMutex(),
	mFileMutex(),
	mStates(),
	mLastChangedInterface()
{
}

//-------------------------------------------------------------------------------------------------------------
NetStatus::~NetStatus()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string NetStatus::getInterface() const
{
	Mutex::Lock lock(mMutex) ;
	return mLastChangedInterface ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetStatus::getIp() const
{
	std::string interface(getInterface()) ;
	return getIp(interface) ;
}

//-------------------------------------------------------------------------------------------------------------
INetChange::NetState NetStatus::getState() const
{
	std::string interface(getInterface()) ;
	return getState(interface) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string NetStatus::getIp(const std::string& interface) const
{
	Mutex::Lock lock(mMutex) ;
	if (mStates.find(interface) == mStates.end())
		return "0.0.0.0" ;

	return mStates.at(interface).getIp() ;
}

//-------------------------------------------------------------------------------------------------------------
INetChange::NetState NetStatus::getState(const std::string& interface) const
{
	Mutex::Lock lock(mMutex) ;
	if (mStates.find(interface) == mStates.end())
		return INetChange::NetState::NET_DISCONNECTED ;

	return mStates.at(interface).getState() ;
}

//-------------------------------------------------------------------------------------------------------------
bool NetStatus::setState(const std::string& interface,
		INetChange::NetState state, const std::string& ipAddress)
{
//std::cerr << "NetStatus::setState(" << interface << " : " << STATE_STRINGS.at(state) << " : " << ipAddress << ")" << std::endl ;

	NetChange current(interface, ipAddress, state) ;

	// check existing
	{
		Mutex::Lock lock(mMutex) ;

		// see if this is actually a change
		bool change(false) ;
		if (mStates.find(interface) == mStates.end())
		{
			change = true ;
		}

		else if (mStates[interface] != current)
		{
			change = true ;
		}

		// no change so just stop
		if (!change)
			return true ;
	}

//std::cerr << "NetStatus::setState - CHANGE" << std::endl ;

	// notify observers
	notify(current) ;

//std::cerr << "NetStatus::setState - update" << std::endl ;
	// Update state
	{
		Mutex::Lock lock(mMutex) ;
		mLastChangedInterface = interface ;
		mStates[mLastChangedInterface] = current ;
	}

//std::cerr << "NetStatus::setState - write" << std::endl ;
	// write file
	{
		Mutex::Lock lock(mFileMutex) ;

		std::ofstream outfile;
		outfile.open(mIpLogFile, std::ios_base::app);

		if (!outfile.is_open())
			return false ;

		outfile << STATE_STRINGS.at(state) << ":" << interface << ":" << ipAddress << std::endl ;
		outfile.close() ;
	}

//std::cerr << "NetStatus::setState - >END<" << std::endl ;
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool NetStatus::runEvent()
{
//	std::cerr << "NetStatus::runEvent" << std::endl ;

	std::map<std::string, NetChange> newStates ;

	// file read
	{
		Mutex::Lock lock(mFileMutex) ;

		std::ifstream infile;
		infile.open(mIpLogFile);

		if (!infile.is_open())
			return true ;

		// Scan through file updating each interface so we end up with their latest state
		std::string linebuff ;
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);

			// Log line expected to be of the form:
			// <state>:<interface>:<ip>
			std::vector<std::string> fields(split(linebuff, ':')) ;
			if (fields.size() != 3)
				continue ;

			INetChange::NetState state(INetChange::NetState::NET_DISCONNECTED) ;
			for (auto entry : STATE_STRINGS)
			{
				if (fields[0] == entry.second)
				{
					state = entry.first ;
					break ;
				}
			}
			newStates[fields[1]] = NetChange(fields[1], fields[2], state) ;
		}
		infile.close() ;
	}

	// Now check for change
	std::vector<NetChange> changed ;
	for (auto entry : newStates)
	{
		// if no entry yet or entry changed, then notify
		bool change(false) ;
		if (mStates.find(entry.first) == mStates.end())
		{
			change = true ;
		}
		else if (mStates[entry.first] != entry.second)
		{
			change = true ;
		}

		if (change)
		{
//std::cerr << "NetStatus::runEvent - CHANGE " << entry.first << ":" <<
//		STATE_STRINGS.at(entry.second.getState()) << " : " << entry.second.getIp() << std::endl ;

			notify(entry.second) ;
			changed.push_back(entry.second) ;
		}
	}

	// Update state
	Mutex::Lock lock(mMutex) ;
	for (auto entry : changed)
	{
		mLastChangedInterface = entry.getInterface() ;
		mStates[mLastChangedInterface] = entry ;
	}


	return true ;
}
