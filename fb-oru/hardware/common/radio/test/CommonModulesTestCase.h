#ifndef _COMMONMODULESTESTCASE_H_
#define _COMMONMODULESTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonModulesTestCase.h
 * \brief     Define the unit tests for the CommonModules class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            CommonModules implementation of the IModules interface.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the CommonModules class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonModules class.
 */
class CommonModulesTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonModulesTestCase );
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
     * @test Test the CommonModules object constructor options
     */
    void unittest();


};


} /* namespace Mplane */

#endif /* _COMMONMODULESTESTCASE_H_ */
