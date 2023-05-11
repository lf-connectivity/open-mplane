#ifndef _COMMONTXRFBANDTESTCASE_H_
#define _COMMONTXRFBANDTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxRFBandTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "CommonTxRfBandConfig.h"

namespace Mplane
{


class TestTxRfBandConfig: public CommonTxRfBandConfig
{
public:
	TestTxRfBandConfig();

    ~TestTxRfBandConfig();
};


/*! @brief Unit test harness for the common Tx RF band implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonTxRFBandTestCase : public ::testing::Test
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





#endif /* _COMMONTXRFBANDTESTCASE_H_ */
