/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxWindowMeasurement.h
 * \brief     Class to configure and measure for Rx window parameters
 *
 *
 * \details   Class to configure and measure for Rx window parameters
 *
 */


#ifndef YANG_HANDLERS_INC_RXWINDOWMEASUREMENT_H_
#define YANG_HANDLERS_INC_RXWINDOWMEASUREMENT_H_

#include <memory>
#include <utility>
#include <map>
#include <vector>
#include <mutex>

#include "IPerformanceMgmt.h"

namespace Mplane {

/*!
 * \class  RxWindowMeasurement
 * \brief
 * \details
 *
 */
class RxWindowMeasurement{
public:

	explicit RxWindowMeasurement(IPerformanceMgmt::RxWindowMeasType_T type);

	/**
	 * Activate/Deactivate measurement
	 */
	void activateDeactivate(bool activate) ;

	/**
	 * Set the function type for the measurement
	 */
	void setObjectUnitId(IPerformanceMgmt::RxWindowObjectUnitId_T id) ;

	/*
	 * Is measurement active
	 */
	bool isActive(void);

	/**
	 * Get the measurement results since the measurement was activated
	 */
	bool getStatsFromActive(uint64_t& data);

	/**
	 * Get the measurement results since the measurement was restarted
	 */
	bool getStatsFromReset(uint64_t& data, std::string& startTime, bool reset);

private:

	bool mActive;
	bool  mReset;
	IPerformanceMgmt::RxWindowMeasType_T mMeasType;
	IPerformanceMgmt::RxWindowObjectUnitId_T mObjUnitId;
	uint64_t mDataFromActive;
	uint64_t mDataFromReset;
	std::mutex mMutex;
	std::string mMeasurementStartTime;
} ;

}

#endif /* YANG_HANDLERS_INC_RXWINDOWMEASUREMENT_H_ */
