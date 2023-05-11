/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanPerformanceMgmt.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPERFMANAGEMENT_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPERFMANAGEMENT_H_

#include "YangHandlerSysrepo.h"
#include "IPerformanceMgmt.h"
#include "PerformanceMgmtService.h"
#include "SysrepoGetitemsCallback.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanPerformanceMgmt
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanPerformanceMgmt : public YangHandlerSysrepo
{
public:

	static const uint16_t MAX_BIN_COUNT;
	static const uint16_t DEFAULT_MEASUREMENT_INTERVAL_SEC;
	static const uint16_t DEFAULT_NOTIFICATION_INTERVAL_SEC;
	static const uint16_t DEFAULT_FILE_UPLOAD_INTERVAL_SEC;
	static const uint16_t PM_FILE_THRESHOLD;

	Zcu111FbcOranrrhHandlerORanPerformanceMgmt(std::shared_ptr<IYangModuleMgr> moduleMgr);
	virtual ~Zcu111FbcOranrrhHandlerORanPerformanceMgmt();

	/*
	 * Run the initialisation of the handler (can only be done once the rest of the YANG framework is up)
	 */
	virtual bool initialise() override;

protected:

	/*!
	 \brief Module change hook - called by module_change() method to have this class validate the proposed values changes
	 \param params A YangParams pointer containing all of the changed values
	 \return SR_ERR_OK if the values are validated; SR_ERR_VALIDATION_FAILED on validation failure. Can return any other sysrepo error
	 status as necessary.
	 */
	virtual int validate(std::shared_ptr<YangParams> params, std::shared_ptr<YangParams> deletedParams) ;

	/**
	 * Module change hook - called by module_change() method with filtered events
	 */
	virtual void valueChange(const std::string& xpath,
	                         std::shared_ptr<YangParam> oldValue,
	                         std::shared_ptr<YangParam> newValue);

	/*!
	 \brief Module change hook - called by module_change() method with filtered events
	 \param xpath Contains full path of the element for which paramDelete callback is called. Eg /o-ran-sync:sync/ptp-config/ptp-profile.
	 \param oldValue The original value of the element
	 */
	virtual void paramDelete(const std::string& xpath, std::shared_ptr<YangParam> oldValue) ;


	void sendNotificationData(std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transNotif,
			std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinNotif);

	void uploadFileData(std::map<IPerformanceMgmt::TransceiverMeasType_T,std::vector<IPerformanceMgmt::transMeasData>> transData,
			std::map<IPerformanceMgmt::RxWindowMeasType_T,std::vector<IPerformanceMgmt::rxWindowMeasData>> rxWinData,
			std::string startTime, std::string endTime);

private:

	std::shared_ptr<SysrepoGetitemsCallback> mCallback;
	std::shared_ptr<IPerformanceMgmt> mPerfMgmt;
	std::map<std::string, uint8_t> mInterfaces;
	std::map<int, int> mEthPortToSFPPort;
	uint16_t mNotificationInterval;
	uint16_t mFileUploadInterval;
	std::map<std::string, std::shared_ptr<YangParams>> mSftpUploadData;

	/**
	 * Get the interfaces from ietf-interfaces module
	 */
	std::map<std::string, std::map<std::string, std::string> > getInterfaces(void);

	/**
	 * Get the port reference for a given interface name
	 */
	std::map<std::string, std::shared_ptr<YangParam> > getPortReference(std::string interface);

	/**
	 * Method to populate interfaces
	 */
	void populateInterfaces(void);

	/**
	 * Method to create transceiver read-write data based on the measurement object
	 */
	void createTransReadWriteData(IPerformanceMgmt::TransceiverMeasType_T);

	/**
	 * Method to create transceiver operational data based on the measurement object
	 */
	void createTransReadOnlyData(IPerformanceMgmt::TransceiverMeasType_T);

	/**
	 * Method to delete transceiver operational data based on the measurement object
	 */
	void deleteTransReadOnlyData(IPerformanceMgmt::TransceiverMeasType_T);

	/**
	 * Method to update transceiver frequency table based on the measurement object
	 */
	void updateTransFreqTable(IPerformanceMgmt::TransceiverMeasType_T);

	/**
	 * Method to return statistics for a given report info type
	 */
	std::string getTransMeasValue(IPerformanceMgmt::TransceiverMeasType_T measType,
			IPerformanceMgmt::TransReportInfoType_T reportType, int portNum);

	/**
	 * Method to return timestamp for a given report info type
	 */
	std::string getTransMeasTimestamp(IPerformanceMgmt::TransceiverMeasType_T measType,
			IPerformanceMgmt::TransReportInfoType_T reportType, int portNum);

	/**
	 * Method to create rx window read-write data based on the measurement object
	 */
	void createRxWinReadWriteData(IPerformanceMgmt::RxWindowMeasType_T);

	/**
	 * Method to create rx window operational data based on the measurement object
	 */
	void createRxWinReadOnlyData(IPerformanceMgmt::RxWindowMeasType_T);

	/**
	 * Method to delete rx window operational data based on the measurement object
	 */
	void deleteRxWinReadOnlyData(IPerformanceMgmt::RxWindowMeasType_T);


	/**
	 * Method to update the notification interval
	 */
	void configureNotificationInterval(uint16_t interval);

	/**
	 * Method to update the file upload interval
	 */
	void configureFileUploadInterval(uint16_t interval);
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANPERFMANAGEMENT_H_ */
