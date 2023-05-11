/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonModules.cpp
 * \brief     Base class implementation for CommonModules class.
 *
 *
 * \details   Base class implementation for CommonModules class.
 *
 */

#include "CommonModules.h"
#include "IFilter.h"
#include "IFem.h"

using namespace Mplane;

ReturnType::State Mplane::CommonModules::initialise()
{
    throw std::invalid_argument("initialise() must be implemented by a radio specific base class.");

    return ReturnType::RT_OK;
}

bool Mplane::CommonModules::shutdown(void)
{
    throw std::invalid_argument("shutdown() must be implemented by a radio specific base class.");

    return false;
}

IFilter& Mplane::CommonModules::getFilter( int index ) /* throw (std::invalid_argument) */
{
    IFilter* module = 0;

    throw std::invalid_argument("getFilter() must be implemented by a radio specific base class, if supported.");

    // cppcheck-suppress nullPointer
    return *module;
}

IFem& Mplane::CommonModules::getFem(int index) /* throw (std::invalid_argument) */
{
    IFem* module = 0;

    throw std::invalid_argument("getFem() must be implemented by a radio specific base class, if supported.");

    // cppcheck-suppress nullPointer
    return *module;
}

void Mplane::CommonModules::show()
{
}

Mplane::CommonModules::CommonModules()
{
}

Mplane::CommonModules::~CommonModules()
{
}
