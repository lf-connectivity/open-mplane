/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRadioTestCase.h
 * \brief     Define the unit tests for the CommonRadio class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 * CommonRadio implementation of the IRadio interface. It implements missing
 * static methods to create and instance of the radio and its Tx and Rx ports.
 *
 */

#ifndef COM_RADIO_HW__RADIO_TESTCASE_H_
#define COM_RADIO_HW__RADIO_TESTCASE_H_

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the Frequency class.
 */
class CommonRadioTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonRadioTestCase );
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

};


} /* namespace Mplane */

#endif /* COM_RADIO_HW__RADIO_TESTCASE_H_ */
