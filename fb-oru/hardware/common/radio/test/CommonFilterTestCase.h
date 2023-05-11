#ifndef _COMMONFILTERTESTCASE_H_
#define _COMMONFILTERTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFilterTestCase.h
 * \brief     Define the unit tests for the CommonFilter class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonFilter implementation of the IFilter interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonFilter class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonFilter class.
 */
class CommonFilterTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonFilterTestCase );
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
     * @test Test the CommonFilter object constructor options
     */
    void testCreation();

    /**
     * @test Test the CommonFilter object initialisation
     */
    void testInitialisation();

};


} /* namespace Mplane */

#endif /* _COMMONFILTERTESTCASE_H_ */
