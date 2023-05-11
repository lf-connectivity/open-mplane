/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BootTimer.cpp
 * \brief
 *
 *
 * \details	  Tracks time from boot of various points in the application.
 *			  NOTE: Object is only expected to be called once at various points in the app, and never
 *			  at the same time by more than one thread, so we don't need a mutex.
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "stringfunc.hpp"
#include "Benchmark.h"
#include "BootTimer.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static const std::string BOOT_TIMER{"  __BOOT"} ;
static const std::string BOOT_TIF_NAME{"tif"} ;
static const std::string BOOT_APP_NAME{"app"} ;

// We have a fixed (ish) delay while u-boot starts up the kernel and device tree - this is the measured value
static const float UBOOT_TIME{10.6} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IBootTimer> IBootTimer::getInstance()
{
	static std::shared_ptr<IBootTimer> instance(std::make_shared<BootTimer>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BootTimer::BootTimer() :
	mComplete(false),
	mStartTime(0.0),
	mTimers(),
	mAppCallbacks(),
	mTifCallbacks(),
	mNamedCallbacks()
{
	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	bench->start(BOOT_TIMER) ;
	mStartTime = static_cast<float>(bench->upTime()) + UBOOT_TIME ;

	mTimers[BOOT_TIF_NAME] = 0.0 ;
	mTimers[BOOT_APP_NAME] = 0.0 ;
}

//-------------------------------------------------------------------------------------------------------------
BootTimer::~BootTimer()
{
}

//-------------------------------------------------------------------------------------------------------------
void BootTimer::tifStarted()
{
	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	mTimers[BOOT_TIF_NAME] = bench->elapsedTime(BOOT_TIMER) ;

	for (auto cb : mTifCallbacks)
		cb() ;
}

//-------------------------------------------------------------------------------------------------------------
void BootTimer::appStarted()
{
	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	mTimers[BOOT_APP_NAME] = bench->elapsedTime(BOOT_TIMER) ;
//	bench->stop(BOOT_TIMER) ;
	mComplete = true ;

	for (auto cb : mAppCallbacks)
		cb() ;
}

//-------------------------------------------------------------------------------------------------------------
void BootTimer::nameComplete(const std::string& name)
{
	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	mTimers[name] = bench->elapsedTime(BOOT_TIMER) ;

	if (mNamedCallbacks.find(name) == mNamedCallbacks.end())
		return ;

	for (auto cb : mNamedCallbacks[name])
		cb(name) ;

}

//-------------------------------------------------------------------------------------------------------------
void BootTimer::show(std::ostream& os)
{
	static const unsigned NAME_WIDTH{20} ;
	static const unsigned ELAPSED_WIDTH{20} ;
	static const unsigned TIME_WIDTH{20} ;

	// Dump out the list in increasing order of time
	std::map<float, std::string> times ;
	for (auto entry : mTimers)
		times[entry.second] = entry.first ;

	os << padLeft("Name", NAME_WIDTH, ' ') << " " <<
		  padLeft("Elapsed (s)", ELAPSED_WIDTH, ' ') << " " <<
		  padLeft("Total (s)", TIME_WIDTH, ' ') << " " <<
		  std::endl ;

	os << padLeft("", NAME_WIDTH, '-') << " " <<
		  padLeft("", ELAPSED_WIDTH, '-') << " " <<
		  padLeft("", TIME_WIDTH, '-') << " " <<
		  std::endl ;

	for (auto timing : times)
	{
		std::stringstream ss1, ss2 ;
		ss1 << timing.first ;
		float totalTime(timing.first + mStartTime) ;
		ss2 << totalTime ;
//		ss2 << timing.first + mStartTime ;
		os << padLeft(timing.second, NAME_WIDTH, ' ') << " " <<
			  padLeft(ss1.str(), ELAPSED_WIDTH, ' ') << " " <<
			  padLeft(ss2.str(), TIME_WIDTH, ' ') << " " <<
			  std::endl ;
	}
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getStartTime() const
{
	return mStartTime ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getTifTime() const
{
	return mTimers.at(BOOT_TIF_NAME) + mStartTime ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getTifElapsed() const
{
	return mTimers.at(BOOT_TIF_NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getAppTime() const
{
	return mTimers.at(BOOT_APP_NAME) + mStartTime ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getAppElapsed() const
{
	return mTimers.at(BOOT_APP_NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getNameTime(const std::string& name) const
{
	auto entry(mTimers.find(name)) ;
	if (entry == mTimers.end())
		return 0.0 ;

	return mTimers.at(name) + mStartTime ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getNameElapsed(const std::string& name) const
{
	auto entry(mTimers.find(name)) ;
	if (entry == mTimers.end())
		return 0.0 ;

	return mTimers.at(name) ;
}

//-------------------------------------------------------------------------------------------------------------
float BootTimer::getRunTime() const
{
	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	float now(bench->elapsedTime(BOOT_TIMER)) ;
	return now + mStartTime  ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootTimer::registerAppCompleteCallback(AppCompleteCallback cb)
{
	mAppCallbacks.push_back(cb) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootTimer::registerTifCompleteCallback(TifCompleteCallback cb)
{
	mTifCallbacks.push_back(cb) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool BootTimer::registerNamedCompleteCallback(const std::string &name, NamedCompleteCallback cb)
{
	if (mNamedCallbacks.find(name) == mNamedCallbacks.end())
		mNamedCallbacks[name] = std::vector<NamedCompleteCallback>() ;

	mNamedCallbacks[name].push_back(cb) ;
	return true ;
}
