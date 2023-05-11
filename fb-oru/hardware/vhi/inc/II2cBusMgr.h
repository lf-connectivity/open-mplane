/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      II2cBusMgr.h
 * \brief     Manager for I2c busses
 *
 *
 * \details   Manages the creation of i2c busses for devices. Uses a unified naming scheme to ensure code reuse on any board
 *
 * 				The unified bus naming scheme follows the format:
 *
 * 				/<bus number>
 * 				or
 * 				/<bus number>/mux:<mux index>:<mux port>
 *
 * 				Given a name, the manager will return the full device path to the i2c bus device related to that name. This path
 * 				can then be used to create an I2cBusLinux object.
 *
 * 				On top of this is the unified device bus naming scheme which points to a bus for a particular device. This follows
 * 				the format:
 *
 * 				<unified bus name>/0x<i2c address in hex>
 *
 * 				Examples:
 * 				/1/mux:0:5/0x2F
 * 				/1/mux:0:1/0x36
 * 				/0/0x20
 *
 */


#ifndef VHI_INC_II2CBUSMGR_H_
#define VHI_INC_II2CBUSMGR_H_

#include <string>
#include <memory>
#include <map>

#include "II2cBus.h"

namespace Mplane {

/*!
 * \class  II2cBusMgr
 * \brief
 * \details
 *
 */
class II2cBusMgr {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<II2cBusMgr> singleton() ;

	II2cBusMgr() {}
	virtual ~II2cBusMgr() {}

	/**
	 * Registers a mapping from a user friendly name to a unified device name. This friendly alias can then be used
	 * via the namedDeviceBus() method
	 */
	virtual void registerNames(const std::map<std::string, std::string>& namesMap) =0 ;

	/**
	 * Get the map of alias names and their associated unified device name
	 */
	virtual std::map<std::string, std::string> getRegisteredNames() const =0 ;

	/**
	 * Given a name, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name.
	 * \note The name will need to have been registered previously via registerNames()
	 */
	virtual std::shared_ptr<II2cBus> namedDeviceBus(const std::string& name) =0 ;



	/**
	 * Given a unified device name, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<II2cBus> deviceBus(const std::string& unifiedDeviceName) =0 ;

	/**
	 * Given a unified device name and an i2c address, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<II2cBus> deviceBus(const std::string& unifiedBusName, unsigned i2cAddress) =0 ;

} ;

}

#endif /* VHI_INC_II2CBUSMGR_H_ */
