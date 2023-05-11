/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullRadioConfig.h
 * \brief     An IRadioConfig that does nothing
 *
 *
 * \details   An IRadioConfig that does nothing
 *
 */


#ifndef COMMON_RADIOCONFIG_INC_NULLRADIOCONFIG_H_
#define COMMON_RADIOCONFIG_INC_NULLRADIOCONFIG_H_

#include "IRadioConfig.h"

namespace Mplane {

/*!
 * \class  NullRadioConfig
 * \brief
 * \details
 *
 */
class NullRadioConfig : public virtual IRadioConfigSetter {
public:
	NullRadioConfig() ;
	NullRadioConfig(const std::string& path,
			const std::map<std::string, std::string> defaults = std::map<std::string, std::string>{}) ;
	virtual ~NullRadioConfig() ;

	/**
	 * Set limits on some/all of the variables. The keys must match a variable name
	 */
	virtual void setLimits(const std::map<std::string, std::shared_ptr<DataVariant>>& limits) override ;

	/**
	 * Is the current config valid?
	 */
	virtual bool isValid() const override ;

	/**
	 * Get the value of the variable
	 * @return value string if variable is preset; empty string otherwise
	 */
	virtual std::string value(const std::string& varname) const override ;

	/**
	 * is the variable available?
	 */
	virtual bool isVariable(const std::string& varname) const override ;


	/**
	 * Get the value of the variable as a double
	 * @return value if variable is preset; 0.0 otherwise
	 */
	virtual double doubleValue(const std::string& varname) const override ;

	/**
	 * Get the value of the variable as an int
	 * @return value if variable is preset; 0 otherwise
	 */
	virtual int intValue(const std::string& varname) const override ;

	/**
	 * Is the value of the variable a double?
	 * @return TRUE value if variable is a double
	 */
	virtual bool isDoubleValue(const std::string& varname) const override ;

	/**
	 * Is the value of the variable an int?
	 * @return TRUE value if variable is an integer
	 */
	virtual bool isIntValue(const std::string& varname) const override ;


	/**
	 * Get all the settings as varname/value pairs.
	 */
	virtual std::vector<std::pair<std::string, std::string>> values() const override ;


	/**
	 * Change a value
	 */
	virtual bool setValue(const std::string& varname, const std::string& value) override ;

	/**
	 * Save all values to non-volatile storage
	 */
	virtual bool save() override ;

	/**
	 * Get (and clear) any error strings
	 */
	virtual std::string error() override ;

} ;

}

#endif /* COMMON_RADIOCONFIG_INC_NULLRADIOCONFIG_H_ */
