/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      INetopeerMonService.cpp
 * \brief     Netopeer Monitoring service
 *
 *
 * \details   Responsible for monitoring the Netopeer application .
 *
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

#include "IAppOptions.h"

#include "NetopeerMonService.h"

#ifdef OFF_TARGET
#define DISABLE_NETOPEER_MONITORING
#endif

using namespace Mplane;

#define NETOPEER_CMD   "netopeer2-server"

const std::string NetopeerMonService::mServiceStatusStoppedStr = "Stopped";
const std::string NetopeerMonService::mServiceStatusRunningStr = "Running";
const std::string NetopeerMonService::mServiceStatusFailedStr = "Failed";

const std::string NetopeerMonService::mEnabledStr = "Enabled";
const std::string NetopeerMonService::mDisabledStr = "Disabled";

const std::string NetopeerMonService::mNetopeerPathStr = NETOPEER_PATH;
const std::string NetopeerMonService::mNetopeerCommandStr = mNetopeerPathStr + "/" NETOPEER_CMD;
std::string NetopeerMonService::mNetopeerCmdFullStr;

const std::string NetopeerMonService::mServerProcessTxtStr = "/tmp/" NETOPEER_CMD "Process.txt";
const std::string NetopeerMonService::mFindNetopeerProcessStr = "ps -aux | grep \"" NETOPEER_CMD "\" > " + mServerProcessTxtStr;
const std::string NetopeerMonService::mQuickFindNetopeerProcessStr = "ps -aux | grep \"" NETOPEER_CMD "\" -c > " + mServerProcessTxtStr;

// ====================================================================================================
Mplane::NetopeerMonService::NetopeerMonService()
	: Service(SERVICE_LOW_PRIORITY,
	          SMALL_STACK,
	          1000, // update stuff every 1000 msec
	          "NetopeerMonService",
	          "NETOPEER")
	, mServiceState(INetopeerMonService::serviceStatus_T::STOPPED)
	, mMonitorServiceState(INetopeerMonService::enableDisable_T::ENABLE)
	, mAutoRestartProcess(INetopeerMonService::enableDisable_T::DISABLE)
	, mFailedCount(0)
	, mReportOnlyOnce(false)
{
	std::string appPath(NETOPEER_PATH);
	if (appPath.empty())
	{
		std::string errorStr = "NETOPEER_PATH [" + appPath + "] must be set in the projects CMakeLists.txt file";
		throw std::runtime_error(errorStr);
	}
}

// ====================================================================================================
Mplane::NetopeerMonService::~NetopeerMonService()
{
}

// ====================================================================================================
ReturnType::State Mplane::NetopeerMonService::startService(void)
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	if(mServiceState == serviceStatus_T::RUNNING)
	{
		// If we are already running
		returnValue = ReturnType::RT_OK;
	}
	else
	{
// ToDo: netopeer does not run in host build - permission denied
		DataVariant netopeerDbgOption(IAppOptions::getInstance()->getOption("netopeerdbg"));
		std::string netopeerDbgOptionStr = netopeerDbgOption.toString();
		netopeerDbgOption.setLimits("0", "2", "1");
		if (netopeerDbgOption.checkLimits())
		{
			// Remove leading zeros, unless 0
			UINT32 value = std::stoul(netopeerDbgOptionStr);
			netopeerDbgOptionStr = std::to_string(value);
		}
		else
		{
			// DEFAULT
			netopeerDbgOptionStr = "1";
		}
		mNetopeerCmdFullStr = mNetopeerCommandStr + " -v " + netopeerDbgOptionStr;
		//std::cerr << "mNetopeerCmdFullStr: " << mNetopeerCmdFullStr << std::endl;
		int processStartReturn = system(mNetopeerCmdFullStr.c_str());

		// Check to see if the command was successful
		if(0 == processStartReturn)
		{
			int processRunningReturn = system(mQuickFindNetopeerProcessStr.c_str());

			// Check to see if the command was successful
			if(0 == processRunningReturn)
			{
				std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

				if(serverProcessTxtFile.is_open())
				{
					std::string numberFoundStr = "\0";

					std::getline(serverProcessTxtFile, numberFoundStr);

					unsigned long int numberFound = std::strtoul(numberFoundStr.c_str(), 0, 10);

					// If the process is running then we will find two entries - the process and the grep for it!
					if(numberFound > 2)
					{
						// 2 found, so the process is running
						mServiceState = serviceStatus_T::RUNNING;

						returnValue = ReturnType::RT_OK;
					}
					else
					{
						// Process has not started
						eventError("NetopeerMonService::startService() - start process failed!");

						mServiceState = serviceStatus_T::FAILED;

						returnValue = ReturnType::RT_ERROR;
					}
				}
				else
				{
					// Could not write file
					eventError("NetopeerMonService::startService() - failed to write tmp file!");

					mServiceState = serviceStatus_T::FAILED;

					returnValue = ReturnType::RT_ERROR;
				}

				// Clean up after ourselves.
				serverProcessTxtFile.close();
			}
			else
			{
				// System command to start process failed
				eventError("NetopeerMonService::startService() - quick find to confirm start failed");

				mServiceState = serviceStatus_T::FAILED;

				returnValue = ReturnType::RT_ERROR;
			}

			// Remove the file we created
			std::remove(mServerProcessTxtStr.c_str());
		}
		else
		{
			// System command to start process failed
			eventError("NetopeerMonService::startService() - system command to start process failed");

			mServiceState = serviceStatus_T::FAILED;

			returnValue = ReturnType::RT_ERROR;
		}

		// Remove the file we created
		std::remove(mServerProcessTxtStr.c_str());
	}

	return returnValue;
}

