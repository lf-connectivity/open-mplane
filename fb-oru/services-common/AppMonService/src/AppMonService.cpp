/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppMonService.cpp
 * \brief     Application Monitoring service
 *
 *
 * \details   Responsible for monitoring an external application.
 *
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

#include "AppMonService.h"

#ifdef OFF_TARGET
#define DISABLE_MONITORING
#endif

using namespace Mplane;

const std::string AppMonService::mServiceStatusStoppedStr = "Stopped";
const std::string AppMonService::mServiceStatusRunningStr = "Running";
const std::string AppMonService::mServiceStatusFailedStr = "Failed";

const std::string AppMonService::mEnabledStr = "Enabled";
const std::string AppMonService::mDisabledStr = "Disabled";

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AppMonService::AppMonService(const std::string & appPath,
                             const std::string & appCmd,
                             UINT32 monIntervalMs)
	: Service(SERVICE_LOW_PRIORITY,
	          SMALL_STACK,
	          monIntervalMs, // update stuff every monIntervalMs
	          appCmd.c_str(),
	          "APPMON")
	, mServiceState(IAppMonService::serviceStatus_T::STOPPED)
	, mMonServiceState(IAppMonService::enableDisable_T::ENABLE)
	, mAutoRestartApp(IAppMonService::enableDisable_T::DISABLE)
	, mAppPathStr(appPath)
	, mAppCmdStr(appCmd)
	, mAppOptionsStr()
	, mAppProcessTxtStr("/tmp/" + mAppCmdStr + "Process.txt")
	, mFindAppProcessStr("ps -aux | grep \"" + mAppCmdStr + "\" > " + mAppProcessTxtStr)
	, mQuickFindAppProcessStr("ps -aux | grep \"" + mAppCmdStr + "\" -c > " + mAppProcessTxtStr)
	, mMutex()
	, mFailedCount(0)
	, mReportOnlyOnce(false)
{
	if (mAppCmdStr.empty())
	{
		throw std::runtime_error("AppMonService- Command not specified");
	}
	else if (mAppPathStr.empty())
	{
		throw std::runtime_error("AppMonService[" + mAppCmdStr + "] - Path not specified");
	}
}

