/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ServicesMonitorFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "IServicesMonitorFactory.h"
#include "IServicesMonitor.h"
#include "ServicesMonitor.h"

using namespace Mplane;

std::shared_ptr<IServicesMonitor> IServicesMonitorFactory::getInterface()
{
    static std::shared_ptr<IServicesMonitor> servicesMonitor(new ServicesMonitor());
    return servicesMonitor;
}
