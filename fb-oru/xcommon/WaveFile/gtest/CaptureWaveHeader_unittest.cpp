/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CaptureWaveHeader_unittest.cpp
 * \brief     Google Test of CaptureWaveHeader
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the CaptureWaveHeader class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "IWaveFile.h"
#include "ByteTransfer.hpp"
#include "CaptureWaveHeader.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(CaptureWaveHeader, CaptureComplete)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Create some data with a header
	CaptureWaveHeader header ;
	std::vector<uint8_t> data ;
	unsigned waveIndex{13} ;
	header.createHeader(data, waveIndex, 15360) ;
	header.createBlockHeader(data, IWaveFile::WaveBlockType::RAW, 32) ;

	// dummy data
	for (unsigned iq=0; iq < 8; ++iq)
	{
		ByteTransfer::appendShort(data, 0x8900+iq) ;
		ByteTransfer::appendShort(data, 0x3400+iq) ;
	}

	ByteTransfer::dump(data) ;


	// Now try reading using the header class
	IWaveFile::WaveDataIter dataStart(data.begin()) ;
	IWaveFile::WaveDataIter dataEnd(data.end()) ;

	std::cerr << "Data: " << std::distance(dataStart, dataEnd) << " bytes" << std::endl ;
	ByteTransfer::dump(dataStart, dataEnd) ;

	EXPECT_TRUE(header.processHeader(dataStart, dataEnd)) ;
	EXPECT_EQ("", header.getError()) ;
	EXPECT_EQ(13u, header.getWaveIndex()) ;
	EXPECT_EQ(15360u, header.getSampleRateKsps()) ;

	std::cerr << "Data after reading header: " << std::distance(dataStart, dataEnd) << " bytes" << std::endl ;
	ByteTransfer::dump(dataStart, dataEnd) ;

	EXPECT_TRUE(header.processBlockHeader(dataStart, dataEnd)) ;
	EXPECT_EQ("", header.getError()) ;
	EXPECT_EQ(32u, header.getBlockLength()) ;

	std::cerr << "Data after reading block header: " << std::distance(dataStart, dataEnd) << " bytes" << std::endl ;
	ByteTransfer::dump(dataStart, dataEnd) ;

	for (unsigned iq=0; iq < 8; ++iq)
	{
		EXPECT_EQ(0x89, *dataStart++) ;
		EXPECT_EQ((uint8_t)iq, *dataStart++) ;
		EXPECT_EQ(0x34, *dataStart++) ;
		EXPECT_EQ((uint8_t)iq, *dataStart++) ;
	}
}
