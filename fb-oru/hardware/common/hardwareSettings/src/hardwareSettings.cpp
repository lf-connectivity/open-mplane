/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HardwareSettings.cpp
 * \brief     Etna-specific system settings
 *
 *
 * \details   Contains the clock rates etc. for Etna. Object is a singleton that provides read-only values and conversion functions
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFpgaMgr.h"
#include "hardwareSettings.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

/*
//-------------------------------------------------------------------------------------------------------------
class HardwareSettingsInstance : public HardwareSettings {
public:
	HardwareSettingsInstance() : HardwareSettings(Frequency(245760000ull, Frequency::Hz)) {}
	virtual ~HardwareSettingsInstance() {}
};
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHardwareSettings> HardwareSettings::getInstance(void)
{
	static std::shared_ptr<IHardwareSettings> singleton( std::make_shared<HardwareSettingsInstance>() );
	return singleton ;
}
*/


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HardwareSettings::HardwareSettings(Frequency dsp_clock) :
	m_dsp_clock(dsp_clock),
	m_ul_nco_width(23),
	m_dl_nco_width(23),

	// == Constant ==

	m_DL_NCO_DIVISOR(8), 		// (Currently this divisor is 8 for DL, so for DSP clock = 245.76MHz, NCO = 30.72MHz)
	m_UL_NCO_DIVISOR(4),		// (Currently this divisor is 4 for UL, so for DSP clock = 245.76MHz, NCO = 61.44MHz)


	// == Derived ==
	m_CPRI_CAPABILITY(IHardwareSettings::RATE6),
	m_clockToUi(0),
	m_fpgaAfTimerFreq(0ull, Frequency::KHz),
	m_fpgaAfTimerPeriodUtus(0.0),
	m_clktype(CLK_UNSET),
	m_ul_nco_max(1 << m_ul_nco_width),
	m_dl_nco_max(1 << m_dl_nco_width),
	m_dl_nco_freq(0ull),
	m_ul_nco_freq(0ull)
{
	load() ;
}

//-------------------------------------------------------------------------------------------------------------
HardwareSettings::~HardwareSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
void HardwareSettings::reload()
{
	load() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void HardwareSettings::load()
{
	// Defaults
	m_ul_nco_width = (23) ;
	m_dl_nco_width = (23) ;
	m_DL_NCO_DIVISOR = (8) ;
	m_UL_NCO_DIVISOR = (4) ;
	m_CPRI_CAPABILITY = (IHardwareSettings::RATE6) ;
	m_clockToUi = (0) ;
	m_fpgaAfTimerFreq = Frequency(0ull, Frequency::KHz) ;
	m_fpgaAfTimerPeriodUtus = (0.0) ;
	m_clktype = (CLK_UNSET) ;
	m_ul_nco_max = (1 << m_ul_nco_width) ;
	m_dl_nco_max = (1 << m_dl_nco_width) ;
	m_dl_nco_freq = (0ull) ;
	m_ul_nco_freq = (0ull) ;


	//-------------------------------------------------------------------------------------------------
	// Sets the calculated values derived from the DSP clock setting

	// From src/etc/nsn_objects.ax:
	//
	//fpgaAfTimerFreq_kHz = fpgaDspClkFreq_kHz / 8;
	//::fpgaAfTimerPeriodUtus = 1228800.0 / toReal(fpgaAfTimerFreq_kHz);
	//
	m_fpgaAfTimerFreq = Frequency(m_dsp_clock.getUint(Frequency::Hz) / 8, Frequency::Hz) ;
	m_fpgaAfTimerPeriodUtus = 1228800.0 / static_cast<float>(m_fpgaAfTimerFreq.getUint(Frequency::KHz)) ;

	m_clktype = CLK_UNSET ;
	if (m_dsp_clock.getUint(Frequency::KHz) == 224000u)
	{
		m_clktype = CLK_224000 ;
	}
	else if (m_dsp_clock.getUint(Frequency::KHz) == 245760u)
	{
		m_clktype = CLK_245760 ;
	}
	else if (m_dsp_clock.getUint(Frequency::KHz) == 491520u)
	{
		m_clktype = CLK_491520;
	}

	//-------------------------------------------------------------------------------------------------
	// Read the number of clocks per sample for UL & DL
	// Note: Older fpgas will read back 0, in which case keep the defaults
	auto fpga( IFpgaMgr::getIFpgaSystemRegs() ) ;
	UINT16 rdval = fpga->read_dlTunerClocksPerSample() ;
	if (rdval) m_DL_NCO_DIVISOR = rdval ;
	rdval = fpga->read_ulTunerClocksPerSample() ;
	if (rdval) m_UL_NCO_DIVISOR = rdval ;


	//-------------------------------------------------------------------------------------------------
	// Calculate NCO frequency
	// Convert offset value into a frequency offset:
	//
	// NCO_Phase_Inc = (2^NCO_Width) * Freq_Offset / NCO_Freq
	//
	// (the divisor is 30.72 MHz for DL but 61.44 MHz for UL.
	// So, if you are trying to tune DL by 1 MHz the tuner phase increment would be round(2^23 * (1 MHz / 30.72 MHz)).)
	//
	// Freq_Offset = NCO_Phase_Inc * NCO_Freq / (2^NCO_Width)
	//
	// Where:
	//   NCO_Width is fixed (currently 23 bits)
	//   NCO_Freq = DSP_Clock_Freq / Tuner_NCO_Divisor
	//   (see http://twiki.axisnt.co.uk/cgi-bin/twiki/view/Engineering/SwIfCommonSync digital
	//	frequency tuning section)
	//

	// With fpgaDspClkFreq=245,760,000 HZ and NCO_DIVISOR=8 then $nco_freq_Hz=30.72MHz
	m_dl_nco_freq = Frequency( m_dsp_clock.getUint() / m_DL_NCO_DIVISOR ) ;
	m_ul_nco_freq = Frequency(m_dsp_clock.getUint() / m_UL_NCO_DIVISOR ) ;


	//-------------------------------------------------------------------------------------------------
	// See http://twiki.axisnt.co.uk/cgi-bin/twiki/view/Engineering/SwIfCommonBbIfCpri#Delay_Measurement_and_Compensati
	// I'm assuming that all fibres will use the same core version!
	UINT16 majorVersion(IFpgaMgr::getIFpgaFibreRegs()->read_xilinxCoreMajorRevision(0)) ;
	if (majorVersion >= 8)
		m_CPRI_CAPABILITY = IHardwareSettings::RATE8_CAPABLE ;
	else if (majorVersion >= 5)
		m_CPRI_CAPABILITY = IHardwareSettings::RATE7_CAPABLE ;


	// UI conversion depends on the cpri core
	m_clockToUi = 20 ;
	if (m_CPRI_CAPABILITY == IHardwareSettings::RATE8_CAPABLE)
		m_clockToUi = 33 ;
	else if (m_CPRI_CAPABILITY == IHardwareSettings::RATE7_CAPABLE)
		m_clockToUi = 40 ;

	// Check the number of NCO bits
	rdval = fpga->read_dlTunerNcoBits() ;
	if (rdval)
	{
		m_dl_nco_width = rdval ;
		m_dl_nco_max = 1 << m_dl_nco_width ;
	}
	rdval = fpga->read_ulTunerNcoBits() ;
	if (rdval)
	{
		m_ul_nco_width = rdval ;
		m_ul_nco_max = 1 << m_ul_nco_width ;
	}

}
