/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111BootEnv.h
 * \brief     Manages access to the u-boot environment
 *
 *
 * \details   The u-boot environment is stored in 2 NOR flash partitions (access in Linux as 2 devices). One is marked
 *            as the active bank, the other the inactive bank. Every time a change is made, it is written to the inactive
 *            bank and the banks swapped.
 *
 */


#ifndef Zcu111BootEnv_H_
#define Zcu111BootEnv_H_

#include "SingleBootEnv.h"

namespace Mplane {

class Zcu111BootEnv : public SingleBootEnv {
public:

	/**
	 * Singleton
	 */
	static std::shared_ptr<Zcu111BootEnv> getInstance() ;

	virtual ~Zcu111BootEnv() ;

	// TEST INTERFACE
#ifdef OFF_TARGET
public:
	/**
	 * Reset the environment back to default settings
	 */
	virtual void reset(const std::map<std::string, std::string>& env = std::map<std::string, std::string>()) override ;

#endif

protected:
	// May be overridden by derived object

	/**
	 * Process the device information line
	 * \param line Entry from /proc/mtd
	 * \param index If a valid line, returns the device index
	 * \return true if this is a valid line for the env; false otherwise
	 */
	virtual bool processDeviceLine(const std::string& line, unsigned& index) override ;

#ifdef OFF_TARGET
	/**
	 * Get the simulation list of devices
	 */
	virtual std::map<unsigned, BootEnv::PartitionInfo> getSimDeviceList() override ;

#endif


protected:
	// hide constructor so only singleton can be used
	Zcu111BootEnv() ;
} ;

}

#endif /* Zcu111BootEnv_H_ */
