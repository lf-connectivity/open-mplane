/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetDevice.h
 * \brief     Provides an interface to gather information about a named device
 *
 *
 * \details   Uses Linux low-level access to the named network interface device
 *
 */


#ifndef NETDEVICE_H_
#define NETDEVICE_H_

#include <net/if.h>

#include <memory>
#include <string>
#include <vector>

#include "GlobalTypeDefs.h"

namespace Mplane {

#define ETH_SPEED_1K   (1000L)
#define ETH_SPEED_NULL (-1)

class NetDevice {
public:
	NetDevice() ;
	explicit NetDevice(const std::string& name, int64_t speed = -1, const std::string& descName = std::string()) ;
	virtual ~NetDevice() ;

	/**
	 * Factory method that finds all the network interfaces in the system and creates a vector of NetDevices, one
	 * per interface
	 */
	static std::vector<std::shared_ptr<NetDevice>> getInterfaces() ;

	/**
	 * Open the named network interface
	 * @param name
	 * @return true if opened; false on failure to open the device
	 */
	virtual bool open(const std::string& name) ;

	/**
	 * Close the device. Normally not specifically called since this class auto-closes any open device
	 */
	virtual void close() ;

	/**
	 * Loads/refreshes the opened device's current status
	 * @return true if updated ok
	 */
	virtual bool getStatus() ;

	// Accessors

	/**
	 * Get the device name
	 */
	virtual std::string getName() const ;

	/**
	 * Was the device opened correctly and all the data read properly?
	 */
	virtual bool isValid() const ;

	/**
	 * Is this a vlan tagged interface?
	 */
	virtual bool isVlan() const ;

	/**
	 * Get the vlan id (or 0 if not tagged)
	 */
	virtual int vlanId() const ;

	/**
	 * Get the base device name
	 */
	virtual std::string getBaseName() const ;

	/**
	 * For a physical device, add a tagged vlan interface
	 */
	virtual std::shared_ptr<NetDevice> createVlan(unsigned vlanId, const std::string& macId) ;

	/**
	 * Is the interface up
	 * @return true if up
	 */
	virtual bool isUp() const ;

	/**
	 * Valid broadcast address set
	 */
	virtual bool isBroadcast() const ;

	/**
	 * Supports multicast
	 */
	virtual bool isMulticast() const ;

	/**
	 * Is the interface physically connected?
	 */
	virtual bool isConnected() const ;


	/**
	 * Get the interface ip address
	 */
	virtual std::string getAddr() const ;

	/**
	 * Get the interface ip broadcast address
	 */
	virtual std::string getBroadcastAddr() const ;

	/**
	 * Get the interface ip net mask
	 */
	virtual std::string getNetmask() const ;

	/**
	 * Get the interface MAC id
	 */
	virtual std::string getMac() const ;

	/**
	 * Get the formatted interface MAC id (separated with ':')
	 */
	virtual std::string getMacFormatted() const;

	/**
	 * Set the interface ip address and optionally the netmask
	 */
	virtual bool setAddr(const std::string& addr, const std::string& netmask = "") ;

	/**
	 * Set the interface MAC id
	 */
	virtual bool setMac(const std::string& mac) ;

	/**
	 * Set interface up (or down if up=false)
	 */
	virtual bool setUp(bool up) ;

	/**
	 * Add a network route for this interface
	 */
	virtual bool addRoute(const std::string& addr, const std::string& netmask = "") ;

	/**
	 * Set the default gateway
	 */
	virtual bool addDefaultGateway(const std::string& addr) ;

protected:
	// get only the hardware status (should always be available)
	bool getHwStatus() ;

	/**
	 * Update the cached mac string
	 */
	void setMacStr(const std::string& macstr) ;

protected:
	// Convert sockaddr to C++ string
	static std::string addrToString(struct sockaddr* addr) ;

	// Convert hwaddr to C++ string
	static std::string macToString(struct sockaddr* addr) ;

	// carrier status - is carrier available (i.e. is the wire plugged in!)
	static bool carrierStatus(const std::string& interface) ;

#if 0
	// debug
	static void dump(struct sockaddr* addr) ;
#endif

private:
	std::string mName ;
	int mFd ;
	bool mGotInfo ;
	bool mGotHwInfo ;
	short mIfFlags ;
	std::string mAddr ;
	std::string mBroadcastAddr ;
	std::string mNetMask ;
	std::string mMac ;
	bool mConnected ;
} ;

}

#endif /* NETDEVICE_H_ */
