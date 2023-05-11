/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppMonService.h
 * \brief     Application Monitor Service virtual interface
 *
 *
 * \details   Application Monitor Service virtual interface
 *
 */

#ifndef _VYMS_INC_IAPP_MONITOR_SERVICE_H_
#define _VYMS_INC_IAPP_MONITOR_SERVICE_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane
{
	class IAppMonService
	{
	public:
		IAppMonService() {}
		virtual ~IAppMonService() {}

		virtual ReturnType::State setOptions(const std::string & optionsStr) = 0;
		virtual ReturnType::State clearOptions(void) = 0;

		virtual ReturnType::State startService(void) = 0;		//!> Start the service
		virtual ReturnType::State restartService(void) = 0;		//!> Restart the service
		virtual ReturnType::State stopService(void) = 0;		//!> Stop the service

		typedef enum
		{
			STOPPED,
			RUNNING,
			FAILED,
		} serviceStatus_T;

		virtual serviceStatus_T getServiceStatus(void) = 0;		//!> Get the current service state
		virtual std::string getServiceStatusString(void) = 0;	//!> Get the current service state string

		typedef enum
		{
			ENABLE,
			DISABLE,
		} enableDisable_T;

		virtual void setMonitorServiceState(enableDisable_T enableDisableMonitor) = 0;	//!> Enable/Disable the monitor service
		virtual enableDisable_T getMonitorServiceState(void) = 0;						//!> Get the state of the monitor service
		virtual std::string getMonitorServiceStateString(void) = 0;						//!> Get the state of the monitor service string

		virtual void setAutoRestart(enableDisable_T enableDisableAutoRestart) = 0;	//!> Enable/Disable the application auto restart
		virtual enableDisable_T getAutoRestart(void) = 0;							//!> Get Enable/Disable auto restart state
		virtual std::string getAutoRestartString(void) = 0;							//!> Get Enable/Disable auto restart state string

		virtual UINT32 getAppFailedCount(void) = 0;		//!> Get the application failed count
		virtual void clrAppFailedCount(void) = 0;		//!> Clear the application failed count

	private:
		virtual ReturnType::State cleanupApp(const std::string & funcStr) = 0;	//!> Called to cleanup the application

	};
}

#endif /* _VYMS_INC_IAPP_MONITOR_SERVICE_H_ */
