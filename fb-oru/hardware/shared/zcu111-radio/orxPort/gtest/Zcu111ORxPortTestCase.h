#ifndef _ZCU111RXPORTTESTCASE_H_
#define _ZCU111RXPORTTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111RxPortTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "Zcu111RrhSRxPort.h"
#include "IRegData.h"

namespace Mplane
{

/*! @brief Unit test harness
 *
 */
class TestZcu111ORxPortTestCase : public ::testing::Test
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





#endif /* _ZCU111RXPORTTESTCASE_H_ */
