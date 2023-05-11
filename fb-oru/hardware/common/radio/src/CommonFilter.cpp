/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFilter.cpp
 * \brief     Implementation of the CommonFilter class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonFilter class.
 *
 */

// Includes go here, before the namespace
#include "CommonFilter.h"

using namespace Mplane;


Mplane::CommonFilter::CommonFilter(int index, int number, const char* name):
        Mplane::IFilter::IFilter( index, number, name )
{
}

bool Mplane::CommonFilter::shutdown(void)
{
    // do the filter shutdown - TBD

    return true;
}


Mplane::CommonFilter::~CommonFilter()
{
}

void Mplane::CommonFilter::show(void)
{
}

const Power& Mplane::CommonFilterPortData::getForward() const
{
    return mForward;
}

const Power& Mplane::CommonFilterPortData::getReverse() const
{
    return mReverse;
}

const Power& Mplane::CommonFilterPortData::getDigital() const
{
    return mDigital;
}

const float& Mplane::CommonFilterPortData::getTemperature() const
{
    return mTemperature;
}

void Mplane::CommonFilterPortData::setForward(Power power)
{
    mForward = power;
}

void Mplane::CommonFilterPortData::setReverse(Power power)
{
    mReverse = power;
}

void Mplane::CommonFilterPortData::setDigital(Power power)
{
    mDigital = power;
}

void Mplane::CommonFilterPortData::setTemperature(float temperature)
{
    mTemperature = temperature;
}
