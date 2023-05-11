/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPerformanceMgmt.h
 * \brief     Virtual interface to configure and measure for transceiver and rx window parameters
 *
 *
 * \details   Virtual interface to configure and measure for transceiver and rx window parameters
 *
 */


#ifndef YANG_HANDLERS_INC_IPERFORMANCEMGMT_H_
#define YANG_HANDLERS_INC_IPERFORMANCEMGMT_H_

#include <memory>
#include <utility>
#include <cstdint>
#include <functional>
#include <vector>
#include <set>

namespace Mplane {

/*!
 * \class  IPerformanceMgmt
 * \brief
 * \details
 *
 */
class IPerformanceMgmt {
public:
 typedef enum {
   SFP_RX_POWER,
   SFP_TX_POWER,
   SFP_TX_BIAS_COUNT,
   SFP_SUPPLY_VOLTAGE,
   SFP_TEMPERATURE
 } TransceiverMeasType_T;

 typedef enum {
   RX_ON_TIME,
   RX_EARLY,
   RX_LATE,
   RX_CORRUPT,
   RX_DUPL,
   RX_TOTAL
 } RxWindowMeasType_T;

 typedef enum { PER_RU, PER_TRANSPORT, PER_EAXC_ID } RxWindowObjectUnitId_T;

 typedef enum {
   REPORT_MAXIMUM,
   REPORT_MINIMUM,
   REPORT_FIRST,
   REPORT_LATEST,
   REPORT_FREQ_TABLE
 } TransReportInfoType_T;

 typedef enum { FUNCTION_RAW, FUNCTION_LOG10 } FunctionType_T;

 IPerformanceMgmt() {}
 virtual ~IPerformanceMgmt() {}

 /*
  * Create singleton
  */
 static std::shared_ptr<IPerformanceMgmt> singleton(void);

 /*
  * Method to convert between transceiver measurement type enum and string
  */
 static void measTypeToStr(
     IPerformanceMgmt::TransceiverMeasType_T type, std::string& str);
 static void measStrToType(
     std::string str, IPerformanceMgmt::TransceiverMeasType_T& type);

 /*
  * Method to convert between transceiver measurement type enum and identifier
  */
 static void measTypeToId(
     IPerformanceMgmt::TransceiverMeasType_T type, int& id);
 static void measIdToType(
     int id, IPerformanceMgmt::TransceiverMeasType_T& type);

 /*
  * Method to convert between reporting info type enum and string
  */
 static void reportTypeToStr(
     IPerformanceMgmt::TransReportInfoType_T type, std::string& str);
 static void reportStrToType(
     std::string str, IPerformanceMgmt::TransReportInfoType_T& type);

 /*
  * Method to convert between measurement function type enum and string
  */
 static void functionTypeToStr(
     IPerformanceMgmt::FunctionType_T type, std::string& str);
 static void functionStrToType(
     std::string str, IPerformanceMgmt::FunctionType_T& type);

 /*
  * Method to convert between Rx window measurement type enum and string
  */
 static void rxWindowMeasTypeToStr(
     IPerformanceMgmt::RxWindowMeasType_T type, std::string& str);
 static void rxWindowMeasStrToType(
     std::string str, IPerformanceMgmt::RxWindowMeasType_T& type);

 /*
  * Method to convert between Rx window object unit id enum and string
  */
 static void rxWindowObjIdToStr(
     IPerformanceMgmt::RxWindowObjectUnitId_T type, std::string& str);
 static void rxWindowObjIdStrToType(
     std::string str, IPerformanceMgmt::RxWindowObjectUnitId_T& type);

 /*
  * Method to convert between transceiver measurement type enum and identifier
  */
 static void rxWindowMeasTypeToId(
     IPerformanceMgmt::RxWindowMeasType_T type, int& id);
 static void rxWindowMeasIdToType(
     int id, IPerformanceMgmt::RxWindowMeasType_T& type);

 /**
  * Returns whether transceiver measurement is active
  */
 virtual bool isTransMeasActive(TransceiverMeasType_T measType) = 0;

 /**
  * Activate/Deactivate a transceiver measurement type
  */
 virtual void setTransMeasActiveInactive(
     TransceiverMeasType_T measType, bool activate) = 0;

 /**
  * Set the function type for a transceiver measurement type
  */
 virtual void setTransMeasFunction(
     TransceiverMeasType_T measType, FunctionType_T function) = 0;

