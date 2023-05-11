
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCalBase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CommonCalBase.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;


Mplane::CommonCalBase::CommonCalBase(const char* objectName, const char* subUnitId):
        Loggable( objectName, subUnitId ),
        mVersion(-1),
        mInfo(""),
        mIsLoaded(false)

{
}


std::string Mplane::CommonCalBase::getInfo()
{
    return mInfo;
}

int Mplane::CommonCalBase::getVersion()
{
    return mVersion;
}

bool Mplane::CommonCalBase::isLoaded()
{
    return mIsLoaded;
}

Mplane::CommonCalBase::~CommonCalBase()
{
}

void Mplane::CommonCalBase::setLoaded(bool loaded)
{
    mIsLoaded = loaded;
}

void Mplane::CommonCalBase::setInfo(const std::string& info)
{
    mInfo = info;
}

void Mplane::CommonCalBase::setVersion(int version)
{
    mVersion = version;
}
