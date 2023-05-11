/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareFullrate_unittest.cpp
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
#include "WaveformHardwareFullrate.h"

using namespace Mplane;

//===================================================================================================================
class WaveformHardwareFullrateTest : public ModelFixture {
};

//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformHardwareFullrateTest, Basic)
{
	// Ensure methods run
	std::shared_ptr<WaveformHardwareFullrate> waveformHardware(new WaveformHardwareFullrate(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform(new Waveform) ;
	std::cout << "Wave=" << waveform << std::endl ;
	waveform->setDepth(2048) ;


	std::string error ;
	waveformHardware->updateSettings(waveform, std::shared_ptr<WaveformMem>(), error) ;
	waveformHardware->updateHardware(error) ;

	waveformHardware->isCaptureWriteError() ;

	waveformHardware->isCaptureDone() ;

	waveformHardware->isPlaybackEnabled() ;

	waveformHardware->isPlaybackReadError() ;

	std::vector<short> buffer ;
	bool endOfFile ;

	waveformHardware->writeMemoryStart();

	waveformHardware->writeMemory(buffer.data(), buffer.size(), endOfFile, error);

	waveformHardware->readMemoryStart();

	// test << overload
	std::cout << "waveformHardwareFullrate=" << waveformHardware << std::endl ;
}
