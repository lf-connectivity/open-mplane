/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EuropaAppControlTests.cpp
 * \brief     main method to start the ETNA FTU radio control services
 *
 *
 * \details   main method to start the ETNA FTU radio control services
 *
 */

#include <unistd.h>
#include "gtest/gtest.h"

#include "TestAppOptions.h"

using namespace Mplane ;

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);

  TestAppOptions setupOptions ;

  chdir("AppServices") ;
  return RUN_ALL_TESTS();
}
