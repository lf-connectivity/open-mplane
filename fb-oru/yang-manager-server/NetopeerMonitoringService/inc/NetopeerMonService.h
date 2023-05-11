/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NetopeerMonService.h
 * \brief     Netopeer Monitoring service
 *
 *
 * \details   Responsible for monitoring the Netopeer application.
 *
 */

#ifndef _NETOPEER_MONITOR_SERVICE_H_
#define _NETOPEER_MONITOR_SERVICE_H_

#include "Mutex.h"
#include "Service.h"

#include "INetopeerMonService.h"

namespace Mplane
{
	class NetopeerMonService : public Service, public INetopeerMonService
	{
	public:
		NetopeerMonService();

		virtual ~NetopeerMonService();

		virtual ReturnType::State startService(void);		//!> Start the service
		virtual ReturnType::State restartService(void);		//!> Restart the service
		virtual ReturnType::State stopService(void);		//!> Stop the service

		virtual serviceStatus_T getServiceStatus(void);		//!> Get the current service state
		virtual std::string getServiceStatusString(void);	//!> Get the current service state

		virtual void setMonitorServiceState(enableDisable_T enableDisableMonitor);	//!> Enable/Disable the monitor service
		virtual enableDisable_T getMonitorServiceState(void);						//!> Get the state of the monitor service
		virtual std::string getMonitorServiceStateString(void);						//!> Get the state of the monitor service

		virtual void setAutoRestart(enableDisable_T enableDisableAutoRestart);	//!> Enable/Disable the process auto restart
		virtual enableDisable_T getAutoRestart(void);							//!> Get Enable/Disable auto restart state
		virtual std::string getAutoRestartString(void);							//!> Get Enable/Disable auto restart state

		virtual UINT32 getAppFailedCount(void);		//!> Get the netopeer application failed count
		virtual void clrAppFailedCount(void);		//!> Clear the netopeer application failed count

	protected:
		/**
		 * Method defined by the Loggable interface must be implemented by all
		 * object to force the display of the objects current status.
		 */
		virtual void show();

		/**
		 * Method that MUST be implemented by the inheriting service. The work done
		 * by the service, is implemented by this method.
		 * @return
		 */
		virtual int service();

		/**
		 * Method called as a result of the radio control process calling reset
		 * in the service. By default the base class implementation does nothing.
		 */
		virtual void doReset();

	private:
		INetopeerMonService::serviceStatus_T mServiceState;			//!> Internal service state member variable
		INetopeerMonService::enableDisable_T mMonitorServiceState;	//!> Internal monitor service state member variable
		INetopeerMonService::enableDisable_T mAutoRestartProcess;	//!> Internal auto restart process member variable

		static const std::string mServiceStatusStoppedStr;			//!> Service status stopped string container
		static const std::string mServiceStatusRunningStr;			//!> Service status running string container
		static const std::string mServiceStatusFailedStr;			//!> Service status failed string container

		static const std::string mEnabledStr;						//!> Enabled string container
		static const std::string mDisabledStr;						//!> Disabled string container

		static const std::string mNetopeerPathStr;					//!> Netopeer path
		static const std::string mNetopeerCommandStr;				//!> Netopeer start command string container
		static const std::string mQuickFindNetopeerProcessStr;		//!> Netopeer quick find string container
		static const std::string mFindNetopeerProcessStr;			//!> Netopeer find process string container
		static const std::string mServerProcessTxtStr;				//!> Temporary file string container

		static std::string mNetopeerCmdFullStr;

		mutable Mutex mMutex;		//!> Mutex to prevent the service from being interrupted by TIF command requests

		UINT32 mFailedCount;	//!> Failure counter to keep track of the number of times the application failed to start

		bool mReportOnlyOnce; //!> Reports application has failed and auto restart disabled once to prevent filling up the log.

	};
} /* namespace Mplane */

#endif /* _NETOPEER_MONITOR_SERVICE_H_ */
