/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiSettings.cpp
 * \brief     Settings object
 *
 *
 * \details   Contains the settings for the RTI session
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iterator>

#include "stringfunc.hpp"
#include "RtiSettings.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RtiSettings::RtiSettings()
{
	// Create the list of settings
	define("showInfo", DataVariantType::Bool, "false", "Enable to show extra info in command replies") ;
	define("showColumn", DataVariantType::Bool, "false", "Enable to display the replies in a column, one var/val per line") ;
	define("timestamp", DataVariantType::Bool, "false", "Timestamp prompt, showing execution time") ;
	define("memory", DataVariantType::Bool, "false", "Memory prompt, showing application used memory") ;
	define("formatVarVal", DataVariantType::Bool, "false", "(column mode) Enable to format variable/value for ease of viewing") ;
	define("varValChar", DataVariantType::String, ".", "(format column mode) Set to the variable space char") ;
	define("scriptsDir", DataVariantType::String, "/nandflash/tif/scripts", "Test scripts directory path") ;
	define("noecho", DataVariantType::Bool, "false", "Enable to stop telnet command echo, history, editing etc.") ;
}

//-------------------------------------------------------------------------------------------------------------
RtiSettings::~RtiSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
bool RtiSettings::has(const std::string& name) const
{
	std::shared_ptr<DataVariant> find( get(name) ) ;

	return find.get() != 0 ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DataVariant> RtiSettings::get(const std::string& name) const
{
	for(std::vector< std::shared_ptr<DataVariant> >::const_iterator iter(mSettings.begin()); iter != mSettings.end(); ++iter)
	{
		if (toLower((*iter)->getName()) == toLower(name))
			return *iter ;
	}
	return std::shared_ptr<DataVariant>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiSettings::getComment(const std::string& name) const
{
	for(std::vector< std::shared_ptr<DataVariant> >::const_iterator iter(mSettings.begin()); iter != mSettings.end(); ++iter)
	{
		if (toLower((*iter)->getName()) == toLower(name))
			return mComments.at( std::distance(mSettings.begin(), iter) ) ;
	}
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiSettings::set(const std::string& name, const std::string& value)
{
	for(std::vector< std::shared_ptr<DataVariant> >::const_iterator iter(mSettings.begin()); iter != mSettings.end(); ++iter)
	{
		if (toLower((*iter)->getName()) == toLower(name))
		{
			(*iter)->set(value) ;
			return true ;
		}
	}
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<DataVariant> >::const_iterator RtiSettings::begin(void) const
{
	return mSettings.begin() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<DataVariant> >::const_iterator RtiSettings::end(void) const
{
	return mSettings.end() ;
}


//-------------------------------------------------------------------------------------------------------------
bool RtiSettings::define(const std::string& name, const DataVariantType::Type& type,
		const std::string& value, const std::string& comment)
{
	if (!has(name))
	{
		std::shared_ptr<DataVariant> dv(new DataVariant(type, name, value) ) ;
		mSettings.push_back( dv ) ;
		mComments.push_back( comment ) ;
		return true ;
	}

	return false ;
}
