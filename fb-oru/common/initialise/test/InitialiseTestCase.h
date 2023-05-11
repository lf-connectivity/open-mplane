#ifndef _COMM_INITIALISETESTCASE_H_
#define _COMM_INITIALISETESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      InitialiseTestCase.h
 * \brief     The CppUnit test harness for Initialise
 *
 *
 * \details   This file defines the CppUnit test cases that will unit test
 *            the common Initialise class.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! \brief Unit test harness for the Initialise class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common Initialise class.
 */
class InitialiseTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( InitialiseTestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testInitialisation );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Initialise object constructor options
     */
    void testCreation();

    /**
     * @test Test the Initialise object initialisation options
     */
    void testInitialisation();

};

} /* namespace Mplane */

#endif /* _COMM_INITIALISETESTCASE_H_ */
