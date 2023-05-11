/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ina226.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Ina226.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned ADDR_WIDTH(7) ;
const unsigned DATA_WIDTH(16) ;
const unsigned ADDR_LSB(17) ;
const bool USE_RW(true) ;
const unsigned RW_BIT(16) ;

//-------------------------------------------------------------------------------------------------------------
const unsigned CONFIG_REG(0x40);
const unsigned SHUNT_VOLT_REG(0x41);
const unsigned BUS_VOLT_REG(0x42);
const unsigned POWER_REG(0x43);
const unsigned CURRENT_REG(0x44);
const unsigned CALIBRATION_REG(0x45);

const unsigned CONFIG_REGVAL(0x4127) ;

//-------------------------------------------------------------------------------------------------------------
const float CURRENT_LSB_DENOM( (float)(1<<15)) ;
const float CALIBRATION_NUMERATOR(0.00512) ;
const float POWER_CONST(25.0) ;
const float VOLT_CONST(0.00125) ; // 1.25mV / bit

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Ina226::Ina226(std::shared_ptr<II2cBus> i2c, const std::string &name,
		float maxCurrent, float shuntResistor) :
	RegDriver(name, i2c, std::make_shared<RegModel>(name, ADDR_WIDTH, DATA_WIDTH, ADDR_LSB)),
	mI2c(i2c),
	mMaxCurrent(maxCurrent),
	mShuntResistor(shuntResistor),
	mCurrentLSB(0),
	mCalibration(0)
{
	calcCalibration() ;
}

//-------------------------------------------------------------------------------------------------------------
Ina226::~Ina226()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Ina226::name() const
{
	return getName() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State Ina226::initialise(void)
{
	std::cerr << "INA226::initialise" << std::endl ;

    std::vector<IBus::BusCommand> commands ;

   	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, CONFIG_REG, CONFIG_REGVAL)) ;
    commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;

   	commands.push_back(IBus::BusCommand(IBus::BUS_WRITE_SHORT, CALIBRATION_REG, mCalibration)) ;
    commands.push_back(IBus::BusCommand(IBus::BUS_WAIT_MS, 10)) ;

	///  Executes the list of commands as an atomic set
	if (mI2c->commandsList(commands))
	{
		return ReturnType::RT_OK ;
	}

    std::cerr << "INA226::ERROR " << mI2c->error() << std::endl ;
    return ReturnType::RT_OPERATION_FAILED;

}

//-------------------------------------------------------------------------------------------------------------
float Ina226::power()
{
	uint16_t val;
	if (!mI2c->readShort(POWER_REG, val))
	{
		std::cerr << "INA226::ERROR " << mI2c->error() << std::endl ;
		return 0.0;
	}

	float valf = POWER_CONST * mCurrentLSB * (float)val ;
	return valf ;
}

//-------------------------------------------------------------------------------------------------------------
float Ina226::voltage()
{
	uint16_t val;
	if (!mI2c->readShort(BUS_VOLT_REG, val))
	{
		std::cerr << "INA226::ERROR " << mI2c->error() << std::endl ;
		return 0.0;
	}

	float valf = VOLT_CONST * (float)val ;
	return valf ;
}

//-------------------------------------------------------------------------------------------------------------
float Ina226::current()
{
	uint16_t val;
	if (!mI2c->readShort(CURRENT_REG, val))
	{
		std::cerr << "INA226::ERROR " << mI2c->error() << std::endl ;
		return 0.0;
	}

	float valf = mCurrentLSB * (float)val ;
	return valf ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226::isPowerSupported() const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226::isVoltageSupported() const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Ina226::isCurrentSupported() const
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Ina226::show(void)
{
	std::cout << "INA226 " << getName() << std::endl ;
	std::cout << "Current LSB: " << mCurrentLSB << " Cal: " << mCalibration << std::endl ;

	uint16_t config ;
	mI2c->readShort(CONFIG_REG, config) ;

	uint16_t shuntVolt ;
	mI2c->readShort(SHUNT_VOLT_REG, shuntVolt) ;

	uint16_t voltVal ;
	mI2c->readShort(BUS_VOLT_REG, voltVal) ;

	uint16_t powerVal ;
	mI2c->readShort(POWER_REG, powerVal) ;

	uint16_t currentVal ;
	mI2c->readShort(CURRENT_REG, currentVal) ;

	uint16_t cal ;
	mI2c->readShort(CALIBRATION_REG, cal) ;

	std::cout << "[00] Config......: " << config << std::endl ;
	std::cout << "[01] Shunt Volt..: " << shuntVolt << std::endl ;
	std::cout << "[02] Bus Volt....: " << voltVal << std::endl ;
	std::cout << "[03] Power.......: " << powerVal << std::endl ;
	std::cout << "[04] Current.....: " << currentVal << std::endl ;
	std::cout << "[05] Calibration.: " << cal << std::endl ;
	std::cout << "Voltage..........: " << voltage() << std::endl ;
	std::cout << "Current..........: " << current() << std::endl ;
	std::cout << "Power............: " << power() << std::endl ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Ina226::calcCalibration()
{
	// Work out the current LSB
	mCurrentLSB = mMaxCurrent / CURRENT_LSB_DENOM ;

	// now work out the calibration value
	mCalibration = (unsigned)( CALIBRATION_NUMERATOR / (mCurrentLSB * mShuntResistor) + 0.5);
}
