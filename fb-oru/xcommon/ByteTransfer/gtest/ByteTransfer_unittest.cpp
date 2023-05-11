/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ByteTransfer_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "ByteTransfer.hpp"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(ByteTransfer, BigEndian)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<uint8_t> data(32, 0) ;

	uint16_t sval(0x0102) ;
	uint32_t val24(0x030405) ;
	uint32_t wval(0x06070809) ;

	unsigned idx(0) ;
	ByteTransfer::writeShort(idx, data, sval) ;
	EXPECT_EQ(2u, idx) ;
	EXPECT_EQ(0x01, data[0]) ;
	EXPECT_EQ(0x02, data[1]) ;

	ByteTransfer::write24bit(idx, data, val24) ;
	EXPECT_EQ(5u, idx) ;
	EXPECT_EQ(0x03, data[2]) ;
	EXPECT_EQ(0x04, data[3]) ;
	EXPECT_EQ(0x05, data[4]) ;

	ByteTransfer::writeWord(idx, data, wval) ;
	EXPECT_EQ(9u, idx) ;
	EXPECT_EQ(0x06, data[5]) ;
	EXPECT_EQ(0x07, data[6]) ;
	EXPECT_EQ(0x08, data[7]) ;
	EXPECT_EQ(0x09, data[8]) ;


	EXPECT_EQ(0x01, data[0]) ;
	EXPECT_EQ(0x02, data[1]) ;
	EXPECT_EQ(0x03, data[2]) ;
	EXPECT_EQ(0x04, data[3]) ;
	EXPECT_EQ(0x05, data[4]) ;
	EXPECT_EQ(0x06, data[5]) ;
	EXPECT_EQ(0x07, data[6]) ;
	EXPECT_EQ(0x08, data[7]) ;
	EXPECT_EQ(0x09, data[8]) ;


	//---------------------------------------------------
	idx = 0 ;
	uint16_t sval2 = ByteTransfer::readShort(idx, data) ;
	EXPECT_EQ(sval, sval2) ;
	uint32_t val24_2 = ByteTransfer::read24bit(idx, data) ;
	EXPECT_EQ(val24, val24_2) ;
	uint32_t wval2 = ByteTransfer::readWord(idx, data) ;
	EXPECT_EQ(wval, wval2) ;


	//---------------------------------------------------
	std::vector<uint8_t> data2 ;
	ByteTransfer::appendShort(data2, sval) ;
	ByteTransfer::append24bit(data2, val24) ;
	ByteTransfer::appendWord(data2, wval) ;

	ASSERT_EQ(9u, data2.size()) ;
	for (unsigned i=0; i < data2.size(); ++i)
	{
		EXPECT_EQ(data[i], data2[i]) ;
	}


	//---------------------------------------------------
	std::vector<uint8_t> data3(32, 0) ;
	auto d3(data3.begin()) ;
	ByteTransfer::writeShort(d3, data3.end(), sval) ;
	ByteTransfer::write24bit(d3, data3.end(), val24) ;
	ByteTransfer::writeWord(d3, data3.end(), wval) ;

	for (unsigned i=0; i < data3.size(); ++i)
	{
		EXPECT_EQ(data[i], data3[i]) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
TEST(ByteTransfer, LittleEndian)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<uint8_t> data(32, 0) ;

	uint16_t sval(0x0102) ;
	uint32_t val24(0x030405) ;
	uint32_t wval(0x06070809) ;

	unsigned idx(0) ;
	ByteTransfer::writeShortLE(idx, data, sval) ;
	EXPECT_EQ(2u, idx) ;
	EXPECT_EQ(0x02, data[0]) ;
	EXPECT_EQ(0x01, data[1]) ;

	ByteTransfer::write24bitLE(idx, data, val24) ;
	EXPECT_EQ(5u, idx) ;
	EXPECT_EQ(0x05, data[2]) ;
	EXPECT_EQ(0x04, data[3]) ;
	EXPECT_EQ(0x03, data[4]) ;

	ByteTransfer::writeWordLE(idx, data, wval) ;
	EXPECT_EQ(9u, idx) ;
	EXPECT_EQ(0x09, data[5]) ;
	EXPECT_EQ(0x08, data[6]) ;
	EXPECT_EQ(0x07, data[7]) ;
	EXPECT_EQ(0x06, data[8]) ;


	EXPECT_EQ(0x02, data[0]) ;
	EXPECT_EQ(0x01, data[1]) ;
	EXPECT_EQ(0x05, data[2]) ;
	EXPECT_EQ(0x04, data[3]) ;
	EXPECT_EQ(0x03, data[4]) ;
	EXPECT_EQ(0x09, data[5]) ;
	EXPECT_EQ(0x08, data[6]) ;
	EXPECT_EQ(0x07, data[7]) ;
	EXPECT_EQ(0x06, data[8]) ;


	//---------------------------------------------------
	idx = 0 ;
	uint16_t sval2 = ByteTransfer::readShortLE(idx, data) ;
	EXPECT_EQ(sval, sval2) ;
	uint32_t val24_2 = ByteTransfer::read24bitLE(idx, data) ;
	EXPECT_EQ(val24, val24_2) ;
	uint32_t wval2 = ByteTransfer::readWordLE(idx, data) ;
	EXPECT_EQ(wval, wval2) ;

	//---------------------------------------------------
	std::vector<uint8_t> data2 ;
	ByteTransfer::appendShortLE(data2, sval) ;
	ByteTransfer::append24bitLE(data2, val24) ;
	ByteTransfer::appendWordLE(data2, wval) ;

	ASSERT_EQ(9u, data2.size()) ;
	for (unsigned i=0; i < data2.size(); ++i)
	{
		EXPECT_EQ(data[i], data2[i]) ;
	}

	//---------------------------------------------------
	std::vector<uint8_t> data3(32, 0) ;
	auto d3(data3.begin()) ;
	ByteTransfer::writeShortLE(d3, data3.end(), sval) ;
	ByteTransfer::write24bitLE(d3, data3.end(), val24) ;
	ByteTransfer::writeWordLE(d3, data3.end(), wval) ;

	for (unsigned i=0; i < data3.size(); ++i)
	{
		EXPECT_EQ(data[i], data3[i]) ;
	}

}
