/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdAppServices.cpp
 * \brief     Implementation of common radio services interface to create and controls all radio services
 *
 *
 * \details   Implementation of common radio services interface to create and controls all radio services
 *
 */

#include "config.h"

#include "IImageManagement.h"
#include "DpdUpdateService.h"
#include "FibreControlService.h"
#ifdef FEAT_DPD2_APP
#include "IDpdControl.h"
#endif

#include "DpdAppServices.h"
#include "TxService.h"

using namespace Mplane;


// The ApplicationServices implementation
Mplane::DpdAppServices::DpdAppServices():
    AppServices("DpdApplicationServices")
{
    // Task based services
    registerTaskService(IImageManagement::getInstance()) ;
#ifdef FEAT_DPD2_APP
    registerTaskService( std::dynamic_pointer_cast<Task>(IDpdControl::getInterface()) ) ;
#endif

    // Services
    // Start the common TxService that runs power control and vswr alarming
    // TODO: Enable this service to include PCL
    // registerService( std::make_shared<TxService>() ) ;

    registerService( std::make_shared<DpdUpdateService>() ) ;
    registerService( std::make_shared<FibreControlService>() ) ;
}


Mplane::DpdAppServices::~DpdAppServices()
{
}
