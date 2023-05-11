/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetAddrLinkLocal.h
 * \brief     Link local ip address allocator
 *
 *
 */


#ifndef NETWORKING_INC_NETADDRLINKLOCAL_H_
#define NETWORKING_INC_NETADDRLINKLOCAL_H_

#include <random>
#include <map>
#include <bitset>

#include "SystemTask.h"
#include "NetAddr.h"

namespace Mplane {

/*!
 * \class  NetAddrLinkLocal
 * \brief  Link local networking allocator
 * \details   Perform link local address assignment
 *
 */
class NetAddrLinkLocal : public NetAddr {
public:
	NetAddrLinkLocal(const std::string& interface, unsigned timeoutMs=0) ;
	virtual ~NetAddrLinkLocal() ;

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
	virtual void doStart() override ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual void doAllocate() override ;

private:
	/**
	 * Reset the history
	 */
	void init() ;

	/**
	 * Checks to see if this 169.254.S.I has already been tried (i.e. is already in the history). Returns false if not already tried.
	 */
	bool isTried(unsigned subnet, unsigned ip) ;

	/**
	 * Generates a new random ip that has not been used before
	 */
	bool nextRandom(unsigned& subnet, unsigned& ip) ;

	/**
	 * Create new entry for this subnet
	 */
	void addHistory(unsigned subnet) ;

	/**
	 * Uses arping to check the address to see if anything else already uses it
	 */
	bool addressUsed(const std::string& ipAddr) ;

private:
	std::shared_ptr<SystemTask> mArping ;
    std::default_random_engine mRandGen ;
    std::uniform_int_distribution<unsigned> mRandIp ;
    std::map<unsigned, std::bitset<256>> mHistory ;
	unsigned mSubnet ;
	bool mFirst ;
} ;

}

#endif /* NETWORKING_INC_NETADDRLINKLOCAL_H_ */
