/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Base64_unittest.cpp
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

#include "Base64.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(Base64, Rfc4648)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	EXPECT_EQ("", Base64::encode("")) ;
	EXPECT_EQ("Zg==", Base64::encode("f")) ;
	EXPECT_EQ("Zm8=", Base64::encode("fo")) ;
	EXPECT_EQ("Zm9v", Base64::encode("foo")) ;
	EXPECT_EQ("Zm9vYg==", Base64::encode("foob")) ;
	EXPECT_EQ("Zm9vYmE=", Base64::encode("fooba")) ;
	EXPECT_EQ("Zm9vYmFy", Base64::encode("foobar")) ;

	EXPECT_EQ("", Base64::decode("")) ;
	EXPECT_EQ("f", Base64::decode("Zg==")) ;
	EXPECT_EQ("fo", Base64::decode("Zm8=")) ;
	EXPECT_EQ("foo", Base64::decode("Zm9v")) ;
	EXPECT_EQ("foob", Base64::decode("Zm9vYg==")) ;
	EXPECT_EQ("fooba", Base64::decode("Zm9vYmE=")) ;
	EXPECT_EQ("foobar", Base64::decode("Zm9vYmFy")) ;
}
