/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SetVal_unittest.cpp
 * \brief     Google Test of SetVal
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the SetVal class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "SetVal.hpp"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(SetVal, Int)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::stringstream ss ;

	// default constructor
	SetVal<int> val1 ;
	EXPECT_FALSE(val1.isSet()) ;
	EXPECT_EQ(0, val1.get()) ;
	ss.str("") ;
	ss << val1 ;
	EXPECT_EQ("UNSET", ss.str()) ;

	// assignment
	val1 = 10 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_EQ(10, val1.get()) ;
	ss.str("") ;
	ss << val1 ;
	EXPECT_EQ("10", ss.str()) ;

	// copy constructor
	SetVal<int> val2(val1) ;
	EXPECT_TRUE(val2.isSet()) ;
	EXPECT_EQ(10, val2.get()) ;

	// value constructor
	SetVal<int> val3(30) ;
	EXPECT_TRUE(val3.isSet()) ;
	EXPECT_EQ(30, val3.get()) ;

	// assignment
	val1 = val3 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_EQ(30, val1.get()) ;

	// clear
	val1.clear() ;
	EXPECT_FALSE(val1.isSet()) ;
	EXPECT_EQ(0, val1.get()) ;

	val1 = val2 ;

	// compare
	EXPECT_TRUE(val1 == val2) ;
	EXPECT_TRUE(val1 == 10) ;
	EXPECT_FALSE(val3 == val2) ;
	EXPECT_FALSE(val3 == 10) ;

	// swap
	using std::swap ;
	swap(val1, val3) ;
	EXPECT_TRUE(val3 == val2) ;
	EXPECT_TRUE(val3 == 10) ;
	EXPECT_FALSE(val1 == val2) ;
	EXPECT_FALSE(val1 == 10) ;
	EXPECT_TRUE(val1 == 30) ;

}
