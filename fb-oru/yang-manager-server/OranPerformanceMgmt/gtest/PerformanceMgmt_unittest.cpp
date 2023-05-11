/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PerformanceMgmt_unittest.cpp
 * \brief     Performance management unit tests
 *
 *
 * \details   Performance management unit tests.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "TestPerfMgmt.h"
#include "IPerformanceMgmt.h"
#include "PerformanceMgmtService.h"
#include "TestSfpData.h"

using namespace Mplane;


class TestClass : public ::testing::Test
{
public:
	virtual ~TestClass(){};

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        mPerfMgmt = new TestPerfMgmt();

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here
	  delete mPerfMgmt;
	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}

    TestPerfMgmt * mPerfMgmt;
protected:

private:

};

TEST_F(TestClass, verifyLogFunction)
{
	std::shared_ptr<TestSfpData> mSfpData = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(0));

	// Configure Rx power measurement
	mPerfMgmt->setTransMeasFunction(IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE,
			IPerformanceMgmt::FunctionType_T::FUNCTION_LOG10);

	mPerfMgmt->setTransMeasLowerLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, -20.00);

	mPerfMgmt->setTransMeasUpperLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, 100.00);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, 10);

	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, true);

	// Set value
	std::vector<float> temperatureInp{
		91.0, -10.0, -20.90, 53.42, -20.77, 112.33, 135.66, -29.00, 0.0, 22.67
	};

	// Measure with different inputs
	for (unsigned int index = 0; index < temperatureInp.size(); index++)
	{
		mSfpData->setSfpTemperature(temperatureInp[index]);
		mPerfMgmt->measure();
	}

	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	// Get active measurements
	EXPECT_TRUE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE,
			min, max, first, latest, table));

	// Check the results
	EXPECT_NEAR(min.first, -128.0, 0.05);
	EXPECT_NEAR(max.first, 2.13, 0.05);
	EXPECT_NEAR(first.first, 1.96, 0.05);
	EXPECT_NEAR(latest.first, 1.36, 0.05);
	EXPECT_EQ(table.size(), (unsigned)10);
}

