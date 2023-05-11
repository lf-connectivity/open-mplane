/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crc_unittest.cpp
 * \brief     Google Test of Crc
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Crc class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "ByteTransfer.hpp"
#include "Crc.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(Crc, Test1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<uint8_t> data1 ;
	for (unsigned i=0; i <= 255; ++i)
	{
		data1.push_back(i) ;
	}
	uint32_t crc1 = Crc32::calc(0, &data1[0], data1.size()) ;
	std::cout << "Data1 CRC: 0x" << std::hex << crc1 << std::dec << std::endl ;
	EXPECT_EQ(0x29058c73u, crc1) ;

	uint32_t crc = Crc32::calc(0x29058c73, &data1[0], data1.size()) ;
	std::cout << "Data1 CRC: 0x" << std::hex << crc << std::dec << std::endl ;
//	EXPECT_EQ(0x29058c73u, crc) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Crc, Test2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::vector<uint8_t> data2 ;
	for (unsigned i=0; i <= 2047; ++i)
	{
		data2.push_back( (3*i) & 0xff ) ;
	}
	uint32_t crc2 = Crc32::calc(0, data2) ;
	std::cout << "Data2 CRC: 0x" << std::hex << crc2 << std::dec << std::endl ;
	EXPECT_EQ(0x31293fc6u, crc2) ;

	uint32_t crc = Crc32::calc(0x31293fc6, data2) ;
	std::cout << "Data2 CRC: 0x" << std::hex << crc << std::dec << std::endl ;
//	EXPECT_EQ(0x31293fc6u, crc) ;

}
