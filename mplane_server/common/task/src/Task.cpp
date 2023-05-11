/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Task.cpp
 * \brief     Implementation of the Task class
 *
 *
 * \details   This file contains the implementation of the common task Task
 * class.
 *
 */
#include <config.h>
#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include <assert.h>
#include <error.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>

#include "Task.h"
#include "stringfunc.hpp"

// Uncomment this to get more debug
//#define DEBUG_TASK

using namespace Mplane;
using namespace std;

Task::Task(
    int priority, StackSize stacksize, const char* name, const char* suName)
    : Loggable(name, suName),
      mRunForever(false),
      mStackSize(stacksize),
      mStack(0),
      mPriority(0),
      mTaskName(name),
      mSubUnitIdName(suName),
      mThread(0),
      mRunning(false),
      mCancelled(false),
      mRunExitValue(0),
      mParentPid(0),
      mThreadID(0),
      mKickCount(0),
      mTaskListRef(TaskList::getInstance()) {
#ifdef DEBUG_TASK
  std::cerr << "NEW Task " << name << ":" << suName << " @ " << this
            << std::endl;
#endif

  int policy = SCHED_RR;
  if (priority > 0) {
    if (priority > sched_get_priority_max(policy)) {
      static const int _TASK_SAFE_LIMIT = 98;
      priority = _TASK_SAFE_LIMIT;
    }
  } else {
    priority = sched_get_priority_min(policy);
  }

  mPriority = priority;

  mStack = PTHREAD_STACK_MIN * mStackSize;

  TaskList::getInstance()->add(this);
}

Task::~Task() {
#ifdef DEBUG_TASK
  std::cerr << "DEL Task @ " << this << std::endl;
  std::cerr << "Task::~Task " << getInstanceName() << ":" << getGroupName()
            << std::endl;
#endif

  //    if( mThread != 0 )
  //    {
  //        exit();
  //        pthread_attr_destroy( &mThreadAttribute );
  //        pthread_cancel( mThread );
  //    }
  //
  // is our thread still running and the thread ID valid, if it is we need
  // to cancel the thread before all the data associated with is is deleted
  // in this destructor, so call stop() to cancel the thread first
  if (mRunning) {
    stop();
  }
  TaskList::getInstance()->remove(this);
}

int
Task::start() {
  int ret = -1;

  if (!mRunning) {
    pthread_attr_t attr;
    pthread_attr_t* attrp = NULL; /* NULL or &attr */

    attrp = &attr;

    if ((ret = pthread_attr_init(&attr)) != 0) {
      std::cerr << "error in pthread_attr_init : " << strError(ret)
                << std::endl;
      return ret;
    }

    if ((ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED)) !=
        0) {
      std::cerr << "error in pthread_attr_setinheritsched : " << strError(ret)
                << std::endl;
    }

    //        if( (ret = pthread_attr_setschedpolicy(&mThreadAttribute,
    //        SCHED_FIFO)) != 0 )
    if ((ret = pthread_attr_setschedpolicy(&attr, SCHED_RR)) != 0) {
      std::cerr << "error in pthread_attr_setschedpolicy : " << strError(ret)
                << std::endl;
      return ret;
    }

    if ((ret = pthread_attr_setstacksize(&attr, mStack)) != 0) {
      std::cerr << "error in pthread_attr_setstacksize : " << strError(ret)
                << std::endl;
      return ret;
    }

    //        if( (ret = pthread_attr_setdetachstate
    //        (&attr,PTHREAD_CREATE_DETACHED)) != 0)
    //        {
    //            perror("error in pthread_attr_setdetachstae");
    //            return ret;
    //        }

    struct sched_param param;

    if ((ret = pthread_attr_getschedparam(&attr, &param)) == 0) {
      param.sched_priority = mPriority;

      ret = pthread_attr_setschedparam(&attr, &param);
      if (ret) {
        std::cerr << "error in pthread_attr_setschedparam : " << strError(ret)
                  << std::endl;
        return ret;
      }
    } else {
      std::cerr << "error in pthread_attr_getschedparam : " << strError(ret)
                << std::endl;
    }

    if ((ret = pthread_create(&mThread, attrp, &Task::startThread, this)) !=
        0) {
      std::cerr << "error in pthread_create : " << strError(ret) << " (" << ret
                << ")" << std::endl;
#ifdef OFF_TARGET
      std::cerr << "You need to ensure /etc/security/limits.conf has been "
                   "amended to include:"
                << std::endl;
      std::cerr << "  @wtl_axis        -       memlock         51200"
                << std::endl;
      std::cerr << "  @wtl_axis        -       rtprio          98" << std::endl;
      std::cerr << "Please see \"Software Development Environment\" in Radio "
                   "Software Evolution documents area."
                << std::endl;
#endif
    }

    if (attrp != 0) {
      pthread_attr_destroy(attrp);
    }

#ifdef HAVE_PTHREAD_SETAFFINITY_NP
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    if ((ret = pthread_setaffinity_np(mThread, sizeof(cpu_set_t), &cpuset)) !=
        0) {
      std::cerr << "Failed to set CPU affinity for thread : " << strError(ret)
                << std::endl;
    }
#endif
  }
  return ret;
}

