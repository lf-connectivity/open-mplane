/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Benchmark.cpp
 * \brief     Benchmark timing
 *
 *
 * \details   Provides benchmark timing functions for debug and profiling
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/sysinfo.h>
#include <stdio.h>
#include <ctime>

#include "Benchmark.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string Benchmark::datetimeStr()
{
	time_t rawtime;
	time (&rawtime);

	struct tm * timeinfo(localtime (&rawtime));

	char buffer [32];
	strftime (buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);

	return std::string(buffer) ;
}

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<Benchmark> Benchmark::getInstance(void)
{
	static std::shared_ptr<Benchmark> singleton(new Benchmark()) ;
	return singleton ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Benchmark::~Benchmark()
{
}

//-------------------------------------------------------------------------------------------------------------
void Benchmark::start(const std::string& name)
{
	Mutex::Lock lock(mMutex) ;

	if (mTimers.find(name) == mTimers.end())
		mTimers[name] = timespec() ;

	clock_gettime(CLOCK_REALTIME, &mTimers[name]) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::Benchmark::elapsed(const std::string& name)
{
	Mutex::Lock lock(mMutex) ;

	if (mTimers.find(name) == mTimers.end())
		return "ERROR: Timer not started" ;

	timespec tEnd ;
	clock_gettime(CLOCK_REALTIME, &tEnd) ;

	// get diff
	timespec tDiff ;
	tDiff.tv_nsec = tEnd.tv_nsec - mTimers[name].tv_nsec ;
	tDiff.tv_sec  = tEnd.tv_sec  - mTimers[name].tv_sec ;
	if (tDiff.tv_nsec < 0L)
	{
		tDiff.tv_sec--;
		tDiff.tv_nsec += 1000000000L ;
	}

	// Convert to string
	char timer_buff[128];
    unsigned us = (unsigned)(tDiff.tv_nsec / 1000L) ;
	snprintf(timer_buff, sizeof(timer_buff), "%d.%06u", (int)tDiff.tv_sec, us) ;

	std::string elapsedStr(timer_buff) ;
	return elapsedStr ;
}


//-------------------------------------------------------------------------------------------------------------
std::string Benchmark::stop(const std::string& name)
{
	std::string elapsedStr(elapsed(name)) ;

	Mutex::Lock lock(mMutex) ;

	std::map<std::string, timespec>::iterator iter( mTimers.find(name) ) ;
	if (iter == mTimers.end())
		return elapsedStr ;

	mTimers.erase(iter) ;
	return elapsedStr ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::Benchmark::timestamp(void) const
{
	timespec tNow ;
	clock_gettime(CLOCK_REALTIME, &tNow) ;

	// Convert to string
    unsigned us = (unsigned)(tNow.tv_nsec / 1000L) ;

	struct tm result ;
	struct tm  *ts = localtime_r(&tNow.tv_sec, &result);

	char buff[80];
	std::strftime(buff, sizeof(buff), "%H:%M:%S", ts);

	char timer_buff[128];
	snprintf(timer_buff, sizeof(timer_buff), "%s.%06u", buff, us) ;


	std::string timestamp(timer_buff) ;
	return timestamp ;
}

//-------------------------------------------------------------------------------------------------------------
float Benchmark::elapsedTime(const std::string& name)
{
	Mutex::Lock lock(mMutex) ;

	if (mTimers.find(name) == mTimers.end())
		return 0.0 ;

	timespec tEnd ;
	clock_gettime(CLOCK_REALTIME, &tEnd) ;

	// get diff
	timespec tDiff ;
	tDiff.tv_nsec = tEnd.tv_nsec - mTimers[name].tv_nsec ;
	tDiff.tv_sec  = tEnd.tv_sec  - mTimers[name].tv_sec ;
	if (tDiff.tv_nsec < 0L)
	{
		tDiff.tv_sec--;
		tDiff.tv_nsec += 1000000000L ;
	}

	// Convert to float
    unsigned us = (unsigned)(tDiff.tv_nsec / 1000L) ;
    float elapsedSecs = static_cast<float>(tDiff.tv_sec) + (static_cast<float>(us) / 1000000.0) ;
	return elapsedSecs ;
}

//-------------------------------------------------------------------------------------------------------------
long Benchmark::upTime(void) const
{
	struct sysinfo info;
	sysinfo(&info);
	return info.uptime;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Benchmark::Benchmark() :
	mMutex()
{
}
