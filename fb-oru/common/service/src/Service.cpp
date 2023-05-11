/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Service.cpp
 * \brief     Base implementation
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "Service.h"
#include <string>
#include "signal.h"
#include "pthread.h"
#include <sys/time.h>

#ifdef OFF_TARGET
//#define DEBUG_SERVICE
#endif

using namespace Mplane;


Mplane::Service::CtlState Mplane::Service::start()
{
#ifdef DEBUG_SERVICE
	std::cerr << "Service[" << getName() << "] start() mState=" << getStateName(mState) << " mControl=" << getControlName(mControl) << " Task.isRunning=" << isRunning() << std::endl ;
#endif

    // no need for lock because thread not yet started.
    if( mState == ServiceCreated )
    {
        mControl = Start;
        registerObservers();
        Task::start();      // start the thread
        // don't use mControl because there could be a task switch and be set back to Noop
        return Start;
    }
    return Noop;
}

Mplane::Service::CtlState Mplane::Service::reset()
{
    Conditional::Lock lock( mNotify );
    if( mState == ServiceRunning )
    {
        mControl = Reset;
        mNotify.signal();
        return Reset;
    }
    return Noop;
}

Mplane::Service::CtlState Mplane::Service::suspend()
{
    Conditional::Lock lock( mNotify );
    if( mState == ServiceRunning )
    {
        mControl = Suspend;
        mNotify.signal();
        return Suspend;
    }
    return Noop;
}

Mplane::Service::CtlState Mplane::Service::resume()
{
    Conditional::Lock lock( mNotify );
    if( mState == ServiceSuspended )
    {
        mControl = Resume;
        mNotify.signal();
        return Resume;
    }
    return Noop;
}

Mplane::Service::CtlState Mplane::Service::shutdown()
{
#ifdef DEBUG_SERVICE
	std::cerr << "Service[" << getName() << "] shutdown() mState=" << getStateName(mState) << " mControl=" << getControlName(mControl) << " Task.isRunning=" << isRunning() << std::endl ;
#endif

	// If Task isn't running then we've stopped
	if (!isRunning())
	{
		mState = ServiceShutdown;
        return Shutdown;
	}

	// Task running so it's safe to signal to the Sevice thread
    Conditional::Lock lock( mNotify );
    if( mState == ServiceRunning )
    {
        mControl = Shutdown;
        mNotify.signal();
        return Shutdown;
    }
    return Noop;
}

void Mplane::Service::eventNotify()
{
    Conditional::Lock lock( mNotify );
    mNotify.signal();
}

Service::State Mplane::Service::getState()
{
    return mState;
}


Mplane::Service::Service(ServicePriority_t priority, StackSize stacksize,
        unsigned int msecTimerPeriod, const char* name, const char* suName):
                Task( priority, stacksize, name, suName),
                mMsecTimerPeriod( msecTimerPeriod ),
                mState( ServiceCreated ),
                mControl( Noop )

{
    mRunForever = true;
    if( mMsecTimerPeriod > 5000 )
    {
        logDebugNormal("Service[%s]: Error creating with timer period greater than 5000 msec",name);
    }
}


