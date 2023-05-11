/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant_unittest.cpp
 * \brief     Google Test of DataVariant
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the DataVariant class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "DataVariant/Limits.hpp"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Invalid)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<int> lim1 ;


	// Invalid
	EXPECT_FALSE(lim1.set("1")) ;
	std::cerr << "invalid " << lim1 << std::endl ;
	EXPECT_FALSE(lim1.set("..")) ;
	std::cerr << "invalid " << lim1 << std::endl ;
	EXPECT_FALSE(lim1.set("")) ;
	std::cerr << "invalid " << lim1 << std::endl ;
	EXPECT_FALSE(lim1.set("/")) ;
	std::cerr << "invalid " << lim1 << std::endl ;
	EXPECT_FALSE(lim1.set("../")) ;
	std::cerr << "invalid " << lim1 << std::endl ;
	EXPECT_FALSE(lim1.set("a..b")) ;
	std::cerr << "invalid " << lim1 << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Int)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<int> lim1 ;

	// range
	EXPECT_TRUE(lim1.set("1..2/3")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("3", lim1.getStep()) ;

	Limits<int> lim2(lim1) ;
	std::cerr << "range " << lim2 << std::endl ;
	EXPECT_TRUE(lim2.check(1)) ;
	EXPECT_TRUE(lim2.check(2)) ;
	EXPECT_FALSE(lim2.check(0)) ;
	EXPECT_FALSE(lim2.check(-1)) ;
	EXPECT_FALSE(lim2.check(3)) ;
	EXPECT_EQ("1", lim2.getMin()) ;
	EXPECT_EQ("2", lim2.getMax()) ;
	EXPECT_EQ("3", lim2.getStep()) ;

	Limits<int> lim3 = lim1 ;
	std::cerr << "range " << lim3 << std::endl ;
	EXPECT_TRUE(lim3.check(1)) ;
	EXPECT_TRUE(lim3.check(2)) ;
	EXPECT_FALSE(lim3.check(0)) ;
	EXPECT_FALSE(lim3.check(-1)) ;
	EXPECT_FALSE(lim3.check(3)) ;
	EXPECT_EQ("1", lim3.getMin()) ;
	EXPECT_EQ("2", lim3.getMax()) ;
	EXPECT_EQ("3", lim3.getStep()) ;

	EXPECT_TRUE(lim1.set("1..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("-1..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(-2)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("-1", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2/3")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("3", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("..2")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	// MIN
	EXPECT_TRUE(lim1.set("1../3")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("", lim1.getMax()) ;
	EXPECT_EQ("3", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("1..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(Limits, IntReverse)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<int> lim1 ;

	// range
	EXPECT_TRUE(lim1.set("2..1/3")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("3", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("2..1")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Float1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<float> lim1 ;

	// range
	EXPECT_TRUE(lim1.set("1..2/3")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("1..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("-1..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(-2)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2/3")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("..2")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MIN
	EXPECT_TRUE(lim1.set("1../3")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("1..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Float2)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<float> lim1 ;

	// range
	EXPECT_TRUE(lim1.set("1.1..2.1/3.1")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1.1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1.0)) ;
	EXPECT_FALSE(lim1.check(3.0)) ;

	EXPECT_TRUE(lim1.set("1.0..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("-1.0..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(-2)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2.0/3")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("..2.0")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MIN
	EXPECT_TRUE(lim1.set("1.0../3")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("1.0..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(Limits, IntVar)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<int> lim1 ;

	// range
	EXPECT_TRUE(lim1.set("1..${MAX}/3")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("${MAX}", lim1.getMax()) ;
	EXPECT_EQ("3", lim1.getStep()) ;

	Limits<int> lim2(lim1) ;
	std::cerr << "range " << lim2 << std::endl ;
	EXPECT_EQ("1", lim2.getMin()) ;
	EXPECT_EQ("${MAX}", lim2.getMax()) ;
	EXPECT_EQ("3", lim2.getStep()) ;

	Limits<int> lim3 = lim1 ;
	std::cerr << "range " << lim3 << std::endl ;
	EXPECT_EQ("1", lim3.getMin()) ;
	EXPECT_EQ("${MAX}", lim3.getMax()) ;
	EXPECT_EQ("3", lim3.getStep()) ;

	EXPECT_TRUE(lim1.set("${MIN}..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_EQ("${MIN}", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("-1..${MAX}")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_EQ("-1", lim1.getMin()) ;
	EXPECT_EQ("${MAX}", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2/${STEP}")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_EQ("", lim1.getMin()) ;
	EXPECT_EQ("2", lim1.getMax()) ;
	EXPECT_EQ("${STEP}", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("..${MAX}")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_EQ("", lim1.getMin()) ;
	EXPECT_EQ("${MAX}", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;

	// MIN
	EXPECT_TRUE(lim1.set("1../${STEP}")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_EQ("1", lim1.getMin()) ;
	EXPECT_EQ("", lim1.getMax()) ;
	EXPECT_EQ("${STEP}", lim1.getStep()) ;

	EXPECT_TRUE(lim1.set("${MIN}..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_EQ("${MIN}", lim1.getMin()) ;
	EXPECT_EQ("", lim1.getMax()) ;
	EXPECT_EQ("", lim1.getStep()) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Frequency)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<Frequency> lim1 ;
	lim1.setUnits("KHz") ;

	// range
	EXPECT_TRUE(lim1.set("1.1..2.1/3.1")) ;
	std::cerr << "range " << lim1 << std::endl ;


	EXPECT_TRUE(lim1.check(Frequency(1.1, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_FALSE(lim1.check(Frequency(3.0, Frequency::KHz))) ;

	EXPECT_TRUE(lim1.set("1.0..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_FALSE(lim1.check(Frequency(3.0, Frequency::KHz))) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2.0/3")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_FALSE(lim1.check(Frequency(3.0, Frequency::KHz))) ;

	EXPECT_TRUE(lim1.set("..2.0")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_FALSE(lim1.check(Frequency(3.0, Frequency::KHz))) ;

	// MIN
	EXPECT_TRUE(lim1.set("1.0../3")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_TRUE(lim1.check(Frequency(3.0, Frequency::KHz))) ;

	EXPECT_TRUE(lim1.set("1.0..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(Frequency(1.0, Frequency::KHz))) ;
	EXPECT_TRUE(lim1.check(Frequency(2.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(0.0, Frequency::KHz))) ;
	EXPECT_FALSE(lim1.check(Frequency(1.0, Frequency::Hz))) ;
	EXPECT_TRUE(lim1.check(Frequency(3.0, Frequency::KHz))) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(Limits, Power)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	Limits<Power> lim1 ;
	lim1.setUnits("dB") ;

	// range
	EXPECT_TRUE(lim1.set("1.1..2.1/3.1")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1.1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1.0)) ;
	EXPECT_FALSE(lim1.check(3.0)) ;

	EXPECT_TRUE(lim1.set("1.0..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("-1.0..2")) ;
	std::cerr << "range " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(-2)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MAX
	EXPECT_TRUE(lim1.set("..2.0/3")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("..2.0")) ;
	std::cerr << "max " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_TRUE(lim1.check(0)) ;
	EXPECT_TRUE(lim1.check(-1)) ;
	EXPECT_FALSE(lim1.check(3)) ;

	// MIN
	EXPECT_TRUE(lim1.set("1.0../3")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;

	EXPECT_TRUE(lim1.set("1.0..")) ;
	std::cerr << "min " << lim1 << std::endl ;
	EXPECT_TRUE(lim1.check(1)) ;
	EXPECT_TRUE(lim1.check(2)) ;
	EXPECT_FALSE(lim1.check(0)) ;
	EXPECT_FALSE(lim1.check(-1)) ;
	EXPECT_TRUE(lim1.check(3)) ;


}
