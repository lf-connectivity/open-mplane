/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadioConfig.h
 * \brief     Virtual interface to the radio configuration object
 *
 *
 * \details   This is (yet another) singleton that reads the radio configuration data from storage at start up and
 * 				provides the configuration constants to the rest of the application. Values stored here will be things like
 * 				frequency ranges, min/max TX power etc. The storage used can be anything as long as it's non-volatile.
 *
 * 				Variables are accessed by a name path. A variable can be "global" and accessed by just it's name; or it can
 * 				be under a "section" and needs to be accessed as a path with the section as the "directory". For example:
 *
 * 				Global variables:
 * 				"product-code"
 * 				"serial-number"
 *
 * 				Section variables:
 * 				"tx/max-power"
 * 				"tx/min-power"
 * 				"rx/max-frequency"
 *
 */


#ifndef VHI_INC_IRADIOCONFIG_H_
#define VHI_INC_IRADIOCONFIG_H_

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <memory>

#include "DataVariant.h"

namespace Mplane {

/*!
 * \class  IRadioConfig
 * \brief  read-only interface to radio config
 * \details
 *
 */
class IRadioConfig {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<IRadioConfig> singleton() ;

	IRadioConfig() {}
	virtual ~IRadioConfig() {}

	/**
	 * Set limits on some/all of the variables. The keys must match a variable name. For numeric values the key will be of the form:
	 *   min:<name> = minimum value for this <name>
	 *   max:<name> = maximum value for this <name>
	 * If either min or max is missing then that limit is not checked
	 *
	 * TODO: For strings we could implement a regexp check like:
	 *   regex:<name> = regular expression that the string must match
	 *
	 */
	virtual void setLimits(const std::map<std::string, std::shared_ptr<DataVariant>>& limits) =0 ;

	/**
	 * Create the name of the minimum limit from the variable name
	 */
	static std::string limitMinName(const std::string& varname) ;

	/**
	 * Create the name of the maximum limit from the variable name
	 */
	static std::string limitMaxName(const std::string& varname) ;

	/**
	 * Is the current config valid?
	 */
	virtual bool isValid() const =0 ;

	/**
	 * Get the value of the variable
	 * @return value string if variable is preset; empty string otherwise
	 */
	virtual std::string value(const std::string& varname) const =0 ;

	/**
	 * is the variable available?
	 */
	virtual bool isVariable(const std::string& varname) const =0 ;

	/**
	 * Get the value of the variable as a double
	 * @return value if variable is preset; 0.0 otherwise
	 */
	virtual double doubleValue(const std::string& varname) const =0 ;

	/**
	 * Get the value of the variable as an int
	 * @return value if variable is preset; 0 otherwise
	 */
	virtual int intValue(const std::string& varname) const =0 ;

	/**
	 * Is the value of the variable a double?
	 * @return TRUE value if variable is a double
	 */
	virtual bool isDoubleValue(const std::string& varname) const =0 ;

	/**
	 * Is the value of the variable an int?
	 * @return TRUE value if variable is an integer
	 */
	virtual bool isIntValue(const std::string& varname) const =0 ;

	/**
	 * Get all the settings as varname/value pairs.
	 */
	virtual std::vector<std::pair<std::string, std::string>> values() const =0 ;

	/**
	 * Get (and clear) any error strings
	 */
	virtual std::string error() =0 ;

public:
	// Config paths - defined here as constants so that we don't suffer from any typos in the app and end up with a mismatch
	// between the configuration and it's usage

	static const std::string NUM_CARRIERS ;
	static const std::string NUM_TX ;
	static const std::string NUM_RX ;
	static const std::string NUM_SRX ;

	static const std::string RX_BANDWIDTH ;
	static const std::string RX_CENTRE_FREQ ;
	static const std::string RX_MAX_AIR_FREQ ;
	static const std::string RX_MIN_AIR_FREQ ;
	static const std::string RX_MAX_FILTER_FREQ ;
	static const std::string RX_MIN_FILTER_FREQ ;
	static const std::string RX_MAX_FREQ ;
	static const std::string RX_MIN_FREQ ;

	static const std::string SRX_TX_PER_PORT ;

	static const std::string SAW_BANDWIDTH ;
	static const std::string SAW_CENTRE_FREQ ;
	static const std::string SAW_DIG_CENTRE_FREQ ;

	static const std::string TX_BANDWIDTH ;
	static const std::string TX_CENTRE_FREQ ;
	static const std::string TX_MAX_AIR_FREQ ;
	static const std::string TX_MIN_AIR_FREQ ;
	static const std::string TX_MAX_FILTER_FREQ ;
	static const std::string TX_MIN_FILTER_FREQ ;
	static const std::string TX_MAX_FREQ ;
	static const std::string TX_MIN_FREQ ;
	static const std::string TX_MAX_POWER ;
	static const std::string TX_MIN_POWER ;

} ;


/*!
 * \class  IRadioConfigSetter
 * \brief  Writeable interface to radio config
 * \details
 *
 */
class IRadioConfigSetter : public virtual IRadioConfig {
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<IRadioConfigSetter> singleton() ;

	/**
	 * Creator - ensures the singleton is created
	 */
	static std::shared_ptr<IRadioConfigSetter> create(
			const std::map<std::string, std::string> defaults = std::map<std::string, std::string>{}) ;


	IRadioConfigSetter() {}
	virtual ~IRadioConfigSetter() {}

	/**
	 * Change a value
	 */
	virtual bool setValue(const std::string& varname, const std::string& value) =0 ;

	/**
	 * Save all values to non-volatile storage
	 */
	virtual bool save() =0 ;



} ;


}

#endif /* VHI_INC_IRADIOCONFIG_H_ */
