/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfig.h
 * \brief     Read/write the radio config
 *
 *
 * \details   Implements the IRadioConfig and IRadioConfigSetter APIs
 *
 */


#ifndef COMMON_RADIOCONFIG_INC_RADIOCONFIG_H_
#define COMMON_RADIOCONFIG_INC_RADIOCONFIG_H_

#include "IRadioConfig.h"
#include "Loggable.h"
#include "FileConfigWriter.h"

namespace Mplane {

/*!
 * \class  RadioConfig
 * \brief
 * \details
 *
 */
class RadioConfig : public virtual IRadioConfigSetter, public Loggable {
public:
	RadioConfig(const std::string& path,
			const std::map<std::string, std::string> defaults = std::map<std::string, std::string>{}) ;
	virtual ~RadioConfig() ;

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

protected:
	/**
	 * Check a variable value. If this variable has a limit setting then ensures the value is within those limits
	 */
	bool checkValue(const std::string& varname, const std::string& newValue, std::string& validValue,
			std::string& error) const ;

	bool checkMinMax(bool limitIsMax, std::shared_ptr<DataVariant> limit, const std::string& varname,
			const std::string& newValue, std::string& validValue, std::string& error) const ;

	/**
	 * Set an error and return FALSE
	 */
	bool setError(const std::string& error) ;

	/**
	 * Get the type of limit (e.g. min/max etc). If found returns the limit pointer; otherwise returns null
	 */
	std::shared_ptr<DataVariant> getLimit(const std::string& name) const ;

	bool isDouble(const std::string& value) const ;
	bool isInt(const std::string& value) const ;
	double toDouble(const std::string& value) const ;
	int toInt(const std::string& value) const ;


private:
	std::string mError ;
	FileConfigWriter mConfig ;
	std::map<std::string, std::shared_ptr<DataVariant>> mLimits ;
} ;

}

#endif /* COMMON_RADIOCONFIG_INC_RADIOCONFIG_H_ */
