/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PerformanceMgmtService.h
 * \brief     Virtual interface to configure and measure for transceiver and rx window parameters
 *
 *
 * \details   Virtual interface to configure and measure for transceiver and rx window parameters
 *
 */


#ifndef YANG_HANDLERS_INC_PERFORMANCEMGMTSERVICE_H_
#define YANG_HANDLERS_INC_PERFORMANCEMGMTSERVICE_H_

#include <memory>
#include <utility>
#include <map>
#include <vector>

#include "IPerformanceMgmt.h"
#include "Service.h"
#include "TransceiverMeasurement.h"
#include "RxWindowMeasurement.h"

#include "MplanePerformanceMgmt.h"

namespace Mplane {

/*!
 * \class  PerformanceMgmtService
 * \brief
 * \details
 *
 */
class PerformanceMgmtService: public virtual IPerformanceMgmt, public Service {
public:

	PerformanceMgmtService(std::vector<int> sfps);
	virtual ~PerformanceMgmtService() {}

	static const uint16_t MAX_LOCAL_MEASUREMENT_INTERVAL_MSEC;
	static const std::map<IPerformanceMgmt::TransceiverMeasType_T, std::string> mTransMeasTypeToStr;
	static const std::map<IPerformanceMgmt::TransReportInfoType_T, std::string> mTransReportTypeToStr;
	static const std::map<IPerformanceMgmt::FunctionType_T, std::string> mFuncTypeToStr;
	static const std::map<IPerformanceMgmt::TransceiverMeasType_T, int> mTransMeasTypeToId;
	static const std::map<IPerformanceMgmt::RxWindowMeasType_T, std::string> mRxWindowMeasTypeToStr;
	static const std::map<IPerformanceMgmt::RxWindowObjectUnitId_T, std::string> mRxWindowObjIdToStr;
	static const std::map<IPerformanceMgmt::RxWindowMeasType_T, int> mRxWindowMeasTypeToId;

	/**
	 * Returns whether measurement is active
	 */
	virtual bool isTransMeasActive(TransceiverMeasType_T measType) override ;

	/**
	 * Activate/Deactivate a transceiver measurement type
	 */
	virtual void setTransMeasActiveInactive(TransceiverMeasType_T measType, bool activate) override ;

	/**
	 * Set the function type for a transceiver measurement type
	 */
	virtual void setTransMeasFunction(TransceiverMeasType_T measType, FunctionType_T function) override ;

	/**
	 * Add/Remove the report type for a transceiver measurement type
	 */
	virtual void setTransMeasReportType(TransceiverMeasType_T measType, TransReportInfoType_T report, bool add) override ;

	/**
	 * Get the report type list for a transceiver measurement type
	 */
	virtual void getTransMeasReportType(TransceiverMeasType_T measType, std::set<TransReportInfoType_T>& report) override ;

	/**
	 * Set the bin count for the frequency table for a transceiver measurement type
	 */
	virtual void setTransMeasBinCount(TransceiverMeasType_T measType, uint16_t binCount) override ;

	/**
	 * Get the bin count for the frequency table for a transceiver measurement type
	 */
	virtual uint16_t getTransMeasBinCount(TransceiverMeasType_T measType) override ;

	/**
	 * Set the lower limit for the frequency table for a transceiver measurement type
	 */
	virtual void setTransMeasLowerLimit(TransceiverMeasType_T measType, double lowerLimit) override ;

	/**
	 * Set the upper limit for the frequency table for a transceiver measurement type
	 */
	virtual void setTransMeasUpperLimit(TransceiverMeasType_T measType, double upperLimit) override ;

	/**
	 * Set the transceiver measurement interval
	 */
	virtual void setTransMeasInterval(uint16_t interval) override ;

	/**
	 * Get the number of transceiver ports
	 */
	virtual int getNumPorts(void) override ;

