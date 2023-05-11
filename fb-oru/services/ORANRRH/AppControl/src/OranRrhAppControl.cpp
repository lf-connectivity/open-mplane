/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EtnaRRHRadioControl.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "AppTrace.hpp"

#include "IServicesCtl.h"
#include "IRadio.h"
#include "IServicesMonitor.h"
#include "IServicesMonitorFactory.h"
#include "GlobalTypeDefs.h"
#include "TroubleshootHelper.h"
#include "TraceHelper.h"

#include "OranRrhAppControl.h"

using namespace Mplane;

void Mplane::OranRrhAppControl::start()
{
	APP_TRACE("") ;

	eventInfo("RRH call radio initialisation");

	// add troubleshooting
	TroubleshootHelper::commonSetup() ;

	// add trace
	TraceHelper::commonSetup() ;

	// start initialisation
	APP_TRACE_MSG("IRadioFactory::getInterface") ;
	mRadio = IRadioFactory::getInterface();

	ReturnType::State state = ReturnType::RT_OK ;
	try
	{
		APP_TRACE_MSG("mRadio->initialise") ;
		state = mRadio->initialise();
	}
	catch(...)
	{
		state = ReturnType::RT_ERROR;
	}


	APP_TRACE_MSG("IServicesMonitorFactory::getInterface") ;
	eventInfo("RRH create services monitor");
	mServicesMonitor = IServicesMonitorFactory::getInterface();

	if( state == ReturnType::RT_OK )
	{

		APP_TRACE_MSG("IServicesFactory::create") ;
		eventInfo("RRH create services");
		mApplicationServices = IServicesFactory::create();

		eventInfo("RRH start services monitoring");

		APP_TRACE_MSG("mServicesMonitor->startMonitoring") ;
		mServicesMonitor->startMonitoring();  // will start the application stable timer


		eventInfo("RRH start all services");

		APP_TRACE_MSG("mApplicationServices->start") ;
		mApplicationServices->start();

		// if we don't start in time the services monitor will reboot the head.

		eventInfo("RRH application stable point monitor services");

		APP_TRACE_MSG("mServicesMonitor->applicationStable") ;
		mServicesMonitor->applicationStable(); // tell services monitor we are up, hope it's in time
	}
	else
	{
		// need to add
		eventError("RRH application failed to initialise");

		APP_TRACE_MSG("mServicesMonitor->applicationFailed") ;
		mServicesMonitor->applicationFailed();
	}
}

Mplane::OranRrhAppControl::OranRrhAppControl():
	Loggable("RRH","AP"),
	mRadio (),
	mServicesMonitor (),
	mRadioServices (),
	mApplicationServices (),
	mShutdown( false )
{

}

Mplane::OranRrhAppControl::~OranRrhAppControl()
{
}


void Mplane::OranRrhAppControl::run()
{

#ifndef UT
	while( !mShutdown )
	{
		mConditional.wait( 1000 );
	}
#endif

}

void Mplane::OranRrhAppControl::shutdown()
{
	Conditional::Lock lock( mConditional );
	mShutdown = true;
	mConditional.signal();
}


void Mplane::OranRrhAppControl::show()
{
}

void Mplane::OranRrhAppControl::suspend()
{
	eventInfo("RRH suspend services");

	mApplicationServices->suspend();
}

void Mplane::OranRrhAppControl::resume()
{
	eventInfo("RRH resume services");

	mApplicationServices->resume();
}
