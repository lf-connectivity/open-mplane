#ifndef _COMMONTXFREQUENCYCONSTANTTESTCASE_H_
#define _COMMONTXFREQUENCYCONSTANTTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxFrequencyConstantTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "gtest/gtest.h"

#include "CommonTxFrequencyConst.h"

namespace Mplane
{

class TestTxFreqConst: public CommonTxFrequencyConst
{
public:
    TestTxFreqConst();

    ~TestTxFreqConst();
};


/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonTxFrequencyConstTestCase : public ::testing::Test
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




#endif /* _COMMONTXFREQUENCYCONSTANTTESTCASE_H_ */
