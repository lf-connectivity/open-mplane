/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformControl.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>
#include <iterator>

#include "Path.h"
#include "ICarrier.h"
#include "ICarrierServer.h"
#include "ICarrierHardware.h"

#include "CaptureWaveHeader.h"

#include "WaveMemMgr.h"
#include "Waveform.h"
#include "WaveformHardware.h"
#include "WaveformMem.h"
#include "WaveformControl.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// max number of samples to read/write to/from buffer
static const unsigned MAX_BUFF_SAMPLES = 8192 ;

// Default directory paths
static const std::string DEFAULT_PLAYBACK_PATH("/nandflash/tif/playback/") ;
static const std::string DEFAULT_CAPTURE_PATH("/www/htdocs/") ;

// List of the expected waveform types
static const std::vector<IWaveform::WaveType> waveTypesTable{
	//	Waveform Module 0 	Rx1 Capture at 61.44 MSPS
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 1 	Rx2 Capture at 61.44 MSPS
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 2 	CPRI Multicast on RF Chain indexes 0 and 2 at programmed baseband sample rate
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 3 	CPRI Multicast on RF Chain indexes 1 and 3 at programmed baseband sample rate
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 4 	CPRI Capture from RF Chain index 0 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 5 	CPRI Capture from RF Chain index 1 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 6 	Tx1 playback at programmed baseband sample rate
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 7 	Tx2 playback at programmed baseband sample rate
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 8 	CPRI Capture from RF Chain index 2 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 9 	CPRI Capture from RF Chain index 3 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 10 	Tx1 playback direct to DAC
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 11 	Tx2 playback direct to DAC
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 12 	CPRI Capture from RF Chain index 4 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 13 	CPRI Capture from RF Chain index 5 at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 14 	Reserved for playback, currently unused
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 15 	Reserved for playback, currently unused
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 16 	Rx1 Capture at programmed baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 17 	Rx2 Capture at programmed baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 18 	Reserved for playback, currently unused
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 19 	Reserved for playback, currently unused
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 20 	First PIM Block UL Input Capture at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 21 	First PIM Block UL Output Capture at programmed CPRI baseband sample rate
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 22 	CPRI Playback on RF Chain index 0 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 23 	CPRI Playback on RF Chain index 1 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	Waveform::WAVEFORM_PLAYBACK,
	//	Waveform Module 24 	CPRI Capture on RF Chain index 0 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	Waveform::WAVEFORM_CAPTURE,
	//	Waveform Module 25 	CPRI Capture on RF Chain index 1 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	Waveform::WAVEFORM_CAPTURE,


	//
	//	DPD RX CAL (Capture)
	Waveform::WAVEFORM_CAPTURE,
	//	RX1 CAL (Capture)
	Waveform::WAVEFORM_CAPTURE,
	//	RX2 CAL (Capture)
	Waveform::WAVEFORM_CAPTURE,
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformControl::WaveformControl() :
	mUpdateRequired(false),
	mWaveform(new Waveform),
	mWaveformHardware(),
	mWaveformMem()
{
}

//-------------------------------------------------------------------------------------------------------------
WaveformControl::~WaveformControl()
{
	// Deallocate any allocated memory
	std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
	memMgr->deallocate(mWaveformMem) ;

	mWaveformMem = std::shared_ptr<WaveformMem>() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::setWaveformHardware(std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error)
{
//	std::cerr << "WaveformControl::setWaveformHardware" << std::endl ;
	error = "" ;
	mWaveformHardware = waveformHardware ;

	// Set update flag based on the validity of the waveform hardware pointer
	if ( !waveformHardware )
	{
		mUpdateRequired = false ;

		// deallocate memory
		std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
		memMgr->deallocate(mWaveformMem) ;
		mWaveformMem = std::shared_ptr<WaveformMem>() ;

		return true ;
	}

	mUpdateRequired = true ;

	// Clear out any existing memory if depth setting has changed
	if (mWaveform->isDepthChanged())
	{
		// deallocate memory
		std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
		memMgr->deallocate(mWaveformMem) ;
		mWaveformMem = std::shared_ptr<WaveformMem>() ;
	}

	// Allocate waveform memory if not already allocated AND the hardware requires memory
	if (!mWaveformMem && (mWaveformHardware->requiresWaveformMem()))
	{
		// a depth setting of 0 means - read the file size to determine depth
		if (mWaveform->getDepth() == 0)
		{
			mWaveform->setDepth( getFileDepth() ) ;
		}

		// check for valid depth
		if (mWaveform->getDepth() == 0)
		{
			error = "Invalid depth" ;
			return false ;
		}
		if (mWaveform->getDepth() > mWaveformHardware->getMaxDepth())
		{
			error = "Depth too large" ;
			return false ;
		}

		// Each sample is 2x 16-bit words (I&Q) being stored in 64bit memory, so the size to be
		// allocated is 1/2 the depth
		std::shared_ptr<WaveMemMgr> memMgr(WaveMemMgr::getInstance()) ;
		mWaveformMem = memMgr->allocate(mWaveform->getDepth() / 2) ;

		// check for failure
		if (!mWaveformMem)
		{
			error = "Unable to allocate waveform memory" ;
			return false ;
		}
	}

	// update the settings
	if (!mWaveformHardware->updateSettings(mWaveform, mWaveformMem, error))
		return false ;

	// Now that the wave hardware auto-calcs the sample rate, need to copy back the setting so we can use it here (and keep the 2 copies
	// of the wave information the same)
	//
	mWaveform->setSampleRateKsps( mWaveformHardware->getSampleRateKsps() ) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void WaveformControl::enableHasChanged(bool enable)
{
//	std::cerr << "WaveformControl::enableHasChanged " << enable << std::endl ;

	// skip if no hardware
	if (!mWaveformHardware)
		return ;

	// pass change down
	mWaveformHardware->enableHasChanged(enable) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::filenameHasChanged(std::string& error)
{
	// skip if no hardware
	if (!mWaveformHardware)
		return true ;

	// Only update if PLAYBACK *and* already enabled *and* global playback enabled
	if (mWaveform->getType() != Waveform::WAVEFORM_PLAYBACK)
		return true ;
	if ( !mWaveform->isEnable() )
		return true ;
	if ( !WaveformHardware::isMasterPlaybackEnabled() )
		return true ;

	// Check the filename
	if (!checkFilename(error))
		return false ;

	// Now perform the file write
	if (!writeMemFromFile(mWaveform->getFilename(), mWaveformHardware, error))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::validate(std::string& error)
{
	error = "" ;

//std::cerr << "WaveformControl::validate" << std::endl ;

	// Error if not got a waveform hardware resource allocated
	if (!mWaveformHardware)
	{
		error = "Internal error - resource not allocated" ;
		return false ;
	}

	// Check index against table
	if (mWaveformHardware->getIndex() >= waveTypesTable.size())
	{
		error = "Waveform invalid index" ;
		return false ;
	}


	// Check type setting
	if (mWaveform->getType() != waveTypesTable[mWaveformHardware->getIndex()])
	{
		error = "Waveform must be set to " +
			std::string(waveTypesTable[mWaveformHardware->getIndex()] == IWaveform::WAVEFORM_CAPTURE ? "CAPTURE" : "PLAYBACK") ;
		return false ;
	}

	// If depth is set to 0 for playback wave then use the file size
	if ( (mWaveform->getDepth() == 0) && (mWaveform->getType() == IWaveform::WAVEFORM_PLAYBACK) )
	{
		mWaveform->setDepth( getFileDepth() ) ;
	}

	// check parameters
	if (mWaveform->getDepth() == 0)
	{
		error = "Invalid depth" ;
		return false ;
	}
	if (mWaveform->getDepth() > mWaveformHardware->getMaxDepth())
	{
		error = "Depth too large" ;
		return false ;
	}

	// validate waveform module
	if (!mWaveformHardware->validate(error))
		return false ;

	// specific test of carrier
	if (!mWaveformHardware->checkCarrier(error))
		return false ;

	// specific filename test
	if (!checkFilename(error))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::updateHardware(std::string& error)
{
	error = "" ;

//	std::cerr << "WaveformControl::updateHardware" << std::endl ;

	// fail if hardware has not been allocated
	if (!mWaveformHardware)
	{
		error = "Waveform hardware not allocated" ;
		return false ;
	}

	// fail if memory has not been allocated
	if ((!mWaveformMem) && (mWaveformHardware->requiresWaveformMem()))
	{
		error = "Waveform memory not allocated" ;
		return false ;
	}

	// if update is not required then skip
	if (!mUpdateRequired)
		return true ;

	// For playback we need to transfer the file to the memory before starting
	if (mWaveform->getType() == Waveform::WAVEFORM_PLAYBACK)
	{
		if (!writeMemFromFile(mWaveform->getFilename(), mWaveformHardware, error))
			return false ;
	}


	// get hardware to update using the settings
	bool status = mWaveformHardware->updateHardware(error) ;

	// clear flag
	mUpdateRequired = false ;

	return status ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::completeUpdate(std::string& error)
{
	error = "" ;
	mWaveform->clearValueChanged() ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::shutdown(std::string& error)
{
	error = "" ;

	// skip if no hardware
	if (!mWaveformHardware)
		return true ;

	// Shutdown if active
	if (!mWaveform->isEnable())
		return true ;

	return mWaveformHardware->shutdown(error) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::setScalingGain(float scalingGain)
{
	// skip if no waveform
	if (!mWaveform)
		return false ;

	// Check setting
	mWaveform->setScalingGain(scalingGain) ;

	// If this is active then adjust the hardware live

	// skip if no hardware
	if (!mWaveformHardware)
		return true ;

	// skip in not active
	if (!mWaveform->isEnable())
		return true ;

	// skip if not playback waveform
	if (mWaveform->getType() != Waveform::WAVEFORM_PLAYBACK)
		return true ;

	// update the settings
	std::string error ;
	if (!mWaveformHardware->updateSettings(mWaveform, mWaveformMem, error))
		return false ;

	// change the hardware
	return mWaveformHardware->setPlaybackScalingValue() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::setStreaming(bool enable)
{
	// skip if no waveform
	if (!mWaveform)
		return false ;

	// Check setting
	mWaveform->setStreaming(enable) ;

	// If this is active then adjust the hardware live

	// skip if no hardware
	if (!mWaveformHardware)
		return true ;

	// skip if not capture waveform
	if (mWaveform->getType() != Waveform::WAVEFORM_CAPTURE)
		return true ;

	// update the settings
	std::string error ;
	if (!mWaveformHardware->updateSettings(mWaveform, mWaveformMem, error))
		return false ;
	else
		return true;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveform> WaveformControl::getWaveform() const
{
	return mWaveform ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformHardware> WaveformControl::getWaveformHardware() const
{
	return mWaveformHardware ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformMem> WaveformControl::getWaveformMem() const
{
	return mWaveformMem ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformControl::show(std::ostream& os) const
{
	os << "WaveformControl " << mWaveform->getName() << std::endl ;
//	os << " * Waveform........: " << mWaveform << std::endl ;
	os << " * WaveformHardware: " << mWaveformHardware << std::endl ;
	os << " * WaveformMem.....: " << mWaveformMem << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformControl::getFileDepth()
{
	// specific filename test
	std::string error("") ;
	if (!checkFilename(error))
		return 0 ;

	// Must be a playback file to get here - read the size
	unsigned size(Path::fileSize(mWaveform->getFilename())) ;

	// file size should be 4x depth
	return size/4 ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::writeMemFromFile(const std::string& filename, std::shared_ptr<IWaveformHardware> waveformHardware,
		std::string& error) const
{
	error = "" ;

	// open file
	int fd = open(filename.c_str(), O_RDONLY) ;
	if (fd < 0)
	{
		error = "Unable to read from file " + filename ;
		return false ;
	}

	// prepare waveform memory access for writing
	waveformHardware->writeMemoryStart() ;

	// set up buffer
	std::vector<short> buffer(MAX_BUFF_SAMPLES) ;
	unsigned maxBytes = MAX_BUFF_SAMPLES * sizeof(short) ;

//unsigned total(0) ;

	bool ok = true ;
	bool endOfFile = false ;
	while (!endOfFile && ok)
	{
		// read from file
		int numBytes = read(fd, &buffer[0], maxBytes) ;
		if (numBytes <= 0)
		{
			error = "Error reading from file " + filename ;
			close(fd) ;
			return false ;
		}
		if (numBytes < (int)maxBytes)
			buffer.resize(numBytes/sizeof(short)) ;

//total += numBytes ;
//std::cerr << "Read " << numBytes << " bytes, total " << total << " bytes" << std::endl ;

		// write memory
		ok = waveformHardware->writeMemory(&buffer[0], buffer.size(), endOfFile, error) ;
		if (!ok)
			break ;

if (endOfFile)
	std::cerr << "EOF" << std::endl ;

		if (numBytes < (int)maxBytes)
			buffer.resize(MAX_BUFF_SAMPLES) ;
	}

	close(fd) ;
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::checkFilename(std::string& error) const
{

	// check for port setting with capture files
	if ( (mWaveform->getType() == IWaveform::WAVEFORM_CAPTURE) && (mWaveform->getCaptureCallback()) )
		return true ;

	// if none specified then stop with error
	if (mWaveform->getFilename().empty())
	{
		error = "No filename specified" ;
		return false ;
	}

	// check specified filename
	switch (mWaveform->getType())
	{
	case IWaveform::WAVEFORM_PLAYBACK:
	case IWaveform::WAVEFORM_CAPTURE:
		{
			std::string DEFAULT_PATH(DEFAULT_PLAYBACK_PATH) ;
			if (mWaveform->getType() == IWaveform::WAVEFORM_CAPTURE)
				DEFAULT_PATH = DEFAULT_CAPTURE_PATH ;

			// check file path
			std::string path( mWaveform->getFilename() ) ;
			std::size_t pos = path.find_last_of('/') ;
			if (pos == std::string::npos)
			{
				path.insert(0, DEFAULT_PATH) ;
				pos = path.find_last_of('/') ;
				mWaveform->setFilename(path) ;
			}

			if (pos == 0 || !Path::isDir(path.substr(0, pos)))
			{
				// set an error
				std::stringstream ss ;
				ss << "Invalid file path: " << path ;
				error = ss.str() ;
				return false ;
			}

			// For playback, check file exists
			if (mWaveform->getType() == IWaveform::WAVEFORM_PLAYBACK)
			{
				if (!Path::exists(path) || Path::isDir(path))
				{
					// set an error
					std::stringstream ss ;
					ss << "Playback file does not exist: " << path ;
					error = ss.str() ;
					return false ;
				}
			}

		}
		break ;

	default:
		error = "Internal error: waveform settings not set" ;
		return false ;
		break ;
	}

	return true ;
}



//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::startCapturePlayback(bool playbackEnable,
	std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves,
	std::string& error)
{
	error = "" ;

	// pass down to waveform hardware
	std::vector< std::shared_ptr<IWaveformHardware> > waveformHardwareList( getWaveformHardwareList(enabledWaves) )  ;
	if (! WaveformHardware::startAllCapture( playbackEnable, waveformHardwareList, error ) )
		return false ;

	// Check through the waveform list, find the waveforms that were enabled for playback and ensure that their streams
	// are resynchronised.
	for(std::vector< std::shared_ptr<IWaveformControl> >::iterator iter(enabledWaves.begin()); iter != enabledWaves.end(); ++iter)
	{
		if ( ! (*iter)->resyncPlaybackStreams(error) )
			return false ;
	}

	// Check through the waveform list, find the waveforms that were enabled for capture and completed, and copy those
	// captures to their destinations.
	for(std::vector< std::shared_ptr<IWaveformControl> >::iterator iter(enabledWaves.begin()); iter != enabledWaves.end(); ++iter)
	{
		if ( ! (*iter)->checkCaptureComplete(error) )
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::startPlayback(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error)
{
	error = "" ;

	// pass down to waveform hardware
	std::vector< std::shared_ptr<IWaveformHardware> > waveformHardwareList( getWaveformHardwareList(enabledWaves) )  ;
	if ( !WaveformHardware::startAllPlayback( waveformHardwareList, error ) )
		return false ;

	// Check through the waveform list, find the waveforms that were enabled for playback and ensure that their streams
	// are resynchronised.
	for(std::vector< std::shared_ptr<IWaveformControl> >::iterator iter(enabledWaves.begin()); iter != enabledWaves.end(); ++iter)
	{
		if ( ! (*iter)->resyncPlaybackStreams(error) )
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::stopCapture(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error)
{
	error = "" ;

	// pass down to waveform hardware
	std::vector< std::shared_ptr<IWaveformHardware> > waveformHardwareList( getWaveformHardwareList(enabledWaves) )  ;
	return WaveformHardware::stopAllCapture( waveformHardwareList, error ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::stopPlayback(std::vector< std::shared_ptr<IWaveformControl> >& enabledWaves, std::string& error)
{
	error = "" ;

	// pass down to waveform hardware
	std::vector< std::shared_ptr<IWaveformHardware> > waveformHardwareList( getWaveformHardwareList(enabledWaves) )  ;
	return WaveformHardware::stopAllPlayback( waveformHardwareList, error ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::completeStartStop(std::vector<std::shared_ptr<IWaveformControl> >& enabledWaves,	std::string& error)
{
	error = "" ;

	// Run the "complete" method on each WaveformControl
	for(std::vector< std::shared_ptr<IWaveformControl> >::iterator iter(enabledWaves.begin()); iter != enabledWaves.end(); ++iter)
	{
		if ( ! (*iter)->completeUpdate(error) )
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string WaveformControl::getPlaybackDirectory()
{
	return DEFAULT_PLAYBACK_PATH ;
}

//-------------------------------------------------------------------------------------------------------------
std::string WaveformControl::getCaptureDirectory()
{
	return DEFAULT_CAPTURE_PATH ;
}


//=============================================================================================================
// PRIVATE STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IWaveformHardware> > WaveformControl::getWaveformHardwareList(
		std::vector<std::shared_ptr<IWaveformControl> >& enabledWaves)
{
	// Create list of waveform hardware
	std::vector< std::shared_ptr<IWaveformHardware> > waveformHardwareList ;
	for(std::vector< std::shared_ptr<IWaveformControl> >::iterator iter(enabledWaves.begin()); iter != enabledWaves.end(); ++iter)
	{
		std::shared_ptr<IWaveformHardware> waveformHardware((*iter)->getWaveformHardware()) ;
		if (waveformHardware)
			waveformHardwareList.push_back(waveformHardware) ;
	}

	return waveformHardwareList ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::readMemToFile(const std::string& filename, std::shared_ptr<IWaveformHardware> waveformHardware, std::string& error)
{
	error = "" ;

	int fd = open(filename.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ;
	if (fd < 0)
	{
		error = "Unable to write to file" ;
		return false ;
	}

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
			break ;

		// write to file
		int numBytes = write(fd, &buffer[0], bufferSize * sizeof(short)) ;
		if (numBytes <= 0)
		{
			std::cerr << "readMemToFile: Error writing file write() status=" << numBytes <<
					" buffer size=" << bufferSize << std::endl ;
			error = "Error writing to file" ;
			close(fd) ;
			return false ;
		}

	}

	close(fd) ;

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::readMemToCallback(
		IWaveform::CaptureCallback callback,
		std::shared_ptr<IWaveformHardware> waveformHardware,
		std::string& error)
{
	error = "" ;

	// Write out header
	std::vector<uint8_t> header ;
	CaptureWaveHeader waveHead ;
	waveHead.createHeader(header,
		waveformHardware->getIndex(),
		waveformHardware->getSampleRateKsps()
	) ;
	waveHead.createBlockHeader(header,
		IWaveFile::WaveBlockType::RAW,
		waveformHardware->getNumBytes()
	) ;

	callback(header) ;


	// set up buffers
	unsigned bufferSize ;
	std::vector<uint8_t> data(MAX_BUFF_SAMPLES * sizeof(short)) ;

	// prepare waveform memory access for reading
	waveformHardware->readMemoryStart() ;

	bool ok = true ;
	bool endOfFile = false ;
	while (!endOfFile && ok)
	{
		// read memory
		ok = waveformHardware->readMemory( reinterpret_cast<short *>(&data[0]), bufferSize, MAX_BUFF_SAMPLES, endOfFile, error) ;
		if (!ok)
			break ;

		// output
		callback( std::vector<uint8_t>(data.begin(), data.begin()+sizeof(short)*bufferSize) ) ;
	}

	return ok ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::checkCaptureComplete(std::string& error)
{
	error = "" ;

	if (mWaveform->getType() != Waveform::WAVEFORM_CAPTURE)
		return true ;
	if (!mWaveform->isEnable())
		return true ;

	// check for capture error
	if (mWaveformHardware->isCaptureWriteError())
	{
		std::stringstream ss ;
		ss << "Capture write error on waveform " << mWaveform->getName() ;
		error = ss.str() ;
		return false ;
	}

	// check for done
	if (!mWaveformHardware->isCaptureDone())
	{
std::cerr << " ! " << mWaveform->getName() << " capture not done - skipped !" << std::endl ;
		return true ;
	}

	// Transfer file
	std::string readError ;
	IWaveform::CaptureCallback callback(mWaveform->getCaptureCallback()) ;
	if (callback)
	{
		// Capture to callback function (i.e. send data over tcp port)
		if (!readMemToCallback(callback, mWaveformHardware, readError))
		{
			std::stringstream ss ;
			ss << "Unable to read memory on waveform " << mWaveform->getName() <<
					" error: " << readError ;
			error = ss.str() ;
			return false ;
		}
	}
	else
	{
		// Capture to file
		if (!readMemToFile(mWaveform->getFilename(), mWaveformHardware, readError))
		{
			std::stringstream ss ;
			ss << "Unable to read memory into file " << mWaveform->getFilename() << " on waveform " << mWaveform->getName() <<
					" error: " << readError ;
			error = ss.str() ;
			return false ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformControl::resyncPlaybackStreams(std::string& error)
{
	error = "" ;

	if (mWaveform->getType() != Waveform::WAVEFORM_PLAYBACK)
		return true ;
	if (!mWaveform->isEnable())
		return true ;
	if (!mWaveform->isValueChanged())
		return true ;

	// Get carrier hardware and do a resync
	std::shared_ptr<ICarrierHardwareList> carrierHardwareList( ICarrierHardwareList::getInstance() ) ;
	ICarrierHardware* carrierHardware( carrierHardwareList->getCarrierHardware(mWaveform->getCarrierIdx()) ) ;
	if (!carrierHardware)
	{
		error = "Internal error - unable to access carrier hardware" ;
		return false ;
	}

	// do resync - use the antenna port number so carrier hardware can determine the associated stream
	carrierHardware->resyncUlStream( mWaveform->getAntennaPort() ) ;

	return true ;
}
