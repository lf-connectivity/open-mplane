/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnvDevice.h
 * \brief     u-boot environment device class
 *
 *
 * \details   Manages access to one of the u-boot environment devices.
 *
 */


#ifndef BOOTENVDEVICE_H_
#define BOOTENVDEVICE_H_

#include <cstdint>

#include "Loggable.h"
#include "IBootEnvDevice.h"

namespace Mplane {

class BootEnvDevice : public virtual IBootEnvDevice, public Loggable
{
public:
	BootEnvDevice(unsigned index, const std::string& devName, bool flagSupported = true, unsigned envSize = 16384) ;
	virtual ~BootEnvDevice() ;

	/**
	 * Set or clear the active flag on this environment
	 * @param active
	 * @return true if set ok
	 */
	virtual bool setActiveFlag(bool active) override ;



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

	virtual void show() override ;
#endif

protected:
	// set the error message
	virtual void setError(const std::string& error) ;

	// Clear this device's flash
	virtual bool eraseFlash() ;

private:
	bool mFlagSupported ;
	unsigned mEnvSize ;
	bool mValid ;
	unsigned mIndex ;
	std::string mDevName ;
	uint32_t mCrc ;
	bool mActive ;

	// cache of variables
    std::map<std::string, std::string> mEnv ;

    std::string mError ;
} ;

}

#endif /* BOOTENVDEVICE_H_ */
