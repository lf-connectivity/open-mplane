/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LMX2594.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LMX2594.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned LMX2594::ADDR_WIDTH(7) ;
const unsigned LMX2594::DATA_WIDTH(16) ;
const unsigned LMX2594::ADDR_LSB(16) ;
const bool LMX2594::USE_RW(true) ;
const unsigned LMX2594::RW_BIT(23) ;

const unsigned LMX2594::ADDR_MSB(ADDR_LSB + ADDR_WIDTH - 1) ;
const unsigned LMX2594::SR_SIZE(ADDR_WIDTH + DATA_WIDTH + 1) ;
const unsigned LMX2594::PLL_LOCK_REGISTER(110);
const unsigned LMX2594::RB_LD_VTUNE_MASK(0x0600);
const unsigned LMX2594::RB_LD_VTUNE_SHIFT(9);
const unsigned LMX2594::RB_LD_VTUNE_LOCKED(2);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LMX2594::LMX2594(std::shared_ptr<ISpiBus> spi, const std::string& name) :
	RegDriver(name, spi, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mSpi(spi)
{
	// This device has a 24bit shift register; MS bit first; Address bits are 22:16; R/W bit is 23
    mSpi->setDeviceSettings(SR_SIZE, ADDR_MSB,ADDR_LSB, USE_RW,RW_BIT) ;
}

//-------------------------------------------------------------------------------------------------------------
LMX2594::~LMX2594()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State LMX2594::initialise( void )
{

	std::cerr << "LMX2594::initialise" << std::endl ;

	/// Build the command set
    std::vector<IBus::BusCommand> commands ;

    commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 2)) ; // RO RESET=1
    commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;

    commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, 0, 0)) ; // RO RESET=0
    commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;

    /// write regs
    std::vector<uint32_t> initData;

    ReturnType::State rc = regData()->getRegisterData(getName(), initData);
    if (rc != ReturnType::RT_OK)
    {
    	return rc ;
    }

	for (auto& regval : initData)
	{
		uint8_t reg = (uint8_t)((regval >> 16) & 0xff) ; // reg
		uint16_t val = (uint16_t)(regval & 0xffff); // reg value

		commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, reg, val)) ;
		commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;
	}

	/// R0 with FCAL_EN = 1
	uint32_t r0(initData[initData.size()-1]) ;

	uint8_t reg = (uint8_t)((r0 >> 16) & 0xff) ; // reg
	uint16_t val = (uint16_t)(r0 & 0xffff); // reg value

	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, reg, val)) ;
	commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		return ReturnType::RT_OK;
	}

    std::cerr << "LMX2594::ERROR " << mSpi->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::LMX2594::isPllLocked(void)
{
	// Read register 110, field rb_LD_VTune to determine PLL lock status
    std::vector<IBus::BusCommand> commands ;
    std::vector<IBus::BusCommand> readback ;

    commands.push_back(IBus::BusCommand(IBus::BUS_READ_SHORT, PLL_LOCK_REGISTER)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands, readback))
	{
		if (readback.size() == 1 && readback[0].type() == IBus::BUS_READ_SHORT &&
				readback[0].offset() == PLL_LOCK_REGISTER)
		{
			unsigned rb_LD_Vtune = (readback[0].data16() & RB_LD_VTUNE_MASK) >> RB_LD_VTUNE_SHIFT;
			if (rb_LD_Vtune == RB_LD_VTUNE_LOCKED)
			{
				return true;
			}
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
void LMX2594::show(std::ostream& ss)
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

	ss << "PLL status : " << ((isPllLocked() == true) ? "Locked" : "Not locked") << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
void LMX2594::show(void)
{
	show(std::cout);
}
