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
#include <time.h>
#include <sys/time.h>

#include "Task.h"
#include "ICarrier.h"
#include "ICarrierServer.h"

#include "Waveform.h"
#include "WaveformMem.h"
#include "WaveformHardware.h"
#include "ICarrierHardware.h"
#include "IHardwareSettings.h"
#include "WaveMemMgr.h"

using namespace Mplane;


//=============================================================================================================
// CLASS GLOBALS
//=============================================================================================================

// Track when we're capturing
Mutex WaveformHardware::mCaptureMutex ;
bool WaveformHardware::mCapturing(false) ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// TODO: Really should move this into the fpga interface, but to have to change the API just for this one value
// seems like too much hassle at the moment!
const unsigned WAVE_WRITE_LO(0x590) ;
const unsigned WAVE_READ_LO(0x594) ;

// these are the limits set inside the fpga
static const unsigned FPGA_MAX_PAIRS_PER_BLOCK_READ	= 1024 ;
static const unsigned FPGA_MIN_PAIRS_PER_BLOCK_READ	= 128 ;

// set ourselves to read half the fpga limit so we can tack any final reads on to the previous block (to ensure we
// don't go below the minimum)
static const unsigned MAX_PAIRS_PER_BLOCK_READ	= FPGA_MAX_PAIRS_PER_BLOCK_READ/2 ;

static const unsigned LOOP_DELAY_USECS	= 1;
static const unsigned TIMEOUT_USECS		= 100;
static const unsigned MAX_LOOP_COUNT	=(TIMEOUT_USECS / LOOP_DELAY_USECS);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardware::WaveformHardware(unsigned index, unsigned port) :

	mWaveIdx(index),
	mPort(port),
	mWaveAccessMutex(),

	mWaveformFpga( IFpgaMgr::getIFpgaWaveformRegs() ),
	mAntennaFpga( IFpgaMgr::getIFpgaAntennaRegs() ),
	mCarrierServer( ICarrierServer::getInstance() ),
	mHardwareData( ICarrierHardwareData::getInstance() ),
	mHardwareSettings( IHardwareSettings::getInstance() ),

	mWaveform(),
	mWaveformMem(),

	mCarrier(nullptr),
	mAirstd(ICarrierHardwareTypes::AIRSTD_UNSET),
	mChbw(ICarrierHardwareTypes::CHBW_UNSET),

	mReadAddr(0),
	mReadEndAddr(0),
	mWriteAddr(0),

	mPresent(mWaveformFpga->read_waveformModulePresent(mWaveIdx))
{
}


