#ifndef _COMM_TASKTESTCASE_H_
#define _COMM_TASKTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskTestCase.h
 * \brief     The CppUnit test harness for Task
 *
 *
 * \details   This file defines the CppUnit test cases that will unit test
 *            the common task Task class.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "Task.h"

namespace Mplane
{

class ATask : public Task
{
public:
    ATask();

    virtual ~ATask(){};

    int count;

    virtual void show();

    bool mRun;

protected:
        virtual int run();
};


class BTask : public Task
{
public:
    BTask();

    virtual ~BTask(){};

    int getCount();

    int count;

    virtual void show();

    bool mRun;

    bool failWatchDog;

protected:
        virtual int run();

};


class CTask : public Task
{
public:
    CTask();

    virtual ~CTask(){};

    int getCount();

    int count;

    virtual void show();

    bool mRun;

protected:
        virtual int run();
};

/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common task Task class.
 */
class TaskTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( TaskTestCase );
    CPPUNIT_TEST( testCreation );
    CPPUNIT_TEST( testRun );
    CPPUNIT_TEST( testStop );
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
    void testCreation();
    /**
     * @test Test Frequency value assignment operator (=)
     */
    void testRun();
    /**
     * @test Test the Frequency addition operators (+,+=)
     */
    void testStop();

private:
    ATask* task_a;
    BTask* task_b;
    CTask* task_c;
};


} /* namespace Mplane */

#endif /* _COMM_TASKTESTCASE_H_ */
