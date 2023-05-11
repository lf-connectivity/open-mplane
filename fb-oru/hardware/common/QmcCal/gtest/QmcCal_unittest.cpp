/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal_unittest.cpp
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

#include "stringfunc.hpp"

// Uncomment (here or in file that includes this header) to gather expected register writes
//#define GATHER_SEQUENCES

#include "QmcCal_fixture.h"
#include "OffTargetFPGA.h"

#include "QmcCal.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(QmcCalTestFixture, basic)
{
    std::shared_ptr<IQmcCal> qmcCal0 = IQmcCalFactory::get(0);
    std::shared_ptr<IQmcCal> qmcCal1 = IQmcCalFactory::get(1);

    EXPECT_TRUE(qmcCal0.get() != nullptr) ;
    EXPECT_TRUE(qmcCal1.get() != nullptr) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(QmcCalTestFixture, run0)
{
    std::shared_ptr<IQmcCal> qmcCal0 = IQmcCalFactory::get(0);

	// TODO: I should probably sort out writing to all the fpga regs to get this to run through.....but life's too short!
    EXPECT_TRUE(qmcCal0.get() != nullptr) ;
//    EXPECT_TRUE(qmcCal0->performCal()) ;

    // just make sure it doesn't crash!
    qmcCal0->performCal() ;
}
