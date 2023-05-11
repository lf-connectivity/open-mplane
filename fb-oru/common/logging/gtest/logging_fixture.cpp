/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      logging_fixture.cpp
 * \brief     Logging test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>

#include <string>
#include <iostream>
#include <algorithm>

#include "LoggerSyslog.h"
#include "logging_fixture.h"

using namespace Mplane;


//===================================================================================================================
// DATA
//===================================================================================================================
//LogList TestLoggable::mLogList ;

bool Mplane::gFactorySyslog(false) ;

//-------------------------------------------------------------------------------------------------------------------
std::string TestLogger::mLog ;

//===================================================================================================================
// STATIC METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILogger> ILogger::factory(ILoggable* loggableParent, const std::string& instanceName, const std::string& groupName)
{
	if (gFactorySyslog)
		return std::shared_ptr<ILogger>(new LoggerSyslog(loggableParent, instanceName, groupName)) ;

	return std::shared_ptr<ILogger>(new TestLogger(instanceName, groupName)) ;
}



//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void LoggingTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

}


//-------------------------------------------------------------------------------------------------------------------
void LoggingTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;
}
