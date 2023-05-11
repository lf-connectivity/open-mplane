/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiBusSettings.h
 * \brief     Virtual interface to SPI bus settings
 *
 *
 * \details   Virtual interface to SPI bus settings
 *
 */


#ifndef VHI_INC_BUS_ISPIBUSSETTINGS_H_
#define VHI_INC_BUS_ISPIBUSSETTINGS_H_

#include "IBusSettings.h"

namespace Mplane {

/*!
 * \class  ISpiBusReadonlySettings
 * \brief
 * \details
 *
 */
class ISpiBusReadonlySettings : public virtual IBusReadonlySettings {
public:
	ISpiBusReadonlySettings() {}
	virtual ~ISpiBusReadonlySettings() {}

	enum SpiMode {
		SPI_MODE0	= 0,	// normal clock phase, polarity
		SPI_MODE1	= 1,	// inverted clock phase
		SPI_MODE2	= 2,	// inverted clock polarity
		SPI_MODE3	= 3,	// inverted clock phase & inverted clock polarity
	};

	/**
	 * Get the maximum SPI interface speed in Hz
	 */
	virtual unsigned speedHz() const =0 ;

	/**
	 * Get the clock mode
	 */
	virtual SpiMode mode() const =0 ;
} ;

/*!
 * \class  ISpiBusSettings
 * \brief
 * \details
 *
 */
class ISpiBusSettings : public virtual IBusSettings, public virtual ISpiBusReadonlySettings {
public:
	ISpiBusSettings() {}
	virtual ~ISpiBusSettings() {}

	using SpiMode = ISpiBusReadonlySettings::SpiMode ;

	/**
	 * Set the maximum SPI interface speed in Hz (actual SPI bus may run slower than the requested value)
	 */
	virtual bool setSpeedHz(unsigned speedHz) =0 ;

	/**
	 * Set the clock mode
	 */
	virtual bool setMode(SpiMode mode) =0 ;

} ;

}

#endif /* VHI_INC_BUS_ISPIBUSSETTINGS_H_ */
