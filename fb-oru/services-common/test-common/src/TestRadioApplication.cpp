/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestRadioApplication.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "TestRadioApplication.h"

using namespace Mplane;

Mplane::ATestApp::ATestApp(const char* name, const char* suId):
    Service( SERVICE_MEDIUM_PRIORITY,
             SMALL_STACK,
             1000,
             name,
             suId )
{
    count = 0;
    doneRegObs = false;
}

int Mplane::ATestApp::getCount()
{
    return count;
}

void Mplane::ATestApp::notifytest()
{
    mNotify.lock();
    mNotify.signal();
    mNotify.unlock();
}

void Mplane::ATestApp::show()
{
    eventInfo("*** ATestApp Show ***");
}

int Mplane::ATestApp::service()
{
    count++;
    return 0;
}

void Mplane::ATestApp::doReset()
{
    count = 0;
}

bool Mplane::ATestApp::registerObservers()
{
    doneRegObs = true;
    return doneRegObs;
}

Mplane::TestApplicationServices::TestApplicationServices():
    mAapp(  *(new ATestApp("A_Test_App", "TA"))),
    mBapp(  *(new ATestApp("B_Test_App", "TA"))),
    mCapp(  *(new ATestApp("C_Test_App", "TA")))
{
}

void Mplane::TestApplicationServices::start()
{
    mAapp.start();
    mBapp.start();
    mCapp.start();
}

void Mplane::TestApplicationServices::reset()
{
    mAapp.reset();
    mBapp.reset();
    mCapp.reset();
}

void Mplane::TestApplicationServices::suspend()
{
    mAapp.suspend();
    mBapp.suspend();
    mCapp.suspend();
}

void Mplane::TestApplicationServices::resume()
{
    mAapp.resume();
    mBapp.resume();
    mCapp.resume();
}

void Mplane::TestApplicationServices::shutdown()
{
    mAapp.shutdown();
    mBapp.shutdown();
    mCapp.shutdown();
}

Mplane::TestApplicationServices::~TestApplicationServices()
{
    delete &mAapp;
    delete &mBapp;
    delete &mCapp;
}