TEST_F(TestClass, measRxPowerFromActive)
{
	std::shared_ptr<TestSfpData> mSfpData = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(0));

	// Configure temperature measurement
	mPerfMgmt->setTransMeasFunction(IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER,
			IPerformanceMgmt::FunctionType_T::FUNCTION_RAW);

	mPerfMgmt->setTransMeasLowerLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, -2.00);

	mPerfMgmt->setTransMeasUpperLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, 10.00);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, 10);

	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, true);

	// Set value
	std::vector<double> rxPowerInput{
		-1000.0, 9100.0, -2090.0, 5342.0, -2077.0, 11233.0, 13566.0, -2900.0, 2267.0, 0.0
	};

	// Measure with different inputs
	for (unsigned int index = 0; index < rxPowerInput.size(); index++)
	{
		mSfpData->setSfpRxPowerMicroW(rxPowerInput[index]);
		mPerfMgmt->measure();
	}

	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	// Get active measurements
	EXPECT_TRUE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER,
			min, max, first, latest, table));

	// Check the results
	EXPECT_NEAR(min.first, *std::min_element(rxPowerInput.begin(), rxPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(max.first, *std::max_element(rxPowerInput.begin(), rxPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(first.first, rxPowerInput[0]/1000.0, 0.01);
	EXPECT_NEAR(latest.first, rxPowerInput[rxPowerInput.size() - 1]/1000.0, 0.01);
	EXPECT_EQ(table.size(), (unsigned)10);

	// Check the frequency table
	EXPECT_EQ(table[0], (unsigned)3);
	EXPECT_EQ(table[1], (unsigned)1);
	EXPECT_EQ(table[2], (unsigned)1);
	EXPECT_EQ(table[3], (unsigned)1);
	EXPECT_EQ(table[4], (unsigned)0);
	EXPECT_EQ(table[5], (unsigned)1);
	EXPECT_EQ(table[6], (unsigned)0);
	EXPECT_EQ(table[7], (unsigned)0);
	EXPECT_EQ(table[8], (unsigned)1);
	EXPECT_EQ(table[9], (unsigned)2);
}

TEST_F(TestClass, measTxPowerFromActive)
{
	std::shared_ptr<TestSfpData> mSfpData = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(0));

	// Configure Tx power measurement
	mPerfMgmt->setTransMeasFunction(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER,
			IPerformanceMgmt::FunctionType_T::FUNCTION_RAW);

	mPerfMgmt->setTransMeasLowerLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, -5.00);

	mPerfMgmt->setTransMeasUpperLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, 30.00);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, 6);

	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, true);

	// Set value and measure
	std::vector<double> txPowerInput{
		-4488.0, 21003.0, -6544.0, 0.0, 34002.0, 4678.0, -2178.0, 9754.0, 15000.0, 18966.0, -3445.0, 18954.0
	};

	// Measure Tx power
	for (unsigned int index = 0; index < txPowerInput.size(); index++)
	{
		mSfpData->setSfpTxPowerMicroW(txPowerInput[index]);
		mPerfMgmt->measure();
	}

	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	// Get active measurements
	EXPECT_TRUE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER,
			min, max, first, latest, table));

	// Check results
	EXPECT_NEAR(min.first, *std::min_element(txPowerInput.begin(), txPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(max.first, *std::max_element(txPowerInput.begin(), txPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(first.first, txPowerInput[0]/1000.0, 0.01);
	EXPECT_NEAR(latest.first, txPowerInput[txPowerInput.size() - 1]/1000.0, 0.01);
	EXPECT_EQ(table.size(), (unsigned)6);

	// Check frequency table
	EXPECT_EQ(table[0], (unsigned)1);
	EXPECT_EQ(table[1], (unsigned)4);
	EXPECT_EQ(table[2], (unsigned)2);
	EXPECT_EQ(table[3], (unsigned)4);
	EXPECT_EQ(table[4], (unsigned)0);
	EXPECT_EQ(table[5], (unsigned)1);

	// Now deactivate measurement and change bin count
	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, false);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, 15);

	// Activate measurement
	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, true);

	// Change the input
	txPowerInput.clear();
	txPowerInput.push_back(15649.0);
	txPowerInput.push_back(32002.0);
	txPowerInput.push_back(-5688.0);
	txPowerInput.push_back(-1344.0);
	txPowerInput.push_back(0.0);
	txPowerInput.push_back(8766.0);
	txPowerInput.push_back(19776.0);
	txPowerInput.push_back(-3422.0);
	txPowerInput.push_back(-7899.0);
	txPowerInput.push_back(34556.0);
	txPowerInput.push_back(30000.0);
	txPowerInput.push_back(-5000.0);
	txPowerInput.push_back(16554.0);
	txPowerInput.push_back(1098.0);
	txPowerInput.push_back(26987.0);

	// Measure again
	for (unsigned int index = 0; index < txPowerInput.size(); index++)
	{
		mSfpData->setSfpTxPowerMicroW(txPowerInput[index]);
		mPerfMgmt->measure();
	}

	// Get active measurements
	EXPECT_TRUE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER,
			min, max, first, latest, table));

	// Check that the results are based on the new input and the new bin count
	EXPECT_NEAR(min.first, *std::min_element(txPowerInput.begin(), txPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(max.first, *std::max_element(txPowerInput.begin(), txPowerInput.end())/1000.0, 0.01);
	EXPECT_NEAR(first.first, txPowerInput[0]/1000.0, 0.01);
	EXPECT_NEAR(latest.first, txPowerInput[txPowerInput.size() - 1]/1000.0, 0.01);
	EXPECT_EQ(table.size(), (unsigned)15);

	EXPECT_EQ(table[0], (unsigned)2);
	EXPECT_EQ(table[1], (unsigned)2);
	EXPECT_EQ(table[2], (unsigned)2);
	EXPECT_EQ(table[3], (unsigned)1);
	EXPECT_EQ(table[4], (unsigned)0);
	EXPECT_EQ(table[5], (unsigned)0);
	EXPECT_EQ(table[6], (unsigned)1);
	EXPECT_EQ(table[7], (unsigned)0);
	EXPECT_EQ(table[8], (unsigned)1);
	EXPECT_EQ(table[9], (unsigned)1);
	EXPECT_EQ(table[10], (unsigned)1);
	EXPECT_EQ(table[11], (unsigned)0);
	EXPECT_EQ(table[12], (unsigned)1);
	EXPECT_EQ(table[13], (unsigned)0);
	EXPECT_EQ(table[14], (unsigned)3);
}

TEST_F(TestClass, noMeasTaken)
{
	std::shared_ptr<TestSfpData> mSfpData = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(0));
	// Configure supply voltage measurements
	mPerfMgmt->setTransMeasFunction(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE,
			IPerformanceMgmt::FunctionType_T::FUNCTION_RAW);

	mPerfMgmt->setTransMeasLowerLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, -2.00);

	mPerfMgmt->setTransMeasUpperLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, 10.00);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, 10);

	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, true);

	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	// Measurements are not returned as there is not a single one that is available
	EXPECT_FALSE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE,
			min, max, first, latest, table));

	// Now measure
	mPerfMgmt->measure();

	// Measurement should be returned successfully
	EXPECT_TRUE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE,
			min, max, first, latest, table));

	// Deactivate the measurement
	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, false);

	// Measurements are not returned as it is deactivated
	EXPECT_FALSE(mPerfMgmt->getTransceiverMeasResult(0, IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE,
			min, max, first, latest, table));
}

