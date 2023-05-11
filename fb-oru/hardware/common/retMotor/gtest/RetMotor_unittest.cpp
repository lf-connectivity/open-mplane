/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RetMotor_unittest.cpp
 * \brief     Test case implementation file for the RetMotor
 *
 *
 * \details   Test case implementation file for the RetMotor
 *
 */

#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>
#include <string>

#include <memory>
#include "RetMotorControl.h"
#include "Task.h"
#include "RetMotor_unittest.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
RetMotorUnitTest::RetMotorUnitTest(std::shared_ptr<IRetMotorControl> ret) :
		Task(Task::PRIORITY_DEFAULT, Task::MEDIUM_STACK,
						"RetMotorUnitTest",
						"RetMotorUnitTestTask"
					),
		mRetMotorControl(ret)
{
	start();
}

//-------------------------------------------------------------------------------------------------------------
RetMotorUnitTest::~RetMotorUnitTest(void)
{
	mShutdown = true;
}

//-------------------------------------------------------------------------------------------------------------
int RetMotorUnitTest::run(void)
{
	while (!mShutdown)
	{
		mRetMotorControl->timerUpdate();
		Task::msSleep(100);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
TEST(TestRetMotorTestCases, Comm)
{
#ifdef DISABLED_DUE_TO_SERVER_ISSUES

	std::shared_ptr<IRetMotorControl> ret(IRetMotorControl::getInstance());

	//Start a thread to call the timerUpdate method of RetMotorcontrol
	RetMotorUnitTest test(ret);

	//Connect the Ret Motor
	EXPECT_TRUE(ret->connect());

	//Send reset command to reset Aisg devices
	EXPECT_TRUE(ret->reset());

	//Scan the bus for Aisg devices
	EXPECT_TRUE(ret->scan());

	//Wait till scanning is in progress
	while (ret->status() == "SCANNING")
	{
		Task::msSleep(20);
	};

	//Expected to receive 1 device
	EXPECT_EQ(ret->status(), "READY");

	EXPECT_EQ(ret->getNumDevices(), 1);

	//Wait till the device gets initialised
	while (ret->status(1) == "RUN")
	{
		Task::msSleep(20);
	};

	//Device status expected to be ready
	EXPECT_EQ(ret->status(1), "READY");

	//Set tilt to some value
	EXPECT_TRUE(ret->setTilt(1,4.0));
	while (ret->status(1) == "RUN")
	{
		Task::msSleep(20);
	};
	EXPECT_EQ(ret->status(1), "READY");

	double tilt;
	//Expect tilt to be the value that was set
	EXPECT_TRUE(ret->getTilt(1, tilt));
	EXPECT_EQ(tilt, 4.0);

	//Set tilt to some value
	EXPECT_TRUE(ret->setTilt(1,10.7));
	while (ret->status(1) == "RUN")
	{
		Task::msSleep(20);
	};
	EXPECT_EQ(ret->status(1), "READY");

	//Expect tilt to be the value that was set
	EXPECT_TRUE(ret->getTilt(1, tilt));
	EXPECT_EQ(tilt, 10.7);

	//As Get Min tilt is not implemented by the Mock motor, it should fail
	EXPECT_FALSE(ret->getMinTilt(1, tilt));

	EXPECT_EQ(ret->status(1), "FAIL");
#endif
}
