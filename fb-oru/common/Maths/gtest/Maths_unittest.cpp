/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Maths_unittest.cpp
 * \brief     Maths class testing
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the common Maths class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Maths.h"

using namespace Mplane;

/*
 * Unit tests
 */
TEST(MathsTest, basic)
{
    std::cout << "*** MathsTest Tests ***" <<  std::endl;
    std::cout << __func__ << " - START" <<  std::endl;

    std::map<std::string, float> cases = {
    	{ "1.0", 1.0 },
    	{ "+21.3", 21.3 },
    	{ "-12.1", -12.1 },
    	{ "1234565839839.14784784748", 1234565839839.14784784748 },
    };

    for (auto test : cases)
    {
    	float expected = test.second ;
    	float fval1 = Maths::str2float(test.first) ;
    	float fval2 = Maths::char2float(test.first.c_str()) ;
    	float fval3 = atof(test.first.c_str()) ;

    	EXPECT_FLOAT_EQ(expected, fval1) ;
    	EXPECT_FLOAT_EQ(expected, fval2) ;
    	EXPECT_FLOAT_EQ(expected, fval3) ;
    }

    std::cout << __func__ << " - END" <<  std::endl;
}

TEST(MathsTest, exponent)
{
    std::cout << "*** MathsTest Tests ***" <<  std::endl;
    std::cout << __func__ << " - START" <<  std::endl;

    std::map<std::string, float> cases = {
    	{ "1.0e3", 1.0e3 },
    	{ "-12.1e-5", -12.1e-5 },
    	{ "+1234565839839.14e+2", 1234565839839.14e+2 },
    };

    for (auto test : cases)
    {
    	float expected = test.second ;
    	float fval1 = Maths::str2float(test.first) ;
    	float fval2 = Maths::char2float(test.first.c_str()) ;
    	float fval3 = atof(test.first.c_str()) ;

    	EXPECT_FLOAT_EQ(expected, fval1) ;
    	EXPECT_FLOAT_EQ(expected, fval2) ;
    	EXPECT_FLOAT_EQ(expected, fval3) ;
    }

    std::cout << __func__ << " - END" <<  std::endl;
}

TEST(MathsTest, toIeee754)
{
    std::cout << "*** MathsTest Tests ***" <<  std::endl;
    std::cout << __func__ << " - START" <<  std::endl;

    std::map<UINT32, float> cases = {
    	{ 0x3f800000, 1 },
    	{ 0xc0000000, -2 },
    	{ 0x41c80000, 25 },
    	{ 0x7f7fffff, 3.402823466e+38 },
    	{ 0, 0 },
    };

    for (auto test : cases)
    {
    	float expected = test.second ;
    	float fval1 = Maths::ieee754toFloat(test.first) ;

    	EXPECT_FLOAT_EQ(expected, fval1) ;
    }

    std::cout << __func__ << " - END" <<  std::endl;
}

TEST(MathsTest, fromIeee754)
{
    std::cout << "*** MathsTest Tests ***" <<  std::endl;
    std::cout << __func__ << " - START" <<  std::endl;

    std::map<UINT32, float> cases = {
    	{ 0x3f800000, 1 },
    	{ 0xc0000000, -2 },
    	{ 0x41c80000, 25 },
    	{ 0x7f7fffff, 3.402823466e+38 },
    	{ 0, 0 },
    };

    for (auto test : cases)
    {
    	unsigned expected = test.first ;
    	unsigned fval1 = Maths::floatToIeee754(test.second) ;

    	EXPECT_EQ(expected, fval1) ;
    }

    std::cout << __func__ << " - END" <<  std::endl;
}

TEST(MathsTest, floatEqual)
{
    std::cout << "*** MathsTest Tests ***" <<  std::endl;
    std::cout << __func__ << " - START" <<  std::endl;

    float a(1.10) ;
    float b(1.11) ;
    EXPECT_TRUE(Maths::floatEqual(a, a)) ;
    EXPECT_TRUE(Maths::floatEqual(a, a, 0.1)) ;

    EXPECT_FALSE(Maths::floatEqual(a, b)) ;
    EXPECT_TRUE(Maths::floatEqual(a, b, 0.1)) ;

    std::cout << __func__ << " - END" <<  std::endl;
}
