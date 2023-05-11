/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonGpio.cpp
 * \brief     Implementation of the CommonGpio class
 *
 *
 * \details   This file contains the implementation of the hardware gpio
 *            CommonGpio class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "CommonGpio.h"
#include "IGpioKernel.h"

using namespace Mplane;

////=============================================================================================================
//// SINGLETON
////=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CommonGpio> CommonGpio::getInstance(void)
{
    static std::shared_ptr<CommonGpio> instance(new CommonGpio() ) ;
    return instance;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

CommonGpio::CommonGpio() :
	CommonGpioRegs(),
	mInitComplete(false)
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonGpio::initialise(void)
{
    if (mInitComplete)
    {
        /*! \TODO - add init trace here to indicate a false entry, should not
         * call it more than once.
         */

        // already initialised, so early exit, nothing to do
        return ReturnType::RT_ALREADY_INITIALISED;
    }

    /*! \TODO - add init trace here to indicate CommonGpio init complete */

    mInitComplete = true;


    // Initialise the kernel device driver interface
    IGpioKernel::getInstance()->initialise() ;

    return ReturnType::RT_OK;
}


//-------------------------------------------------------------------------------------------------------------
UINT32 CommonGpio::readRegister(unsigned offset)
{
	UINT32 value = 0 ;
	this->CommonGpioRegs::device->read(offset, &value, 0xffffffff);
	return value ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonGpio::writeRegister(unsigned offset, UINT32 value)
{
	this->CommonGpioRegs::device->write(offset, value, 0xffff);
}

//-------------------------------------------------------------------------------------------------------------
void CommonGpio::modifyRegister(unsigned offset, UINT32 value, UINT32 mask)
{
	this->CommonGpioRegs::device->write(offset, value, mask);
}

//-------------------------------------------------------------------------------------------------------------
void CommonGpio::setOutput(unsigned int pin)
{
	if (pin < PPC_MAX_GPIO_PINS)
	{
		//GPIO NOT configured as open drain driver
		device->wr_field(GPIO_REG_OPEN_DRAIN_ADDR, 0, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
		//GPIO NOT in a high impedance state
		device->wr_field(GPIO_REG_THREE_STATE_CONTROL_ADDR, 1, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
		//GPIO output set
		device->wr_field(GPIO_REG_OUTPUT_ADDR, 1, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
	}
}

//-------------------------------------------------------------------------------------------------------------
void CommonGpio::resetOutput(unsigned int pin)
{
	if (pin < PPC_MAX_GPIO_PINS)
	{
		//GPIO NOT configured as open drain driver
		device->wr_field(GPIO_REG_OPEN_DRAIN_ADDR, 0, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
		//GPIO NOT in a high impedance state
		device->wr_field(GPIO_REG_THREE_STATE_CONTROL_ADDR, 1, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
		//GPIO output reset
		device->wr_field(GPIO_REG_OUTPUT_ADDR, 0, 0x00000001, (PPC_MAX_GPIO_PINS - pin - 1));
	}
}
