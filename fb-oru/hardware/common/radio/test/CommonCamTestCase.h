#ifndef _COMMONCAMTESTCASE_H_
#define _COMMONCAMTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAdcTestCase.h
 * \brief     Define the unit tests for the CommonAdc class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonAdc implementation of the IAdc interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonCam class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonCam class.
 */
class CommonCamTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonCamTestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testInitialisation );
    CPPUNIT_TEST( testBaseClass );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the CommonCam object constructor options
     */
    void testCreation();

    /**
     * @test Test the CommonCam object initialisation
     */
    void testInitialisation();

    /**
     * @test Test the base class implementation, throws exceptions.
     */
    void testBaseClass();


};


} /* namespace Mplane */



#endif /* _COMMONCAMTESTCASE_H_ */
