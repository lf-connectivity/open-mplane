/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformControl_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "model_fixture.h"

#include "Waveform.h"
#include "WaveformMem.h"
#include "WaveformHardware.h"
#include "WaveformControl.h"

using namespace Mplane;

//===================================================================================================================
class WaveformControlTest : public ModelFixture {
};

//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformControlTest, Basic)
{
	// Ensure methods run
	std::shared_ptr<IWaveformControl> waveControl(new WaveformControl ) ;
	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform ;
	std::shared_ptr<IWaveformMem> waveformMem ;

	std::string error ;

	waveControl->setWaveformHardware(waveformHardware, error) ;
	waveControl->validate(error) ;
	waveControl->updateHardware(error) ;
	std::shared_ptr<IWaveform> w = waveControl->getWaveform()  ;
	std::shared_ptr<IWaveformHardware> wh = waveControl->getWaveformHardware()  ;
	std::shared_ptr<IWaveformMem> wm = waveControl->getWaveformMem()  ;

	std::vector< std::shared_ptr<IWaveformControl> > enabledWaves ;
	WaveformControl::startCapturePlayback(false, enabledWaves, error) ;
	WaveformControl::startPlayback(enabledWaves, error) ;
	WaveformControl::stopCapture(enabledWaves, error) ;
	WaveformControl::stopPlayback(enabledWaves, error) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformControlTest, Validate)
{
	// Ensure methods run
	std::shared_ptr<IWaveformControl> waveControl(new WaveformControl ) ;
	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::string error ;

	// no hardware allocated
	EXPECT_FALSE(waveControl->validate(error)) ;
	EXPECT_FALSE(error.empty()) ;
	std::cerr << "Expected error : " << error << std::endl ;

	// allocate hardware
	waveControl->setWaveformHardware(waveformHardware, error) ;

	// invalid settings
	EXPECT_FALSE(waveControl->validate(error)) ;
	EXPECT_FALSE(error.empty()) ;
	std::cerr << "Expected error : " << error << std::endl ;

	// set settings
	std::shared_ptr<IWaveform> wave = waveControl->getWaveform()  ;
	wave->setDepth(1024) ;
	EXPECT_FALSE(waveControl->validate(error)) ;
	EXPECT_FALSE(error.empty()) ;

	wave->setAntennaPort(0) ;
	wave->setCarrierIdx(0) ;
	wave->setDirection(IWaveform::WAVE_TX) ;
	wave->setType(IWaveform::WAVEFORM_PLAYBACK) ;
	EXPECT_FALSE(waveControl->validate(error)) ;
	EXPECT_FALSE(error.empty()) ;
	std::cerr << "Expected error : " << error << std::endl ;

	wave->setFilename("playback.bin") ;
	EXPECT_FALSE(waveControl->validate(error)) ;
	EXPECT_FALSE(error.empty()) ;
	std::cerr << "Expected error : " << error << std::endl ;
	std::cerr << "Modified filename : " << wave->getFilename() << std::endl ;

}
