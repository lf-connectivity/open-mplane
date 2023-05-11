/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAppMonServiceSingleton.cpp
 * \brief     TestApp application monitoring service singleton
 *
 *
 * \details   TestApp application monitoring service singleton
 *
 */
#include <memory>

#include "TestAppMonService.h"

using namespace Mplane;

std::shared_ptr<TestAppMonService> TestAppMonService::singleton(void)
{
	static std::shared_ptr<TestAppMonService> instance(std::make_shared<TestAppMonService>());
	return instance;
}
