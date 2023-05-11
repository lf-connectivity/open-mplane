/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrPolicyMock.h
 * \brief     Base class implementing INetAddrPolicy
 *
 *
 */


#ifndef NETWORKING_INC_NETADDRPOLICYMOCK_H_
#define NETWORKING_INC_NETADDRPOLICYMOCK_H_

#include <map>
#include <memory>
#include <vector>
#include <atomic>
#include <chrono>

#include "Loggable.h"

#include "INetAddr.h"
#include "INetAddrPolicy.h"
#include "TestLinuxPtp.h"

namespace Mplane {

/*!
 * \class  NetAddrPolicy
 * \brief  Base class implementing INetAddrPolicy
 * \details
 *
 */
class NetAddrPolicyMock : public virtual INetAddrPolicy, public Loggable {
public:
	NetAddrPolicyMock(const std::string& interface) ;
	virtual ~NetAddrPolicyMock() ;

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

	void setInterface(bool up) {
		mInterfaceUp = up;
	}

private:
	bool mInterfaceUp ;
	bool mPrevInterfaceUp ;
	std::string mInterface ;
	std::atomic<INetAddr::NetAddrStatus> mStatus ;
	std::vector<INetAddrPolicy::InterfaceDownFunc> mDownFunc ;
	std::vector<INetAddrPolicy::InterfaceUpFunc> mUpFunc ;

	friend class TestLinuxPtp;
} ;

}

#endif /* NETWORKING_INC_NETADDRPOLICY_H_ */
