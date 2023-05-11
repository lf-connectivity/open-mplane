/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBusSettings.h
 * \brief     ISpiBusSettings
 *
 *
 * \details   Settings specific to SPI bus
 *
 */


#ifndef COMMON_BUS_INC_SPIBUSSETTINGS_H_
#define COMMON_BUS_INC_SPIBUSSETTINGS_H_

#include "ISpiBusSettings.h"
#include "BusSettings.hpp"

namespace Mplane {

/*!
 * \class  SpiBusSettings
 * \brief
 * \details
 *
 */
class SpiBusSettings : public virtual ISpiBusSettings, public BusSettings {
public:
	SpiBusSettings() ;
	virtual ~SpiBusSettings() ;

	// Read interface

	/**
	 * Set the maximum SPI interface speed in Hz (actual SPI bus may run slower than the requested value)
	 */
	virtual unsigned speedHz() const override ;

	/**
	 * Set the clock mode
	 */
	virtual ISpiBusSettings::SpiMode mode() const override ;

	// Write interface

	/**
	 * Set the maximum SPI interface speed in Hz (actual SPI bus may run slower than the requested value)
	 */
	virtual bool setSpeedHz(unsigned speedHz) override ;

	/**
	 * Set the clock mode
	 */
	virtual bool setMode(ISpiBusSettings::SpiMode mode) override ;


private:
	unsigned mSpeedHz ;
	ISpiBusSettings::SpiMode mMode ;
} ;

}

#endif /* COMMON_BUS_INC_SPIBUSSETTINGS_H_ */
