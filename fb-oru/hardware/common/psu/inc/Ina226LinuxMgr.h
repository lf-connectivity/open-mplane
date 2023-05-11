/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226LinuxMgr.h
 * \brief     Create a list of available INA226 monitors
 *
 *
 * \details   Runs through all hwmon drivers creating INA226 objects for each
 * 				and keeping only the valid ones. Creates a map of objects based
 * 				on a given table.
 *
 */


#ifndef COMMON_PSU_INC_INA226LINUXMGR_H_
#define COMMON_PSU_INC_INA226LINUXMGR_H_


#include <string>
#include <memory>
#include <map>

#include "IPsuMonitorDriver.h"

namespace Mplane {

/*!
 * \class  Ina226LinuxMgr
 * \brief
 * \details
 *
 */
class Ina226LinuxMgr {
public:
	Ina226LinuxMgr() ;
	Ina226LinuxMgr(const std::map<std::string, std::string>& names) ;
	virtual ~Ina226LinuxMgr() ;

	/**
	 * Sets the name map to map from a device name to a user name
	 */
	void setMapping(const std::map<std::string, std::string>& names) ;

	/**
	 * Get a named monitor; or null if not found
	 */
	std::shared_ptr<IPsuMonitorDriver> getMonitor(const std::string& name) ;

	// DEBUG

	/**
	 * Set the top-level sysfs location for debugging
	 */
	void setSysfs(const std::string& sysfs) ;

private:
	void init() ;

private:
	std::map<std::string, std::shared_ptr<IPsuMonitorDriver>> mMonitors ;
	std::string mSysFs ;
} ;

}

#endif /* COMMON_PSU_INC_INA226LINUXMGR_H_ */
