#ifndef _MUTEXTESTCASE_H_
#define _MUTEXTESTCASE_H_

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
#include "Mutex.h"

namespace Mplane
{


enum MutexTestState
{
    mt_idle,
    mt_increment,
    mt_reset,
    mt_exit
};

class WTask: public Task
{
public:
    WTask();

    virtual ~WTask() { };

    void setCount(int count);

    int getCount();

    int mCount;

    bool testHold;

    MutexTestState state;

    Mutex mMutex;

protected:
    virtual int run();
};

class IncTask: public Task
{
public:
    IncTask(WTask &task);

    virtual ~IncTask() { };

    int count;

    MutexTestState state;

    WTask &mTask;

protected:
    virtual int run();

};

class ResetTask: public Task
{
public:
    ResetTask(WTask &task);

    virtual ~ResetTask() { };

    MutexTestState state;

    WTask &mTask;

protected:
    virtual int run();
};

/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common task Task class.
 */
class MutexTestCase: public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( MutexTestCase );
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
    WTask* wtask;
    IncTask* inctask;
    ResetTask* resettask;
};

} /* namespace Mplane */

#endif /* _MUTEXTESTCASE_H_ */
