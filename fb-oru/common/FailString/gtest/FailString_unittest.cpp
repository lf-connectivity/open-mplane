/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FailString_unittest.cpp
 * \brief     Google Test of FailString
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FailString class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include "FailString.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(FailString, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    FailString fs ;

    EXPECT_EQ(std::string(""), fs.failReason()) ;

    // set string
    fs.setFailReason("reason1") ;
    EXPECT_EQ(std::string("reason1"), fs.failReason()) ; // first read also clears
    EXPECT_EQ(std::string(""), fs.failReason()) ;

    // check clear
    fs.setFailReason("reason2") ;
    fs.clearFailReason() ;
    EXPECT_EQ(std::string(""), fs.failReason()) ;
}
