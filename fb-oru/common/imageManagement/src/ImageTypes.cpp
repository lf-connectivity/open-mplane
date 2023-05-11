/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageTypes.cpp
 * \brief     Implements IImageTypes static methods
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>
#include "stringfunc.hpp"
#include "IImageTypes.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const std::map<IImageTypes::Type, std::string> typeMap{
	{IImageTypes::IMAGE_PACKAGE, 		"PKG"},
	{IImageTypes::IMAGE_APPLICATION, 	"APP"},
	{IImageTypes::IMAGE_LIBRARY, 		"LIB"},
	{IImageTypes::IMAGE_ROS, 			"OS"},
	{IImageTypes::IMAGE_FPGA, 			"FPGA"},
} ;

static const std::vector<IImageTypes::Type> types{
	IImageTypes::IMAGE_PACKAGE,
	IImageTypes::IMAGE_APPLICATION,
	IImageTypes::IMAGE_LIBRARY,
	IImageTypes::IMAGE_ROS,
	IImageTypes::IMAGE_FPGA,
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IImageTypes::typeToStr(Type type)
{
	return typeMap.at(type) ;
}

//-------------------------------------------------------------------------------------------------------------
bool IImageTypes::strToType(const std::string& str, Type& type)
{
	// See if we can match up this string with any of the image type strings
	// All the type strings are stored uppercase, so make the incoming string uppercase for
	// case-insensitive match
	std::string upperStr(toUpper(str)) ;

	for (auto typeEntry : typeMap)
	{
		// match type name anywhere in the string so we can match with things like 'application', 'ros' etc
		if (upperStr.find(typeEntry.second) != std::string::npos)
		{
			type = typeEntry.first ;
			return true ;
		}
	}
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<IImageTypes::Type> IImageTypes::typesList(void)
{
	return types ;
}
