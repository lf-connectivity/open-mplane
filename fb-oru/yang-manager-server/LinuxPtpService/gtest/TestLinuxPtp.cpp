/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestLinuxPtp.cpp
 * \brief     LinuxPtp test class
 *
 *
 * \details   LinuxPtp test class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "TestLinuxPtp.h"

using namespace Mplane;

TestLinuxPtp::TestLinuxPtp():
		LinuxPtp()
{
	ruClockClass = 248;
	ruClockIdentity = "0xCC11223344556677";
	ptpSourceStatus.mTwoStepFlag = true;
	ptpSourceStatus.mLeap61 = true;
	ptpSourceStatus.mLeap59 = true;
	ptpSourceStatus.mCurrentUtcOffset = 45;
	ptpSourceStatus.mCurrentUtcOffsetValid = true;
	ptpSourceStatus.mPtpTimescale = false;
	ptpSourceStatus.mTimeTraceable = true;
	ptpSourceStatus.mFreqTraceable = false;
	ptpSourceStatus.mTimeSource = 0xA3;
	ptpSourceStatus.mStepsRemoved = 55;
	ptpSourceStatus.mPriority1 = 240;
	ptpSourceStatus.mPriority2 = 136;
	ptpSourceStatus.mClockClass = 5;
	ptpSourceStatus.mClockAccuracy = 0x12;
	ptpSourceStatus.mOffsetScaledLogVariance = 0x4edc;
	ptpSourceStatus.mGrandmasterIdentity = "0xCC11223344556688";
	ptpSourceStatus.mSourceClockIdentity = "0xCC112233445566AA";
	lock = false;
};

bool TestLinuxPtp::startPtp(void)
{
	eventInfo("LinuxPtpService::startPtp()");
	std::cout << "LinuxPtpService::startPtp()" << std::endl;

	std::ofstream ofs(mPtpProcessOutputFile);

	ofs << "ptp4l[103.797]: selected /dev/ptp0 as PTP clock" << std::endl;
	ofs << "ptp4l[103.832]: port 1: INITIALIZING to LISTENING on INIT_COMPLETE" << std::endl;
	ofs << "ptp4l[103.832]: port 0: INITIALIZING to LISTENING on INIT_COMPLETE" << std::endl;
	ofs << "ptp4l[103.832]: port 1: received SYNC without timestamp" << std::endl;
	ofs << "ptp4l[103.933]: port 1: new foreign master 84c807.fffe.0f9c80-2" << std::endl;
	ofs << "ptp4l[104.183]: selected best master clock 84c807.fffe.0f9c80" << std::endl;
	ofs << "ptp4l[104.183]: updating UTC offset to 37" << std::endl;
	ofs << "ptp4l[104.183]: port 1: LISTENING to UNCALIBRATED on RS_SLAVE" << std::endl;
	ofs << "ptp4l[104.504]: port 1: UNCALIBRATED to SLAVE on MASTER_CLOCK_SELECTED" << std::endl;
	ofs << "ptp4l[105.191]: rms 798273576370234240 max 1596547152740468992 freq  -5117 +/- 2459 delay   171 +/-  52" << std::endl;
	ofs << "ptp4l[106.191]: rms  139 max  161 freq  -6568 +/-  88 delay    85 +/-   1" << std::endl;
	ofs << "ptp4l[107.191]: rms   89 max  131 freq  -6674 +/-  11 delay    82 +/-   0" << std::endl;
	ofs << "ptp4l[108.191]: rms   33 max   51 freq  -6671 +/-   8 delay    82 +/-   0" << std::endl;
	ofs << "ptp4l[109.191]: rms   11 max   23 freq  -6660 +/-  13 delay    83 +/-   1" << std::endl;
	ofs << "ptp4l[110.191]: rms   19 max   18 freq  -6662 +/-  14 delay    83 +/-   1" << std::endl;
	ofs << "ptp4l[111.191]: rms   27 max   19 freq  -6664 +/-  12 delay    84 +/-   1" << std::endl;
	ofs << "ptp4l[112.191]: rms   17 max   63 freq  -6658 +/-  28 delay    85 +/-   1" << std::endl;
	ofs << "ptp4l[113.191]: rms   20 max   59 freq  -6656 +/-  28 delay    85 +/-   0" << std::endl;
	ofs << "ptp4l[114.191]: rms    7 max   12 freq  -6653 +/-  11 delay    84 +/-   1" << std::endl;
	if (lock)
	{
		ofs << "ptp4l[115.191]: rms    7 max   16 freq  -6654 +/-  12 delay    83 +/-   1" << std::endl;
		ofs << "ptp4l[116.191]: rms    8 max   14 freq  -6659 +/-  13 delay    83 +/-   0" << std::endl;
		ofs << "ptp4l[117.191]: rms    7 max   15 freq  -6660 +/-  11 delay    83 +/-   1" << std::endl;
		ofs << "ptp4l[118.191]: rms   52 max  198 freq  -6663 +/-  87 delay    84 +/-   1" << std::endl;
		ofs << "ptp4l[119.191]: rms    7 max   18 freq  -6664 +/-  10 delay    83 +/-   1" << std::endl;
		ofs << "ptp4l[120.191]: rms   14 max   38 freq  -6650 +/-  23 delay    83 +/-   1" << std::endl;
		ofs << "ptp4l[121.191]: rms   14 max   50 freq  -6651 +/-  24 delay    85 +/-   1" << std::endl;
	}

	ofs.close();

	// Open the file that contains the PTP output log
	mPtpProcessResult.open(mPtpProcessOutputFile);

	return true;
}

