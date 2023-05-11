/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeLong.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeLong.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"LONG"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeLong::DvTypeLong(const std::string& typeStr) :
	DvTypeBase(typeStr),
	mLong(0),
	mLimits()
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeLong::~DvTypeLong()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::canHaveUnits() const
{
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::canSetValue(const std::string& valueStr) const
{
	if (!strIsNumber(valueStr))
	{
		return false ;
	}

	if (strIsFloat(valueStr))
	{
		return false ;
	}

	if (strIsInt(valueStr))
	{
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::canSetType(const std::string& typeStr) const
{
    if ( typeStr == TYPESTR)
    	return true ;

    return false ;
}


//-------------------------------------------------------------------------------------------------------------
void DvTypeLong::clear()
{
	mLong = 0 ;
	this->DvTypeBase::clear() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeLong::getTypeStr() const
{
	return TYPESTR ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeLong::getLimitsStr() const
{
	return formatLimits(mLimits) ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeLong::getLimitsMin() const
{
	return mLimits.getMin() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeLong::getLimitsMax() const
{
	return mLimits.getMax() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeLong::getLimitsStep() const
{
	return mLimits.getStep() ;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type DvTypeLong::getType() const
{
	return DataVariantType::Long ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::setLimits(const std::string& limitsStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(limitsStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(minStr, maxStr, stepStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::checkLimits(std::string& error)
{
	// skip if not set
	if (!isSet())
		return true ;

	return mLimits.check(mLong, error) ;
}


//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::set(const std::string& value)
{
	std::string valueStr(unitsFromStr(value)) ;

	// Check valid value
	if ( !strIsNumber(valueStr) )
	{
		// invalid setting
		clear() ;
		return false ;
	}

	// Set value
    mLong = atoll( valueStr.c_str() );
    setStr(valueStr) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
long long DvTypeLong::toLong() const
{
	return mLong ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::setLong(long long value)
{
    mLong = value;
    std::ostringstream oss;
	oss << mLong ;
	setStr(oss.str()) ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt DvTypeLong::toInterInt() const
{
	return static_cast<IDvAccess::InterInt>(mLong) ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat DvTypeLong::toInterFloat() const
{
	return static_cast<IDvAccess::InterFloat>(mLong) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::fromInterInt(const IDvAccess::InterInt& value)
{
	return setLong(static_cast<long long>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeLong::fromInterFloat(const IDvAccess::InterFloat& value)
{
	return setLong(static_cast<long long>(value)) ;
}
