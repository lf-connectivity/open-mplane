/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareDpdAdcDpdAdc.cpp
 * \brief     Waveform Hardware for DPD ADC capture
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <time.h>

#include "ICarrier.h"
#include "ICarrierServer.h"

#include "Maths.h"
#include "Waveform.h"
#include "WaveformMem.h"
#include "WaveformHardwareDpdAdc.h"
#include "IHardwareSettings.h"

#include "ILoggable.h"

using namespace Mplane;



//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const unsigned SrxSampleRateKsps{491520} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardwareDpdAdc::WaveformHardwareDpdAdc(unsigned index, unsigned port) :
	WaveformHardware(index, port),
	mMaxCaptureDepth(0)
{
	// Read the register and calculate the actual maximum depth
	unsigned captureDepth(static_cast<unsigned>(mWaveformFpga->read_dpdadcCaptureDepth())) ;
	mMaxCaptureDepth = captureDepth * 64 * 1024 ;

	// if capture depth is set to non-zero then hardware is present
	if (captureDepth > 0)
		setPresent(true) ;
	else
		setPresent(false) ;
}


//-------------------------------------------------------------------------------------------------------------
WaveformHardwareDpdAdc::~WaveformHardwareDpdAdc()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::init(std::string& error)
{
	error = "" ;

	// initialise hardware - falling edge of enable ensures done bit is clear
	mWaveformFpga->write_dpdadcCaptureEnable(1) ;
	mWaveformFpga->write_dpdadcCaptureEnable(0) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::updateSettings(
	std::shared_ptr<IWaveform> waveform,
	std::shared_ptr<IWaveformMem> waveformMem,
	std::string& error)
{
	error = "" ;

	// == update settings ==

	mWaveformMem = waveformMem ;

	// take a *copy* of the current waveform settings
	if (waveform.get() == 0)
		mWaveform = std::shared_ptr<IWaveform>() ;
	else
		mWaveform = std::shared_ptr<IWaveform>(new Waveform(*waveform)) ;

	// skip if waveform null
	if (mWaveform.get() == 0)
		return true ;

	// Ensure sample rate is correct
	mWaveform->setSampleRateKsps(SrxSampleRateKsps) ;

	setStreaming(mWaveform->getStreaming());

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::updateHardware(std::string& error)
{
	error = "" ;

	if (mWaveform.get() == 0)
	{
		error = "Waveform settings not allocated" ;
		return false ;
	}
	if (mWaveformMem)
	{
		error = "Internal error - Waveform memory allocated for DPD ADC" ;
		return false ;
	}

	if (mWaveform->getType() != Waveform::WAVEFORM_CAPTURE)
	{
		error = "DPD ADC waveform must be used in capture mode" ;
		return false ;
	}

	return updateCapture(error) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::isCaptureWriteError() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::isCaptureDone() const
{
	return (mWaveformFpga->read_dpdadcCaptureDone() != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::isPlaybackEnabled() const
{
	// no playback
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::isPlaybackReadError() const
{
	// no playback
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::writeMemoryStart()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error)
{
	error = "Memory write not supported for DPD ADC capture" ;
	return false ;
}


//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::readMemoryStart()
{
	// Toggle the CalRxAdcCaptureReadReset bit to reset the read
	// address of the memory
	mWaveformFpga->write_dpdadcCaptureReadReset(0) ;
	mWaveformFpga->write_dpdadcCaptureReadReset(1) ;

	// use the "read address" as a counter
	mReadAddr = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::readMemory( short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error)
{
	error = "" ;
	endOfFile = false ;
	bufferSize = 0;

	// Read interface has a sample fifo - can only grab a fifo's worth at a time

	// -- Lock fpga mutex --
	mWaveformFpga->mutexLock() ;

	// Read the requested length a block at a time
	unsigned numOfSamplesToRead = maxReadSize;
	while (numOfSamplesToRead > 0 && mReadAddr < mWaveform->getDepth())
	{
		// Determine how many samples to read on this block up to
		// a maximum of MAX_PAIRS_PER_BLOCK_READ.

		unsigned numOfSamplesToReadThisBlock = numOfSamplesToRead;
		if (numOfSamplesToReadThisBlock + mReadAddr >= mWaveform->getDepth())
			numOfSamplesToReadThisBlock = mWaveform->getDepth() - mReadAddr;
		numOfSamplesToRead -= numOfSamplesToReadThisBlock;
		mReadAddr += numOfSamplesToReadThisBlock ;

		// Read out the data
		bufferSize += numOfSamplesToReadThisBlock ;
		while (numOfSamplesToReadThisBlock--)
		{
			short adcData = static_cast<short>(mWaveformFpga->read_nomutex_dpdadcCaptureData()) ;
			*buffer++ = adcData ;
		}


	} // end while (numOfSamplesToRead > 0)

	// check for end of file
	if (mReadAddr >= mWaveform->getDepth())
	{
		endOfFile = true ;
	}

	// -- Un Lock fpga mutex --
	mWaveformFpga->mutexUnLock() ;

	return true ;
}


//-------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::checkCarrier(std::string& error) const
{
	// Carrier not required
	error = "" ;
	return true ;
}

//-------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::show(std::ostream& os) const
{
	os << "WaveformHardwareDpdAdc " << std::endl ;
	os << "   * Index...........: " << mWaveIdx << std::endl ;
	os << "   * Max Depth.......: " << mMaxCaptureDepth << std::endl ;
	os << "   * Waveform........: " << mWaveform << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::showWaveformReg(std::ostream& os) const
{
	os << "-----------------------------------" << std::endl ;
	os << "Wave wrxcal (" << mWaveIdx << ")" << std::hex << std::endl ;
	os << "Capture Enable.......: 0x" << mWaveformFpga->read_dpdadcCaptureEnable() << std::endl ;
	os << "Capture Done.........: 0x" << mWaveformFpga->read_dpdadcCaptureDone() << std::endl ;
	os << "Capture Trigger......: 0x" << mWaveformFpga->read_dpdadcCaptureTrigger() << std::endl ;
	os << "Capture Depth........: 0x" << mWaveformFpga->read_dpdadcCaptureDepth() << std::endl ;

	os << std::dec << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::requiresWaveformMem(void) const
{
	// Uses dedicated BlockRAM in the Xilinx fpga so no need to allocate memory
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareDpdAdc::getMaxDepth(void) const
{
	return mMaxCaptureDepth ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::showWaveformMasterReg(std::ostream& os) const
{
	this->super::showWaveformMasterReg(os) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::shutdown(std::string& error)
{
	error = "" ;

	// skip if not allocated
	if (mWaveform.get() == 0)
		return true ;

	if (mWaveformFpga->read_dpdadcCaptureEnable() != 0)
		mWaveformFpga->write_dpdadcCaptureEnable(0) ;

	mWaveformFpga->write_dpdadcCaptureStreamEnable(0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::captureInit(void)
{
	// Need to ensure we generate a falling edge to clear out any previous DONE flag
	mWaveformFpga->write_dpdadcCaptureEnable(0) ;
	mWaveformFpga->write_dpdadcCaptureEnable( mWaveform->isEnable() ) ;
	mWaveformFpga->write_dpdadcCaptureStreamEnable(0) ;
	mWaveformFpga->write_dpdadcCaptureStreamEnable( mWaveform->getStreaming() ) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::WaveformHardwareDpdAdc::getNumBytes(void) const
{
	// skip if not allocated
	if (!mWaveform)
		return 0 ;

	// Here the number of bytes is Depth x 16-bit val
	return mWaveform->getDepth() * 2 ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::usesFpgaBus() const
{
	// Uses internal bus
	return false ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::updateCapture(std::string& error)
{
	error = "" ;

	UINT16 captureEnabled = mWaveformFpga->read_dpdadcCaptureEnable() ;

	// Nothing can change if the capture is enabled and we're currently capturing
	if (!captureEnabled || !isCapturing())
	{
		// Program the airframe count to trigger the capture
		if ( !setCaptureTrigger(mWaveform->getTrigger()) )
		{
			error = "Unable to set trigger" ;
			return false ;
		}
	}

	//Now configure the averaging length. The number of samples to average should match the capture depth
	// (in terms of complex pairs) - 2

	//waveform set is total samples either I or Q, the length Reg is in IQ pairs!!!!!
	int nFPGALength = (mWaveform->getDepth() / 2) - 2;
	mWaveformFpga->write_dpdadcCaptureAveDepth(nFPGALength) ;

	//Trigger position
	int tsTrigger = (int)fround(307200.0 * (float)mWaveform->getTrigger() / 10.0);
	if (tsTrigger < 0) tsTrigger += 307200;
	mWaveformFpga->write_dpdadcCaptureAveTrigger(tsTrigger) ;

	//Now set the decimation rate and number of averages
	unsigned decimation = 1;
	switch (mWaveform->getDecimation())
	{
		case IWaveform::DECIMATE_NONE:  decimation = 1; break;
		case IWaveform::DECIMATE_BY_2:  decimation = 2; break;
		case IWaveform::DECIMATE_BY_4:  decimation = 4; break;
		case IWaveform::DECIMATE_BY_8:  decimation = 8; break;
		case IWaveform::DECIMATE_BY_16: decimation = 16; break;
		case IWaveform::DECIMATE_BY_32: decimation = 32; break;
		case IWaveform::DECIMATE_BY_64: decimation = 64; break;
		case IWaveform::DECIMATE_BY_1024: decimation = 1024; break;

		default:
			decimation = 1 ;
			break ;
	}

	//Throttle control for settings that will break the 100Mb interface
	// bypass throttle if decimate by 1024
	unsigned throttle = 0;
	if (mWaveform->getDecimation() != IWaveform::DECIMATE_BY_1024)
	{
		double speed = (245.76 * 32) / (float)(decimation * mWaveform->getAveraging());
		if (speed > 63.0)
		{
			throttle = (unsigned)(speed / 63.0 + 0.5) - 1 ;
			if (throttle > 15) throttle = 15 ;
		}
	}

	//Program the decimation/throttle/averaging register
	mWaveformFpga->write_dpdadcCaptureDecimation( (unsigned)mWaveform->getDecimation() + 1) ;
	mWaveformFpga->write_dpdadcCaptureThrottle(throttle) ;
	mWaveformFpga->write_dpdadcCaptureAveNumCapt(mWaveform->getAveraging()) ;


	//Program the Tuner according to the required Freq Offset
//    int tuningWord = (int)fround((mWaveform->getNco() / 245.760000) * 2147483648);

	uint32_t tuningWord = (uint32_t)fround((mWaveform->getNco() / 245.760000) * 4294967296u);
	auto fpgaSys(IFpgaMgr::getIFpgaSystemRegs()) ;
	fpgaSys->write_calRxTunerNcoHi( (UINT16)((tuningWord & 0xFFFF0000) >> 16) );
	fpgaSys->write_calRxTunerNcoLo( (UINT16)(tuningWord & 0x0000FFFF) );

    ILoggable::logEventInfo("WF-DPDHW:  Freq=%f, NCO=0x%X",mWaveform->getNco(),tuningWord);


	// Program the capture enable
	mWaveformFpga->write_dpdadcCaptureEnable(mWaveform->isEnable()) ;
	mWaveformFpga->write_dpdadcCaptureStreamEnable( mWaveform->getStreaming() ) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareDpdAdc::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	return SrxSampleRateKsps ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareDpdAdc::setTrigger(int airframeCountToTrigger)
{
	if (airframeCountToTrigger < 0)
	{
		airframeCountToTrigger += 307200;
	}

	// Program the airframe count to trigger the module
	mWaveformFpga->write_dpdadcCaptureTrigger(airframeCountToTrigger) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareDpdAdc::setStreaming(bool enable)
{
	//If streaming is enabled, then set a rising edge on the capture enable and
	//streaming enable bit
	if (enable)
	{
		mWaveformFpga->write_dpdadcCaptureEnable(0) ;
		mWaveformFpga->write_dpdadcCaptureStreamEnable(0) ;
	}
	mWaveformFpga->write_dpdadcCaptureStreamEnable(enable ? 1 : 0) ;
	mWaveformFpga->write_dpdadcCaptureEnable(enable ? 1 : 0) ;
}
