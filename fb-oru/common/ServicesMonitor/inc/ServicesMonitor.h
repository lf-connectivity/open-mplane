#ifndef _COMMON_SERVICESMONITOR_H_
#define _COMMON_SERVICESMONITOR_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ServicesMonitor.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IServicesMonitor.h"
#include "Task.h"
#include "Conditional.h"

namespace Mplane
{

class KickWatchdog;

class ServicesMonitor: public IServicesMonitor, public Task
{

public:
    /**
     * ServicesMonitorTestCase is a friend for unit test purposes;
     */
    friend class ServicesMonitorTestCase;

    /**
     * Method used to start service monitoring task
     */
    virtual void startMonitoring() override;

    /**
     * Indicates that the application failed to start, calling this method
     * should for more than 2 successive reboots will result in the current
     * application image being retired and the previous image restored
     * as the primary.
     */
    virtual void applicationFailed() override;

    /**
     * Calling this method indicates that the application has reached a stable
     * point where all services have been started and the radio is ready to be
     * connected and configured.
     */
    virtual  void applicationStable() override;

    /**
     * Return the current application state
     */
    virtual IServicesMonitor::ApplicationState getApplicationState() const override ;



    /**
     * destructor
     */
    ~ServicesMonitor();


protected:
    friend class IServicesMonitorFactory;
    /**
     * Constructor protected so task can only be created by the singleton
     * implementation in the friend class IServicesMonitorFactory.
     */
    ServicesMonitor();

    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run();

    /**
     * Once the application has started an reached its stable point, the
     * monitorServices method is called to ensure all the services in
     * the services list continue to run and that no task is hoging
     * all the available CPU resources.
     */
    void monitorServices();

    static const int SERVICE_MONITOR_PRIORITY = 95;

    /**
     * Update the application state file. The state file is a text file that contains the state of the application.
     * A new line containing the current application state is written each time the state changes. The last line is the current
     * application state
     */
    void updateStateFile() ;

private:

    IServicesMonitor::ApplicationState mAppState ;

    bool mLoop;
    /**
     * Allow up to 45 seconds for the application to reach its stable
     * point.
     */
    static const int APPLICATION_STABLE_TIME = 45;
    /*!
     * Down counter used on system start up to ensure the application starts
     * and reaches a stable point within the APPLICATION_STABLE_TIME.
     */
    int mApplicationStableCount;

    bool mStartupPhase;

    static const unsigned int MONITOR_RATE = 1000;

    /**
     * The service monitor rate
     */
    unsigned int mMsecTimerPeriod;


    /**
     * This conditional is used in the main run loop by calling the
     * conditionals wait with timeout method the service() method will either
     * be called as a result of the timer expiring or being notified by
     * a call to the conditional signal method.
     */
    Conditional mNotify;

    /**
     * Define how often the the services monitor checks for dead and stuck tasks
     */
    static const int SERVICE_CHECK_RATE = 5;

    /**
     * Check count used to determine number of 1 second counts has expire.
     */
    int mServiceCheckCount;


    /**
     * The task that increments our application monitor count.
     */
    KickWatchdog* mWatchdog;

    bool mServiceDied;

    bool mServiceStuck;

    std::string mStateFilename ;

};


}



#endif /* _SERVICESMONITOR_H_ */
