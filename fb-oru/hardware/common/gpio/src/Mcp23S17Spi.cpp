/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mcp23S17Spi.cpp
 * \brief     GPIO expander
 *
 *
 * \details   GPIO expander that is configured via the SPI bus
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "MCP23S17.h"
#include "Mcp23S17Spi.h"
#include "Mcp23S17RegModel.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned Mcp23S17Spi::ADDR_WIDTH(8) ;
const unsigned Mcp23S17Spi::DATA_WIDTH(8) ;
const unsigned Mcp23S17Spi::ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mcp23S17Spi::Mcp23S17Spi(std::shared_ptr<ISpiBus> spi, const std::string& name) :
	RegDriver(name, spi, std::make_shared<Mcp23S17RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mSpi(spi),
	mMutex(),
	mPortValues(),
	mPortDir()
{
	// Port A = 0
	mPortValues.push_back(0);
	mPortDir.push_back(0xFF);
	// Port B = 0
	mPortValues.push_back(0);
	mPortDir.push_back(0xFF);
}

//-------------------------------------------------------------------------------------------------------------
Mcp23S17Spi::~Mcp23S17Spi()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mcp23S17Spi::initialise(void)
{
	std::cerr << "Mcp23S17Spi::initialise" << std::endl ;

	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    /// write regs
    std::vector< std::pair<uint32_t, uint32_t> > initData;

    ReturnType::State rc = regData()->getRegisterData(getName(), initData);
    if (rc != ReturnType::RT_OK)
    {
    	return rc ;
    }

	for (auto& regval : initData)
	{
		// Update member variables containing port values

		switch (regval.first & 0xFF)
		{
		case MCP23S17::GPIOA:
			mPortValues[0] = (regval.second & 0xFF);
			break;

		case MCP23S17::GPIOB:
			mPortValues[1] = (regval.second & 0xFF);
			break;

		case MCP23S17::IODIRA:
			mPortDir[0] = (regval.second & 0xFF);
			break;

		case MCP23S17::IODIRB:
			mPortDir[1] = (regval.second & 0xFF);
			break;

		default:
			break;
		}

		uint16_t reg = (uint16_t)(((regval.first & 0xFF) << 8) | MCP23S17::WR_Opcode); // reg address appended by the Write opcode
		uint8_t val = (uint8_t)(regval.second); // reg value

    	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, val)) ;
	}

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		return ReturnType::RT_OK ;
	}

    std::cerr << "Mcp23S17Spi::ERROR " << mSpi->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
void Mcp23S17Spi::show(std::ostream& ss)
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
void Mcp23S17Spi::show(void)
{
	show(std::cout);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mcp23S17Spi::setDirection( int port, UINT8 dir, UINT8 mask )
{
	if (port < 0 || port > 1)
	{
		std::cerr << "Mcp23S17Spi::write8BitPort - Port value invalid" << std::endl;
		return ReturnType::RT_OUT_OF_RANGE;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    uint8_t regAddress;
    uint16_t reg;
    uint8_t write_val = 0;

    if (mask != 0xFF)
    {
    	// Change the bits indicated by the mask
    	write_val = ((mPortDir[port] & ~mask) | (dir & mask));
    }
    else
    {
    	write_val = dir & mask;
    }

	/// Write the port
    regAddress = (port == 0 ? MCP23S17::IODIRA : MCP23S17::IODIRB );
	reg = (uint16_t)((regAddress << 8) | MCP23S17::WR_Opcode); // reg address appended by the Write opcode

	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, write_val)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		// Record new value
		mPortDir[port] = write_val;
		return ReturnType::RT_OK ;
	}

	std::cerr << "Mcp23S17Spi::setDirection ERROR " << mSpi->error() << std::endl ;

    return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mcp23S17Spi::write8BitPort( int port, UINT8 value, UINT8 mask)
{
	if (port < 0 || port > 1)
	{
		std::cerr << "Mcp23S17Spi::write8BitPort - Port value invalid" << std::endl;
		return ReturnType::RT_OUT_OF_RANGE;
	}

	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    uint8_t regAddress;
    uint16_t reg;
    uint8_t write_val = 0;

    if (mask != 0xFF)
    {
    	// Change the bits indicated by the mask
    	write_val = ((mPortValues[port] & ~mask) | (value & mask));
    }
    else
    {
    	write_val = value & mask;
    }

	/// Write the port
    regAddress = (port == 0 ? MCP23S17::GPIOA : MCP23S17::GPIOB );
	reg = (uint16_t)((regAddress << 8) | MCP23S17::WR_Opcode); // reg address appended by the Write opcode

	commands.clear();
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, write_val)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		// Record new value
		mPortValues[port] = write_val;
		return ReturnType::RT_OK ;
	}

	std::cerr << "Mcp23S17Spi::write8BitPort ERROR " << mSpi->error() << std::endl ;

    return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Mcp23S17Spi::read8BitPort( int port, UINT8 &value )
{
	/// Protect the method with a mutex
	std::lock_guard<std::mutex> lock(mMutex);

	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;
    std::vector<IBus::BusCommand> readback ;

    uint8_t regAddress;
    uint16_t reg;

    regAddress = (port == 0 ? MCP23S17::GPIOA : MCP23S17::GPIOB) ;
	reg = (uint16_t)((regAddress << 8) | MCP23S17::RD_Opcode); // reg address appended by the read opcode

	commands.push_back(IBus::BusCommand(IBus::BUS_READ_BYTE, reg)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands, readback))
	{
		/// Read the port value
		if (readback.size() == 1 && readback[0].type() == IBus::BUS_READ_BYTE &&
			readback[0].offset() == reg)
		{
			value = readback[0].data8();

			return ReturnType::RT_OK ;
		}
	}

	std::cerr << "Mcp23S17Spi::read8BitPort ERROR " << mSpi->error() <<
    		", Readback size = " << (unsigned)(readback.size()) <<
			", Readback type = " << (unsigned)(readback[0].type()) <<
			", Readback offset = " << (unsigned)(readback[0].offset()) << std::endl ;

    return ReturnType::RT_OPERATION_FAILED;
}
