#ifndef _COMMON_MODULE_TESTCASE_H_
#define _COMMON_MODULE_TESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ModuleTestCase.h
 * \brief     Define the unit tests for the Module class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 *            Module implementation of the Module class.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "Module.h"

namespace Mplane
{


class TestFilterModule: public Module
{
public:
    TestFilterModule();
    ~TestFilterModule();

    /*! \brief  Display the module data and information related to its general
     * status.
     *
     *  Display the state of the module on the console or log file
     */
    virtual void show(void);

    virtual ReturnType::State doInit();


    bool mDoInitCalled;

};


/*! @brief Unit test harness for the CommonCam class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonCam class.
 */
class ModuleTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( ModuleTestCase );
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
     * @test Test the CommonModule object constructor options
     */
    void unittest();


};


} /* namespace Mplane */

#endif /* _COMMON_MODULE_TESTCASE_H_ */
