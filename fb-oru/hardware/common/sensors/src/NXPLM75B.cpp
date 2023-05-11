/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NXPLM75B.cpp
 * \brief     Digital temperature sensor driver
 *
 *
 * \details   Temperature sensor driver for NXP LM75B chip
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NXPLM75B.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned NXPLM75B::ADDR_WIDTH(8) ;
const unsigned NXPLM75B::DATA_WIDTH(16) ;
const unsigned NXPLM75B::ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value
const uint8_t NXPLM75B::TEMPERATURE_REG_ADDR(0);
const uint16_t NXPLM75B::TEMPERATURE_DATA_MASK(0x7FF);
const uint16_t NXPLM75B::TEMPERATURE_SHIFT(5);
const uint16_t NXPLM75B::TEMPERATURE_SIGN_BIT_MASK(0x400);
const unsigned NXPLM75B::MAX_FAIL(5) ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NXPLM75B::NXPLM75B(std::shared_ptr<II2cBus> i2c, const std::string& name) :
	RegDriver(name, i2c, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mI2c(i2c),
	mMutex(),
	mEnable(true),
	mFailCount(0)
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State NXPLM75B::initialise(void)
{
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
const Temperature NXPLM75B::getTemperature( void )
{
	Mutex::Lock lock(mMutex) ;

	if (!mEnable)
		return Temperature(0.0) ;

	std::vector<IBus::BusCommand> commands ;
    std::vector<IBus::BusCommand> readback ;

    commands.push_back(IBus::BusCommand(IBus::BUS_READ_SHORT, TEMPERATURE_REG_ADDR)) ;

	/// Executes the list of commands as an atomic set
	if (!mI2c->commandsList(commands, readback))
	{
		++mFailCount ;
		std::cerr << "NXPLM75B::ERROR " << mI2c->error() << " [" << mFailCount << "]" << std::endl ;
		if (mFailCount >= MAX_FAIL)
		{
			mEnable = false ;
			std::cerr << "NXPLM75B::DISABLED" << std::endl ;
		}

		return Temperature(0.0) ;
	}

    Temperature val(0.0);
	if (readback.size() == 1 && readback[0].type() == IBus::BUS_READ_SHORT &&
			readback[0].offset() == TEMPERATURE_REG_ADDR)
	{
		/// Swap the received bytes to get the temperature raw data
		uint8_t lowerByte = (readback[0].data16() & 0xFF00) >> 8;
		uint8_t upperByte = (readback[0].data16() & 0xFF);

		uint16_t data = (((uint16_t)upperByte << 8) | lowerByte);

		/// Read the temperature register and use the 11 MSBs
		data = (data >> TEMPERATURE_SHIFT) & TEMPERATURE_DATA_MASK;

		/// Check it the temperature is negative
		if (data & TEMPERATURE_SIGN_BIT_MASK)
		{
			/// Extend sign bit
			data |= (0xFFFF & (~TEMPERATURE_DATA_MASK));
			/// Calculate 2s compliment
			data = (~data) + 1;
			/// Multiply by the temperature sensor slope
			val = (float)(data * -0.125);
		}
		else
		{
			/// Multiply by the temperature sensor slope
			val = (float)(data * 0.125);
		}
	}

    return val;
}

//-------------------------------------------------------------------------------------------------------------
void NXPLM75B::show(std::ostream& ss)
{
	std::shared_ptr<IRegModel> reg = regModel();
	unsigned deviceWidth(reg->addressWidth() + reg->dataWidth()) ;
	unsigned formatWidth( (deviceWidth+3) / 4 ) ;

	bool regSet(false) ;
	ss << "'" << getName() << "' Registers" << std::endl ;
	std::vector<uint32_t> regs(reg->deviceValues()) ;
	for (unsigned i=0; i < regs.size(); ++i)
	{
		if (!reg->regIsSet(i))
		{
			continue ;
		}

		ss << "R" << std::setw(3) << std::setfill(' ') << std::left << i << " 0x" <<
			std::hex << std::right << std::setfill('0') << std::setw(formatWidth) << regs[i] << std::dec << std::endl ;
		regSet = true ;
	}
	if (!regSet)
	{
		ss << ">> No registers set <<" << std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void NXPLM75B::show(void)
{
	show(std::cout);
}
