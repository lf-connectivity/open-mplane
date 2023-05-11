/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812Temperature.cpp
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
#include "Amc7812Temperature.h"

using namespace Mplane;

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAmc7812Handler> Amc7812Temperature::factory(const std::string& name,
		float convertOffset, float convertFactor,
		float startTemp, float endTemp, float step)
{
	return std::make_shared<Amc7812Temperature>(name, convertOffset, convertFactor, startTemp, endTemp, step) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812Temperature::Amc7812Temperature(const std::string& name,
		float convertOffset, float convertFactor,
		float startTemp, float endTemp, float step) :
	Amc7812Profile(name, "Temperature", convertOffset, convertFactor, startTemp, endTemp, step)
{
	setProfile(Amc7812Profile::profileRampUp) ;
}

//-------------------------------------------------------------------------------------------------------------
Amc7812Temperature::~Amc7812Temperature()
{
}
