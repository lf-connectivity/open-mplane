/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sc18is602bBusSettings.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Sc18is602bBusSettings.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const uint8_t SPI_CONFIG_ADDR(0xF0) ;
const unsigned BIT_ORDER(5) ;
const unsigned BIT_MODE(2) ;
const unsigned BIT_F(0) ;
const unsigned MASK_ORDER(1) ;
const unsigned MASK_MODE(3) ;
const unsigned MASK_F(3) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Sc18is602bBusSettings::Sc18is602bBusSettings(std::shared_ptr<II2cBus> i2c) :
	SpiBusSettings(),
	mI2c(i2c)
{
	// read the current config
	uint8_t config ;
	if (!mI2c->readByte(SPI_CONFIG_ADDR, config))
		return ;

	// extract the config settings
	uint8_t order( (config >> BIT_ORDER) & MASK_ORDER ) ;
	uint8_t mode( (config >> BIT_MODE) & MASK_MODE ) ;
	uint8_t f( (config >> BIT_F) & MASK_F ) ;

	if (order == 0)
	{
		SpiBusSettings::setBigEndian() ;
	}
	else
	{
		SpiBusSettings::setLittleEndian() ;
	}

	SpiBusSettings::setMode( (ISpiBusSettings::SpiMode)mode ) ;

	unsigned speedHz(0) ;
	switch(f)
	{
	case 0: speedHz = 1843000 ; break ;
	case 1: speedHz = 461000 ; break ;
	case 2: speedHz = 115000 ; break ;
	case 3: speedHz = 58000 ; break ;
	default: speedHz = 0 ; break ;
	}
	SpiBusSettings::setSpeedHz(speedHz) ;
}

//-------------------------------------------------------------------------------------------------------------
Sc18is602bBusSettings::~Sc18is602bBusSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Sc18is602bBusSettings::setBigEndian()
{
	SpiBusSettings::setBigEndian() ;
	return setConfigReg() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Sc18is602bBusSettings::setLittleEndian()
{
	SpiBusSettings::setLittleEndian() ;
	return setConfigReg() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Sc18is602bBusSettings::setSpeedHz(unsigned speedHz)
{
	if (speedHz >= 1843000)
		speedHz = 1843000 ;
	else if (speedHz >= 461000)
		speedHz = 461000 ;
	else if (speedHz >= 115000)
		speedHz = 115000 ;
	else if (speedHz >= 58000)
		speedHz = 58000 ;
	else
		speedHz = 0 ;

	SpiBusSettings::setSpeedHz(speedHz) ;
	return setConfigReg() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Sc18is602bBusSettings::setMode(ISpiBusSettings::SpiMode mode)
{
	SpiBusSettings::setMode( mode ) ;
	return setConfigReg() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Sc18is602bBusSettings::setConfigReg()
{
	// create the register value from the current settings

	unsigned f(3) ;
	if (speedHz() >= 1843000)
		f = 0 ;
	else if (speedHz() >= 461000)
		f = 1 ;
	else if (speedHz() >= 115000)
		f = 2 ;
	else if (speedHz() >= 58000)
		f = 3 ;
	else
		f = 3 ;

	uint8_t config(0) ;
	config |= (f << BIT_F) ;
	config |= ( (uint8_t)mode() << BIT_MODE) ;
	if (isLittleEndian())
		config |= (1 << BIT_ORDER) ;

	return mI2c->writeByte(SPI_CONFIG_ADDR, config) ;
}
