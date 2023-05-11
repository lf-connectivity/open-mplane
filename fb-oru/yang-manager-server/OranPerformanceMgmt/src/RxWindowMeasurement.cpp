/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxWindowMeasurement.cpp
 * \brief     Class to configure and measure for Rx window parameters
 *
 *
 * \details   Class to configure and measure for Rx window parameters
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxWindowMeasurement.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "math.h"

#include "stringfunc.hpp"
#include "YangUtils.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxWindowMeasurement::RxWindowMeasurement(IPerformanceMgmt::RxWindowMeasType_T type)
{
	mMeasType = type;
	mActive = false;
	mReset = false;
	mObjUnitId = IPerformanceMgmt::RxWindowObjectUnitId_T::PER_RU;
}

//-------------------------------------------------------------------------------------------------------------
void RxWindowMeasurement::activateDeactivate(bool activate)
{
	std::lock_guard<std::mutex> guard(mMutex);

	if (mActive != activate)
	{
		mActive = activate;
		mReset = activate;

		// Clear recorded data
		mDataFromActive = 0;
		mDataFromReset = 0;

		uint64_t liveVal = 0;
		// TODO Read live value of the counter from the FPGA

		// Write the live values into previous data
		mDataFromActive = liveVal;
		mDataFromReset = liveVal;

		if (mReset)
		{
			// Record the start time of the measurement and convert to YANG format of date-and-time
			time_t currTime = time(NULL);
			mMeasurementStartTime = YangUtils::getDateTime(currTime);
		}

	}
}

//-------------------------------------------------------------------------------------------------------------
void RxWindowMeasurement::setObjectUnitId(IPerformanceMgmt::RxWindowObjectUnitId_T id)
{
	if (mActive == false)
	{
		mObjUnitId = id;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool RxWindowMeasurement::isActive(void)
{
	return mActive;
}

//-------------------------------------------------------------------------------------------------------------
bool RxWindowMeasurement::getStatsFromActive(uint64_t& data)
{
	// No results are returned if measurement is not active
	// or if not a single measurement has been done since activating the type
	if (!mActive)
	{
		return false;
	}

	std::lock_guard<std::mutex> guard(mMutex);

	uint64_t liveVal = 0;
	// TODO Read live value of the counter from the FPGA

	// Write the difference between the previous value and the live count into the return value
	data = liveVal - mDataFromActive;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool RxWindowMeasurement::getStatsFromReset(uint64_t& data, std::string& startTime, bool reset)
{
	// No results are returned if measurement is not active
	// or if not a single measurement has been done since resetting the measurement
	if (!mActive)
	{
		return false;
	}

	std::lock_guard<std::mutex> guard(mMutex);

	uint64_t liveVal = 0;
	// TODO Read live value of the counter from the FPGA

    // Write the difference between the previous value and the live count into the return value
	data = liveVal - mDataFromReset;

	startTime = mMeasurementStartTime;

	mReset = reset;

	if (reset)
	{
		// Record the start time of the measurement and convert to YANG format of date-and-time
		time_t currTime = time(NULL);
		mMeasurementStartTime = YangUtils::getDateTime(currTime);

		// Record the current live value as the last value for the next measurement interval
		mDataFromReset = liveVal;
	}

	return true;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================


//=============================================================================================================
// PRIVATE
//=============================================================================================================
