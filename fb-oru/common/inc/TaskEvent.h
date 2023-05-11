/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TaskEvent.h
 * \brief     Task which operates as a result of some event
 *
 *
 * \details   A task which blocks until an event condition occurs, at which point it then calls the derivede object's
 * 			 runEvent() method. Ensures the task is exited on destruction (which calls shutdown() method)
 *
 */


#ifndef TASKEVENT_H_
#define TASKEVENT_H_

#include "Task.h"
#include "Mutex.h"
#include "Conditional.h"

namespace Mplane {

class TaskEvent : public Task
{
public:
	TaskEvent(int priority = 0, StackSize stacksize = SMALL_STACK,
            const std::string& name="Unnamed Task",
            const std::string& suName="TKEV") ;
	virtual ~TaskEvent() ;

	/**
	 * Shutdown any running process
	 */
	virtual void shutdown() ;

	/**
	 * Event has occurred - trigger the task to run
	 */
	virtual void event() ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() =0 ;

protected:
    /**
     * This is the Task method that is run by the start() method.
     *
     * \return the exit status of task process
     */
    virtual int run() override ;

protected:
    bool mTaskRun ;
    bool mTaskRunning ;
    Conditional mEvent ;
} ;

}

#endif /* TASKEVENT_H_ */
