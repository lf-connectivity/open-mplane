/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioControl.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IServicesCtl.h"
#include "EgAppControl.h"
#include "IRadio.h"
#include "IServicesMonitor.h"
#include "IServicesMonitorFactory.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

void Mplane::EgAppControl::start()
{

    ReturnType::State state = ReturnType::RT_OK ;
    try
    {
         state = radio->initialise();
    }
    catch(...)
    {
    }

    if( state == ReturnType::RT_OK )
    {
        servicesMonitor->startMonitoring();  // will start the application stable timer

        services->start();


        // if we don't start in time the services monitor will reboot the head.

        servicesMonitor->applicationStable(); // tell services monitor we are up, hope it's in time

        // call the run method of the final specific radio control implementation.
        run();
    }
    else
    {
        // need to add
        servicesMonitor->applicationFailed();
    }
}

Mplane::EgAppControl::EgAppControl():
    radio (IRadioFactory::getInterface()),
    servicesMonitor (IServicesMonitorFactory::getInterface()),
    services (IServicesFactory::create())
{
}

Mplane::EgAppControl::~EgAppControl()
{
}

void Mplane::EgAppControl::suspend()
{
    services->suspend();
}

void Mplane::EgAppControl::resume()
{
    services->resume();
}
