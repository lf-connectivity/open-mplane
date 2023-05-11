#ifndef _ACE_AXIS_HARDWARESETTINGS_H_
#define _ACE_AXIS_HARDWARESETTINGS_H_

#include <memory>
#include "Frequency.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HardwareSettings.h
 * \brief     Etna-specific system settings
 *
 *
 * \details   Contains the clock rates etc. for Etna. Object is a singleton that provides read-only values and conversion functions
 *
 */

#include "IHardwareSettings.h"

namespace Mplane
{

/*! @brief  Carrier Hardware interface
 *
 *
 *
 */
class HardwareSettings : public virtual IHardwareSettings
{
public:

    /*! @brief  Get the singleton instance of this particular variant
     *
     *  Method used to obtain a reference to the single instance of this object within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IHardwareSettings> getInstance(void);


    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~HardwareSettings() ;


    /**
     * Reload from the fpga settings (mainly used for testbench testing)
     */
    virtual void reload() override ;

    /**
     * DSP clock rate
     */
    virtual const enum dspclk_type getClktype() const override {
		return m_clktype;
	}

    /**
     * Actual DSP clock rate
     */
    virtual const Frequency getDspClock() const override {
		return m_dsp_clock;
	}

	/**
	 * Airframe timer frequency
	 */
    virtual const Frequency getFpgaAfTimerFreq() const override {
		return m_fpgaAfTimerFreq;
	}

	/**
	 * Airframe timer period in UTUs
	 */
    virtual const float getFpgaAfTimerPeriodUtus() const override {
		return m_fpgaAfTimerPeriodUtus;
	}


	/**
	 * DL NCO number of bits
	 */
    virtual const unsigned getDlNcoWidth() const override {
		return m_dl_nco_width;
	}

	/**
	 * DL NCO maximum value
	 */
    virtual const unsigned getDlNcoMax() const override {
		return m_dl_nco_max;
	}

    /**
     * DL NCO divisor
     */
    virtual const unsigned getDlNcoDivisor() const override {
		return m_DL_NCO_DIVISOR;
	}

    /**
     * DL NCO frequency (DSP CLOCK / DL NCO DIVISOR)
     */
    virtual const Frequency getDlNcoFreq() const override {
		return m_dl_nco_freq;
	}


	/**
	 * UL NCO number of bits
	 */
    virtual const unsigned getUlNcoWidth() const override {
		return m_ul_nco_width;
	}

	/**
	 * UL NCO maximum value
	 */
    virtual const unsigned getUlNcoMax() const override {
		return m_ul_nco_max;
	}



    /**
     * UL NCO divisor
     */
    virtual const unsigned getUlNcoDivisor() const override {
		return m_UL_NCO_DIVISOR;
	}

    /**
     * UL NCO frequency (DSP CLOCK / UL NCO DIVISOR)
     */
    virtual const Frequency getUlNcoFreq() const override {
		return m_ul_nco_freq;
	}



	/**
	 * Conversion factor to convert clock rate to UIs
	 */
    virtual unsigned getClockToUi() const override {
		return m_clockToUi;
	}

	/**
	 * Get the line rate capability of the CPRI core
	 */
	virtual IHardwareSettings::CpriRateCapable getCpriRateCapablity() const override {
		return m_CPRI_CAPABILITY;
	}


protected:
    /**
     *
     */
	HardwareSettings(Frequency dsp_clock);

	void load() ;

protected:

	// used to calculate the sample rate
	Frequency	m_dsp_clock ;

	// Number of bits in NCO
	unsigned	m_ul_nco_width ;
	unsigned	m_dl_nco_width ;

	// == Constant ==

	// NCO_Freq = DSP_Clock_Freq / Tuner_NCO_Divisor
	// (Currently this divisor is 8 for DL, so for DSP clock = 245.76MHz, NCO = 30.72MHz)
	// (Currently this divisor is 4 for UL, so for DSP clock = 245.76MHz, NCO = 61.44MHz)
	unsigned 	m_DL_NCO_DIVISOR ;
	unsigned 	m_UL_NCO_DIVISOR ;

	// Rate capability - CPRI core is rate6/rate7/rate8 capable (changes how the delays are calculated)
	IHardwareSettings::CpriRateCapable m_CPRI_CAPABILITY ;
	unsigned	m_clockToUi ;


	// == Derived ==

	// calculated from the DSP clock rate
	Frequency	m_fpgaAfTimerFreq ;
	float		m_fpgaAfTimerPeriodUtus ;

	enum dspclk_type m_clktype ;

	// calc 2**nco_width
	unsigned	m_ul_nco_max ;
	unsigned	m_dl_nco_max ;

	// DL and UL nco frequency in Hz
	Frequency 	m_dl_nco_freq ;
	Frequency 	m_ul_nco_freq ;
};



}

#endif /* _ACE_AXIS_HARDWARESETTINGS_H_ */
