/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Module.cpp
 * \brief     Implementation of common Module base class.
 *
 *
 * \details   Implementation of common Module base class.
 *
 */

#include "Module.h"
#include "Initialise.h"

using namespace Mplane;

Mplane::Module::Module(Module::Type type, int index, int number, const char* name):
        mType( type ), mIndex( index ), mNumber( number ), mName( name )
{
}

Mplane::Module::~Module()
{
}

Module::Type Mplane::Module::getType()
{
    return mType;
}

ReturnType::State Mplane::Module::initialise()
{
    return this->_initialise();
}

int Mplane::Module::getIndex()
{
    return mIndex;
}

int Mplane::Module::getNumber()
{
    return mNumber;
}

const char* Mplane::Module::getName()
{
    return mName.c_str();
}
