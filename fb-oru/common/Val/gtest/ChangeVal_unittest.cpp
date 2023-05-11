/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ChangeVal_unittest.cpp
 * \brief     Google Test of ChangeVal
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ChangeVal class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "ChangeVal.hpp"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(ChangeVal, IntSet)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::stringstream ss ;

	// default constructor
	ChangeVal<int> val1 ;
	EXPECT_FALSE(val1.isSet()) ;
	EXPECT_EQ(0, val1.get()) ;
	EXPECT_FALSE(val1.isChanged()) ;
	ss.str("") ;
	ss << val1 ;
	EXPECT_EQ("UNSET", ss.str()) ;

	// assignment
	val1 = 10 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_EQ(10, val1.get()) ;
	EXPECT_TRUE(val1.isChanged()) ;
	ss.str("") ;
	ss << val1 ;
	EXPECT_EQ("10*", ss.str()) ;

	// copy constructor
	ChangeVal<int> val2(val1) ;
	EXPECT_TRUE(val2.isSet()) ;
	EXPECT_EQ(10, val2.get()) ;
	EXPECT_TRUE(val2.isChanged()) ;

	// value constructor
	ChangeVal<int> val3(30) ;
	EXPECT_TRUE(val3.isSet()) ;
	EXPECT_EQ(30, val3.get()) ;
	EXPECT_FALSE(val3.isChanged()) ;
	ss.str("") ;
	ss << val3 ;
	EXPECT_EQ("30", ss.str()) ;

	// assignment from another ChangeVal is same as copy
	val1 = val3 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_EQ(30, val1.get()) ;
	EXPECT_FALSE(val1.isChanged()) ;
	val1 = 0 ;
	val1 = 30 ;
	EXPECT_TRUE(val1.isChanged()) ;

	ChangeVal<int> val4(10) ;
	val2 = val4 ;
	EXPECT_FALSE(val2.isChanged()) ;

	// val1: 30 changed
	// val2: 10
	// val3: 30
	// val4: 10

	// compare
	EXPECT_TRUE(val1 == val3) ;
	EXPECT_TRUE(val1 == 30) ;
	EXPECT_TRUE(val1.isChanged()) ;
	EXPECT_FALSE(val2 == val3) ;
	EXPECT_FALSE(val2 == 30) ;
	EXPECT_FALSE(val2.isChanged()) ;

	// swap
	using std::swap ;
	swap(val1, val2) ;
	EXPECT_TRUE(val2 == val3) ;
	EXPECT_TRUE(val2 == 30) ;
	EXPECT_TRUE(val2.isChanged()) ;
	EXPECT_FALSE(val1 == val3) ;
	EXPECT_FALSE(val1 == 30) ;
	EXPECT_FALSE(val1.isChanged()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(ChangeVal, IntChange)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// default constructor
	ChangeVal<int> val1 ;
	EXPECT_FALSE(val1.isSet()) ;
	EXPECT_FALSE(val1.isChanged()) ;
	EXPECT_EQ(0, val1.get()) ;

	val1 = 10 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_TRUE(val1.isChanged()) ;
	EXPECT_EQ(10, val1.get()) ;

	val1.acceptChange() ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_FALSE(val1.isChanged()) ;
	EXPECT_EQ(10, val1.get()) ;

	val1 = 10 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_FALSE(val1.isChanged()) ;
	EXPECT_EQ(10, val1.get()) ;

	val1 = 20 ;
	EXPECT_TRUE(val1.isSet()) ;
	EXPECT_TRUE(val1.isChanged()) ;
	EXPECT_EQ(20, val1.get()) ;
}
