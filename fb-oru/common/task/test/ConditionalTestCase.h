#ifndef _CONDITIONAL_TESTCASE_H_
#define _CONDITIONAL_TESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MutexTestCase.h
 * \brief     CPPUNIT test cases for Mutex and Lock class.
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "Task.h"
#include "Conditional.h"

namespace Mplane
{


enum ConditionalTestState
{
    ct_idle,
    ct_writecount,
    ct_exit
};

class CondWTask: public Task
{
public:
    CondWTask();

    virtual ~CondWTask() { };

    int waitCount();

    void setCount(int count);

    int getCount();

    int mCount;

    int nowCount;

    bool testHold;

    ConditionalTestState state;

    Conditional mConditional;

protected:
    virtual int run();
};

class CondTestTask: public Task
{
public:
    CondTestTask(CondWTask &task);

    virtual ~CondTestTask() { };

    int count;

    ConditionalTestState state;

    CondWTask &mTask;

protected:
    virtual int run();

};



/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common task Task class.
 */
class ConditionalTestCase: public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( ConditionalTestCase );
    CPPUNIT_TEST(unittest);
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp(){};

    /*! @brief Tear down the test harness
     */
    void tearDown(){};

    /**
     * @test Test the Frequency object constructor options
     */
    void unittest();

private:
    CondWTask* wtask;
    CondTestTask* atask;
};

} /* namespace Mplane */

#endif /* _CONDITIONAL_TESTCASE_H_ */
