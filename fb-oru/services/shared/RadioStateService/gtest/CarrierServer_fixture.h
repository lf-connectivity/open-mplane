#ifndef _MPLANE_ETNACARRIERSERVERFIXTURE_H_
#define _MPLANE_ETNACARRIERSERVERFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierServer_fixture.h
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

/*! @brief Test class for testing CarrierServer
 *
 */
class CarrierServerTest :
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


/*! @brief Test fixture for CarrierServer
 *
 *  This class uses the Google test facilities to perform unit testing
 *  of the CarrierServer class.
 */
class CarrierServerTestFixture
{
public:
	//using super = FpgaRegCaptureTestFixture ;

    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

    // Check the CarrierHardware->show() output
    bool carrierHwCheck(unsigned index, const std::string& msg, const std::string& findStr) ;

protected:

    // Set up the test case (create shared resources)
    static void SetUpTestCase() ;

    // Shut down test case
    static void TearDownTestCase() ;


protected:
    // Shared resource across multiple tests
    static std::shared_ptr<CarrierServerTest> mSharedServer ;
};




} /* namespace Mplane */




#endif /* _MPLANE_COMMONCARRIERSERVERTESTCASE_H_ */
