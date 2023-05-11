/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Delay.cpp
 * \brief     Model delays
 *
 *
 * \details   Provides a set of methods that convert from one set of delay units to another
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <cmath>

#include "Maths.h"
#include "Delay.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const DelayUnitNS& Delay::NS = DelayUnitNS::UNIT ;
const DelayUnitUI& Delay::UI = DelayUnitUI::UNIT ;
//const DelayUnitCLK& Delay::CLK = DelayUnitCLK::UNIT ;
//const DelayUnitCLK128& Delay::CLK128 = DelayUnitCLK128::UNIT ;
const DelayUnitBF& Delay::BF = DelayUnitBF::UNIT ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Delay::Delay(float delay, const IDelayUnit& unit, float lineRateMHz) :
	mDelay(delay),
	mUnit(&unit),
	mLineRateMHz(lineRateMHz)
{
}

//-------------------------------------------------------------------------------------------------------------
Delay::Delay(const Delay& other, const IDelayUnit& unit) :
	mDelay(other.get(unit)),
	mUnit(&unit),
	mLineRateMHz(other.mLineRateMHz)
{
}

//-------------------------------------------------------------------------------------------------------------
Delay::Delay(const Delay& other, const IDelayUnit& unit, float lineRateMHz) :
	mDelay(other.get(unit, lineRateMHz)),
	mUnit(&unit),
	mLineRateMHz(lineRateMHz)
{
}

//-------------------------------------------------------------------------------------------------------------
float Delay::get(const IDelayUnit& unit) const
{
	// if already in these units just return delay
	if (unit == *mUnit)
		return mDelay ;

	// First get the delay in ns
	float delay_ns = mUnit->to_ns(mDelay, mLineRateMHz) ;

	// Then convert to the final units
	float delay = unit.from_ns(delay_ns, mLineRateMHz) ;

	return delay ;
}


//-------------------------------------------------------------------------------------------------------------
float Delay::get(const IDelayUnit& unit, float lineRateMHz) const
{
	// First get the delay in ns
	float delay_ns = mUnit->to_ns(mDelay, mLineRateMHz) ;

	// Then convert to the final units
	float newDelay = unit.from_ns(delay_ns, lineRateMHz) ;

	return newDelay ;
}

//-------------------------------------------------------------------------------------------------------------
int Delay::getInt(const IDelayUnit& unit) const
{
	return static_cast<int>( fround( get(unit) ) ) ;
}

//-------------------------------------------------------------------------------------------------------------
const IDelayUnit& Delay::getUnit() const
{
	return *mUnit ;
}

//-------------------------------------------------------------------------------------------------------------
float Delay::getLineRate() const
{
	return mLineRateMHz ;
}

//-------------------------------------------------------------------------------------------------------------
void Delay::show(std::ostream& os) const
{
	os << get(*mUnit) << " " << mUnit->tostring(mLineRateMHz) ;
}


//-------------------------------------------------------------------------------------------------------------
Delay& Delay::add(const Delay& delta)
{
	Delay deltaAdjusted(delta) ;

	// if delta does not use the line rate BUT this delay does, then the conversion will go wrong because
	// delta will have a default line rate. To make the sums correct we need to adjust the delta so that
	// it's line rate matches 'this'
	if (mUnit->usesLineRate() && !delta.mUnit->usesLineRate())
	{
		deltaAdjusted.mLineRateMHz = mLineRateMHz ;
	}

	// Add
	Delay added(mDelay + deltaAdjusted.get(*mUnit, mLineRateMHz), *mUnit, mLineRateMHz) ;

	using std::swap ;
	swap(*this, added) ;
	return *this ;
}


//-------------------------------------------------------------------------------------------------------------
Delay& Delay::sub(const Delay& delta)
{
	Delay deltaAdjusted(delta) ;

	// if delta does not use the line rate BUT this delay does, then the conversion will go wrong because
	// delta will have a default line rate. To make the sums correct we need to adjust the delta so that
	// it's line rate matches 'this'
	if (mUnit->usesLineRate() && !delta.mUnit->usesLineRate())
	{
		deltaAdjusted.mLineRateMHz = mLineRateMHz ;
	}

	// Subtract
	Delay subtracted(mDelay - deltaAdjusted.get(*mUnit, mLineRateMHz), *mUnit, mLineRateMHz) ;

	using std::swap ;
	swap(*this, subtracted) ;
	return *this ;
}


//-------------------------------------------------------------------------------------------------------------
Delay& Delay::operator+=(const Delay& rhs)
{
	return add(rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::operator+=(const float rhs)
{
	return add(Delay(rhs)) ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::operator-=(const Delay& rhs)
{
	return sub(rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::operator-=(const float rhs)
{
	return sub(Delay(rhs)) ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::round()
{
	mDelay = static_cast<float>( getInt(*mUnit) ) ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::round(const IDelayUnit& unit)
{
	setUnit(unit) ;
	(void)round() ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::round(const IDelayUnit& unit, float lineRateMHz)
{
	setUnit(unit, lineRateMHz) ;
	(void)round() ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::ceil()
{
	mDelay = static_cast<float>( ::ceil(get(*mUnit)) ) ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::ceil(const IDelayUnit& unit)
{
	setUnit(unit) ;
	(void)ceil() ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::ceil(const IDelayUnit& unit, float lineRateMHz)
{
	setUnit(unit, lineRateMHz) ;
	(void)ceil() ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::floor()
{
	mDelay = static_cast<float>( ::floor(get(*mUnit)) ) ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::floor(const IDelayUnit& unit)
{
	setUnit(unit) ;
	(void)floor() ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::floor(const IDelayUnit& unit, float lineRateMHz)
{
	setUnit(unit, lineRateMHz) ;
	(void)floor() ;
	return *this ;
}


//-------------------------------------------------------------------------------------------------------------
Delay& Delay::setUnit(const IDelayUnit& unit)
{
	mDelay = get(unit) ;
	mUnit = &unit ;

	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
Delay& Delay::setUnit(const IDelayUnit& unit, float lineRateMHz)
{
	mDelay = get(unit, lineRateMHz) ;
	mUnit = &unit ;
	mLineRateMHz = lineRateMHz ;

	return *this ;
}
