/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppSettings_unittest.cpp
 * \brief     Google Test of AppSettings
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AppSettings class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "IAppSettingsFactory.h"
#include "IAppSettings.h"

#include "AppSettings.h"
#include "TestAppSettings.h"

using namespace Mplane;

using namespace std;

////-------------------------------------------------------------------------------------------------------------
//TEST(AppSettings, Basic)
//{
//	const ::testing::TestInfo* const test_info =
//	  ::testing::UnitTest::GetInstance()->current_test_info();
//
//	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
//	std::cout << test_info->name() << " - START" <<  std::endl;
//
//	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
//
//	// Local build will use defaults
//	EXPECT_EQ(IAppSettings::DUPLEX_TDD, appSettings->getDuplex() ) ;
//	EXPECT_EQ(IAppSettings::APP_RRH, appSettings->getApp() ) ;
//	EXPECT_EQ(IAppSettings::IF_CPRI, appSettings->getFibreInterface() ) ;
//	EXPECT_EQ(IAppSettings::BOARD_HOST, appSettings->getBoard() ) ;
//	EXPECT_EQ(IAppSettings::CUSTOMER_GENERIC, appSettings->getCustomer() ) ;
//	EXPECT_EQ("0.0", appSettings->getBuildVersion() ) ;
////	EXPECT_EQ(1u, appSettings->getBuildNumber() ) ;	// Will use Jenkins build number
//}


//-------------------------------------------------------------------------------------------------------------
TEST(AppSettings, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IAppSettings> realAppSettings(new AppSettings) ;

	// Run the methods - should be no faults
	realAppSettings->getDuplex() ;
	realAppSettings->getApp() ;
	realAppSettings->getFibreInterface() ;
	realAppSettings->getBoard() ;
	realAppSettings->getCustomer() ;

	realAppSettings->getDuplexString() ;
	realAppSettings->getAppString() ;
	realAppSettings->getFibreInterfaceString() ;
	realAppSettings->getBoardString() ;
	realAppSettings->getCustomerString() ;

	realAppSettings->getBuildVersion() ;
	realAppSettings->getBuildNumber() ;

	realAppSettings->getFpgaPart() ;
	realAppSettings->getFpgaBuild() ;


	std::shared_ptr<IAppSettings> appSettings(new TestAppSettings) ;

//	// Local build will use defaults
//	EXPECT_EQ(IAppSettings::DUPLEX_TDD, appSettings->getDuplex() ) ;
//	EXPECT_EQ(IAppSettings::APP_RRH, appSettings->getApp() ) ;
//	EXPECT_EQ(IAppSettings::IF_CPRI, appSettings->getFibreInterface() ) ;
//	EXPECT_EQ(IAppSettings::BOARD_HOST, appSettings->getBoard() ) ;
//	EXPECT_EQ(IAppSettings::CUSTOMER_GENERIC, appSettings->getCustomer() ) ;
//	EXPECT_EQ("0.0", appSettings->getBuildVersion() ) ;
//	EXPECT_EQ(1u, appSettings->getBuildNumber() ) ;

	// Should be able to change settings
	std::shared_ptr<TestAppSettings> testAppSettings(std::dynamic_pointer_cast<TestAppSettings>(appSettings)) ;

	testAppSettings->setApp(IAppSettings::APP_ORANRRH) ;
	testAppSettings->setBoard(IAppSettings::BOARD_ZCU111) ;
	testAppSettings->setBuildNumber(1234) ;
	testAppSettings->setBuildVersion("2.3") ;
	testAppSettings->setCustomer(IAppSettings::CUSTOMER_FBC) ;
	testAppSettings->setDuplex(IAppSettings::DUPLEX_FDD) ;
	testAppSettings->setFibreInterface(IAppSettings::IF_ORAN) ;

	EXPECT_EQ(IAppSettings::DUPLEX_FDD, appSettings->getDuplex() ) ;
	EXPECT_EQ(IAppSettings::APP_ORANRRH, appSettings->getApp() ) ;
	EXPECT_EQ(IAppSettings::IF_ORAN, appSettings->getFibreInterface() ) ;
	EXPECT_EQ(IAppSettings::BOARD_ZCU111, appSettings->getBoard() ) ;
	EXPECT_EQ(IAppSettings::CUSTOMER_FBC, appSettings->getCustomer() ) ;
	EXPECT_EQ("2.3", appSettings->getBuildVersion() ) ;
	EXPECT_EQ(1234u, appSettings->getBuildNumber() ) ;
}
