#ifndef _COMMONDACTESTCASE_H_
#define _COMMONDACTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDacTestCase.h
 * \brief     Define the unit tests for the CommonDac class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonDac implementation of the IDac interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonDac class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonDac class.
 */
class CommonDacTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonDacTestCase );
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
     * @test Test the CommonDac object constructor options
     */
    void testCreation();

    /**
     * @test Test the CommonDac object initialisation
     */
    void testInitialisation();


};


} /* namespace Mplane */



#endif /* _COMMONDACTESTCASE_H_ */
