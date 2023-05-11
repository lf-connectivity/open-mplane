/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      gentool_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"

#include "GtestFile.h"

#include "rti_fixture.h"

using namespace Mplane ;


void RtiTests::SetUp()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

}

void RtiTests::TearDown()
{

}

std::string RtiTests::runCmdOk(const std::string& cmd)
{
	std::string result = parse(cmd) ;
	std::cout << "CMD: " << cmd << std::endl << "REPLY: '" << result << "'" << std::endl ;
	EXPECT_TRUE( result.find("Error") == std::string::npos ) << "Unexpected command error" ;
	EXPECT_TRUE( result.find("error") == std::string::npos ) << "Unexpected command error" ;
	EXPECT_TRUE( result.find("Status=ERROR") == std::string::npos ) << "Unexpected command error" ;
	EXPECT_TRUE( result.find("Status=OK") != std::string::npos ) << "Unexpected command error" ;

	return result ;
}

std::string RtiTests::runCmdError(const std::string& cmd)
{
	std::string result = parse(cmd) ;
	std::cout << "CMD: " << cmd << std::endl << "REPLY: " << result << std::endl ;
//	EXPECT_TRUE( result.find("Error") != std::string::npos ) << "Expected command error but found none" ;
	EXPECT_TRUE( result.find("Status=OK") == std::string::npos ) << "Expected command error but found none" ;
	EXPECT_TRUE( result.find("Status=ERROR") != std::string::npos ) << "Expected command error but found none" ;

	return result ;
}


//===================================================================================================================
