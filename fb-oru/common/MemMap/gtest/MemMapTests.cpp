/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMapTests.cpp
 * \brief     Google test main
 *
 *
 * \details   Google test main for MemMap tests
 *
 */
#include "gtest/gtest.h"

int main( int argc, char* argv[] )
{
//	chdir("MemMap") ;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}




