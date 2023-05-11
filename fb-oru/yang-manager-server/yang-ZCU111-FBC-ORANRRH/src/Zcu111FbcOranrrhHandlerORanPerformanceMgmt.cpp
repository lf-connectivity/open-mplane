/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanPerformanceMgmt.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "stringfunc.hpp"
#include "Path.h"
#include "IAppOptions.h"
#include "INetworkingService.h"

#include "ILoggable.h"
#include "ILeafContainer.h"
#include "IBootEnv.h"

#include "ISftpMgr.h"

#include "XpathUtils.h"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangUserAuth.h"
#include "YangMgrServer.h"
#include "YangParamUtils.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanPerformanceMgmt.h"
#include "Zcu111FbcOranrrhHandlerORanFileManagement.h"
#include "Zcu111FbcOranrrhHandlerIetfHardware.h"

// for debug
#include "CdiNetworkingService.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const uint16_t Zcu111FbcOranrrhHandlerORanPerformanceMgmt::MAX_BIN_COUNT(100);
const uint16_t Zcu111FbcOranrrhHandlerORanPerformanceMgmt::DEFAULT_MEASUREMENT_INTERVAL_SEC(20);
const uint16_t Zcu111FbcOranrrhHandlerORanPerformanceMgmt::DEFAULT_NOTIFICATION_INTERVAL_SEC(60);
const uint16_t Zcu111FbcOranrrhHandlerORanPerformanceMgmt::DEFAULT_FILE_UPLOAD_INTERVAL_SEC(120);
const uint16_t Zcu111FbcOranrrhHandlerORanPerformanceMgmt::PM_FILE_THRESHOLD(50);

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanPerformanceMgmt::Zcu111FbcOranrrhHandlerORanPerformanceMgmt(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: YangHandlerSysrepo("o-ran-performance-management", moduleMgr, "Zcu111FbcOranrrhHandlerORanPerformanceMgmt")
	, mCallback(std::make_shared<SysrepoGetitemsCallback>(path("performance-measurement-objects")))
	, mPerfMgmt(IPerformanceMgmt::singleton())
    , mInterfaces()
    , mNotificationInterval(DEFAULT_NOTIFICATION_INTERVAL_SEC)
    , mFileUploadInterval(DEFAULT_FILE_UPLOAD_INTERVAL_SEC)
    , mSftpUploadData()
{
#ifdef TEST_BB_ON_CDI
	const std::string itfc("ethcdi") ;
#else
	const std::string itfc("ethbb") ;
#endif
	std::string ethbbInterface = IAppOptions::getInstance()->getOption(itfc).toString() ;

	// Network services access
	auto ns(INetworkingService::singleton(ethbbInterface));
	auto policy(ns->getNetAddrPolicy());

	int interfaceNum = policy->interfacePort();

	// Ethbb interface is linked to SFP0
	mEthPortToSFPPort[interfaceNum] = 0;
}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanPerformanceMgmt::~Zcu111FbcOranrrhHandlerORanPerformanceMgmt()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanPerformanceMgmt::initialise()
{
	// daisychain the initialisations
	if (!this->YangHandlerSysrepo::initialise())
		return false ;

//  +--rw performance-measurement-objects
//	 +--rw enable-SFTP-upload?               boolean
//	 +--rw enable-random-file-upload?        boolean
//	 +--rw remote-SFTP-uploads* [remote-SFTP-upload-path]
//	 |  +--rw remote-SFTP-upload-path  inet:uri
//	 |  +--rw (credentials)?
//	 |     +--:(password)
//	 |     |  +--rw password!
//	 |     |  |  +--rw password  string
//	 |     |  +--rw server
//	 |     |     +--rw keys* [algorithm]
//	 |     |        +--rw algorithm   asymmetric-key-algorithm-ref
//	 |     |        +--rw public-key? binary
//	 |     +--:(certificate)
//	 |        +--rw certificate!
//	 +--rw transceiver-measurement-interval? uint16
//	 +--rw rx-window-measurement-interval?   uint16
//	 +--rw notification-interval?            uint16
//	 +--rw file-upload-interval?             uint16
//	 +--ro max-bin-count                     uint16
//	 +--rw transceiver-measurement-objects* [measurement-object]
//	 |  +--rw measurement-object              enumeration
//	 |  +--rw active?                         boolean
//	 |  +--rw report-info*                    enumeration
//	 |  +--rw object-unit                     enumeration
//	 |  +--rw function?                       enumeration
//	 |  +--rw bin-count?                      uint16
//	 |  +--rw lower-bound?                    decimal64
//	 |  +--rw upper-bound?                    decimal64
//	 |  +--ro transceiver-measurement-result* [object-unit-id]
//	 |     +--ro object-unit-id  leafref
//	 |     +--ro min
//	 |     |  +--ro value? decimal64
//	 |     |  +--ro time?  yang-types:date-and-time
//	 |     +--ro max
//	 |     |  +--ro value? decimal64
//	 |     |  +--ro time?  yang-types:date-and-time
//	 |     +--ro first
//	 |     |  +--ro value? decimal64
//	 |     |  +--ro time?  yang-types:date-and-time
//	 |     +--ro latest
//	 |     |  +--ro value? decimal64
//	 |     |  +--ro time?  yang-types:date-and-time
//	 |     +--ro frequeny-table* uint32


	populateInterfaces();

	for (auto & type : PerformanceMgmtService::mTransMeasTypeToStr)
	{
		createTransReadWriteData(type.first);
	}

	for (auto & type : PerformanceMgmtService::mRxWindowMeasTypeToStr)
	{
		createRxWinReadWriteData(type.first);
	}

	mPerfMgmt->setTransMeasInterval(DEFAULT_MEASUREMENT_INTERVAL_SEC);
	mPerfMgmt->setRxWindowMeasInterval(DEFAULT_MEASUREMENT_INTERVAL_SEC);
	configureNotificationInterval(mNotificationInterval);
	configureFileUploadInterval(mFileUploadInterval);

	// Register callbacks
	getItemsSubscribe(mCallback->path(), mCallback);
	changeSubscribe() ;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::sendNotificationData(
		std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transNotif,
		std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinNotif)
{
	eventInfo("Sending performance management notification");

	std::string notifPath( "/o-ran-performance-management:measurement-result-stats") ;
	std::string measObjPath;

	std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;

	for (auto & entry : transNotif)
	{
		std::set<IPerformanceMgmt::TransReportInfoType_T> reportType;
		mPerfMgmt->getTransMeasReportType(entry.first, reportType);

		std::string typeStr;
		IPerformanceMgmt::measTypeToStr(entry.first, typeStr);

		measObjPath = notifPath + "/transceiver-stats[measurement-object='" + typeStr + "']";
		params->addParam(typeStr, measObjPath + "/measurement-object") ;

		unsigned int numMeasurements = entry.second.size();
		if (numMeasurements < 1)
		{
			continue;
		}

		// We are interested only in the latest measurement for each type
		IPerformanceMgmt::transMeasData measData = entry.second[numMeasurements - 1];

		params->addParam(measData.startTime, measObjPath + "/start-time");
		params->addParam(measData.endTime, measObjPath + "/end-time");

		for (auto & val : measData.data)
		{
			// Get the ethernet port number from the SFP port
			uint8_t objectId = 0;
			for (auto & elem : mEthPortToSFPPort)
			{
				if (elem.second == val.port)
				{
					objectId = elem.first;
					break;
				}
			}
			std::string measResultPath = measObjPath + "/transceiver-measurement-result[object-unit-id='" + std::to_string(objectId) + "']";
			params->addParam(objectId, measResultPath + "/object-unit-id") ;

			std::stringstream ss;
			if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_MINIMUM) != reportType.end())
			{
				ss << std::fixed << std::setprecision(4) << val.min.first;
				params->addParam(ss.str(), measResultPath + "/min/value") ;
				params->addParam(val.min.second, measResultPath + "/min/time") ;
			}

			ss = std::stringstream("");
			if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_MAXIMUM) != reportType.end())
			{
				ss << std::fixed << std::setprecision(4) << val.max.first;
				params->addParam(ss.str(), measResultPath + "/max/value") ;
				params->addParam(val.max.second, measResultPath + "/max/time") ;
			}

			ss = std::stringstream("");
			if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_FIRST) != reportType.end())
			{
				ss << std::fixed << std::setprecision(4) << val.first.first;
				params->addParam(ss.str(), measResultPath + "/first/value") ;
				params->addParam(val.first.second, measResultPath + "/first/time") ;
			}

			ss = std::stringstream("");
			if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_LATEST) != reportType.end())
			{
				ss << std::fixed << std::setprecision(4) << val.latest.first;
				params->addParam(ss.str(), measResultPath + "/latest/value") ;
				params->addParam(val.latest.second, measResultPath + "/latest/time") ;
			}

			if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_FREQ_TABLE) != reportType.end())
			{
				for (int index = 0; index < (int)(val.table.size()); index++)
				{
					params->addParam(val.table[index], measResultPath + "/frequeny-table[.='" + std::to_string(val.table[index]) + "']");
				}
			}
		}
	}

	for (auto & entry : rxWinNotif)
	{
		std::string typeStr;
		IPerformanceMgmt::rxWindowMeasTypeToStr(entry.first, typeStr);

		measObjPath = notifPath + "/rx-window-stats[measurement-object='" + typeStr + "']";
		params->addParam(typeStr, measObjPath + "/measurement-object") ;

		unsigned int numMeasurements = entry.second.size();
		if (numMeasurements < 1)
		{
			continue;
		}
		// We are interested only in the latest measurement for each type
		IPerformanceMgmt::rxWindowMeasData measData = entry.second[numMeasurements - 1];

		params->addParam(measData.startTime, measObjPath + "/start-time");
		params->addParam(measData.endTime, measObjPath + "/end-time");
		params->addParam(Zcu111FbcOranrrhHandlerIetfHardware::mRadioCardHardwareName, measObjPath + "/name");
		params->addParam(measData.data, measObjPath + "/count");
	}

	if (params->getNumParams() > 0)
	{
		sendNotification(notifPath, params) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::uploadFileData(
		std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transData,
		std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinData,
		std::string startTime, std::string endTime)
{
	std::stringstream measLine;

	std::string filePath = Zcu111FbcOranrrhHandlerORanFileManagement::mDirPrefix +
			Zcu111FbcOranrrhHandlerORanFileManagement::mOranPMFolder + "/";

	std::string fileName = "C" + startTime + "_" + endTime + "_" +
			Zcu111FbcOranrrhHandlerIetfHardware::mRadioCardHardwareName + ".csv";
	std::ofstream pmFileHandler;

	// Open the file to write the measurement data
	pmFileHandler.open(std::string(filePath + fileName).c_str());

	// Go through each type of measurement
	for (auto & entry : transData)
	{
		std::set<IPerformanceMgmt::TransReportInfoType_T> reportType;
		mPerfMgmt->getTransMeasReportType(entry.first, reportType);

		std::string typeStr;
		int identifier;
		IPerformanceMgmt::measTypeToStr(entry.first, typeStr);
		IPerformanceMgmt::measTypeToId(entry.first, identifier);

		for (auto & measData : entry.second)
		{
			measLine << std::to_string(identifier) << "," << typeStr << "," <<
					measData.startTime << "," << measData.endTime << ",";

			// Go through each objectId
			for (auto & val : measData.data)
			{
				// Get the ethernet port number from the SFP port
				uint8_t objectId = 0;
				for (auto & elem : mEthPortToSFPPort)
				{
					if (elem.second == val.port)
					{
						objectId = elem.first;
						break;
					}
				}

				// Write the measurement data in the file as per the format in section 7.2.2 File Management process
				// in ORAN-WG4.MP.0-v02.00.00
				measLine << std::to_string(objectId);
				if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_MINIMUM) != reportType.end())
				{
					measLine << "," << std::fixed << std::setprecision(4) << val.min.first << "," << val.min.second;
				}

				if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_MAXIMUM) != reportType.end())
				{
					measLine << "," << std::fixed << std::setprecision(4) << val.max.first << "," << val.max.second;
				}

				if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_FIRST) != reportType.end())
				{
					measLine << "," << std::fixed << std::setprecision(4) << val.first.first << "," << val.first.second;
				}

				if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_LATEST) != reportType.end())
				{
					measLine << "," << std::fixed << std::setprecision(4) << val.latest.first << "," << val.latest.second ;
				}

				if (reportType.find(IPerformanceMgmt::TransReportInfoType_T::REPORT_FREQ_TABLE) != reportType.end())
				{
					// Add the frequency table information
					for (int index = 0; index < (int)(val.table.size()); index++)
					{
						measLine << ",";
						measLine << std::to_string(val.table[index]);
					}
				}

			}

			measLine << std::endl;

			// Add the measurement to the file
			pmFileHandler << measLine.str();

			measLine = std::stringstream("");
		}

	}

	for (auto & entry : rxWinData)
	{
		std::string typeStr;
		int identifier;
		IPerformanceMgmt::rxWindowMeasTypeToStr(entry.first, typeStr);
		IPerformanceMgmt::rxWindowMeasTypeToId(entry.first, identifier);

		for (auto & measData : entry.second)
		{
			measLine << std::to_string(identifier) << "," << typeStr << "," <<
					 measData.startTime << "," << measData.endTime << "," <<
					 Zcu111FbcOranrrhHandlerIetfHardware::mRadioCardHardwareName << "," <<
					 std::to_string(measData.data) << std::endl;

			// Add the measurement to the file
			pmFileHandler << measLine.str();

			measLine = std::stringstream("");
		}
	}

	pmFileHandler.close();

	// Now upload the file to number of servers as per the yang configuration
	for (auto & sftpEntry : mSftpUploadData)
	{
		std::string error ;
		std::string remotePath(sftpEntry.first + "/" + fileName) ;

		eventInfo("Uploading file %s to %s", fileName.c_str(), sftpEntry.first.c_str());

		std::string authData ;
		ISftpMgr::AuthenticationType authType(ISftpMgr::AUTH_NONE) ;
		std::vector<ISshSession::PublicKey> serverKeys ;
		if (!YangUserAuth::authParams(sftpEntry.second, authData, authType, serverKeys))
		{
			eventError("Failed to get authentication parameters while uploading file %s to %s", fileName.c_str(), remotePath.c_str());
			continue ;
		}

		if (authType == ISftpMgr::AUTH_NONE)
		{
			eventError("No supported authorisation method provided while uploading file %s to %s", fileName.c_str(), remotePath.c_str());
			continue ;
		}

		// Ok now to create an sftp session
		std::shared_ptr<ISftpSession> sftp(ISftpMgr::factory(remotePath, authData, authType, serverKeys, error)) ;
		if (!sftp)
		{
			eventError("Error \"%s\" while uploading file %s to %s", error.c_str(), fileName.c_str(), remotePath.c_str());
			continue ;
		}

		// Schedule the file upload
		auto complete = [this, fileName, remotePath](const std::string& remoteFile, const std::string& localFile,
				ISftpSession::SftpTransaction transaction, const std::string& error, bool timedOut){

			if (!error.empty())
			{
				eventError("Upload error \"%s\" while uploading file %s to %s", error.c_str(), fileName.c_str(), remotePath.c_str());
			}
		} ;

		// do transfer
		if (!sftp->fileUpload(remotePath, filePath + fileName, complete))
		{
			eventError("Failed to upload file %s to %s", fileName.c_str(), remotePath.c_str());
			continue ;
		}
	}

	// Delete older files
	std::vector<std::string> fileList = Path::dirContents(filePath, true);

	if (fileList.size() > PM_FILE_THRESHOLD)
	{
		int filesToDelete = fileList.size() - PM_FILE_THRESHOLD;
		int count = 0;
		for (auto & file : fileList)
		{
			Path::remove(file);
			count++;

			if (count >= filesToDelete)
			{
				break;
			}
		}
	}
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Zcu111FbcOranrrhHandlerORanPerformanceMgmt::validate(std::shared_ptr<YangParams> params,
		std::shared_ptr<YangParams> deletedParams)
{
	int ret = SR_ERR_OK;

	for (unsigned i=0; i < params->getNumParams(); ++i)
	{
		std::shared_ptr<YangParam> param(params->getParam(i)) ;

		std::string listName ;
		std::string key ;
		std::string index ;
		std::string error;
		std::string value;
		std::string leaf;
		bool isList = false;

		value = YangParamUtils::toString(param, error) ;
		isList = listIndex(param->name(), listName, key, index) ;
		leaf = leafName(param->name());

		if (isList)
		{
			if (listName == "transceiver-measurement-objects")
			{
				IPerformanceMgmt::TransceiverMeasType_T type;
				IPerformanceMgmt::measStrToType(index, type);

				if (leaf == "function" ||
					leaf == "bin-count" ||
					leaf == "lower-bound" ||
					leaf == "upper-bound")
				{
					// If measurement is active, then its configuration cannot be changed
					if (mPerfMgmt->isTransMeasActive(type))
					{
						ret = SR_ERR_VALIDATION_FAILED;
						break;
					}
					else
					{
						// Ensure that the bin count is within the range supported by this yang model
						if (leaf == "bin-count")
						{
							uint16_t count = YangParamUtils::toUint16(param, error);
							if (count > MAX_BIN_COUNT)
							{
								ret = SR_ERR_VALIDATION_FAILED;
								break;
							}
						}
					}
				}
			}
		}
	}
	return ret ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::valueChange(const std::string & xpath,
                                                  std::shared_ptr<YangParam> oldValue,
                                                  std::shared_ptr<YangParam> newValue)
{
	logDebugVerbose("Zcu111FbcOranrrhHandlerORanPerformanceMgmt::valueChange() - %s", xpath.c_str());

	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	std::string value ;
	std::string leaf ;
	bool isList = false;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		//std::cerr << " + OLD: " << oldValue->name() << " = " << value << std::endl ;
		isList = listIndex(oldValue->name(), listName, key, index) ;
		leaf = leafName(oldValue->name()) ;
	}
	if (newValue)
	{
		value = YangParamUtils::toString(newValue, error) ;
		//std::cerr << " + NEW: " << newValue->name() << " = " << value << std::endl ;
		isList = listIndex(newValue->name(), listName, key, index) ;
		leaf = leafName(newValue->name()) ;
	}

	if (! isList)
	{
		// Set the transceiver measurement interval
		if (leaf == "transceiver-measurement-interval")
		{
			uint16_t interval = (uint16_t)std::stoul(value);
			mPerfMgmt->setTransMeasInterval(interval);
		}
		// Set the rx window measurement interval
		else if (leaf == "rx-window-measurement-interval")
		{
			uint16_t interval = (uint16_t)std::stoul(value);
			mPerfMgmt->setRxWindowMeasInterval(interval);
		}
		// Set the notification interval
		else if (leaf == "notification-interval")
		{
			uint16_t interval = (uint16_t)std::stoul(value);
			configureNotificationInterval(interval);
		}
		// Set the file upload interval
		else if (leaf == "file-upload-interval")
		{
			uint16_t interval = (uint16_t)std::stoul(value);
			configureFileUploadInterval(interval);
		}
		// Set the file upload enable/disable flag
		else if (leaf == "enable-SFTP-upload")
		{
			bool enable = (value == "true" ? true : false);
			mPerfMgmt->enableFileUpload(enable);
		}
	}
	else
	{
		// Check if any measurement configuration for the transceiver has been updated
		if (listName == "transceiver-measurement-objects")
		{
			IPerformanceMgmt::TransceiverMeasType_T type;
			IPerformanceMgmt::measStrToType(index, type);

			if (leaf == "active")
			{
				// If measurement is activated, create operational data for this measurement,
				// Make all the other configurable parameters for this measurement as read-only
				if (value == "true")
				{
					createTransReadOnlyData(type);
					mPerfMgmt->setTransMeasActiveInactive(type, true);
				}
				else
				{
					deleteTransReadOnlyData(type);
					mPerfMgmt->setTransMeasActiveInactive(type, false);
				}
			}
			else if (leaf == "function")
			{
				IPerformanceMgmt::FunctionType_T function;
				IPerformanceMgmt::functionStrToType(value, function);
				mPerfMgmt->setTransMeasFunction(type, function);
			}
			else if (leaf == "report-info")
			{
				IPerformanceMgmt::TransReportInfoType_T report;
				IPerformanceMgmt::reportStrToType(value, report);
				mPerfMgmt->setTransMeasReportType(type, report, true);
			}
			else if (leaf == "bin-count")
			{
				uint16_t count = (uint16_t)std::stoul(value);
				mPerfMgmt->setTransMeasBinCount(type, count);

				updateTransFreqTable(type);
			}
			else if (leaf == "lower-bound")
			{
				double bound = std::stod(value);
				mPerfMgmt->setTransMeasLowerLimit(type, bound);
			}
			else if (leaf == "upper-bound")
			{
				double bound = std::stod(value);
				mPerfMgmt->setTransMeasUpperLimit(type, bound);
			}
		}
		else if (listName == "rx-window-measurement-objects")
		{
			IPerformanceMgmt::RxWindowMeasType_T type;
			IPerformanceMgmt::rxWindowMeasStrToType(index, type);

			if (leaf == "active")
			{
				// If measurement is activated, create operational data for this measurement,
				// Make all the other configurable parameters for this measurement as read-only
				if (value == "true")
				{
					createRxWinReadOnlyData(type);
					mPerfMgmt->setRxWindowMeasActiveInactive(type, true);
				}
				else
				{
					deleteRxWinReadOnlyData(type);
					mPerfMgmt->setRxWindowMeasActiveInactive(type, false);
				}
			}
		}
		else if (listName == "remote-SFTP-uploads")
		{
			if (mSftpUploadData.find(index) == mSftpUploadData.end())
			{
				mSftpUploadData[index] = std::make_shared<YangParams>();
			}

			// Add any file upload yang parameter that is set to the list
			mSftpUploadData[index]->addParam(newValue);
		}
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::paramDelete(const std::string& xpath, std::shared_ptr<YangParam> oldValue)
{
	std::string error ;

	std::string listName ;
	std::string key ;
	std::string index ;
	std::string value ;
	std::string leaf ;
	bool isList = false;

	if (oldValue)
	{
		value = YangParamUtils::toString(oldValue, error) ;
		//std::cerr << " + OLD: " << oldValue->name() << " = " << value << std::endl ;
		isList = listIndex(oldValue->name(), listName, key, index) ;
		leaf = leafName(oldValue->name()) ;
	}

	if (isList)
	{
		// Check if any measurement configuration for the transceiver has been updated
		if (listName == "transceiver-measurement-objects")
		{
			IPerformanceMgmt::TransceiverMeasType_T type;
			IPerformanceMgmt::measStrToType(index, type);

			if (leaf == "report-info")
			{
				IPerformanceMgmt::TransReportInfoType_T report;
				IPerformanceMgmt::reportStrToType(value, report);
				mPerfMgmt->setTransMeasReportType(type, report, false);
			}
		}
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::map<std::string, std::string> > Zcu111FbcOranrrhHandlerORanPerformanceMgmt::getInterfaces(void)
{
	// get all of the interfaces so I can search for the interface name
	return getKeyValues( "/ietf-interfaces:interfaces/interface//.") ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::shared_ptr<YangParam> > Zcu111FbcOranrrhHandlerORanPerformanceMgmt::getPortReference(std::string interface)
{
	// get port reference for the specified interface
	return getParams( "/ietf-interfaces:interfaces/interface[name='" + interface + "']/o-ran-interfaces:port-reference//.") ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::populateInterfaces(void)
{
	// Get all interfaces
	std::map<std::string, std::map<std::string, std::string> > interfaces(getInterfaces());

	for (auto & name : interfaces)
	{
		std::map<std::string, std::shared_ptr<YangParam>> portReference = getPortReference(name.first);
		for (auto & entry : portReference)
		{
			if (entry.first == "port-number")
			{
				std::string error;
				mInterfaces[name.first] = YangParamUtils::toUint8(entry.second, error);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::createTransReadWriteData(IPerformanceMgmt::TransceiverMeasType_T type)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string transceiverMeasObjs = mCallback->path() + "/transceiver-measurement-objects";
	ds->createListEntry(transceiverMeasObjs, "measurement-object", PerformanceMgmtService::mTransMeasTypeToStr.at(type),
			std::map<std::string, std::string>{
				{"active", "false"},
				{"object-unit", "PORT_NUMBER"},
				{"report-info", "MINIMUM"},
				{"report-info", "MAXIMUM"},
				{"report-info", "FIRST"},
				{"report-info", "LATEST"},
				{"report-info", "FREQUENCY_TABLE"}
			});

	for (auto & reportType : PerformanceMgmtService::mTransReportTypeToStr)
	{
		mPerfMgmt->setTransMeasReportType(type, reportType.first, true);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::createTransReadOnlyData(IPerformanceMgmt::TransceiverMeasType_T type)
{
	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	auto transMeasObjects = parent->addContainerList("transceiver-measurement-objects");
	transMeasObjects->addLeaf("measurement-object", PerformanceMgmtService::mTransMeasTypeToStr.at(type));

	for (auto & source : mInterfaces)
	{
		// Check if the interface number is same as the ethbb port number
		if (mEthPortToSFPPort.find(source.second) != mEthPortToSFPPort.end())
		{
			int portNum = source.second;
			auto result = transMeasObjects->addContainerList("transceiver-measurement-result");
			result->addLeaf("object-unit-id", std::to_string(portNum));

			// Add leaf function to populate stats based on reportType parameter
			int sfpPort = mEthPortToSFPPort[portNum];

			// Add container min
			auto min = result->addContainer("min");

			auto minValueFunc = [this, sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasValue(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_MINIMUM, sfpPort));
			} ;

			auto minTimeFunc = [this,sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasTimestamp(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_MINIMUM, sfpPort));
			} ;

			min->addLeaf("value", minValueFunc);
			min->addLeaf("time", minTimeFunc);

			// Add container max
			auto max = result->addContainer("max");

			auto maxValueFunc = [this, sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasValue(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_MAXIMUM, sfpPort));
			} ;

			auto maxTimeFunc = [this,sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasTimestamp(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_MAXIMUM, sfpPort));
			} ;

			max->addLeaf("value", maxValueFunc);
			max->addLeaf("time", maxTimeFunc);

			// Add container first
			auto first = result->addContainer("first");

			auto firstValueFunc = [this, sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasValue(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_FIRST, sfpPort));
			} ;

			auto firstTimeFunc = [this,sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasTimestamp(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_FIRST, sfpPort));
			} ;

			first->addLeaf("value", firstValueFunc);
			first->addLeaf("time", firstTimeFunc);

			// Add container latest
			auto latest = result->addContainer("latest");

			auto latestValueFunc = [this, sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasValue(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_LATEST, sfpPort));
			} ;

			auto latestTimeFunc = [this,sfpPort, type](const std::string& leafName)->std::string {
				return (getTransMeasTimestamp(type, IPerformanceMgmt::TransReportInfoType_T::REPORT_LATEST, sfpPort));
			} ;

			latest->addLeaf("value", latestValueFunc);
			latest->addLeaf("time", latestTimeFunc);

			// Remove and create frequency table
			result->deleteNamed("frequeny-table", false);

			uint16_t binCount = mPerfMgmt->getTransMeasBinCount(type);

			for (unsigned int index = 0 ; index < binCount; index++)
			{
				auto frequencyPointFunc = [this, sfpPort, type, index](const std::string& leafName)->std::string {
					std::pair<double, std::string> min;
					std::pair<double, std::string> max;
					std::pair<double, std::string> first;
					std::pair<double, std::string> latest;
					std::vector<uint32_t> table;

					mPerfMgmt->getTransceiverMeasResult(sfpPort, type, min, max, first, latest, table);

					return (std::to_string(table[index]));
				} ;

				// Add one entry to the leaf-list and get its value from the performance management interface
				result->addLeaf("frequeny-table", frequencyPointFunc);
			}

		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::deleteTransReadOnlyData(IPerformanceMgmt::TransceiverMeasType_T type)
{
	std::string measTypeStr;
	IPerformanceMgmt::measTypeToStr(type, measTypeStr);

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Get the children for the top level container
	std::vector<std::shared_ptr<ILeafContainer>> performanceMgmtChildren = parent->contents();

	for (auto & pmChild : performanceMgmtChildren)
	{
		if (pmChild->name() != "transceiver-measurement-objects")
		{
			continue;
		}

		// Find the children of transceiver measurement objects
		std::vector<std::shared_ptr<ILeafContainer>> transMeasChildren = pmChild->contents();

		for (auto & tmChild : transMeasChildren)
		{
			if (tmChild->name() != "measurement-object")
			{
				continue;
			}

			// Check if this child has a measurement object of the type that we want to delete operational data for
			if (tmChild->value() == measTypeStr)
			{
				// Delte operationl data for this type
				parent->removeContainer(pmChild);
				return;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::updateTransFreqTable(IPerformanceMgmt::TransceiverMeasType_T type)
{
	// Recreate read only data if measurement is active
	if (mPerfMgmt->isTransMeasActive(type))
	{
		deleteTransReadOnlyData(type);
		createTransReadOnlyData(type);
	}

}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanPerformanceMgmt::getTransMeasValue(IPerformanceMgmt::TransceiverMeasType_T measType,
		IPerformanceMgmt::TransReportInfoType_T reportType, int portNum)
{
	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	mPerfMgmt->getTransceiverMeasResult(portNum, measType, min, max, first, latest, table);

	std::string ret = "";

	switch (reportType)
	{
	case IPerformanceMgmt::REPORT_MINIMUM:
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(4) << min.first;
		ret = ss.str();
	}
	break;

	case IPerformanceMgmt::REPORT_MAXIMUM:
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(4) << max.first;
		ret = ss.str();
	}
	break;

	case IPerformanceMgmt::REPORT_FIRST:
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(4) << first.first;
		ret = ss.str();
	}
	break;

	case IPerformanceMgmt::REPORT_LATEST:
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(4) << latest.first;
		ret = ss.str();
	}
	break;

	default:
		break;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111FbcOranrrhHandlerORanPerformanceMgmt::getTransMeasTimestamp(IPerformanceMgmt::TransceiverMeasType_T measType,
		IPerformanceMgmt::TransReportInfoType_T reportType, int portNum)
{
	std::pair<double, std::string> min;
	std::pair<double, std::string> max;
	std::pair<double, std::string> first;
	std::pair<double, std::string> latest;
	std::vector<uint32_t> table;

	mPerfMgmt->getTransceiverMeasResult(portNum, measType, min, max, first, latest, table);

	std::string ret = "";

	switch (reportType)
	{
	case IPerformanceMgmt::REPORT_MINIMUM:
		ret = min.second;
	break;

	case IPerformanceMgmt::REPORT_MAXIMUM:
		ret = max.second;
	break;

	case IPerformanceMgmt::REPORT_FIRST:
		ret = first.second;
	break;

	case IPerformanceMgmt::REPORT_LATEST:
		ret = latest.second;
	break;

	default:
		break;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::createRxWinReadWriteData(IPerformanceMgmt::RxWindowMeasType_T type)
{
	std::shared_ptr<YangMgrServer> mgr(std::dynamic_pointer_cast<YangMgrServer>(moduleMgr())) ;
	std::shared_ptr<RadioDatastoreSysrepo> ds(std::dynamic_pointer_cast<RadioDatastoreSysrepo>(mgr->dataStore())) ;

	std::string typeStr;
	IPerformanceMgmt::rxWindowMeasTypeToStr(type, typeStr);

	std::string rxWinMeasObjs = mCallback->path() + "/rx-window-measurement-objects";
	ds->createListEntry(rxWinMeasObjs, "measurement-object", typeStr,
			std::map<std::string, std::string>{
				{"active", "false"},
				{"object-unit", "RU"},
				{"report-info", "COUNT"}
			});

	std::string objectUnitPath = rxWinMeasObjs + "/[measurement-object='" + typeStr + "']'/object-unit";
	makeReadOnly(objectUnitPath);
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::createRxWinReadOnlyData(IPerformanceMgmt::RxWindowMeasType_T type)
{
	std::shared_ptr<ILeafContainer> parent(mCallback) ;
	std::string typeStr;
	IPerformanceMgmt::rxWindowMeasTypeToStr(type, typeStr);

	auto rxWinMeasObjects = parent->addContainerList("rx-window-measurement-objects");
	rxWinMeasObjects->addLeaf("measurement-object", typeStr);
	rxWinMeasObjects->addLeaf("name", Zcu111FbcOranrrhHandlerIetfHardware::mRadioCardHardwareName);

	auto rxWinDataFunc = [this, type](const std::string& leafName)->std::string {
		uint64_t count;
		mPerfMgmt->getRxWindowMeasResult(type, count);
		return std::to_string(count);
	} ;

	rxWinMeasObjects->addLeaf("count", rxWinDataFunc);
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::deleteRxWinReadOnlyData(IPerformanceMgmt::RxWindowMeasType_T type)
{
	std::string measTypeStr;
	IPerformanceMgmt::rxWindowMeasTypeToStr(type, measTypeStr);

	std::shared_ptr<ILeafContainer> parent(mCallback) ;

	// Get the children for the top level container
	std::vector<std::shared_ptr<ILeafContainer>> performanceMgmtChildren = parent->contents();

	for (auto & pmChild : performanceMgmtChildren)
	{
		if (pmChild->name() != "rx-window-measurement-objects")
		{
			continue;
		}

		// Find the children of rx window measurement objects
		std::vector<std::shared_ptr<ILeafContainer>> rxWinMeasChildren = pmChild->contents();

		for (auto & tmChild : rxWinMeasChildren)
		{
			if (tmChild->name() != "measurement-object")
			{
				continue;
			}

			// Check if this child has a measurement object of the type that we want to delete operational data for
			if (tmChild->value() == measTypeStr)
			{
				// Delete operational data for this type
				parent->removeContainer(pmChild);
				return;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::configureNotificationInterval(uint16_t interval)
{
	mNotificationInterval = interval;
	mPerfMgmt->configureNotification(mNotificationInterval, [this](
			std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transNotif,
			std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinNotif){
		sendNotificationData(transNotif, rxWinNotif);
	});
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111FbcOranrrhHandlerORanPerformanceMgmt::configureFileUploadInterval(uint16_t interval)
{
	mFileUploadInterval = interval;

	mPerfMgmt->configureFileUpload(mFileUploadInterval, [this](
			std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transData,
			std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinData,
			std::string startTime, std::string endTime){
		uploadFileData(transData, rxWinData, startTime, endTime);
	});
}
