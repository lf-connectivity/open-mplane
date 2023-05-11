/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Key_unittest.cpp
 * \brief     Google Test of Key
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Key class.
 *
 */

#include <gtest/gtest.h>

#include <time.h>

#include <random>
#include <bitset>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "Key.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(Key, Key)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Key key ;

	EXPECT_FALSE(key.isSet()) ;

	// set the license key directly from string
	std::string license("0a00b000c111d111e222f22933383337") ;
	EXPECT_TRUE(key.setLicenseKey(license)) ;
	EXPECT_TRUE(key.isSet()) ;

	std::string encodedKey(key.encodedKey()) ;
	std::cerr << "License: " << license << " Encoded: " << encodedKey << std::endl ;

	// try setting it again, this time via the encoded key
	Key key2 ;
	EXPECT_FALSE(key2.isSet()) ;
	EXPECT_TRUE(key2.setFromEncodedKey(encodedKey)) ;
	EXPECT_TRUE(key2.isSet()) ;

	// The 2 keys should be the same and encode the feature bits the same
	uint32_t val(0xfeedface) ;
	std::string encoded1(key.encode32bits(val)) ;
	std::string encoded2(key2.encode32bits(val)) ;
	EXPECT_EQ(encoded1, encoded2) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Key, SerialNum)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// Use the factory to create a license key based on board serial
	// serial="B0A-00053V15140038" hostid="00:24:24:25:19:09"
	//
	std::shared_ptr<IKey> key(IKey::factory("B0A-00053V15140038", "00:24:24:25:19:09", "not used")) ;
	ASSERT_TRUE(key.get() != 0) ;

//	INFO 'B0A-00053V15140038/00:24:24:25:19:09'
//        0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19
//	SHA1 '26 b9 72 11 55 a9 ce 2a 31 27 d7 53 e1 ab ae ee 99 55 ec d9'
//
//        6  13 1  14 10 19 2  7  12 0  4  16 3  5  17 18
//  KEY  'ce ab b9 ae d7 d9 72 2a e1 26 55 99 11 a9 55 ec'
//	License:  0x11a955ec 0xe1265599 0xd7d9722a 0xceabb9ae Encoded: 1c31fc4e10ad3618b5482892f30078d9

	EXPECT_TRUE(key->isSet()) ;
	std::vector<uint32_t> keyVal(key->licenseKey()) ;
	std::string encodedKey(key->encodedKey()) ;

	std::cerr <<
		"License: " <<
			std::hex <<
			std::setw(2) << std::setfill('0') <<
			" 0x" << keyVal[0] <<
			" 0x" << keyVal[1] <<
			" 0x" << keyVal[2] <<
			" 0x" << keyVal[3] <<
			std::dec <<
		" Encoded: " <<
		encodedKey <<
		std::endl ;

	EXPECT_EQ("1c31fc4e10ad3618b5482892f30078d9", encodedKey) ;
	EXPECT_EQ(0xceabb9aeu, keyVal[3]) ;
	EXPECT_EQ(0xd7d9722au, keyVal[2]) ;
	EXPECT_EQ(0xe1265599u, keyVal[1]) ;
	EXPECT_EQ(0x11a955ecu, keyVal[0]) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(Key, FeatureBits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Key key ;

	std::string encoded ;

	// must set a license key
	{
		uint32_t decoded ;
		EXPECT_FALSE( key.decode32bits(encoded, decoded)) ;
	}

	EXPECT_TRUE(key.setLicenseKey("00000000111111112222222233333333")) ;

	std::vector<uint32_t> testValues {
		0x00000000,
		0xAAAAAAAA,
		0x55555555,
		0xfeedface,
		0xdeadbeef,
		0xffffffff,
		0x00000001,
		0x00001001,
	} ;
	for (auto val : testValues)
	{
		encoded = key.encode32bits(val) ;
		uint32_t decoded ;
		EXPECT_TRUE( key.decode32bits(encoded, decoded)) ;
		std::cout << std::hex << "0x" << val << " " << encoded << " 0x" << decoded << std::endl ;
		EXPECT_EQ(val, decoded) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
TEST(Key, Invalid)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Key key ;

	EXPECT_FALSE(key.isSet()) ;

	EXPECT_FALSE(key.setLicenseKey("0a00b000c111d111e222f2293338333")) ;
	EXPECT_FALSE(key.isSet()) ;
	EXPECT_FALSE(key.setLicenseKey("0a00b000c111d111e222f229333833345")) ;
	EXPECT_FALSE(key.isSet()) ;
	EXPECT_FALSE(key.setLicenseKey("0a00z000c111d111e222f22933383334")) ;
	EXPECT_FALSE(key.isSet()) ;

	EXPECT_FALSE(key.setFromEncodedKey("0a00b000c111d111e222f2293338333")) ;
	EXPECT_FALSE(key.isSet()) ;
	EXPECT_FALSE(key.setFromEncodedKey("0a00b000c111d111e222f229333833345")) ;
	EXPECT_FALSE(key.isSet()) ;
	EXPECT_FALSE(key.setFromEncodedKey("0a00z000c111d111e222f22933383334")) ;
	EXPECT_FALSE(key.isSet()) ;

	// unset license should result in an invalid encoded key
	EXPECT_EQ("0", key.encodedKey()) ;

}

#if 0
//-------------------------------------------------------------------------------------------------------------
TEST(Key, KeyVals)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::default_random_engine generator( ::time(0) );
	std::uniform_int_distribution<unsigned> distribution;

	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;
	printf("0x%08x\n", distribution(generator)) ;

}
#endif


