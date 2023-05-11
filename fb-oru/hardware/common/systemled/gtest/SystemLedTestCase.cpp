
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemLedTestCcase.cpp
 * \brief     Pure virtual interface that defines methods needed to access the
 *            LED indicators.
 *
 *
 * \details   Pure virtual interface that defines methods needed to access the
 *            LED indicators.
 *
 */

#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

#include "GlobalTypeDefs.h"

#include "gtest/gtest.h"

#include "SystemLed.h"

/*! \brief
 *
 *
 */

using namespace Mplane;


// implement the interface for test purposes.



/* Google Tests */
TEST(SystemLedControl, unittest)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    std::shared_ptr<ILedControl> ledControl( SystemLedControl::getInstance(0) );

    ASSERT_TRUE(ledControl->initialise() == ReturnType::RT_OK);

    ASSERT_TRUE(ledControl->getNumberOfLeds() == 1);

    std::cout << test_info->name() << " - END" <<  std::endl;

}
