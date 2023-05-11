/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TransceiverMeasurement.h
 * \brief     Class to configure and measure for transceiver parameters
 *
 *
 * \details   Class to configure and measure for transceiver parameters
 *
 */


#ifndef YANG_HANDLERS_INC_TRANSCEIVERMEASUREMENT_H_
#define YANG_HANDLERS_INC_PERFORMANCEMGMTSERVICE_H_

#include <memory>
#include <utility>
#include <map>
#include <vector>
#include <mutex>

#include "ISfpData.h"
#include "IPerformanceMgmt.h"

namespace Mplane {

/*!
 * \class  TransceiverMeasurement
 * \brief
 * \details
 *
 */
class TransceiverMeasurement{
public:

	explicit TransceiverMeasurement(int portNum, IPerformanceMgmt::TransceiverMeasType_T type) :
		mPortNum(portNum),
		mActive(false),
		mPrevActive(false),
		mReset(false),
		mMeasType(type),
		mFunction(IPerformanceMgmt::FunctionType_T::FUNCTION_RAW),
		mReportType(),
		mBinCount(0),
		mLowerLimit(0.0),
		mUpperLimit(0.0)
	{
		mSfpData = ISfpData::getInstance(portNum);
		mMinFromActive = std::make_pair(0.0, "");
		mMaxFromActive = std::make_pair(0.0, "");
		mFirstFromActive = std::make_pair(0.0, "");
		mLatestFromActive = std::make_pair(0.0, "");
		mTableFromActive = std::vector<uint32_t>();

		mMinFromReset = std::make_pair(0.0, "");
		mMaxFromReset = std::make_pair(0.0, "");
		mFirstFromReset = std::make_pair(0.0, "");
		mLatestFromReset = std::make_pair(0.0, "");
		mTableFromReset = std::vector<uint32_t>();
		mMeasurementStartTime = "";
	};

	static const double mSaturatedLogValue;
	static const double mMinValueForLog;

	/**
	 * Activate/Deactivate measurement
	 */
	void activateDeactivate(bool activate) ;

	/**
	 * Set the function type for the measurement
	 */
	void setFunction(IPerformanceMgmt::FunctionType_T function) ;

	/**
	 * Add/Remove the report type for the measurement
	 */
	void setReportType(IPerformanceMgmt::TransReportInfoType_T report, bool add) ;

	/**
	 * Get the report type list for the measurement
	 */
	void getReportType(std::set<IPerformanceMgmt::TransReportInfoType_T>& report) ;

	/**
	 * Set the bin count for the measurement
	 */
	void setBinCount(uint16_t binCount) ;

	/**
	 * Get the bin count for the measurement
	 */
	uint16_t getBinCount(void) ;

	/**
	 * Set the lower limit for the frequency table
	 */
	void setLowerLimit(double lowerLimit) ;

	/**
	 * Set the upper limit for the frequency table
	 */
	void setUpperLimit(double upperLimit) ;

	/**
	 * Make a measurement
	 */
	bool measure(void);

	/*
	 * Is measurement active
	 */
	bool isActive(void);

	/*
	 * Get port number
	 */
	int getPortNum(void);

	/**
	 * Get the measurement results since the measurement was activated
	 */
	bool getStatsFromActive(std::pair<double, std::string>& min, std::pair<double, std::string>& max,
			std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
			std::vector<uint32_t>& table);

	/**
	 * Get the measurement results since the measurement was restarted
	 */
	bool getStatsFromReset(std::pair<double, std::string>& min, std::pair<double, std::string>& max,
			std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
			std::vector<uint32_t>& table, std::string& startTime, bool reset);

private:

	/**
	 * Populate the frequency table
	 */
	void populateFrequencyTable(double value);

	int mPortNum;
	bool mActive;
	bool mPrevActive;
	bool  mReset;
	IPerformanceMgmt::TransceiverMeasType_T mMeasType;
	IPerformanceMgmt::FunctionType_T mFunction;
	std::set<IPerformanceMgmt::TransReportInfoType_T> mReportType;
	uint16_t mBinCount;
	double mLowerLimit;
	double mUpperLimit;
	std::shared_ptr<ISfpData> mSfpData;
	std::pair<double, std::string> mMinFromActive;
	std::pair<double, std::string> mMinFromReset;
	std::pair<double, std::string> mMaxFromActive;
	std::pair<double, std::string> mMaxFromReset;
	std::pair<double, std::string> mFirstFromActive;
	std::pair<double, std::string> mFirstFromReset;
	std::pair<double, std::string> mLatestFromActive;
	std::pair<double, std::string> mLatestFromReset;
	std::vector<uint32_t> mTableFromActive;
	std::vector<uint32_t> mTableFromReset;
	std::mutex mMutex;
	std::string mMeasurementStartTime;
} ;

}

#endif /* YANG_HANDLERS_INC_PERFORMANCEMGMTSERVICE_H_ */
