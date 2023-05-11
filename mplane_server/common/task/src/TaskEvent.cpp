/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskEvent.cpp
 * \brief     Task which operates as a result of some event
 *
 *
 * \details   A task which blocks until an event condition occurs, at which
 * point it then calls the derivede object's runEvent() method. Ensures the task
 * is exited on destruction (which calls shutdown() method)
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TaskEvent.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TaskEvent::TaskEvent(
    int priority,
    StackSize stacksize,
    const std::string& name,
    const std::string& suName)
    : Task(priority, stacksize, name.c_str(), suName.c_str()),
      mTaskRun(true),
      mTaskRunning(false),
      mEvent() {
  // self-starting
  start();
}

//-------------------------------------------------------------------------------------------------------------
TaskEvent::~TaskEvent() { shutdown(); }

//-------------------------------------------------------------------------------------------------------------
void
TaskEvent::shutdown() {
  if (!mTaskRunning)
    return;

  // clear run flag to stop task
  mTaskRun = false;

  // keep trying until task stops
  while (mTaskRunning) {
    // trigger task to wait up
    event();

    // wait for task to respond
    msSleep(10);
  }
}

//-------------------------------------------------------------------------------------------------------------
void
TaskEvent::event() {
  // signal to task that event has occurred
  Conditional::Lock condLock(mEvent);
  mEvent.signal();
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int
TaskEvent::run() {
  int rc = 0;
  mTaskRunning = true;

  /*
   * Now our thread is running we just enter an infinite loop so we never end.
   * ALl image management is triggered by invocation of class methods, which are
   * explicit action requests.
   */
  while (mTaskRun) {
    // wait for event
    mEvent.wait();

    // check for task stop
    if (!mTaskRun)
      break;

    // run method
    if (!runEvent()) {
      // exit with error
      rc = 1;
      break;
    }
  }

  mTaskRunning = false;
  return rc;
}
