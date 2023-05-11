/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestPerfMgmt.h
 * \brief     Performance management test class
 *
 *
 * \details   Performance management test class.
 *
 */

#ifndef TESTPERFMGMT_H_
#define TESTPERFMGMT_H_

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "PerformanceMgmtService.h"

using namespace Mplane;

namespace Mplane
{

class TestPerfMgmt : public PerformanceMgmtService
{
public :
	TestPerfMgmt();
	virtual ~TestPerfMgmt(){};

	/**
	 * Method to take measurement for each enabled measurement type.
	 */
	void measure(void);

	/**
	 * Method to calculate statistics in the current measurement interval.
	 */
	void calculate(void);

	std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> getNotificationData(void);

	void clearNotificationData(void);

	std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> getFileUploadData(void);

	void clearFileUploadData(void);

};
}

#endif