bool TestLinuxPtp::stopPtp(void)
{
	eventInfo("LinuxPtpService::stopPtp()");
	std::cout << "LinuxPtpService::stopPtp()" << std::endl;

	return true;
}

bool TestLinuxPtp::sendPmcCommands(void)
{
	mPtpResponseData["clockClass"] = std::to_string(ruClockClass);
	mPtpResponseData["clockIdentity"] = ruClockIdentity;
	mPtpResponseData["twoStepFlag"] = (ptpSourceStatus.mTwoStepFlag == true ? "1" : "0");
	mPtpResponseData["leap61"] = (ptpSourceStatus.mLeap61 == true ? "1" : "0");
	mPtpResponseData["leap59"] = (ptpSourceStatus.mLeap59 == true ? "1" : "0");
	mPtpResponseData["currentUtcOffset"] = std::to_string(ptpSourceStatus.mCurrentUtcOffset);
	mPtpResponseData["currentUtcOffsetValid"] = (ptpSourceStatus.mCurrentUtcOffsetValid == true ? "1" : "0");
	mPtpResponseData["ptpTimescale"] = (ptpSourceStatus.mPtpTimescale == true ? "1" : "0");
	mPtpResponseData["timeTraceable"] = (ptpSourceStatus.mTimeTraceable == true ? "1" : "0");
	mPtpResponseData["frequencyTraceable"] = (ptpSourceStatus.mFreqTraceable == true ? "1" : "0");
	mPtpResponseData["timeSource"] = std::to_string(ptpSourceStatus.mTimeSource);
	mPtpResponseData["stepsRemoved"] = std::to_string(ptpSourceStatus.mStepsRemoved);
	mPtpResponseData["grandmasterPriority1"] = std::to_string(ptpSourceStatus.mPriority1);
	mPtpResponseData["grandmasterPriority2"] = std::to_string(ptpSourceStatus.mPriority2);
	mPtpResponseData["gm.ClockClass"] = std::to_string(ptpSourceStatus.mClockClass);
	mPtpResponseData["gm.ClockAccuracy"] = std::to_string(ptpSourceStatus.mClockAccuracy);
	mPtpResponseData["gm.OffsetScaledLogVariance"] = std::to_string(ptpSourceStatus.mOffsetScaledLogVariance);
	mPtpResponseData["grandmasterIdentity"] = ptpSourceStatus.mGrandmasterIdentity;
	mPtpResponseData["parentPortIdentity"] = ptpSourceStatus.mSourceClockIdentity;

	return true;
}

LinuxPtp::LinuxPtpServiceState TestLinuxPtp::getState(void)
{
	return mServiceState;
}

void TestLinuxPtp::serviceLinuxPtp(void)
{
	service();
}

void TestLinuxPtp::setRuClockClass(uint8_t param)
{
	ruClockClass = param;
}

/*
 * Method to set the clock identity of the clock controlled by O-RU
 */
void TestLinuxPtp::setRuClockIdentity(std::string param)
{
	ruClockIdentity = param;
}

/*
 * Method to set the PTP source state
 */
void TestLinuxPtp::setPtpParams(PtpSourceStatus param)
{
	ptpSourceStatus = param;
}

void TestLinuxPtp::setLockOutcome(bool outcome)
{
	lock = outcome;
}
