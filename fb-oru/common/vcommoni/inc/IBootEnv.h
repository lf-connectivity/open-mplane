/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBootEnv.h
 * \brief     Virtual interface to low-level u-boot environment storage
 *
 *
 * \details   Provides access both to the low-level device driver and also to the environment variables. This interface uses IBootEnvDevice
 * 			as the storage and manages one or more of these devices transparently
 *
 */


#ifndef IBOOTENV_H_
#define IBOOTENV_H_

#include <string>
#include <map>
#include <vector>
#include <memory>


namespace Mplane {

class IBootEnvDevice ;

class IBootEnv {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<IBootEnv> getInstance() ;

	IBootEnv() {}
	virtual ~IBootEnv() {}

	/**
	 * Was the object created properly from the device
	 */
	virtual bool isValid() const =0 ;

	/**
	 * Get error string
	 */
	virtual std::string getError() =0 ;


	// Variable access

	/**
	 * Returns a copy of all the variable/value pairs
	 */
	virtual std::map<std::string, std::string> getVars() const =0 ;

	/**
	 * Does this environment variable exist?
	 * @param var
	 * @return true if valid variable
	 */
	virtual bool isVar(const std::string& var) const =0 ;

	/**
	 * Get the boot environment variable value
	 * @param var
	 * @return variable value as a string
	 */
	virtual std::string getVar(const std::string& var) const =0 ;

	/**
	 * Set a new value for the variable
	 * @param var
	 * @param value
	 * @return true if set ok
	 */
	virtual bool setVar(const std::string& var, const std::string& value) =0 ;

	/**
	 * Set one or more variable/value pairs
	 * @param vars	map of var/value pairs to be set
	 * @return true if set ok
	 */
	virtual bool setVar(const std::map<std::string, std::string>& vars) =0 ;

	/**
	 * Delete a variable
	 * @param var
	 * @return true if set ok
	 */
	virtual bool deleteVar(const std::string& var) =0 ;

	/**
	 * Delete one or more variables
	 * @param vars	list of variables to be delete
	 * @return true if set ok
	 */
	virtual bool deleteVar(const std::vector<std::string>& vars) =0 ;

	/**
	 * Clear out the environment and replace with the new variable/value pairs
	 * @param vars	new map of var/value pairs to be used as the environment
	 * @return true if set ok
	 */
	virtual bool resetVars(const std::map<std::string, std::string>& vars) =0 ;


	// Device access

	/**
	 * Get the index number (e.g. 1 for ubenv1, 2 for ubenv2 etc) for this object
	 */
	virtual unsigned getIndex() const =0 ;

	/**
	 * Get the underlying device name for this object
	 */
	virtual std::string getDeviceName() const =0 ;

	/**
	 * Is this the "active" u-boot environment
	 */
	virtual bool isActive() const =0 ;

	/**
	 * Read (re-read) the data from the device into this object. Automatically called at construction
	 */
	virtual bool read() =0 ;

	/**
	 * Write out the current contents of the object into flash
	 */
	virtual bool write() =0 ;

	// TEST INTERFACE
#ifdef OFF_TARGET
	/**
	 * Reset the environment back to default settings
	 */
	virtual void reset(const std::map<std::string, std::string>& env = std::map<std::string, std::string>()) =0 ;


	/**
	 * Get the underlying devices (used for testing)
	 */
	virtual std::vector<std::shared_ptr<IBootEnvDevice>> getDevices() const =0 ;

#endif


} ;

}

#endif /* IBOOTENV_H_ */
