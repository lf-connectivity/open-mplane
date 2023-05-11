/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetopeerMonService_unittest.cpp
 * \brief     Netopeer Monitoring service unit tests
 *
 *
 * \details   Netopeer Monitoring service unit tests
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "INetopeerMonService.h"

using namespace Mplane;

class NetopeerMonServiceTests : public ::testing::Test
{
public:

	virtual void SetUp()
	{
		const ::testing::TestInfo* const test_info =
				::testing::UnitTest::GetInstance()->current_test_info();

		std::cout << std::endl << "*** " << test_info->test_case_name()
				<< " Tests ***" << std::endl;
		std::cout << test_info->name() << " - SETUP" << std::endl;

		// Do the setup here

		std::cout << test_info->name() << " - SETUP complete" << std::endl;
	}

	virtual void TearDown()
	{
		const ::testing::TestInfo* const test_info =
				::testing::UnitTest::GetInstance()->current_test_info();

		std::cout << test_info->name() << " - TEARDOWN" << std::endl;

		// Do the tear down here

		std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}
protected:

private:
};

TEST_F(NetopeerMonServiceTests, initalStates)
{
	std::shared_ptr<INetopeerMonService> NetopeerMonitor(INetopeerMonService::singleton());

	// Make sure that we've come up in the expected states
	ASSERT_EQ(NetopeerMonitor->getAutoRestart(),INetopeerMonService::enableDisable_T::DISABLE);
	ASSERT_EQ(NetopeerMonitor->getMonitorServiceState(),INetopeerMonService::enableDisable_T::ENABLE);
	ASSERT_EQ(NetopeerMonitor->getServiceStatus(),INetopeerMonService::serviceStatus_T::STOPPED);
}

TEST_F(NetopeerMonServiceTests, autoRestart)
{
	std::shared_ptr<INetopeerMonService> NetopeerMonitor(INetopeerMonService::singleton());

	// Make sure that we've come up in the expected state
	ASSERT_EQ(NetopeerMonitor->getAutoRestart(),INetopeerMonService::enableDisable_T::DISABLE);
	ASSERT_EQ(NetopeerMonitor->getAutoRestartString(),"Disabled");

	NetopeerMonitor->setAutoRestart(INetopeerMonService::enableDisable_T::ENABLE);

	ASSERT_EQ(NetopeerMonitor->getAutoRestart(),INetopeerMonService::enableDisable_T::ENABLE);
	ASSERT_EQ(NetopeerMonitor->getAutoRestartString(),"Enabled");

	NetopeerMonitor->setAutoRestart(INetopeerMonService::enableDisable_T::DISABLE);

	ASSERT_EQ(NetopeerMonitor->getAutoRestart(),INetopeerMonService::enableDisable_T::DISABLE);
}

TEST_F(NetopeerMonServiceTests, monitorServiceState)
{
	std::shared_ptr<INetopeerMonService> NetopeerMonitor(INetopeerMonService::singleton());

	// Make sure that we've come up in the expected state
	ASSERT_EQ(NetopeerMonitor->getMonitorServiceState(),INetopeerMonService::enableDisable_T::ENABLE);
	ASSERT_EQ(NetopeerMonitor->getMonitorServiceStateString(),"Enabled");

	NetopeerMonitor->setMonitorServiceState(INetopeerMonService::enableDisable_T::DISABLE);

	ASSERT_EQ(NetopeerMonitor->getMonitorServiceState(),INetopeerMonService::enableDisable_T::DISABLE);
	ASSERT_EQ(NetopeerMonitor->getMonitorServiceStateString(),"Disabled");

	NetopeerMonitor->setMonitorServiceState(INetopeerMonService::enableDisable_T::ENABLE);

	ASSERT_EQ(NetopeerMonitor->getMonitorServiceState(),INetopeerMonService::enableDisable_T::ENABLE);
	ASSERT_EQ(NetopeerMonitor->getMonitorServiceStateString(),"Enabled");

	NetopeerMonitor->setMonitorServiceState(INetopeerMonService::enableDisable_T::DISABLE);

	ASSERT_EQ(NetopeerMonitor->getMonitorServiceState(),INetopeerMonService::enableDisable_T::DISABLE);
}
