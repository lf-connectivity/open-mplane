/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Initialise.cpp
 * \brief     The implementation of the Initialise base class
 *
 *
 * \details   This file contains the implementation of the Initialise
 *            base class, from which all other software modules must inherit.
 *            They must implement the pure virtual method initialise().
 *            This common class implements the setters and getters for them
 *            to use.
 *
 */

#include "Initialise.h"

using namespace Mplane;


/******* End - Base class interface implementation ***********/

Initialise::Initialise() :
	mInitResult{ReturnType::RT_ERROR},
	mInitResultString{"UNINITIALISED"},
	mInitStartTime{0, 0},
	mInitEndTime{0, 0},
	mInitDurationTime{0},
	mInitComplete{false}
{
}

Initialise::~Initialise()
{
    mInitResultString.clear();
}

ReturnType::State Initialise::_initialise()
{
//    if (isInitComplete())
//    {
//        /*! \TODO - add init trace here to indicate a false entry, should not
//         * call it more than once.
//         */
//
//        // already initialised, so early exit, nothing to do
//        return ReturnType::RT_ALREADY_INITIALISED;
//    }

    setInitStartTime();  // record the time of the

    // do the specific init procedure
    ReturnType::State result = doInit();

    setInitResult(result);
    setInitComplete();
    setInitEndTime();
    setInitDurationTime();

    return result;
}

////////////// Getters //////////////////

ReturnType::State Initialise::getInitResult()
{
    return mInitResult;
}

std::string& Initialise::getInitResultString()
{
    return mInitResultString;
}

struct timeval* Initialise::getInitStartTime()
{
    return &mInitStartTime;
}

struct timeval* Initialise::getInitEndTime()
{
    return &mInitEndTime;
}

int Initialise::getInitDurationTime()
{
    return mInitDurationTime;
}

bool Initialise::isInitComplete()
{
    return mInitComplete;
}


////////////// Setters //////////////////

void Initialise::setInitResult(ReturnType::State value)
{
    if (!mInitComplete)
    {
        // Cannot be set if init is already done
        mInitResult = value;
    }
}

void Initialise::setInitResultString(std::string& value)
{
    if (!mInitComplete)
    {
        // Cannot be set if init is already done
        mInitResultString = value;
    }
}

void Initialise::setInitStartTime()
{
    if (mInitDurationTime == 0)
    {
        // Cannot be set if init is already done
        (void)gettimeofday(&mInitStartTime, 0);
    }
}

void Initialise::setInitEndTime()
{
    if (mInitDurationTime == 0)
    {
        // Cannot be set if init is already done
        (void)gettimeofday(&mInitEndTime, 0);
    }
}

void Initialise::setInitDurationTime()
{
    if (mInitDurationTime == 0)
    {
        // Cannot be set if init is already done
        INT64 delta;

        delta = (INT64)mInitEndTime.tv_sec * 1000000L + mInitEndTime.tv_usec;
        delta -= (INT64)mInitStartTime.tv_sec * 1000000L + mInitStartTime.tv_usec;

        mInitDurationTime = (int)delta;
    }
}

void Initialise::setInitComplete()
{
    mInitComplete = true;
}
