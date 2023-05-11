/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      md5_unittest.cpp
 * \brief     Google Test of md5
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Md5Sum class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <memory>

#include "Md5Sum.h"

using namespace Mplane ;

#define TESTDIR "../../../md5/gtest/test/"

//-------------------------------------------------------------------------------------------------------------
TEST(md5, test1)
{
	Md5Sum md5 ;
	md5.setFilename(TESTDIR "test1.txt") ;
	std::string sum(md5.sum()) ;

	std::cerr << "TEST1: " << sum << std::endl ;

	EXPECT_EQ("8e7dfb9349c9d482ad1bc18d4266b010", md5.sum()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(md5, test2)
{
	Md5Sum md5(TESTDIR "test2.txt") ;
	std::string sum(md5.sum()) ;

	std::cerr << "TEST2: " << sum << std::endl ;

	EXPECT_EQ("a5e3407b7e7b93eda58231ccfe7c8137", md5.sum()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(md5, test3)
{
	Md5Sum md5(TESTDIR "noth-there.txt") ;
	std::string sum(md5.sum()) ;

	std::cerr << "TEST3: " << sum << std::endl ;

	EXPECT_TRUE(sum.empty()) ;
}
