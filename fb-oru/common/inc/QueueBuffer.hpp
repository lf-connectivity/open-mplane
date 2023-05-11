/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QueueBuffer.h
 * \brief     Task-based buffer
 *
 *
 * \details   This class implements a queue which is quick to add elements to, and a task is continuously run which calls a
 * 				callback function to empty the queue. This detaches a fast/bursty source from a slower sink (for example the data
 * 				may end up being written to a log or sent over a network)
 *
 */


#ifndef QUEUEBUFFER_H_
#define QUEUEBUFFER_H_

#include <string>
#include <queue>
#include <functional>

#include "Task.h"
#include "Mutex.h"
#include "Conditional.h"

namespace Mplane {

template<typename T>
class QueueBuffer : public Task
{
public:
	template <typename U>
	using QueueCallback = std::function<void(const U&)> ;

	/**
	 * Create the buffer with a callback for emptying the queue
	 * @param callback
	 */
	QueueBuffer(QueueCallback<T> callback, unsigned priority = 50) :
		Task(priority, Task::SMALL_STACK, "QueueBuffer", "TA"),
		mTaskRun(true),
		mTaskRunning(false),
		mCallback(callback),
		mDataReady(),
		mMutex(),
		mQueue()
	{
		start() ;
	}

	/**
	 * Create the buffer with a callback for emptying the queue
	 * @param callback
	 */
	QueueBuffer(const std::string& name, const std::string& group, QueueCallback<T> callback, unsigned priority = 50) :
		Task(priority, Task::SMALL_STACK, name.c_str(), group.c_str()),
		mTaskRun(true),
		mTaskRunning(false),
		mCallback(callback),
		mDataReady(),
		mMutex(),
		mQueue()
	{
		start() ;
	}

	/**
	 * Destructor
	 */
	~QueueBuffer()
	{
		if (!mTaskRunning)
			return ;

		mTaskRun = false ;
		{
		Conditional::Lock condLock(mDataReady) ;
		mDataReady.signal() ;
		}
		msSleep(2) ;
	}

	/**
	 * Add an entry to the queue
	 * @param entry
	 */
	void add(const T& entry)
	{
		{
			Mutex::Lock lock(mMutex) ;
			mQueue.push(entry) ;
		}

		Conditional::Lock condLock(mDataReady) ;
		mDataReady.signal() ;
	}

protected:
	int run() override
	{
		mTaskRunning = true ;

	    /*
	     * Now our thread is running we just enter an infinite loop so we never end.
	     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
	     */
	    while (mTaskRun)
	    {
	    	// wait for messages to become available
	    	mDataReady.wait() ;

			// check for task stop
			if (!mTaskRun)
				break ;

			// process all messages
			bool dataReady(false) ;
			{
				Mutex::Lock lock(mMutex) ;
				dataReady = !mQueue.empty() ;
			}

			while (dataReady && mTaskRun)
			{
				// get data
				T entry ;
				{
					Mutex::Lock lock(mMutex) ;
					entry = mQueue.front() ;
				}

				// Send
				mCallback(entry) ;

				// finished with data
				{
					Mutex::Lock lock(mMutex) ;
					mQueue.pop() ;
					dataReady = !mQueue.empty() ;
				}

			} // while still got messages
	    }

		mTaskRunning = false ;
	    return 0;
	}


private:
	bool mTaskRun ;
	bool mTaskRunning ;
	QueueCallback<T> mCallback ;
	Conditional mDataReady ;
	Mutex mMutex ;
	std::queue<T> mQueue ;
} ;

}

#endif /* QUEUEBUFFER_H_ */
