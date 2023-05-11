/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware153M6.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IFpgaMgr.h"
#include "WaveformHardware153M6.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned SAMPLE_RATE_KSPS{153600} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardware153M6::WaveformHardware153M6(unsigned index, unsigned port) :
	WaveformHardware(index, port)
{
}

//-------------------------------------------------------------------------------------------------------------
WaveformHardware153M6::~WaveformHardware153M6()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware153M6::checkCarrier(std::string& error) const
{
	// do default checks
	if (!this->super::checkCarrier(error))
		return false ;

	// add check that carrier is set to the required setting
	if (mChbw != ICarrierHardwareTypes::CHBW_153600)
	{
		error = "Carrier BW needs to be set to 153.6M" ;
		return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardware153M6::getSampleRateKsps() const
{
	return SAMPLE_RATE_KSPS ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware153M6::setPlaybackSamplerate()
{
	// Program this waveform module to the fixed sample rate
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	// 153.6MSPS = CLK (245.76M) / (N + A/B) = 245.76 / 1.6
	waveformFpga->write_waveSampleRateN(mWaveIdx, 0) ;
	waveformFpga->write_waveSampleRateA(mWaveIdx, 3) ;
	waveformFpga->write_waveSampleRateB(mWaveIdx, 4) ;

	return true ;
}
