/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetAddr.h
 * \brief     Virtual interface to an ip address allocator
 *
 *
 */


#ifndef NETWORKING_INC_INETADDR_H_
#define NETWORKING_INC_INETADDR_H_

#include <memory>
#include <string>

#include "INetStatus.h"

namespace Mplane {

/*!
 * \class  INetAddr
 * \brief  Virtual interface to an ip address allocator
 * \details   A net address allocator describes how an IP address will be attained for a particular interface (e.g. use of DHCP). Multiple policies
 * 			can be set in a list so that if one fails the next can be tried.
 *
 */
class INetAddr {
public:
	INetAddr() {}
	virtual ~INetAddr() {}

	/**
	 * Special allocator used at the end of the list to restart processing from the start of the list
	 */
	static std::shared_ptr<INetAddr> REPEAT() ;

	/**
	 * Name of this allocator (for debug)
	 */
	virtual std::string name() const =0 ;

	/**
	 * Returns the state as defined in INetChange::NetState which this allocator will be allocating an ip address
	 * as (e.g. NET_DHCP, NET_STATIC etc)
	 */
	virtual INetChange::NetState netStateType() const =0 ;

	/**
	 * Readback the interface that this allocator applies to
	 */
	virtual std::string interface() const =0 ;

	/**
	 * Does this allocator have a timeout time. If not then it will run forever or until an ip as allocated
	 */
	virtual bool isTimed() const =0 ;

	/**
	 * If timed this returns the timeout time in millisecs (or 0 if not timed)
	 */
	virtual unsigned timeoutTimeMs() const =0 ;

	/**
	 * Get current status of the allocator
	 */
	enum NetAddrStatus {
		NET_INACTIVE	= 0,
		NET_RUNNING,
		NET_IP_ALLOCATED,
		NET_TIMED_OUT,
		NET_ERROR,
	};
	virtual NetAddrStatus status() const =0 ;

	/**
	 * Get the allocated ip address (or empty string if not allocated)
	 */
	virtual std::string ipAddress() const =0 ;

	/**
	 * Get the error string (clears stored error)
	 */
	virtual std::string error() =0 ;

	/**
	 * Initialise the allocator
	 */
	virtual NetAddrStatus start() =0 ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual NetAddrStatus allocate() =0 ;

	/**
	 * If this allocator allocated an ip address, should we stop now or carry on trying
	 * to allocate alternate addresses? (used by the address allocation policy)
	 */
	virtual bool stopOnAllocate() const =0 ;
} ;

}

#endif /* NETWORKING_INC_INETADDR_H_ */
