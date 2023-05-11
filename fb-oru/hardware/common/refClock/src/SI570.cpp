/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI570.cpp
 * \brief     Programmable clock source
 *
 *
 * \details   Programmable clock source that is configured via the I2C bus
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SI570.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned SI570::ADDR_WIDTH(8) ;
const unsigned SI570::DATA_WIDTH(8) ;
const unsigned SI570::ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value

/// Freeze the DCO by setting Freeze DCO = 1 (bit 4 of register 137).
const std::vector< std::pair<uint32_t, uint32_t> > SI570::mPreamble =
{
	{ 137, 0x10 }
};

/// Unfreeze the DCO by setting Freeze DCO = 0 and assert
/// the NewFreq bit (bit 6 of register 135)
const std::vector< std::pair<uint32_t, uint32_t> > SI570::mPostamble =
{
	{ 137, 0x00 },
	{ 135, 0x40 }
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SI570::SI570(std::shared_ptr<II2cBus> i2c, const std::string& name) :
	RegDriver(name, i2c, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mI2c(i2c)
{
}

//-------------------------------------------------------------------------------------------------------------
SI570::~SI570()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State SI570::initialise(void)
{

	std::cerr << "SI570::initialise" << std::endl ;

	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    /// Write the preamble
	for (auto& regval : mPreamble)
	{
		uint8_t reg = (uint8_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

		commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, val)) ;
	}

    /// write regs
    std::vector< std::pair<uint32_t, uint32_t> > initData;

    ReturnType::State rc = regData()->getRegisterData(getName(), initData);
    if (rc != ReturnType::RT_OK)
    {
    	return rc ;
    }

	for (auto& regval : initData)
	{
		uint8_t reg = (uint8_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

    	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, val)) ;
	}

    /// Write the postamble
	for (auto& regval : mPostamble)
	{
		uint8_t reg = (uint8_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

		commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, val)) ;
	}

	/// Executes the list of commands as an atomic set
	if (mI2c->commandsList(commands))
	{
		return ReturnType::RT_OK ;
	}

    std::cerr << "SI570::ERROR " << mI2c->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::SI570::isPllLocked(void)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void SI570::show(std::ostream& ss)
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
void SI570::show(void)
{
	show(std::cout);
}
