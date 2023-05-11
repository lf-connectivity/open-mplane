/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tests.cpp
 * \brief     main method to start the DPD services tests
 *
 *
 */

#include <unistd.h>
#include "gtest/gtest.h"


int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  chdir("DpdService") ;
  return RUN_ALL_TESTS();
}
