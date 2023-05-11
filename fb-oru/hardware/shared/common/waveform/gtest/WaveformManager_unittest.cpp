/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformManager_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>
#include <fstream>

#include "Power.h"
#include "ICarrierServer.h"
#include "ICarrier.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrierHardware.h"

#include "model_fixture.h"

#include "WaveformHardware.h"
#include "WaveformHardwareFullrate.h"
#include "WaveformHardwareDpdAdc.h"

#include "WaveformManager.h"

using namespace Mplane;


//===================================================================================================================
class WaveformManagerTest : public ModelFixture {
public:

	void checkError(std::shared_ptr<WaveformManager> waveMgr, bool expectedError = false, const std::string& expectedErrorStr = "")
	{
		std::string error ;

		error = waveMgr->getErrorReason() ;
		if (!error.empty())
			std::cout << "ERROR: " << error << std::endl ;

		EXPECT_EQ(expectedError, !error.empty()) ;

		if (expectedError)
		{
			EXPECT_TRUE(error.find(expectedErrorStr) != std::string::npos) ;
		}
	}

};

//===================================================================================================================
class TesterWaveformManager : public WaveformManager {
public:
	TesterWaveformManager() :
		WaveformManager()
	{
	}

	~TesterWaveformManager() {}

	bool init()
	{
		std::string error ;

		// Nailed to w0-w7 (w8, w9 are dummies for now), w10 is special playback at full rate
		// Also, the index sets the waveform type:
		// 0, 1 = CAPTURE
		// 2, 3 = PLAYBACK
		// ..
		// 10, 11 = PLAYBACK
		// 12 (DPD) = CAPTURE

		// Nail down to the 10 possible resources for now
		unsigned idx ;
		for (idx=0; idx <= 9; ++idx)
		{
			std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardware(idx, (idx % 2))) ;
			addResource(waveformHardware);

			// do any initialisation
			waveformHardware->init(error) ;
		}

		// special case for w10 (w11 is dummy to ensure DPD ADC capture waveform has an even index)
		for (idx=10; idx <= 11; ++idx)
		{
			std::shared_ptr<WaveformHardwareFullrate> waveformHardware(new WaveformHardwareFullrate(idx, (idx % 2))) ;
			addResource(waveformHardware);

			// do any initialisation
			waveformHardware->init(error) ;
		}

		// Append a DPD ADC capture waveform
		{
			std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardwareDpdAdc(idx, 0)) ;
			addResource(waveformHardware);

			// do any initialisation
			waveformHardware->init(error) ;
		}

		if (!error.empty())
		{
			setError(error) ;
			return false ;
		}

		return true ;
	}

};


