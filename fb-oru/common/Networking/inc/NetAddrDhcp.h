/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrDhcp.h
 * \brief     DHCP ip address allocator
 *
 *
 */


#ifndef NETWORKING_INC_NETADDRDHCP_H_
#define NETWORKING_INC_NETADDRDHCP_H_

#include "SystemTask.h"
#include "NetAddr.h"

namespace Mplane {

/*!
 * \class  NetAddrDhcp
 * \brief  DHCP ip address allocator
 * \details   Runs DHCP to get an ip address allocated. May be run "in the background" to get a dynamic address after assigning
 * 			an address some other way (static/link local etc)
 *
 */
class NetAddrDhcp : public NetAddr {
public:
	NetAddrDhcp(const std::string& interface, const std::string& hostname = "", const std::string& dhcpScript = "", unsigned timeoutMs=0) ;
	virtual ~NetAddrDhcp() ;

protected:
	// Hooks which must be overridden by the derived classes

	/**
	 * Initialise the allocator
	 */
	virtual void doStart() override ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual void doAllocate() override ;

private:
	bool runDhcp() ;

private:
	std::string mHostname ;
	std::string mScript ;
	std::shared_ptr<SystemTask> mDhcp ;
	std::string mCurrentIp ;
} ;

}

#endif /* NETWORKING_INC_NETADDRDHCP_H_ */
