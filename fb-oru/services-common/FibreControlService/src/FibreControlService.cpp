/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FibreControlService.cpp
 * \brief     Implementation of common radio Fibre Control services interface to create and control the fibre interface
 *
 *
 * \details   Implementation of common radio Fibre Control services interface to create and control the fibre interface
 *
 */

#include "IFibreControl.h"
#include "FibreControlService.h"

using namespace Mplane;

Mplane::FibreControlService::FibreControlService():
        Service( SERVICE_MEDIUM_PRIORITY,
                SMALL_STACK,
                FibreControlService::SERVICE_PERIOD,
                "FibreControlService", "FS" ),
        mFibreController( IFibreControl::getInterface() )
{
    eventInfo("FibreControlService created");
}

void Mplane::FibreControlService::show()
{
    eventInfo("*** FibreControlService Show ***");

    mFibreController->showFibreControl();

    eventInfo("*** End FibreControlService Show ***");
}

int Mplane::FibreControlService::service()
{
    static int count = 0;

    count++;

    logDebugNormal("FibreControlService - executing service, entered %d times", count);

    mFibreController->serviceFibreControl();

    return 0;  // normal good exit, all OK
}

bool Mplane::FibreControlService::registerObservers()
{
    mFibreController->startFibreControl();
    return true;
}

void Mplane::FibreControlService::doReset()
{
    mFibreController->resetFibreControl();
}

Mplane::FibreControlService::~FibreControlService()
{
}
