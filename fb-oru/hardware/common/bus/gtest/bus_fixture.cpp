/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      bus_fixture.cpp
 * \brief     Image Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <string>
#include <iostream>
#include <algorithm>

#include "IBootEnv.h"
#include "Path.h"
#include "bus_fixture.h"

using namespace Mplane;


//===================================================================================================================
// DATA
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------

//===================================================================================================================
// WorkingDir METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
std::string WorkingDir::wd(".") ;

void WorkingDir::getWd()
{
	char buff[PATH_MAX] ;
	WorkingDir::wd = std::string(getcwd(buff, sizeof(buff))) ;

	std::cerr << "WorkingDir::getWd() " << WorkingDir::wd << std::endl ;
}

void WorkingDir::chdirWd()
{
	std::cerr << "WorkingDir::chdirWd() " << WorkingDir::wd << std::endl ;
	chdir(WorkingDir::wd.c_str()) ;
}


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void BusTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

}


//-------------------------------------------------------------------------------------------------------------------
void BusTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;

}
