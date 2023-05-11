#ifndef _RECURSIVE_MUTEXTESTCASE_H_
#define _RECURSIVE_MUTEXTESTCASE_H_

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
#include "RecursiveMutex.h"

namespace Mplane
{


enum RecursiveMutexTestState
{
    mt_idle,
    mt_increment,
    mt_reset,
    mt_exit
};

class RecWTask: public Task
{
public:
    RecWTask();

    virtual ~RecWTask() { };

    void setCount(int count);

    int getCount();

    int mCount;

    bool testHold;

    RecursiveMutexTestState state;

    RecursiveMutex mMutex;

protected:
    virtual int run();
};

class RecIncTask: public Task
{
public:
    RecIncTask(RecWTask &task);

    virtual ~RecIncTask() { };

    int count;

    RecursiveMutexTestState state;

    RecWTask &mTask;

protected:
    virtual int run();

};

class RecResetTask: public Task
{
public:
    RecResetTask(RecWTask &task);

    virtual ~RecResetTask() { };

    RecursiveMutexTestState state;

    RecWTask &mTask;

protected:
    virtual int run();
};

/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common task Task class.
 */
class RecursiveMutexTestCase: public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( RecursiveMutexTestCase );
    CPPUNIT_TEST(unittest);CPPUNIT_TEST_SUITE_END();

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
    RecWTask* wtask;
    RecIncTask* inctask;
    RecResetTask* resettask;
};

} /* namespace Mplane */

#endif /* _RECURSIVE_MUTEXTESTCASE_H_ */
