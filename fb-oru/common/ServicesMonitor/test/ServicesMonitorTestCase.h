
#ifndef COMMON_SERVICESMONITOR_TESTCASE_H_
#define COMMON_SERVICESMONITOR_TESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ServicesMonitorTestCase.h
 * \brief     Unit test definition for ServicesMonitor task
 *
 *
 * \details   Unit test definition for ServicesMonitor task
 *
 */


#include <cppunit/extensions/HelperMacros.h>

#include "Service.h"

namespace Mplane
{
class ServicesMonitor;

class ServiceTest : public Service
{
public:
    ServiceTest(const char* sname, const char* su);

    virtual ~ServiceTest();

    int count;

    virtual void show();

    bool mEnterTightLoop;
    bool mShutdown;

protected:
    virtual int service();

};


/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the Frequency class.
 */
class ServicesMonitorTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( ServicesMonitorTestCase );
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

    ServiceTest * svc_a;
    ServiceTest * svc_b;
    ServiceTest * svc_c;
    ServiceTest * svc_d;
    ServiceTest * svc_e;


};


} /* namespace Mplane */

#endif /* RADIOSVC_POWER_CONTROL_TESTCASE_H_ */
