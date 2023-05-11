/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Dot1agdMonService.h
 * \brief     Dot1agd monitoring service
 *
 *
 * \details   Responsible for monitoring the Dot1agd (IEEE 802.1ag Daemon) application
 *
 */

#ifndef _DOT1AGD_MONITOR_SERVICE_H_
#define _DOT1AGD_MONITOR_SERVICE_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

#include "AppMonService.h"

namespace Mplane
{
	class Dot1agdMonService : public AppMonService
	{
	public:
		Dot1agdMonService();
		virtual ~Dot1agdMonService();

		static std::shared_ptr<Dot1agdMonService> singleton(void);	//!> 802.1ag Daemon Monitor Service singleton interface

	protected:

	private:
		virtual ReturnType::State cleanupApp(const std::string & funcStr) override;
	};
} /* namespace Mplane */

#endif /* _DOT1AGD_MONITOR_SERVICE_H_ */
