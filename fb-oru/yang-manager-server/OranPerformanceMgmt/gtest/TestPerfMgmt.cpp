/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestPerfMgmt.cpp
 * \brief     Performance management test class
 *
 *
 * \details   Performance management test class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "TestPerfMgmt.h"
#include "ISfpData.h"
#include "TestBus.h"
#include "TestSfpData.h"

using namespace Mplane;

namespace Mplane
{

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISfpData> ISfpData::getInstance(int port)
{
	std::vector< std::shared_ptr<ISfpData> > sfpList( ISfpData::getSfps() );

	int index = 0;
	for (auto & sfp : sfpList)
	{
		if (sfp->getPort() == port)
		{
			break;
		}
		index++;
	}

	if ((unsigned)index >= sfpList.size())
	{
		return nullptr;
	}

    return (sfpList[index]) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::shared_ptr<ISfpData> > ISfpData::getSfps( void )
{
	static std::vector< std::shared_ptr<ISfpData> > sfpList;

	// Create SFPs for all ports
	if( sfpList.empty())
	{
		// Create buses for I2C access for A0 and A1 chips
		std::shared_ptr<II2cBus> i2cA0 = std::make_shared<TestI2cBus>("A0-SFP-0", "SFP I2C bus");
		std::shared_ptr<II2cBus> i2cA1 = std::make_shared<TestI2cBus>("A2-SFP-0", "SFP I2C bus");
		std::shared_ptr<II2cBus> i2c3A0 = std::make_shared<TestI2cBus>("A0-SFP-3", "SFP I2C bus");
		std::shared_ptr<II2cBus> i2c3A1 = std::make_shared<TestI2cBus>("A2-SFP-3", "SFP I2C bus");

		// Create SFP data
		sfpList.push_back ( std::shared_ptr<ISfpData>(std::make_shared<TestSfpData>(0, i2cA0, i2cA1)) );
		sfpList.push_back ( std::shared_ptr<ISfpData>(std::make_shared<TestSfpData>(3, i2c3A0, i2c3A1)) );

	}
	return sfpList;
}

}

TestPerfMgmt::TestPerfMgmt():
		PerformanceMgmtService(std::vector<int>{0,3})
{
};

void TestPerfMgmt::measure(void)
{
	takeLocalMeasurement();
}

void TestPerfMgmt::calculate(void)
{
	calculateTransStatistics();
}

std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> TestPerfMgmt::getNotificationData(void)
{
	return mTransNotificationData;
}

void TestPerfMgmt::clearNotificationData(void)
{
	mTransNotificationData.clear();
}

std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> TestPerfMgmt::getFileUploadData(void)
{
	return mTransFileUploadData;
}

void TestPerfMgmt::clearFileUploadData(void)
{
	mTransFileUploadData.clear();
}
