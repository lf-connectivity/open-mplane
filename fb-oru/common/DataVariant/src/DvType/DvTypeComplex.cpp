/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeComplex.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "DvTypeComplex.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string TYPESTR{"COMPLEX"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeComplex::DvTypeComplex(const std::string& typeStr) :
	DvTypeBase(typeStr),
	mComplex(0.0, 0.0),
	mLimits()
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeComplex::~DvTypeComplex()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::canSetValue(const std::string& valueStr) const
{
	std::complex<float> complexVal ;
    if (strIsComplex(valueStr, complexVal))
   		return true ;

 	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::canSetType(const std::string& typeStr) const
{
    if ( typeStr == TYPESTR)
    	return true ;

    return false ;
}


//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeComplex::getTypeStr() const
{
	return TYPESTR ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeComplex::getLimitsStr() const
{
	std::stringstream ss ;

	mLimits.show(ss) ;
	if (!ss.str().empty())
		return "{" + ss.str() + "}" ;

	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeComplex::getLimitsMin() const
{
	return mLimits.getMin() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeComplex::getLimitsMax() const
{
	return mLimits.getMax() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeComplex::getLimitsStep() const
{
	return mLimits.getStep() ;
}

//-------------------------------------------------------------------------------------------------------------
const DataVariantType::Type DvTypeComplex::getType() const
{
	return DataVariantType::Complex ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::setLimits(const std::string& limitsStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(limitsStr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)
{
	mLimits.setUnits(getUnits()) ;
	return mLimits.set(minStr, maxStr, stepStr) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeComplex::clear()
{
	mComplex = std::complex<float>(0.0, 0.0) ;
	this->DvTypeBase::clear() ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::checkLimits(std::string& error)
{
	// skip if not set
	if (!isSet())
		return true ;

	if (!mLimits.check(mComplex.real(), error))
		return false ;

	if (!mLimits.check(mComplex.imag(), error))
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::complex<float> DvTypeComplex::toComplex() const
{
	return mComplex ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::set(const std::string& valueStr)
{
	// Check valid value
	std::complex<float> complexVal ;
    if (!strIsComplex(valueStr, complexVal))
    {
    	mComplex = std::complex<float>(0.0, 0.0) ;
    	setStr("") ;
    	return false ;
    }

	// Set value
    mComplex = complexVal ;
    setStr(valueStr) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::setComplex(const std::complex<float>& value)
{
    mComplex = value;
    setStr(mComplex) ;
    return true ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterInt DvTypeComplex::toInterInt() const
{
	return static_cast<IDvAccess::InterInt>(mComplex.real()) ;
}

//-------------------------------------------------------------------------------------------------------------
IDvAccess::InterFloat DvTypeComplex::toInterFloat() const
{
	return static_cast<IDvAccess::InterFloat>(mComplex.real()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::fromInterInt(const IDvAccess::InterInt& value)
{
	return setComplex(std::complex<float>(
		static_cast<float>(value),
		0.0
	)) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeComplex::fromInterFloat(const IDvAccess::InterFloat& value)
{
	return setComplex(std::complex<float>(
		static_cast<float>(value),
		0.0
	)) ;
}
