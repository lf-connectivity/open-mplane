/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sc18is602bBusSettings.h
 * \brief     IBusSettings implemented for SC18IS602B device
 *
 *
 * \details   Implements ISpiBusSettings by setting the SC18IS602B register values
 *
 */


#ifndef COMMON_I2CTOSPI_INC_SC18IS602BBUSSETTINGS_H_
#define COMMON_I2CTOSPI_INC_SC18IS602BBUSSETTINGS_H_

#include "II2cBus.h"
#include "SpiBusSettings.h"

namespace Mplane {

/*!
 * \class  Sc18is602bBusSettings
 * \brief
 * \details
 *
 */
class Sc18is602bBusSettings : public SpiBusSettings {
public:
	Sc18is602bBusSettings(std::shared_ptr<II2cBus> i2c) ;
	virtual ~Sc18is602bBusSettings() ;

	// Write interface

	/**
	 * Data transported over the bus MS first
	 */
	virtual bool setBigEndian() override ;

	/**
	 * Data transported over the bus LS first
	 */
	virtual bool setLittleEndian() override ;


	/**
	 * Set the maximum SPI interface speed in Hz (actual SPI bus may run slower than the requested value)
	 */
	virtual bool setSpeedHz(unsigned speedHz) override ;

	/**
	 * Set the clock mode
	 */
	virtual bool setMode(ISpiBusSettings::SpiMode mode) override ;

private:
	bool setConfigReg() ;

private:
	std::shared_ptr<II2cBus> mI2c ;
} ;

}

#endif /* COMMON_I2CTOSPI_INC_SC18IS602BBUSSETTINGS_H_ */
