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


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	::chdir("SoftwareSlots") ;
	return RUN_ALL_TESTS();
}