//-------------------------------------------------------------------------------------------------------------
TEST(Key, GlobalKey)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IKey> globalKey(IKey::getGlobalInstance()) ;
	EXPECT_TRUE(globalKey->isSet()) ;

	std::string encodedKey(globalKey->encodedKey()) ;
	std::cerr << "Global Encoded: " << encodedKey << std::endl ;

#if 1
	EXPECT_EQ("41636541786973476c6f62616c4b6579", encodedKey) ;
#else
// Mplane Proprietary
	EXPECT_EQ("01234567890abcdef01234567890abcd", encodedKey) ;
// Mplane Proprietary
#endif
// Mplane Proprietary
}


//-------------------------------------------------------------------------------------------------------------
TEST(Key, KeyRnd1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP3) ;
	Key key ;

	EXPECT_FALSE(key.isSet()) ;

	// set the license key directly from string
	std::string license("0a00b000c111d111e222f22933383337") ;
	EXPECT_TRUE(key.setLicenseKey(license)) ;
	EXPECT_TRUE(key.isSet()) ;

	Key keyNormal(IKey::KeyEncodeType::KEY_DUP4) ;
	EXPECT_TRUE(keyNormal.setLicenseKey(license)) ;

	std::string encodedKey(key.encodedKey()) ;
	std::cerr << "License: " << license << " Encoded: " << encodedKey << std::endl ;

	// try setting it again, this time via the encoded key
	Key key2 ;
	EXPECT_FALSE(key2.isSet()) ;
	EXPECT_TRUE(key2.setFromEncodedKey(encodedKey)) ;
	EXPECT_TRUE(key2.isSet()) ;

	// The 2 keys should be the same and decode the feature bits the same BUT the encoded bits should be
	// different
	uint32_t val(0xfeedface) ;
	std::string encoded1(key.encode32bits(val)) ;
	std::string encoded2(key2.encode32bits(val)) ;
	EXPECT_NE(encoded1, encoded2) ;

	uint32_t decoded1 ;
	EXPECT_TRUE(key.decode32bits(encoded1, decoded1)) ;
	uint32_t decoded2 ;
	EXPECT_TRUE(key.decode32bits(encoded2, decoded2)) ;

	EXPECT_EQ(val, decoded1) ;
	EXPECT_EQ(val, decoded2) ;

	// Encode/decode using normal key
	std::string encodedNormal(keyNormal.encode32bits(val)) ;
	EXPECT_NE(encodedNormal, encoded1) ;
	EXPECT_NE(encodedNormal, encoded2) ;

	uint32_t decodedNormal ;
	EXPECT_TRUE(key.decode32bits(encodedNormal, decodedNormal)) ;

	EXPECT_EQ(val, decodedNormal) ;


	// END
	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP4) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Key, KeyRnd2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP2) ;
	Key key ;

	EXPECT_FALSE(key.isSet()) ;

	// set the license key directly from string
	std::string license("0a00b000c111d111e222f22933383337") ;
	EXPECT_TRUE(key.setLicenseKey(license)) ;
	EXPECT_TRUE(key.isSet()) ;

	Key keyNormal(IKey::KeyEncodeType::KEY_DUP4) ;
	EXPECT_TRUE(keyNormal.setLicenseKey(license)) ;

	std::string encodedKey(key.encodedKey()) ;
	std::cerr << "License: " << license << " Encoded: " << encodedKey << std::endl ;

	// try setting it again, this time via the encoded key
	Key key2 ;
	EXPECT_FALSE(key2.isSet()) ;
	EXPECT_TRUE(key2.setFromEncodedKey(encodedKey)) ;
	EXPECT_TRUE(key2.isSet()) ;

	// The 2 keys should be the same and decode the feature bits the same BUT the encoded bits should be
	// different
	uint32_t val(0xfeedface) ;
	std::string encoded1(key.encode32bits(val)) ;
	std::string encoded2(key2.encode32bits(val)) ;
	EXPECT_NE(encoded1, encoded2) ;

	uint32_t decoded1 ;
	EXPECT_TRUE(key.decode32bits(encoded1, decoded1)) ;
	uint32_t decoded2 ;
	EXPECT_TRUE(key.decode32bits(encoded2, decoded2)) ;

	EXPECT_EQ(val, decoded1) ;
	EXPECT_EQ(val, decoded2) ;

	// Encode/decode using normal key
	std::string encodedNormal(keyNormal.encode32bits(val)) ;
	EXPECT_NE(encodedNormal, encoded1) ;
	EXPECT_NE(encodedNormal, encoded2) ;

	uint32_t decodedNormal ;
	EXPECT_TRUE(key.decode32bits(encodedNormal, decodedNormal)) ;

	EXPECT_EQ(val, decodedNormal) ;


	// END
	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP4) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Key, KeyRnd3)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP1) ;
	Key key ;

	EXPECT_FALSE(key.isSet()) ;

	// set the license key directly from string
	std::string license("0a00b000c111d111e222f22933383337") ;
	EXPECT_TRUE(key.setLicenseKey(license)) ;
	EXPECT_TRUE(key.isSet()) ;

	Key keyNormal(IKey::KeyEncodeType::KEY_DUP4) ;
	EXPECT_TRUE(keyNormal.setLicenseKey(license)) ;

	std::string encodedKey(key.encodedKey()) ;
	std::cerr << "License: " << license << " Encoded: " << encodedKey << std::endl ;

	// try setting it again, this time via the encoded key
	Key key2 ;
	EXPECT_FALSE(key2.isSet()) ;
	EXPECT_TRUE(key2.setFromEncodedKey(encodedKey)) ;
	EXPECT_TRUE(key2.isSet()) ;

	// The 2 keys should be the same and decode the feature bits the same BUT the encoded bits should be
	// different
	uint32_t val(0xfeedface) ;
	std::string encoded1(key.encode32bits(val)) ;
	std::string encoded2(key2.encode32bits(val)) ;
	EXPECT_NE(encoded1, encoded2) ;

	uint32_t decoded1 ;
	EXPECT_TRUE(key.decode32bits(encoded1, decoded1)) ;
	uint32_t decoded2 ;
	EXPECT_TRUE(key.decode32bits(encoded2, decoded2)) ;

	EXPECT_EQ(val, decoded1) ;
	EXPECT_EQ(val, decoded2) ;

	// Encode/decode using normal key
	std::string encodedNormal(keyNormal.encode32bits(val)) ;
	EXPECT_NE(encodedNormal, encoded1) ;
	EXPECT_NE(encodedNormal, encoded2) ;

	uint32_t decodedNormal ;
	EXPECT_TRUE(key.decode32bits(encodedNormal, decodedNormal)) ;

	EXPECT_EQ(val, decodedNormal) ;


	// END
	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP4) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(Key, FeatureRnd2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP2) ;
	Key key ;

	// set the license key directly from string
	std::string license("0a00b000c111d111e222f22933383337") ;
	EXPECT_TRUE(key.setLicenseKey(license)) ;
	EXPECT_TRUE(key.isSet()) ;

	Key keyNormal(IKey::KeyEncodeType::KEY_DUP4) ;
	EXPECT_TRUE(keyNormal.setLicenseKey(license)) ;


	// The 2 keys should be the same and decode the feature bits the same BUT the encoded bits should be
	// different
	uint32_t val(0x00000001) ;
	std::string encoded1(key.encode32bits(val)) ;
	std::string encoded2(key.encode32bits(val)) ;
	std::string encodedNormal(keyNormal.encode32bits(val)) ;
	EXPECT_NE(encoded1, encoded2) ;
	EXPECT_NE(encoded1, encodedNormal) ;

	uint32_t decoded1 ;
	EXPECT_TRUE(key.decode32bits(encoded1, decoded1)) ;
	uint32_t decoded2 ;
	EXPECT_TRUE(key.decode32bits(encoded2, decoded2)) ;

	EXPECT_EQ(val, decoded1) ;
	EXPECT_EQ(val, decoded2) ;

	std::cerr << "0x" << std::setfill('0') << std::setw(8) << std::hex << val <<
		" : " << encoded1 << " " << encoded2 << " : " << encodedNormal << std::endl ;


	val = 0x00000002 ;
	encoded1 = key.encode32bits(val) ;
	encoded2 = key.encode32bits(val) ;
	encodedNormal = keyNormal.encode32bits(val) ;

	std::cerr << "0x" << std::setfill('0') << std::setw(8) << std::hex << val <<
		" : " << encoded1 << " " << encoded2 << " : " << encodedNormal << std::endl ;



	// END
	IKey::setKeyEncodeType(IKey::KeyEncodeType::KEY_DUP4) ;
}
