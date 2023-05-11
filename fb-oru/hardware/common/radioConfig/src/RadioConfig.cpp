/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfig.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include "Path.h"

#include "RadioConfig.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
const std::string STORAGE_PATH("/tmp/nandflash/.settings/radio-config") ;
#else
const std::string STORAGE_PATH("/nandflash/.settings/radio-config") ;
#endif

const std::string IRadioConfig::NUM_CARRIERS("max-carriers") ;
const std::string IRadioConfig::NUM_TX("tx/num-ports") ;
const std::string IRadioConfig::NUM_RX("rx/num-ports") ;
const std::string IRadioConfig::NUM_SRX("srx/num-ports") ;

const std::string IRadioConfig::RX_BANDWIDTH("rx/bandwidth-khz") ;
const std::string IRadioConfig::RX_CENTRE_FREQ("rx/centre-khz") ;
const std::string IRadioConfig::RX_MAX_AIR_FREQ("rx/max-air-khz") ;
const std::string IRadioConfig::RX_MIN_AIR_FREQ("rx/min-air-khz") ;
const std::string IRadioConfig::RX_MAX_FILTER_FREQ("rx/max-filter-khz") ;
const std::string IRadioConfig::RX_MIN_FILTER_FREQ("rx/min-filter-khz") ;
const std::string IRadioConfig::RX_MAX_FREQ("rx/max-freq-khz") ;
const std::string IRadioConfig::RX_MIN_FREQ("rx/min-freq-khz") ;

const std::string IRadioConfig::SRX_TX_PER_PORT("srx/tx-per-port") ;
const std::string IRadioConfig::SAW_BANDWIDTH("srx/bandwidth-khz") ;
const std::string IRadioConfig::SAW_CENTRE_FREQ("srx/centre-khz") ;
const std::string IRadioConfig::SAW_DIG_CENTRE_FREQ("srx/dig-centre-khz") ;

const std::string IRadioConfig::TX_BANDWIDTH("tx/bandwidth-khz") ;
const std::string IRadioConfig::TX_CENTRE_FREQ("tx/centre-khz") ;
const std::string IRadioConfig::TX_MAX_AIR_FREQ("tx/max-air-khz") ;
const std::string IRadioConfig::TX_MIN_AIR_FREQ("tx/min-air-khz") ;
const std::string IRadioConfig::TX_MAX_FILTER_FREQ("tx/max-filter-khz") ;
const std::string IRadioConfig::TX_MIN_FILTER_FREQ("tx/min-filter-khz") ;
const std::string IRadioConfig::TX_MAX_FREQ("tx/max-freq-khz") ;
const std::string IRadioConfig::TX_MIN_FREQ("tx/min-freq-khz") ;
const std::string IRadioConfig::TX_MAX_POWER("tx/max-power-db") ;
const std::string IRadioConfig::TX_MIN_POWER("tx/min-power-db") ;


//=============================================================================================================
// SINGLETONS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioConfig> IRadioConfig::singleton()
{
	return IRadioConfigSetter::singleton() ;
}

// NOTE: Each application that uses the IRadioConfig needs to provide it's own factory to create the singleton with the correct
// defaults

