#ifndef _NXPBAP70QTESTCASE_H_
#define _NXPBAP70QTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NxpBap70QTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "NxpBap70Q.h"
#include "IRegData.h"

namespace Mplane
{

/*! @brief Unit test harness for the attenuator implementation.
 *
 *  This class uses the google test facilities to perform unit testing
 */
class NxpBap70QTestCase : public ::testing::Test
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





#endif /* _NXPBAP70QTESTCASE_H_ */
