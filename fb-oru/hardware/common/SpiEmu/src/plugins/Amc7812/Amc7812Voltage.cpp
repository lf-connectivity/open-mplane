/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Voltage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "Amc7812Voltage.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAmc7812Handler> Amc7812Voltage::factory(const std::string& name,
		float convertOffset, float convertFactor,
		float minVoltage, float maxVoltage, float step)
{
	return std::make_shared<Amc7812Voltage>(name, convertOffset, convertFactor, minVoltage, maxVoltage, step) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812Voltage::Amc7812Voltage(const std::string& name,
		float convertOffset, float convertFactor,
		float minVoltage, float maxVoltage, float step) :
	Amc7812Profile(name, "Voltage", convertOffset, convertFactor, minVoltage, maxVoltage, step)
{
	setProfile(Amc7812Profile::profileSaw) ;
}

//-------------------------------------------------------------------------------------------------------------
Amc7812Voltage::~Amc7812Voltage()
{
}