////-------------------------------------------------------------------------------------------------------------
//std::shared_ptr<IRadioConfigSetter> IRadioConfigSetter::singleton()
//{
//	return IRadioConfigSetter::create() ;
//}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioConfigSetter> IRadioConfigSetter::create(const std::map<std::string, std::string> defaults)
{
	static std::shared_ptr<IRadioConfigSetter> instance(std::make_shared<RadioConfig>(STORAGE_PATH, defaults)) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IRadioConfig::limitMinName(const std::string& varname)
{
	return std::string("min:") + varname ;
}

//-------------------------------------------------------------------------------------------------------------
std::string IRadioConfig::limitMaxName(const std::string& varname)
{
	return std::string("max:") + varname ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioConfig::RadioConfig(const std::string &path,
		const std::map<std::string, std::string> defaults) :
	Loggable("RadioConfig", "RadioConfig"),
	mConfig(defaults)
{
	// Ensure path exists
	Path::mkpath(Path::dir(path)) ;

	// Check for file existence
	FileConfigWriter currentConfig ;
	mConfig.setPath(path) ;
	currentConfig.setPath(path) ;
	if (Path::exists(path))
	{
		// config exists so read it
		mConfig.read() ;
		currentConfig.read() ;
	}

	// Clear out any unused/invalid variables from the config - i.e. any variables that are not in the defaults list
	mConfig.clean() ;

	// Check config in memory with that read from file - only need to write the file if the memory config is different
	if (mConfig != currentConfig)
	{
		// write out config to ensure all required variables are stored with a value (based on the defaults).
		// This ensures that older files will be updated to match the defaults
		mConfig.save() ;
		eventInfo("RadioConfig written - file does not match memory model") ;
	}
	else
	{
		logDebugNormal("Not writing RadioConfig - file matches memory") ;
	}
}

//-------------------------------------------------------------------------------------------------------------
RadioConfig::~RadioConfig()
{
}

//-------------------------------------------------------------------------------------------------------------
void RadioConfig::setLimits(const std::map<std::string, std::shared_ptr<DataVariant> > &limits)
{
	mLimits = limits ;

	// Apply the checks on all existing data
	std::vector< std::pair<std::string, std::string> > values(mConfig.values()) ;
	for (auto pair : values)
	{
		std::string validValue ;
		std::string error ;
		if (checkValue(pair.first, pair.second, validValue, error))
			continue ;

		// Report the error to the log
		eventWarning("%s", error.c_str()) ;

		// Modify the setting to a valid value
		mConfig.modifyValue(pair.first, validValue) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isValid() const
{
	return mConfig.isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RadioConfig::value(const std::string &varname) const
{
	return mConfig.value(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isVariable(const std::string &varname) const
{
	return mConfig.isVariable(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::setValue(const std::string &varname, const std::string &value)
{
	std::string validValue ;
	std::string error ;
	if (!checkValue(varname, value, validValue, error))
	{
		setError(error) ;
		return false ;
	}

	if (!mConfig.modifyValue(varname, value))
	{
		setError(mConfig.error()) ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::save()
{
	if (!mConfig.save())
	{
		setError(mConfig.error()) ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
double RadioConfig::doubleValue(const std::string &varname) const
{
	return mConfig.doubleValue(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
int RadioConfig::intValue(const std::string &varname) const
{
	return mConfig.intValue(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isDoubleValue(const std::string& varname) const
{
	if (!mConfig.isVariable(varname))
		return false ;

	return isDouble(mConfig.value(varname)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isIntValue(const std::string& varname) const
{
	if (!mConfig.isVariable(varname))
		return false ;

	return isInt(mConfig.value(varname)) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, std::string> > RadioConfig::values() const
{
	return mConfig.values() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RadioConfig::error()
{
	std::string err ;
	swap(mError, err) ;
	return err ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::checkValue(const std::string &varname, const std::string& newValue, std::string& validValue,
		std::string& error) const
{
	// get any limit settings for this variable
	std::shared_ptr<DataVariant> min( getLimit(IRadioConfig::limitMinName(varname)) ) ;
	std::shared_ptr<DataVariant> max( getLimit(IRadioConfig::limitMaxName(varname)) ) ;

	if (!checkMinMax(false, min, varname, newValue, validValue, error))
		return false ;

	if (!checkMinMax(true, max, varname, newValue, validValue, error))
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::checkMinMax(bool limitIsMax,
		std::shared_ptr<DataVariant> limit, const std::string &varname,
		const std::string &newValue, std::string &validValue,
		std::string &error) const
{
	if (!limit)
		return true ;

	std::stringstream ss ;

	// Compare value
	switch (limit->getType())
	{
	case DataVariantType::Int:
		validValue = std::to_string(limit->toInt()) ;
		if (!isInt(newValue))
		{
			ss << "RadioConfig " << varname << " value " << newValue << " is not an integer" ;
			error = ss.str() ;
			return false ;
		}

		if (limitIsMax)
		{
			if (toInt(newValue) > limit->toInt())
			{
				ss << "RadioConfig " << varname << " value " << newValue << " is above maximum " << validValue ;
				error = ss.str() ;
				return false ;
			}
		}
		else
		{
			if (toInt(newValue) < limit->toInt())
			{
				ss << "RadioConfig " << varname << " value " << newValue << " is below minimum " << validValue ;
				error = ss.str() ;
				return false ;
			}
		}
		break ;

	case DataVariantType::Double:
	case DataVariantType::Float:
		validValue = std::to_string(limit->toDouble()) ;
		if (!isDouble(newValue))
		{
			ss << "RadioConfig " << varname << " value " << newValue << " is not a float" ;
			error = ss.str() ;
			return false ;
		}

		if (limitIsMax)
		{
			if (toDouble(newValue) > limit->toDouble())
			{
				ss << "RadioConfig " << varname << " value " << newValue << " is above maximum " << validValue ;
				error = ss.str() ;
				return false ;
			}
		}
		else
		{
			if (toDouble(newValue) < limit->toDouble())
			{
				ss << "RadioConfig " << varname << " value " << newValue << " is below minimum " << validValue ;
				error = ss.str() ;
				return false ;
			}
		}
		break ;


	default:
		ss << "RadioConfig " << varname << " has an unknown limit type" ;
		error = ss.str() ;
		return false ;
		break ;

	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DataVariant> RadioConfig::getLimit(const std::string &name) const
{
	if (mLimits.find(name) == mLimits.end())
		return std::shared_ptr<DataVariant>() ;

	return mLimits.at(name) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isDouble(const std::string &value) const
{
	char* p ;
	const char* vp(value.c_str()) ;
	strtod(vp, &p) ;

	// if null then failed to convert
	if (p == nullptr)
		return false ;

	// if points to start of string then failed to convert
	if (p == vp)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RadioConfig::isInt(const std::string &value) const
{
	char* p ;
	const char* vp(value.c_str()) ;
	strtol(vp, &p, 0) ;

	// if null then failed to convert
	if (p == nullptr)
		return false ;

	// if points to start of string then failed to convert
	if (p == vp)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
double RadioConfig::toDouble(const std::string &value) const
{
	return strtod(value.c_str(), nullptr) ;
}

//-------------------------------------------------------------------------------------------------------------
int RadioConfig::toInt(const std::string &value) const
{
	return strtol(value.c_str(), nullptr, 0) ;
}
