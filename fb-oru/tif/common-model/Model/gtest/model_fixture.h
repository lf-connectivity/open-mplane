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

#include "TestInterface.h"

namespace Mplane {

class ModelTests : public ::testing::Test, public TestInterface
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp() ;

    /*! @brief Tear down the test
     */
    virtual void TearDown() ;

protected:
    /**
     * Run the command with the expectation that there will be no error text in the result string.
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdOk(const std::string& cmd) ;

    /**
     * Run the command without performing any error checks in the result
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdNoErrorCheck(const std::string& cmd) ;

    /**
     * Run the command with the expectation that there *will* be an error
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdError(const std::string& cmd) ;
};

}
#endif /* RTI_FIXTURE_H_ */
