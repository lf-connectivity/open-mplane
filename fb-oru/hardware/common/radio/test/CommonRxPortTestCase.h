#ifndef _COMMONRXPORTTESTCASE_H_
#define _COMMONRXPORTTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxPortTestCase.h
 * \brief     Define the unit tests for the CommonRxPort class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 * CommonRxPort implementation of the IRxPort interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonRxPortTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( Mplane::CommonRxPortTestCase );
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





#endif /* _COMMONRXPORTTESTCASE_H_ */
