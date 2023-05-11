/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Adc.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Amc7812Adc.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAmc7812Handler> Amc7812Adc::factory(
		const std::string& name, float convertOffset, float convertFactor,
		float min, float max, float step)
{
	return std::make_shared<Amc7812Adc>(name, convertOffset, convertFactor, min, max, step) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812Adc::Amc7812Adc(const std::string& name, float convertOffset,
		float convertFactor, float min, float max, float step) :
	Amc7812Profile(name, "ADC", convertOffset, convertFactor, min, max, step)
{
	setProfile(Amc7812Profile::profileSaw) ;
}

//-------------------------------------------------------------------------------------------------------------
Amc7812Adc::~Amc7812Adc()
{
}
