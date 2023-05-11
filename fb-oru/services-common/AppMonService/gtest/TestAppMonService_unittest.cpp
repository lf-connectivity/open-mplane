/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAppMonService_unittest.cpp
 * \brief     TestApp application monitoring service unit tests
 *
 *
 * \details   TestApp application monitoring service unit tests
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "TestAppMonService.h"

using namespace Mplane;

class TestAppMonServiceTests : public ::testing::Test
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

TEST_F(TestAppMonServiceTests, initalStates)
{
	std::shared_ptr<TestAppMonService> AppMonitor(TestAppMonService::singleton());

	// Make sure that we've come up in the expected states
	EXPECT_EQ(AppMonitor->getAutoRestart(),IAppMonService::enableDisable_T::DISABLE);
	EXPECT_EQ(AppMonitor->getMonitorServiceState(),IAppMonService::enableDisable_T::ENABLE);
	EXPECT_EQ(AppMonitor->getServiceStatus(),IAppMonService::serviceStatus_T::STOPPED);
}

TEST_F(TestAppMonServiceTests, autoRestart)
{
	std::shared_ptr<TestAppMonService> AppMonitor(TestAppMonService::singleton());

	// Make sure that we've come up in the expected state
	EXPECT_EQ(AppMonitor->getAutoRestart(),IAppMonService::enableDisable_T::DISABLE);
	EXPECT_EQ(AppMonitor->getAutoRestartString(),"Disabled");

	AppMonitor->setAutoRestart(IAppMonService::enableDisable_T::ENABLE);

	EXPECT_EQ(AppMonitor->getAutoRestart(),IAppMonService::enableDisable_T::ENABLE);
	EXPECT_EQ(AppMonitor->getAutoRestartString(),"Enabled");

	AppMonitor->setAutoRestart(IAppMonService::enableDisable_T::DISABLE);

	EXPECT_EQ(AppMonitor->getAutoRestart(),IAppMonService::enableDisable_T::DISABLE);
}

TEST_F(TestAppMonServiceTests, monitorServiceState)
{
	std::shared_ptr<TestAppMonService> AppMonitor(TestAppMonService::singleton());

	// Make sure that we've come up in the expected state
	EXPECT_EQ(AppMonitor->getMonitorServiceState(),IAppMonService::enableDisable_T::ENABLE);
	EXPECT_EQ(AppMonitor->getMonitorServiceStateString(),"Enabled");

	AppMonitor->setMonitorServiceState(IAppMonService::enableDisable_T::DISABLE);

	EXPECT_EQ(AppMonitor->getMonitorServiceState(),IAppMonService::enableDisable_T::DISABLE);
	EXPECT_EQ(AppMonitor->getMonitorServiceStateString(),"Disabled");

	AppMonitor->setMonitorServiceState(IAppMonService::enableDisable_T::ENABLE);

	EXPECT_EQ(AppMonitor->getMonitorServiceState(),IAppMonService::enableDisable_T::ENABLE);
	EXPECT_EQ(AppMonitor->getMonitorServiceStateString(),"Enabled");

	AppMonitor->setMonitorServiceState(IAppMonService::enableDisable_T::DISABLE);

	EXPECT_EQ(AppMonitor->getMonitorServiceState(),IAppMonService::enableDisable_T::DISABLE);
}
