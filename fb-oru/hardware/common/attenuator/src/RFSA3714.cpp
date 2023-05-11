/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RFSA3714.cpp
 * \brief     Class representing the RFSA3714 attenuator device
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <math.h>

#include "RFSA3714.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned ADDR_WIDTH(8) ;
const unsigned DATA_WIDTH(8) ;
const unsigned ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RFSA3714::RFSA3714(std::shared_ptr<ISpiBus> spi, const std::string& name, const Power& minAtten, const Power& maxAtten) :
	RegDriver(name, spi, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mSpi(spi),
	mMinAttenuation(minAtten),
	mMaxAttenuation(maxAtten)
{
}

//-------------------------------------------------------------------------------------------------------------
RFSA3714::~RFSA3714()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RFSA3714::initialise(void)
{
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void RFSA3714::show(std::ostream& ss)
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
void RFSA3714::show(void)
{
	show(std::cout);
}

//-------------------------------------------------------------------------------------------------------------
Power RFSA3714::getMaxAttenuation(void)
{
    return mMaxAttenuation;
}

//-------------------------------------------------------------------------------------------------------------
Power RFSA3714::getMinAttenuation(void)
{
    return mMinAttenuation;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RFSA3714::applyAttenuation(unsigned int control)
{
	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    uint8_t reg = 0;
	uint8_t value = control;

	/// Write the attenuation control value to the peripheral
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_BYTE, reg, value)) ;

	/// Executes the list of commands as an atomic set
	if (mSpi->commandsList(commands))
	{
		return ReturnType::RT_OK;
	}

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
unsigned int RFSA3714::calcControl(Power requestedAtten)
{
	// RFSA3714 uses 7-bit value
	// 0.0 - 31.75 float converts to 7-bit 0-127 value so multiply by 4
	// Entering > 31.75 does not set the attenuator value and returns RT_ERROR
	float wrData = requestedAtten.get() * 4.0;
	UINT8 control = ((UINT8)(wrData - floor(wrData) > 0.5 ? ceil(wrData) : floor(wrData)));

	return static_cast<unsigned int>(control);
}

//-------------------------------------------------------------------------------------------------------------
unsigned int RFSA3714::calcControl(Power requestedAtten, Temperature temp)
{
	return calcControl(requestedAtten);
}

//-------------------------------------------------------------------------------------------------------------
Power RFSA3714::calcAttenuation(unsigned int control)
{
	// Convert back from control value in 0.25 dB steps
	Power atten(0.25 * static_cast<float>(control)) ;
	return atten ;
}
