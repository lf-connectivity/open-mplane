/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBus.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
#include "ByteTransfer.hpp"

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SpiBus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiBus::SpiBus(const std::string &busName, const std::string &busDetails, std::shared_ptr<IBusLock> busLock,
		std::shared_ptr<IBusReadonlySettings> busSettings) :
	Bus(busName, busDetails, busLock, busSettings),
	mSrSize(16),
	mAddrMs(14),
	mAddrLs(8),
	mAddrSize(mAddrMs - mAddrLs + 1),
	mUseReadWriteBit(true),
	mReadWriteBit(15)
{
}

//-------------------------------------------------------------------------------------------------------------
SpiBus::~SpiBus()
{
}

//-------------------------------------------------------------------------------------------------------------
void SpiBus::setDeviceSettings(unsigned srRegisterWidth,
		unsigned addrMS, unsigned addrLS, bool useReadWriteBit,
		unsigned readWriteBit)
{
	mSrSize = srRegisterWidth ;
	mAddrMs = addrMS ;
	mAddrLs = addrLS ;
	mAddrSize = mAddrMs - mAddrLs + 1 ;
	mUseReadWriteBit = useReadWriteBit ;
	mReadWriteBit = readWriteBit ;

	if (mAddrMs <= mAddrLs)
		throw std::runtime_error("SPI address bits incorrect") ;

	if ((mUseReadWriteBit) && (mReadWriteBit >= mSrSize))
		throw std::runtime_error("SPI R/W bit incorrect") ;

	// start simple and only support SPI devices with up to 32 bits of shift reg
	if (mSrSize > 32)
		throw std::runtime_error("SPI unsupported shift register size") ;

	// only support up to 8 bit address
	if (mAddrSize > 8)
		throw std::runtime_error("SPI unsupported address size") ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t> SpiBus::writeBytes(uint32_t offset, const std::vector<uint8_t> &data) const
{
	std::vector<uint8_t> bytes(data) ;

	// Assume everything is big endian
	unsigned numBytes( (mSrSize + 7) / 8 ) ;
	std::vector<uint8_t> shiftReg(numBytes, 0) ;

	// address info
	unsigned addrBit( mAddrLs % 8 ) ;
	unsigned addrIndex( numBytes - 1 - (mAddrLs / 8) ) ;
	if (settings()->isLittleEndian())
	{
		addrIndex = mAddrLs / 8 ;
	}


	// insert (shifted) data

	// see if address is at the MS (or 1 less than MS if R/W bit)
	if ( (mAddrLs + mAddrSize) < (mSrSize - 1) )
	{
		unsigned shift( (mAddrMs%8) + 1 ) ;
		unsigned shiftHi(8 - shift) ;
		uint8_t loMask(0xFF << shift) ;
		uint8_t hiMask( (1 << shift) - 1) ;

		// not at MS so shift required
		bytes.insert(bytes.begin(), 0) ;
		bytes.push_back(0) ;
		for (unsigned i=1; i < bytes.size(); ++i)
		{
			uint8_t low( (bytes[i-1] << shift) & loMask ) ;
			low |= (bytes[i] >> shiftHi)  & hiMask ;
			bytes[i-1] = low ;
		}
		bytes.pop_back() ;

	}

	// ensure we only use the correct number of bytes.
	// 1. If data bytes are < SR size then pad
	while (bytes.size() < numBytes)
	{
		bytes.insert(bytes.begin(), 0) ;
	}

	// 2. if data bytes are > SR size then drop the MS (first) bytes
	unsigned bytesStart(bytes.size() - numBytes) ;

	// just ensure we don't overflow into the address
	for (unsigned i=bytesStart, j=0; (i < bytes.size()) && (j < shiftReg.size()); ++i, ++j)
	{
		// check for this byte overlapping with address with address at MS
		if ( (j==addrIndex) && (j==0) )
		{
			// need to mask out top part of byte
			uint8_t mask( (1 << addrBit) -1) ;
			bytes[i] &= mask ;
		}

		// check for this byte overlapping with address at LS
		else if ( (j==addrIndex) && (j > 0) )
		{
			// need to mask out bottom part of byte
			uint8_t mask(0xFF) ;
			mask <<= addrBit ;
			bytes[i] &= mask ;
		}

		shiftReg[j] = bytes[i] ;
	}

	// insert address
	offset = spiWriteOffset(offset) ;
	offset <<= addrBit ;
	shiftReg[addrIndex] |= (uint8_t)(offset & 0xff) ;

	// clear write bit
	if (mUseReadWriteBit)
	{
		unsigned rwBit( mReadWriteBit % 8 ) ;
		unsigned rwIndex( numBytes - 1 - (mReadWriteBit / 8) ) ;
		if (settings()->isLittleEndian())
		{
			rwIndex = mReadWriteBit / 8 ;
		}
		shiftReg[rwIndex] &= ~(1 << rwBit) ;
	}

	return shiftReg ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t> SpiBus::readBytes(uint32_t offset) const
{
	unsigned numBytes( (mSrSize + 7) / 8 ) ;
	std::vector<uint8_t> shiftReg(numBytes, 0) ;

	// address info
	unsigned addrBit( mAddrLs % 8 ) ;
	unsigned addrIndex( numBytes - 1 - (mAddrLs / 8) ) ;
	if (settings()->isLittleEndian())
	{
		addrIndex = mAddrLs / 8 ;
	}

	// insert address
	offset = spiReadOffset(offset) ;
	offset <<= addrBit ;
	shiftReg[addrIndex] |= (uint8_t)(offset & 0xff) ;

	// set read bit
	if (mUseReadWriteBit)
	{
		unsigned rwBit( mReadWriteBit % 8 ) ;
		unsigned rwIndex( numBytes - 1 - (mReadWriteBit / 8) ) ;
		if (settings()->isLittleEndian())
		{
			rwIndex = mReadWriteBit / 8 ;
		}
		shiftReg[rwIndex] |= (1 << rwBit) ;
	}

	return shiftReg ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t SpiBus::spiWriteOffset(uint32_t offset) const
{
	offset &= ((1 << mAddrSize) -1) ;

	return offset ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t SpiBus::spiReadOffset(uint32_t offset) const
{
	offset &= ((1 << mAddrSize) -1) ;

	return offset ;
}
