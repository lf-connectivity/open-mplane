/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestMemMon.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTMEMMON_H_
#define TESTMEMMON_H_

#include "IMemMon.h"

namespace Mplane {

class TestMemMon : public virtual IMemMon {
public:
	TestMemMon() {}
	virtual ~TestMemMon() {}

	// IMemMon Interface

	/**
	 * Set a logging function. This function is called if logging is enabled (in addition to the normal logging
	 * @param func
	 * @return
	 */
	virtual bool setLogFunction(const LogFunction& func) override {return true;}

	/**
	 * Set the rate of updates (in seconds)
	 * @param rate
	 * @return
	 */
	virtual bool setUpdateRate(unsigned rate) override {return true;}

	/**
	 * Enable/disable logging
	 * @param enable
	 * @return
	 */
	virtual bool setLogging(bool enable) override {return true;}

	/**
	 * Set rate of logging - either at every update interval or just when value changes
	 * @param logRate
	 * @return
	 */
	virtual bool setLogRate(IMemMon::LogRate logRate) override {return true;}

	/**
	 * Set a threshold (in kB) which causes a log message when the memory usage goes through the threshold
	 * @param threshold
	 * @return
	 */
	virtual bool setThreshold(long int threshold) override {return true;}

	/**
	 * Get the update rate (seconds)
	 */
	virtual unsigned getUpdateRate() const override {return 1;}

	/**
	 * Get logging enable
	 */
	virtual bool getLogging() const override {return false;}

	/**
	 * Get the logging rate
	 */
	virtual IMemMon::LogRate getLogRate() const override {return IMemMon::PERIODIC;}

	/**
	 * Get threshold (in kB)
	 */
	virtual long int getThreshold() const override {return 0;}

	/**
	 * Get the memory usage (in kB) at the last update
	 */
	virtual long int getLastMemUsage() const override {return 0;}

	/**
	 * Get the memory usage (in kB) now
	 */
	virtual long int getCurrentMemUsage() const override {return 0;}


} ;

}

#endif /* TESTMEMMON_H_ */