int
Mplane::Task::getExitValue() {
  return mRunExitValue;
}

void
Task::execute() {
#ifdef DEBUG_TASK
  std::cerr << "Task::execute @ " << this << std::endl;
  std::cerr << "Task::execute " << getInstanceName() << ":" << getGroupName()
            << std::endl;
#endif

  // now we are running store out parents PID and our own thread PID.
  mParentPid = getpid();
  mThreadID = syscall(SYS_gettid);
  setRunning(true);

  // Add a cleanup method should we get a thread cancel request.
  pthread_cleanup_push(&Task::cancelThread, this);

  mRunExitValue = run();
  //
  // If we exit here then we are return from our run condition normally
  // and not as a result of a cancellation request. So we want to cleanup our
  // task cancellation macro without executing the cleanup routine and
  // then call our exit() method clean cleanup and stop the thread.
  //
  pthread_cleanup_pop(0);
  // remove this task from the global task list.
  //        TaskList::getInstance()->remove( this );
  // now exit our thread safely
  exit();
}

void
Task::exit() {
#ifdef DEBUG_TASK
  std::cerr << "Task::exit @ " << this << std::endl;
  std::cerr << "Task::exit " << getInstanceName() << ":" << getGroupName()
            << std::endl;
#endif

  setRunning(false);
  pthread_detach(pthread_self());
  mThread = 0;
  mThreadID = 0;
  mParentPid = 0;
}

int
Task::getStackSize() {
  return mStack;
}

int
Task::getPriority() {
  return mPriority;
}

const char*
Task::getName() const {
  return mTaskName.c_str();
}

const char*
Task::getSubUnitId() const {
  return mSubUnitIdName.c_str();
}

void
Task::show() {
  logDebugNormal("Task class show() method called, this should be overridden");
}

void*
Task::startThread(void* task) {
#ifdef DEBUG_TASK
  std::cerr << "Task::startThread @ " << task << std::endl;
#endif

  assert(task != NULL);
  Task* theTask = static_cast<Task*>(task);
  theTask->execute();
  return NULL;
}

void
Task::msSleep(int timeout) {
  struct timespec ts = {0};
  ts.tv_sec = 0;
  if (timeout >= 1000) {
    ts.tv_sec = timeout / 1000;
    ts.tv_nsec = (timeout % 1000) * 1000000L;
  } else {
    ts.tv_nsec = timeout * 1000000L;
  }
  nanosleep(&ts, (struct timespec*)0);
}

void
Task::yield(void) {
  sched_yield();
}

bool
Task::isRunning() {
  return mRunning;
}

void
Task::setRunning(bool running) {
  mRunning = running;
}

pthread_t
Mplane::Task::getId() {
  return mThread;
}

pid_t
Mplane::Task::getParentPID() {
  return mParentPid;
}

pid_t
Mplane::Task::getThreadID() {
  return mThreadID;
}

void
Mplane::Task::kickSoftwareWatchdog() {
  ++mKickCount;
}

int
Mplane::Task::getKickCount() {
  return mKickCount;
}

bool
Mplane::Task::isRunForever() {
  return mRunForever;
}

int
Mplane::Task::stop() {
#ifdef DEBUG_TASK
  std::cerr << "Task::stop @ " << this << std::endl;
  std::cerr << "Task::stop " << getInstanceName() << ":" << getGroupName()
            << std::endl;
#endif

  int result;
  void* res;

  // NOTE: stop() and exit() may occur at the same time, so cope with mThread
  // going away
  if (mThread == 0)
    return 0;

  // ask the thread to cancel
  result = pthread_cancel(mThread);

  if (result == 0) {
    if (mThread == 0)
      return 0;

    // join the thread until it cancels
    result = pthread_join(mThread, &res);

    if (result == 0) {
      if (res == PTHREAD_CANCELED) {
        mThread = 0;
      } else {
        result = -1;
      }
    }
  } else // thread ID must be invalid
  {
    mThread = 0;
  }
  return result;
}

void
Mplane::Task::cleanup() {
  // virtual that does nothing here but may be implemented by task
  // implementations.
}

void
Mplane::Task::cancelThread(void* task) {
#ifdef DEBUG_TASK
  std::cerr << "Task::cancelThread @ " << task << std::endl;
#endif

  assert(task != NULL);
  Task* theTask = static_cast<Task*>(task);
  theTask->cancel();
}

void
Mplane::Task::cancel() {
#ifdef DEBUG_TASK
  std::cerr << "Task::cancel @ " << this << std::endl;
  std::cerr << "Task::cancel " << getInstanceName() << ":" << getGroupName()
            << std::endl;
#endif

  //
  // Call the extending classes cleanup method so they can tidy things
  // up when the the underlying task )thread) they are running in is being
  // cancelled.
  //
  cleanup();

  // now tidy up the task related data.
  setRunning(false);
  mCancelled = true;
  // if we are stopping because of a call to our stop method then reset the
  // thread id variable, otherwise leave as is so that the task monitor list
  // nows that the task has been cancelled by some other means,
  pthread_detach(mThread);
  mParentPid = 0;
}

bool
Mplane::Task::wasCancelled() {
  return mCancelled;
}
