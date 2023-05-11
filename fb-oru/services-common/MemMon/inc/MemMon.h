/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMon.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef MEMMON_H_
#define MEMMON_H_

#include "IMemMon.h"
#include "Service.h"
#include "Mutex.h"

namespace Mplane {

class MemMon : public virtual IMemMon, public Service {
public:
	MemMon() ;
	virtual ~MemMon() ;


	// IMemMon Interface

	/**
	 * Set a logging function. This function is called if logging is enabled (in addition to the normal logging
	 * @param func
	 * @return
	 */
	virtual bool setLogFunction(const LogFunction& func) override ;

	/**
	 * Set the rate of updates (in seconds)
	 * @param rate
	 * @return
	 */
	virtual bool setUpdateRate(unsigned rate) override ;

	/**
	 * Enable/disable logging
	 * @param enable
	 * @return
	 */
	virtual bool setLogging(bool enable) override ;

	/**
	 * Set rate of logging - either at every update interval or just when value changes
	 * @param logRate
	 * @return
	 */
	virtual bool setLogRate(IMemMon::LogRate logRate) override ;

	/**
	 * Set a threshold (in kB) which causes a log message when the memory usage goes through the threshold
	 * @param threshold
	 * @return
	 */
	virtual bool setThreshold(long int threshold) override ;

	/**
	 * Get the update rate (seconds)
	 */
	virtual unsigned getUpdateRate() const override ;

	/**
	 * Get logging enable
	 */
	virtual bool getLogging() const override ;

	/**
	 * Get the logging rate
	 */
	virtual IMemMon::LogRate getLogRate() const override ;

	/**
	 * Get threshold (in kB)
	 */
	virtual long int getThreshold() const override ;

	/**
	 * Get the memory usage (in kB) at the last update
	 */
	virtual long int getLastMemUsage() const override ;

	/**
	 * Get the memory usage (in kB) now
	 */
	virtual long int getCurrentMemUsage() const override ;


protected:
    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * my the service, is implemented by this method.
     *
     * @note The service method will continue to be called for as long as is
     * returns zero, non-zero indicates and execution error in the service
     * that will result in it being shutdown and the error made available to the
     * Task exit value.
     *
     * @return 0 when running normally, any other value is a error condition
     */
    virtual int service() override ;

private:
	mutable Mutex mMutex ;
	IMemMon::LogFunction mLogFunc ;
	unsigned mUpdateRate ;
	bool mLogging ;
	IMemMon::LogRate mLogRate ;
	long int mThreshold ;

	unsigned mUpdateTick ;
	long int mLastMemUsage ;
	bool mLastOverThreshold ;
} ;

}

#endif /* MEMMON_H_ */
