/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrPolicy.h
 * \brief     Base class implementing INetAddrPolicy
 *
 *
 */


#ifndef NETWORKING_INC_NETADDRPOLICY_H_
#define NETWORKING_INC_NETADDRPOLICY_H_

#include <map>
#include <memory>
#include <vector>
#include <atomic>
#include <chrono>

#include "Loggable.h"
#include "NetDevice.h"

#include "INetAddr.h"
#include "INetAddrPolicy.h"

namespace Mplane {

#define NET_SPEED_1K   (1000L)
#define NET_SPEED_NULL (-1)

/*!
 * \class  NetAddrPolicy
 * \brief  Base class implementing INetAddrPolicy
 * \details
 *
 */
class NetAddrPolicy : public virtual INetAddrPolicy, public Loggable {
public:
	enum class NetSpeed : int64_t
	{
		SPEED_1K   = NET_SPEED_1K,
		SPEED_1M   = (SPEED_1K * SPEED_1K),
		SPEED_1G   = (SPEED_1M * SPEED_1K),
		SPEED_1T   = (SPEED_1G * SPEED_1K),

		SPEED_10G  = (SPEED_1G * 10L),
		SPEED_25G  = (SPEED_1G * 25L),
	};

	NetAddrPolicy(const std::string& interface) ;
	virtual ~NetAddrPolicy() ;

	/**
	 * add an allocator to the list
	 */
	virtual void addAllocator(std::shared_ptr<INetAddr> allocator) override ;

	/**
	 * Get the named allocator or null pointer if unable to find
	 */
	virtual std::shared_ptr<INetAddr> getAllocator(const std::string& name) override ;

	/**
	 * Readback the interface
	 */
	virtual std::string interface() const override ;

	/**
	 * Readback the interface description
	 */
	virtual std::string interfaceDescription() override;

	/**
	 * Readback the interface speed
	 */
	virtual int64_t interfaceSpeed() override;

	/**
	 * Readback the interface port
	 */
	virtual int8_t interfacePort() override;

	/**
	 * Get current status
	 */
	virtual INetAddr::NetAddrStatus status() const override ;

	/**
	 * Get the allocated ip address (or empty string if not allocated)
	 */
	virtual std::string ipAddress() const override ;

	/**
	 * Get the allocated MAC address (or empty string if not allocated)
	 */
	virtual std::string macAddress() const override;

	/**
	 * Get the error string (clears stored error)
	 */
	virtual std::string error() override ;

	/**
	 * Run the allocators until an ip has been assigned
	 */
	virtual void run() override ;

	/**
	 * Start up with initial state (used when running as a service)
	 */
	virtual void start() override ;

	/**
	 * Perform a single cycle of address allocation (used when running as a service)
	 */
	virtual void runCycle() override ;

	/**
	 * Called when activity is detected on the newly connected network (e.g. a TIF connection has been made)
	 * This will then stop the policy from trying to allocate any other ip address
	 */
	virtual void networkInUse() override ;

	/**
	 * Register a callback that is called when interface goes down
	 */
	virtual void registerDownFunc(INetAddrPolicy::InterfaceDownFunc func) override ;

	/**
	 * Register a callback that is called when interface goes up
	 */
	virtual void registerUpFunc(INetAddrPolicy::InterfaceUpFunc func) override ;

	/**
	 * Register a callback for when the interface is allocated an IP address
	 */
	virtual void registerAllocatedFunc(INetAddrPolicy::InterfaceAllocatedFunc func) override ;

	/*
	 * Debug
	 */
	virtual void dump() const override;

protected:
	// add to error string
	void setError(const std::string& error) ;

private:
	bool setMacAddress(const std::string & macAddress);
	bool setInterfaceSpeed(int64_t speed);
	bool setInterfaceDescription(const std::string & descName);
	bool setInterfacePort(uint8_t portNumber);

	// is interface connected (i.e. wire plugged in)
	// If not, side effect is that the state is reset to WAIT_CONNECT
	bool isConnected() ;

	// checks the "network in use" flag to see if we need to stop allocating addresses
	// will set the state to CONNECTED
	bool isStopAllocating() ;

	// start a timer to timeout after specified MS
	void startTimer(unsigned timeoutMs) ;

	// has timer expired
	bool timerExpired() const ;

private:
	/**
	 * State machine
	 */
	enum PolicyState {
		POLICY_WAIT_CONNECT,
		POLICY_WAIT_CONNECT_TIMER,
		POLICY_START_ALLOCATE,
		POLICY_ALLOCATE,
		POLICY_ALLOCATED,
		POLICY_ALLOCATED_TIMER,
		POLICY_CONNECTED,
		POLICY_CONNECTED_TIMER,
	};
	static std::map<PolicyState, std::string> mPolicyStateStrings ;

private:
	PolicyState mState ;
	bool mConnected ;
	unsigned mAllocatorIndex ;
	std::atomic<bool> mNetworkInUse ;
	std::vector<std::shared_ptr<INetAddr>> mAllocators ;
	std::string mError ;
	std::string mInterface ;
	std::string mIfDesc ;
	int64_t mIfSpeed ;
	uint8_t mIfPort;
	std::atomic<INetAddr::NetAddrStatus> mStatus ;
	std::string mIpAddress ;
	std::string mMacAddress ;
	std::chrono::steady_clock::time_point mTimer ;
	std::vector<INetAddrPolicy::InterfaceDownFunc> mDownFunc ;
	std::vector<INetAddrPolicy::InterfaceUpFunc> mUpFunc ;

	std::vector<INetAddrPolicy::InterfaceAllocatedFunc> mAllocatedFunc ;
} ;

}

#endif /* NETWORKING_INC_NETADDRPOLICY_H_ */
