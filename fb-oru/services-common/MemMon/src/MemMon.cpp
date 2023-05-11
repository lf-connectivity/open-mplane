/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MemMon.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IBootTimer.h"
#include "Process.h"
#include "MemMon.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned TICK_RATE_MS{1000} ;
const unsigned UPDATE_RATE_SECS{15} ;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IMemMon> IMemMon::getInstance()
{
	static std::shared_ptr<IMemMon> instance(std::make_shared<MemMon>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
MemMon::MemMon() :
	Service( Service::SERVICE_MEDIUM_PRIORITY,
    	     Service::SMALL_STACK,
    	     TICK_RATE_MS,
    	     "MemMon",
    	     "MON"),

 	mMutex(),
 	mLogFunc(),
	mUpdateRate(UPDATE_RATE_SECS),
	mLogging(true),
	mLogRate(IMemMon::PERIODIC),
	mThreshold(0),

	mUpdateTick(0),
	mLastMemUsage(0),
	mLastOverThreshold(true)

{
}

//-------------------------------------------------------------------------------------------------------------
MemMon::~MemMon()
{
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::setLogFunction(const LogFunction& func)
{
	Mutex::Lock lock(mMutex) ;
	mLogFunc = func ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::setUpdateRate(unsigned rate)
{
	Mutex::Lock lock(mMutex) ;
	mUpdateRate = rate ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::setThreshold(long int threshold)
{
	Mutex::Lock lock(mMutex) ;
	mThreshold = threshold ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::setLogging(bool enable)
{
	Mutex::Lock lock(mMutex) ;
	mLogging = enable ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::setLogRate(IMemMon::LogRate logRate)
{
	Mutex::Lock lock(mMutex) ;
	mLogRate = logRate ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned MemMon::getUpdateRate() const
{
	Mutex::Lock lock(mMutex) ;
	return mUpdateRate ;
}

//-------------------------------------------------------------------------------------------------------------
bool MemMon::getLogging() const
{
	Mutex::Lock lock(mMutex) ;
	return mLogging ;
}

//-------------------------------------------------------------------------------------------------------------
IMemMon::LogRate MemMon::getLogRate() const
{
	Mutex::Lock lock(mMutex) ;
	return mLogRate ;
}

//-------------------------------------------------------------------------------------------------------------
long int MemMon::getThreshold() const
{
	Mutex::Lock lock(mMutex) ;
	return mThreshold ;
}

//-------------------------------------------------------------------------------------------------------------
long int MemMon::getLastMemUsage() const
{
	Mutex::Lock lock(mMutex) ;
	return mLastMemUsage ;
}

//-------------------------------------------------------------------------------------------------------------
long int MemMon::getCurrentMemUsage() const
{
	return Process::getResidentSetSize() ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int MemMon::service()
{
	Mutex::Lock lock(mMutex) ;
	if (++mUpdateTick < mUpdateRate)
		return 0 ;

	// Time to do an update
	mUpdateTick=0 ;

	// get latest usage
	long int currentMemUsage( Process::getResidentSetSize() ) ;
	bool currentOverThreshold( currentMemUsage > mThreshold ) ;

	// Set flags
	// cppcheck-suppress variableScope
	bool usageChange(currentMemUsage != mLastMemUsage) ;
	bool thresholdChange(currentOverThreshold != mLastOverThreshold) ;

	// Keep track
	mLastMemUsage = currentMemUsage ;
	mLastOverThreshold = currentOverThreshold ;

	// Log threshold changes always
	if (thresholdChange)
	{
		if (currentOverThreshold)
			eventWarning("Memory usage %ld kB has exceeded threshold (%ld kB)", currentMemUsage, mThreshold) ;
		else
			eventInfo("Memory usage %ld kB is now below threshold (%ld kB)", currentMemUsage, mThreshold) ;
	}

	// Do logging as necessary
	if (mLogging)
	{
		if (usageChange || (mLogRate == IMemMon::PERIODIC))
		{
			// log
			eventInfo("Memory usage %ld kB", currentMemUsage) ;

			// Send to logging function if defined
			if (mLogFunc)
			{
				std::shared_ptr<IBootTimer> bootTimer(IBootTimer::getInstance()) ;
				float runtime(bootTimer->getRunTime()) ;

				// Format the message
				std::string msg(
					"runtime=" + std::to_string(runtime) + " usageKb=" + std::to_string(currentMemUsage)
				) ;

				if (thresholdChange && currentOverThreshold)
					msg += " warning=\"Memory usage exceeded threshold\"" ;

				// send
				mLogFunc(msg) ;
			}
		}
	}

	return 0 ;
}
