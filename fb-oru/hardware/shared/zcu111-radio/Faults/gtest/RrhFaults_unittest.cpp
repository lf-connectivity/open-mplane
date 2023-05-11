/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhFaults_unittest.cpp
 * \brief     Google Test for D1T Fault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the RrhFault class.
 *
 */

#include "RrhFaults.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>


using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(RrhFaults, Test)
{
    std::shared_ptr<RrhFaults>faults = RrhFaults::getInstance();
}
