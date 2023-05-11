/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskPeriodicEvent.h
 * \brief     Task which operates as the result of an event OR after a fixed
 * period
 *
 *
 * \details   Task which operates immediately on an asynchronous event. If no
 * event has occurred after a fixed period then task will operate anyway.
 *
 */

#ifndef TASKPERIODICEVENT_H_
#define TASKPERIODICEVENT_H_

#include "Conditional.h"
#include "Mutex.h"
#include "Task.h"

namespace Mplane {

class TaskPeriodicEvent : public Task {
 public:
  TaskPeriodicEvent(
      unsigned periodMs,
      int priority = 0,
      StackSize stacksize = SMALL_STACK,
      const std::string& name = "Unnamed Task",
      const std::string& suName = "TKEVENT");
  virtual ~TaskPeriodicEvent();

  /**
   * Shutdown any running process
   */
  virtual void shutdown();

  /**
   * Event has occurred - trigger the task to run
   */
  virtual void event();

 protected:
  /**
   * True if runEvent() is called due to an event
   */
  bool isEvent() const;

  /**
   * True if runEvent() is called due to period timeout
   */
  bool isPeriodic() const;

 protected:
  /**
   * This is the TaskEvent run method that must be provided by inherited objects
   *
   * @return true if ok; false if operation failed and task should exit
   */
  virtual bool runEvent() = 0;

 protected:
  /**
   * This is the Task method that is run by the start() method.
   *
   * \return the exit status of task process
   */
  virtual int run() override;

 protected:
  bool mTaskRun;
  bool mTaskRunning;
  Conditional mEvent;
  unsigned mPeriodMs;
  bool mPeriodicEvent; //<! Set if event is due to periodic timeout rather than
                       // asynchronous event
};

} // namespace Mplane

#endif /* TASKPERIODICEVENT_H_ */
