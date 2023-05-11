#ifndef _MPLANE_ETNACARRIERSERVERFIXTURE_H_
#define _MPLANE_ETNACARRIERSERVERFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      bus_fixture.h
 * \brief     Image Management test fixture
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
class WorkingDir {
public:
	static std::string wd ;
	static void getWd() ;
	static void chdirWd() ;
};

//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture for IBus testing
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class BusTestFixture : public ::testing::Test
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
