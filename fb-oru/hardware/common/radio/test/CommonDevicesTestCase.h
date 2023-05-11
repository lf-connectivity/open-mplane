#ifndef _COMMONDEVICESTESTCASE_H_
#define _COMMONDEVICESTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDevicesTestCase.h
 * \brief     Define the unit tests for the CommonDevices class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonDevices implementation of the IDevices interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonDevices class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonDevices class.
 */
class CommonDevicesTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonDevicesTestCase );
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
     * @test Test the CommonDevices object constructor options
     */
    void unittest();


};


} /* namespace Mplane */



#endif /* _COMMONDEVICESTESTCASE_H_ */
