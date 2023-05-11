/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ObserverTestCode.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ObserverTestCase.h"

using namespace Mplane;

using namespace std;

Mplane::TestHighTemperatureFaultInterface::~TestHighTemperatureFaultInterface()
{
}

Mplane::TestTemperatureFaultSubject::TestTemperatureFaultSubject() :
        mHigh(false), mCritical(false), mLow(false), mWarmup(false)
{
}

Mplane::TestTemperatureFaultSubject::~TestTemperatureFaultSubject()
{

}

bool Mplane::TestTemperatureFaultSubject::high()
{
    return mHigh;
}

bool Mplane::TestTemperatureFaultSubject::critical()
{
    return mCritical;
}

bool Mplane::TestTemperatureFaultSubject::low()
{
    return mLow;
}

bool Mplane::TestTemperatureFaultSubject::warmup()
{
    return mWarmup;
}

Mplane::TestLowTemperatureFaultInterface::~TestLowTemperatureFaultInterface()
{
}


void Mplane::TestTemperatureFaultSubject::changeHigh()
{
    dynamic_cast<TestHighTemperatureFaultInterface *>(this)->notify();/*-?|review #268|gdurban|c3|?*/
}

void Mplane::TestTemperatureFaultSubject::changeLow()
{
    dynamic_cast<TestLowTemperatureFaultInterface *>(this)->notify();
}


Mplane::TestTemperatureFaultObserver::TestTemperatureFaultObserver() :
        mHigh(false), mCritical(false), mLow(false), mWarmup(false),
        mName ( "Test Temperature Fault Observer" )
{
}

Mplane::TestTemperatureFaultObserver::~TestTemperatureFaultObserver()
{
}

void Mplane::TestTemperatureFaultObserver::update(
        TestHighTemperatureFaultInterface& subject)
{
    mHigh = subject.high();
    mCritical = subject.critical();
}

void Mplane::TestTemperatureFaultObserver::update(
        TestLowTemperatureFaultInterface& subject)
{
    mLow = subject.low();
    mWarmup = subject.warmup();
}

Mplane::TestCritTemperatureFaultObserver::TestCritTemperatureFaultObserver() :
        mHigh(false), mCritical(false),
        mName ( "Test Critical Temperature Fault Observer" )
{
}

Mplane::TestCritTemperatureFaultObserver::~TestCritTemperatureFaultObserver()
{
}

void Mplane::TestCritTemperatureFaultObserver::update(
        TestHighTemperatureFaultInterface& subject)
{
    mHigh = subject.high();
    mCritical = subject.critical();
}


TestTemperatureFaultSubject& Mplane::TestSubjectFactory::getTemperatureFaultSubject()
{
    static TestTemperatureFaultSubject* subject =
            new TestTemperatureFaultSubject();

    return *subject;
}

TestHighTemperatureFaultInterface& Mplane::TestSubjectFactory::getHighTemperatureFaultInterface()
{
    return TestSubjectFactory::getTemperatureFaultSubject();
}

TestLowTemperatureFaultInterface& Mplane::TestSubjectFactory::getLowTemperatureFaultInterface()
{
    return TestSubjectFactory::getTemperatureFaultSubject();
}
