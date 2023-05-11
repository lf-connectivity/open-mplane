#ifndef _MPLANE_FIXTURE_H_
#define _MPLANE_FIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      fixture.h
 * \brief     test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>
#include <string>
#include <memory>

#include "gtest/gtest.h"

namespace Mplane
{

//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class TestFixture : public ::testing::Test
{
public:
    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

};



} /* namespace Mplane */

#endif