TEST_F(TestClass, getTxCurrNotifications)
{
	std::shared_ptr<TestSfpData> mSfpData = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(0));
	std::shared_ptr<TestSfpData> mSfp3Data = std::dynamic_pointer_cast<TestSfpData>(ISfpData::getInstance(3));

	// Configure Tx Bias current measurement
	mPerfMgmt->setTransMeasFunction(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT,
			IPerformanceMgmt::FunctionType_T::FUNCTION_RAW);

	mPerfMgmt->setTransMeasLowerLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, -2.00);

	mPerfMgmt->setTransMeasUpperLimit(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, 10.00);

	mPerfMgmt->setTransMeasBinCount(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, 10);

	mPerfMgmt->setTransMeasActiveInactive(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, true);

	// Set value and measure
	std::vector<double> txbiasCurr{
		-1.0, 9.100, -2.090, 5.342, -2.077, 11.233, 13.566, -2.900, 2.267, 0.0
	};

	std::vector<double> txbiasCurr3{
		-1.1, 9.200, -2.590, 15.342, -2.7, 11.543, 17.566, -2.900, 2.267, 0.0
	};
	for (unsigned int index = 0; index < txbiasCurr.size(); index++)
	{
		mSfpData->setSfpTxBiasCurrent(txbiasCurr[index]);
		mSfp3Data->setSfpTxBiasCurrent(txbiasCurr3[index]);
		mPerfMgmt->measure();
	}

	// Calculate statistics for the measurement interval
	mPerfMgmt->calculate();

	// Get the data for the interval
	std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> notif = mPerfMgmt->getNotificationData();

	// Verify that it contains only 1 type of measurement
	EXPECT_NE(notif.find(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT), notif.end());
	EXPECT_EQ(notif.size(), (unsigned)1);
	EXPECT_EQ(notif[IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT][0].data.size(), (unsigned)2);

	// Verify measurement data
	IPerformanceMgmt::transMeasurement measData = notif[IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT][0].data[0];
	EXPECT_EQ(measData.port, 0);
	EXPECT_NEAR(measData.min.first, *std::min_element(txbiasCurr.begin(), txbiasCurr.end()), 0.01);
	EXPECT_NEAR(measData.max.first, *std::max_element(txbiasCurr.begin(), txbiasCurr.end()), 0.01);
	EXPECT_NEAR(measData.first.first, txbiasCurr[0], 0.01);
	EXPECT_NEAR(measData.latest.first, txbiasCurr[txbiasCurr.size() - 1], 0.01);
	EXPECT_EQ(measData.table.size(), (unsigned)10);

	measData = notif[IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT][0].data[1];
	EXPECT_EQ(measData.port, 3);
	EXPECT_NEAR(measData.min.first, *std::min_element(txbiasCurr3.begin(), txbiasCurr3.end()), 0.01);
	EXPECT_NEAR(measData.max.first, *std::max_element(txbiasCurr3.begin(), txbiasCurr3.end()), 0.01);
	EXPECT_NEAR(measData.first.first, txbiasCurr3[0], 0.01);
	EXPECT_NEAR(measData.latest.first, txbiasCurr3[txbiasCurr3.size() - 1], 0.01);
	EXPECT_EQ(measData.table.size(), (unsigned)10);

	// Clear the notification data
	mPerfMgmt->clearNotificationData();

	// Setup new input values
	txbiasCurr.clear();
	txbiasCurr.push_back(15.649);
	txbiasCurr.push_back(32.002);
	txbiasCurr.push_back(-5.688);
	txbiasCurr.push_back(-1.344);
	txbiasCurr.push_back(0.0);
	txbiasCurr.push_back(8.766);
	txbiasCurr.push_back(19.776);
	txbiasCurr.push_back(-3.422);
	txbiasCurr.push_back(-7.899);
	txbiasCurr.push_back(34.556);
	txbiasCurr.push_back(30.000);
	txbiasCurr.push_back(-5.000);
	txbiasCurr.push_back(16.554);
	txbiasCurr.push_back(1.098);
	txbiasCurr.push_back(26.987);

	// Measure
	for (unsigned int index = 0; index < txbiasCurr.size(); index++)
	{
		mSfpData->setSfpTxBiasCurrent(txbiasCurr[index]);
		mPerfMgmt->measure();
	}

	// Calculate stats
	mPerfMgmt->calculate();

	// Get the notification data
	notif.clear();
	notif = mPerfMgmt->getNotificationData();

	// Verify that the notification data is based on new inputs
	EXPECT_NE(notif.find(IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT), notif.end());
	EXPECT_EQ(notif.size(), (unsigned)1);
	EXPECT_EQ(notif[IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT][0].data.size(), (unsigned)2);

	measData = notif[IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT][0].data[0];
	EXPECT_EQ(measData.port, 0);
	EXPECT_NEAR(measData.min.first, *std::min_element(txbiasCurr.begin(), txbiasCurr.end()), 0.01);
	EXPECT_NEAR(measData.max.first, *std::max_element(txbiasCurr.begin(), txbiasCurr.end()), 0.01);
	EXPECT_NEAR(measData.first.first, txbiasCurr[0], 0.01);
	EXPECT_NEAR(measData.latest.first, txbiasCurr[txbiasCurr.size() - 1], 0.01);
	EXPECT_EQ(measData.table.size(), (unsigned)10);

	mPerfMgmt->clearNotificationData();
}
