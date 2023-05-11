/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TransceiverMeasurement.cpp
 * \brief     Class to configure and measure for transceiver parameters
 *
 *
 * \details   Class to configure and measure for transceiver parameters
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TransceiverMeasurement.h"

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

const double TransceiverMeasurement::mSaturatedLogValue(-128.0);
const double TransceiverMeasurement::mMinValueForLog(pow(10, -128));

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::activateDeactivate(bool activate)
{
	if (mActive != activate)
	{
		mPrevActive = mActive;
		mActive = activate;
		mReset = activate;

		if (mReset)
		{
			// Record the start time of the measurement and convert to YANG format of date-and-time
			time_t currTime = time(NULL);
			mMeasurementStartTime = YangUtils::getDateTime(currTime);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::setFunction(IPerformanceMgmt::FunctionType_T function)
{
	mFunction = function;
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::setReportType(IPerformanceMgmt::TransReportInfoType_T report, bool add)
{
	if (add)
	{
		mReportType.insert(report);
	}
	else
	{
		mReportType.erase(report);
	}
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::getReportType(std::set<IPerformanceMgmt::TransReportInfoType_T>& report)
{
	report = mReportType;
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::setBinCount(uint16_t binCount)
{
	mBinCount = binCount;

	// Clear the frequency table and resize as per the bin count
	mTableFromActive.resize(mBinCount);
	std::fill(mTableFromActive.begin(), mTableFromActive.end(), 0);

	mTableFromReset.resize(mBinCount);
	std::fill(mTableFromReset.begin(), mTableFromReset.end(), 0);
}

//-------------------------------------------------------------------------------------------------------------
uint16_t TransceiverMeasurement::getBinCount(void)
{
	return mBinCount;
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::setLowerLimit(double lowerLimit)
{
	mLowerLimit = lowerLimit;
}

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::setUpperLimit(double upperLimit)
{
	mUpperLimit = upperLimit;
}

//-------------------------------------------------------------------------------------------------------------
bool TransceiverMeasurement::measure(void)
{
	double value = 0.0;

	// If measurement is not activated, return false
	if (!mActive)
	{
		return false;
	}

	// Read the measurement from SFP data as per the measurement type
	switch (mMeasType)
	{
	case IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER:
	{
		value = mSfpData->sfpRxPowerMilliW();
	}
	break;

	case IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER:
	{
		value = mSfpData->sfpTxPowerMilliW();
	}
	break;

	case IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT:
	{
		value = mSfpData->sfpTxBiasCurrent();
	}
	break;

	case IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE:
	{
		value = mSfpData->sfpSupplyVoltage();
	}
	break;

	case IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE:
	{
		value = mSfpData->sfpTemperature();
	}
	break;

	default:
		return false;
	}

	// If a transfer function is configured, then apply it
	if (mFunction == IPerformanceMgmt::FunctionType_T::FUNCTION_LOG10)
	{
		// Prevent invalid argument to log10
		// For such values, as per the M plane spec, the result should be saturated to -128
		if (value < mMinValueForLog)
		{
			value = mSaturatedLogValue;
		}
		else
		{
			value = log10(value);
		}
	}

	// Record the time of the measurement and convert to YANG format of date-and-time
	time_t currTime = time(NULL);
	std::string yangCurrDT = YangUtils::getDateTime(currTime);

	{
		std::lock_guard<std::mutex> guard(mMutex);

		// The current value is the latest value
		mLatestFromActive.first = value;
		mLatestFromActive.second = yangCurrDT;
		mLatestFromReset.first = value;
		mLatestFromReset.second = yangCurrDT;

		// Check if this is the first measurement
		if (mPrevActive != mActive)
		{
			// Save the first measurement along with the timestamp
			mFirstFromActive.first = value;
			mFirstFromActive.second = yangCurrDT;

			// Save the first measurement as the min value along with the timestamp
			mMinFromActive.first = value;
			mMinFromActive.second = yangCurrDT;

			// Save the first measurement as the max value along with the timestamp
			mMaxFromActive.first = value;
			mMaxFromActive.second = yangCurrDT;

			// Clear the frequency table and resize as per the bin count
			mTableFromActive.resize(mBinCount);
			std::fill(mTableFromActive.begin(), mTableFromActive.end(), 0);

			mPrevActive = mActive;
		}
		// This is not the first measurement
		else
		{
			// If the current value is less than the recorded min, then record new min value
			// along with the timestamp
			if (value < mMinFromActive.first)
			{
				mMinFromActive.first = value;
				mMinFromActive.second = yangCurrDT;
			}

			// If the current value is greater than the recorded max, then record new max value
			// along with the timestamp
			if (value > mMaxFromActive.first)
			{
				mMaxFromActive.first = value;
				mMaxFromActive.second = yangCurrDT;
			}
		}

		// Check if this is the first value since a new measurement interval was started
		if (mReset)
		{
			// Save the first measurement along with the timestamp
			mFirstFromReset.first = value;
			mFirstFromReset.second = yangCurrDT;

			// Save the first measurement as the min value along with the timestamp
			mMinFromReset.first = value;
			mMinFromReset.second = yangCurrDT;

			// Save the first measurement as the max value along with the timestamp
			mMaxFromReset.first = value;
			mMaxFromReset.second = yangCurrDT;

			// Clear the frequency table and resize as per the bin count
			mTableFromReset.resize(mBinCount);
			std::fill(mTableFromActive.begin(), mTableFromActive.end(), 0);
			mReset = false;
		}
		// This is not the first value in the measurement interval
		else
		{
			// If the current value is less than the recorded min, then record new min value
			// along with the timestamp
			if (value < mMinFromReset.first)
			{
				mMinFromReset.first = value;
				mMinFromReset.second = yangCurrDT;
			}

			// If the current value is greater than the recorded max, then record new max value
			// along with the timestamp
			if (value > mMaxFromReset.first)
			{
				mMaxFromReset.first = value;
				mMaxFromReset.second = yangCurrDT;
			}
		}

		// Populate the frequency tables
		populateFrequencyTable(value);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TransceiverMeasurement::isActive(void)
{
	return mActive;
}

//-------------------------------------------------------------------------------------------------------------
int TransceiverMeasurement::getPortNum(void)
{
	return mPortNum;
}

//-------------------------------------------------------------------------------------------------------------
bool TransceiverMeasurement::getStatsFromActive(std::pair<double, std::string>& min, std::pair<double, std::string>& max,
			std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
			std::vector<uint32_t>& table)
{
	// No results are returned if measurement is not active
	// or if not a single measurement has been done since activating the type
	if (!mActive || (mPrevActive != mActive))
	{
		return false;
	}

	std::lock_guard<std::mutex> guard(mMutex);

	// Return statistics
	min = mMinFromActive;
	max = mMaxFromActive;
	first = mFirstFromActive;
	latest = mLatestFromActive;
	table = mTableFromActive;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TransceiverMeasurement::getStatsFromReset(std::pair<double, std::string>& min, std::pair<double, std::string>& max,
			std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
			std::vector<uint32_t>& table, std::string& startTime, bool reset)
{
	// No results are returned if measurement is not active
	// or if not a single measurement has been done since resetting the measurement
	if (!mActive || mReset)
	{
		return false;
	}

	std::lock_guard<std::mutex> guard(mMutex);

	// Return statistics for the measurement interval
	min = mMinFromReset;
	max = mMaxFromReset;
	first = mFirstFromReset;
	latest = mLatestFromReset;
	table = mTableFromReset;
	startTime = mMeasurementStartTime;

	mReset = reset;

	if (reset)
	{
		// Record the start time of the measurement and convert to YANG format of date-and-time
		time_t currTime = time(NULL);
		mMeasurementStartTime = YangUtils::getDateTime(currTime);
	}

	return true;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TransceiverMeasurement::populateFrequencyTable(double value)
{
    // Let n = bin-count, a = lower-bound, b = upper-bound, x = f(s) where s is value of monitored parameter and f is a
	// function selected for statistics via parameter function.

	// If n = 0 then frequency table is empty and is not updated
	// If n > 0 there are n bins: hk where k = 0...n-1
	if (mBinCount == 0)
	{
		return;
	}

	// If x < a then bin h0 is incremented
	if (value < mLowerLimit)
	{
		mTableFromActive[0] += 1;
		mTableFromReset[0] += 1;
	}
	// If b ≤ x and n > 1 then bin hn-1 is incremented
	else if (value >= mUpperLimit)
	{
		if (mBinCount > 1)
		{
			mTableFromActive[mBinCount - 1] += 1;
			mTableFromReset[mBinCount - 1] += 1;
		}
	}
	else
	{
		// If a ≤ x and x < b and n > 2 then bin hk is incremented for k such that
		// k-1 ≤ (n-2) * (x-a) / (b-a) < k. 32
		if (mBinCount > 2)
		{
			int position = static_cast<int>((mBinCount - 2) * (value - mLowerLimit)/(mUpperLimit - mLowerLimit));

			mTableFromActive[position + 1] += 1;
			mTableFromReset[position + 1] += 1;
		}
	}
}
