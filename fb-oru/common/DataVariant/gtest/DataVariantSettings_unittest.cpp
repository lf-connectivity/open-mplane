/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantSettings_unittest.cpp
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
#include "DataVariantSettings.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantSettings, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;

	// have to ensure settings are cleared out otherwise the following tests won't work
	settings->clearSettings() ;

	EXPECT_FALSE(settings->isSetting("unexpected")) ;
	EXPECT_FALSE(settings->isSetting("NUM_TX_PATHS")) ;
	EXPECT_FALSE(settings->isSetting("another")) ;

	std::string error ;
	EXPECT_EQ("this is a test", settings->expandString("this is a test", error)) ;
	EXPECT_TRUE(error.empty()) ;
	EXPECT_EQ("this is ${unexpected} test", settings->expandString("this is ${unexpected} test", error)) ;
	EXPECT_TRUE(error.empty()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantSettings, Register)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;

	settings->registerSettings(std::map<std::string, std::string>{
		{ "NUM_TX_PATHS",	"" },
		{ "another",		"" },
	}) ;

	EXPECT_FALSE(settings->isSetting("unexpected")) ;
	EXPECT_TRUE(settings->isSetting("NUM_TX_PATHS")) ;
	EXPECT_TRUE(settings->isSetting("another")) ;

	std::string error ;
	EXPECT_EQ("this is a test", settings->expandString("this is a test", error)) ;
	EXPECT_TRUE(error.empty()) ;
	EXPECT_EQ("this is  test", settings->expandString("this is ${another} test", error)) ;
	EXPECT_TRUE(error.empty()) ;
	EXPECT_EQ("Number of TX:", settings->expandString("Number of TX:${NUM_TX_PATHS}", error)) ;
	EXPECT_TRUE(error.empty()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantSettings, Set)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;

	settings->registerSettings(std::map<std::string, std::string>{
		{ "NUM_TX_PATHS",	"" },
		{ "another",		"" },
	}) ;

	EXPECT_FALSE(settings->setSetting("invalid", "fred")) ;
	EXPECT_TRUE(settings->setSetting("another", "yet another string")) ;
	EXPECT_TRUE(settings->setSetting("NUM_TX_PATHS", "4")) ;

	std::string error ;
	EXPECT_EQ("this is a test", settings->expandString("this is a test", error)) ;
	EXPECT_TRUE(error.empty()) ;
	EXPECT_EQ("this is yet another string test", settings->expandString("this is ${another} test", error)) ;
	EXPECT_TRUE(error.empty()) ;
	EXPECT_EQ("Number of TX:4", settings->expandString("Number of TX:${NUM_TX_PATHS}", error)) ;
	EXPECT_TRUE(error.empty()) ;
}
