/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierTests.cpp
 * \brief     Google test main
 *
 *
 * \details   Google test main for common carrier tests
 *
 */

#include "gtest/gtest.h"
#include "Task.h"
#include "SystemLed.h"
#include "DelaysMgrSingleton.hpp"

using namespace Mplane ;

int main( int argc, char* argv[] )
{
        ::testing::InitGoogleTest(&argc, argv);
        int rc = RUN_ALL_TESTS();

        // wait for LEDs to complete
        std::shared_ptr<ILedControl> led(SystemLedControl::getInstance(0)) ;
        while (!led->isInitComplete())
                Task::msSleep(100) ;

        return rc ;
}