//-------------------------------------------------------------------------------------------------------------
WaveformHardware::~WaveformHardware()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::init(std::string& error)
{
	error = "" ;

	// initialise hardware
	mWaveformFpga->write_wavePlaybackEnable(mWaveIdx, 0) ;
	mWaveformFpga->write_waveCaptureEnable(mWaveIdx, 0) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::updateSettings(std::shared_ptr<IWaveform> waveform, std::shared_ptr<IWaveformMem> waveformMem, std::string& error)
{
	error = "" ;

	// Check for presence
	if (!isPresent())
	{
		error = "Waveform hardware not present" ;
		return false ;
	}

	// == update settings ==

	mWaveformMem = waveformMem ;

	// take a *copy* of the current waveform settings
	if (waveform.get() == 0)
		mWaveform = std::shared_ptr<IWaveform>() ;
	else
		mWaveform = std::shared_ptr<IWaveform>(new Waveform(*waveform)) ;

	// skip if waveform null
	if (!mWaveform)
		return true ;

	// set up carrier settings if carrier is set
	ICarrier::Type carrierType(ICarrier::CARRTYPE_NONE) ;
	if (!mWaveform->isCarrierSet())
	{
		mCarrier = nullptr ;
		mAirstd = ICarrierHardwareTypes::AIRSTD_UNSET ;
		mChbw = ICarrierHardwareTypes::CHBW_UNSET ;
	}
	else
	{
		// Get carrier
		if (mWaveform->getCarrierIdx() >= mCarrierServer->getMaxCarriers())
		{
			error = "Invalid carrier" ;
			return false ;
		}
		mCarrier = &(mCarrierServer->getCarrier(mWaveform->getCarrierIdx())) ;

		// Get carrier airstd/chbw
		carrierType = mCarrier->getType() ;
		mAirstd = mHardwareData->getAirStd(mCarrier->getType()) ;
		mChbw = mHardwareData->getChbw(mCarrier->getType()) ;
	}

	// Call method to calculate the sample rate (or return a fixed rate)
	mWaveform->setSampleRateKsps( getInstanceSampleRateKsps(carrierType) ) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::updateHardware(std::string& error)
{
//	std::cerr << "WaveformHardware::updateHardware" << std::endl ;
	error = "" ;

	// Check for presence
	if (!isPresent())
	{
		error = "Waveform hardware not present" ;
		return false ;
	}

	if (!mWaveform)
	{
		error = "Waveform settings not allocated" ;
		return false ;
	}
	if (mWaveformMem.get() == 0)
	{
		error = "Waveform memory not allocated" ;
		return false ;
	}

	// == Now run the type-specific update ==
	switch (mWaveform->getType())
	{
	case Waveform::WAVEFORM_PLAYBACK:
		return updatePlayback(error) ;
		break ;

	case Waveform::WAVEFORM_CAPTURE:
		return updateCapture(error) ;
		break ;

	default:
		return false ;
		break ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::enableHasChanged(bool enable)
{
//	std::cerr << "WaveformHardware::enableHasChanged" << std::endl ;

	// reflect the enable change in the waveform
	if (!mWaveform)
		return ;

	mWaveform->setEnable(enable) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isCaptureWriteError() const
{
	return (mWaveformFpga->read_waveCaptureWriteError(mWaveIdx) != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isCaptureDone() const
{
	return (mWaveformFpga->read_waveCaptureDone(mWaveIdx) != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isPlaybackEnabled() const
{
	return (mWaveformFpga->read_wavePlaybackEnable(mWaveIdx) != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isPlaybackReadError() const
{
	return (mWaveformFpga->read_wavePlaybackReadError(mWaveIdx) != 0) ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::isCapturing()
{
	Mutex::Lock lock(mCaptureMutex) ;
	return mCapturing ;
}


//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::writeMemoryStart()
{
	if (mWaveformMem.get() == 0)
		return ;

	mWriteAddr = mWaveformMem->start() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error)
{
	error = "" ;
	endOfData = false ;

	// check for memory allocated
	if (mWaveformMem.get() == 0)
	{
		error = "Waveform memory not allocated" ;
		return false ;
	}

	// check for valid buffer
	if (bufferSize == 0)
	{
		error = "Zero length buffer" ;
		return false ;
	}

	// Need to mutex protect memory read/write because they're in the system space
	Mutex::Lock lock(mWaveAccessMutex) ;

	// Write interface can take data as fast as we write it

	// Wait until the Waveform_Write_FIFO_Empty bit is high,
	// indicating that the interface is ready to accept a
	// new block of data

	// Check buffer size to see if it will go over the memory size
	const short* bufferEnd(buffer + bufferSize) ;
	unsigned num64(bufferSize / 4) ;
	if (mWriteAddr + num64 > mWaveformMem->end()+1)
	{
		num64 = mWaveformMem->end() - mWriteAddr + 1 ;
		bufferSize = 4 * num64 ;
		bufferEnd = (buffer + bufferSize) ;
	}

//std::cerr << "WRITE addr 0x" << std::hex << mWriteAddr << std::dec << " buff size=" << bufferSize << std::endl ;

	// wait for write fifo empty
	if (!waitWriteFifoEmpty(error))
		return false ;

	// -- Lock fpga mutex --
	mWaveformFpga->mutexLock() ;

	// Program the upper 10 bits of the block's starting address
	// into the WaveformControl_Start_Address_Hi field and the lower 16
	// bits of this address into the WaveformControl_Start_Address_Lo field
	mWaveformFpga->write_nomutex_waveformMemStartAddr(mWriteAddr) ;

	// Program the upper 10 bits of the block's end address + 1
	// (i.e. Start Address plus Length) into the
	// WaveformControl_End_Address_Hi field and the lower 16 bits of
	// this address into the WaveformControl_End_Address_Lo field
	mWriteAddr += num64 ;
	mWaveformFpga->write_nomutex_waveformMemEndAddr(mWriteAddr) ;

//std::cerr << "WRITE end addr 0x" << std::hex << mWriteAddr << std::dec << std::endl ;

	// Set the WaveformControl_Write_Enable bit high
	mWaveformFpga->write_nomutex_waveformWriteEnable(1) ;


	std::shared_ptr<IFpgaKernel> kernel(mWaveformFpga->kernel()) ;


	// Write each pair of 16-bit words to the interface by
	// writing the first word to the WaveformControl_Write_Lo field
	// followed by writing the the second word  to
	// WaveformControl_Write_Hi field

	while (buffer < bufferEnd)
	{
		UINT32 ival = *buffer++ ;
		UINT32 qval = *buffer++ ;

		// Reading the data into an array of 'short' swaps the bytes
		//
		// FILE:
		//  I        Q       I      Q
		// +---+---+---+---+---+---+---+---+ ...
		// | A | B | C | D | E | F | G | H | ...
		// +---+---+---+---+---+---+---+---+ ...
		//
		// short[]:
		//     +---+---+
		// [0] | B | A | I
		//     +---+---+
		// [1] | D | C | Q
		//     +---+---+
		//
		// We need the 32 bit word to end up as:
		// +---+---+---+---+
		// | A | B | C | D |
		// +---+---+---+---+

		// Assemble the 32-bit waveform memory word.
		// The First location of pLocalData goes in the
		// lower 16 bits and the second goes in the upper
		// 16 bits.  Write the whole 32-bit word instead
		// of two 16-bit writes as the interface will
		// not write the data into the FIFO properly if
		// two 16-bit writes are used.
//		UINT32 word( (ival << 16) | qval ) ;
		UINT32 word(0) ;
		word |= (qval >> 8)  & 0xff ;
		word |= (qval << 8)  & 0xff00 ;
		word |= (ival << 8)  & 0xff0000 ;
		word |= (ival << 24) & 0xff000000 ;

		kernel->write32(WAVE_WRITE_LO, word) ;
//		usleep(5);	//TODO: slow down the writes as they seem to fail at full speed
	}

	// After all data has been written set the
	// WaveformControl_Write_Enable bit low to indicate
	// the end of the block to the interface
	mWaveformFpga->write_nomutex_waveformWriteEnable(0) ;

	// -- Un Lock fpga mutex --
	mWaveformFpga->mutexUnLock() ;


	// check for end of data
	if (mWriteAddr >= mWaveformMem->end())
	{
		endOfData = true ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::readMemoryStart()
{
	if (!mWaveformMem)
		return ;

	// start and end points in memory
	mReadAddr = mWaveformMem->start() ;
	mReadEndAddr = mWaveformMem->end() ;

	// Note that the memory is allocated based on the minimum fifo read size of the fifo, so this could well be more samples
	// than have actually been requested via the depth setting. So set the end to the depth setting if it's less
	unsigned depthEnd(mReadAddr + (2*mWaveform->getDepth())) ;
	if (mReadEndAddr > depthEnd)
		mReadEndAddr = depthEnd ;

//#ifdef OFF_TARGET
//	// Limit the wave sizes so the tests run in a decent time
//	if ( (mReadEndAddr - mReadAddr) > 8192)
//		mReadEndAddr = mReadAddr + 8192 ;
//#endif
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::readMemory( short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error)
{
	error = "" ;
	endOfFile = false ;
	bufferSize = 0;

	if (mWaveformMem.get() == 0)
	{
		error = "Waveform memory not allocated" ;
		return false ;
	}

	// Need to mutex protect memory read/write because they're in the system space
	Mutex::Lock lock(mWaveAccessMutex) ;

	// Read interface has a sample fifo - can only grab a fifo's worth at a time

	// Read the requested length a block at a time
	unsigned numOfPairsToRead = maxReadSize/2;

	if (mReadAddr + (numOfPairsToRead/2) > mReadEndAddr)
	{
	    // get the current amount of read memory still left
	    unsigned readMemLeft((mReadEndAddr+1) - mReadAddr) ;

		numOfPairsToRead = readMemLeft * 2 ;
	}

	while (numOfPairsToRead > 0 && mReadAddr <= mReadEndAddr)
	{
		// Determine how many samples to read on this block up to
		// a maximum of MAX_PAIRS_PER_BLOCK_READ.
		unsigned numOfPairsToReadThisBlock(calcNumPairsToRead(numOfPairsToRead)) ;
		numOfPairsToRead -= numOfPairsToReadThisBlock;
		unsigned numOfPairsToReadNextBlock(calcNumPairsToRead(numOfPairsToRead)) ;

		// If the next block read is less than the minimum, then add it to this block's read
		if ( (numOfPairsToReadNextBlock > 0) && (numOfPairsToReadNextBlock < FPGA_MIN_PAIRS_PER_BLOCK_READ) )
		{
			numOfPairsToReadThisBlock += numOfPairsToReadNextBlock ;
			numOfPairsToRead -= numOfPairsToReadNextBlock;
		}

		// -- Lock fpga mutex --
		mWaveformFpga->mutexLock() ;

		// Program the upper 10 bits of the block's starting address
		// into the Waveform_Start_Address_Hi field and the lower 16
		// bits of this address into the Waveform_Start_Address_Lo field
		mWaveformFpga->write_nomutex_waveformMemStartAddr(mReadAddr) ;

		// Program the upper 10 bits of the block's end address + 1
		// (i.e. Start Address plus Length) into the
		// Waveform_End_Address_Hi field and the lower 16 bits of
		// this address into the Waveform_End_Address_Lo field
		mReadAddr += numOfPairsToReadThisBlock / 2 ;
		mWaveformFpga->write_nomutex_waveformMemEndAddr(mReadAddr) ;

		// Program the read length in 128-bit words so divide
		// the number of pairs by 4 and round up.
		unsigned waveformReadLength = numOfPairsToReadThisBlock / 4 ;
		if (numOfPairsToReadThisBlock & 3)
		{
			waveformReadLength++;
		}

		// NOTE: Read length needs to be LENGTH-1
		mWaveformFpga->write_nomutex_waveformReadLength(waveformReadLength - 1) ;

		// start read - need to wait for fifo to fill
		mWaveformFpga->write_nomutex_waveformReadEnable(1) ;

#ifndef OFF_TARGET
		// Wait for data available to read - should be ready immediately
		bool done = false ;
		unsigned waitCount = 10 ;
		while ( (waitCount > 0) && !done)
		{
			done = (mWaveformFpga->read_nomutex_waveformReadFifoEmpty() == 0) ;
			--waitCount ;
		}
#else
		bool done = true ;
#endif

		// Check for error
		if (!done)
		{
			std::cerr << "readMemory: not done - fifo empty = " <<
					mWaveformFpga->read_nomutex_waveformReadFifoEmpty() << std::endl ;
			error = "Waveform read fifo not done" ;
			return false ;
		}


		std::shared_ptr<IFpgaKernel> kernel(mWaveformFpga->kernel()) ;

		// Read out the data
		bufferSize += numOfPairsToReadThisBlock*2 ;
		while (numOfPairsToReadThisBlock--)
		{
			UINT32 word ;
			kernel->read32(WAVE_READ_LO, &word) ;

//			short qval(word & 0xffff) ;
//			short ival( (word >> 16) & 0xffff) ;

			short qval( (word >> 8) & 0xff ) ;
			qval |= (word << 8) & 0xff00 ;

			short ival( (word >> 24) & 0xff) ;
			ival |= (word >> 8) & 0xff00 ;

			*buffer++ = ival ;
			*buffer++ = qval ;
		}

		// completed read
		mWaveformFpga->write_nomutex_waveformReadEnable(0) ;

		// -- Un Lock fpga mutex --
		mWaveformFpga->mutexUnLock() ;

	} // end while (numOfPairsToRead > 0)

	// check for end of file
	if (mReadAddr >= mReadEndAddr)
		endOfFile = true ;

	return true ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::validate(std::string& error) const
{
	error = "" ;

	// Check for presence
	if (!isPresent())
	{
		error = "Waveform hardware not present" ;
		return false ;
	}

	if (!mWaveform)
	{
		error = "Internal error - Waveform hardware has no waveform settings" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::checkCarrier(std::string& error) const
{
	error = "" ;

	// check carrier is actually set
	if (!mWaveform->isCarrierSet())
	{
		error = "Carrier not specified" ;
		if (mWaveform->getType() == Waveform::WAVEFORM_CAPTURE)
			error = "Must specify carrier" ;

		return false ;
	}

	// check carrier settings
	if (mAirstd == ICarrierHardwareTypes::AIRSTD_UNSET || mChbw == ICarrierHardwareTypes::CHBW_UNSET)
	{
		error = "Carrier not configured" ;
		return false ;
	}

	// check carrier index
	if (mWaveform->getCarrierIdx() >= mCarrierServer->getMaxCarriers())
	{
		error = "Invalid carrier index" ;
		return false ;
	}

	// Calculate the sample rate
	std::shared_ptr<ICarrierHardwareData> carrierHardwareData(ICarrierHardwareData::getInstance()) ;
	const SampleRate* sampleRate = carrierHardwareData->getSampleRate(mHardwareSettings->getClktype(), mAirstd, mChbw) ;
	if (!sampleRate)
	{
		error = "Unable to determine sample rate setting" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::requiresWaveformMem(void) const
{
	// The standard WaveformHardware requires memory to be allocated for waveform transfer
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getMaxDepth(void) const
{
	// Return the waveform memory size
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	return memMgr->getMemSize() ;
}

//-------------------------------------------------------------------------------------------------
const unsigned WaveformHardware::getCaptureTime(void) const
{
	if (mWaveform->isCarrierSet())
	{
		std::shared_ptr<ICarrierHardwareData> carrierHardwareData(ICarrierHardwareData::getInstance()) ;
		return carrierHardwareData->calcSampleDelay(
			mHardwareSettings->getClktype(),
			mAirstd,
			mChbw,
			mWaveform->getDepth()
		) ;
	}

	// use specified sample rate
	unsigned delay_ms(mWaveform->getCaptureEndMs()) ;

	// allow an extra 2x10ms frames
	delay_ms += 20 ;

	return static_cast<unsigned>(delay_ms) ;
}


//-------------------------------------------------------------------------------------------------
void WaveformHardware::captureInit(void)
{
	// Dummy read of the capture write error bit
	// to clear it prior to the new capture
	mWaveformFpga->read_waveCaptureWriteError(mWaveIdx) ;

	// Need to ensure we generate a falling edge to clear out any previous DONE flag
	mWaveformFpga->write_waveCaptureEnable(mWaveIdx, 0) ;
	mWaveformFpga->write_waveCaptureEnable(mWaveIdx, mWaveform->isEnable() ) ;

}



//-------------------------------------------------------------------------------------------------
void WaveformHardware::show(std::ostream& os) const
{
	os << "WaveformHardware " << std::endl ;
	os << "   * Index...........: " << mWaveIdx << std::endl ;
	os << "   * Present.........: " << isPresent() << std::endl ;
	os << "   * Waveform........: " << mWaveform << std::endl ;
	os << "   * Memory..........: " << mWaveformMem << std::endl ;
	os << "   * Read Address....: 0x" << std::hex << mReadAddr << std::dec << std::endl ;
	os << "   * Write Address...: 0x" << std::hex << mWriteAddr << std::dec ;

	//	mCarrier(0),
	//	mAirstd(ICarrierHardwareTypes::AIRSTD_UNSET),
	//	mChbw(ICarrierHardwareTypes::CHBW_UNSET),
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::showWaveformReg(std::ostream& os) const
{
	os << "-----------------------------------" << std::endl ;
	os << "Wave w" << mWaveIdx << std::hex << std::endl ;

	UINT16 type = mWaveformFpga->read_waveformModuleType(mWaveIdx) ;
	os << "Type.................: " << (type == 0 ? "PLAYBACK" : "CAPTURE") << std::endl ;
	os << "Start Address........: 0x" << mWaveformFpga->read_waveStartAddr(mWaveIdx) << std::endl ;
	os << "End Address..........: 0x" << mWaveformFpga->read_waveEndAddr(mWaveIdx) << std::endl ;
	os << "Playback Enable......: 0x" << mWaveformFpga->read_wavePlaybackEnable(mWaveIdx) << std::endl ;
	os << "Capture Enable.......: 0x" << mWaveformFpga->read_waveCaptureEnable(mWaveIdx) << std::endl ;
	os << "Capture Done.........: 0x" << mWaveformFpga->read_waveCaptureDone(mWaveIdx) << std::endl ;
	os << "Capture Length.......: 0x" << mWaveformFpga->read_waveCaptureLen(mWaveIdx) << std::endl ;
	os << "Trigger..............: 0x" << mWaveformFpga->read_waveStartAirframe(mWaveIdx) << std::endl ;
	os << "Playback Read Error..: 0x" << mWaveformFpga->read_wavePlaybackReadError(mWaveIdx) << std::endl ;
	os << "Capture Write Error..: 0x" << mWaveformFpga->read_waveCaptureWriteError(mWaveIdx) << std::endl ;
	os << "Sample Rate N........: 0x" << mWaveformFpga->read_waveSampleRateN(mWaveIdx) << std::endl ;
	os << "Sample Rate A........: 0x" << mWaveformFpga->read_waveSampleRateA(mWaveIdx) << std::endl ;
	os << "Sample Rate B........: 0x" << mWaveformFpga->read_waveSampleRateB(mWaveIdx) << std::endl ;

	os << std::dec << std::endl ;
}



//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::showWaveformMasterReg(std::ostream& os) const
{
	os << "-----------------------------------" << std::endl ;
	os << "Master Control" << std::hex << std::endl ;
	os << "Master Playback Enable....: 0x" << mWaveformFpga->read_masterPlaybackEnable() << std::endl ;
	os << "Master Capture Enable.....: 0x" << mWaveformFpga->read_masterCaptureEnable() << std::endl ;

	auto fpgaSys(IFpgaMgr::getIFpgaSystemRegs()) ;
	os << "DAC Input Select..........: 0x" << fpgaSys->read_dacInputSel() << std::endl ;

	os << std::dec << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::shutdown(std::string& error)
{
	error = "" ;

	// skip if not allocated
	if (!mWaveform)
		return true ;

	if (mWaveformFpga->read_waveCaptureEnable(mWaveIdx) != 0)
		mWaveformFpga->write_waveCaptureEnable(mWaveIdx, 0) ;

	if (mWaveformFpga->read_wavePlaybackEnable(mWaveIdx) != 0)
		mWaveformFpga->write_wavePlaybackEnable(mWaveIdx, 0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::usesFpgaBus() const
{
	// defauult is for the wave module to use the fpga bus
	return true ;
}


//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getIndex(void) const
{
	return mWaveIdx ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::isPresent() const
{
	return mPresent ;
}

//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getNumBytes(void) const
{
	// skip if not allocated
	if (!mWaveform)
		return 0 ;

	// Normal operation is Depth x 16-bit I x 16-bit Q
	return mWaveform->getDepth() * 4 ;
}

//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getSampleRateKsps() const
{
	// skip if not allocated
	if (!mWaveform)
		return 0 ;

	return mWaveform->getSampleRateKsps() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveform> WaveformHardware::getWaveform() const
{
	return mWaveform ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformMem> WaveformHardware::getWaveformMem() const
{
	return mWaveformMem ;
}


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardware::calcCarrierSampleRateKsps(ICarrier::Type type)
{
	// If NONE use default
	if (type == ICarrier::CARRTYPE_NONE)
		return 61440 ;

	// Do calculation
	std::shared_ptr< ICarrierHardwareData> hardwareData( ICarrierHardwareData::getInstance() ) ;

	AirstdType airstd( hardwareData->getAirStd(type) ) ;
	ChbwType chbw( hardwareData->getChbw(type) ) ;

	std::shared_ptr<const IHardwareSettings> hardwareSettings( IHardwareSettings::getInstance() ) ;
	const SampleRate* sampleRate = hardwareData->getSampleRate(
			hardwareSettings->getClktype(), airstd, chbw) ;
	if (!sampleRate)
		return 0 ;

	return static_cast<unsigned>(sampleRate->rate_ksps) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::initMaster(std::string& error)
{
	error = "" ;
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	// Disable the capture bit
	waveformFpga->write_masterCaptureEnable(0) ;
	setCapturingState(false) ;

	// Disable the playback bit
	waveformFpga->write_masterPlaybackEnable(0) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::startAllCapture(bool playbackEnable,
	std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList,
	std::string& error)
{
	error = "" ;
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	// Disable the master capture enable bit as it needs
	// a rising edge to start a capture
	waveformFpga->write_masterCaptureEnable(0) ;

	unsigned numCapture ;
	unsigned numPlayback ;
	countEnabled(waveformHardwareList, numCapture, numPlayback) ;

	// Calculate the timeout based on the maximum capture
	// depth and sample rate of all waveform modules enabled
	// to capture
	unsigned maxCaptureTime_msec = 0;
	for (std::vector< std::shared_ptr<IWaveformHardware> >::const_iterator iter(waveformHardwareList.begin()); iter != waveformHardwareList.end(); ++iter)
	{
		if ( (*iter)->getWaveform().get() == 0)
			continue ;

		if ( !(*iter)->getWaveform()->isEnable() )
			continue ;

		if ( (*iter)->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;

		// init ready for capture
		(*iter)->captureInit() ;

		// get capture time
		unsigned captureTime_msec = (*iter)->getCaptureTime() ;

		// calc longest capture period
		if (captureTime_msec > maxCaptureTime_msec)
			maxCaptureTime_msec = captureTime_msec;
	}

	// gate playback enable with the count of currently enabled playback waveforms - if none enabled then playback
	// is disabled
	if (numPlayback == 0)
		playbackEnable = false ;

	// Rewrite all the start and end addresses for enabled plabyack
	// modules so that the playback begins from the start of the data,
	// but only if playback is currently disabled
	UINT16 currentPlaybackEnabled = waveformFpga->read_masterPlaybackEnable() ;
	if (playbackEnable && !currentPlaybackEnabled)
	{
		// enabling
		if (!setAllWaveformMem(waveformHardwareList))
			return false ;
	}

	// set flag
	setCapturingState(true) ;

	// Enable the capture and possibly playback in a single write
	FpgaVal enableReg = waveformFpga->read_masterPlaybackCaptureReg() ;
	waveformFpga->write_masterCaptureEnable(&enableReg, 1) ;
	waveformFpga->write_masterPlaybackEnable(&enableReg, (playbackEnable ? 1 : 0) ) ;
	waveformFpga->write_masterPlaybackCaptureReg(enableReg) ;

	// Wait for capture to finish and report any timeouts
	if (!waitCapturesDone(waveformHardwareList, maxCaptureTime_msec, error))
		return false ;

	// clear flag
	setCapturingState(false) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::startAllPlayback(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error)
{
	error = "" ;

	// Rewrite all the start and end addresses for enabled playback
	// modules so that the playback begins from the start of the data
	if (!setAllWaveformMem(waveformHardwareList))
		return false ;

	// Enable the playback bit
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;
	waveformFpga->write_masterPlaybackEnable(1) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::stopAllCapture(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error)
{
	error = "" ;

	// Disable the capture bit
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;
	waveformFpga->write_masterCaptureEnable(0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::stopAllPlayback(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, std::string& error)
{
	error = "" ;

	// Disable the playback bit
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;
	waveformFpga->write_masterPlaybackEnable(0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isMasterPlaybackEnabled()
{
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;
	return (waveformFpga->read_masterPlaybackEnable() != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::isMasterCaptureEnabled()
{
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;
	return (waveformFpga->read_masterCaptureEnable() != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::microSleep(unsigned microsecs)
{
#ifndef OFF_TARGET
	struct timespec ts = {0};
	ts.tv_sec = 0;
	ts.tv_nsec = microsecs * 1000;
	nanosleep(&ts, (struct timespec *)0);
#endif
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::setPresent(bool present)
{
	mPresent = present ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::updateCapture(std::string& error)
{
	error = "" ;

	UINT16 captureEnabled = mWaveformFpga->read_waveCaptureEnable(mWaveIdx) ;

	// Nothing can change if the capture is enabled and we're currently capturing
	if (!captureEnabled || !isCapturing())
	{
		// Program the start and end addresses
		if ( !setWaveformMem() )
		{
			error = "Unable to set memory addresses" ;
			return false ;
		}

		// Program the capture depth
		if ( !setCaptureDepth(mWaveform->getDepth()) )
		{
			error = "Unable to set depth" ;
			return false ;
		}

		// Program the airframe count to trigger the capture
		if ( !setCaptureTrigger(mWaveform->getDelayedTrigger()) )
		{
			error = "Unable to set trigger" ;
			return false ;
		}
	}

	// Program the capture enable
	mWaveformFpga->write_waveCaptureEnable(mWaveIdx, mWaveform->isEnable()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::updatePlayback(std::string& error)
{
	error = "" ;

	// Program the playback gain where 1.0 is unity
	// TO DO
	// waveform_set_playback_gain(mrc,waveformp);

	// Only the gain can change while the waveform is already enabled
	UINT16 playbackEnabled = mWaveformFpga->read_wavePlaybackEnable(mWaveIdx) ;
	if (!playbackEnabled)
	{
		// Program the start and end addresses
		if ( !setWaveformMem() )
		{
			error = "Unable to set memory addresses" ;
			return false ;
		}

		// Program the playback sample rate
		if ( !setPlaybackSamplerate() )
		{
			error = "Unable to set sample rate" ;
			return false ;
		}

		// Program the scaling value
		if( !setPlaybackScalingValue() )
		{
            error = "Unable to set scaling value" ;
            return false ;
		}

		// Program the airframe count to trigger the capture
		if ( !setPlaybackTrigger(mWaveform->getTrigger()) )
		{
			error = "Unable to set trigger" ;
			return false ;
		}

	}

	// Program the playback enable
	mWaveformFpga->write_wavePlaybackEnable(mWaveIdx, mWaveform->isEnable()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setWaveformMem()
{
	// Program the start and end addresses based on the waveform
	// memory address and depth
	if (mWaveformMem.get() == 0)
		return false ;

	if (mWaveform->getDepth() == 0)
		return false ;

	mWaveformFpga->write_waveStartAddr(mWaveIdx, mWaveformMem->start()) ;
	mWaveformFpga->write_waveEndAddr(mWaveIdx, mWaveformMem->end()+1) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setCaptureDepth(unsigned depth)
{
	mWaveformFpga->write_waveCaptureLen(mWaveIdx, depth) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setCaptureTrigger(unsigned trigger)
{
	// Program the airframe count to trigger the module
	// TODO - Compensate for delays
	int delayCompensatedTrigger = static_cast<int>(trigger) - 2;

	return setTrigger(delayCompensatedTrigger);
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setPlaybackTrigger(unsigned trigger)
{
	// Program the airframe count to trigger the module
	// TODO - Compensate for delays
	int delayCompensatedTrigger = static_cast<int>(trigger) - 2;

	return setTrigger(delayCompensatedTrigger);
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setTrigger(int airframeCountToTrigger)
{
	if (airframeCountToTrigger < 0)
	{
		airframeCountToTrigger += 307200;
	}

	// Program the airframe count to trigger the module
	mWaveformFpga->write_waveStartAirframe(mWaveIdx, airframeCountToTrigger) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardware::setPlaybackSamplerate()
{
	// Calculate the sample rate
	std::shared_ptr<ICarrierHardwareData> carrierHardwareData(ICarrierHardwareData::getInstance()) ;
	const SampleRate* sampleRate = carrierHardwareData->getSampleRate(mHardwareSettings->getClktype(), mAirstd, mChbw) ;
	if (!sampleRate)
		return false ;

	// Program this waveform module to the proper sample rate
	// for the airstd/chbw
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

	waveformFpga->write_waveSampleRateN(mWaveIdx, sampleRate->integral) ;
	waveformFpga->write_waveSampleRateA(mWaveIdx, sampleRate->numerator) ;
	waveformFpga->write_waveSampleRateB(mWaveIdx, sampleRate->denominator) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::setPlaybackScalingValue()
{
    unsigned scalingValue = calcScalingValue();

    // Program this waveform module to the proper playback scaling
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

    waveformFpga->write_wavePlaybackScaling(mWaveIdx, scalingValue);
    return true;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::waitWriteFifoEmpty(std::string& error)
{
	unsigned loop_count = 0 ;
	bool done ;
	do
	{
		if (loop_count > 0)
			microSleep(LOOP_DELAY_USECS) ;
		++loop_count ;

		// Now check for WaveformControl_Write_FIFO_Empty

#ifndef OFF_TARGET
		done = (mWaveformFpga->read_waveformWriteFifoEmpty() == 1) ;
#else
		done = 1 ;
#endif
	} while (!done && (loop_count < MAX_LOOP_COUNT)) ;

	// Check for error
	if (done == 0)
	{
		error = "Waveform write fifo not ready" ;
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------
bool WaveformHardware::waitReadFifoNotEmpty(std::string& error)
{
	// Wait until the Waveform_Read_FIFO_Empty bit is low,
	// indicating that the interface has data available to read
	unsigned loop_count = 0 ;
	bool done ;
	do
	{
#ifndef OFF_TARGET
		done = (mWaveformFpga->read_nomutex_waveformReadFifoEmpty() == 0) ;
#else
		done = true ;
#endif
		if (done)
			break ;

		++loop_count ;
		microSleep(LOOP_DELAY_USECS) ;

		// Now check for Waveform Read FIFO Not Empty

	} while (!done && (loop_count < MAX_LOOP_COUNT)) ;


	// Check for error
	if (!done)
	{
		error = "Waveform read fifo not done" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardware::calcScalingValue( void )
{
    float scalingGain = (float)mWaveform->getScalingGain();

    // Calculate the scaling value from the supplied gain. Unity is 4096
    UINT16 scalingValue = (4096 * pow(10, (scalingGain/20)));

    return static_cast<unsigned>(scalingValue) ;
}

//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::calcNumPairsToRead(unsigned numOfPairsToRead) const
{
	unsigned numOfPairsToReadThisBlock = numOfPairsToRead;
	if (numOfPairsToRead > (MAX_PAIRS_PER_BLOCK_READ - 4))
		numOfPairsToReadThisBlock = MAX_PAIRS_PER_BLOCK_READ;

	if (mReadAddr + (numOfPairsToReadThisBlock/2) > mReadEndAddr)
		numOfPairsToReadThisBlock = ((mReadEndAddr+1) - mReadAddr) * 2 ;

	return numOfPairsToReadThisBlock ;
}

//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	// Default behaviour is to just use the carrier information and calculate rate based on that
	return calcCarrierSampleRateKsps(carrierType) ;
}

//=============================================================================================================
// PROTECTED STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void WaveformHardware::countEnabled(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList, unsigned& numCapture, unsigned& numPlayback)
{
	numCapture = 0 ;
	numPlayback = 0 ;
	for (std::vector< std::shared_ptr<IWaveformHardware> >::const_iterator iter(waveformHardwareList.begin()); iter != waveformHardwareList.end(); ++iter)
	{
		if ( (*iter)->getWaveform().get() == 0)
			continue ;

		if ( !(*iter)->getWaveform()->isEnable() )
			continue ;

		// count
		if ( (*iter)->getWaveform()->getType() == Waveform::WAVEFORM_CAPTURE )
			++numCapture ;
		else if ( (*iter)->getWaveform()->getType() == Waveform::WAVEFORM_PLAYBACK )
			++numPlayback ;
	}
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::setAllWaveformMem(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList)
{
	for (std::vector< std::shared_ptr<IWaveformHardware> >::iterator iter(waveformHardwareList.begin()); iter != waveformHardwareList.end(); ++iter)
	{
		if ( (*iter)->getWaveform().get() == 0)
			continue ;

		// if it's enabled for playback then set the waveform address
		if ( (*iter)->getWaveform()->getType() != Waveform::WAVEFORM_PLAYBACK )
			continue ;
		if ( !(*iter)->getWaveform()->isEnable() )
			continue ;

		if ( !(*iter)->setWaveformMem() )
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------
bool WaveformHardware::waitCapturesDone(std::vector< std::shared_ptr<IWaveformHardware> >& waveformHardwareList,
		unsigned maxCaptureTime_msec, std::string& error)
{
	auto waveformFpga(IFpgaMgr::getIFpgaWaveformRegs()) ;

//	const unsigned LOOP_DELAY_USECS(100) ;
//	const unsigned LOOP_DELAY_NSECS(1000 * LOOP_DELAY_USECS) ;
//	unsigned maxLoopCount = (2 * maxCaptureTime_nsec / LOOP_DELAY_NSECS) + 50;
	unsigned maxLoopCount = 2 * (maxCaptureTime_msec + 1);
	unsigned loop_count = 0;
	bool done;

	//Get start time
	unsigned long currentTime, startTime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	startTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	do
	{
		if (loop_count > 0)
//			microSleep(LOOP_DELAY_USECS) ;
			Task::msSleep(1) ;
		++loop_count ;

		// Now check all the capture dones
		done = true ;
		for (std::vector< std::shared_ptr<IWaveformHardware> >::const_iterator iter(waveformHardwareList.begin());
				iter != waveformHardwareList.end(); ++iter)
		{
			if ( (*iter)->getWaveform().get() == 0)
				continue ;

			if ( !(*iter)->getWaveform()->isEnable() )
				continue ;

			if ( (*iter)->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
				continue ;

			done &= (*iter)->isCaptureDone();
		}
	#ifdef OFF_TARGET
		done = true ;
	#endif

	} while (!done && (loop_count < maxLoopCount)) ;

	gettimeofday(&tv, NULL);
	currentTime = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	if (!done)
	{
		std::stringstream ss ;
		ss << "Capture done not complete for Waveform index: " ;

		unsigned numNotDone=0;
		for (std::vector< std::shared_ptr<IWaveformHardware> >::const_iterator iter(waveformHardwareList.begin());
				iter != waveformHardwareList.end(); ++iter)
		{
			if ( (*iter)->getWaveform().get() == 0)
				continue ;

			if ( !(*iter)->getWaveform()->isEnable() )
				continue ;

			if ( (*iter)->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
				continue ;

			if (! (*iter)->isCaptureDone() )
			{
				if (numNotDone++ > 0)
					ss << "," ;
				ss << " " << (*iter)->getIndex() ;
			}
		}
		ss << " in " << (currentTime - startTime) << " ms";
		error = ss.str() ;
	}
	else
	{
		std::stringstream ss ;
		ss << "Capture done in " << (currentTime - startTime) << " ms";
		ILoggable::logEventInfo(ss.str());
	}

	return (done) ;
}

//-------------------------------------------------------------------------------------------------
unsigned WaveformHardware::getMaxPairsPerBlockRead(void)
{
	return MAX_PAIRS_PER_BLOCK_READ ;
}

//-------------------------------------------------------------------------------------------------
void WaveformHardware::setCapturingState(bool capturing)
{
	Mutex::Lock lock(mCaptureMutex) ;
	mCapturing = capturing ;
}
