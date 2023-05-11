/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EmbeddedMgr_fixture.h
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

/*! @brief Test fixture for EmbeddedMgr
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the EmbeddedMgr class.
 */
class EmbeddedMgrTestFixture : public ::testing::Test
{
public:
    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();


protected:

    // Set up the test case (create shared resources)
    static void SetUpTestCase() ;

    // Shut down test case
    static void TearDownTestCase() ;
};


}

#endif /* RXAGC_FIXTURE_H_ */
