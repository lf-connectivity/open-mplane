/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriEmu_fixture.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef CPRIEMU_FIXTURE_H_
#define CPRIEMU_FIXTURE_H_

#include "FpgaRegCapture_fixture.h"
#include "OffTargetFPGA.h"

namespace Mplane {

/*! @brief Test fixture for CpriEmu
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the CpriEmu class.
 */
class CpriEmuTestFixture : public FpgaRegCaptureTestFixture
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


}

#endif /* CPRIEMU_FIXTURE_H_ */
