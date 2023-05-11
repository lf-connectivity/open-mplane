#ifndef AA_COMMON_TASK_H_
#define AA_COMMON_TASK_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Task.h
 * \brief     A file to contain the base Task class
 *
 *
 * \details   This file defines the base Task class
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include <memory>
#include <vector>
#include <iostream>

#include "Mutex.h"
#include "Loggable.h"

namespace Mplane
{


/**
 * Task is a simple base class that can be used to run a code sequence
 * as a detached POSIX thread. The task will continue to run until it returns
 * from the run) method.
 *
 * The run() method is pure virtual, which means this base class must be
 * inherited from and the run method implemented before the it can be instantiated
 * and the thread created.
 *
 * The task thread will be created by default as a detached thread using the
 * SCHED_FIFO scheduling scheme. Its priority will default to the minimum priority
 * and will have a small stack size of size PTHREAD_STACK_MIN.
 *
 * The inherited task can be as simple as the following:
 *
 * @code
 * class ATask : public Task
 * {
 * public:
 *    ATask();
 *
 *    virtual ~ATask(){};
 *
 *   int count;
 *
 * protected:
 *       virtual int run();
 * };
 *
 * @endcode
 *
 * With a simple implementation
 *
 * @code
 *
 * ATask::ATask():Task(0, Task::SMALL_STACK)
 * {
 *    count = 0;
 * }
 *
 * int ATask::run()
 * {
 *   while(count)
 *   {
 *       count++;
 *       Task::sleep( 500 );
 *   }
 *   return count;
 * }
 *
 * To use the task simple instantiate it and run it. For example:
 *
 * ATask *task = new ATask();
 * task->run();
 *
 * @endcode
 *
 *
 */
class TaskList ;

class Task:  public Loggable
{
public:

    /**
     * Enumerated value used to select a sensible stack size for the task
     */
    enum StackSize
    {
#ifdef OFF_TARGET
        SMALL_STACK = 4,    //!< Default small stack
        MEDIUM_STACK = 4,   //!< Medium sized stack
        LARGE_STACK = 4,    //!< Large stack
#else
        SMALL_STACK = 1,    //!< Default small stack
        MEDIUM_STACK = 2,   //!< Medium sized stack
        LARGE_STACK = 4,    //!< Large stack
#endif
        DEFAULT_STACK = SMALL_STACK,
    };

    enum PriorityDefaults
    {
    	PRIORITY_MIN = 1,
    	PRIORITY_LOW = 30,
    	PRIORITY_DEFAULT = 40,
    	PRIORITY_MEDIUM = 50,
    	PRIORITY_HIGH = 80,
    	PRIORITY_MAX = 98,
    };

	/**
	 * Method called to start run the tasks run() method.
	 */
	int start();

	/**
	 * Method used to cancel the running task, the calling thread will
	 * block until the task cancellation is complete.
	 */
	int stop();

    /**
     * Method return true, if the task is running.
     */
    bool isRunning();

    /**
     * Method used to return the exit value when (and if) the
     * tasks main thread exits.
     * @return 0 if task is running (@see isRunning() ), otherwise the
     * value returned when the run() method terminates.
     */
    int getExitValue();

    /**
     * Yield execution context of the current thread. This is a static
     * and may be used anywhere.
     */
    static void yield();

    /**
     * Sleep current thread for a specified time period.
     * @param timeout to sleep for in milliseconds.
     */
    static void msSleep(int timeout);

    /**
     * Method used to return the stack size in use by this task in bytes
     * @return stack size in bytes.
     */
    int getStackSize();

    /**
     * Method used to return the priority of this task
     * @return the tasks priority
     */
    int getPriority();

    /**
     * Method used to return the name of the service.
     * @return
     */
    const char* getName() const;

    /**
     * Method used to return the name of the sub-unit Id.
     * @return
     */
    const char* getSubUnitId() const;

    /**
     * Method returns the POSIC thread ID of the running task
     * @return
     */
    pthread_t getId();

    /**
     * Get the process ID of the process parent that created this task thread.
     * @return parent process ID.
     */
    pid_t getParentPID();

    /**
     * Get the thread process ID. (This is not the POSIC thread ID).
     * @return thread process ID.
     */
    pid_t getThreadID();


    /**
     * Method defined by the Loggable interface must be implemented by all
     * object to force the display of the objects current status.
     */
    virtual void show();

    /**
     * Method used to return the tasks run forever indicator.
     * @return true if task should always be running, false if transitory task.
     */
    bool isRunForever();

    /**
     * Method used to determine if the task thread was cancelled rather than
     * exiting from its run method normally.
     *
     * @return true is cancelled, otherwise false.
     */
    bool wasCancelled();


protected:

    friend class TaskEntry;

    /**
     * Base task constructor used to create a context within which a task
     * can execute. Creating the instance does not run the task only prepares
     * it for execution. This constructor is protected as it must be inherited from
     * in order to be instantiated.
     *
     * @param priority set the tasks thread priority from 1 to 99, typical pthread
     * user space priority.
     * @param stacksize used to selec small, medium or large stack for the thread.
     * @param name pointer to the name of the running task
     * @param suName sub-system name that identifies the group this task belongs to.
     */
    Task(int priority = PRIORITY_DEFAULT, StackSize stacksize = DEFAULT_STACK,
            const char* name="Unnamed Task",
            const char* suName="TK");

    /**
     * Destructor can only be called by the exit function so that the task
     * remains in context throughout the lifetime of the thread.
     */
    virtual ~Task();

    /**
     * Method used to stop the task execution, only called when the run method
     * has completed.
     */
    void exit();

    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() = 0;

