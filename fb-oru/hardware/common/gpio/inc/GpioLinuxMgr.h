/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GpioLinuxMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef COMMON_BUS_INC_GPIOLINUXMGR_H_
#define COMMON_BUS_INC_GPIOLINUXMGR_H_

#include "IGpioLinuxMgr.h"

namespace Mplane {

/*!
 * \class  GpioLinuxMgr
 * \brief
 * \details
 *
 */
class GpioLinuxMgr : public virtual IGpioLinuxMgr {
public:
	GpioLinuxMgr() ;
	virtual ~GpioLinuxMgr() ;
	/**
	 * Registers a mapping from a user friendly name to a Gpio Linux device label. This friendly alias can then be used
	 * via the namedDeviceBus() method
	 */
	virtual void registerNames(const std::map<std::string, std::string>& namesMap) override;

	/**
	 * Get the map of alias names and their associated unified device name
	 */
	virtual std::map<std::string, std::string> getRegisteredNames() const override ;

	/**
	 * Given a name, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name.
	 * \note The name will need to have been registered previously via registerNames()
	 */
	virtual std::shared_ptr<IGpioControl> getDeviceFromName(const std::string& name) override ;

	/**
	 * Given a device label, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<IGpioControl> getDeviceFromLabel(const std::string& label) override ;

private:
	struct GpioChipInfo {
		GpioChipInfo() :
		devPath(), devLabel(), baseIndex(0), numGpios(0)
		{}

		GpioChipInfo(const std::string& path, const std::string& label, unsigned base, unsigned ngpio) :
		devPath(path), devLabel(label), baseIndex(base), numGpios(ngpio)
		{}

		std::string devPath ;                //!> Path in the format /dev/gpiochipN
		std::string devLabel;                //!> Label for the device
		unsigned baseIndex;                  //!> Start index of the GPIO for this device
		unsigned numGpios;                   //!> Number of GPIOs available for this device

	};

	std::vector<GpioChipInfo> mGpiochipInfo;
	std::map<std::string, std::shared_ptr<IGpioControl>> mGpioDevices ;
	std::map<std::string, std::string> mNames ;
	std::string mGpioSysPath;
} ;

}

#endif /* COMMON_BUS_INC_I2CBUSMGR_H_ */
