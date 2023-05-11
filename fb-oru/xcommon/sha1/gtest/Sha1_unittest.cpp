/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sha1_unittest.cpp
 * \brief     Google Test of Sha1
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Sha1 class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "Sha1.h"

using namespace Mplane ;

#if 0
static void dump(const std::vector<uint8_t>& data)
{
	for (unsigned idx=0; idx < data.size(); )
	{
		for (unsigned byte=0; byte < 16 && idx < data.size(); ++byte, ++idx)
		{
			printf("0x%02x ", data[idx]) ;
		}
		std::cout << std::endl ;
	}
	std::cout << std::endl ;

	for (unsigned idx=0; idx < data.size(); )
	{
		for (unsigned byte=0; byte < 16 && idx < data.size(); ++byte, ++idx)
		{
			if (isprint(data[idx]))
				std::cout << (char)data[idx] ;
			else
				std::cout << "." ;
		}
		std::cout << std::endl ;
	}
	std::cout << std::endl ;
}
#endif

//-------------------------------------------------------------------------------------------------------------
TEST(Sha1, Test1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string test("The quick brown fox jumps over the lazy dog") ;
	std::string expectedHash("2fd4e1c67a2d28fced849ee1bb76e7391b93eb12") ;

	std::string hash(Sha1::getHashString(test)) ;
	std::cerr << "STRING: " << test << "  HASH: " << hash << std::endl ;
	EXPECT_EQ(expectedHash, hash) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Sha1, Test2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string test("The quick brown fox jumps over the lazy cog") ;
	std::string expectedHash("de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3") ;

	std::string hash(Sha1::getHashString(test)) ;
	std::cerr << "STRING: " << test << "  HASH: " << hash << std::endl ;
	EXPECT_EQ(expectedHash, hash) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Sha1, Test3)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    std::string test ;
    for (int i = 0; i < 1000; ++i)
    {
        test += std::to_string(i % 10) ;
    }
	std::string hash(Sha1::getHashString(test)) ;
	std::cerr << "STRING: " << test << "  HASH: " << hash << std::endl ;

	std::string expectedHash("f2b2f38b074c387a1415c3afb834c7232f31b097") ;
	EXPECT_EQ(expectedHash, hash) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Sha1, Test4)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    std::vector<uint8_t> test ;
    for (int i = 0; i < 1000; ++i)
    {
        test.push_back( static_cast<uint8_t>(i & 0xff) ) ;
    }
//	std::string hash(Sha1::getHashString(test)) ;
//	std::cerr << "  HASH: " << hash << std::endl ;
//
//	std::string expectedHash("af0b191c2de46fe13fe0908f5a6a4e90e0cafc46") ;
//	EXPECT_EQ(expectedHash, hash) ;

	std::vector<uint8_t> hashBytes(Sha1::getHash(test)) ;
	std::vector<uint8_t> hashName(Sha1::getHash("atestfile.txt")) ;

	std::vector<uint8_t> combined(hashBytes) ;
	combined.insert(combined.end(), hashName.begin(), hashName.end()) ;

	std::string hashNameStr(Sha1::getHashString("atestfile.txt")) ;
	std::string hashBytesStr(Sha1::getHashString(test)) ;
	std::cerr << "  NAME HASH: " << hashNameStr << std::endl ;
	std::cerr << "  DATA HASH: " << hashBytesStr << std::endl ;

	std::string hash(Sha1::getHashString(combined)) ;
	std::cerr << "  COMBINED HASH: " << hash << std::endl ;
}