// ====================================================================================================
ReturnType::State Mplane::NetopeerMonService::restartService(void)
{
	ReturnType::State stopReturn = stopService();

	if(stopReturn == ReturnType::RT_OK)
	{
		ReturnType::State startReturn = startService();

		if(startReturn == ReturnType::RT_OK)
		{
			return ReturnType::RT_OK;
		}
		else
		{
			eventError("NetopeerMonService::restartService() - failed to start process");
		}
	}
	else
	{
		eventError("NetopeerMonService::restartService() - failed to stop process");
	}
	return ReturnType::RT_ERROR;
}

// ====================================================================================================
ReturnType::State Mplane::NetopeerMonService::stopService(void)
{
	ReturnType::State returnValue = ReturnType::RT_OK;

	if(mServiceState == serviceStatus_T::STOPPED)
	{
		// If we are already running
		returnValue = ReturnType::RT_OK;
	}
	else
	{
		int processRunningReturn = system(mQuickFindNetopeerProcessStr.c_str());

		// Check to see if the command was successful
		if(0 == processRunningReturn)
		{
			std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

			if(serverProcessTxtFile.is_open())
			{
				std::string numberFoundStr = "\0";

				std::getline(serverProcessTxtFile, numberFoundStr);

				unsigned long int numberFound = std::strtoul(numberFoundStr.c_str(), 0, 10);

				// If the process is running then we will find two entries - the process and the grep for it!
				if(numberFound > 2)
				{
					int processFindReturn = system(mFindNetopeerProcessStr.c_str());

					// Check to see if the command was successful
					if(0 == processFindReturn)
					{
						std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

						if(serverProcessTxtFile.is_open())
						{
							std::string processStr = "\0";

							std::getline(serverProcessTxtFile, processStr);

							std::string processNumStr = processStr.substr(10,14);

							std::string killCommand = "kill " + processNumStr;

							int killProcessReturn = system(killCommand.c_str());

							if(0 == killProcessReturn)
							{
								// netopeer2 stopped removing possible corrupted sysrepo files from shared memory
								eventInfo("NetopeerMonService::stopService() - Removing sysrepo files from shared memory folder");
								system("rm -rf /dev/shm/sr_*");
								system("rm -rf /dev/shm/srsub_*");

								// Kill successfully issued
								mServiceState = serviceStatus_T::STOPPED;

								returnValue = ReturnType::RT_OK;
							}
							else
							{
								// Kill failed
								eventError("NetopeerMonService::stopService() - process kill failed");
								returnValue = ReturnType::RT_ERROR;
							}
						}
						else
						{
							// Could not open process file
							eventError("NetopeerMonService::stopService() - could not open process file");
							returnValue = ReturnType::RT_ERROR;
						}

						// Clean up after ourselves
						serverProcessTxtFile.close();
					}
					else
					{
						// Find netopeer 2 process failed
						eventError("NetopeerMonService::stopService() - find netopeer 2 process failed");
						returnValue = ReturnType::RT_ERROR;
					}

					// Remove the file we created
					std::remove(mServerProcessTxtStr.c_str());
				}
				else
				{
					// Process is already dead!
					eventError("NetopeerMonService::stopService() - Process is already dead!");
					mServiceState = serviceStatus_T::STOPPED;

					returnValue = ReturnType::RT_OK;
				}
			}
			else
			{
				// Cannot open quick find file
				eventError("NetopeerMonService::stopService() - quick find could not open process file");
				returnValue = ReturnType::RT_ERROR;
			}

			// Close the file we opened
			serverProcessTxtFile.close();
		}
		else
		{
			// Quick find system command failed
			eventError("NetopeerMonService::stopService() - quick find system command failed");
			returnValue = ReturnType::RT_ERROR;
		}

		// Remove the file we created
		std::remove(mServerProcessTxtStr.c_str());
	}

	// Reset the report only once to we will see if it happens again after a stop.
	mReportOnlyOnce = false;

	return returnValue;
}

// ====================================================================================================
INetopeerMonService::serviceStatus_T Mplane::NetopeerMonService::getServiceStatus(void)
{
	return mServiceState;
}

// ====================================================================================================
std::string Mplane::NetopeerMonService::getServiceStatusString(void)
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

