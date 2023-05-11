/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMemMon.h
 * \brief     A memory monitor
 *
 *
 * \details
 *
 */


#ifndef IMEMMON_H_
#define IMEMMON_H_

#include <memory>
#include <functional>

namespace Mplane {

class IMemMon {
public:
	IMemMon() {}
	virtual ~IMemMon() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IMemMon> getInstance() ;

	// Rate of logging
	enum LogRate {
		PERIODIC =0,
		ONCHANGE =1,
	};

	using LogFunction = std::function<void(const std::string& msg)> ;


	/**
	 * Set a logging function. This function is called if logging is enabled (in addition to the normal logging
	 * @param func
	 * @return
	 */
	virtual bool setLogFunction(const LogFunction& func) =0 ;

	/**
	 * Set the rate of updates (in seconds)
	 * @param rate
	 * @return
	 */
	virtual bool setUpdateRate(unsigned rate) =0 ;

	/**
	 * Enable/disable logging
	 * @param enable
	 * @return
	 */
	virtual bool setLogging(bool enable) =0 ;

	/**
	 * Set rate of logging - either at every update interval or just when value changes
	 * @param logRate
	 * @return
	 */
	virtual bool setLogRate(LogRate logRate) =0 ;

	/**
	 * Set a threshold (in kB) which causes a log message when the memory usage goes through the threshold
	 * @param threshold
	 * @return
	 */
	virtual bool setThreshold(long int threshold) =0 ;

	/**
	 * Get the update rate (seconds)
	 */
	virtual unsigned getUpdateRate() const =0 ;

	/**
	 * Get logging enable
	 */
	virtual bool getLogging() const =0 ;

	/**
	 * Get the logging rate
	 */
	virtual LogRate getLogRate() const =0 ;

	/**
	 * Get threshold (in kB)
	 */
	virtual long int getThreshold() const =0 ;

	/**
	 * Get the memory usage (in kB) at the last update
	 */
	virtual long int getLastMemUsage() const =0 ;

	/**
	 * Get the memory usage (in kB) now
	 */
	virtual long int getCurrentMemUsage() const =0 ;
} ;

}

#endif /* IMEMMON_H_ */
