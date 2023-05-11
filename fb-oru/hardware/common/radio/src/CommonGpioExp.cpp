/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpioExp.cpp
 * \brief     Implementation of the CommonGpioExp class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonGpioExp class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// Includes go here, before the namespace
#include "CommonGpioExp.h"
#include <iostream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonGpioExp::CommonGpioExp(std::shared_ptr<IGpioExpDriver> driver, int index, const char* name):
       Device(Device::EXP, index, name ),
	   mDriver(driver)
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonGpioExp::~CommonGpioExp()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonGpioExp::doInit()
{
	ReturnType::State rc = mDriver->initialise();

    setInitResult(rc);
    std::string str = getName() + " Init" + ReturnType::getState(rc);
    setInitResultString(str);
    return rc;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
void CommonGpioExp::show(std::ostream& os)
{
	os << "GPIO Expander device : " << getName() << std::endl;
	mDriver->show(os);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonGpioExp::show(void)
{
	show(std::cout);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonGpioExp::setDirection( int port, UINT8 dir, UINT8 mask )
{
	return mDriver->setDirection(port, dir, mask);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonGpioExp::write8BitPort( int port, UINT8 value, UINT8 mask )
{
    return mDriver->write8BitPort(port, value, mask);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonGpioExp::read8BitPort( int port, UINT8& value )
{
	return mDriver->read8BitPort(port, value);
}
