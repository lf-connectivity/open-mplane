/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Device.cpp
 * \brief     Implementation of common Device base class.
 *
 *
 * \details   Implementation of common Device base class.
 *
 */

#include "Device.h"

using namespace Mplane;

Mplane::Device::Device(Device::Type type, int index, const std::string& name):
        mType( type ), mIndex( index ), mName( name )
{
}

Mplane::Device::~Device()
{
}

Device::Type Mplane::Device::getType()
{
    return mType;
}

ReturnType::State Mplane::Device::initialise()
{
    return this->_initialise();
}

int Mplane::Device::getIndex()
{
    return mIndex;
}

std::string Mplane::Device::getName()
{
    return mName;
}

std::string Mplane::Device::initResultString()
{
	return this->getInitResultString() ;
}
