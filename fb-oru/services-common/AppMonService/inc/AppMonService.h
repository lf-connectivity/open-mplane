/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppMonService.h
 * \brief     Application Monitoring service
 *
 *
 * \details   Responsible for monitoring an application.
 *
 */

#ifndef _APP_MONITOR_SERVICE_H_
#define _APP_MONITOR_SERVICE_H_

#include "Mutex.h"
#include "Service.h"

#include "IAppMonService.h"

namespace Mplane
{
	class AppMonService : public Service, public IAppMonService
	{
	public:
		AppMonService(const std::string & path,
		              const std::string & appCmd,
		              UINT32 monIntervalMs);

		virtual ~AppMonService();

		virtual ReturnType::State setOptions(const std::string & optionsStr) override;
		virtual ReturnType::State clearOptions(void) override;

		virtual ReturnType::State startService(void) override;		//!> Start the service
		virtual ReturnType::State restartService(void) override;		//!> Restart the service
		virtual ReturnType::State stopService(void) override;		//!> Stop the service

		virtual IAppMonService::serviceStatus_T getServiceStatus(void) override;		//!> Get the current service state
		virtual std::string getServiceStatusString(void) override;	//!> Get the current service state

		virtual void setMonitorServiceState(IAppMonService::enableDisable_T enableDisableMonitor) override;	//!> Enable/Disable the monitor service
		virtual IAppMonService::enableDisable_T getMonitorServiceState(void) override;						//!> Get the state of the monitor service
		virtual std::string getMonitorServiceStateString(void) override;						//!> Get the state of the monitor service

		virtual void setAutoRestart(IAppMonService::enableDisable_T enableDisableAutoRestart) override;	//!> Enable/Disable the application auto restart
		virtual IAppMonService::enableDisable_T getAutoRestart(void) override;							//!> Get Enable/Disable auto restart state
		virtual std::string getAutoRestartString(void) override;							//!> Get Enable/Disable auto restart state

		virtual UINT32 getAppFailedCount(void) override;		//!> Get the application failed count
		virtual void clrAppFailedCount(void) override;		//!> Clear the application failed count

	protected:
		/**
		 * Method defined by the Loggable interface must be implemented by all
		 * object to force the display of the objects current status.
		 */
		virtual void show() override;

		/**
		 * Method that MUST be implemented by the inheriting service. The work done
		 * by the service, is implemented by this method.
		 * @return
		 */
		virtual int service() override;

		/**
		 * Method called as a result of the radio control process calling reset
		 * in the service. By default the base class implementation does nothing.
		 */
		virtual void doReset() override;

	private:
		virtual ReturnType::State cleanupApp(const std::string & funcStr) override;	//!> Called to cleanup the application

		ReturnType::State startApp(const std::string & funcStr);	//!> Start the application
		bool isAppRunning(const std::string & funcStr);				//!> Check if the application is running

		static const std::string mServiceStatusStoppedStr;		//!> Service status stopped string container
		static const std::string mServiceStatusRunningStr;		//!> Service status running string container
		static const std::string mServiceStatusFailedStr;		//!> Service status failed string container

		static const std::string mEnabledStr;					//!> Enabled string container
		static const std::string mDisabledStr;					//!> Disabled string container

		IAppMonService::serviceStatus_T mServiceState;			//!> Internal service state member variable
		IAppMonService::enableDisable_T mMonServiceState;		//!> Internal monitor service state member variable
		IAppMonService::enableDisable_T mAutoRestartApp;	//!> Internal auto restart process member variable

		const std::string mAppPathStr;							//!> Application path
		const std::string mAppCmdStr;							//!> Application command string container
		std::string mAppOptionsStr;								//!> Application options string container
		const std::string mAppProcessTxtStr;					//!> Application file string container
		const std::string mFindAppProcessStr;					//!> Application find process string container
		const std::string mQuickFindAppProcessStr;				//!> Application quick find string container

		mutable Mutex mMutex;		//!> Mutex to prevent the service from being interrupted by TIF command requests

		UINT32 mFailedCount;	//!> Failure counter to keep track of the number of times that the application process fails

		bool mReportOnlyOnce; //!> Reports application has failed and auto restart is disabled only once (Prevents filling up the log).

	};
} /* namespace Mplane */

#endif /* _APP_MONITOR_SERVICE_H_ */
