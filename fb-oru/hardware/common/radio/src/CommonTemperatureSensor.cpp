/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTemperatureSensor.cpp
 * \brief     A file to contain the common implementation of a generic temperature sensor.
 *
 *
 * \details   This file defines the common implementation of a generic temperature sensor
 *            and expands on it if necessary.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// Includes go here, before the namespace
#include "CommonTemperatureSensor.h"
#include <iostream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================
//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonTemperatureSensor::CommonTemperatureSensor(std::shared_ptr<ITemperatureSensorDriver> driver, int index, const std::string& name):
	Device( Device::TEMPERATURE_SENSOR, index, name ),
	mDriver( driver )
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonTemperatureSensor::~CommonTemperatureSensor()
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonTemperatureSensor::doInit()
{
	ReturnType::State rc = mDriver->initialise();

    setInitResult(rc);
    std::string str = getName() + " Init" + ReturnType::getState(rc);
    setInitResultString(str);
    return rc;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
const Temperature Mplane::CommonTemperatureSensor::getTemperature( void )
{
	return mDriver->getTemperature();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void CommonTemperatureSensor::show(std::ostream& os)
{
	os << "Temperature sensor device : " << getName() << std::endl;
	mDriver->show(os);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonTemperatureSensor::show(void)
{
	show(std::cout);
}
