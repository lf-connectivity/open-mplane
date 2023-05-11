/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>

#include "IFpgaMgr.h"

#include "WaveformHardwareFullrate.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardwareFullrate::WaveformHardwareFullrate(unsigned index, unsigned port) :
	WaveformHardware(index, port)
{
}


//-------------------------------------------------------------------------------------------------------------
WaveformHardwareFullrate::~WaveformHardwareFullrate()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFullrate::init(std::string& error)
{
	if (!this->super::init(error))
		return false ;

	// init bit
	setMulticastDac( false ) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFullrate::updateHardware(std::string& error)
{
	if (!this->super::updateHardware(error))
		return false ;

	// Only do special writes for w10
	unsigned port(mWaveIdx % 2) ;
	if (port != 0)
		return true ;

	//Set the Capture Trigger window to match the playback length to ensure consistent captures. This is done is 30.72MHz for consistency
	//This must be done before playback=on is sent as the FPGA re-syncronises the triggers upon playback
	unsigned nTrig = (mWaveform->getDepth() / 8);
	if (nTrig > 2) nTrig -= 2 ;
	mWaveformFpga->write_dpdadcCaptureAveTriggerWidth(nTrig) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareFullrate::enableHasChanged(bool enable)
{
	this->super::enableHasChanged(enable) ;

	// update the bit to multicast waveform to DACs
	setMulticastDac( enable ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFullrate::checkCarrier(std::string& error) const
{
	// Carrier not required
	error = "" ;
	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFullrate::setPlaybackSamplerate()
{
	// Waveform modules are currently nailed to w10 = TX1, w11=TX2
	unsigned port(mWaveIdx % 2) ;

	// Read the existing DAC test setting for the DAC clock samples. Then use this setting for the full-rate waveform
	auto antFpga(IFpgaMgr::getIFpgaAntennaRegs()) ;
	UINT16 clksPerSample = antFpga->read_antDacClksPerSample(port) ;

	// Program this waveform module to the proper sample rate - 245.76 (i.e. DSP clock). Just want a x1 multiplier
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	waveformFpga->write_waveSampleRateN(mWaveIdx, clksPerSample) ;
	waveformFpga->write_waveSampleRateA(mWaveIdx, 0) ;
	waveformFpga->write_waveSampleRateB(mWaveIdx, 0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareFullrate::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	// Waveform modules are currently nailed to w10 = TX1, w11=TX1
	unsigned port(mWaveIdx % 2) ;

	// Read the existing DAC test setting for the DAC clock samples. Then use this setting for the full-rate waveform
	auto antFpga(IFpgaMgr::getIFpgaAntennaRegs()) ;
	UINT16 clksPerSample( antFpga->read_antDacClksPerSample(port) + 1 ) ;

	std::shared_ptr<const IHardwareSettings> hwSettings(IHardwareSettings::getInstance());
	const Frequency dspClk(hwSettings->getDspClock()) ;
	unsigned dspRateKsps(dspClk.getUint(Frequency::KHz)) ;

	unsigned rateKsps(dspRateKsps / clksPerSample) ;

//	std::cerr << "WaveformHardwareFullrate::getInstanceSampleRateKsps clksPerSample=" << clksPerSample <<
//			" dspClk=" << dspClk <<
//			" rateKsps=" << rateKsps <<
//			std::endl ;

	return rateKsps ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareFullrate::setMulticastDac(bool enable)
{
	auto fpgaSys(IFpgaMgr::getIFpgaSystemRegs()) ;

	// write bit(s) - original fpga had single bit; new fpga has selector. Both use bit 0=1 for playback multicast
	fpgaSys->write_dacInputSel(enable ? 1 : 0) ;

	return true ;
}
