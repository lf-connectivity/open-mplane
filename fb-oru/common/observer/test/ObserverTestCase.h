#ifndef _AA_COMMON_OBSERVERTESTCASE_H_
#define _AA_COMMON_OBSERVERTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ObserverTestCase.h
 * \brief     The CppUnit test harness for observer template class
 *
 *
 * \details   The CppUnit test harness for observer template class
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "Observer.hpp"

namespace Mplane
{

class TestHighTemperatureFaultInterface: public Subject< TestHighTemperatureFaultInterface >
{
public:
    virtual bool high() = 0;
    virtual bool critical() = 0;
protected:
    virtual ~TestHighTemperatureFaultInterface();
};

class TestLowTemperatureFaultInterface: public Subject< TestLowTemperatureFaultInterface >
{
public:
    virtual bool low() = 0;
    virtual bool warmup() = 0;
protected:
    virtual ~TestLowTemperatureFaultInterface();
};

class TestTemperatureFaultSubject: public TestHighTemperatureFaultInterface,
    public TestLowTemperatureFaultInterface
{
public:
    TestTemperatureFaultSubject();
    virtual ~TestTemperatureFaultSubject();
    virtual bool high();
    virtual bool critical();
    virtual bool low();
    virtual bool warmup();

    void changeHigh();
    void changeLow();

    bool mHigh;
    bool mCritical;
    bool mLow;
    bool mWarmup;
};

class TestTemperatureFaultObserver:
        public Observer<TestHighTemperatureFaultInterface>,
        public Observer<TestLowTemperatureFaultInterface>
{
public:
    TestTemperatureFaultObserver();
    virtual ~TestTemperatureFaultObserver();
    virtual void update(TestHighTemperatureFaultInterface& subject);
    virtual void update(TestLowTemperatureFaultInterface& subject);
    virtual const char* name() const
    {
        return mName;
    }

   bool mHigh;
   bool mCritical;
   bool mLow;
   bool mWarmup;

   const char* mName;
};

class TestCritTemperatureFaultObserver:
        public Observer<TestHighTemperatureFaultInterface>
{
public:
    TestCritTemperatureFaultObserver();
    virtual ~TestCritTemperatureFaultObserver();
    virtual void update(TestHighTemperatureFaultInterface& subject);
    virtual const char* name() const
    {
        return mName;
    }

   bool mHigh;
   bool mCritical;

   const char* mName;
};

class TestSubjectFactory
{
public:
    static TestTemperatureFaultSubject& getTemperatureFaultSubject();
    static TestHighTemperatureFaultInterface& getHighTemperatureFaultInterface();
    static TestLowTemperatureFaultInterface& getLowTemperatureFaultInterface();
};


/*! @brief Unit test harness for the collection of socket classes class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common socket server and client base classes.
 */
class ObserverTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( ObserverTestCase );
    CPPUNIT_TEST( unittests );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the socket server and client through test implementations
     * of the base class.
     */
    void unittests();

private:


};


} /* namespace Mplane */

#endif /* _AA_COMMON_OBSERVERTESTCASE_H_ */
