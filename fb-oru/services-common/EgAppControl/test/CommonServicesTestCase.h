#ifndef _RS_COMMONSERVICESTESTCASE_H_
#define _RS_COMMONSERVICESTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServicesTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
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
class CommonServicesTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonServicesTestCase );
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




#endif /* _RS_COMMONSERVICESTESTCASE_H_ */