 /**
  * Add/Remove the report type for a transceiver measurement type
  */
 virtual void setTransMeasReportType(
     TransceiverMeasType_T measType,
     TransReportInfoType_T report,
     bool add) = 0;

 /**
  * Get the report type list for a transceiver measurement type
  */
 virtual void getTransMeasReportType(
     TransceiverMeasType_T measType,
     std::set<TransReportInfoType_T>& report) = 0;

 /**
  * Set the bin count for the frequency table for a transceiver measurement type
  */
 virtual void setTransMeasBinCount(
     TransceiverMeasType_T measType, uint16_t binCount) = 0;

 /**
  * Get the bin count for the frequency table for a transceiver measurement type
  */
 virtual uint16_t getTransMeasBinCount(TransceiverMeasType_T measType) = 0;

 /**
  * Set the lower limit for the frequency table for a transceiver measurement
  * type
  */
 virtual void setTransMeasLowerLimit(
     TransceiverMeasType_T measType, double lowerLimit) = 0;

 /**
  * Set the upper limit for the frequency table for a transceiver measurement
  * type
  */
 virtual void setTransMeasUpperLimit(
     TransceiverMeasType_T measType, double upperLimit) = 0;

 /**
  * Set the transceiver measurement interval
  */
 virtual void setTransMeasInterval(uint16_t interval) = 0;

 /**
  * Get the number of transceiver ports
  */
 virtual int getNumPorts(void) = 0;

 /**
  * Get the result for a transceiver measurement object
  */
 virtual bool getTransceiverMeasResult(
     int portNum,
     TransceiverMeasType_T measType,
     std::pair<double, std::string>& min,
     std::pair<double, std::string>& max,
     std::pair<double, std::string>& first,
     std::pair<double, std::string>& latest,
     std::vector<uint32_t>& table) = 0;

 /**
  * Returns whether Rx window measurement is active
  */
 virtual bool isRxWindowMeasActive(RxWindowMeasType_T measType) = 0;

 /**
  * Activate/Deactivate a Rx window measurement type
  */
 virtual void setRxWindowMeasActiveInactive(
     RxWindowMeasType_T measType, bool activate) = 0;

 /**
  * Set the function type for the measurement
  */
 virtual void setObjectUnitId(
     RxWindowMeasType_T measType,
     IPerformanceMgmt::RxWindowObjectUnitId_T id) = 0;

 /**
  * Set the rx window measurement interval
  */
 virtual void setRxWindowMeasInterval(uint16_t interval) = 0;

 /**
  * Get the result for a Rx window measurement object
  */
 virtual bool getRxWindowMeasResult(
     RxWindowMeasType_T measType, uint64_t& data) = 0;

 struct transMeasurement {
   int port;
   std::pair<double, std::string> min;
   std::pair<double, std::string> max;
   std::pair<double, std::string> first;
   std::pair<double, std::string> latest;
   std::vector<uint32_t> table;
 };

    struct transMeasData
    {
        std::string startTime;
        std::string endTime;
        std::vector<transMeasurement> data;
    };

    struct rxWindowMeasData
    {
        std::string startTime;
        std::string endTime;
        uint64_t data;
    };

    /**
     * Callback function for when the notification interval expires
     */
    using NotificationCbFunc = std::function<void(
        std::map<TransceiverMeasType_T, std::vector<transMeasData>>,
        std::map<RxWindowMeasType_T, std::vector<rxWindowMeasData>>)>;

    /**
     * Configure notification for measurements
     */
    virtual void configureNotification(
        uint16_t interval, NotificationCbFunc func) = 0;

    /**
     * Callback function with transceiver data for when the file upload interval
     * expires
     */
    using FileUploadCbFunc = std::function<void(
        std::map<TransceiverMeasType_T, std::vector<transMeasData>>,
        std::map<RxWindowMeasType_T, std::vector<rxWindowMeasData>>,
        std::string,
        std::string)>;

    /**
     * Configure file upload for measurements
     */
    virtual void configureFileUpload(
        uint16_t interval, FileUploadCbFunc func) = 0;

    /**
     * Enable/Disable file upload
     */
    virtual void enableFileUpload(bool enable) = 0;
} ;

}

#endif /* YANG_HANDLERS_INC_IPERFORMANCEMGMT_H_ */
