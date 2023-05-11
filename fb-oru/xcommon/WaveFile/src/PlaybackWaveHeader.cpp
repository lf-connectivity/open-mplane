/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PlaybackWaveHeader.cpp
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
#include "Sha1.h"

#include "PlaybackWaveHeader.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Size of playback-specific portion of header
static const unsigned UNUSED_SIZE{1} ;
static const unsigned SAMPLE_RATE_SIZE{3} ;
static const unsigned PLAYBACK_HEAD_LEN{Sha1::SHA1_SIZE + UNUSED_SIZE + SAMPLE_RATE_SIZE} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PlaybackWaveHeader::PlaybackWaveHeader() :
	WaveFileHeader(),
	mSha1(Sha1::SHA1_SIZE, 0)
{
}

//-------------------------------------------------------------------------------------------------------------
PlaybackWaveHeader::~PlaybackWaveHeader()
{
}

//-------------------------------------------------------------------------------------------------------------
bool PlaybackWaveHeader::processHeader(IWaveFile::WaveDataIter& dataStart, IWaveFile::WaveDataIter dataEnd)
{
	// process common bytes
	if (!this->super::processHeader(dataStart, dataEnd))
		return false ;

	// Ensure that this IS a playback file
	if (getType() != IWaveFile::WaveType::PLAYBACK)
	{
		setError("Not a playback file") ;
		return false ;
	}

	// Now process the playback-specific header
	unsigned numBytes(std::distance(dataStart, dataEnd)) ;
	if (numBytes < PLAYBACK_HEAD_LEN)
	{
		setError("Invalid header data") ;
		return true ;
	}

	// Read SHA1
	mSha1.clear() ;
	mSha1.reserve(Sha1::SHA1_SIZE) ;
	for (unsigned byte=0; byte < Sha1::SHA1_SIZE; ++byte)
	{
		mSha1.push_back(ByteTransfer::readByte(dataStart, dataEnd)) ;
	}

	// unused
	uint8_t unused(ByteTransfer::readByte(dataStart, dataEnd)) ;
	uint32_t rate(ByteTransfer::read24bit(dataStart, dataEnd)) ;
	(void)unused ;
	(void)rate ;


	// Now skip to the block start
	skipHeader(dataStart) ;

//{
//	printf("SHA1.......: 0x%s\n", Sha1::hashToString(mSha1).c_str()) ;
//	printf("Unused.....: 0x%02x\n", unused) ;
//	printf("Rate.......: 0x%06x\n", rate) ;
//}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t> PlaybackWaveHeader::getSha1() const
{
	return mSha1 ;
}

//-------------------------------------------------------------------------------------------------------------
std::string PlaybackWaveHeader::getSha1String() const
{
	return Sha1::hashToString(mSha1) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::PlaybackWaveHeader::getHeaderSize() const
{
	return PLAYBACK_HEAD_LEN + this->super::getHeaderSize() ;
}

//-------------------------------------------------------------------------------------------------------------
bool PlaybackWaveHeader::createHeader(std::vector<uint8_t>& data, const std::vector<uint8_t>& sha1)
{
	if (sha1.size() != Sha1::SHA1_SIZE)
	{
		setError("Invalid SHA1") ;
		return false ;
	}

	// Use common class to create a playback header, filling in the common bytes
	if (!this->super::createHeader(data, IWaveFile::WaveType::PLAYBACK, PLAYBACK_HEAD_LEN))
		return false ;

	// Add playback header data
	for (auto byte : sha1)
	{
		ByteTransfer::appendByte(data, byte) ;
	}

	// dummy
	ByteTransfer::appendByte(data, 0x00) ;
	ByteTransfer::append24bit(data, 0x00dead) ;

	return true ;
}
