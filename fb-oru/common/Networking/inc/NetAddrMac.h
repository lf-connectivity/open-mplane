/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrMac.h
 * \brief     A "pseudo" policy that just checks the MAC
 *
 *
 * \details   This class checks the MAC, sets it if it doesn't match the expected value, then returns TIMED_OUT. Doesn't do any ip address
 * 				allocation, but since the MAC being set is crucial to IP addressing then it's sometimes useful to have this at the start
 * 				of the list
 *
 */


#ifndef NETWORKING_INC_NETADDRMAC_H_
#define NETWORKING_INC_NETADDRMAC_H_

#include "NetAddr.h"

namespace Mplane {

/*!
 * \class  NetAddrMac
 * \brief
 * \details
 *
 */
class NetAddrMac : public NetAddr {
public:
	NetAddrMac(const std::string& interface, const std::string& mac) ;
	virtual ~NetAddrMac() ;

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
	std::string mMac ;
} ;

}

#endif /* NETWORKING_INC_NETADDRMAC_H_ */
