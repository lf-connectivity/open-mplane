#ifndef RADIOSVC_FAULTSERVICE_TESTCASE_H_
#define RADIOSVC_FAULTSERVICE_TESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultServiceTestCase.h
 * \brief     The CppUnit test harness for FaultService
 *
 *
 * \details   This file defines the CppUnit test cases that will unit test
 *            the FaultService classes.
 *
 */

// Includes go here, before the namespace

#include <cppunit/extensions/HelperMacros.h>

#include "Loggable.h"

namespace Mplane
{


/*! @brief Unit test harness for the FaultService class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the FaultService class.
 */
class FaultServiceTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( FaultServiceTestCase );
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
     * @test Test the FaultService object constructor options
     */
    void testCreation();

};


} /* namespace Mplane */

#endif /* RADIOSVC_FAULTSERVICE_TESTCASE_H_ */
