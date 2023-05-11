#ifndef _COMMONRXFREQUENCYCONSTANTTESTCASE_H_
#define _COMMONRXFREQUENCYCONSTANTTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxFrequencyConstantTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "CommonRxFrequencyConst.h"

namespace Mplane
{


class TestRxFreqConst: public CommonRxFrequencyConst
{
public:
    TestRxFreqConst();

    ~TestRxFreqConst();
};


/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonRxFrequencyConstTestCase : public ::testing::Test
{

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Frequency object constructor options
     */
    void unittest();

};


} /* namespace Mplane */





#endif /* _COMMONRXFREQUENCYCONSTANTTESTCASE_H_ */
