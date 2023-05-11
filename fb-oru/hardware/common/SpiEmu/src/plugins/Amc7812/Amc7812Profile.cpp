/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Profile.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Amc7812Profile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812Profile::Amc7812Profile(const std::string& name,
		const std::string& measurement, float convertOffset,
		float convertFactor, float min, float max, float step) :
	Amc7812Handler(name, convertOffset, convertFactor),
	mMeasurement(measurement),
	mProfile(),
	mMin(min),
	mMax(max),
	mStep(step),
	mValue(min)
{
}

//-------------------------------------------------------------------------------------------------------------
Amc7812Profile::~Amc7812Profile()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Amc7812Profile::setProfile(ProfileFunc profile)
{
	mProfile = profile ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::Amc7812Profile::setValue(float value)
{
	mValue = value ;
}


//=============================================================================================================
// PROFILES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float Amc7812Profile::profileRampUp(float& value, float& min, float& max, float& step)
{
	// Ramp up to max then ripple between max and max-3*step

	// inc for next time
	if (value < min)
		value = min ;
	else if (value < max)
		value += step ;
	else
		value = max - 3*step ;

	return value ;
}

//-------------------------------------------------------------------------------------------------------------
float Amc7812Profile::profileSaw(float& value, float& min, float& max, float& step)
{
	// inc for next time
	value += step ;
	if (value >= max)
	{
		if (step > 0.0)
			step = -step ;
		value = max + step ;
	}
	if (value <= min)
	{
		if (step < 0.0)
			step = -step ;
		value = min + step ;
	}
	return value ;
}

//=============================================================================================================
// PROTECTED HOOK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float Amc7812Profile::getValue(unsigned address)
{
	logDebugNormal("Amc7812[%s] : %s %f", getInstanceName().c_str(), mMeasurement.c_str(), mValue) ;

	float value(mValue) ;

	// if profile set, then call it to update the next value
	if (mProfile)
	{
		mProfile(mValue, mMin, mMax, mStep) ;
	}

	return value ;
}