//-------------------------------------------------------------------------------------------------------------
AppMonService::~AppMonService()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::setOptions(const std::string & optionsStr)
{
	mAppOptionsStr = optionsStr;
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::clearOptions(void)
{
	mAppOptionsStr = "";
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::startService(void)
{
	ReturnType::State result = ReturnType::RT_ERROR;
	const std::string funcStr = "startService";

	if(mServiceState == IAppMonService::serviceStatus_T::RUNNING)
	{
		// If we are already running
		result = ReturnType::RT_OK;
	}

	// Start the application
	else if ((startApp(funcStr) == ReturnType::RT_OK) && (isAppRunning(funcStr)))
	{
		mServiceState = IAppMonService::serviceStatus_T::RUNNING;
		result = ReturnType::RT_OK;
	}
	else
	{
		eventError("AppMonService::%s() - Failed to start %s application",
				funcStr.c_str(), mAppCmdStr.c_str());
		mServiceState = IAppMonService::serviceStatus_T::FAILED;
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::restartService(void)
{
	ReturnType::State result = ReturnType::RT_ERROR;
	const std::string funcStr = "restartService";

	result = stopService();
	if (result == ReturnType::RT_OK)
	{
		result = startService();
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::stopService(void)
{
	ReturnType::State result = ReturnType::RT_OK;
	const std::string funcStr = "stopService";

	if(mServiceState == IAppMonService::serviceStatus_T::STOPPED)
	{
		// If we are already stopped
		result = ReturnType::RT_OK;
	}

	// Check if the application is running
	else if(isAppRunning(funcStr))
	{
		// Determine the applications task ID
		int processFindReturn = system(mFindAppProcessStr.c_str());

		// Check to see if the command was successful
		if(0 == processFindReturn)
		{
			// Command was successful.
			std::ifstream appProcessTxtFile(mAppProcessTxtStr.c_str());
			if(appProcessTxtFile.is_open())
			{
				// Extract the task ID from the generated file
				std::string processStr = "\0";
				std::getline(appProcessTxtFile, processStr);
				std::string processNumStr = processStr.substr(10, 14);

				// Kill the process
				std::string killCommand = "kill " + processNumStr;
				int killProcessReturn = system(killCommand.c_str());
				if(0 == killProcessReturn)
				{
					cleanupApp(funcStr);

					// Kill successfully issued
					mServiceState = IAppMonService::serviceStatus_T::STOPPED;

					result = ReturnType::RT_OK;
				}
				else
				{
					// Kill failed
					eventError("AppMonService::stopService() - Failed to kill %s process",
							mAppCmdStr.c_str());
					result = ReturnType::RT_ERROR;
				}
			}
			else
			{
				// Could not open process file
				eventError("AppMonService::stopService() - Could not open %s file",
						mAppProcessTxtStr.c_str());
				result = ReturnType::RT_ERROR;
			}

			// Clean up after ourselves
			appProcessTxtFile.close();
		}
		else
		{
			// Find application process failed
			eventError("AppMonService::stopService() - Unable to find %s file",
					mAppProcessTxtStr.c_str());
			result = ReturnType::RT_ERROR;
		}
	}
	else
	{
		// Process already dead!
		eventError("AppMonService::stopService() - %s process already dead!",
				mAppCmdStr.c_str());
		mServiceState = IAppMonService::serviceStatus_T::STOPPED;

		result = ReturnType::RT_OK;
	}

	// Reset the report only once to we will see if it happens again after a stop.
	mReportOnlyOnce = false;

	return result;
}

//-------------------------------------------------------------------------------------------------------------
IAppMonService::serviceStatus_T AppMonService::getServiceStatus(void)
{
	return mServiceState;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppMonService::getServiceStatusString(void)
{
	std::string state;

	switch(mServiceState)
	{
	case STOPPED:
		state = mServiceStatusStoppedStr;
		break;
	case RUNNING:
		state = mServiceStatusRunningStr;
		break;
	case FAILED:
		state = mServiceStatusFailedStr;
		break;
	default:
		state = mServiceStatusFailedStr;
		break;
	}
	return state;
}

//-------------------------------------------------------------------------------------------------------------
void AppMonService::setMonitorServiceState(enableDisable_T enableDisableMonitor)
{
	mMonServiceState = enableDisableMonitor;
}

//-------------------------------------------------------------------------------------------------------------
IAppMonService::enableDisable_T AppMonService::getMonitorServiceState(void)
{
	return mMonServiceState;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppMonService::getMonitorServiceStateString(void)
{
	return (mMonServiceState == IAppMonService::enableDisable_T::ENABLE ? mEnabledStr : mDisabledStr);
}

//-------------------------------------------------------------------------------------------------------------
void AppMonService::setAutoRestart(enableDisable_T enableDisableAutoRestart)
{
	mAutoRestartApp = enableDisableAutoRestart;
}

//-------------------------------------------------------------------------------------------------------------
IAppMonService::enableDisable_T AppMonService::getAutoRestart(void)
{
	return mAutoRestartApp;
}

//-------------------------------------------------------------------------------------------------------------
std::string AppMonService::getAutoRestartString(void)
{
	return (mAutoRestartApp == IAppMonService::enableDisable_T::ENABLE ? mEnabledStr : mDisabledStr);
}

//-------------------------------------------------------------------------------------------------------------
UINT32 AppMonService::getAppFailedCount(void)
{
	return mFailedCount;
}

//-------------------------------------------------------------------------------------------------------------
void AppMonService::clrAppFailedCount(void)
{
	mFailedCount = 0;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void AppMonService::show()
{
	eventInfo("AppMonService::show()");
}

//-------------------------------------------------------------------------------------------------------------
int AppMonService::service()
{
	const std::string funcStr = "service";

	//eventInfo("AppMonService::service() - STATE: %s", getMonitorServiceStateString());

#ifndef DISABLE_MONITORING
	Mutex::Lock lock(mMutex) ; // Protect from the Test Interface

	if(mMonServiceState == IAppMonService::enableDisable_T::ENABLE)
	{
		// Check if the application is running
		if(isAppRunning(funcStr))
		{
			// Application is running
			mServiceState = IAppMonService::serviceStatus_T::RUNNING;
		}

		// Application has stopped. Should we restart?
		else if(mAutoRestartApp == IAppMonService::enableDisable_T::ENABLE)
		{
			eventError("AppMonService::service() - %s not running. Auto restart.",
					mAppCmdStr.c_str());

			cleanupApp(funcStr);

			// Increment the failed counter
			mFailedCount++;

			// Try and start the application again
			if (startApp(funcStr) != ReturnType::RT_OK)
			{
				eventError("AppMonService::service() - %s restart failed in system command. Retry next service.",
						mAppCmdStr.c_str());
				mServiceState = IAppMonService::serviceStatus_T::FAILED;
			}
		}
		else
		{
			if(mReportOnlyOnce == false)
			{
				eventError("AppMonService::service() - %s not running. Auto restart disabled.",
						mAppCmdStr.c_str());
				mReportOnlyOnce = true;
			}

			mServiceState = IAppMonService::serviceStatus_T::FAILED;
		}
	}
#endif // DISABLE_MONITORING

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
void AppMonService::doReset()
{
	eventInfo("AppMonService::doReset()");
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::cleanupApp(const std::string & funcStr)
{
	// Cleanup application
	eventInfo("AppMonService::%s() - cleanupApp", funcStr.c_str());
	return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AppMonService::startApp(const std::string & funcStr)
{
	ReturnType::State result = ReturnType::RT_OK;

	std::string appFullCmdStr = mAppPathStr + "/" + mAppCmdStr;
	if (!mAppOptionsStr.empty())
		appFullCmdStr += " " + mAppOptionsStr;

// ToDo: Applications do not run in host build - permission denied
	//std::cerr << "appFullCmdStr: " << appFullCmdStr << std::endl;
	if (system(appFullCmdStr.c_str()) != 0)
	{
		result = ReturnType::RT_ERROR;
	}

	return result;
}

//-------------------------------------------------------------------------------------------------------------
bool AppMonService::isAppRunning(const std::string & funcStr)
{
	bool success = false;

	// Run system command to generate a text file containing the number of
	// processes running containing the application name.
	if (system(mQuickFindAppProcessStr.c_str()) == 0)
	{
		// System command success

		// Check the process file exists.
		std::ifstream appProcessTxtFile(mAppProcessTxtStr.c_str());
		if (appProcessTxtFile.is_open())
		{
			std::string numberFoundStr = "\0";
			std::getline(appProcessTxtFile, numberFoundStr);
			UINT64 numberFound = std::strtoul(numberFoundStr.c_str(), 0, 10);

			// If the process is running then we will find two entries; the app process and the grep for it!
			if (numberFound > 2)
			{
				success = true;
			}
		}
		else
		{
			// Unable to open file to see if the process is running.
			eventError("AppMonService::%s() - Unable to open %s file",
					funcStr.c_str(), mAppProcessTxtStr.c_str());
		}

		// Clean up after ourselves. Close the open file.
		appProcessTxtFile.close();
	}
	else
	{
		// System command failed
		eventError("AppMonService::%s() - %s system command failure",
				funcStr.c_str(), mAppCmdStr.c_str());
	}

	// Remove the file we created
	std::remove(mAppProcessTxtStr.c_str());

	return success;
}