//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformManagerTest, Methods)
{
	std::shared_ptr<TesterWaveformManager> waveMgr(new TesterWaveformManager) ;
	waveMgr->init() ;

	// Check all methods run
	std::string waveName("w2") ;
	waveMgr->createWave(waveName, IWaveform::WAVEFORM_PLAYBACK) ;
	waveMgr->hasWave(waveName) ;
	waveMgr->deleteWave(waveName) ;

	waveMgr->setAntennaPort(waveName, 1) ;
	waveMgr->setCarrierIdx(waveName, 0) ;
	waveMgr->setDirection(waveName, IWaveform::WAVE_TX) ;
	waveMgr->setFilename(waveName, "test2048.bin") ;
	waveMgr->setEnable(waveName, true) ;
	waveMgr->setDepth(waveName, 1024) ;
	waveMgr->setGain(waveName, 1.0) ;
	waveMgr->setGainFilename(waveName, "gain.bin") ;
	waveMgr->setTrigger(waveName, 0) ;
	waveMgr->setScalingGain(waveName, 0) ;

	waveMgr->setCapturePlayback(true, true) ;
	waveMgr->getErrorReason() ;
	waveMgr->supportedWaveforms()  ;
	waveMgr->numWaveforms()  ;
	waveMgr->isPlaybackEnabled()  ;
	waveMgr->isCaptureEnabled()  ;

	// Debug
	waveMgr->show() ;
	waveMgr->show("w2") ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformManagerTest, Wave)
{
	std::string error ;
	std::shared_ptr<TesterWaveformManager> waveMgr(new TesterWaveformManager) ;
	waveMgr->init() ;

	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;

	std::string waveName("w2") ;
	EXPECT_FALSE(waveMgr->hasWave(waveName)) ;
	EXPECT_TRUE(waveMgr->createWave(waveName, IWaveform::WAVEFORM_PLAYBACK)) ;
	EXPECT_TRUE(waveMgr->hasWave(waveName)) ;
	EXPECT_EQ(1u, waveMgr->numWaveforms())  ;

	EXPECT_TRUE(waveMgr->setAntennaPort(waveName, 1)) ;
	EXPECT_TRUE(waveMgr->setCarrierIdx(waveName, 0)) ;
	EXPECT_TRUE(waveMgr->setDirection(waveName, IWaveform::WAVE_TX)) ;
	EXPECT_TRUE(waveMgr->setFilename(waveName, "../../../waveform/gtest/playback/test2048.bin")) ;
	EXPECT_TRUE(waveMgr->setDepth(waveName, 1024)) ;
	EXPECT_TRUE(waveMgr->setGain(waveName, 1.0)) ;
	EXPECT_TRUE(waveMgr->setGainFilename(waveName, "gain.bin")) ;
	EXPECT_TRUE(waveMgr->setTrigger(waveName, 0)) ;
	EXPECT_TRUE(waveMgr->setScalingGain(waveName, -1)) ;

	// Settings enable will cause the manager to check the waveform settings
	EXPECT_FALSE(waveMgr->setEnable(waveName, true)) ;
	checkError(waveMgr, true, "Carrier not configured") ;


	EXPECT_FALSE(waveMgr->setTrigger("w0", 0)) ;



	waveMgr->show(waveName) ;
	waveMgr->show() ;

	EXPECT_TRUE(waveMgr->deleteWave(waveName)) ;
	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;

	waveMgr->show() ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformManagerTest, WaveType)
{
	std::string error ;
	std::shared_ptr<TesterWaveformManager> waveMgr(new TesterWaveformManager) ;
	waveMgr->init() ;

	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;

	std::string waveName("w4") ;
	EXPECT_FALSE(waveMgr->hasWave(waveName)) ;
	EXPECT_TRUE(waveMgr->createWave(waveName, IWaveform::WAVEFORM_PLAYBACK)) ;
	EXPECT_TRUE(waveMgr->hasWave(waveName)) ;
	EXPECT_EQ(1u, waveMgr->numWaveforms())  ;

	EXPECT_TRUE(waveMgr->setAntennaPort(waveName, 1)) ;
	EXPECT_TRUE(waveMgr->setCarrierIdx(waveName, 0)) ;
	EXPECT_TRUE(waveMgr->setDirection(waveName, IWaveform::WAVE_TX)) ;
	EXPECT_TRUE(waveMgr->setFilename(waveName, "../../../waveform/gtest/playback/test2048.bin")) ;
	EXPECT_TRUE(waveMgr->setDepth(waveName, 1024)) ;
	EXPECT_TRUE(waveMgr->setGain(waveName, 1.0)) ;
	EXPECT_TRUE(waveMgr->setGainFilename(waveName, "gain.bin")) ;
	EXPECT_TRUE(waveMgr->setTrigger(waveName, 0)) ;
	EXPECT_TRUE(waveMgr->setScalingGain(waveName, 1)) ;

	// Settings enable will cause the manager to check the waveform settings
	EXPECT_FALSE(waveMgr->setEnable(waveName, true)) ;
	checkError(waveMgr, true, "Waveform must be set to CAPTURE") ;

	waveMgr->show(waveName) ;
	waveMgr->show() ;

	EXPECT_TRUE(waveMgr->deleteWave(waveName)) ;
	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;


	waveName = "w2" ;
	EXPECT_FALSE(waveMgr->hasWave(waveName)) ;
	EXPECT_TRUE(waveMgr->createWave(waveName, IWaveform::WAVEFORM_CAPTURE)) ;
	EXPECT_TRUE(waveMgr->hasWave(waveName)) ;
	EXPECT_EQ(1u, waveMgr->numWaveforms())  ;

	EXPECT_TRUE(waveMgr->setAntennaPort(waveName, 1)) ;
	EXPECT_TRUE(waveMgr->setCarrierIdx(waveName, 0)) ;
	EXPECT_TRUE(waveMgr->setDirection(waveName, IWaveform::WAVE_TX)) ;
	EXPECT_TRUE(waveMgr->setFilename(waveName, "../../../waveform/gtest/playback/test2048.bin")) ;
	EXPECT_TRUE(waveMgr->setDepth(waveName, 1024)) ;
	EXPECT_TRUE(waveMgr->setGain(waveName, 1.0)) ;
	EXPECT_TRUE(waveMgr->setGainFilename(waveName, "gain.bin")) ;
	EXPECT_TRUE(waveMgr->setTrigger(waveName, 0)) ;

	// Settings enable will cause the manager to check the waveform settings
	EXPECT_FALSE(waveMgr->setEnable(waveName, true)) ;
	checkError(waveMgr, true, "Waveform must be set to PLAYBACK") ;

	waveMgr->show(waveName) ;
	waveMgr->show() ;

	EXPECT_TRUE(waveMgr->deleteWave(waveName)) ;
	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;


	waveMgr->show() ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformManagerTest, FullRate)
{
	std::string error ;
	std::shared_ptr<TesterWaveformManager> waveMgr(new TesterWaveformManager) ;
	waveMgr->init() ;

	std::string waveName("w10") ;
	EXPECT_FALSE(waveMgr->hasWave(waveName)) ;
	EXPECT_TRUE(waveMgr->createWave(waveName, IWaveform::WAVEFORM_PLAYBACK)) ;
	EXPECT_TRUE(waveMgr->hasWave(waveName)) ;
	EXPECT_EQ(1u, waveMgr->numWaveforms())  ;

	waveMgr->show(waveName) ;
	waveMgr->show() ;

	EXPECT_TRUE(waveMgr->deleteWave(waveName)) ;
	EXPECT_EQ(0u, waveMgr->numWaveforms())  ;
}

// **** NOTE: FULL REGISTER COMPARISON CHECKS ARE DONE IN THE APPLICATION AREA (e.g. ETNA_ART) ****
