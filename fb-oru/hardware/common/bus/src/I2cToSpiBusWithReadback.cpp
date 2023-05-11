/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cToSpiBusWithReadback.cpp
 * \brief     An I2cToSpi bus with readout using GPIO expander
 *
 *
 * \details   An I2cToSpi bus with readout using GPIO expander
 *
 */

#include <iostream>
#include "ByteTransfer.hpp"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>

#include "BusLock.hpp"
#include "I2cToSpiBusWithReadback.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
I2cToSpiBusWithReadback::I2cToSpiBusWithReadback(std::shared_ptr<IGpioExp> gpioExp,
		unsigned gpioExpPort, unsigned gpioExpVal, unsigned gpioExpMask,
		std::shared_ptr<II2cBus> i2c,
		std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) :
	I2cToSpiBus(i2c, busSettings, spiSelect),
	mGpioExp(gpioExp),
	mGpioExpPort(gpioExpPort),
	mGpioExpValue(gpioExpVal),
	mGpioExpMask(gpioExpMask)
{
}

//-------------------------------------------------------------------------------------------------------------
I2cToSpiBusWithReadback::~I2cToSpiBusWithReadback()
{
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBusWithReadback::doReadByte(uint32_t offset, uint8_t &byte)
{
	// Set the select lines before doing a read
	if (mGpioExp->setDirection(mGpioExpPort, ~(mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	if (mGpioExp->write8BitPort(mGpioExpPort, (mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	return I2cToSpiBus::doReadByte(offset, byte) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBusWithReadback::doReadShort(uint32_t offset, uint16_t &shortVal)
{
	// Set the select lines before doing a read
	if (mGpioExp->setDirection(mGpioExpPort, ~(mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	if (mGpioExp->write8BitPort(mGpioExpPort, (mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	return I2cToSpiBus::doReadShort(offset, shortVal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool I2cToSpiBusWithReadback::doReadWord(uint32_t offset, uint32_t &word)
{
	// Set the select lines before doing a read
	if (mGpioExp->setDirection(mGpioExpPort, ~(mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	if (mGpioExp->write8BitPort(mGpioExpPort, (mGpioExpValue & 0xFF), (mGpioExpMask & 0xFF)) != ReturnType::RT_OK)
	{
		return false;
	}

	return I2cToSpiBus::doReadWord(offset, word) ;
}
