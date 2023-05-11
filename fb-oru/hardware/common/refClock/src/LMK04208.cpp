/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LMK04208.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "LMK04208.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned LMK04208::ADDR_WIDTH(5) ;
const unsigned LMK04208::DATA_WIDTH(27) ;
const unsigned LMK04208::ADDR_LSB(0) ;
const bool LMK04208::USE_RW(false) ;
const unsigned LMK04208::RW_BIT(0) ;

const unsigned LMK04208::ADDR_MSB(ADDR_LSB + ADDR_WIDTH - 1) ;
const unsigned LMK04208::SR_SIZE(ADDR_WIDTH + DATA_WIDTH) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LMK04208::LMK04208(std::shared_ptr<ISpiBus> spi, const std::string& name) :
	RegDriver(name, spi, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mSpi(spi)
{
	///  This device has a 32bit shift register; MS bit first; Address bits are 4:0; no R/W bit
    mSpi->setDeviceSettings(SR_SIZE, ADDR_MSB,ADDR_LSB, USE_RW,RW_BIT) ;
}

//-------------------------------------------------------------------------------------------------------------
LMK04208::~LMK04208()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State LMK04208::initialise(void)
{
	std::cerr << "LMK04208::initialise" << std::endl ;

    std::vector<IBus::BusCommand> commands ;

    ///  write regs
    std::vector<uint32_t> initData;

    ReturnType::State rc = regData()->getRegisterData(getName(), initData);
    if (rc != ReturnType::RT_OK)
    {
    	return rc ;
    }


	for (auto& regval : initData)
	{
        uint32_t reg(regval & 0x1f);
    	regval >>= 5 ;

    	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_WORD, reg, regval)) ;
        commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;
	}

	///  Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		return ReturnType::RT_OK ;
	}

    std::cerr << "LMK04208::ERROR " << mSpi->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::LMK04208::isPllLocked(void)
{
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void LMK04208::show(std::ostream& ss)
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
void LMK04208::show(void)
{
	show(std::cout);
}
