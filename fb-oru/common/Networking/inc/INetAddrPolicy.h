/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetAddrPolicy.h
 * \brief     Virtual interface to address allocation policy
 *
 *
 */


#ifndef NETWORKING_INC_INETADDRPOLICY_H_
#define NETWORKING_INC_INETADDRPOLICY_H_

#include <string>
#include <memory>
#include <functional>

#include "INetAddr.h"

namespace Mplane {

/*!
 * \class  INetAddrPolicy
 * \brief  Virtual interface to address allocation policy
 * \details   The address allocation policy is basically a list of address allocators that are run in sequence until
 * 			the interface in question has a valid ip address
 *
 */
class INetAddrPolicy {
public:

	/**
	 * Factory
	 */
	static std::shared_ptr<INetAddrPolicy> factory(const std::string& interface) ;

	INetAddrPolicy() {}
	virtual ~INetAddrPolicy() {}

	/**
	 * add an allocator to the list
	 */
	virtual void addAllocator(std::shared_ptr<INetAddr> allocator) =0 ;

	/**
	 * Get the named allocator or null pointer if unable to find
	 */
	virtual std::shared_ptr<INetAddr> getAllocator(const std::string& name) =0 ;

	/**
	 * Readback the interface name
	 */
	virtual std::string interface() const =0 ;

	/**
	 * Readback the interface description
	 */
	virtual std::string interfaceDescription() =0 ;

	/**
	 * Readback the interface speed
	 */
	virtual int64_t interfaceSpeed() =0 ;

	/**
	 * Readback the interface port
	 */
	virtual int8_t interfacePort() =0 ;

	/**
	 * Get current status
	 */
	virtual INetAddr::NetAddrStatus status() const =0 ;

	/**
	 * Get the allocated ip address (or empty string if not allocated)
	 */
	virtual std::string ipAddress() const =0 ;

	/**
	 * Get the allocated MAC address (or empty string if not allocated)
	 */
	virtual std::string macAddress() const =0 ;

	/**
	 * Get the error string (clears stored error)
	 */
	virtual std::string error() =0 ;

	/**
	 * Run the allocators until an ip has been assigned
	 */
	virtual void run() =0 ;

	/**
	 * Start up with initial state (used when running as a service)
	 */
	virtual void start() =0 ;

	/**
	 * Perform a single cycle of address allocation (used when running as a service)
	 */
	virtual void runCycle() =0 ;

	/**
	 * Called when activity is detected on the newly connected network (e.g. a TIF connection has been made)
	 * This will then stop the policy from trying to allocate any other ip address
	 */
	virtual void networkInUse() =0 ;

	/**
	 * Callback function for when interface goes down
	 */
	using InterfaceDownFunc = std::function<void(void)> ;

	/**
	 * Callback function for when interface goes up
	 */
	using InterfaceUpFunc = std::function<void(void)> ;

	/**
	 * Register a callback that is called when interface goes down
	 */
	virtual void registerDownFunc(InterfaceDownFunc func) =0 ;

	/**
	 * Register a callback that is called when interface goes up
	 */
	virtual void registerUpFunc(InterfaceUpFunc func) =0 ;

	/**
	 * Callback function for when the interface is allocated an IP address
	 */
	using InterfaceAllocatedFunc = std::function<void(const std::string& interface, const std::string& ipAddress,
			const std::string& macAddress, const std::string& allocatorName, INetChange::NetState allocatorType)> ;


	/**
	 * Register a callback for when the interface is allocated an IP address
	 */
	virtual void registerAllocatedFunc(InterfaceAllocatedFunc func) =0 ;

	/*
	 * Debug
	 */
	virtual void dump() const =0;
} ;

}

#endif /* NETWORKING_INC_INETADDRPOLICY_H_ */
