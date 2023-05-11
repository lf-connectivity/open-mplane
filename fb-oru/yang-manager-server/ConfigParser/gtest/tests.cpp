/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tests.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "FileLockSockets.h"
#include "ILoggable.h"

using namespace Mplane ;


int main( int argc, char* argv[] )
{
    // stop any other socket tests from running at the same time
    FileLockSockets locker ;
    locker.lock() ;

    ::testing::InitGoogleTest(&argc, argv);
    ::chdir("ConfigParser") ;
    return RUN_ALL_TESTS();

}
