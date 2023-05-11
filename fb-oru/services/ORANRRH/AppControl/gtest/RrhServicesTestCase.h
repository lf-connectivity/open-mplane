#ifndef _ETNAFTUSERVICESTESTCASE_H_
#define _ETNAFTUSERVICESTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhServicesTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

namespace Mplane
{

class RrhServicesTestCases: public ::testing::Test
{

protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void unittest();
};

}

#endif /* _ETNAFTUSERVICESTESTCASE_H_ */
