#ifndef _MPLANE_QMCCALFIXTURE_H_
#define _MPLANE_QMCCALFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal_fixture.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "FpgaRegCapture_fixture.h"

#include "CommonCarrierServer.h"
#include "OffTargetFPGA.h"

namespace Mplane
{

/*! @brief Test fixture for QmcCal
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the QmcCal class.
 */
class QmcCalTestFixture : public FpgaRegCaptureTestFixture
{
public:
	using super = FpgaRegCaptureTestFixture ;

    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

protected:

    // Set up the test case (create shared resources)
    static void SetUpTestCase() ;

    // Shut down test case
    static void TearDownTestCase() ;

};




} /* namespace Mplane */




#endif /* _MPLANE_QMCCALFIXTURE_H_ */
