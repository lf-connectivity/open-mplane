/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriTests.cpp
 * \brief     Implementation of the main CppUnit test harness for CommonCpri classes
 *
 *
 * \details   This file contains the main CppUnit controlling function for the
 *            CommonCpri sources.
 *
 */

#include <unistd.h>
#include "gtest/gtest.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

int main( int argc, char* argv[] )
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
