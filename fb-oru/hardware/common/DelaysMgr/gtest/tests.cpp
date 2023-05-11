/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tests.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <unistd.h>
#include "gtest/gtest.h"

#include "IDelaysMgr.h"
#include "DelaysMgrSingleton.hpp"

using namespace Mplane ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

int main( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	::chdir("DelaysMgr") ;
	return RUN_ALL_TESTS();
}
