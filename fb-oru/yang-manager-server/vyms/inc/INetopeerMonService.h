/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetopeerMonService.h
 * \brief     Netopeer Monitor Service virtual interface
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _VYMS_INC_INETOPEER_MONITOR_SERVICE_H_
#define _VYMS_INC_INETOPEER_MONITOR_SERVICE_H_

#include <memory>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane
{
	class INetopeerMonService
	{
	public:
		INetopeerMonService() {}
		virtual ~INetopeerMonService() {}

		static std::shared_ptr<INetopeerMonService> singleton(void);	//!> Netopeer Monitor Service singleton interface

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
		virtual std::string getServiceStatusString(void) = 0;	//!> Get the current service state

		typedef enum
		{
			ENABLE,
			DISABLE,
		} enableDisable_T;

		virtual void setMonitorServiceState(enableDisable_T enableDisableMonitor) = 0;	//!> Enable/Disable the monitor service
		virtual enableDisable_T getMonitorServiceState(void) = 0;						//!> Get the state of the monitor service
		virtual std::string getMonitorServiceStateString(void) = 0;						//!> Get the state of the monitor service

		virtual void setAutoRestart(enableDisable_T enableDisableAutoRestart) = 0;	//!> Enable/Disable the process auto restart
		virtual enableDisable_T getAutoRestart(void) = 0;							//!> Get Enable/Disable auto restart state
		virtual std::string getAutoRestartString(void) = 0;							//!> Get Enable/Disable auto restart state

		virtual UINT32 getAppFailedCount(void) = 0;	//!> Get the netopeer application failed count
		virtual void clrAppFailedCount(void) = 0;			//!> Clear the netopeer application failed count
	};
}

#endif /* _VYMS_INC_INETOPEER_MONITOR_SERVICE_H_ */
