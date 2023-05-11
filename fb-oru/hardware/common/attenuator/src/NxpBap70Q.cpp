/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NxpBap70Q.cpp
 * \brief     Class representing the NxpBap70Q attenuator device
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <math.h>
#include <cmath>

#include "NxpBap70Q.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned ADDR_WIDTH(8) ;
const unsigned DATA_WIDTH(14) ;
const unsigned ADDR_LSB(32) ; //The address is not part of the register data, hence setting it to max value

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
NxpBap70Q::NxpBap70Q(std::shared_ptr<IBus> bus, const std::string& name, const Power& minAtten, const Power& maxAtten) :
	RegDriver(name, bus, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mBus(bus),
	mMinAttenuation(minAtten),
	mMaxAttenuation(maxAtten)
{
}

//-------------------------------------------------------------------------------------------------------------
NxpBap70Q::~NxpBap70Q()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State NxpBap70Q::initialise(void)
{
    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
void NxpBap70Q::show(std::ostream& ss)
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
void NxpBap70Q::show(void)
{
	show(std::cout);
}

//-------------------------------------------------------------------------------------------------------------
Power NxpBap70Q::getMaxAttenuation(void)
{
    return mMaxAttenuation;
}

//-------------------------------------------------------------------------------------------------------------
Power NxpBap70Q::getMinAttenuation(void)
{
    return mMinAttenuation;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State NxpBap70Q::applyAttenuation(unsigned int control)
{
	/// Build up the commands
    std::vector<IBus::BusCommand> commands ;

    uint8_t reg = 0;
	uint16_t value = control;

	/// Write the attenuation control value to the peripheral
	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, reg, value)) ;

	/// Executes the list of commands as an atomic set
	if (mBus->commandsList(commands))
	{
		return ReturnType::RT_OK;
	}

	return ReturnType::RT_OPERATION_FAILED;
}

//-------------------------------------------------------------------------------------------------------------
unsigned int NxpBap70Q::calcControl(Power requestedAtten)
{
	// Calculate PWM duty cycle
	double dutyCycle = (68.27 * (pow(10,(requestedAtten.get() * 0.0307)))) +
			(31.73 * pow(10,(requestedAtten.get() * 0.101)));
	float wrData = dutyCycle * 163.83;
	UINT16 control = ((UINT16)(wrData - floor(wrData) > 0.5 ? ceil(wrData) : floor(wrData)));

	return static_cast<unsigned int>(control);
}

//-------------------------------------------------------------------------------------------------------------
unsigned int NxpBap70Q::calcControl(Power requestedAtten, Temperature temp)
{
	return calcControl(requestedAtten);
}

//-------------------------------------------------------------------------------------------------------------
Power NxpBap70Q::calcAttenuation(unsigned int control)
{
	// TODO Convert the control word to attenuation value
	return Power(0.0) ;
}
