#ifndef _COMMONSYNTHTESTCASE_H_
#define _COMMONSYNTHTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSynthTestCase.h
 * \brief     Define the unit tests for the CommonSynth class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonSynth implementation of the ISynth interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonSynth class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonSynth class.
 */
class CommonSynthTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonSynthTestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testInitialisation );
    CPPUNIT_TEST( testSynthGetAndSet );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the CommonSynth object constructor options
     */
    void testCreation();

    /**
     * @test Test the CommonSynth object initialisation
     */
    void testInitialisation();

    /**
     * @test Test the CommonSynth operations
     */
    void testSynthGetAndSet();

};


} /* namespace Mplane */



#endif /* _COMMONSYNTHTESTCASE_H_ */
