/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemTask.h
 * \brief     Run a system call in a task
 *
 *
 * \details   Runs an external command inside a task and monitors that task. Optionally can terminate the task if a timeout
 * is specified and the runtime exceeds the timeout.
 *
 * Also optionally can specify a callback function and the expected runtime. The callback is then called every second with the
 * current progress (i.e. the executed time vs expected total runtime). Progress will be an unsigned value 0-100. Guarantees to call
 * at the start with value of 0, and at the end with value of 100 if executes to completion.
 *
 * Unless a specific redirection has been added to the comand string (e.g. "cmd >tmp.txt") then all output will be redirected
 * to /dev/null
 *
 */


#ifndef SYSTEMTASK_H_
#define SYSTEMTASK_H_

#include <sys/types.h>

#include <functional>

#include "Task.h"
#include "Conditional.h"
#include "Mutex.h"

namespace Mplane {

class SystemTask : public Task
{
public:
	// Progress callback - argument is percentage complete (0-100)
	using ProgressFunction = std::function< void(unsigned) > ;

	// Internal exist status values
	enum SystemTaskExit {
		STEXIT_OK				= 0,
		STEXIT_INVALID_ARG		= -1,
		STEXIT_ALREADY_RUNNING	= -2,
		STEXIT_TIMEOUT			= -3,
	};

	SystemTask() ;

	virtual ~SystemTask() ;

	/**
	 * Simplest call - just runs the command and returns the system status.
	 * @param cmd Command string
	 * @return 0 on sucessful completion; otherwise returns executable exit code
	 */
	int runCmd(const std::string& cmd) ;

	/**
	 * Runs the command and returns the system status. If runtime exceeds the specified timeout in seconds then terminates the
	 * command and sets the timedOut flag
	 * @param cmd Command string
	 * @param timeoutSecs Timeout period in seconds
	 * @param timedOut Flag set if execution times out
	 * @return 0 on sucessful completion; otherwise returns executable exit code
	 */
	int runCmd(const std::string& cmd, unsigned timeoutSecs, bool& timedOut) ;

	/**
	 * Runs the command and returns the system status. Every second the progress callback is called with the current progress
	 * comparing the actual runtime against the expected runtime
	 * @param cmd Command string
	 * @param progressFunc Progress callback
	 * @param expectedRuntimeSecs Amount of time in seconds that the command is expected to run for
	 * @return 0 on sucessful completion; otherwise returns executable exit code
	 */
	int runCmd(const std::string& cmd, ProgressFunction progressFunc, unsigned expectedRuntimeSecs) ;

	/**
	 * Runs the command and returns the system status. Every second the progress callback is called with the current progress
	 * comparing the actual runtime against the expected runtime. If runtime exceeds the specified timeout in seconds then terminates the
	 * command and sets the timedOut flag
	 * @param cmd Command string
	 * @param progressFunc Progress callback
	 * @param expectedRuntimeSecs Amount of time in seconds that the command is expected to run for
	 * @param timeoutSecs Timeout period in seconds
	 * @param timedOut Flag set if execution times out
	 * @return 0 on sucessful completion; otherwise returns executable exit code
	 */
	int runCmd(const std::string& cmd,
			ProgressFunction progressFunc, unsigned expectedRuntimeSecs,
			unsigned timeoutSecs, bool& timedOut) ;

protected:
    /**
     * Set a low priority for system calls.
     */
    static const int SYSTEM_TASK_PRIORITY = 20;

    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override;

private:
    /**
     * Implements a (much) simpler version of system(). But also sets the object's child PID member field so that the
     * process can be killed.
     * @param cmd Command
     * @return system exit code
     */
    int simpleSystem(const std::string& cmd) ;

private:
    // Task loop control
    bool mTaskRunning ;

    // Protect state
    mutable Mutex mMutex ;

    // Running state
    std::string mCmd ;
    bool mExecuting ;
    int mCmdStatus ;
    pid_t mChildPid ;

    // Conditional used to start execution
    Conditional mCondStart ;

    // Conditional used to indicate completion
    Conditional mCondEnd ;

} ;

}

#endif /* SYSTEMTASK_H_ */
