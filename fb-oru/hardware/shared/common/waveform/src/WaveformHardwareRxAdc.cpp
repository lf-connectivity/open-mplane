/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformHardwareRxAdc.cpp
 * \brief     Waveform Hardware for Rx ADC capture
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
#include "WaveformHardwareRxAdc.h"
#include "IHardwareSettings.h"
#include "ICarrierHardware.h"

using namespace Mplane;



//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const unsigned RxSampleRateKsps{245760} ; //The Rx ADC runs at 245.76MSPS
static const unsigned CHAIN_IQ{0};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformHardwareRxAdc::WaveformHardwareRxAdc(unsigned index, unsigned port) :
	WaveformHardware(index, port),
	mMaxCaptureDepth(0)
{
	// Read the register and calculate the actual maximum depth
	unsigned captureDepth(static_cast<unsigned>(mAntennaFpga->read_rxadcCapture1KDepth(port))) ;
	mMaxCaptureDepth = captureDepth * 1024;

	// if capture depth is set to non-zero then hardware is present
	if (captureDepth > 0)
		setPresent(true) ;
	else
		setPresent(false) ;
}


//-------------------------------------------------------------------------------------------------------------
WaveformHardwareRxAdc::~WaveformHardwareRxAdc()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::init(std::string& error)
{
	error = "" ;

	// initialise hardware - falling edge of enable ensures done bit is clear
	mAntennaFpga->write_rxadcCaptureEnable(mPort,1) ;
	mAntennaFpga->write_rxadcCaptureEnable(mPort,0) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::updateSettings(
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
	mWaveform->setSampleRateKsps(RxSampleRateKsps) ;

	//Set streaming as per waveform setting
	setStreaming(mWaveform->getStreaming());

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::updateHardware(std::string& error)
{
	error = "" ;

	if (mWaveform.get() == 0)
	{
		error = "Waveform settings not allocated" ;
		return false ;
	}
	if (mWaveformMem)
	{
		error = "Internal error - Waveform memory allocated for Rx ADC" ;
		return false ;
	}

	if (mWaveform->getType() != Waveform::WAVEFORM_CAPTURE)
	{
		error = "Rx ADC waveform must be used in capture mode" ;
		return false ;
	}

	return updateCapture(error) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::isCaptureWriteError() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::isCaptureDone() const
{
	return (mAntennaFpga->read_rxadcCaptureDone(mPort) != 0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::isPlaybackEnabled() const
{
	// no playback
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::isPlaybackReadError() const
{
	// no playback
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::writeMemoryStart()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::writeMemory(const short* buffer, unsigned bufferSize, bool& endOfData, std::string& error)
{
	error = "Memory write not supported for Rx ADC capture" ;
	return false ;
}


//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::readMemoryStart()
{
	// Toggle the RxAdcCaptureReadReset bit to reset the read
	// address of the memory
	mAntennaFpga->write_rxadcCaptureReadReset(mPort, 0) ;
	mAntennaFpga->write_rxadcCaptureReadReset(mPort, 1) ;

	// use the "read address" as a counter
	mReadAddr = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::readMemory( short* buffer, unsigned& bufferSize, unsigned maxReadSize, bool& endOfFile, std::string& error)
{
	error = "" ;
	endOfFile = false ;
	bufferSize = 0;

	// Read interface has a sample fifo - can only grab a fifo's worth at a time

	// -- Lock fpga mutex --
	mAntennaFpga->mutexLock() ;

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
			short adcData = static_cast<short>(mAntennaFpga->read_nomutex_rxadcCaptureData(mPort)) ;
			*buffer++ = adcData ;
		}


	} // end while (numOfSamplesToRead > 0)

	// check for end of file
	if (mReadAddr >= mWaveform->getDepth())
	{
		endOfFile = true ;
	}

	// -- Un Lock fpga mutex --
	mAntennaFpga->mutexUnLock() ;

	return true ;
}


//-------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::checkCarrier(std::string& error) const
{
	// Carrier not required
	error = "" ;
	return true ;
}

//-------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::show(std::ostream& os) const
{
	os << "WaveformHardwareRxAdc " << std::endl ;
	os << "   * Index...........: " << mWaveIdx << std::endl ;
	os << "   * Max Depth.......: " << mMaxCaptureDepth << std::endl ;
	os << "   * Waveform........: " << mWaveform << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::showWaveformReg(std::ostream& os) const
{
	os << "-----------------------------------" << std::endl ;
	os << "Wave wrxcal" << mPort + 1 << " (" << mWaveIdx << ")" << std::hex << std::endl ;
	os << "Capture Enable.......: 0x" << mAntennaFpga->read_rxadcCaptureEnable(mPort) << std::endl ;
	os << "Capture Done.........: 0x" << mAntennaFpga->read_rxadcCaptureDone(mPort) << std::endl ;
	os << "Capture Trigger......: 0x" << mAntennaFpga->read_rxadcCaptureTrigger(mPort) << std::endl ;
	os << "Capture Depth........: 0x" << mAntennaFpga->read_rxadcCapture1KDepth(mPort) << std::endl ;

	os << std::dec << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::requiresWaveformMem(void) const
{
	// Uses dedicated BlockRAM in the Xilinx fpga so no need to allocate memory
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareRxAdc::getMaxDepth(void) const
{
	return (mMaxCaptureDepth) ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::showWaveformMasterReg(std::ostream& os) const
{
	this->super::showWaveformMasterReg(os) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::shutdown(std::string& error)
{
	error = "" ;

	// skip if not allocated
	if (mWaveform.get() == 0)
		return true ;

	if (mAntennaFpga->read_rxadcCaptureEnable(mPort) != 0)
		mAntennaFpga->write_rxadcCaptureEnable(mPort,0) ;

	mAntennaFpga->write_rxadcCaptureStreamEnable(mPort,0) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::captureInit(void)
{
	// Need to ensure we generate a falling edge to clear out any previous DONE flag
	mAntennaFpga->write_rxadcCaptureEnable(mPort, 0) ;
	mAntennaFpga->write_rxadcCaptureEnable(mPort, mWaveform->isEnable() ) ;
	mAntennaFpga->write_rxadcCaptureStreamEnable(mPort, 0) ;
	mAntennaFpga->write_rxadcCaptureStreamEnable(mPort, mWaveform->getStreaming() ) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::WaveformHardwareRxAdc::getNumBytes(void) const
{
	// skip if not allocated
	if (!mWaveform)
		return 0 ;

	// Here the number of bytes is Depth x 16-bit val
	return mWaveform->getDepth() * 2 ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::usesFpgaBus() const
{
	// Uses internal bus
	return false ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::updateCapture(std::string& error)
{
	error = "" ;

	UINT16 captureEnabled = mAntennaFpga->read_rxadcCaptureEnable(mPort) ;

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
	mAntennaFpga->write_rxadcCaptureAveDepth(mPort, nFPGALength) ;

	//Trigger position
	int tsTrigger = (int)fround(307200.0 * (float)mWaveform->getTrigger() / 10.0);
	if (tsTrigger < 0) tsTrigger += 307200;
	mAntennaFpga->write_rxadcCaptureAveTrigger(mPort, tsTrigger) ;

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
	mAntennaFpga->write_rxadcCaptureDecimation(mPort, (unsigned)mWaveform->getDecimation() + 1) ;
	mAntennaFpga->write_rxadcCaptureThrottle(mPort, throttle) ;
	mAntennaFpga->write_rxadcCaptureAveNumCapt(mPort, mWaveform->getAveraging()) ;

	//Program the Tuner according to the required Freq Offset
	FrequencyOffset offset(mWaveform->getNco());
	ICarrierHardware::changeUlNco(offset, CHAIN_IQ + mPort);

	// Program the capture enable
	mAntennaFpga->write_rxadcCaptureEnable(mPort, mWaveform->isEnable()) ;
	mAntennaFpga->write_rxadcCaptureStreamEnable(mPort, mWaveform->getStreaming() ) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformHardwareRxAdc::getInstanceSampleRateKsps(ICarrier::Type carrierType) const
{
	return RxSampleRateKsps ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformHardwareRxAdc::setTrigger(int airframeCountToTrigger)
{
	if (airframeCountToTrigger < 0)
	{
		airframeCountToTrigger += 307200;
	}

	// Program the airframe count to trigger the module
	mAntennaFpga->write_rxadcCaptureTrigger(mPort, airframeCountToTrigger) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformHardwareRxAdc::setStreaming(bool enable)
{
	//If streaming is enabled, then set a rising edge on the capture enable and
	//streaming enable bit
	if (enable)
	{
		mAntennaFpga->write_rxadcCaptureEnable(mPort, 0) ;
		mAntennaFpga->write_rxadcCaptureStreamEnable(mPort, 0) ;
	}
	mAntennaFpga->write_rxadcCaptureStreamEnable(mPort, enable ? 1 : 0) ;
	mAntennaFpga->write_rxadcCaptureEnable(mPort, enable ? 1 : 0) ;
}
