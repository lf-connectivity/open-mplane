/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetStatus.h
 * \brief     Monitor network status
 *
 *
 */


#ifndef INETSTATUS_H_
#define INETSTATUS_H_

#include <string>
#include <memory>

#include "Observer.hpp"

namespace Mplane {

/**
 * \class  NetChange
 * \brief  Network status change event
 * \details   Encapsulates the state of a network interface on a change event. Uses a log file to keep track of the current interface settings
 *
 */
class INetChange {
public:
	enum NetState {
		NET_DISCONNECTED,
		NET_STATIC,
		NET_DHCP,
		NET_LINK_LOCAL,
	};

	INetChange() {}
	virtual ~INetChange() {}

	// Accessors
	virtual const std::string& getInterface() const =0 ;
	virtual const std::string& getIp() const =0 ;
	virtual NetState getState() const =0 ;

	/**
	 * Convert state to string for logging
	 */
	static std::string stateStr(NetState state) ;
};


/*!
 * \class  INetStatus
 * \brief
 * \details
 *
 */
class INetStatus : public Subject<INetStatus, const INetChange&> {
public:
	INetStatus() {}
	virtual ~INetStatus() {}



	/**
	 * Singleton
	 */
	static std::shared_ptr<INetStatus> getInstance() ;

	/**
	 * Get latest changed interface
	 */
	virtual std::string getInterface() const =0 ;

	/**
	 * Get ip address for latest changed interface
	 */
	virtual std::string getIp() const =0 ;

	/**
	 * Get state for latest changed interface
	 */
	virtual INetChange::NetState getState() const =0 ;

	/**
	 * Get ip address for specified interface
	 */
	virtual std::string getIp(const std::string& interface) const =0 ;

	/**
	 * Get state for specified interface
	 */
	virtual INetChange::NetState getState(const std::string& interface) const =0 ;

	/**
	 * Set the current state of an interface
	 */
	virtual bool setState(const std::string& interface, INetChange::NetState state, const std::string& ipAddress = "") =0 ;

} ;

}

#endif /* INETSTATUS_H_ */
