#ifndef _MPLANE_COMMONCARRIERSERVERTESTCASE_H_
#define _MPLANE_COMMONCARRIERSERVERTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServerTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "CommonCarrierServer.h"

namespace Mplane
{

class TestRadioCarrierServer: public CommonCarrierServer
{
public:
    TestRadioCarrierServer();

    ~TestRadioCarrierServer();

//    virtual bool setCarrier( ICarrierSetter &carrier );

    void writeErrorMsg(char* str);
};


/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonCarrierServerTestCase : public CPPUNIT_NS::TestFixture,
    public ICarrierControl,
    public ICarrierServerObserver
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonCarrierServerTestCase );
    CPPUNIT_TEST( unittest );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Frequency object constructor options
     */
    void unittest();

    virtual const unsigned getIndex() const;

    virtual bool notify( ICarrierServer const &carrierServer );

    virtual char const * const getObjName();

private:
    /*
     * Attributes
     */
    unsigned m_index;

    ICarrier* m_cbCarrier;

    unsigned m_cbCount;

};


} /* namespace Mplane */




#endif /* _MPLANE_COMMONCARRIERSERVERTESTCASE_H_ */
