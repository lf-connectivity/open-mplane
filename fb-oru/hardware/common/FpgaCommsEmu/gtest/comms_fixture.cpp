/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      fixture.cpp
 * \brief     test fixture
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

#include "comms_fixture.h"

using namespace Mplane;


//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
void CommsTestFixture::SetUp()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

}


//-------------------------------------------------------------------------------------------------------------------
void CommsTestFixture::TearDown()
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << test_info->name() << " - END" <<  std::endl;
}