int Mplane::Service::run()
{
    int serviceError = 0;
    mState = ServiceRunning;
    mControl = Noop;
    // for now just use sleep until we get the timer stak delivery to the conditional working.
    unsigned int loopTime = mMsecTimerPeriod;
    unsigned int execTime = 0;
    struct timeval startTime;
    struct timeval endTime;

    while( mState != ServiceShutdown)
    {
        // if we are in this loop not because of a control, try and run the service.
        if( mControl == Noop )
        {
            if( mState == ServiceRunning )
            {
                // is we have something to do, see how long it takes.
                gettimeofday(&startTime, 0);
                serviceError = service();  // while we are in the running state, do our stuff.
                if( serviceError != 0 )
                {
                    mState = ServiceShutdown;
                }
                gettimeofday(&endTime, 0);

                execTime = (endTime.tv_sec * 1000) + (endTime.tv_usec / 1000 );
                execTime -= (startTime.tv_sec * 1000) + (startTime.tv_usec / 1000 );
                // use this to adjust how long we wait, so our service has accurate update rate
                if( execTime >= mMsecTimerPeriod )
                {
                    logDebugNormal("Service[%s]: execution time overrun", getName());
                    execTime = 0;
                }
            }
        }
        loopTime = mMsecTimerPeriod - execTime; // correct for the service execution time

        // if our service return an error, let's get out straight away.
        if( serviceError == 0 && mNotify.wait( loopTime ) == true ) // where we signalled, or did we reach timeout
        {
            // got a signal, what control do we have to do?
            execTime = 0;
            switch( mControl )
            {
            case Noop:
            case Start:     // only valid when service thread not started.
                break;
            case Reset:
                mState = ServiceReset;    // we've been asked to reset
                doReset();                  // perform reset, should be overridden
                mState = ServiceRunning;
                break;
            case Suspend:
                mState = ServiceSuspended;
                break;
            case Resume:
                mState = ServiceRunning;
                break;
            case Shutdown:
                mState = ServiceShutdown;
                break;
            }
            mControl = Noop;
        }

        kickSoftwareWatchdog();

    }
    return serviceError;
}

bool Mplane::Service::registerObservers()
{
    // nothing to do in the base class, must be overridden
    logDebugNormal("Service[%s]: Class registerObservers() method called, this should be overridden", getName());
    return true; // nothing to do in the base class, must be overridden
}

Mplane::Service::~Service()
{
#ifdef DEBUG_SERVICE
	std::cerr << "Service[" << getName() << "] destroy mState=" << getStateName(mState) << " mControl=" << getControlName(mControl) << std::endl ;
#endif

    // hold in destructor until the Service really is shutdown!
    while ( mState == ServiceRunning )
    {
#ifdef DEBUG_SERVICE
	std::cerr << "Service[" << getName() << "] destroy (call shutdown()) mState=" << getStateName(mState) << " mControl=" << getControlName(mControl) << std::endl ;
#endif
        shutdown() ;
        Task::msSleep(1) ;
    }

#ifdef DEBUG_SERVICE
	std::cerr << "Service[" << getName() << "] destroy END mState=" << getStateName(mState) << " mControl=" << getControlName(mControl) << std::endl ;
#endif
}

void Mplane::Service::doReset()
{
    // nothing to do in the base class, must be overridden
    logDebugNormal("Service[%s]: Class doReset() method called, this should be overridden", getName());
}

void Mplane::Service::show()
{
    // nothing to do in the base class, must be overridden
    logDebugNormal("Service[%s]: Class show() method called, this should be overridden", getName());
}

const char* Mplane::Service::getStateName(State state)
{
    const char *stateName="Unknown";

    switch ( state )
    {
    case ServiceCreated:
        stateName = "Created";
        break;
    case ServiceStarted:
        stateName = "Started";
        break;
    case ServiceReset:
        stateName = "Reset";
        break;
    case ServiceSuspended:
        stateName = "Suspended";
        break;
    case ServiceResumed:
        stateName = "Resumed";
        break;
    case ServiceRunning:
        stateName = "Running";
        break;
    case ServiceFault:
        stateName = "Fault";
        break;
    case ServiceShutdown:
        stateName = "Shutdown";
        break;
    }
    return stateName;
}


const char* Mplane::Service::getControlName(CtlState ctlState)
{
    const char *stateName="Unknown";

    switch ( ctlState )
    {
    case Noop:
        stateName = "NoOperation";
        break;
    case Start:
        stateName = "Start";
        break;
    case Reset:
        stateName = "Reset";
        break;
    case Suspend:
        stateName = "Suspend";
        break;
    case Resume:
        stateName = "Resume";
        break;
    case Shutdown:
        stateName = "Shutdown";
        break;
    }
    return stateName;

}
