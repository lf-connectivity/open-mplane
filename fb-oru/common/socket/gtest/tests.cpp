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

#include "gtest/gtest.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
	// stop any other socket tests from running at the same time
	FileLockSockets locker ;
	locker.lock() ;

	::testing::InitGoogleTest(&argc, argv);
	::chdir("socket") ;
	return RUN_ALL_TESTS();
}
