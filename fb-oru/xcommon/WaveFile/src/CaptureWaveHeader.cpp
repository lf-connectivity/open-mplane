/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWaveHeader.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ByteTransfer.hpp"
#include "CaptureWaveHeader.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Size of capture-specific portion of header
static const unsigned WAVE_IDX_SIZE{1} ;
static const unsigned SAMPLE_RATE_SIZE{3} ;
static const unsigned CAPTURE_HEAD_LEN{WAVE_IDX_SIZE + SAMPLE_RATE_SIZE} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CaptureWaveHeader::CaptureWaveHeader() :
	WaveFileHeader(),
	mWaveIndex(0),
	mSampleRateKsps(0)
{
}

//-------------------------------------------------------------------------------------------------------------
CaptureWaveHeader::~CaptureWaveHeader()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveHeader::getHeaderSize() const
{
	return CAPTURE_HEAD_LEN + this->super::getHeaderSize() ;
}

//-------------------------------------------------------------------------------------------------------------
bool CaptureWaveHeader::processHeader(IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd)
{
	// process common bytes
	if (!this->super::processHeader(dataStart, dataEnd))
		return false ;

	// Ensure that this IS a capture file
	if (getType() != IWaveFile::WaveType::CAPTURE)
	{
		setError("Not a capture file") ;
		return false ;
	}

	// Now process the capture-specific header
	unsigned numBytes(std::distance(dataStart, dataEnd)) ;
	if (numBytes < CAPTURE_HEAD_LEN)
	{
		setError("Invalid header data") ;
		return true ;
	}

	mWaveIndex = (unsigned)ByteTransfer::readByte(dataStart, dataEnd) ;
	mSampleRateKsps = ByteTransfer::read24bit(dataStart, dataEnd) ;

	// Now skip to the block start
	skipHeader(dataStart) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveHeader::getWaveIndex() const
{
	return mWaveIndex ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveHeader::getSampleRateKsps() const
{
	return mSampleRateKsps ;
}

//-------------------------------------------------------------------------------------------------------------
bool CaptureWaveHeader::createHeader(std::vector<uint8_t>& data, unsigned waveIndex, unsigned sampleRateKsps)
{
	// Use common class to create a capture header, filling in the common bytes
	if (!this->super::createHeader(data, IWaveFile::WaveType::CAPTURE, CAPTURE_HEAD_LEN))
		return false ;

	// Add capture header data
	ByteTransfer::appendByte(data, (uint8_t)waveIndex) ;
	ByteTransfer::append24bit(data, sampleRateKsps) ;

	return true ;
}
