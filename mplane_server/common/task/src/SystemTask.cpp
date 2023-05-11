/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemTask.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "SystemTask.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//#define DEBUG_SYSTEM_TASK

// tick time in ms
static const unsigned TASK_TICK_MS = 50;
static constexpr unsigned TICKS_PER_SEC = 1000 / TASK_TICK_MS;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::SystemTask::SystemTask()
    : Task(SYSTEM_TASK_PRIORITY, Task::MEDIUM_STACK, "System Task", "ST"),
      mTaskRunning(true),
      mMutex(),
      mCmd(""),
      mExecuting(false),
      mCmdStatus(0),
      mChildPid(0),
      mCondStart(),
      mCondEnd() {}

//-------------------------------------------------------------------------------------------------------------
Mplane::SystemTask::~SystemTask() {
  // kill off command
  if (mChildPid != 0)
    ::kill(mChildPid, SIGKILL);

  mTaskRunning = false;
  msSleep(2 * TASK_TICK_MS);
}

//-------------------------------------------------------------------------------------------------------------
int
Mplane::SystemTask::runCmd(const std::string& cmd) {
  bool timedOut;
  return runCmd(
      cmd, [](unsigned) {}, 0u, 0u, timedOut);
}

//-------------------------------------------------------------------------------------------------------------
int
Mplane::SystemTask::runCmd(
    const std::string& cmd, unsigned timeoutSecs, bool& timedOut) {
  return runCmd(
      cmd, [](unsigned) {}, 0u, timeoutSecs, timedOut);
}

//-------------------------------------------------------------------------------------------------------------
int
Mplane::SystemTask::runCmd(
    const std::string& cmd,
    ProgressFunction progressFunc,
    unsigned expectedRuntimeSecs) {
  bool timedOut;
  return runCmd(cmd, progressFunc, expectedRuntimeSecs, 0u, timedOut);
}

//-------------------------------------------------------------------------------------------------------------
int
Mplane::SystemTask::runCmd(
    const std::string& cmd,
    ProgressFunction progressFunc,
    unsigned expectedRuntimeSecs,
    unsigned timeoutSecs,
    bool& timedOut) {
  Mutex::Lock lock(mMutex);

#ifdef DEBUG_SYSTEM_TASK
  std::cerr << "SystemTask::runCmd cmd=" << cmd << std::endl;
#endif

  // check settings
  if (cmd.empty()) {
    return STEXIT_INVALID_ARG;
  }

  // Get state and run if idle
  if (mExecuting) {
    return STEXIT_ALREADY_RUNNING;
  }
  mExecuting = true;

  // If nothing has been set in the command string then redirect output to null
  mCmd = cmd;
  if (cmd.find('>') == std::string::npos) {
#ifdef DEBUG_SYSTEM_TASK
    mCmd.append(" 2>&1 >/tmp/systemTask.log");
#else
    mCmd.append(" 2>&1 >/dev/null");
#endif
  }
  // Grab settings for task
  mCmdStatus = 0;
  mChildPid = 0;
  timedOut = false;

  // Show 0 progress if required
  if (expectedRuntimeSecs > 0)
    progressFunc(0);

  // Initiate command
  {
    Conditional::Lock condLock(mCondStart);
    mCondStart.signal();
  }

  // Wait for command to complete
  unsigned runtimeTimer(0);
  unsigned timeoutTimer(timeoutSecs);
  unsigned tick(0);
  while (mCondEnd.wait(TASK_TICK_MS) == false) {
    if (++tick < TICKS_PER_SEC)
      continue;

    tick = 0;

#ifdef DEBUG_SYSTEM_TASK
    std::cerr << "TICK: child=" << mChildPid << std::endl;
#endif

    // Check for timeout
    if (timeoutSecs > 0) {
      if (--timeoutTimer == 0) {
        timedOut = true;

        // kill off command
        ::kill(mChildPid, SIGKILL);

#ifdef DEBUG_SYSTEM_TASK
        std::cerr << "TIMED OUT killing child..." << std::endl;
#endif

        // Keep ticking (and possibly sending kill) until command is exited
      }
    }

    // check for progress report
    if (expectedRuntimeSecs > 0) {
      ++runtimeTimer;

      // callback with progress - limit to max of 99 while running
      unsigned progress(100 * runtimeTimer / expectedRuntimeSecs);
      if (progress >= 100)
        progress = 99;
      progressFunc(progress);
    }
  }

#ifdef DEBUG_SYSTEM_TASK
  std::cerr << "SystemTask::runCmd end rc=" << mCmdStatus << std::endl;
#endif

  mChildPid = 0;

  if (timedOut)
    return STEXIT_TIMEOUT;

  // Show 100 progress if required
  if (expectedRuntimeSecs > 0)
    progressFunc(100);

  return mCmdStatus;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int
SystemTask::run() {
#ifdef DEBUG_SYSTEM_TASK
  std::cerr << "SystemTask run start" << std::endl;
#endif

  /*
   * Now our thread is running we just enter an infinite loop so we never end.
   * ALl image management is triggered by invocation of class methods, which are
   * explicit action requests.
   */
  while (mTaskRunning) {
    //#ifdef DEBUG_SYSTEM_TASK
    //        std::cerr << "SystemTask run tick" << std::endl ;
    //#endif

    // Wait for next TICK or start of download
    if (mCondStart.wait(TASK_TICK_MS) == true) {
#ifdef DEBUG_SYSTEM_TASK
      std::cout << "SystemTask - Start CMD=" << mCmd << std::endl;
#endif
      // run command
      mCmdStatus = simpleSystem(mCmd);

      // Signal end
      {
        Conditional::Lock lock(mCondEnd);
        mCondEnd.signal();
      }

      // Switch back to idle state
      mExecuting = false;

#ifdef DEBUG_SYSTEM_TASK
      std::cerr << "SystemTask - cmd complete status=" << mCmdStatus
                << std::endl;
#endif
    }
  }

  return 0;
}

//-------------------------------------------------------------------------------------------------------------
int
SystemTask::simpleSystem(const std::string& cmd) {
  int status;

  switch (mChildPid = fork()) {
    case -1: /* Error */
#ifdef DEBUG_SYSTEM_TASK
      std::cerr << "SystemTask fork error=" << errno << std::endl;
#endif
      return -1;

    case 0: /* Child */
      ::execl("/bin/sh", "sh", "-c", cmd.c_str(), (char*)NULL);
#ifdef DEBUG_SYSTEM_TASK
      std::cerr << "SystemTask execl error=" << errno << std::endl;
#endif
      ::_exit(127); /* Failed exec */

    default: /* Parent */
      if (::waitpid(mChildPid, &status, 0) == -1) {
#ifdef DEBUG_SYSTEM_TASK
        std::cerr << "SystemTask waitpid error=" << errno << std::endl;
#endif
        return -1;
      } else {
#ifdef DEBUG_SYSTEM_TASK
        std::cerr << "SystemTask waitpid status=" << status << std::endl;
#endif
        return status;
      }
  }
  return 0;
}
