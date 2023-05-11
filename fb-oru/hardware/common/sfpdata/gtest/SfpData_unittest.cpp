/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SfpData_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <memory>

#include "ISfpData.h"
#include "SfpData.h"
#include "TestBus.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(SfpData, rx1)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    // Create buses for I2C access for A0 and A1 chips
    std::shared_ptr<II2cBus> i2cA0 = std::make_shared<TestI2cBus>("A0-SFP-0", "SFP I2C bus");
    std::shared_ptr<II2cBus> i2cA1 = std::make_shared<TestI2cBus>("A2-SFP-0", "SFP I2C bus");

	SfpData sfp0(0, i2cA0, i2cA1) ;
	EXPECT_TRUE(sfp0.sfpIsPresent()) ;
//	EXPECT_EQ(3100u, sfp0.sfpSupportedRateMBps()) ;
//	EXPECT_EQ(9900u, sfp0.sfpSupportedRateMBps()) ;
	EXPECT_EQ(10200u, sfp0.sfpSupportedRateMBps()) ;
	std::cout << "Vendor: '" << sfp0.sfpVendorName() << "'" << std::endl ;
	std::cout << "Part: '" << sfp0.sfpVendorPart() << "'" << std::endl ;
	std::cout << "Rev: '" << sfp0.sfpVendorRev() << "'" << std::endl ;

}
