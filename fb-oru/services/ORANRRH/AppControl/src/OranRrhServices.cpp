/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhServices.cpp
 * \brief     Implementation of common radio services interface to create and controls all radio services
 *
 *
 * \details   Implementation of common radio services interface to create and controls all radio services
 *
 */

//#define REGISTER_YANG_MGR_SERVICE
#include "config.h"

#include "IImageManagement.h"
#include "TxService.h"

#include "OranRrhUpdateService.h"
#include "RadioStateService.h"

#ifdef FEAT_DPD2_APP
#include "IDpdControl.h"
#endif

#include "OranRrhServices.h"

using namespace Mplane;


// The ApplicationServices implementation

OranRrhServices::OranRrhServices():
	AppServices("RRHApplicationServices")
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

    // Start the update services first as this creates all hardware faults.
    registerService( OranRrhUpdateService::singleton() ) ;

    // Now everything is running create the Radio State Service, which is dependent on owned faults and alarms.
    registerService( std::dynamic_pointer_cast<Service>(IRadioState::getInstance()) );

}

OranRrhServices::~OranRrhServices()
{
}
