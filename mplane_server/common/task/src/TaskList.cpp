/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskList.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include "Task.h"
#include "pthread.h"
#include "signal.h"
#include <string.h>

#include "stringfunc.hpp"

using namespace Mplane;
using namespace std;

std::shared_ptr<TaskList>
TaskList::getInstance() {
  static std::shared_ptr<TaskList> instance(new TaskList);
  return instance;
}

TaskEntry::TaskEntry(Task* task) : mTask(task), mLastKickCount(0) {
  mLastKickCount = mTask->getKickCount();
}

Task*
TaskEntry::getTask() {
  return mTask;
}

TaskEntry::~TaskEntry() {
  mLastKickCount = 0;
  mTask = 0;
}

bool
TaskEntry::checkKickCount() {
  int count = mTask->getKickCount();
  if (count != mLastKickCount) {
    mLastKickCount = count;
    return true;
  }

  return false; // the software watchdog kick counter failed
}

TaskList::TaskList() : Loggable("TaskList", "SY") {}

TaskList::~TaskList() {}

void
TaskList::add(Task* task) {
  Mutex::Lock lock(mTaskListMutex);
  std::shared_ptr<TaskEntry> taskEntry(new TaskEntry(task));
  mTaskList.push_back(taskEntry);
}

void
TaskList::remove(Task* task) {
  Mutex::Lock lock(mTaskListMutex);

  TaskIterator taskIterator;

  for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
       ++taskIterator) {

    if ((*taskIterator)->getTask() == task) {
      // Remove the entry
      mTaskList.erase(taskIterator);
      break;
    }
  }
}

void
TaskList::show(std::ostream& os) {
  os << "-- Task List --" << std::endl;

  static const unsigned TID_WIDTH = 16;
  static const unsigned SUID_WIDTH = 16;
  static const unsigned NAME_WIDTH = 30;
  static const unsigned STATE_WIDTH = 15;
  static const unsigned PRIORITY_WIDTH = 3;

  os << padLeft("TDI", TID_WIDTH) << padLeft("SUID", SUID_WIDTH)
     << padLeft("Name", NAME_WIDTH) << padLeft("State", STATE_WIDTH)
     << padLeft("PRI", PRIORITY_WIDTH) << std::endl;
  os << padLeft("---", TID_WIDTH) << padLeft("----", SUID_WIDTH)
     << padLeft("----", NAME_WIDTH) << padLeft("-----", STATE_WIDTH)
     << padLeft("---", PRIORITY_WIDTH) << std::endl;

  if (!mTaskList.empty()) {
    TaskIterator taskIterator;
    for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
         ++taskIterator) {
      Task* task = (*taskIterator)->getTask();
      string tid = std::to_string(task->getId());
      os << padLeft(tid, TID_WIDTH);
      os << padLeft(task->getSubUnitId(), SUID_WIDTH);
      os << padLeft(task->getName(), NAME_WIDTH);
      if (task->isRunning()) {
        os << padLeft("RUNNING", STATE_WIDTH);
      } else {
        os << padLeft("STOPPPED", STATE_WIDTH);
      }
      os << padLeft(std::to_string(task->getPriority()), PRIORITY_WIDTH);
      os << std::endl;
    }
  }
}

void
TaskList::showNames() {
  if (!mTaskList.empty()) {
    TaskIterator taskIterator;
    for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
         ++taskIterator) {
      Task* task = (*taskIterator)->getTask();
      std::string logout(task->getName());
      if (task->isRunning()) {
        logout += " is RUNNING";
      } else {
        logout += " is STOPPPED";
      }
      logDebugNormal(logout);
    }
  } else {
    logDebugNormal("(showNames) task list is empty");
  }
}

void
TaskList::show() {
  if (!mTaskList.empty()) {
    TaskIterator taskIterator;

    for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
         ++taskIterator) {
      (*taskIterator)->getTask()->show();
    }
  } else {
    logDebugNormal("(show) task list is empty");
  }
}

bool
TaskList::allRunning(const char** failedName) {
  Mutex::Lock lock(mTaskListMutex);

  TaskIterator taskIterator;

  for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
       ++taskIterator) {
    Task* task = (*taskIterator)->getTask();
    if (task != 0) {
      // only check the status of tasks that have been marked as run forever.
      if (task->isRunForever()) {
        // check to see if the thread associated with the task is still active
        if (task->getId() != 0 && pthread_kill(task->getId(), 0) != 0) {
          *failedName = task->getName();
          return false;
        }
      }
    }
  }
  return true;
}

Task*
TaskList::checkStuckTask() {
  Mutex::Lock lock(mTaskListMutex);

  TaskIterator taskIterator;

  for (taskIterator = mTaskList.begin(); taskIterator != mTaskList.end();
       ++taskIterator) {
    Task* task = (*taskIterator)->getTask();
    if (task != 0) {
      // only check the stuck status of tasks that have been marked as run
      // forever.
      if (task->isRunForever()) {
        // check to see if the thread associated with the task is still active
        if (task->getId() != 0 && pthread_kill(task->getId(), 0) == 0) {
          if (!(*taskIterator)->checkKickCount()) {
            return task;
          }
        }
      }
    }
  }
  return (Task*)0;
}
