/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardware_unittest.cpp
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
#include "OffTargetFPGA.h"

#include "Waveform.h"
#include "WaveMemMgr.h"
#include "WaveformMem.h"
#include "WaveformHardware.h"

using namespace Mplane;

//===================================================================================================================
class WaveformHardwareTest : public ModelFixture {
};

// max number of samples to read/write to/from buffer
static const unsigned MAX_BUFF_SAMPLES = 8192 ;

//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformHardwareTest, Basic)
{
	// Ensure methods run
	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform ;
	std::shared_ptr<IWaveformMem> waveformMem ;

	std::string error ;
	waveformHardware->updateSettings(waveform, waveformMem, error) ;
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

//	unsigned maxReadSize = 1024 ;
//	waveformHardware->readMemory(buffer, maxReadSize, endOfFile, error);


	EXPECT_TRUE(waveformHardware->requiresWaveformMem()) ;

	EXPECT_TRUE(waveformHardware->getMaxDepth() > 0) ;
	std::cout << "Max depth=" << waveformHardware->getMaxDepth() << std::endl ;

	// test << overload
	std::cout << "waveformHardware=" << waveformHardware << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformHardwareTest, Capture3072)
{
	std::string error ;

	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform(std::make_shared<Waveform>()) ;
	waveform->setType(IWaveform::WAVEFORM_CAPTURE) ;
	waveform->setDepth(3072) ;

	// Each sample is 2x 16-bit words (I&Q) so the size to be allocated is 2x the depth
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	std::shared_ptr<IWaveformMem> waveformMem(memMgr->allocate(waveform->getDepth() * 2)) ;

	EXPECT_TRUE(waveformHardware->updateSettings(waveform, waveformMem, error)) << error ;

	// get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
	fpgaEmu->reset() ;

	// set the done bit
	fpgaEmu->writeField("waveCaptureDone[0]", 1) ;


	// set up buffer
	std::vector<short> buffer(MAX_BUFF_SAMPLES, 0) ;
	unsigned bufferSize ;

	// prepare waveform memory access for reading
	waveformHardware->readMemoryStart() ;

	bool ok = true ;
	bool endOfFile = false ;
	while (!endOfFile && ok)
	{
		// read memory
		ok = waveformHardware->readMemory( static_cast<short *>(&buffer[0]), bufferSize, MAX_BUFF_SAMPLES, endOfFile, error) ;
		if (!ok)
			std::cerr << "ERROR: " << error << std::endl ;
		ASSERT_TRUE(ok) ;
	}

	EXPECT_TRUE(endOfFile) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(2*3072, bufferSize) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformHardwareTest, Capture3076)
{
	std::string error ;

	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform(std::make_shared<Waveform>()) ;
	waveform->setType(IWaveform::WAVEFORM_CAPTURE) ;
	waveform->setDepth(3076) ;

	// Each sample is 2x 16-bit words (I&Q) so the size to be allocated is 2x the depth
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	std::shared_ptr<IWaveformMem> waveformMem(memMgr->allocate(waveform->getDepth() * 2)) ;

	EXPECT_TRUE(waveformHardware->updateSettings(waveform, waveformMem, error)) << error ;

	// get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
	fpgaEmu->reset() ;

	// set the done bit
	fpgaEmu->writeField("waveCaptureDone[0]", 1) ;


	// set up buffer
	std::vector<short> buffer(MAX_BUFF_SAMPLES, 0) ;
	unsigned bufferSize ;

	// prepare waveform memory access for reading
	waveformHardware->readMemoryStart() ;

	bool ok = true ;
	bool endOfFile = false ;
	while (!endOfFile && ok)
	{
		// read memory
		ok = waveformHardware->readMemory( static_cast<short *>(&buffer[0]), bufferSize, MAX_BUFF_SAMPLES, endOfFile, error) ;
		if (!ok)
			std::cerr << "ERROR: " << error << std::endl ;
		ASSERT_TRUE(ok) ;
	}

	EXPECT_TRUE(endOfFile) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(2*3076, bufferSize) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(WaveformHardwareTest, Capture3073)
{
	std::string error ;

	std::shared_ptr<IWaveformHardware> waveformHardware(new WaveformHardware(0, 0) ) ;

	std::shared_ptr<IWaveform> waveform(std::make_shared<Waveform>()) ;
	waveform->setType(IWaveform::WAVEFORM_CAPTURE) ;
	waveform->setDepth(3073) ;

	// Each sample is 2x 16-bit words (I&Q) so the size to be allocated is 2x the depth
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	std::shared_ptr<IWaveformMem> waveformMem(memMgr->allocate(waveform->getDepth() * 2)) ;

	EXPECT_TRUE(waveformHardware->updateSettings(waveform, waveformMem, error)) << error ;

	// get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
	fpgaEmu->reset() ;

	// set the done bit
	fpgaEmu->writeField("waveCaptureDone[0]", 1) ;


	// set up buffer
	std::vector<short> buffer(MAX_BUFF_SAMPLES, 0) ;
	unsigned bufferSize ;

	// prepare waveform memory access for reading
	waveformHardware->readMemoryStart() ;

	bool ok = true ;
	bool endOfFile = false ;
	while (!endOfFile && ok)
	{
		// read memory
		ok = waveformHardware->readMemory( static_cast<short *>(&buffer[0]), bufferSize, MAX_BUFF_SAMPLES, endOfFile, error) ;
		if (!ok)
			std::cerr << "ERROR: " << error << std::endl ;
		ASSERT_TRUE(ok) ;
	}

	EXPECT_TRUE(endOfFile) ;
	EXPECT_TRUE(ok) ;

	EXPECT_EQ(2*3073, bufferSize) ;
}
