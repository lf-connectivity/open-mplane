#ifndef _RADIO_HARDWARE_OTFPGATESTCASE_H_
#define _RADIO_HARDWARE_OTFPGATESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetFPGATestCase.h
 * \brief     The CppUnit test harness for OffTargetFPGA
 *
 *
 * \details   This file defines the CppUnit test cases that will unit test
 *            the hardware fpga OffTargetFPGA class.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! \brief Unit test harness for the OffTargetFPGA class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the hardware fpga OffTargetFPGA class.
 */
class OffTargetFPGATestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( OffTargetFPGATestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testRegisterWriteRead );
    CPPUNIT_TEST( testFields );
    CPPUNIT_TEST( testData );
    CPPUNIT_TEST( testReset );
    CPPUNIT_TEST( testSequenceCheck );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the OffTargetFPGA object constructor options
     */
    void testCreation();

    /**
     * @test Test the OffTargetFPGA register read and write
     */
    void testRegisterWriteRead();


    /**
     * @test Test the OffTargetFPGA field access operations
     */
    void testFields();

    /**
     * @test Test data sources attached to address
     */
    void testData();

    /**
     * @test Test emulated reset
     */
    void testReset();

    /**
     * Test the sequence checking
     */
    void testSequenceCheck() ;
};


} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_OTFPGATESTCASE_H_ */
