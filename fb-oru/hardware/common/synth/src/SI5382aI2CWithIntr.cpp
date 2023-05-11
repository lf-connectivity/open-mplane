/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI5382aI2CWithIntr.cpp
 * \brief     SI5382a I2C driver with interrupt pin access
 *
 *
 * \details   SI5382a I2C driver with interrupt pin access
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SI5382aI2CWithIntr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SI5382aI2CWithIntr::SI5382aI2CWithIntr(std::shared_ptr<IGpioExp> gpioExp,
		unsigned gpioExpPort, unsigned gpioExpBitIndex,
		std::shared_ptr<II2cBus> i2c, const std::string& name) :
	SI5382aI2C(i2c, name),
	mGpioExp(gpioExp),
	mGpioExpPort(gpioExpPort),
	mGpioExpBitIndex(gpioExpBitIndex)
{
}

//-------------------------------------------------------------------------------------------------------------
bool SI5382aI2CWithIntr::isPllLocked(void)
{
	// Read SFP28_SI5328_INT_ALM line using the GPIO expander. If it is set, then clear sticky bits in status registers (Page 0, 0x0B-0x15)
	if (mGpioExp->setDirection(mGpioExpPort, (1u << mGpioExpBitIndex), (1u << mGpioExpBitIndex)) != ReturnType::RT_OK)
	{
		return false;
	}

	uint8_t value;
	if (mGpioExp->read8BitPort(mGpioExpPort, value) != ReturnType::RT_OK)
	{
		return false;
	}

	// If alarm bit is 0, then PLL is not locked
	if ((value & (1u << mGpioExpBitIndex)) == 0)
	{
		std::vector<IBus::BusCommand> commands ;

		// Clear sticky bits in status registers
		uint16_t writeAddress = STATUS_REG_START_ADDR;
        uint8_t page = (writeAddress & 0xFF00) >> 8;

        commands.clear();

    	/// Change the page number
    	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 1, page)) ;

    	// Write the device status flags that have sticky bits
    	uint8_t writeRegAddr = (uint8_t)(writeAddress & 0xFF);
    	std::vector<uint8_t> writeBytes(NUM_STATUS_REGS, 0);

		commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_DATA_OFFSET, writeRegAddr, writeBytes)) ;

		///  Executes the list of commands as an atomic set
		mI2c->commandsList(commands);

		return false;
	}

	return true;
}
