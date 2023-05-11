#ifndef _COMMONATTENTESTCASE_H_
#define _COMMONATTENTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAttenuatorTestCase.h
 * \brief     Define the unit tests for the CommonAttenuator class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonAttenuator implementation of the IAttenuator interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonAttenuator class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonAttenuator class.
 */
class CommonAttenuatorTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonAttenuatorTestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testInitialisation );
    CPPUNIT_TEST( testAttenSetting );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the CommonAttenuator object constructor options
     */
    void testCreation();

    /**
     * @test Test the CommonAttenuator object initialisation
     */
    void testInitialisation();

    /**
     * @test Test the CommonAttenuator attenuator setting operations
     */
    void testAttenSetting();

};


} /* namespace Mplane */



#endif /* _COMMONATTENTESTCASE_H_ */
