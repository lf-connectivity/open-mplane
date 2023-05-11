/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      etna_model_fixture.h
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

#include "model_fixture.h"

using namespace Mplane ;


void ModelTests::SetUp()
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

}

void ModelTests::TearDown()
{

}


std::string ModelTests::runCmdOk(const std::string& cmd)
{
	std::cout << "SEND CMD: " << cmd << std::endl ;
	std::string result = parse(cmd) ;
	std::string RESULT(toUpper(result)) ;
	std::cout << "CMD: " << cmd << std::endl << "REPLY: '" << result << "'" << std::endl ;
	EXPECT_TRUE( RESULT.find("ERROR") == std::string::npos ) << "Unexpected command error" ;
	EXPECT_TRUE( RESULT.find("STATUS=OK") != std::string::npos ) << "Unexpected command error" ;

	return result ;
}

std::string ModelTests::runCmdNoCheck(const std::string& cmd)
{
	std::cout << "SEND CMD: " << cmd << std::endl ;
	std::string result = parse(cmd) ;
	std::string RESULT(toUpper(result)) ;
	std::cout << "CMD: " << cmd << std::endl << "REPLY: '" << result << "'" << std::endl ;

	return result ;
}

std::string ModelTests::runCmdError(const std::string& cmd)
{
	std::string result = parse(cmd) ;
	std::string RESULT(toUpper(result)) ;
	std::cout << "CMD: " << cmd << std::endl << "REPLY: " << result << std::endl ;
	EXPECT_TRUE(
		(RESULT.find("STATUS=ERROR") != std::string::npos) ||
		(RESULT.find("ERROR:") != std::string::npos)
	) << "Expected command error but found none" ;

	return result ;
}


//===================================================================================================================
