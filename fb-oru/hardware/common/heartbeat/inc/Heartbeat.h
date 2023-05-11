/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Heartbeat.h
 * \brief     Heartbeat monitor
 *
 *
 * \details   The heartbeat monitor, once started, will time down for the timeout period and will
 * 				perform some application-specific action on timeout. However, if the resetTimer()
 * 				method is called then the timer restarts. Continually calling the resetTimer() method
 * 				before the timeout period will ensure the monitor never times out.
 *
 * 				This version of the IHeartbeat interface raises a heartbeat fault on timeout
 *
 */


#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include "IHeartbeat.h"
#include "Mutex.h"
#include "TaskPeriodicEvent.h"

namespace Mplane {

class Heartbeat : public virtual IHeartbeat, public TaskPeriodicEvent {
public:
	virtual ~Heartbeat() ;

	/**
	 * Get the timeout period in seconds
	 */
	virtual unsigned getTimeoutSecs() const override ;

	/**
	 * Set the timeout period in seconds
	 */
	virtual void setTimeoutSecs(unsigned timeout) override ;

	/**
	 * Get the heartbeat monitor enable state
	 */
	virtual bool getEnable() const override ;

	/**
	 * Enable/disable the monitor
	 */
	virtual void setEnable(bool enable) override ;

	/**
	 * "Ping" the monitor to ensure it doesn't time out
	 */
	virtual void resetTimer() override ;

	/**
	 * Has the heartbeat timer timed out
	 * @return true if timed out
	 */
	virtual bool isExpired() const override ;


protected:
	/**
	 * Event created by heartbeat monitor - used by derived classes (to raise faults etc)
	 * Event is generated on change of timer expiration
	 * @param expired
	 */
	virtual void heartbeatEvent(bool expired) ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

protected:
	// Protect constructor for singleton pattern
	Heartbeat() ;

private:
	// Update the expiration flag (and send event if necessary)
	void updateExpiredFlag() ;

private:
	mutable Mutex mTimerMutex ;
	bool mEnabled ;
	unsigned mTimeoutSecs ;
	unsigned mTimeoutCounter ;
	bool mTimerExpired ;
} ;

}

#endif /* HEARTBEAT_H_ */
