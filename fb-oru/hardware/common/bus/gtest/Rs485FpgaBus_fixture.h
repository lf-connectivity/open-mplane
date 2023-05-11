#ifndef _MPLANE_RS485FPGABUSFIXTURE_H_
#define _MPLANE_RS485FPGABUSFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485FpgaBus_fixture.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"
#include "FpgaRegCapture_fixture.h"
#include "OffTargetFPGA.h"

namespace Mplane
{



/*! @brief Test fixture for Rs485FpgaBus_fixture
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the Rs485FpgaBus_fixture class.
 */
class Rs485FpgaBusTestFixture : public FpgaRegCaptureTestFixture
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




#endif /* _MPLANE_RS485FPGABUSFIXTURE_H_ */
