#ifndef _COMMONRESAMPLERCONFIGTESTCASE_H_
#define _COMMONRESAMPLERCONFIGTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonResamplerConfigTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "CommonResamplerConfig.h"

namespace Mplane
{


class TestResamplerConfig: public CommonResamplerConfig
{
public:
	TestResamplerConfig();

    ~TestResamplerConfig();
};


/*! @brief Unit test harness for the common resampler config implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonResamplerConfigTestCase : public ::testing::Test
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





#endif /* _COMMONRESAMPLERCONFIGTESTCASE_H_ */
