/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWaveData.cpp
 * \brief     Contains a single capture waveform file data
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "ByteTransfer.hpp"

#include "CaptureWaveHeader.h"
#include "CaptureWaveData.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CaptureWaveData::CaptureWaveData() :
	mError(""),
	mDataLen(0),
	mEof(false),
	mHeader(),
	mData()
{
}

//-------------------------------------------------------------------------------------------------------------
CaptureWaveData::~CaptureWaveData()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CaptureWaveData::addData(IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd)
{
//	std::cerr << "append() " << std::distance(dataStart, dataEnd) << " bytes [current buffer " << mData.size() << " bytes]" << std::endl ;

	if (mEof)
	{
		setError("Attempt to add data when already at end of file") ;
		return false ;
	}

	// is this the start of the data
	if (!mHeader)
	{
//		std::cerr << " * Handle header" << std::endl ;

		// Process the header
		mHeader = std::make_shared<CaptureWaveHeader>() ;
		if (!mHeader->processHeader(dataStart, dataEnd))
		{
			setError( mHeader->getError() ) ;
			return false ;
		}
		if (!mHeader->processBlockHeader(dataStart, dataEnd))
		{
			setError( mHeader->getError() ) ;
			return false ;
		}
		mDataLen = mHeader->getBlockLength() ;

//std::cerr << " * data length=" << mDataLen << std::endl ;
//std::cerr << " * data bytes left = " << std::distance(dataStart, dataEnd) << std::endl ;

		// Scale the buffer ready for the data
		mData.reserve(mDataLen) ;

	}

	// insert data (might be whatever is left after the headers)
	// Need to handle the case where the start of the next waveform is part of this packet
	unsigned numBytes(std::distance(dataStart, dataEnd));
	if (numBytes == 0)
		return true ;

	if (mData.size() + numBytes <= mDataLen)
	{
		// only got data for this wave
		mData.insert(mData.end(), dataStart, dataEnd) ;
		dataStart = dataEnd ;

//std::cerr << " * saved bytes onto end of buffer:" << std::endl ;
//ByteTransfer::dump(mData) ;

	}
	else
	{
		// got the end of this wave and the start of the next
		IWaveFile::WaveDataIter dataNext(dataStart+mDataLen-mData.size()) ;
		mData.insert(mData.end(), dataStart, dataNext) ;
		dataStart = dataNext ;
//std::cerr << "Got start of next:" << std::endl ;
//ByteTransfer::dump(dataStart, dataEnd) ;

	}

	// check for EOF
	if (mData.size() >= mDataLen)
		mEof = true ;

//std::cerr << std::endl << "BUFFERS" << std::endl ;
//std::cerr << "## mData ########################" << std::endl ;
//ByteTransfer::dump(mData) ;
//std::cerr << "#################################" << std::endl << std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveData::getDataLength() const
{
	return mDataLen ;
}

//-------------------------------------------------------------------------------------------------------------
bool CaptureWaveData::endOfFile() const
{
	return mEof ;
}

//-------------------------------------------------------------------------------------------------------------
void CaptureWaveData::reset()
{
	mError.clear() ;
	mDataLen = 0 ;
	mEof = false ;
	mHeader.reset() ;
	mData.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
const std::vector<uint8_t>& CaptureWaveData::getData() const
{
	return mData ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveData::getWaveIndex() const
{
	if (!mHeader)
		return 0 ;

	return mHeader->getWaveIndex() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CaptureWaveData::getSampleRateKsps() const
{
	if (!mHeader)
		return 0 ;

	return mHeader->getSampleRateKsps() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CaptureWaveData::getError()
{
	std::string error("") ;
	std::swap(mError, error) ;
	return error ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CaptureWaveData::setError(const std::string& error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}
