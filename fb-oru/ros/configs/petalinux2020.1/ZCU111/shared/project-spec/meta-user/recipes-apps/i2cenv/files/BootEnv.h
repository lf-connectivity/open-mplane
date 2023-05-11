/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnv.h
 * \brief     Manages access to the u-boot environment
 *
 *
 * \details   The u-boot environment is stored in 2 NOR flash partitions (access in Linux as 2 devices). One is marked
 *            as the active bank, the other the inactive bank. Every time a change is made, it is written to the inactive
 *            bank and the banks swapped.
 *
 */


#ifndef BOOTENV_H_
#define BOOTENV_H_

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <mutex>

#include "IBootEnv.h"
#include "IBootEnvDevice.h"
#include "Loggable.h"

namespace Mplane {

class BootEnv : public virtual IBootEnv, public Loggable {
public:

	/**
	 * Singleton
	 */
	static std::shared_ptr<BootEnv> getInstance() ;

	virtual ~BootEnv() ;

	/**
	 * Was the object created properly from the device
	 */
	virtual bool isValid() const override ;

	/**
	 * Get error string
	 */
	virtual std::string getError() override ;


	// Variable access

	/**
	 * Returns a copy of all the variable/value pairs
	 */
	virtual std::map<std::string, std::string> getVars() const override ;

	/**
	 * Does this environment variable exist?
	 * @param var
	 * @return true if valid variable
	 */
	virtual bool isVar(const std::string& var) const override ;

	/**
	 * Get the boot environment variable value
	 * @param var
	 * @return variable value as a string
	 */
	virtual std::string getVar(const std::string& var) const override ;

	/**
	 * Set a new value for the variable
	 * @param var
	 * @param value
	 * @return true if set ok
	 */
	virtual bool setVar(const std::string& var, const std::string& value) override ;

	/**
	 * Set one or more variable/value pairs
	 * @param vars	map of var/value pairs to be set
	 * @return true if set ok
	 */
	virtual bool setVar(const std::map<std::string, std::string>& vars) override ;

	/**
	 * Delete a variable
	 * @param var
	 * @return true if set ok
	 */
	virtual bool deleteVar(const std::string& var) override ;

	/**
	 * Delete one or more variables
	 * @param vars	list of variables to be delete
	 * @return true if set ok
	 */
	virtual bool deleteVar(const std::vector<std::string>& vars) override ;

	/**
	 * Clear out the environment and replace with the new variable/value pairs
	 * @param vars	new map of var/value pairs to be used as the environment
	 * @return true if set ok
	 */
	virtual bool resetVars(const std::map<std::string, std::string>& vars) override ;


	// Device access

	/**
	 * Get the index number (e.g. 1 for ubenv1, 2 for ubenv2 etc) for this object
	 */
	virtual unsigned getIndex() const override ;

	/**
	 * Get the underlying device name for this object
	 */
	virtual std::string getDeviceName() const override ;

	/**
	 * Is this the "active" u-boot environment
	 */
	virtual bool isActive() const override ;

	/**
	 * Read (re-read) the data from the device into this object. Automatically called at construction
	 */
	virtual bool read() override ;

	/**
	 * Write out the current contents of the object into flash
	 */
	virtual bool write() override ;


	// TEST INTERFACE
#ifdef OFF_TARGET
public:
	/**
	 * Reset the environment back to default settings
	 */
	virtual void reset(const std::map<std::string, std::string>& env = std::map<std::string, std::string>()) override ;


	/**
	 * Get the underlying devices (used for testing)
	 */
	virtual std::vector<std::shared_ptr<IBootEnvDevice>> getDevices() const override ;

#endif

protected:
	// May be overridden by derived object

	/**
	 * Process the device information line
	 * \param line Entry from /proc/mtd
	 * \param index If a valid line, returns the device index
	 * \return true if this is a valid line for the env; false otherwise
	 */
	virtual bool processDeviceLine(const std::string& line, unsigned& index) ;

	/**
	 * Write the new environment
	 * @return false (and set error string) on any error
	 */
	virtual bool writeEnv(const std::map<std::string, std::string>& newEnv) ;

	/**
	 * Information derived from process table
	 */
	struct PartitionInfo {
		std::string name ;
		unsigned size ;
		unsigned eraseSize ;
	};

#ifdef OFF_TARGET
	/**
	 * Get the simulation list of devices
	 */
	virtual std::map<unsigned, PartitionInfo> getSimDeviceList() ;

#endif

protected:
	// Utilities

	// Check current data and return false (and set error) if current state is not valid
	virtual bool checkState() const ;

	// Read the partition information
	virtual std::map<unsigned, PartitionInfo> getDeviceList() ;

	// Set the expected minimum number of "banks" of env vars
	void setMinBanks(unsigned numBanks) ;

	/**
	 * Write the new environment to the inactive bank, then switch banks
	 * @return false (and set error string) on any error
	 */
	bool writeInactive(const std::map<std::string, std::string>& newEnv) ;

	/**
	 * Write the new environment to the active bank
	 * @return false (and set error string) on any error
	 */
	bool writeActive(const std::map<std::string, std::string>& newEnv) ;

protected:
	// constructor
	// maxEnvSize       - when >0 sets the maximum size of the environment
	// flagSupported 	- set when env supports active flag
	// deferInit		- set when derived class wants to defer initialisation until that class is ready
	BootEnv(unsigned maxEnvSize =0, bool flagSupported = true, bool deferInit = false) ;

	// Initialise the object data
	bool init() ;


private:
	bool mFlagSupported ;
	unsigned mMaxEnvSize ;

	mutable std::mutex mMutex ;

    // List of devices
    std::vector<std::shared_ptr<IBootEnvDevice>> mEnvDevices ;

    // The currently active device
    std::shared_ptr<IBootEnvDevice> mActiveEnv ;

    // The alternate device
    std::shared_ptr<IBootEnvDevice> mInactiveEnv ;

    // Current error
    mutable std::string mError ;

    // expected number of banks
    unsigned mMinNumBanks ;
} ;

}

#endif /* BOOTENV_H_ */
