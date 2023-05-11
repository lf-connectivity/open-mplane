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
#include "ILimitsSettings.h"
using namespace Mplane ;

int main( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);

	chdir("Model") ;
	char buff[256] ;
	std::cerr << "Running in: " << getcwd(buff, sizeof(buff)) << std::endl ;

	// limits
	std::shared_ptr<ILimitsSettings> limitsSettings(ILimitsSettings::getInstance()) ;
	limitsSettings->registerSettings() ;

	return RUN_ALL_TESTS();
}
