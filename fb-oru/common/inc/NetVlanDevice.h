/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetVlanDevice.h
 * \brief     A vlan-tagged "virtual" interface
 *
 *
 * \details   A vlan-tagged "virtual" interface. This will be a "child" of a physical interface
 *
 */


#ifndef INC_NETVLANDEVICE_H_
#define INC_NETVLANDEVICE_H_

#include "NetDevice.h"

namespace Mplane {

/*!
 * \class  NetVlanDevice
 * \brief
 * \details
 *
 */
class NetVlanDevice : public NetDevice {
public:
//	NetVlanDevice() ;
	NetVlanDevice(const std::string& parent, unsigned vlanId, const std::string& macId) ;
	virtual ~NetVlanDevice() ;

	/**
	 * Open the named network interface
	 * @param name
	 * @return true if opened; false on failure to open the device
	 */
	virtual bool open(const std::string& name) override ;

	/**
	 * Close the device. Normally not specifically called since this class auto-closes any open device
	 */
	virtual void close() override ;

	/**
	 * Loads/refreshes the opened device's current status
	 * @return true if updated ok
	 */
	virtual bool getStatus() override ;

	// Accessors

	/**
	 * Get the device name
	 */
	virtual std::string getName() const override ;

	/**
	 * Was the device opened correctly and all the data read properly?
	 */
	virtual bool isValid() const override ;

	/**
	 * Is this a vlan tagged interface?
	 */
	virtual bool isVlan() const override ;

	/**
	 * Get the vlan id (or 0 if not tagged)
	 */
	virtual int vlanId() const override ;

	/**
	 * Get the base device name
	 */
	virtual std::string getBaseName() const override ;

	/**
	 * For a vlan device this method does nothing
	 */
	virtual std::shared_ptr<NetDevice> createVlan(unsigned vlanId, const std::string& macId) override ;


	/**
	 * Is the interface up
	 * @return true if up
	 */
	virtual bool isUp() const override ;

	/**
	 * Valid broadcast address set
	 */
	virtual bool isBroadcast() const override ;

	/**
	 * Supports multicast
	 */
	virtual bool isMulticast() const override ;

	/**
	 * Is the interface physically connected?
	 */
	virtual bool isConnected() const override ;


	/**
	 * Get the interface ip address
	 */
	virtual std::string getAddr() const override ;

	/**
	 * Get the interface ip broadcast address
	 */
	virtual std::string getBroadcastAddr() const override ;

	/**
	 * Get the interface ip net mask
	 */
	virtual std::string getNetmask() const override ;

	/**
	 * Get the interface MAC id
	 */
	virtual std::string getMac() const override ;


	/**
	 * Set the interface ip address and optionally the netmask
	 */
	virtual bool setAddr(const std::string& addr, const std::string& netmask = "") override ;

	/**
	 * Set the interface MAC id
	 */
	virtual bool setMac(const std::string& mac) override ;

	/**
	 * Set interface up (or down if up=false)
	 */
	virtual bool setUp(bool up) override ;

	/**
	 * Add a network route for this interface
	 */
	virtual bool addRoute(const std::string& addr, const std::string& netmask = "") override ;

	/**
	 * Set the default gateway
	 */
	virtual bool addDefaultGateway(const std::string& addr) override ;

private:
	std::string mParentName ;
	unsigned mVlanId ;
	std::string mVlanBaseName;
	std::string mVlanMac ;
	bool mVlanCreated ;
} ;

}

#endif /* INC_NETVLANDEVICE_H_ */
