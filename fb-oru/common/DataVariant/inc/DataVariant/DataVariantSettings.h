/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantSettings.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef DATAVARIANTSETTINGS_H_
#define DATAVARIANTSETTINGS_H_

#include "IDataVariantSettings.h"

namespace Mplane {

class DataVariantSettings : public IDataVariantSettings {
public:
	virtual ~DataVariantSettings() ;

	/**
	 * Clear out all settings (mainly used for test)
	 */
	virtual void clearSettings() override ;

	/**
	 * One-off registration of all the valid variable names and any default values
	 * @param settings
	 */
	virtual void registerSettings(const std::map<std::string, std::string>& settings) override ;

	/**
	 * Is the named setting registered?
	 * @param name
	 * @return true if registered; false otherwise
	 */
	virtual bool isSetting(const std::string& name) const override ;

	/**
	 * Set the value of the specified named setting
	 * @param name
	 * @param value
	 * @return true if set; false if unable to set (setting name invalid)
	 */
	virtual bool setSetting(const std::string& name, const std::string& value) override ;

	/**
	 * Expand any settings variables in string 'str' and return the expanded string
	 * @param str
	 * @param error
	 * @return expanded string or empty string with error string set on error
	 */
	virtual std::string expandString(const std::string& str, std::string& error) override ;

protected:
	DataVariantSettings() ;

private:
	std::map<std::string, std::string> mSettings ;
} ;

}

#endif /* DATAVARIANTSETTINGS_H_ */
