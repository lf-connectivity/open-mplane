/*
 * ServicesMonitor.cpp
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "signal.h"

#include "Conditional.h"
#include "Mutex.h"
#include "Service.h"

#include "KickWatchdog.h"
#include "ServicesMonitor.h"

using namespace Mplane;
using namespace std;

#ifdef OFF_TARGET
const std::string STATE_DIR("/tmp/");
#else
const std::string STATE_DIR("/var/log/");
#endif

const std::map<IServicesMonitor::ApplicationState, std::string> STATE_MAP{
    {IServicesMonitor::INITIALISING, "INITIALISING"},
    {IServicesMonitor::STABLE, "STABLE"},
    {IServicesMonitor::FAILED, "FAILED"},
};

/*
 * Provides the "application stable state" feedback for image rollback feature
 *
 *  \satisfy{@req_8403{061}}
 *  \satisfy{@req_8403{062}}
 *  \satisfy{@req_8403{063}}
 *  \satisfy{@req_8403{064}}
 *  \satisfy{@req_8403{065}}
 *
 */

Mplane::ServicesMonitor::ServicesMonitor()
    : Task(
          SERVICE_MONITOR_PRIORITY,
          Task::MEDIUM_STACK,
          "Services Monitor",
          "SY"),
      mAppState(IServicesMonitor::INITIALISING),
      mLoop(true),
      mApplicationStableCount(APPLICATION_STABLE_TIME),
      mStartupPhase(true),
      mMsecTimerPeriod(MONITOR_RATE),
      mServiceCheckCount(0),
      mServiceDied(false),
      mServiceStuck(false),
      mStateFilename(STATE_DIR + "app-state.txt") {
  mWatchdog = new KickWatchdog();

  updateStateFile();
}

Mplane::ServicesMonitor::~ServicesMonitor() { delete mWatchdog; }

void
Mplane::ServicesMonitor::startMonitoring() {
  if (isRunning() == false) {
    // start our monitor thread, so that our run method is called.
    start();
  }
}

void
Mplane::ServicesMonitor::applicationFailed() {
  Conditional::Lock lock(mNotify); // acquire conditional mutex, BSTS
  mAppState = IServicesMonitor::FAILED;
  mApplicationStableCount = 1;
  mNotify.signal();

  updateStateFile();
}

void
Mplane::ServicesMonitor::applicationStable() {
  Conditional::Lock lock(mNotify); // acquire conditional mutex, BSTS
  mAppState = IServicesMonitor::STABLE;
  mStartupPhase = false; // startup complete start services monitoring
  mNotify.signal();

  updateStateFile();
}

IServicesMonitor::ApplicationState
ServicesMonitor::getApplicationState() const {
  return mAppState;
}

int
Mplane::ServicesMonitor::run() {
  // remove ourselves from the task list.
  TaskList::getInstance()->remove(mWatchdog);
  TaskList::getInstance()->remove(this);
  Task::msSleep(100);

  // now our thread is running, start the 'stuck service monitor' thread.
  mWatchdog->start();

  while (mLoop) {
    mNotify.wait(mMsecTimerPeriod);
    //        Mplane::Task::msSleep( 1000 );
    if (mStartupPhase) {
      logDebugNormal("Services monitor - waiting to reach app stable");
      if (--mApplicationStableCount <= 0) {
        eventInfo("WARNING - Application failed to reach stable point");
        mStartupPhase = false;
        mAppState = IServicesMonitor::FAILED;

        updateStateFile();
      }
    } else {
      monitorServices();
    }
  }
  mWatchdog->shutdown();
  return 0;
}

void
Mplane::ServicesMonitor::monitorServices() {
  static const char* failedService;

  if (++mServiceCheckCount == SERVICE_CHECK_RATE) {
    char time_str[50];
    time_t t = time(NULL);
    struct tm tm;
    localtime_r(&t, &tm);

    sprintf(
        time_str,
        "%4d-%02d-%02d %02d:%02d:%02d:",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec);

    logDebugNormal(
        "%s Services monitor - check for stuck or cancelled tasks", time_str);
    mServiceCheckCount = 0;
    if (TaskList::getInstance()->allRunning(&failedService) == false) {
      if (mServiceDied == false)
        logDebugNormal(
            "%s Critical error: %s has failed - restart",
            time_str,
            failedService);
      mServiceDied = true;
    }

    // check for tasks that have not called the kickSoftwareWatchdog() method.
    Task* task = TaskList::getInstance()->checkStuckTask();
    if (task != 0) {
      if (mServiceStuck == false)
        logDebugNormal(
            "%s Critical error: task %s is a CPU hog - for now cancel thread",
            time_str,
            task->getName());
      //            pthread_kill( task->getId(), SIGQUIT ); // for now kill the
      //            task causing the problem
      pthread_cancel(task->getId());

      mServiceStuck = true;
    }
  }
}

void
ServicesMonitor::updateStateFile() {
  std::ofstream file(mStateFilename, ios::app);
  file << "appState=" << STATE_MAP.at(mAppState) << std::endl;
  file.close();
}
