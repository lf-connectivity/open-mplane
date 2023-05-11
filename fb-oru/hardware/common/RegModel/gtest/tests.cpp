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
#include <unistd.h>
#include "gtest/gtest.h"
#include "DelaysMgrSingleton.hpp"
#include "ILoggable.h"

int main( int argc, char* argv[] )
{
	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "QMC") ;
	::chdir("RegModel") ;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}




