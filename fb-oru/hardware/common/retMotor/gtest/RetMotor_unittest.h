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

namespace Mplane
{

class RetMotorUnitTest: public Task
{
public:
	RetMotorUnitTest(std::shared_ptr<IRetMotorControl> ret);

	virtual ~RetMotorUnitTest();

protected:
	virtual int run() override;
	std::shared_ptr<IRetMotorControl> mRetMotorControl;
	bool mShutdown;
};

}
