/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddr.h
 * \brief     Base ip address allocator class
 *
 *
 */


#ifndef NETWORKING_INC_NETADDR_H_
#define NETWORKING_INC_NETADDR_H_

#include <chrono>
#include <mutex>

#include "INetAddr.h"
#include "Loggable.h"

namespace Mplane {

/*!
 * \class  NetAddr
 * \brief  Base ip address allocator class
 * \details   Base class that implements the ip address allocator
 *
 */
class NetAddr : public virtual INetAddr, public Loggable {
public:
	NetAddr(const std::string& name, INetChange::NetState netState, const std::string& interface, unsigned timeoutMs=0) ;
	virtual ~NetAddr() ;

	/**
	 * Name of this allocator (for debug)
	 */
	virtual std::string name() const override ;

	/**
	 * Returns the state as defined in INetChange::NetState which this allocator will be allocating an ip address
	 * as (e.g. NET_DHCP, NET_STATIC etc)
	 */
	virtual INetChange::NetState netStateType() const override ;

	/**
	 * Readback the interface that this allocator applies to
	 */
	virtual std::string interface() const override ;

	/**
	 * Does this allocator have a timeout time. If not then it will run forever or until an ip as allocated
	 */
	virtual bool isTimed() const override ;

	/**
	 * If timed this returns the timeout time in millisecs (or 0 if not timed)
	 */
	virtual unsigned timeoutTimeMs() const override ;

	/**
	 * Get current status of the allocator
	 */
	virtual INetAddr::NetAddrStatus status() const override ;

	/**
	 * Get the allocated ip address (or empty string if not allocated)
	 */
	virtual std::string ipAddress() const override ;

	/**
	 * Get the error string (clears stored error)
	 */
	virtual std::string error() override ;

	/**
	 * Initialise the allocator
	 */
	virtual INetAddr::NetAddrStatus start() override ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual INetAddr::NetAddrStatus allocate() override ;

	/**
	 * If this allocator allocated an ip address, should we stop now or carry on trying
	 * to allocate alternate addresses? (used by the address allocation policy)
	 */
	virtual bool stopOnAllocate() const override ;

protected:
	// Hooks which must be overridden by the derived classes

	/**
	 * Initialise the allocator
	 */
	virtual void doStart() =0 ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual void doAllocate() =0 ;


protected:
	// add to error string
	void setError(const std::string& error) ;

	// update the status
	void setStatus(INetAddr::NetAddrStatus status) ;

	// set the ip address
	void setIpAddress(const std::string& ipAddress) ;

	// has the allocator timed out yet?
	bool timedOut() ;

	// Utility to set the interface ip address
	bool setInterfaceIp(const std::string& ipAddr, const std::string& netmask = "255.255.0.0") ;

	// Utility to set the interface ip address and gateway
	bool setInterfaceIp(const std::string& ipAddr, const std::string& netmask, const std::string& gateway) ;

	// Utility to get current ip of the interface. If not UP with an allocated IP then
	// returns an empty string
	std::string interfaceUp() const ;

private:
	std::string mName ;
	INetChange::NetState mNetStateType ;
	std::string mInterface ;
	mutable std::mutex mMutex ;
	bool mIsTimed ;
	unsigned mTimeoutMs ;
	INetAddr::NetAddrStatus mStatus ;
	std::string mIpAddress ;
	std::string mError ;
	std::chrono::steady_clock::time_point mTimeoutTime ;
} ;

}

#endif /* NETWORKING_INC_NETADDR_H_ */