// ====================================================================================================
void Mplane::NetopeerMonService::setMonitorServiceState(enableDisable_T enableDisableMonitor)
{
	mMonitorServiceState = enableDisableMonitor;
}

// ====================================================================================================
INetopeerMonService::enableDisable_T Mplane::NetopeerMonService::getMonitorServiceState(void)
{
	return mMonitorServiceState;
}

// ====================================================================================================
std::string Mplane::NetopeerMonService::getMonitorServiceStateString(void)
{
	return (mMonitorServiceState == enableDisable_T::ENABLE ? mEnabledStr : mDisabledStr);
}

// ====================================================================================================
void Mplane::NetopeerMonService::show()
{
	eventInfo("NetopeerMonService::show()");
}

// ====================================================================================================
int Mplane::NetopeerMonService::service()
{
	Mutex::Lock lock(mMutex) ; // Protect from the Test Interface

#ifndef DISABLE_NETOPEER_MONITORING
	if(mMonitorServiceState == enableDisable_T::ENABLE)
	{
		//eventInfo("NetopeerMonService::service() - mMonitorServiceState = ENABLE");

		int processRunningReturn = system(mQuickFindNetopeerProcessStr.c_str());

		// Check to see if the command was successful
		if(0 == processRunningReturn)
		{
			std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

			if(serverProcessTxtFile.is_open())
			{
				std::string numberFoundStr = "\0";

				std::getline(serverProcessTxtFile, numberFoundStr);

				unsigned long int numberFound = std::strtoul(numberFoundStr.c_str(), 0, 10);

				// If the process is running then we will only find, that's right more thats 2 entries!
				if(numberFound > 2)
				{
					// more than 2 found, so the process is running
					//eventInfo("NetopeerMonService::service() - entries found = %lu", numberFound);
					//eventInfo("NetopeerMonService::service() - entries found = %s", numberFoundStr.c_str());

					mServiceState = serviceStatus_T::RUNNING;
				}
				else
				{
					// Less than 2 found, so the process has stopped
					if(mAutoRestartProcess == enableDisable_T::ENABLE)
					{
						// netopeer2 stopped, removing possible corrupted sysrepo files from shared memory
						eventInfo("NetopeerMonService::service() - Removing sysrepo files from shared memory folder");
						system("rm -rf /dev/shm/sr_*");
						system("rm -rf /dev/shm/srsub_*");

						//eventInfo("NetopeerMonService::service() - mAutoRestartProcess = ENABLE");
						eventError("NetopeerMonService::service() - netopeer2 is not running, attempting to restart.");

						// Increment the failed counter
						mFailedCount ++;

						// Try and start the process again
						int processTryAgainReturn = system(mNetopeerCmdFullStr.c_str());

						if(0 == processTryAgainReturn)
						{
							// Command succeeded
						}
						else
						{
							// Command failed
							eventError("NetopeerMonService::service() - Attempt to restart has failed in system command. Will retry on next service.");

							mServiceState = serviceStatus_T::FAILED;
						}
					}
					else
					{
						if(mReportOnlyOnce == false)
						{
							eventError("NetopeerMonService::service() - Netopeer2 not running. Auto restart disabled.");

							mReportOnlyOnce = true;
						}

						mServiceState = serviceStatus_T::FAILED;
					}
				}
			}
			else
			{
				// Unable to open file to see if the process is running.
				eventError("NetopeerMonService::service() - Unable to open file to see if the netopeer2 process is running.");
			}

			// Clean up after ourselves. Close the open file.
			serverProcessTxtFile.close();
		}
		else
		{
			// Unable to do system write to check if the process is running.
			eventError("NetopeerMonService::service() - Unable to do system write to check if the netopeer2 process is running");
		}

		// Clean up after ourselves. Remove the file we tried to create
		std::remove(mServerProcessTxtStr.c_str());
	}
	else
	{
		//eventInfo("NetopeerMonService::service() - mMonitorServiceState = DISABLE");
	}
#endif // DISABLE_NETOPEER_MONITORING

	return 0;
}

// ====================================================================================================
// Warning! This function won't do anything as the base class function has not been overridden
void Mplane::NetopeerMonService::doReset()
{
}

// ====================================================================================================
void Mplane::NetopeerMonService::setAutoRestart(enableDisable_T enableDisableAutoRestart)
{
	mAutoRestartProcess = enableDisableAutoRestart;
}

// ====================================================================================================
INetopeerMonService::enableDisable_T Mplane::NetopeerMonService::getAutoRestart(void)
{
	return mAutoRestartProcess;
}

// ====================================================================================================
std::string Mplane::NetopeerMonService::getAutoRestartString(void)
{
	return (mAutoRestartProcess == enableDisable_T::ENABLE ? mEnabledStr : mDisabledStr);
}

// ====================================================================================================
UINT32 Mplane::NetopeerMonService::getAppFailedCount(void)
{
	return mFailedCount;
}

// ====================================================================================================
void Mplane::NetopeerMonService::clrAppFailedCount(void)
{
	mFailedCount = 0;
}
