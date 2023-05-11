/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrStatic.h
 * \brief     Link local ip address allocator
 *
 *
 */


#ifndef NETWORKING_INC_NETADDRSTATIC_H_
#define NETWORKING_INC_NETADDRSTATIC_H_

#include <random>
#include <map>
#include <bitset>

#include "SystemTask.h"
#include "NetAddr.h"

namespace Mplane {

/*!
 * \class  NetAddrStatic
 * \brief  Static ip allocator
 * \details   Perform static address assignment
 *
 */
class NetAddrStatic : public NetAddr {
public:
	NetAddrStatic(const std::string& interface) ;
	virtual ~NetAddrStatic() ;

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

} ;

}

#endif /* NETWORKING_INC_NETADDRSTATIC_H_ */
