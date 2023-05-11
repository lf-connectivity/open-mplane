/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tca6416aGpio.cpp
 * \brief     GPIO expander
 *
 *
 * \details   GPIO expander that is configured via the Gpio control interface
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Tca6416a.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Tca6416aGpio.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Tca6416aGpio::Tca6416aGpio(std::shared_ptr<IGpioControl> gpio, const std::string& name) :
	Driver(name),
	mGpio(gpio),
	mMutex()
{
}

//-------------------------------------------------------------------------------------------------------------
Tca6416aGpio::~Tca6416aGpio()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Tca6416aGpio::initialise(void)
{
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void Tca6416aGpio::show(std::ostream& ss)
{
	ss << getName() << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void Tca6416aGpio::show(void)
{
	show(std::cout);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Tca6416aGpio::setDirection( int port, UINT8 dir, UINT8 mask )
{
	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Find the index for the first pin on the port
	unsigned base_pin = (port * 8);

	// Go through all pins on the port
	for (unsigned index = 0; index < 8; index++)
	{
		// Check if the mask bit is set for this pin
		if (mask & (1u << index))
		{
			// Calculate the pin index with base 0
			unsigned pin = base_pin + index;

			// Write the pin direction
			if (mGpio->setDirection(pin,
					((dir & (1 << index)) != 0) ? IGpioControl::GpioDirection::DIR_IN : IGpioControl::GpioDirection::DIR_OUT) == false)
			{
				return ReturnType::RT_ERROR;
			}
		}
	}

	return ReturnType::RT_OK;

}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Tca6416aGpio::write8BitPort( int port, UINT8 value, UINT8 mask)
{
	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Find the index for the first pin on the port
	unsigned base_pin = (port * 8);

	// Go through all pins on the port
	for (unsigned index = 0; index < 8; index++)
	{
		// Check if the mask bit is set for this pin
		if (mask & (1u << index))
		{
			// Calculate the pin index with base 0
			unsigned pin = base_pin + index;

			// Write the pin value
			if (mGpio->setValue(pin, ((value & (1 << index)) != 0)) == false)
			{
				return ReturnType::RT_ERROR;
			}
		}
	}

	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Tca6416aGpio::read8BitPort( int port, UINT8 &value )
{
	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	// Find the index for the first pin on the port
	unsigned base_pin = (port * 8);

	// Go through all pins on the port
	for (int index = 0; index < 8; index++)
	{
		// Calculate the pin index with base 0
		unsigned pin = base_pin + index;

		int readVal = 0;

		// Write the pin value
		if (mGpio->getValue(pin, readVal) == false)
		{
			return ReturnType::RT_ERROR;
		}

		// Update the pin value in the return variable
		if (readVal == 0)
		{
			value &= (~(1 << index));
		}
		else
		{
			value |= (1 << index);
		}
	}

	return ReturnType::RT_OK;
}
