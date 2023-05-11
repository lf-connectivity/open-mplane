/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusLinuxMgr.h
 * \brief     Manage the I2cBus objects on Linux
 *
 *
 * \details   In Linux the I2c busses are enumerated according to the board's device tree. This can change per board, so to make
 * 				code more reusable, this management class probes the board to determine the i2c busses and their numbering. Applications
 * 				can then get access to the I2cBus device via a unified naming scheme.
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


#ifndef COMMON_BUS_INC_I2CBUSLINUXMGR_H_
#define COMMON_BUS_INC_I2CBUSLINUXMGR_H_

#include <map>
#include <string>
#include <memory>

#include "I2cBusMgr.h"

namespace Mplane {

/*!
 * \class  I2cBusLinuxMgr
 * \brief
 * \details
 *
 */
class I2cBusLinuxMgr : public I2cBusMgr {
public:
	/**
	 * Constructor scans the i2c busses and builds the name table
	 */
	I2cBusLinuxMgr() ;
	virtual ~I2cBusLinuxMgr() ;

protected:
	/**
	 * Hook to create a new device bus
	 */
	virtual std::shared_ptr<II2cBus> createBus(const std::string& unifiedBusName, unsigned i2cAddress, unsigned bus,
			std::shared_ptr<IBusLock> busLock, std::shared_ptr<IBusSettings> busSettings) override ;

private:
	/**
	 * Process sysfs to discover the i2c busses
	 */
	void gatherI2cBusses() ;

	/**
	 * Given a unified bus name, returns a device path; otherwise returns empty string if unable to resolve name
	 */
	std::string devicePath(const std::string& unifiedBusName) const ;


private:
	std::map<std::string, std::string> mNameMap ;
} ;

}

#endif /* COMMON_BUS_INC_I2CBUSLINUXMGR_H_ */
