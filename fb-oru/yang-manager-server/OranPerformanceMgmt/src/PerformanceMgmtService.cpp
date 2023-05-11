/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PerformanceMgmtService.cpp
 * \brief     Virtual interface to configure and measure for transceiver and rx window parameters
 *
 *
 * \details   Virtual interface to configure and measure for transceiver and rx window parameters
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PerformanceMgmtService.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "stringfunc.hpp"
#include "YangUtils.h"
#include "YangParam.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"
#include "Path.h"

#include "RadioDatastoreSysrepo.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const uint16_t PerformanceMgmtService::MAX_LOCAL_MEASUREMENT_INTERVAL_MSEC(5000);

const std::map<IPerformanceMgmt::TransceiverMeasType_T, std::string> PerformanceMgmtService::mTransMeasTypeToStr =
{
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, "RX_POWER"},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, "TX_POPWER"},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, "TX_BIAS_COUNT"},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, "VOLTAGE"},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, "TEMPERATURE"}
};

const std::map<IPerformanceMgmt::TransReportInfoType_T, std::string> PerformanceMgmtService::mTransReportTypeToStr =
{
	{IPerformanceMgmt::TransReportInfoType_T::REPORT_FIRST, "FIRST"},
	{IPerformanceMgmt::TransReportInfoType_T::REPORT_MINIMUM, "MINIMUM"},
	{IPerformanceMgmt::TransReportInfoType_T::REPORT_MAXIMUM, "MAXIMUM"},
	{IPerformanceMgmt::TransReportInfoType_T::REPORT_LATEST, "LATEST"},
	{IPerformanceMgmt::TransReportInfoType_T::REPORT_FREQ_TABLE, "FREQUENCY_TABLE"}
};

const std::map<IPerformanceMgmt::FunctionType_T, std::string> PerformanceMgmtService::mFuncTypeToStr =
{
	{IPerformanceMgmt::FunctionType_T::FUNCTION_RAW, "RAW"},
	{IPerformanceMgmt::FunctionType_T::FUNCTION_LOG10, "LOG_10"}
};

const std::map<IPerformanceMgmt::TransceiverMeasType_T, int> PerformanceMgmtService::mTransMeasTypeToId =
{
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_RX_POWER, 11},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_POWER, 12},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TX_BIAS_COUNT, 13},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_SUPPLY_VOLTAGE, 14},
	{IPerformanceMgmt::TransceiverMeasType_T::SFP_TEMPERATURE, 15}
};

const std::map<IPerformanceMgmt::RxWindowMeasType_T, std::string> PerformanceMgmtService::mRxWindowMeasTypeToStr =
{
	{IPerformanceMgmt::RxWindowMeasType_T::RX_ON_TIME , "RX_ON_TIME"},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_EARLY , "RX_EARLY"},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_LATE , "RX_LATE"},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_CORRUPT , "RX_CORRUPT"},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_DUPL , "RX_DUPL"},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_TOTAL , "RX_TOTAL"}
};

const std::map<IPerformanceMgmt::RxWindowObjectUnitId_T, std::string> PerformanceMgmtService::mRxWindowObjIdToStr =
{
	{IPerformanceMgmt::RxWindowObjectUnitId_T::PER_RU , "RU"},
	{IPerformanceMgmt::RxWindowObjectUnitId_T::PER_TRANSPORT , "TRANSPORT"},
	{IPerformanceMgmt::RxWindowObjectUnitId_T::PER_EAXC_ID , "EAXC_ID"}
};

