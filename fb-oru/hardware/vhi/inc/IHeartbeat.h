/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IHeartbeat.h
 * \brief     Virtual interface to heartbeat monitor
 *
 *
 * \details   The heartbeat monitor, once started, will time down for the timeout period and will
 * 				perform some application-specific action on timeout. However, if the resetTimer()
 * 				method is called then the timer restarts. Continually calling the resetTimer() method
 * 				before the timeout period will ensure the monitor never times out
 *
 */


#ifndef IHEARTBEAT_H_
#define IHEARTBEAT_H_

#include <memory>

namespace Mplane {

class IHeartbeat {
public:
	IHeartbeat() {}
	virtual ~IHeartbeat() {}

	/**
	 * Get singleton
	 */
	static std::shared_ptr<IHeartbeat> getInstance() ;

	/**
	 * Get the timeout period in seconds
	 */
	virtual unsigned getTimeoutSecs() const =0 ;

	/**
	 * Set the timeout period in seconds
	 */
	virtual void setTimeoutSecs(unsigned timeout) =0 ;

	/**
	 * Get the heartbeat monitor enable state
	 */
	virtual bool getEnable() const =0 ;

	/**
	 * Enable/disable the monitor
	 */
	virtual void setEnable(bool enable) =0 ;

	/**
	 * "Ping" the monitor to ensure it doesn't time out
	 */
	virtual void resetTimer() =0 ;

	/**
	 * Has the heartbeat timer timed out
	 * @return true if timed out
	 */
	virtual bool isExpired() const =0 ;

} ;

}

#endif /* IHEARTBEAT_H_ */