	/**
	 * Get the result for a transceiver measurement object
	 */
	virtual bool getTransceiverMeasResult(int portNum, TransceiverMeasType_T measType,
			std::pair<double, std::string>& min, std::pair<double, std::string>& max,
			std::pair<double, std::string>& first, std::pair<double, std::string>& latest,
			std::vector<uint32_t>& table) override ;

	/**
	 * Returns whether Rx window measurement is active
	 */
	virtual bool isRxWindowMeasActive(RxWindowMeasType_T measType) override ;

	/**
	 * Activate/Deactivate a Rx window measurement type
	 */
	virtual void setRxWindowMeasActiveInactive(RxWindowMeasType_T measType, bool activate) override ;

	/**
	 * Set the function type for the measurement
	 */
	virtual void setObjectUnitId(RxWindowMeasType_T measType, IPerformanceMgmt::RxWindowObjectUnitId_T id) override ;

	/**
	 * Set the rx window measurement interval
	 */
	virtual void setRxWindowMeasInterval(uint16_t interval) override ;

	/**
	 * Get the result for a Rx window measurement object
	 */
	virtual bool getRxWindowMeasResult(RxWindowMeasType_T measType,	uint64_t& data) override ;

	/**
	 * Configure notification for measurements
	 */
	virtual void configureNotification(uint16_t interval, IPerformanceMgmt::NotificationCbFunc func) override;

	/**
	 * Configure file upload for measurements
	 */
	virtual void configureFileUpload(uint16_t interval, IPerformanceMgmt::FileUploadCbFunc func) override ;

	/**
	 * Enable/Disable file upload
	 */
	virtual void enableFileUpload(bool enable) override ;

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

	/**
	 * Method to take measurement for each enabled measurement type.
	 */
	void takeLocalMeasurement(void);

	/**
	 * Method to calculate transceiver statistics in the current measurement interval.
	 */
	void calculateTransStatistics(void);

	/**
	 * Method to calculate Rx window statistics in the current measurement interval.
	 */
	void calculateRxWinStatistics(void);

private:

	void registerHalPerformanceMgmt();

	std::vector<int> mSfps;                      //!> Number of SFPs supported
	bool measureNow;                             //!> Flag to indicate that local measurement needs to be done immediately
	uint16_t mLocalMeasIntervalmSec;             //!> Interval in milliseconds to measure all parameters
	uint16_t mTransMeasIntervalSec;              //!> Interval in seconds to collect transceiver measurement parameters
	uint16_t mRxWinMeasIntervalSec;              //!> Interval in seconds to collect Rx window measurement parameters
	bool mFileUploadEnable;                      //!> Whether file upload is enabled
	uint16_t mFileUploadIntervalSec;             //!> Interval in seconds to upload file with measurement statistics in that interval
	std::string mFileUploadStartTime;            //!> Time when the file upload interval started
	IPerformanceMgmt::FileUploadCbFunc mFileUploadFunc; //!> Callback function for file upload
	uint16_t mNotificationIntervalSec;           //!> Interval in seconds to call notification callback with measurement statistics in that interval
	IPerformanceMgmt::NotificationCbFunc mNotifFunc; //!> Callback function for notification
	std::map<TransceiverMeasType_T, std::vector<std::shared_ptr<TransceiverMeasurement>>> mTransMeasData;
	std::map<RxWindowMeasType_T, std::shared_ptr<RxWindowMeasurement>> mRxWindowMeasData;

	bool isAnyTransActive(void);
	bool isAnyRxWinActive(void);

protected:

    std::map<TransceiverMeasType_T,std::vector<transMeasData>> mTransNotificationData;
    std::map<TransceiverMeasType_T,std::vector<transMeasData>> mTransFileUploadData;
    std::map<RxWindowMeasType_T,std::vector<rxWindowMeasData>> mRxWinNotificationData;
    std::map<RxWindowMeasType_T,std::vector<rxWindowMeasData>> mRxWinFileUploadData;
} ;

}

#endif /* YANG_HANDLERS_INC_PERFORMANCEMGMTSERVICE_H_ */
