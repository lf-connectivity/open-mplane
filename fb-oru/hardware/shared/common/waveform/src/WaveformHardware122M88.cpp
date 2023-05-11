/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware122M88.cpp
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
#include "WaveformHardware122M88.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned SAMPLE_RATE_KSPS122{122880} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardware122M88::WaveformHardware122M88(unsigned index, unsigned port) :
	WaveformHardware(index, port)
{
}

//-------------------------------------------------------------------------------------------------------------
WaveformHardware122M88::~WaveformHardware122M88()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware122M88::checkCarrier(std::string& error) const
{
	// do default checks
	if (!this->super::checkCarrier(error))
		return false ;

	// add check that carrier is set to the required setting
	if (mChbw != ICarrierHardwareTypes::CHBW_122880)
	{
		error = "Carrier BW needs to be set to 122.88M" ;
		return false ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardware122M88::getSampleRateKsps() const
{
	return SAMPLE_RATE_KSPS122 ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware122M88::setPlaybackSamplerate()
{
	// Program this waveform module to the fixed sample rate
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	// 122.88MSPS = CLK (245.76M) / (N + A/B) = 245.76 / 1.6
	waveformFpga->write_waveSampleRateN(mWaveIdx, 1) ;
	waveformFpga->write_waveSampleRateA(mWaveIdx, 0) ;
	waveformFpga->write_waveSampleRateB(mWaveIdx, 0) ;

	return true ;
}
