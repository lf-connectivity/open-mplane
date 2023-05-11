/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgc_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "ByteTransfer.hpp"
#include "BusLock.hpp"
#include "BusSettings.hpp"
#include "SpiBus.h"

#include "bus_fixture.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
class SpiBusFixture : public BusTestFixture
{
public:
};


//=============================================================================================================
// SpiBusTest
//=============================================================================================================

class SpiBusTest : public SpiBus {
public:
	SpiBusTest(unsigned srSize, unsigned addrMs, unsigned addrLs) :
		SpiBus("SpiBus", "test", std::make_shared<NullBusLock>(), std::make_shared<BusSettings>())
	{
		// assume we use R/W and at its the next bit above the address
		setDeviceSettings(srSize, addrMs, addrLs, true, addrMs+1) ;
	}
	SpiBusTest(unsigned srSize, unsigned addrMs, unsigned addrLs, bool useRw, unsigned rwBit) :
		SpiBus("SpiBus", "test", std::make_shared<NullBusLock>(), std::make_shared<BusSettings>())
	{
		// assume we use R/W and at its the next bit above the address
		setDeviceSettings(srSize, addrMs, addrLs, useRw, rwBit) ;
	}
	virtual ~SpiBusTest() {}

	/**
	 * Converts an offset address and a vector of bytes into shift register sized set of bytes
	 *
	 * The returned vector will be MS first. So, for example, a 32 bit shift reg will be returned
	 * as:
	 *
	 * [0] 31 .. 24
	 * [1] 23 .. 16
	 * [2] 15 ..  8
	 * [3]  7 ..  0
	 *
	 * If address bits are 4 .. 0 then the address will be in the LS part of the [3] byte. The data provided in bytes
	 * will be shifted to fit into the remaining data. Assumes the provided by data is also MS first. If the number of bytes
	 * provided is the same as the size of the shift register (or larger) then the MS bits will be dropped during the alignment
	 * to fit in the address.
	 */
	std::vector<uint8_t> writeBytes(uint32_t offset, const std::vector<uint8_t>& bytes) const
	{
		return SpiBus::writeBytes(offset, bytes) ;
	}


	std::vector<uint8_t> readBytes(uint32_t offset) const
	{
		return SpiBus::readBytes(offset) ;
	}

	/**
	 *                                                                     _
	 * Use the address size to convert address to a valid value with the R/W bit for a write
	 */
	uint32_t spiWriteOffset(uint32_t offset) const
	{
		return SpiBus::spiWriteOffset(offset) ;
	}

	/**
	 *                                                                     _
	 * Use the address size to convert address to a valid value with the R/W bit for a read
	 */
	uint32_t spiReadOffset(uint32_t offset) const
	{
		return SpiBus::spiReadOffset(offset) ;
	}
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(SpiBusFixture, spiOffset)
{
	{
	SpiBusTest spi(16, 14, 8) ;
	uint8_t offset ;

	offset = spi.spiWriteOffset(0xff) ;
	EXPECT_EQ(0x7fu, offset) ;
	offset = spi.spiReadOffset(0) ;
	EXPECT_EQ(0u, offset) ;

	std::vector<uint8_t> bytes(spi.readBytes(0)) ;
	EXPECT_EQ(0x80u, bytes[0]) ;
	}

	{
	SpiBusTest spi(32, 4, 0) ;
	uint8_t offset ;

	offset = spi.spiWriteOffset(0xff) ;
	EXPECT_EQ(0x1fu, offset) ;
	offset = spi.spiReadOffset(0) ;
	EXPECT_EQ(0u, offset) ;

	std::vector<uint8_t> bytes(spi.readBytes(0)) ;
	EXPECT_EQ(0x20u, bytes[3]) ;
	}

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(SpiBusFixture, writeBytes)
{
	{
	SpiBusTest spi(24, 22, 16) ;
	spi.setDebug(true) ;

	std::cout << "-- Initial bytes: --" << std::endl ;
	std::vector<uint8_t> bytes{0xA1, 0xA2} ;
	ByteTransfer::dump(bytes) ;

	std::vector<uint8_t> spibytes( spi.writeBytes(0x55, bytes)) ;
	std::cout << "SPI bytes [24, 22..16] wr 0x55:" << std::endl ;
	ByteTransfer::dump(spibytes) ;

	ASSERT_EQ(3ul, spibytes.size()) ;

	EXPECT_EQ(0x55u, spibytes[0]) ;
	EXPECT_EQ(0xA1u, spibytes[1]) ;
	EXPECT_EQ(0xA2u, spibytes[2]) ;
	}

	{
	SpiBusTest spi(24, 22, 16) ;
	spi.setDebug(true) ;

	std::cout << "-- Initial bytes: --" << std::endl ;
	std::vector<uint8_t> bytes{0xA1, 0xA2, 0xA3, 0xA4} ;
	ByteTransfer::dump(bytes) ;

	std::vector<uint8_t> spibytes( spi.writeBytes(0x11, bytes)) ;
	std::cout << "SPI bytes [24, 22..16] wr 0x11:" << std::endl ;
	ByteTransfer::dump(spibytes) ;

	ASSERT_EQ(3ul, spibytes.size()) ;

	EXPECT_EQ(0x11u, spibytes[0]) ;
	EXPECT_EQ(0xA3u, spibytes[1]) ;
	EXPECT_EQ(0xA4u, spibytes[2]) ;
	}

	{
	SpiBusTest spi(32, 4, 0, false, 0) ;
	spi.setDebug(true) ;

	std::cout << "-- Initial bytes: --" << std::endl ;
	std::vector<uint8_t> bytes{0xB1, 0xB2, 0xB3} ;
	ByteTransfer::dump(bytes) ;

	std::vector<uint8_t> spibytes( spi.writeBytes(0x2, bytes)) ;
	std::cout << "SPI bytes [32, 4..0] wr 0x2:" << std::endl ;
	ByteTransfer::dump(spibytes) ;

	ASSERT_EQ(4ul, spibytes.size()) ;

	EXPECT_EQ(0x16u, spibytes[0]) ;
	EXPECT_EQ(0x36u, spibytes[1]) ;
	EXPECT_EQ(0x56u, spibytes[2]) ;
	EXPECT_EQ(0x62u, spibytes[3]) ;
	}


}
