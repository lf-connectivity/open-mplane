/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Crypt_unittest.cpp
 * \brief     Google Test of Crypt
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Crypt class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#if 0
#ifdef OFF_TARGET
#include "Path.h"
#endif
#endif

#include "ByteTransfer.hpp"
#include "Crypt.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(Crypt, DataAligned)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Data is aligned on 64-bit boundary
	std::string testData = "This is some test data\nWith another line of stuff\nAnd another\nEM" ;
    std::vector<uint8_t> in(testData.begin(), testData.end()) ;

    std::cout << "Input data:" << std::endl ;
    ByteTransfer::dump(in) ;

    // Encrypt
    std::vector<uint8_t> encrypted ;
    Crypt crypt({0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface}) ;
    EXPECT_TRUE(crypt.encrypt(in, encrypted)) ;
//    EXPECT_EQ(in.size(), encrypted.size()) ;
    EXPECT_NE(in[0], encrypted[0]) ;

    std::cout << "Encrypted:" << std::endl ;
    ByteTransfer::dump(encrypted) ;

    // Decrypt
    std::vector<uint8_t> decrypted ;
    EXPECT_TRUE(crypt.decrypt(encrypted, decrypted)) ;
//    EXPECT_EQ(in.size(), decrypted.size()) ;
    EXPECT_EQ(in[0], decrypted[0]) ;

    std::cout << "Decrypted:" << std::endl ;
    ByteTransfer::dump(decrypted) ;


    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

}

//-------------------------------------------------------------------------------------------------------------
TEST(Crypt, DataMisAligned)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Data is *NOT* aligned on 64-bit boundary
	std::string testData = "This is some test data\nWith another line of stuff\nAnd another\nEOM" ;
    std::vector<uint8_t> in(testData.begin(), testData.end()) ;

    std::cout << "Input data:" << std::endl ;
    ByteTransfer::dump(in) ;

    // Encrypt
    std::vector<uint8_t> encrypted ;
    Crypt crypt({0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface}) ;
    EXPECT_TRUE(crypt.encrypt(in, encrypted)) ;
//    EXPECT_EQ(in.size(), encrypted.size()) ;
    EXPECT_NE(in[0], encrypted[0]) ;

    std::cout << "Encrypted:" << std::endl ;
    ByteTransfer::dump(encrypted) ;

    // Decrypt
    std::vector<uint8_t> decrypted ;
    EXPECT_TRUE(crypt.decrypt(encrypted, decrypted)) ;
//    EXPECT_EQ(in.size(), decrypted.size()) ;
    EXPECT_EQ(in[0], decrypted[0]) ;

    std::cout << "Decrypted:" << std::endl ;
    ByteTransfer::dump(decrypted) ;


    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

}

#if 0
#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
TEST(Crypt, File)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    std::string filename("../../../crypt/gtest/test/LTE_TDD38-1_10M_TM31_15.36MSPS.art") ;

    unsigned long len = Path::fileSize(filename);

    std::vector<uint8_t> in(len) ;
    std::ifstream file(filename, std::ios::binary);
    EXPECT_TRUE(file.read( (char *)in.data(), len)) ;

    // Encrypt
    std::vector<uint8_t> encrypted ;
    Crypt crypt({0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface}) ;
    crypt.encrypt(in, encrypted) ;
//    EXPECT_EQ(in.size(), encrypted.size()) ;
    EXPECT_NE(in[0], encrypted[0]) ;

    std::vector<uint8_t> encrypted2 ;
    crypt.encrypt(encrypted, encrypted2) ;
//    EXPECT_EQ(in.size(), encrypted2.size()) ;
    EXPECT_NE(in[0], encrypted2[0]) ;
    EXPECT_NE(encrypted[0], encrypted2[0]) ;


    // Decrypt
    std::vector<uint8_t> decrypted ;
    crypt.decrypt(encrypted, decrypted) ;
    EXPECT_EQ(in.size(), decrypted.size()) ;
    EXPECT_EQ(in[0], decrypted[0]) ;
    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

    std::vector<uint8_t> decrypted2 ;
    crypt.decrypt(encrypted2, decrypted2) ;
//    EXPECT_EQ(in.size(), decrypted2.size()) ;
    EXPECT_NE(in[0], decrypted2[0]) ;

    crypt.decrypt(decrypted2, decrypted) ;
//    EXPECT_EQ(in.size(), decrypted.size()) ;
    EXPECT_EQ(in[0], decrypted[0]) ;
    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

}
#endif
#endif


//-------------------------------------------------------------------------------------------------------------
TEST(Crypt, Header)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Data is *NOT* aligned on 64-bit boundary

	std::string header = "HEADER\n" ;
	unsigned headLen(header.size()) ;
	std::string testData =
			header +
			"This is some test data\nWith another line of stuff\nAnd another\nEOM" ;
    std::vector<uint8_t> in(testData.begin(), testData.end()) ;

    std::cout << "Input data:" << std::endl ;
    ByteTransfer::dump(in) ;

    // Encrypt
    std::vector<uint8_t> encrypted(header.begin(), header.end()) ;
    Crypt crypt({0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface}) ;
    EXPECT_TRUE(crypt.encrypt(in.begin()+headLen, in.end(), encrypted)) ;
    EXPECT_EQ(in[0], encrypted[0]) ;
    EXPECT_NE(in[headLen], encrypted[headLen]) ;

    std::cout << "Encrypted:" << std::endl ;
    ByteTransfer::dump(encrypted) ;

    // Decrypt
    std::vector<uint8_t> decrypted(header.begin(), header.end()) ;
    EXPECT_TRUE(crypt.decrypt(encrypted.begin()+headLen, encrypted.end(), decrypted)) ;
    EXPECT_EQ(in[0], decrypted[0]) ;

    std::cout << "Decrypted:" << std::endl ;
    ByteTransfer::dump(decrypted) ;


    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

}

//-------------------------------------------------------------------------------------------------------------
TEST(Crypt, TestData)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	unsigned size(64) ;
	std::vector<uint8_t> in(size) ;
	for (unsigned byte=0; byte < in.size(); ++byte)
	{
		in[byte] = (uint8_t)(byte & 0xff) ;
	}

    std::cout << "Input data:" << std::endl ;
    ByteTransfer::dump(in) ;

    // Encrypt
    std::vector<uint8_t> encrypted ;
//    Crypt crypt({0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface}) ;
    Crypt crypt({0x33383337, 0xe222f229, 0xc111d111, 0x0a00b000}) ;
    EXPECT_TRUE(crypt.encrypt(in.begin(), in.end(), encrypted)) ;
    EXPECT_NE(in[0], encrypted[0]) ;

    std::cout << "Encrypted:" << std::endl ;
    ByteTransfer::dump(encrypted) ;

    // Decrypt
    std::vector<uint8_t> decrypted ;
    EXPECT_TRUE(crypt.decrypt(encrypted.begin(), encrypted.end(), decrypted)) ;
    EXPECT_EQ(in[0], decrypted[0]) ;

    std::cout << "Decrypted:" << std::endl ;
    ByteTransfer::dump(decrypted) ;


    for (unsigned idx=0; idx < in.size(); ++idx)
    {
    	ASSERT_EQ(in[idx], decrypted[idx]) ;
    }

}
