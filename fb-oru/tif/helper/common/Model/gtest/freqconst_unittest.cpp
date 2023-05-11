/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      freqconst_unittest.cpp
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

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "stringfunc.hpp"
#include "model_fixture.h"

using namespace Mplane ;

class FreqConstTests : public ModelTests
{
};

//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(FreqConstTests, Exists)
{
    // Test all commands are at least present
    std::string result ;

    result = runCmdNoCheck("/freqconst/getRx") ;
    result = runCmdNoCheck("/freqconst/getTx") ;

    result = runCmdNoCheck("/freqconst/setRx") ;
    result = runCmdNoCheck("/freqconst/setTx") ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(FreqConstTests, Basic)
{
    // @TODO
}
