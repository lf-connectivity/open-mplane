/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Discovery.h
 * \brief     Network discovery service
 *
 *
 * \details   Uses SSDP to allow this application to be detected on the network
 *
 */


#ifndef DISCOVERY_H_
#define DISCOVERY_H_

#include "IDiscovery.h"

namespace Mplane {

class Ssdp ;

class Discovery : public virtual IDiscovery {
public:
	Discovery() ;
	virtual ~Discovery() ;

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

private:
	std::shared_ptr<Ssdp> mSsdp ;
} ;

}

#endif /* DISCOVERY_H_ */
