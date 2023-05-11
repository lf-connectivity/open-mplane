/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppControl.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IServicesCtl.h"
#include "IRadio.h"
#include "IServicesMonitor.h"
#include "IServicesMonitorFactory.h"
#include "GlobalTypeDefs.h"

#include "AppControl.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AppControl::AppControl(const std::string& name) :
	Loggable(name,"AP"),

	mRadio(),
	mServicesMonitor(),
	mRadioServices(),
	mApplicationServices(),

	mAppName(name),
	mShutdown( false ),
	mConditional()
{
}

//-------------------------------------------------------------------------------------------------------------
AppControl::~AppControl()
{
}

//-------------------------------------------------------------------------------------------------------------
void AppControl::start()
{
    eventInfo(getName() + " call radio initialisation");

    mRadio = IRadioFactory::getInterface();

    ReturnType::State state = ReturnType::RT_OK ;
    try
    {
         state = mRadio->initialise();
    }
    catch(...)
    {
        state = ReturnType::RT_ERROR;
    }

    eventInfo(getName() + " create services monitor");
    mServicesMonitor = IServicesMonitorFactory::getInterface();

    if( state == ReturnType::RT_OK )
    {

        eventInfo(getName() + " create services");
        mApplicationServices = IServicesFactory::create();

        eventInfo(getName() + " start services monitoring");

        mServicesMonitor->startMonitoring();  // will start the application stable timer


        eventInfo(getName() + " start all services");

        mApplicationServices->start();

        // if we don't start in time the services monitor will reboot the head.

        eventInfo(getName() + " application stable point monitor services");

        mServicesMonitor->applicationStable(); // tell services monitor we are up, hope it's in time
    }
    else
    {
        eventInfo(getName() + " radio initialisation failed");
        // need to add
        mServicesMonitor->applicationFailed();
    }
}

//-------------------------------------------------------------------------------------------------------------
void AppControl::suspend()
{
    eventInfo(getName() + " suspend services");

    mApplicationServices->suspend();
}

//-------------------------------------------------------------------------------------------------------------
void AppControl::resume()
{
    eventInfo(getName() + " resume services");

    mApplicationServices->resume();
}

//-------------------------------------------------------------------------------------------------------------
void AppControl::shutdown()
{
    eventInfo(getName() + " application shutdown request");
    Conditional::Lock lock( mConditional );
    mShutdown = true;
    mConditional.signal();
}

//-------------------------------------------------------------------------------------------------------------
void AppControl::show()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void AppControl::run()
{
    while( !mShutdown )
    {
        mConditional.wait( 1000 );
    }
}

//-------------------------------------------------------------------------------------------------------------
std::string AppControl::getName() const
{
	return mAppName ;
}
