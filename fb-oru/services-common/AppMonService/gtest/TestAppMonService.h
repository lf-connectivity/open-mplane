/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestAppMonService.h
 * \brief     Test Application monitoring service
 *
 *
 * \details   Responsible for monitoring the TestApp application
 *
 */

#ifndef _TESTAPP_MONITOR_SERVICE_H_
#define _TESTAPP_MONITOR_SERVICE_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

#include "AppMonService.h"

namespace Mplane
{
	class TestAppMonService : public AppMonService
	{
	public:
		TestAppMonService();
		virtual ~TestAppMonService();

		static std::shared_ptr<TestAppMonService> singleton(void);	//!> TestApp Monitor Service singleton interface

	protected:

	private:
		virtual ReturnType::State cleanupApp(const std::string & funcStr) override;
	};
} /* namespace Mplane */

#endif /* _TESTAPP_MONITOR_SERVICE_H_ */
