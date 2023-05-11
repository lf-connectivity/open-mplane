/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageTypes_unittest.cpp
 * \brief     Google Test of ImageTypes
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ImageTypes class.
 *
 */

#include <gtest/gtest.h>

#include "IImageTypes.h"

using namespace Mplane;

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST(ImageTypes, ToStr)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	EXPECT_EQ(std::string("PKG"), IImageTypes::typeToStr(IImageTypes::IMAGE_PACKAGE)) ;
	EXPECT_EQ(std::string("APP"), IImageTypes::typeToStr(IImageTypes::IMAGE_APPLICATION)) ;
	EXPECT_EQ(std::string("LIB"), IImageTypes::typeToStr(IImageTypes::IMAGE_LIBRARY)) ;
	EXPECT_EQ(std::string("OS"), IImageTypes::typeToStr(IImageTypes::IMAGE_ROS)) ;
	EXPECT_EQ(std::string("FPGA"), IImageTypes::typeToStr(IImageTypes::IMAGE_FPGA)) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(ImageTypes, ToType)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	IImageTypes::Type type ;

#define CHECK_TYPE(_str, _type) \
	EXPECT_TRUE(IImageTypes::strToType(_str, type)) ; \
	EXPECT_EQ(IImageTypes::_type, type)

#define CHECK_NOT_TYPE(_str) \
	EXPECT_FALSE(IImageTypes::strToType(_str, type))

	CHECK_TYPE("APP", IMAGE_APPLICATION);
	CHECK_TYPE("app", IMAGE_APPLICATION);
	CHECK_TYPE("application", IMAGE_APPLICATION);

	CHECK_TYPE("LIB", IMAGE_LIBRARY);
	CHECK_TYPE("lib", IMAGE_LIBRARY);
	CHECK_TYPE("library", IMAGE_LIBRARY);

	CHECK_TYPE("OS", IMAGE_ROS);
	CHECK_TYPE("os", IMAGE_ROS);
	CHECK_TYPE("ros", IMAGE_ROS);

	CHECK_TYPE("FPGA", IMAGE_FPGA);
	CHECK_TYPE("fpga", IMAGE_FPGA);
	CHECK_TYPE("myfpga", IMAGE_FPGA);

	CHECK_TYPE("PKG", IMAGE_PACKAGE);
	CHECK_TYPE("pkg", IMAGE_PACKAGE);
	CHECK_TYPE("apkg", IMAGE_PACKAGE);


	CHECK_NOT_TYPE("ap");
	CHECK_NOT_TYPE("lb");
	CHECK_NOT_TYPE("o");
	CHECK_NOT_TYPE("fpa");
	CHECK_NOT_TYPE("package");

}
