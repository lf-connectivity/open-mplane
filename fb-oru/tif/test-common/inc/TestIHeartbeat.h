/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIHeartbeat.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTIHEARTBEAT_H_
#define TESTIHEARTBEAT_H_

#include "IHeartbeat.h"

namespace Mplane {

class TestIHeartbeat : public virtual IHeartbeat {
public:
	TestIHeartbeat() {}
	virtual ~TestIHeartbeat() {}

	/**
	 * Get the timeout period in seconds
	 */
	virtual unsigned getTimeoutSecs() const override { return 30; }

	/**
	 * Set the timeout period in seconds
	 */
	virtual void setTimeoutSecs(unsigned timeout) override {}

	/**
	 * Get the heartbeat monitor enable state
	 */
	virtual bool getEnable() const override { return true; }

	/**
	 * Enable/disable the monitor
	 */
	virtual void setEnable(bool enable) override {}

	/**
	 * "Ping" the monitor to ensure it doesn't time out
	 */
	virtual void resetTimer() override {}

	/**
	 * Has the heartbeat timer timed out
	 * @return true if timed out
	 */
	virtual bool isExpired() const override {return false ; }

} ;

}

#endif /* TESTIHEARTBEAT_H_ */
