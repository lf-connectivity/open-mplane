/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IGpioLinuxMgr.h
 * \brief     Manager for Gpio linux devices
 *
 *
 * \details   Manages the creation of Gpio linux devices.
 *
 */


#ifndef VHI_INC_IGPIOLINUXMGR_H_
#define VHI_INC_IGPIOLINUXMGR_H_

#include <string>
#include <memory>
#include <map>

#include "IGpioControl.h"

namespace Mplane {

/*!
 * \class  IGpioLinuxMgr
 * \brief
 * \details
 *
 */
class IGpioLinuxMgr {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<IGpioLinuxMgr> singleton() ;

	IGpioLinuxMgr() {}
	virtual ~IGpioLinuxMgr() {}

	/**
	 * Registers a mapping from a user friendly name to a Gpio Linux device label. This friendly alias can then be used
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
	virtual std::shared_ptr<IGpioControl> getDeviceFromName(const std::string& name) =0 ;

	/**
	 * Given a device label, returns a pointer to the bus for that device; otherwise returns null pointer
	 * if unable to resolve name
	 */
	virtual std::shared_ptr<IGpioControl> getDeviceFromLabel(const std::string& label) =0 ;
} ;

}

#endif /* VHI_INC_IGPIOLINUXMGR_H_ */
