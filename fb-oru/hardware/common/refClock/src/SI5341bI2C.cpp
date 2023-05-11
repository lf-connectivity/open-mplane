/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SI5341bI2C.cpp
 * \brief     Ultra Low Jitter, Any-Frequency, Any Output Clock Generator, Revision D
 *
 *
 * \details   Clock Generator that is configured via the I2C bus
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SI5341bI2C.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const unsigned SI5341bI2C::ADDR_WIDTH(8) ;
const unsigned SI5341bI2C::DATA_WIDTH(8) ;
const unsigned SI5341bI2C::ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value
const unsigned SI5341bI2C::PAGE_BITS(8) ;
const unsigned SI5341bI2C::PAGE_REG_OFFSET(1);

const std::vector< std::pair<uint32_t, uint32_t> > SI5341bI2C::mPreamble =
{
	{ 0x0B24, 0xC0 },
	{ 0x0B25, 0x00 },
	{ 0x0502, 0x01 },
	{ 0x0505, 0x03 },
	{ 0x0957, 0x17 },
	{ 0x0B4E, 0x1A },
};

const std::vector< std::pair<uint32_t, uint32_t> > SI5341bI2C::mPostamble =
{
	{ 0x001C, 0x01 },
	{ 0x0B24, 0xC3 },
	{ 0x0B25, 0x02 }
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SI5341bI2C::SI5341bI2C(std::shared_ptr<II2cBus> i2c, const std::string& name) :
	RegDriver(name, i2c, std::make_shared<PagedRegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB, PAGE_BITS, PAGE_REG_OFFSET)),
	mI2c(i2c),
	mCurrentPage(0)
{
}

//-------------------------------------------------------------------------------------------------------------
SI5341bI2C::~SI5341bI2C()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State SI5341bI2C::initialise(void)
{
	std::cerr << "SI5341bI2C::initialise" << std::endl ;

	/// Build the command set
    std::vector<IBus::BusCommand> commands ;

    /// Write the preamble
	for (auto& regval : mPreamble)
	{
		uint16_t reg = (uint16_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

		appendWriteCommand(reg, val, commands) ;
	}

    /// After writing the preamble, wait for 300 ms
    commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 300)) ;

    /// write regs
    std::vector< std::pair<uint32_t, uint32_t> > initData;

    ReturnType::State rc = regData()->getRegisterData(getName(), initData);
    if (rc != ReturnType::RT_OK)
    {
    	return rc ;
    }

	for (auto& regval : initData)
	{
		uint16_t reg = (uint16_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

		appendWriteCommand(reg, val, commands) ;
	}

	/// Write the postamble
	for (auto& regval : mPostamble)
	{
		uint16_t reg = (uint16_t)(regval.first) ; // reg
		uint8_t val = (uint8_t)(regval.second); // reg value

		appendWriteCommand(reg, val, commands) ;
	}


	/// Executes the list of commands as an atomic set
	if (mI2c->commandsList(commands))
	{
		return ReturnType::RT_OK;
	}


    std::cerr << "SI5341bI2C::ERROR " << mI2c->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::SI5341bI2C::isPllLocked(void)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void SI5341bI2C::show(std::ostream& ss)
{
	std::shared_ptr<IRegModel> reg = regModel();
	unsigned deviceWidth(reg->addressWidth() + reg->dataWidth()) ;
	unsigned formatWidth( (deviceWidth+3) / 4 ) ;

	bool regSet(false) ;
	ss << "'" << getName() << "' Registers" << std::endl ;

	std::vector<uint32_t> regs;
	for (unsigned page=0; page < 0x0B; ++page)
	{
		reg->setReadPage(page);
		regs = reg->deviceValues() ;
		for (unsigned i=0; i < regs.size(); ++i)
		{
			if (!reg->regIsSet(i))
			{
				continue ;
			}

			ss << "R" << std::setw(4) << std::setfill(' ') << std::left << (page << 8 | i) << " 0x" <<
				std::hex << std::right << std::setfill('0') << std::setw(formatWidth) << regs[i] << std::dec << std::endl ;
			regSet = true ;
		}
	}

	if (!regSet)
	{
		ss << ">> No registers set <<" << std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void SI5341bI2C::show(void)
{
	show(std::cout);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void SI5341bI2C::appendWriteCommand(uint16_t address, uint8_t data,
		std::vector<IBus::BusCommand>& commands)
{
	uint8_t page = (address & 0xFF00) >> 8;
	if (page != mCurrentPage)
	{
		/// Change the page number
		commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, 1, page)) ;
		/// Set the current page
		mCurrentPage = page;
	}

	uint8_t regAddr = (uint8_t)(address & 0xFF);
	/// Add the register write into the command vector
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, regAddr, data)) ;
}
