/*
 * RxServiceTestCase.h
 *
 *  Created on: 27 Mar 2013
 *      Author: gdurban
 */

#ifndef RADIOSVC_POWER_CONTROL_TESTCASE_H_
#define RADIOSVC_POWER_CONTROL_TESTCASE_H_

/*
 *      File:           TestFrequency.h
 *
 *      Description:    This file defines the CppUnit test harness for RsdString.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the Frequency class.
 */
class RxServiceTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( RxServiceTestCase );
    CPPUNIT_TEST( testCreation );
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
    void testCreation();

};


} /* namespace Mplane */

#endif /* RADIOSVC_POWER_CONTROL_TESTCASE_H_ */
