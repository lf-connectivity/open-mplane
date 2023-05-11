/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootEnvDevice_unittest.cpp
 * \brief     Google Test of BootEnvDevice
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the BootEnvDevice class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "BootEnvDevice.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(BootEnvDevice, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<BootEnvDevice> bootEnvDev1( std::make_shared<BootEnvDevice>(1, "/dev/mtd5") ) ;
	std::shared_ptr<BootEnvDevice> bootEnvDev2( std::make_shared<BootEnvDevice>(2, "/dev/mtd4") ) ;

}
