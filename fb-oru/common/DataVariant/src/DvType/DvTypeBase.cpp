/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeBase.cpp
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
#include "stringfunc.hpp"

#include "DvTypeBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DvTypeBase::DvTypeBase(const std::string& typeStr) :
	mTypeStr(typeStr),
	mIsSet(false),
	mStr(""),
	mUnits("")
{
}

//-------------------------------------------------------------------------------------------------------------
DvTypeBase::~DvTypeBase()
{
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::canHaveUnits() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::isSet() const
{
	return mIsSet ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::clear()
{
	mIsSet = false ;
	mStr.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::toString() const
{
	return mStr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::getValue() const
{
	std::string value(mStr) ;

	// get any units
	if (!mUnits.empty() && !value.empty())
    	value += mUnits ;

    return value ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeBase::getLimitsStr() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeBase::getLimitsMin() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeBase::getLimitsMax() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeBase::getLimitsStep() const
{
	return "" ;
}

//-------------------------------------------------------------------------------------------------------------
const bool DvTypeBase::isHex() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::setLimits(const std::string& limitsStr)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::checkLimits(std::string& error)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::checkLimits()
{
	std::string error ;
	return checkLimits(error) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setUnits(const std::string& units)
{
	mUnits = units ;
}

//-------------------------------------------------------------------------------------------------------------
const std::string DvTypeBase::getUnits() const
{
	return mUnits ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::getInitialTypeStr() const
{
	return mTypeStr ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(const std::string& str)
{
	mIsSet = true ;
	mStr = str ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(const IDvAccess::InterInt& ival)
{
    setStr(intToStr(ival)) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(const IDvAccess::InterFloat& fval)
{
    setStr(floatToStr(fval)) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(int ival)
{
    setStr(intToStr(ival)) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(float fval)
{
    setStr(floatToStr(fval)) ;
}

//-------------------------------------------------------------------------------------------------------------
void DvTypeBase::setStr(const std::complex<float>& complex)
{
    setStr(complexToStr(complex)) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::unitsFromStr(const std::string& value)
{
	// expect value to be integer or float with/without a units string suffix:
	//
	// 123.4MHz
	// -18dB
	//

	static const std::string validCharsNonHex("0123456789.-") ;
	static const std::string validCharsHex("0123456789ABCDEFabcdef") ;
	const std::string* validChars(&validCharsNonHex) ;

	// first check for hex input
	std::size_t start(0) ;
	if (DvTypeBase::strIsHex(value))
	{
		start = 2 ;
		validChars = &validCharsHex ;
	}

	// find first non-value char
	std::size_t suffixPos( value.find_first_not_of(*validChars, start) ) ;
	if (suffixPos == std::string::npos)
		return value ;

	// skip all string
	if (suffixPos == 0)
		return value ;

	// Ensure units string is valid
	std::string unitsStr(value.substr(suffixPos)) ;
	for (auto cc : unitsStr)
	{
		if (isalnum(cc))
			continue ;

		if (cc == '_')
			continue ;

		// invalid units char
		return value ;
	}

	// Check valid units
	if (!unitsStr.empty())
	{
		// Only allow units to be set if (a) no type defined yet, or (b) type defined AND default units are set
		// so fail if type defined AND no default units
		if (mIsSet && mUnits.empty())
		{
			// Invalid setting
			clear() ;
			return "" ;
		}

		// Now ok to set units
		mUnits = unitsStr ;
	}

	// return rest of value string
	return value.substr(0, suffixPos) ;
}


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsHex(const std::string& value)
{
	if (value.size() < 3)
		return false ;

	if ( value[0] != '0' || (value[1] != 'x' && value[1] != 'X') )
		return false ;

	for (unsigned idx=2; idx < value.size(); ++idx)
		if (!isxdigit(value[idx]))
			return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsNumber(const std::string& value)
{
	if (value.empty())
		return false ;

	// Generic check to see if this string starts with a valid INT or FLOAT (Does NOT do complete check)

    // if the string contains numbers from the start we assume we are setting
    // a number using a string value. Also need to check for negatives
	if (value[0] == '-')
	{
		if (value.size() == 1 || !isdigit(value[1]))
			return false ;

		return true ;
	}

	if ( !isdigit(value[0]) )
		return false ;

    return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsUnsigned(const std::string& value)
{
	if (value.empty())
		return false ;

    // Look for leading '-'
	if (value[0] == '-')
		return false ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsInt(const std::string& value)
{
	if (value.empty())
		return false ;

	unsigned start(0) ;

    // if the string contains numbers from the start we assume we are setting
    // a number using a string value. Also need to check for negatives
	if (value[0] == '-')
	{
		start = 1 ;
		if (value.size()==1)
			return false ;
	}

	for (unsigned idx=start; idx < value.size(); ++idx)
		if ( !isdigit(value[idx]) )
			return false ;

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsFloat(const std::string& value)
{
    // if the string contains a decimal point assume it is a float - need at least 2 chars to check this
	if (value.size() < 2)
		return false ;

	unsigned start(0) ;

    // if the string contains numbers from the start we assume we are setting
    // a number using a string value. Also need to check for negatives
	if (value[0] == '-')
	{
		start = 1 ;
		if (value.size() < 3)
			return false ;
	}

	// Check validity of chars
	unsigned numDp(0) ;
	for (unsigned idx=start; idx < value.size(); ++idx)
	{
		if (value[idx] == '.')
		{
			if (++numDp > 1)
				return false ;
			continue ;
		}

		if ( !isdigit(value[idx]) )
			return false ;
	}

	// should be 1 and only 1 DP
	if (numDp != 1)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsBool(const std::string& value)
{
	std::string lower(toLower(value)) ;
	for (auto valid : std::vector<std::string>{"true", "false", "1", "0"})
	{
		if (lower == valid)
			return true ;
	}
	return false ;
}



//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strToBool(const std::string& value)
{
	std::string lower(toLower(value)) ;
	for (auto validTrue : std::vector<std::string>{"true", "1"})
	{
		if (lower == validTrue)
			return true ;
	}
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::string > DvTypeBase::strToEnum(const std::string& str)
{
	std::vector< std::string > enumList ;

	// Expect string of the form "(LTE5:LTE10:LTE20)"
	if ((str.size() <= 2) || (str.at(0) != '('))
		return enumList ;

	size_t start = 1 ;
	while(start < str.size())
	{
		size_t end = str.find_first_of(":)", start) ;
		if (end == std::string::npos)
			break ;

		enumList.push_back(str.substr(start, end-start)) ;
		start = end+1 ;
	}

	return enumList ;
}

//-------------------------------------------------------------------------------------------------------------
bool DvTypeBase::strIsComplex(const std::string& value, std::complex<float>& complexVal)
{
	// General form is:
	// <real>+j<imag> or <real>-j<imag>
	// <real>+i<imag> or <real>-i<imag>
	// Where <real> and <imag> can be expressed as int or float
	//
	// Imaginary part must always follow real part.
	// <real> can be omitted, but imaginary part must always be specified even if 0
	//
	// Sign of imaginary part must always be before the 'j'

	static const std::string validChars{"0123456789.e+-ji"} ;

	if (value.empty())
		return false ;

	// Must have imaginary part specified
	std::size_t ipos(value.find_first_of("ji")) ;
	if (ipos == std::string::npos)
		return false ;

	// first check we only have valid chars
	if (value.find_first_not_of(validChars) != std::string::npos)
		return false ;

	// Get imaginary sign
	bool ineg(false) ;
	if (ipos > 0)
	{
		// char just in front of 'i' must be either '+' or '-'
		char isign(value[ipos-1]) ;
		if (isign != '+' && isign != '-')
			return false ;

		if (isign == '-')
			ineg = true ;
	}

	// imaginary value
	std::string imagStr(value.substr(ipos+1)) ;
	if (imagStr.empty())
		return false ;

	float imag(atof(imagStr.c_str())) ;
	if (ineg)
		imag = -imag ;
	complexVal.imag(imag) ;

	// real value if specified
	if (ipos >= 2)
		complexVal.real(atof(value.substr(0, ipos-1).c_str())) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::complexToStr(const std::complex<float>& complex)
{
	std::string sep("+j") ;
	auto realStr(floatToStr(complex.real())) ;

	float imag(complex.imag()) ;
	auto imagStr(floatToStr(imag)) ;
	if (imag < 0)
	{
		imagStr = floatToStr(-imag) ;
		sep = "-j" ;
	}

	return realStr+sep+imagStr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::floatToStr(const IDvAccess::InterFloat& fval)
{
	std::stringstream ss ;
	ss << std::fixed << fval ;
	return trim_float(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::DvTypeBase::intToStr(const IDvAccess::InterInt& ival)
{
	std::stringstream ss ;
	ss  << ival ;
	return trim_float(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DvTypeBase::floatToStr(float fval)
{
	std::stringstream ss ;
	ss << std::fixed << fval ;
	return trim_float(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::DvTypeBase::intToStr(int ival)
{
	std::stringstream ss ;
	ss  << ival ;
	return trim_float(ss.str()) ;
}
