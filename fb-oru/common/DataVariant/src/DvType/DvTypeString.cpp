/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeString.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include "DvTypeString.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string TYPE_STR{"STRING"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeString::DvTypeString(const std::string& typeStr) :
	DvTypeBase(typeStr)
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeString::~DvTypeString()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeString::canSetValue(const std::string& value) const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeString::canSetType(const std::string& typeStr) const
{
	if (typeStr == TYPE_STR)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeString::clear()
{
	setStr("") ;
	this->DvTypeBase::clear() ;
}


//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeString::getTypeStr() const
{
	return TYPE_STR ;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type DvTypeString::getType() const
{
	return DataVariantType::String ;
}


//-------------------------------------------------------------------------------------------------------------
std::string DvTypeString::getValue() const
{
	return "\"" + toString() + "\"" ;
}



//-------------------------------------------------------------------------------------------------------------
bool DvTypeString::set(const std::string& value)
{
	// treat empty string as clearing
	if (value.empty())
		clear() ;
	else
		setStr(value) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt Mplane::DvTypeString::toInterInt() const
{
	long long ll(0) ;
	try {
		ll = std::stoll(toString()) ;
	} catch (...) {}

	return static_cast<IDvAccess::InterInt>(ll) ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat Mplane::DvTypeString::toInterFloat() const
{
	double d(0.0) ;
	try {
		d = std::stod(toString()) ;
	} catch (...) {}

	return static_cast<IDvAccess::InterFloat>(d) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DvTypeString::fromInterInt(const IDvAccess::InterInt& value)
{
	std::stringstream ss ;
	ss << value ;
	setStr(ss.str()) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DvTypeString::fromInterFloat(const IDvAccess::InterFloat& value)
{
	std::stringstream ss ;
	ss << std::fixed << value ;
	setStr(ss.str()) ;
	return true ;
}
