/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhAppControl.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "AppTrace.hpp"

#include "GlobalTypeDefs.h"
#include "IServicesCtl.h"
#include "IServicesMonitor.h"
#include "IServicesMonitorFactory.h"

#include "OranRrhAppControl.h"

using namespace Mplane;

void
Mplane::OranRrhAppControl::start() {
  APP_TRACE("");

  eventInfo("RRH call radio initialisation");

  // start initialisation
  APP_TRACE_MSG("IServicesMonitorFactory::getInterface");
  eventInfo("RRH create services monitor");
  mServicesMonitor = IServicesMonitorFactory::getInterface();

  APP_TRACE_MSG("IServicesFactory::create");
  eventInfo("RRH create services");
  mApplicationServices = IServicesFactory::create();

  eventInfo("RRH start services monitoring");

  APP_TRACE_MSG("mServicesMonitor->startMonitoring");
  mServicesMonitor->startMonitoring(); // will start the application stable
                                       // timer

  eventInfo("RRH start all services");

  APP_TRACE_MSG("mApplicationServices->start");
  mApplicationServices->start();

  // if we don't start in time the services monitor will reboot the head.

  eventInfo("RRH application stable point monitor services");

  APP_TRACE_MSG("mServicesMonitor->applicationStable");
  mServicesMonitor->applicationStable(); // tell services monitor we are up,
                                         // hope it's in time
}

Mplane::OranRrhAppControl::OranRrhAppControl()
    : Loggable("RRH", "AP"),
      mServicesMonitor(),
      mApplicationServices(),
      mShutdown(false) {}

Mplane::OranRrhAppControl::~OranRrhAppControl() {}

void
Mplane::OranRrhAppControl::run() {

#ifndef UT
  while (!mShutdown) {
    mConditional.wait(1000);
  }
#endif
}

void
Mplane::OranRrhAppControl::shutdown() {
  eventInfo("RRH application shutdown request");
  mApplicationServices->shutdown();

  Conditional::Lock lock(mConditional);
  mShutdown = true;
  mConditional.signal();
}

void
Mplane::OranRrhAppControl::show() {}

void
Mplane::OranRrhAppControl::suspend() {
  eventInfo("RRH suspend services");

  mApplicationServices->suspend();
}

void
Mplane::OranRrhAppControl::resume() {
  eventInfo("RRH resume services");

  mApplicationServices->resume();
}
