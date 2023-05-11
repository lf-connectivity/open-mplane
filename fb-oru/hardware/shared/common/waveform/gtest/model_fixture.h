/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      model_fixture.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef MODEL_FIXTURE_H_
#define MODEL_FIXTURE_H_

#include "gtest/gtest.h"

namespace Mplane {

class ModelFixture : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp() ;

    /*! @brief Tear down the test
     */
    virtual void TearDown() ;
};

}
#endif /* RTI_FIXTURE_H_ */
