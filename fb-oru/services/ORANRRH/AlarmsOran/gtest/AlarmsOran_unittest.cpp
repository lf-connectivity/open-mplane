/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmsOran_unittest.cpp
 * \brief     Google Test of Alarms
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ORAN RrhAlarms class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "Fault.h"
#include "FaultOwner.h"
#include "IAlarm.h"
#include "IAlarmsList.h"
#include "IFaultsList.h"

#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"

#include "FaultCUPlaneConnectivityMinor.h"
#include "AlarmCUPlaneConnectivityMinor.h"
#include "FaultCUPlaneConnectivityMajor.h"
#include "AlarmCUPlaneConnectivityMajor.h"

using namespace Mplane;

class FaultInfo
{
public:
	FaultInfo(const std::string & name, std::shared_ptr<IFault> fault, std::shared_ptr<IAlarm> alarm)
		: mName(name), mFault(fault), mAlarm(alarm)
	{
	}
	virtual ~FaultInfo() {}

	const std::string       name()  { return mName;  }
	std::shared_ptr<IFault> fault() { return mFault; }
	std::shared_ptr<IAlarm> alarm() { return mAlarm; }

private:
	const std::string       mName;
	std::shared_ptr<IFault> mFault;
	std::shared_ptr<IAlarm> mAlarm;
	std::vector<bool>       mStates;
	uint32_t                mStateIdx;
};

class TestDef
{
public:
	TestDef(const std::string & name, std::vector<FaultInfo> faultInfo) :
		mName(name), mFaultInfo(faultInfo) {}
	~TestDef() {}

	void runTests()
	{
		// Run all combinations
		uint32_t numFaults = mFaultInfo.size();
		uint64_t numTests  = pow(2, numFaults);
		for (uint64_t testIdx = 0; testIdx < numTests; testIdx++)
		{
			std::cerr << "************************************************************" << std::endl;
			std::cout << "* TEST: '" << mName << "'" << std::endl;

			std::vector<bool> faultState;
			uint64_t mask = testIdx;
			std::cout << "* Mask: ";
			for (uint8_t faultIdx = 0; faultIdx < numFaults; faultIdx++)
			{
				bool state = ((mask & 1) ? true : false);
				std::cout << state;

				faultState.push_back(state);
				mask >>= 1;
			}
			std::cerr << std::endl;
			std::cerr << "************************************************************" << std::endl;
			std::cerr << std::endl;

			showFaults(true, true);
			std::cerr << std::endl;

			updateFaults(faultState);

			std::cerr << std::endl;
			showFaults(false, true);
			std::cerr << std::endl;

			verifyFaults(faultState);
			clearFaults();

			std::cerr << std::endl;
			std::cerr << "************************************************************" << std::endl;
			std::cerr << std::endl;
		}
	}

private:
	void showFaults(bool fault, bool alarm)
	{
		for (auto faultInfo : mFaultInfo)
		{
			if (fault)
				showFault(faultInfo.fault());
			if (alarm)
				showAlarm(faultInfo.alarm());
		}
	}

	bool updateFaults(std::vector<bool> faultState)
	{
		if (faultState.size() != mFaultInfo.size())
			return false;

		for (uint32_t idx = 0; idx < mFaultInfo.size(); idx++)
		{
			if (faultState[idx])
				raiseFault(idx);
			else
				clearFault(idx);
		}

		return true;
	}

	void clearFaults()
	{
		for (uint32_t idx = 0; idx < mFaultInfo.size(); idx++)
			clearFault(idx);
	}

	bool verifyFaults(std::vector<bool> faultState)
	{
		if (faultState.size() != mFaultInfo.size())
			return false;

		for (uint32_t idx = 0; idx < mFaultInfo.size(); idx++)
		{
			std::string rootCause;

			if (faultState[idx])
			{
				EXPECT_TRUE(mFaultInfo[idx].fault()->isFaultPresent());
				EXPECT_TRUE(mFaultInfo[idx].alarm()->isAlarmActive());
				rootCause = mFaultInfo[idx].alarm()->getRootCause();
				EXPECT_EQ(rootCause, cause(idx));
			}
			else
			{
				EXPECT_FALSE(mFaultInfo[idx].fault()->isFaultPresent());
				EXPECT_FALSE(mFaultInfo[idx].alarm()->isAlarmActive());
				rootCause = mFaultInfo[idx].alarm()->getRootCause();
				EXPECT_TRUE(rootCause.empty());
			}
		}
		return true;
	}

	void showFault(std::shared_ptr<IFault> fault)
	{
		fault->show();
		std::cerr << std::endl;
	}

	void showAlarm(std::shared_ptr<IAlarm> alarm)
	{
		alarm->show();
		std::cerr << std::endl;
	}

	void raiseFault(uint32_t idx)
	{
		std::cerr << "Raise '" << mFaultInfo[idx].fault()->getName() << "' fault" << std::endl;
		mFaultInfo[idx].fault()->setStatus(true);
		//showAlarm(mFaultInfo[idx].alarm());
	}

	void clearFault(uint32_t idx)
	{
		std::cerr << "Clear '" << mFaultInfo[idx].fault()->getName() << "' fault" << std::endl;
		mFaultInfo[idx].fault()->setStatus(false);
		//showAlarm(mFaultInfo[idx].alarm());
	}

	std::string cause(uint32_t idx) { return (mName + mFaultInfo[idx].name()); }

	const std::string mName;
	std::vector<FaultInfo> mFaultInfo;
};

//===================================================================================================================
class AlarmTests : public ::testing::Test
{
public:
	AlarmTests() {}
	virtual ~AlarmTests() {}

	/*! @brief Setup the test
	 */
	virtual void SetUp()
	{
		const ::testing::TestInfo* const test_info =
		  ::testing::UnitTest::GetInstance()->current_test_info();

		std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
		std::cout << test_info->name() << " - START" <<  std::endl;
	}

	/*! @brief Tear down the test
	 */
	virtual void TearDown()
	{
	}

protected:

private:

};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST(CUPlaneConnectivityAlarms, Test)
{
	TestDef testData
	{
		"FaultCUPlane",
		{
		//	{ faultName,           fault,                                       alarm                                        },
			{ "ConnectivityMinor", make_fault<FaultCUPlaneConnectivityMinor>(), make_alarm<AlarmCUPlaneConnectivityMinor>() },
			{ "ConnectivityMajor", make_fault<FaultCUPlaneConnectivityMajor>(), make_alarm<AlarmCUPlaneConnectivityMajor>() },
		},
	};
	testData.runTests();
}
