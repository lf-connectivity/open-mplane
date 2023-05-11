/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDac.cpp
 * \brief     Implementation of the CommonDac class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonDac class.
 *
 */

// Includes go here, before the namespace
#include "CommonDac.h"

using namespace Mplane;


Mplane::CommonDac::CommonDac(int index, const char* name):
        Device(Device::DAC, index, name ),
        mState(false)
{
}

Mplane::CommonDac::~CommonDac()
{
}

void Mplane::CommonDac::enableOutput()
{
    mState = true;
}

void Mplane::CommonDac::disableOutput()
{
    mState = false;
}


void Mplane::CommonDac::show(void)
{
}

int Mplane::CommonDac::getState()
{
    return mState;
}

ReturnType::State Mplane::CommonDac::setDCOffset(short int i, short int q)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

ReturnType::State Mplane::CommonDac::setPhaseOffset(short int i, short int q)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

ReturnType::State Mplane::CommonDac::setMagOffset(short int i, short int q)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

ReturnType::State Mplane::CommonDac::setIfOffset(double  MHzOffset)
{
    return ReturnType::RT_NOT_SUPPORTED;
}

double Mplane::CommonDac::getIfOffset()
{
    return 0.0;
}

ReturnType::State Mplane::CommonDac::setFrequency( double  MHz )
{
    return ReturnType::RT_NOT_SUPPORTED;
}

double Mplane::CommonDac::getFrequency()
{
    return 0.0;
}

ReturnType::State Mplane::CommonDac::resetFifo()
{
    return ReturnType::RT_NOT_SUPPORTED;
}

unsigned Mplane::CommonDac::getFifoLevel()
{
	return 0 ;
}
