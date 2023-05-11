/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Benchmark.h
 * \brief     Benchmark timing
 *
 *
 * \details   Provides benchmark timing functions for debug and profiling
 *
 */


#ifndef BENCHMARK_H_
#define BENCHMARK_H_
#include <time.h>

#include <map>
#include <string>
#include <memory>
#include "Mutex.h"

namespace Mplane {

class Benchmark {
public:

	/**
	 * Get the singleton object
	 * @return
	 */
	static std::shared_ptr<Benchmark> getInstance(void) ;

	virtual ~Benchmark() ;

	/**
	 * Start a timer with a given name - creating the timer if necessary
	 * @param name
	 */
	void start(const std::string& name) ;

	/**
	 * Return a string containing the difference between now and the start point
	 * @param name
	 * @return string with delta time
	 */
	std::string elapsed(const std::string& name) ;

	/**
	 * Return the difference between now and the start point
	 * @param name
	 * @return delta time as a float in secs
	 */
	float elapsedTime(const std::string& name) ;

	/**
	 * Stop and delete the timer with the specified name and return a string containing the difference between now and the start point
	 * @param name
	 * @return string with delta time
	 */
	std::string stop(const std::string& name) ;

	/**
	 * Get the current time (in hi res)
	 * @return formatted string of timestamp
	 */
	std::string timestamp(void) const ;

	/**
	 * Get the current up time
	 * @return current up time in seconds
	 */
	long upTime(void) const ;

	/**
	 * Return a date/time timestamp string of the form "YYYYMMDDHHmmss"
	 */
	static std::string datetimeStr() ;


private:
	Benchmark() ;

private:
	Mutex mMutex ;
	std::map<std::string, timespec> mTimers ;
} ;

}

#endif /* BENCHMARK_H_ */
