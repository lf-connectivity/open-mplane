/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCam.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "CommonCam.h"

using namespace Mplane;


void Mplane::CommonCam::show(void)
{
}

Mplane::CommonCam::CommonCam(int index, const char* name):
		Device(Device::CAM, index, name )
{
}

Mplane::CommonCam::~CommonCam()
{
}

ReturnType::State Mplane::CommonCam::readAdc(int channelIndex, int &value) /* throw (std::out_of_range) */
{
    value = 0;
    throw( std::out_of_range("readAdc() not implemented in base class") );
    return ReturnType::RT_OK;
}

bool Mplane::CommonCam::writeDac(int channelIndex, int value) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("writeDac() not implemented in base class") );
    return false;
}

int Mplane::CommonCam::getValue(int channelIndex) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("getValue() not implemented in base class") );
    return 0;
}

bool Mplane::CommonCam::setOutput(unsigned bitSelect, unsigned value) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("setOutput() not implemented in base class") );
    return false;
}

bool Mplane::CommonCam::getOutput(unsigned bitSelect) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("getOutput() not implemented in base class") );
    return false;
}

bool Mplane::CommonCam::getInput(int bitSelect) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("getInput() not implemented in base class") );
    return false;
}

bool Mplane::CommonCam::setFreeRun(bool value) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("setFreeRun() not implemented in base class") );
    return false;
}

bool Mplane::CommonCam::getFreeRun() /* throw (std::out_of_range) */
{
    throw( std::out_of_range("getFreeRun() not implemented in base class") );
    return false;
}

bool Mplane::CommonCam::setAdcGain( unsigned int channel, adcGain_T adcGain) /* throw (std::out_of_range) */
{
    throw( std::out_of_range("setAdcGain() not implemented in base class") );
    return false;
}
