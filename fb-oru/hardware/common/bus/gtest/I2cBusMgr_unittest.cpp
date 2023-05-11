/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cBusMgr_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include "ByteTransfer.hpp"
#include "II2cBusMgr.h"

#include "bus_fixture.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
class I2cBusMgr : public BusTestFixture
{
public:
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(I2cBusMgr, construct)
{
	{
    std::shared_ptr<II2cBus> i2c1(II2cBusMgr::singleton()->deviceBus("/1/mux:0:5", 0x2F)) ;
    EXPECT_NE(i2c1.get(), nullptr) ;
	}

	{
    std::shared_ptr<II2cBus> i2c1(II2cBusMgr::singleton()->deviceBus("/1/mux:0:5", 0x2F)) ;
    EXPECT_NE(i2c1.get(), nullptr) ;
	}

}
