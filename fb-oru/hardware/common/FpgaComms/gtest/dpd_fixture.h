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

#include "IFpgaPdu.h"
#include "IFpgaMsg.h"
#include "gtest/gtest.h"

namespace Mplane
{

//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class DpdTestFixture : public ::testing::Test
{
public:
    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

    void handleMsg(std::shared_ptr<IFpgaMsg> msg);

    std::shared_ptr<IFpgaMsg> createMsg(const IFpgaPdu& pdu);

    bool doRx() ;

public:
	std::vector<std::shared_ptr<IFpgaMsg>> mRxMsgs ;

};



} /* namespace Mplane */

#endif
