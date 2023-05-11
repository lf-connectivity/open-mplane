 /*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioTests.cpp
 * \brief     The Google Unit test harness for commonhardware/radio
 *
 *  Created on: 08 May 2014
 *      Author: cmeech
 * \details   This file calls the Google Unit test cases that will unit test
 *            the commonhardware/radio test cases.
 *
 */
#include <unistd.h>
#include "gtest/gtest.h"


int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}




