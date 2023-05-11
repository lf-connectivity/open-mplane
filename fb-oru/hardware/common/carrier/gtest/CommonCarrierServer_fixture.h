#ifndef _MPLANE_COMMONCARRIERSERVERFIXTURE_H_
#define _MPLANE_COMMONCARRIERSERVERFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServer_fixture.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include "CommonCarrierServer.h"
#include "OffTargetFPGA.h"

namespace Mplane
{

/*! @brief Test class for testing CommonCarrierServer
 *
 */
class CommonCarrierServerTest :
    public ICarrierControl,
    public ICarrierServerObserver
{
public:

    virtual const unsigned getIndex() const;

    virtual bool notify( ICarrierServer const &carrierServer );

    virtual char const * const getObjName();

    /*
     * Attributes
     */
    unsigned m_index;

    ICarrier* m_cbCarrier;

    unsigned m_cbCount;

};


/*! @brief Test fixture for CommonCarrierServer
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the CommonCarrierServer class.
 */
class CommonCarrierServerTestFixture : public ::testing::Test
{
public:

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

    // Restart the fpga emulator and set any test-specific registers
    void restartFpgaEmulator() ;

    /**
     * Test string contains the string fragment, case insensitive
     */
    void checkString(const std::string& expectedFragment, const std::string actual) ;


protected:
    // Shared resource across multiple tests
    static std::shared_ptr<CommonCarrierServerTest> mSharedServer ;
};




} /* namespace Mplane */




#endif /* _MPLANE_COMMONCARRIERSERVERTESTCASE_H_ */
