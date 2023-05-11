/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IHardwareSettings.h
 * \brief     Hardware-specific system settings
 *
 *
 * \details   Contains the clock rates etc for specific hardware. Object is a singleton that provides read-only values and conversion functions
 *
 */


#ifndef IHARDWARESETTINGS_H_
#define IHARDWARESETTINGS_H_

#include <memory>

#include "Frequency.h"

namespace Mplane {

class IHardwareSettings {
public:
    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of this object within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IHardwareSettings> getInstance(void);

	IHardwareSettings() {}
	virtual ~IHardwareSettings() {}

    // Supported DSP clock rates
    enum dspclk_type {
    	CLK_224000	= 0,
    	CLK_245760	= 1,
		CLK_491520  = 2,

    	CLK_MIN		= CLK_224000,
    	CLK_MAX		= CLK_491520,
    	CLK_UNSET	= 0xff,
    };

    // Supported CPRI rates
    enum CpriRateCapable {
    	RATE6			= 0,
    	RATE7_CAPABLE	= 1,
    	RATE8_CAPABLE	= 2,
    };

    /**
     * Reload from the fpga settings (mainly used for testbench testing)
     */
    virtual void reload() =0 ;

    /**
     * DSP clock rate
     */
    virtual const enum dspclk_type getClktype() const =0 ;

    /**
     * Actual DSP clock rate
     */
	virtual const Frequency getDspClock() const =0;

	/**
	 * Airframe timer frequency
	 */
	virtual const Frequency getFpgaAfTimerFreq() const =0;

	/**
	 * Airframe timer period in UTUs
	 */
	virtual const float getFpgaAfTimerPeriodUtus() const =0;



	/**
	 * DL NCO number of bits
	 */
	virtual const unsigned getDlNcoWidth() const =0;

	/**
	 * DL NCO maximum value
	 */
	virtual const unsigned getDlNcoMax() const =0;

    /**
     * DL NCO divisor
     */
    virtual const unsigned getDlNcoDivisor() const =0;

    /**
     * DL NCO frequency (DSP CLOCK / DL NCO DIVISOR)
     */
    virtual const Frequency getDlNcoFreq() const =0;


	/**
	 * UL NCO number of bits
	 */
	virtual const unsigned getUlNcoWidth() const =0;

	/**
	 * UL NCO maximum value
	 */
	virtual const unsigned getUlNcoMax() const =0;


    /**
     * UL NCO divisor
     */
	virtual const unsigned getUlNcoDivisor() const =0;

    /**
     * UL NCO frequency (DSP CLOCK / UL NCO DIVISOR)
     */
	virtual const Frequency getUlNcoFreq() const =0;



	/**
	 * Conversion factor to convert clock rate to UIs
	 */
	virtual unsigned getClockToUi() const =0;

	/**
	 * Get the line rate capability of the CPRI core
	 */
	virtual CpriRateCapable getCpriRateCapablity() const =0;

} ;

}

#endif /* IHARDWARESETTINGS_H_ */
