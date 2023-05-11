/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      rti_fixture.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef RTI_FIXTURE_H_
#define RTI_FIXTURE_H_

#include "gtest/gtest.h"

#include "GtestFile.h"
#include "Model/TestingTestInterface.h"

namespace Mplane {

class RtiTests : public ::testing::Test, public GtestFile, public TestingTestInterface
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
     * Run the command with the expectation that there will be no error
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdOk(const std::string& cmd) ;

    /**
     * Run the command with the expectation that there *will* be an error
     * @param cmd command string
     * @return reply string
     */
    std::string runCmdError(const std::string& cmd) ;
};

}
#endif /* RTI_FIXTURE_H_ */
