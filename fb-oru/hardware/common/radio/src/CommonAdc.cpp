/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAdc.cpp
 * \brief     Implementation of the CommonAdc class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonAdc class.
 *
 */

// Includes go here, before the namespace
#include "CommonAdc.h"

using namespace Mplane;


Mplane::CommonAdc::CommonAdc(int index, const char* name):
       Device( Device::ADC, index, name ),
       mState(false)
{
}

Mplane::CommonAdc::~CommonAdc()
{
}


void Mplane::CommonAdc::enable()
{
    mState = true;
}

void Mplane::CommonAdc::disable()
{
    mState = false;
}


void Mplane::CommonAdc::show(void)
{
}

void Mplane::CommonAdc::show(std::ostream& os)
{
}

int Mplane::CommonAdc::getState()
{
    return mState;
}
