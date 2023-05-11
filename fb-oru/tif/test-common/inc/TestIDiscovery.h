/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIDiscovery.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTIDISCOVERY_H_
#define TESTIDISCOVERY_H_

#include "IDiscovery.h"

namespace Mplane {

class TestIDiscovery : public virtual IDiscovery {
public:
	TestIDiscovery() ;
	virtual ~TestIDiscovery() ;

	/**
	 * Get the interface IP address
	 */
	virtual std::string getIp() const override ;

	/**
	 * Get the SSDP UUID of this node
	 */
	virtual std::string getUuid() const override ;

	/**
	 * Get the cache max age in seconds. This is the maximum time between "alive" notifications
	 */
	virtual unsigned getCacheAge() const override ;

	/**
	 * Get the number of M-SEARCH messages responded to. An M-SEARCH is sent out by a controlling entity to discover what's connected
	 * to the network
	 */
	virtual unsigned getSearchCount() const override ;

	/**
	 * Get the number of NOTIFY messages sent. This node sends out notifications randomly (within a max delay period) in order to tell
	 * all controlling entities of it's presence
	 */
	virtual unsigned getNotifyCount() const override ;


} ;

}

#endif /* TESTIDISCOVERY_H_ */