const std::map<IPerformanceMgmt::RxWindowMeasType_T, int> PerformanceMgmtService::mRxWindowMeasTypeToId =
{
	{IPerformanceMgmt::RxWindowMeasType_T::RX_ON_TIME , 1},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_EARLY , 2},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_LATE , 3},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_CORRUPT , 4},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_DUPL , 5},
	{IPerformanceMgmt::RxWindowMeasType_T::RX_TOTAL , 6}
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PerformanceMgmtService::PerformanceMgmtService(std::vector<int> sfps) : Service(SERVICE_MEDIUM_PRIORITY,
		SMALL_STACK,
		1000, // update stuff every 1000 msec
		"PerformanceMgmtService",
		"PERFMGMT"),
		mSfps(sfps),
		measureNow(false),
		mLocalMeasIntervalmSec(MAX_LOCAL_MEASUREMENT_INTERVAL_MSEC),
		mTransMeasIntervalSec(0),
		mRxWinMeasIntervalSec(0),
		mFileUploadEnable(false),
		mFileUploadIntervalSec(0),
		mFileUploadStartTime(),
		mFileUploadFunc(nullptr),
		mNotificationIntervalSec(0),
		mNotifFunc(nullptr),
		mTransMeasData(),
		mRxWindowMeasData(),
		mTransNotificationData(),
		mTransFileUploadData(),
		mRxWinNotificationData(),
		mRxWinFileUploadData()
{
	registerHalPerformanceMgmt();
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::measTypeToStr(IPerformanceMgmt::TransceiverMeasType_T type, std::string & str)
{
	str = PerformanceMgmtService::mTransMeasTypeToStr.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::measStrToType(std::string str, IPerformanceMgmt::TransceiverMeasType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mTransMeasTypeToStr)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::measTypeToId(IPerformanceMgmt::TransceiverMeasType_T type, int & str)
{
	str = PerformanceMgmtService::mTransMeasTypeToId.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::measIdToType(int str, IPerformanceMgmt::TransceiverMeasType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mTransMeasTypeToId)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::reportTypeToStr(IPerformanceMgmt::TransReportInfoType_T type, std::string & str)
{
	str = PerformanceMgmtService::mTransReportTypeToStr.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::reportStrToType(std::string str, IPerformanceMgmt::TransReportInfoType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mTransReportTypeToStr)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::functionTypeToStr(IPerformanceMgmt::FunctionType_T type, std::string & str)
{
	str = PerformanceMgmtService::mFuncTypeToStr.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::functionStrToType(std::string str, IPerformanceMgmt::FunctionType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mFuncTypeToStr)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowMeasTypeToStr(IPerformanceMgmt::RxWindowMeasType_T type, std::string & str)
{
	str = PerformanceMgmtService::mRxWindowMeasTypeToStr.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowMeasStrToType(std::string str, IPerformanceMgmt::RxWindowMeasType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mRxWindowMeasTypeToStr)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowObjIdToStr(IPerformanceMgmt::RxWindowObjectUnitId_T type, std::string & str)
{
	str = PerformanceMgmtService::mRxWindowObjIdToStr.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowObjIdStrToType(std::string str, IPerformanceMgmt::RxWindowObjectUnitId_T& type)
{
	for (auto & elem : PerformanceMgmtService::mRxWindowObjIdToStr)
	{
		if (elem.second == str)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowMeasTypeToId(IPerformanceMgmt::RxWindowMeasType_T type, int & id)
{
	id = PerformanceMgmtService::mRxWindowMeasTypeToId.at(type);
}

//-------------------------------------------------------------------------------------------------------------
void IPerformanceMgmt::rxWindowMeasIdToType(int id, IPerformanceMgmt::RxWindowMeasType_T& type)
{
	for (auto & elem : PerformanceMgmtService::mRxWindowMeasTypeToId)
	{
		if (elem.second == id)
		{
			type = elem.first;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::isTransMeasActive(TransceiverMeasType_T measType)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) != mTransMeasData.end())
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		return measObjs[0]->isActive();
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasActiveInactive(TransceiverMeasType_T measType, bool activate)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			// Activate/Deactivate the measurement
			measObj->activateDeactivate(activate);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		// Activate/Deactivate the measurement
		for (auto & obj : measObjs)
		{
			obj->activateDeactivate(activate);
		}
	}

	if (activate)
	{
		measureNow = true;
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasFunction(TransceiverMeasType_T measType, FunctionType_T function)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			//Set the transfer function for the measurement
			measObj->setFunction(function);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		//Set the transfer function for the measurement
		for (auto & obj : measObjs)
		{
			obj->setFunction(function);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasReportType(TransceiverMeasType_T measType, TransReportInfoType_T report, bool add)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			//Set the transfer function for the measurement
			measObj->setReportType(report, add);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		//Set the transfer function for the measurement
		for (auto & obj : measObjs)
		{
			obj->setReportType(report, add);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::getTransMeasReportType(TransceiverMeasType_T measType, std::set<TransReportInfoType_T>& report)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) != mTransMeasData.end())
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		measObjs[0]->getReportType(report);
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasBinCount(TransceiverMeasType_T measType, uint16_t binCount)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			//Set the bin count for the measurement
			measObj->setBinCount(binCount);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		//Set the bin count for the measurement
		for (auto & obj : measObjs)
		{
			obj->setBinCount(binCount);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
uint16_t PerformanceMgmtService::getTransMeasBinCount(TransceiverMeasType_T measType)
{
	uint16_t binCount = 0;

	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) != mTransMeasData.end())
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		binCount = measObjs[0]->getBinCount();
	}

	return binCount;
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasLowerLimit(TransceiverMeasType_T measType, double lowerLimit)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			//Set the lower limit for the measurement
			measObj->setLowerLimit(lowerLimit);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		//Set the lower limit for the measurement
		for (auto & obj : measObjs)
		{
			obj->setLowerLimit(lowerLimit);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasUpperLimit(TransceiverMeasType_T measType, double upperLimit)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		for (auto & port : mSfps)
		{
			std::shared_ptr<TransceiverMeasurement> measObj = std::make_shared<TransceiverMeasurement>(port, measType);
			//Set the upper limit for the measurement
			measObj->setUpperLimit(upperLimit);

			mTransMeasData[measType].push_back(measObj);
		}
	}
	else
	{
		// Get the vector of transceiver measurement objects
		std::vector<std::shared_ptr<TransceiverMeasurement>> measObjs = mTransMeasData[measType];

		//Set the upper limit for the measurement
		for (auto & obj : measObjs)
		{
			obj->setUpperLimit(upperLimit);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setTransMeasInterval(uint16_t interval)
{
	mTransMeasIntervalSec = interval;

	unsigned int intervalMSec = mTransMeasIntervalSec * 1000;

	// There should be atleast 3 measurements in a result
	if (intervalMSec/MAX_LOCAL_MEASUREMENT_INTERVAL_MSEC < 3)
	{
		mLocalMeasIntervalmSec = intervalMSec / 3;
	}
	else
	{
		mLocalMeasIntervalmSec = MAX_LOCAL_MEASUREMENT_INTERVAL_MSEC;
	}
}

//-------------------------------------------------------------------------------------------------------------
int PerformanceMgmtService::getNumPorts(void)
{
	return (int)(mSfps.size());
}

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::getTransceiverMeasResult(int portNum, TransceiverMeasType_T measType,
		std::pair<double, std::string>& min, std::pair<double, std::string>& max,
		std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
		std::vector<uint32_t>& table)
{
	// Check if the transceiver measurement type is added to the map
	if (mTransMeasData.find(measType) == mTransMeasData.end())
	{
		return false;
	}

	int portIndex = 0;
	// Check if Sfp port number is present in the list of Sfps
	std::vector<int>::iterator it = std::find(mSfps.begin(), mSfps.end(), portNum);
	if (it == mSfps.end())
	{
		return false;
	}
	else
	{
		portIndex = std::distance(mSfps.begin(), it);
	}

	// Get the transceiver measurement object
	std::shared_ptr<TransceiverMeasurement> measObj = mTransMeasData[measType][portIndex];

	// Return the measurement statistics
	return measObj->getStatsFromActive(min, max, first, latest, table);
}

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::isRxWindowMeasActive(RxWindowMeasType_T measType)
{
	// Check if the Rx window measurement type is added to the map
	if (mRxWindowMeasData.find(measType) != mRxWindowMeasData.end())
	{
		if (mRxWindowMeasData[measType] != nullptr)
		{
			return mRxWindowMeasData[measType]->isActive();
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setRxWindowMeasActiveInactive(RxWindowMeasType_T measType, bool activate)
{
	// Check if the Rx window measurement type is added to the map
	if (mRxWindowMeasData.find(measType) == mRxWindowMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		std::shared_ptr<RxWindowMeasurement> meas = std::make_shared<RxWindowMeasurement>(measType);
		mRxWindowMeasData[measType] = meas;
	}

	mRxWindowMeasData[measType]->activateDeactivate(activate);
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setObjectUnitId(RxWindowMeasType_T measType,
		IPerformanceMgmt::RxWindowObjectUnitId_T id)
{
	// Check if the Rx window measurement type is added to the map
	if (mRxWindowMeasData.find(measType) == mRxWindowMeasData.end())
	{
		// If it is not found, then create a shared pointer for each SFP port and add an object
		// with the received measurement type
		std::shared_ptr<RxWindowMeasurement> meas = std::make_shared<RxWindowMeasurement>(measType);
		mRxWindowMeasData[measType] = meas;
	}

	mRxWindowMeasData[measType]->setObjectUnitId(id);
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::setRxWindowMeasInterval(uint16_t interval)
{
	mRxWinMeasIntervalSec = interval;
}

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::getRxWindowMeasResult(RxWindowMeasType_T measType,	uint64_t& data)
{
	// Check if the transceiver measurement type is added to the map
	if (mRxWindowMeasData.find(measType) == mRxWindowMeasData.end())
	{
		return false;
	}

	// Return the measurement statistics
	return mRxWindowMeasData[measType]->getStatsFromActive(data);

}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::configureNotification(uint16_t interval, IPerformanceMgmt::NotificationCbFunc func)
{
	mNotificationIntervalSec = interval;
	mNotifFunc = func;
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::configureFileUpload(uint16_t interval, IPerformanceMgmt::FileUploadCbFunc func)
{
	mFileUploadIntervalSec = interval;
	mFileUploadFunc = func;
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::enableFileUpload(bool enable)
{
	if (enable != mFileUploadEnable)
	{
		mFileUploadEnable = enable;

		if (enable)
		{
			// Record start time for file upload
			time_t currTime = time(NULL);
			struct tm * timeInfo = localtime(&currTime);
			char buffTimeDate[35];

			// YYYYMMDDHHMM+HHMM
			// Example: 10 September 1972, 14:42:22 London (13:42:22 UTC)
			//          197209101442+0100
			strftime(buffTimeDate, sizeof(buffTimeDate), "%Y%m%d%H%M%z", timeInfo);
			mFileUploadStartTime = buffTimeDate;
		}
	}
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::show()
{
	eventInfo("PerformanceMgmtService::show()");
}

//-------------------------------------------------------------------------------------------------------------
int PerformanceMgmtService::service()
{
	time_t currTime = time(NULL);
	struct tm* timeInfo = localtime(&currTime);

	unsigned timeInSeconds = timeInfo->tm_sec +
			(timeInfo->tm_min * 60) + (timeInfo->tm_hour * 3600);

	// Periodically take local measurement
	if (measureNow ||
	    (timeInSeconds % (mLocalMeasIntervalmSec/1000) == 0))
	{
		measureNow = false;
		takeLocalMeasurement();
	}

	// Check if transceiver measurement interval is over
	if (mTransMeasIntervalSec != 0 && timeInSeconds % mTransMeasIntervalSec == 0)
	{
		if (isAnyTransActive())
		{
			// std::cout << "Calculate transceiver stats" << std::endl;
			calculateTransStatistics();
		}
	}

	// Check if Rx window measurement interval is over
	if (mRxWinMeasIntervalSec != 0 && timeInSeconds % mRxWinMeasIntervalSec == 0)
	{
		if (isAnyRxWinActive())
		{
			// std::cout << "Calculate Rx window stats" << std::endl;
			calculateRxWinStatistics();
		}
	}

	// Check if notification interval is over
	if (timeInSeconds % mNotificationIntervalSec == 0)
	{
		if (isAnyTransActive() || isAnyRxWinActive())
		{
			// Send notification data to caller
			if (mNotifFunc != nullptr)
			{
				mNotifFunc(mTransNotificationData, mRxWinNotificationData);
			}
		}

		// Clear notification data to get next set of measurements
		mTransNotificationData.clear();
		mRxWinNotificationData.clear();
	}

	// Check if file upload interval is over
	if (mFileUploadEnable && (mFileUploadIntervalSec != 0) &&
		(timeInSeconds % mFileUploadIntervalSec == 0))
	{
		std::string endTime;

		// Record the end time for the file upload interval
		time_t currTime = time(NULL);
		struct tm * timeInfo = localtime(&currTime);
		char buffTimeDate[35];

		// YYYYMMDDHHMM+HHMM
		// Example: 10 September 1972, 14:42:22 London (13:42:22 UTC)
		//          197209101442+0100
		strftime(buffTimeDate, sizeof(buffTimeDate), "%Y%m%d%H%M%z", timeInfo);
		endTime = buffTimeDate;

		if (isAnyTransActive() || isAnyRxWinActive())
		{
			// Send file upload data to caller
			if (mFileUploadFunc != nullptr)
			{
				mFileUploadFunc(mTransFileUploadData, mRxWinFileUploadData, mFileUploadStartTime, endTime);
			}
		}

		// Clear file upload data to get next set of measurements
		mTransFileUploadData.clear();
		mRxWinFileUploadData.clear();
		mFileUploadStartTime = endTime;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
// Warning! This function won't do anything as the base class function has not been overridden
void PerformanceMgmtService::doReset()
{

}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::takeLocalMeasurement(void)
{
	for (auto & entry : mTransMeasData)
	{
		std::vector<std::shared_ptr<TransceiverMeasurement>> transMeasObjs = entry.second;

		for (auto & measObj : transMeasObjs)
		{
			measObj->measure();
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::calculateTransStatistics(void)
{
	// Record the start time of the measurement and convert to YANG format of date-and-time
	time_t currTime = time(NULL);
	std::string endTime = YangUtils::getDateTime(currTime);

	for (auto & entry : mTransMeasData)
	{
		std::vector<std::shared_ptr<TransceiverMeasurement>> transMeasObjs = entry.second;

		transMeasData measData;

		for (auto & measObj : transMeasObjs)
		{
			// For each active measurement
			if (measObj->isActive())
			{
				transMeasurement meas;
				std::string startTime;

				// Get port number
				meas.port = measObj->getPortNum();

				// Get the measurement statistics in the current measurement interval and restart the measurement
				measObj->getStatsFromReset(meas.min, meas.max, meas.first, meas.latest, meas.table, startTime, true);

				// Add the measurement to the notification data vector
				measData.startTime = startTime;
				measData.endTime = endTime;
				measData.data.push_back(meas);
			}
		}

		mTransNotificationData[entry.first].push_back(measData);

		// Add the measurement to the file upload data vector
		mTransFileUploadData[entry.first].push_back(measData);
	}
}

//-------------------------------------------------------------------------------------------------------------
void PerformanceMgmtService::calculateRxWinStatistics(void)
{
	// Record the start time of the measurement and convert to YANG format of date-and-time
	time_t currTime = time(NULL);
	std::string endTime = YangUtils::getDateTime(currTime);

	for (auto & measObj : mRxWindowMeasData)
	{
		// For each active measurement
		if (measObj.second->isActive())
		{
			uint64_t meas;
			std::string startTime;

			// Get the measurement statistics in the current measurement interval and restart the measurement
			measObj.second->getStatsFromReset(meas, startTime, true);

			// Add the measurement to the notification data vector
			rxWindowMeasData measData;
			measData.startTime = startTime;
			measData.endTime = endTime;
			measData.data = meas;

			mRxWinNotificationData[measObj.first].push_back(measData);

			// Add the measurement to the file upload data vector
			mRxWinFileUploadData[measObj.first].push_back(measData);
		}
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::isAnyTransActive(void)
{
	bool active = false;

	for (auto & entry : mTransMeasData)
	{
		std::vector<std::shared_ptr<TransceiverMeasurement>> transMeasObjs = entry.second;

		for (auto & measObj : transMeasObjs)
		{
			if (measObj->isActive())
			{
				active = true;
				break;
			}
		}

		if (active)
		{
			break;
		}
	}

	return active;
}

//-------------------------------------------------------------------------------------------------------------
bool PerformanceMgmtService::isAnyRxWinActive(void)
{
	bool active = false;

	for (auto & measObj : mRxWindowMeasData)
	{
		if (measObj.second->isActive())
		{
			active = true;
			break;
		}
	}

	return active;
}

static void halPerfMgmtCallback (const halmplane_oran_perf_meas_t *meas, void *store) {
	printf("Received RSSI %lf \n", meas->rssi);
}

void PerformanceMgmtService::registerHalPerformanceMgmt() {
    halmplane_registerOranPerfMeasCallback(&halPerfMgmtCallback);
}
