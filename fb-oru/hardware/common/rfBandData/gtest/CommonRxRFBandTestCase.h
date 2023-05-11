#ifndef _COMMONRXRFBANDTESTCASE_H_
#define _COMMONRXRFBANDTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxRFBandTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "CommonRxRfBandConfig.h"

namespace Mplane
{


class TestRxRfBandConfig: public CommonRxRfBandConfig
{
public:
	TestRxRfBandConfig();

    ~TestRxRfBandConfig();
};


/*! @brief Unit test harness for the common Rx RF band implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonRxRFBandTestCase : public ::testing::Test
{

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

};


} /* namespace Mplane */





#endif /* _COMMONRXRFBANDTESTCASE_H_ */
