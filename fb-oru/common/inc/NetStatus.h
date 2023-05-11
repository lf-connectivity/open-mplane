/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetStatus.h
 * \brief     Monitor network status
 *
 *
 */


#ifndef NETSTATUS_H_
#define NETSTATUS_H_

#include <map>

#include "INetStatus.h"

#include "TaskPeriodicEvent.h"

namespace Mplane {

/**
 * \class  NetChange
 * \brief  Network status change event
 * \details   Encapsulates the state of a network interface on a change event
 *
 */
class NetChange : public virtual INetChange {
public:
	NetChange(const std::string& interface, const std::string& ip, INetChange::NetState state) :
		mInterface(interface),
		mIp(ip),
		mState(state)
	{}

	NetChange() :
		mInterface(),
		mIp(),
		mState(INetChange::NetState::NET_DISCONNECTED)
	{}

	~NetChange() {}

	bool operator==(const NetChange& rhs)
	{
		if (mIp != rhs.mIp)
			return false ;
		if (mState != rhs.mState)
			return false ;

		return true ;
	}

	bool operator!=(const NetChange& rhs)
	{
		return ! operator==(rhs) ;
	}



	const std::string& getInterface() const override
	{
		return mInterface;
	}

	const std::string& getIp() const override
	{
		return mIp;
	}

	NetState getState() const override
	{
		return mState;
	}

private:
	std::string mInterface ;
	std::string mIp ;
	NetState mState ;
};

/*!
 * \class  NetStatus
 * \brief  Monitor network status
 * \details   Reads the networking status log file (/var/log/ip.log) and generates events based on the ip address changes
 * for an interface
 *
 */
class NetStatus : public INetStatus, public TaskPeriodicEvent {
public:
	NetStatus() ;

	/**
	 * For testing purposes - specify a test log file to use
	 */
	NetStatus(const std::string& ipLogPath, unsigned updateRateMs = 1000) ;

	virtual ~NetStatus() ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<INetStatus> getInstance() ;

	/**
	 * Get latest changed interface
	 */
	virtual std::string getInterface() const override ;

	/**
	 * Get ip address for latest changed interface
	 */
	virtual std::string getIp() const override ;

	/**
	 * Get state for latest changed interface
	 */
	virtual INetChange::NetState getState() const override ;

	/**
	 * Get ip address for specified interface
	 */
	virtual std::string getIp(const std::string& interface) const override ;

	/**
	 * Get state for specified interface
	 */
	virtual INetChange::NetState getState(const std::string& interface) const override ;

	/**
	 * Set the current state of an interface
	 */
	virtual bool setState(const std::string& interface, INetChange::NetState state, const std::string& ipAddress = "") override ;


public:
	// For testing purposes - used with singleton
	static std::string mTestIpLogPath ;
	static unsigned mTestUpdateRateMs ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;


private:
	std::string mIpLogFile ;
	mutable Mutex mMutex ;
	mutable Mutex mFileMutex ;
	std::map<std::string, NetChange> mStates ;
	std::string mLastChangedInterface ;
} ;

}

#endif /* NETSTATUS_H_ */
