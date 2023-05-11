/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgc_fixture.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef RXAGC_FIXTURE_H_
#define RXAGC_FIXTURE_H_

#include "gtest/gtest.h"

namespace Mplane {

/*! @brief Test fixture for RxAgc
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the RxAgc class.
 */
class RxAgcTestFixture: public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp() {};

    /*! @brief Tear down the test
     */
    virtual void TearDown() {};
};


}

#endif /* RXAGC_FIXTURE_H_ */