    /**
     * An internal method used to set the running state.
     * @param running
     */
    void setRunning(bool running );

    /**
     * This method must be called at least once every five seconds.
     *
     * @note If your task run loop updates slower than once every 5 seconds
     * you must loop more quickly and use a count satisfy your task internal
     * timing requirements
     */
    void kickSoftwareWatchdog();


    /**
     * This method is used by the TaskList to check for stuck tasks.
     *
     * @return internal software watchdog kick count.
     */
    int getKickCount();


    /**
     * Method called as part of the task cancellation feature.
     */
    virtual void cleanup();

    /**
     * This flag is set during task construction. It is used to indicate that
     * this is a service task, or a task that is intended to execute throughout
     * the lifetime of the application.
     *
     * @note if this flag is set, the task will be included in the software
     * watch dog monitor checks to ensure that is continues to run.
     *
     */
    bool mRunForever;

private:

    /**
     * An internal static method that provides the POSIX thread entry point
     * for the running thread. It is passed to the thread by the start method
     * with a pointer to the task object, it im turn calls the tasks run
     * method.
     * @param task a pointer to the underlying
     */
    static void *startThread(void *task);

    /**
     * Tasks thread cancellation point, used to tidy up the tasks internals
     * by called the tasks cancel function.
     *
     * @param task
     */
    static void cancelThread( void *task);

    /**
     * Method called by the static startThread() method.
     * It is used to run the main process of the task and then
     * calls exit to top the thread and tidy up.
     */
    void execute();

    /**
     * Method called from the cancelThread static method to tidy up the thread
     * specific data stored in the task before calling the virtual method implementation
     * cleanup() method.
     */
    void cancel();

private:
    /**
     * Enumerated stack size, SMALL, MEDIUM and LARGE
     */
    StackSize mStackSize;

    /**
     * Calculated stack size in bytes
     */
    int mStack;

    /**
     * Task thread priority
     */
    int mPriority;

    // These name strings are used for Loggable logging
    const std::string mTaskName;   //! task Name
    const std::string mSubUnitIdName; //! subunit Id Name


    /**
     * Thread identidier for the running task
     */
    pthread_t mThread;

    /**
     * Flag indicates the tasks run method has been called.
     */
    bool mRunning;

    /**
     * Flag set when the tasks thread was cancelled, as opposed to exiting normally
     * from its run method.
     */
    bool mCancelled;

    /**
     * Used to store the tasks process run exit value.
     */
    int mRunExitValue;

    /**
     * The process ID of the parent process that started the thread.
     */
    pid_t   mParentPid;

    /**
     * The thread process ID.
     */
    pid_t   mThreadID;

    /**
     * Our software watch dog count, gets incremented by a call to
     * kickSoftwareWatchdog().
     */
    int mKickCount;

    /**
     * Keep a copy of the TaskList shared pointer. This ensures that while at least one task is created then the TaskList
     * can't go out of scope and get deleted (which causes a seg fault because we need to use the TaskList to remove each
     * Task from the list)
     */
    const std::shared_ptr<TaskList>	mTaskListRef ;

};


/**
 * Class used in the task list to maintain an entry that contains a reference
 * to the Task object that runs the thread and internal house keeping data
 */
class TaskEntry
{
public:
    /**
     * Constructor for task entry, takes a reference to the task and stores it.
     * @param task
     */
    explicit TaskEntry( Task *task );

    /**
     * Destructor
     */
    ~TaskEntry();

    /**
     * Return the pointer to the task
     * @return
     */
    Task* getTask();
    /**
     * Method used to check the software kick count has incremented. If a task
     * fails to increment its internal kick counter it implies it may be stuck
     * in a tight loop, probably through a programming error, the task is
     * terminated and the system is shutdown and reboot. If it has changed, the
     * new value is stored in mLastKickCount.
     * @return true if count has changed, false if task failed to update it
     */
    bool checkKickCount();
protected:
    Task* mTask;
    int mLastKickCount;
};


class TaskList: public Loggable
{
public:

	/**
	 * Get the task list singleton
	 */
	static std::shared_ptr<TaskList> getInstance() ;

    /**
     * Should never get called unless the system is shutting down
     */
    virtual ~TaskList();

    /**
     * Add a task to the task list
     * @param
     */
    void add( Task* );

    /**
     * Remove a task from the task list.
     * @param
     */
    void remove( Task* );

    /**
     * Show to stream for TIF interface use.
     * @param os
     */
    void show(std::ostream& os);

    /**
     * List the names of all tasks in the list
     */
    void showNames();

    /**
     * Ask each task in the task list to display its current status
     * through its show() method.
     */
    virtual void show();

    /**
     * Check that all tasks in the task list are running and have
     * active threads.
     * @return true if all OK, false if any task has died.
     */
    bool allRunning( const char** failedName);

    /**
     * This method will check the task list for tasks that maybe stuck in a tight
     * loop and not updating their software watch dog by calling
     * Task::kickSoftwareWatchdog(). A pointer to the stuck task is returned
     * to be processed by the caller.
     * @return a pointer to the stuck task, or 0 if none found.
     */
    Task* checkStuckTask();


protected:

    /**
     * Task list constructor
     */
    TaskList();

    typedef std::vector< std::shared_ptr<TaskEntry> >::iterator TaskIterator ;

    /**
     * @note: Standard copy constructors defined but not implemented as a TaskList
     * cannot be copied.
     */
    TaskList& operator=(const TaskList&);

    std::vector< std::shared_ptr<TaskEntry> > mTaskList;

    Mutex mTaskListMutex;

};

} /* namespace Mplane */


#endif /* AA_COMMON_TASK_H_ */
