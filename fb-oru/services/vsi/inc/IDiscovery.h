/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDiscovery.h
 * \brief     Network discovery service
 *
 *
 * \details   Provides the virtual interface to the network discovery service, where applications on the network can be discovered by a controlling
 * 			entity (e.g. GUI etc).
 *
 * 			Uses SSDP as the underlying mechanism
 *
 */


#ifndef IDISCOVERY_H_
#define IDISCOVERY_H_

#include <memory>
#include <string>
#include "IServicesCtl.h"


namespace Mplane {

class IDiscovery : public virtual IServiceMisc {
public:
	IDiscovery() {}
	virtual ~IDiscovery() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IDiscovery> getInstance() ;

	/**
	 * Get the interface IP address
	 */
	virtual std::string getIp() const =0 ;

	/**
	 * Get the SSDP UUID of this node
	 */
	virtual std::string getUuid() const =0 ;

	/**
	 * Get the cache max age in seconds. This is the maximum time between "alive" notifications
	 */
	virtual unsigned getCacheAge() const =0 ;

	/**
	 * Get the number of M-SEARCH messages responded to. An M-SEARCH is sent out by a controlling entity to discover what's connected
	 * to the network
	 */
	virtual unsigned getSearchCount() const =0 ;

	/**
	 * Get the number of NOTIFY messages sent. This node sends out notifications randomly (within a max delay period) in order to tell
	 * all controlling entities of it's presence
	 */
	virtual unsigned getNotifyCount() const =0 ;

} ;

}

#endif /* IDISCOVERY_H_ */
