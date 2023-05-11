/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef COMMON_BUS_INC_I2CBUSMGR_H_
#define COMMON_BUS_INC_I2CBUSMGR_H_

#include "II2cBusMgr.h"

namespace Mplane {

/*!
 * \class  I2cBusMgr
 * \brief
 * \details
 *
 */
class I2cBusMgr : public virtual II2cBusMgr {
public:
	I2cBusMgr() ;
	virtual ~I2cBusMgr() ;

	/**
	 * Registers a mapping from a user friendly name to a unified device name. This friendly alias can then be used
	 * via the namedDeviceBus() method
	 */
	virtual void registerNames(const std::map<std::string, std::string>& namesMap) override ;

	/**
	 * Get the map of alias names and their associated unified device name
	 */
	virtual std::map<std::string, std::string> getRegisteredNames() const override ;

	/**
	 * Given a name, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name.
	 * \note The name will need to have been registered previously via registerNames()
	 */
	virtual std::shared_ptr<II2cBus> namedDeviceBus(const std::string& name) override ;

	/**
	 * Given a unified device name, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<II2cBus> deviceBus(const std::string& unifiedDeviceName) override ;

	/**
	 * Given a unified device name and an i2c address, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<II2cBus> deviceBus(const std::string& unifiedBusName, unsigned i2cAddress) override ;

protected:
	// Hooks - need to be implemented by derived class

	/**
	 * Hook to create a new device bus
	 */
	virtual std::shared_ptr<II2cBus> createBus(const std::string& unifiedBusName, unsigned i2cAddress, unsigned bus,
			std::shared_ptr<IBusLock> busLock, std::shared_ptr<IBusSettings> busSettings) ;

protected:
	// Utilities

	/**
	 * Ensure these many i2c top-level busses are created (builds the bus locks and bus settings)
	 */
	void createBuses(unsigned numBusses) ;

private:
	std::map<std::string, std::shared_ptr<II2cBus>> mI2cBus ;
	std::vector< std::shared_ptr<IBusLock> > mBusLock ;
	std::vector< std::shared_ptr<IBusSettings> > mBusSetting ;
	std::map<std::string, std::string> mNames ;
} ;

}

#endif /* COMMON_BUS_INC_I2CBUSMGR_H_ */
