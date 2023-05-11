/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeDouble.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeDouble.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"DOUBLE"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeDouble::DvTypeDouble(const std::string& typeStr) :
	DvTypeBase(typeStr),
	mDouble(0.0),
	mLimits()
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeDouble::~DvTypeDouble()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::canHaveUnits() const
{
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::canSetValue(const std::string& valueStr) const
{
	if (!strIsNumber(valueStr))
		return false ;

	if (strIsFloat(valueStr))
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::canSetType(const std::string& typeStr) const
{
    if ( typeStr == TYPESTR)
    	return true ;

    return false ;
}


//-------------------------------------------------------------------------------------------------------------
void DvTypeDouble::clear()
{
	mDouble = 0.0 ;
	this->DvTypeBase::clear() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeDouble::getTypeStr() const
{
	return TYPESTR ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeDouble::getLimitsStr() const
{
	return formatLimits(mLimits) ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeDouble::getLimitsMin() const
{
	return mLimits.getMin() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeDouble::getLimitsMax() const
{
	return mLimits.getMax() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeDouble::getLimitsStep() const
{
	return mLimits.getStep() ;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type DvTypeDouble::getType() const
{
	return DataVariantType::Double ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::setLimits(const std::string& limitsStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(limitsStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(minStr, maxStr, stepStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::checkLimits(std::string& error)
{
	// skip if not set
	if (!isSet())
		return true ;

	return mLimits.check(mDouble, error) ;
}


//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::set(const std::string& value)
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
    mDouble = atof( valueStr.c_str() );
    setStr(valueStr) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
double DvTypeDouble::toDouble() const
{
	return mDouble ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::setDouble(double value)
{
    mDouble = value;
    setStr(mDouble) ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt DvTypeDouble::toInterInt() const
{
	return static_cast<IDvAccess::InterInt>(mDouble) ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat DvTypeDouble::toInterFloat() const
{
	return static_cast<IDvAccess::InterFloat>(mDouble) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::fromInterInt(const IDvAccess::InterInt& value)
{
	return setDouble(static_cast<double>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeDouble::fromInterFloat(const IDvAccess::InterFloat& value)
{
	return setDouble(static_cast<double>(value)) ;
}
