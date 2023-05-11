#ifndef _MODULE_O_RAN_PERFORMANCE_MANAGEMENT_H_
#define _MODULE_O_RAN_PERFORMANCE_MANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanPerformanceManagement.h
 * \brief     Module ORanPerformanceManagement interface
 *
 *
 * \details   This file defines the YANG module o-ran-performance-management
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-performance-management"
 *            YANG Filename:    "o-ran-performance-management.yang"
 *            Module Prefix:    "o-ran-pm"
 *            Module namespace: "urn:o-ran:performance-management:1.0"
 *
 * Add user description here
 *
 * %%->

 * <-%%
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// -----------------------------------------------------------------------------
// Common
// -----------------------------------------------------------------------------

#include "YangModule.h"

// -----------------------------------------------------------------------------
// External Modules
// -----------------------------------------------------------------------------

// Module:   ietf-yang-types
// Revision: 2013-07-15
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   ietf-hardware
// Revision:
// Notes:
#include "YangModuleIetfHardware.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"

// Module:   o-ran-processing-element
// Revision:
// Notes:
#include "YangModuleORanProcessingElement.h"

// Module:   o-ran-file-management
// Revision:
// Notes:
#include "YangModuleORanFileManagement.h"


namespace Mplane {

namespace ModuleORanPerformanceManagement_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports an optional object-unit TRANSPORT in rx-window-measurement.
// -----------------------------------------------------------------------------
class FeatureGRANULARITYTRANSPORTMEASUREMENT : public YangFeature
{
public:
 FeatureGRANULARITYTRANSPORTMEASUREMENT(uint32_t id);
 ~FeatureGRANULARITYTRANSPORTMEASUREMENT();

}; // FeatureGRANULARITYTRANSPORTMEASUREMENT

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports an optional object-unit EAXC_ID in rx-window-measurement.
// -----------------------------------------------------------------------------
class FeatureGRANULARITYEAXCIDMEASUREMENT : public YangFeature
{
public:
 FeatureGRANULARITYEAXCIDMEASUREMENT(uint32_t id);
 ~FeatureGRANULARITYEAXCIDMEASUREMENT();

}; // FeatureGRANULARITYEAXCIDMEASUREMENT


// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************
// -----------------------------------------------------------------------------
// Container:   /performance-measurement-objects
// Description: configuration for performance management and measurement-result are
//              included
// -----------------------------------------------------------------------------
class CntPerformanceMeasurementObjects : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MEASUREMENT_GROUP, // Use GrpMeasurementGroup
 };

 CntPerformanceMeasurementObjects(uint32_t id);
 ~CntPerformanceMeasurementObjects();

 YangResult_E initialise(void);

}; // CntPerformanceMeasurementObjects


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /start-and-end-time
// Description: Definition for start and end time for an event
// -----------------------------------------------------------------------------
class GrpStartAndEndTime : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_START_TIME, // LeafStartTime
   ITEM_END_TIME, // LeafEndTime
 };

 GrpStartAndEndTime(uint32_t id);
 ~GrpStartAndEndTime();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /start-and-end-time/start-time
 // Description: Start time for measurement of object stats
 // -----------------------------------------------------------------------------
 class LeafStartTime : public YangLeaf {
  public:
   LeafStartTime(uint32_t id);
   ~LeafStartTime();

 }; // LeafStartTime

 // -----------------------------------------------------------------------------
 // Leaf:        /start-and-end-time/end-time
 // Description: End time for measurement of object stats
 // -----------------------------------------------------------------------------
 class LeafEndTime : public YangLeaf {
  public:
   LeafEndTime(uint32_t id);
   ~LeafEndTime();

 }; // LeafEndTime

}; // GrpStartAndEndTime

// -----------------------------------------------------------------------------
// Grouping:    /transceiver-measurement-result-grouping
// Description: transceiver-measurement-result are listed per port-number
// -----------------------------------------------------------------------------
class GrpTransceiverMeasurementResultGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TRANSCEIVER_MEASUREMENT_RESULT, // LstTransceiverMeasurementResult
 };

 GrpTransceiverMeasurementResultGrouping(uint32_t id);
 ~GrpTransceiverMeasurementResultGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:
 // /transceiver-measurement-result-grouping/transceiver-measurement-result
 // Description: List of transceiver measurement results
 // -----------------------------------------------------------------------------
 class LstTransceiverMeasurementResult : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_OBJECT_UNIT_ID, // RefObjectUnitId
     ITEM_MIN, // CntMin
     ITEM_MAX, // CntMax
     ITEM_FIRST, // CntFirst
     ITEM_LATEST, // CntLatest
     ITEM_FREQUENY_TABLE, // LstFrequenyTable
   };

   LstTransceiverMeasurementResult(uint32_t id);
   ~LstTransceiverMeasurementResult();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/object-unit-id
   // Description: port-number is used for the object-unit-id for the
   //              transceiver-measurement-result, for which object-unit is
   //              PORT_NUMBER only
   // -----------------------------------------------------------------------------
   class RefObjectUnitId : public YangReference {
    public:
     RefObjectUnitId(uint32_t id);
     ~RefObjectUnitId();

   }; // RefObjectUnitId

   // -----------------------------------------------------------------------------
   // Container:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/min
   // Description: minimum value with recorded time are included for the
   //              measurement-object
   // -----------------------------------------------------------------------------
   class CntMin : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_VALUE, // LeafValue
       ITEM_TIME, // LeafTime
     };

     CntMin(uint32_t id);
     ~CntMin();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/min/value
     // Description: minimum value for the measurment-object
     // -----------------------------------------------------------------------------
     class LeafValue : public YangLeaf {
      public:
       LeafValue(uint32_t id);
       ~LeafValue();

     }; // LeafValue

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/min/time
     // Description: recorded time for the minimum value
     // -----------------------------------------------------------------------------
     class LeafTime : public YangLeaf {
      public:
       LeafTime(uint32_t id);
       ~LeafTime();

     }; // LeafTime

   }; // CntMin

   // -----------------------------------------------------------------------------
   // Container:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/max
   // Description: maximum value with recorded time are included for the
   //              measurement-object
   // -----------------------------------------------------------------------------
   class CntMax : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_VALUE, // LeafValue
       ITEM_TIME, // LeafTime
     };

     CntMax(uint32_t id);
     ~CntMax();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/max/value
     // Description: maximum value for the measurment-object
     // -----------------------------------------------------------------------------
     class LeafValue : public YangLeaf {
      public:
       LeafValue(uint32_t id);
       ~LeafValue();

     }; // LeafValue

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/max/time
     // Description: recorded time for the maximum value
     // -----------------------------------------------------------------------------
     class LeafTime : public YangLeaf {
      public:
       LeafTime(uint32_t id);
       ~LeafTime();

     }; // LeafTime

   }; // CntMax

   // -----------------------------------------------------------------------------
   // Container:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/first
   // Description: first value with the recorded time are included for the
   //              measurement-object
   // -----------------------------------------------------------------------------
   class CntFirst : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_VALUE, // LeafValue
       ITEM_TIME, // LeafTime
     };

     CntFirst(uint32_t id);
     ~CntFirst();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/first/value
     // Description: first value of the measurement-object
     // -----------------------------------------------------------------------------
     class LeafValue : public YangLeaf {
      public:
       LeafValue(uint32_t id);
       ~LeafValue();

     }; // LeafValue

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/first/time
     // Description: recorded time for the first value
     // -----------------------------------------------------------------------------
     class LeafTime : public YangLeaf {
      public:
       LeafTime(uint32_t id);
       ~LeafTime();

     }; // LeafTime

   }; // CntFirst

   // -----------------------------------------------------------------------------
   // Container:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest
   // Description: latest value with the recorded time are included for the
   //              measurement-object
   // -----------------------------------------------------------------------------
   class CntLatest : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_VALUE, // LeafValue
       ITEM_TIME, // LeafTime
     };

     CntLatest(uint32_t id);
     ~CntLatest();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/value
     // Description: latest value of the measurement-object
     // -----------------------------------------------------------------------------
     class LeafValue : public YangLeaf {
      public:
       LeafValue(uint32_t id);
       ~LeafValue();

     }; // LeafValue

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/time
     // Description: recorded time for the latest value
     // -----------------------------------------------------------------------------
     class LeafTime : public YangLeaf {
      public:
       LeafTime(uint32_t id);
       ~LeafTime();

     }; // LeafTime

   }; // CntLatest

   // -----------------------------------------------------------------------------
   // List:
   // /transceiver-measurement-result-grouping/transceiver-measurement-result/frequeny-table
   // Description: frequency-table for the measurment-object are included per
   // bin.
   //              The configuration parameters for this frequency-table are
   //              defined by bin-count, lower-bound and upper-bound
   // -----------------------------------------------------------------------------
   class LstFrequenyTable : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstFrequenyTable(uint32_t id);
     ~LstFrequenyTable();

     YangResult_E initialise(void);

   }; // LstFrequenyTable

 }; // LstTransceiverMeasurementResult

}; // GrpTransceiverMeasurementResultGrouping

// -----------------------------------------------------------------------------
// Grouping:    /rx-window-measurement-result-grouping
// Description: Group of measurement reasults for rx window measurements
// -----------------------------------------------------------------------------
class GrpRxWindowMeasurementResultGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OBJECT_UNIT_ID, // ChoiceObjectUnitId
 };

 GrpRxWindowMeasurementResultGrouping(uint32_t id);
 ~GrpRxWindowMeasurementResultGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Choice:      /rx-window-measurement-result-grouping/object-unit-id
 // Description: measurement-result for the reception window stats depends on
 // the
 //              configured object-unit, RU, TRANSPORT or EAXC_ID
 // -----------------------------------------------------------------------------
 class ChoiceObjectUnitId : public YangChoice {
  public:
   // Choice Option
   enum : uint32_t {
     ITEM_RU, // OptRU
     ITEM_TRANSPORT, // OptTRANSPORT
     ITEM_EAXC_ID, // OptEAXCID
   };

   ChoiceObjectUnitId(uint32_t id);
   ~ChoiceObjectUnitId();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Option: /rx-window-measurement-result-grouping/object-unit-id[RU]
   // -----------------------------------------------------------------------------
   class OptRU : public YangChoiceOption {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_COUNT, // LeafCount
       ITEM_NAME, // RefName
     };

     OptRU(uint32_t id);
     ~OptRU();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /rx-window-measurement-result-grouping/object-unit-id[RU]/count
     // Description: the number of data packet are counted for the
     // reception
     //              window stats per O-RU.
     // -----------------------------------------------------------------------------
     class LeafCount : public YangLeaf {
      public:
       LeafCount(uint32_t id);
       ~LeafCount();

     }; // LeafCount

     // -----------------------------------------------------------------------------
     // Reference:
     // /rx-window-measurement-result-grouping/object-unit-id[RU]/name
     // Description: the name of O-RU module or one of its child ports
     //              in ietf-hardware/component is used when O-RU is
     //              selected as object-unit for the reception window
     //              stats.
     // -----------------------------------------------------------------------------
     class RefName : public YangReference {
      public:
       RefName(uint32_t id);
       ~RefName();

     }; // RefName

   }; // OptRU

   // -----------------------------------------------------------------------------
   // Option:
   // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]
   // -----------------------------------------------------------------------------
   class OptTRANSPORT : public YangChoiceOption {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_TR_MEASURED_RESULT, // LstTrMeasuredResult
     };

     OptTRANSPORT(uint32_t id);
     ~OptTRANSPORT();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // List:
     // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result
     // Description: the number of data packet are counted for the
     // reception
     //              window stats per TRANSPORT.
     // -----------------------------------------------------------------------------
     class LstTrMeasuredResult : public YangList {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_COUNT, // LeafCount
         ITEM_NAME, // RefName
       };

       LstTrMeasuredResult(uint32_t id);
       ~LstTrMeasuredResult();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf:
       // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/count
       // Description: the number of data packet are counted for the
       // reception
       //              window stats.
       // -----------------------------------------------------------------------------
       class LeafCount : public YangLeaf {
        public:
         LeafCount(uint32_t id);
         ~LeafCount();

       }; // LeafCount

       // -----------------------------------------------------------------------------
       // Reference:
       // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/name
       // Description: the name of ru-elements in
       // o-ran-processing-elements
       //              when TRANSPORT is selected as object-unit for the
       //              reception window stats.
       // -----------------------------------------------------------------------------
       class RefName : public YangReference {
        public:
         RefName(uint32_t id);
         ~RefName();

       }; // RefName

     }; // LstTrMeasuredResult

   }; // OptTRANSPORT

   // -----------------------------------------------------------------------------
   // Option:
   // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]
   // -----------------------------------------------------------------------------
   class OptEAXCID : public YangChoiceOption {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_EAXC_MEASURED_RESULT, // LstEaxcMeasuredResult
     };

     OptEAXCID(uint32_t id);
     ~OptEAXCID();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // List:
     // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result
     // Description: the number of data packet are counted for the
     // reception
     //              window stats per EAXC-ID.
     // -----------------------------------------------------------------------------
     class LstEaxcMeasuredResult : public YangList {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_EAXC_ID, // LeafEaxcId
         ITEM_COUNT, // LeafCount
         ITEM_TRANSPORT_NAME, // RefTransportName
       };

       LstEaxcMeasuredResult(uint32_t id);
       ~LstEaxcMeasuredResult();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf:
       // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/eaxc-id
       // Description: eaxc-id is used
       //              when EAXC_ID is selected as object-unit for the
       //              reception window stats. EAXC_ID consists of
       //              DU-Port-Id, Band-Selector, CC-id and RU-Port-Id to
       //              be used in header of C/U-plane data packet.
       // -----------------------------------------------------------------------------
       class LeafEaxcId : public YangLeaf {
        public:
         LeafEaxcId(uint32_t id);
         ~LeafEaxcId();

       }; // LeafEaxcId

       // -----------------------------------------------------------------------------
       // Leaf:
       // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/count
       // Description: the number of data packet are counted for the
       // reception
       //              window stats.
       // -----------------------------------------------------------------------------
       class LeafCount : public YangLeaf {
        public:
         LeafCount(uint32_t id);
         ~LeafCount();

       }; // LeafCount

       // -----------------------------------------------------------------------------
       // Reference:
       // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/transport-name
       // Description: the name of ru-elements in
       // o-ran-processing-elements for the
       //              transport information corresponding to this eaxc-id
       // -----------------------------------------------------------------------------
       class RefTransportName : public YangReference {
        public:
         RefTransportName(uint32_t id);
         ~RefTransportName();

       }; // RefTransportName

     }; // LstEaxcMeasuredResult

   }; // OptEAXCID

 }; // ChoiceObjectUnitId

}; // GrpRxWindowMeasurementResultGrouping

// -----------------------------------------------------------------------------
// Grouping:    /measurement-group
// Description: Group of measurement results
// -----------------------------------------------------------------------------
class GrpMeasurementGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ENABLE_SFTP_UPLOAD, // LeafEnableSFTPUpload
   ITEM_ENABLE_RANDOM_FILE_UPLOAD, // LeafEnableRandomFileUpload
   ITEM_TRANSCEIVER_MEASUREMENT_INTERVAL, // LeafTransceiverMeasurementInterval
   ITEM_RX_WINDOW_MEASUREMENT_INTERVAL, // LeafRxWindowMeasurementInterval
   ITEM_NOTIFICATION_INTERVAL, // LeafNotificationInterval
   ITEM_FILE_UPLOAD_INTERVAL, // LeafFileUploadInterval
   ITEM_MAX_BIN_COUNT, // LeafMaxBinCount
   ITEM_REMOTE_SFTP_UPLOADS, // LstRemoteSFTPUploads
   ITEM_TRANSCEIVER_MEASUREMENT_OBJECTS, // LstTransceiverMeasurementObjects
   ITEM_RX_WINDOW_MEASUREMENT_OBJECTS, // LstRxWindowMeasurementObjects
 };

 GrpMeasurementGroup(uint32_t id);
 ~GrpMeasurementGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/enable-SFTP-upload
 // Description: Flag to enable upload of performance measurement result files.
 // -----------------------------------------------------------------------------
 class LeafEnableSFTPUpload : public YangLeaf {
  public:
   LeafEnableSFTPUpload(uint32_t id);
   ~LeafEnableSFTPUpload();

 }; // LeafEnableSFTPUpload

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/enable-random-file-upload
 // Description: Flag to enable upload of performance measurement result files
 // at
 //              random within file-upload-interval.
 // -----------------------------------------------------------------------------
 class LeafEnableRandomFileUpload : public YangLeaf {
  public:
   LeafEnableRandomFileUpload(uint32_t id);
   ~LeafEnableRandomFileUpload();

 }; // LeafEnableRandomFileUpload

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/transceiver-measurement-interval
 // Description: measurement interval to measure the performance of transceiver
 //              measurement objects periodically.
 // -----------------------------------------------------------------------------
 class LeafTransceiverMeasurementInterval : public YangLeaf {
  public:
   LeafTransceiverMeasurementInterval(uint32_t id);
   ~LeafTransceiverMeasurementInterval();

 }; // LeafTransceiverMeasurementInterval

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/rx-window-measurement-interval
 // Description: measurement interval to measure the performance of reception
 //              window measurement objects periodically.
 // -----------------------------------------------------------------------------
 class LeafRxWindowMeasurementInterval : public YangLeaf {
  public:
   LeafRxWindowMeasurementInterval(uint32_t id);
   ~LeafRxWindowMeasurementInterval();

 }; // LeafRxWindowMeasurementInterval

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/notification-interval
 // Description: notification interval for the measurement result to be notified
 //              periodically.
 // -----------------------------------------------------------------------------
 class LeafNotificationInterval : public YangLeaf {
  public:
   LeafNotificationInterval(uint32_t id);
   ~LeafNotificationInterval();

 }; // LeafNotificationInterval

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/file-upload-interval
 // Description: file upload interval for the measurement result file to be
 //              uploaded periodically.
 // -----------------------------------------------------------------------------
 class LeafFileUploadInterval : public YangLeaf {
  public:
   LeafFileUploadInterval(uint32_t id);
   ~LeafFileUploadInterval();

 }; // LeafFileUploadInterval

 // -----------------------------------------------------------------------------
 // Leaf:        /measurement-group/max-bin-count
 // Description: indicates the maximum value of configurable bin-count for
 // frequency
 //              table in transceiver-measurement-objects as one of module
 //              capabilities.
 // -----------------------------------------------------------------------------
 class LeafMaxBinCount : public YangLeaf {
  public:
   LeafMaxBinCount(uint32_t id);
   ~LeafMaxBinCount();

 }; // LeafMaxBinCount

 // -----------------------------------------------------------------------------
 // List:        /measurement-group/remote-SFTP-uploads
 // Description: SFTP upload can be done to one or more than one SFTP servers
 // -----------------------------------------------------------------------------
 class LstRemoteSFTPUploads : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_REMOTE_SFTP_UPLOAD_PATH, // LeafRemoteSFTPUploadPath
     ITEM_O_RAN_FM_CREDENTIAL_INFORMATION, // Use GrpORanFmCredentialInformation
   };

   LstRemoteSFTPUploads(uint32_t id);
   ~LstRemoteSFTPUploads();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /measurement-group/remote-SFTP-uploads/remote-SFTP-upload-path
   // Description: URI specifying the remote location where the files are to
   // uploaded.
   //              The following format is possible:
   //              sftp://<username>@<host>[:<port>]/path
   // -----------------------------------------------------------------------------
   class LeafRemoteSFTPUploadPath : public YangLeaf {
    public:
     LeafRemoteSFTPUploadPath(uint32_t id);
     ~LeafRemoteSFTPUploadPath();

   }; // LeafRemoteSFTPUploadPath

 }; // LstRemoteSFTPUploads

 // -----------------------------------------------------------------------------
 // List:        /measurement-group/transceiver-measurement-objects
 // Description: optional list used to report transceiver measurements
 //              applicable to any O-RAN defined hardware function
 // -----------------------------------------------------------------------------
 class LstTransceiverMeasurementObjects : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_MEASUREMENT_OBJECT, // LeafMeasurementObject
     ITEM_ACTIVE, // LeafActive
     ITEM_OBJECT_UNIT, // LeafObjectUnit
     ITEM_FUNCTION, // LeafFunction
     ITEM_BIN_COUNT, // LeafBinCount
     ITEM_LOWER_BOUND, // LeafLowerBound
     ITEM_UPPER_BOUND, // LeafUpperBound
     ITEM_REPORT_INFO, // LstReportInfo
     ITEM_TRANSCEIVER_MEASUREMENT_RESULT_GROUPING, // Use
                                                   // GrpTransceiverMeasurementResultGrouping
   };

   LstTransceiverMeasurementObjects(uint32_t id);
   ~LstTransceiverMeasurementObjects();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:
   // /measurement-group/transceiver-measurement-objects/measurement-object
   // Description: Target metric to measure the performance
   // -----------------------------------------------------------------------------
   class LeafMeasurementObject : public YangLeaf {
    public:
     // Target metric to measure the performance
     enum class MeasurementObject_E : uint32_t {
       RX_POWER, // Measured Rx input power in mW for SFP or lane 1 of QSFP
       RX_POWER_LANE_2, // Measured Rx input power in mW for lane 2 of QSFP
       RX_POWER_LANE_3, // Measured Rx input power in mW for lane 3 of QSFP
       RX_POWER_LANE_4, // Measured Rx input power in mW for lane 4 of QSFP
       TX_POPWER, // Measured Tx input power in mW.
       TX_POWER_LANE_2, // Measured Tx input power in mW for lane 2 of QSFP
       TX_POWER_LANE_3, // Measured Tx input power in mW for lane 3 of QSFP
       TX_POWER_LANE_4, // Measured Tx input power in mW for lane 4 of QSFP
       TX_BIAS_COUNT, // Internally measured Tx Bias Current in mA for SFP or
                      // lane 1 of QSFP
       TX_BIAS_COUNT_LANE_2, // Internally measured Tx Bias Current in mA for
                             // lane 2 of QSFP
       TX_BIAS_COUNT_LANE_3, // Internally measured Tx Bias Current in mA for
                             // lane 3 of QSFP
       TX_BIAS_COUNT_LANE_4, // Internally measured Tx Bias Current in mA for
                             // lane 4 of QSFP
       VOLTAGE, // Internally measured transceiver supply voltage in mV
       TEMPERATURE, // Internally measured optional laser temperature in degrees
                    // Celsius.

       Num_MeasurementObject_E
     };

     LeafMeasurementObject(uint32_t id);
     ~LeafMeasurementObject();

   }; // LeafMeasurementObject

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/transceiver-measurement-objects/active
   // Description: Enable/disable the performance measurement per Object
   // -----------------------------------------------------------------------------
   class LeafActive : public YangLeaf {
    public:
     LeafActive(uint32_t id);
     ~LeafActive();

   }; // LeafActive

   // -----------------------------------------------------------------------------
   // Leaf: /measurement-group/transceiver-measurement-objects/object-unit
   // Description: unit to measure the performance per object-id.
   // -----------------------------------------------------------------------------
   class LeafObjectUnit : public YangLeaf {
    public:
     // unit to measure the performance per object-id.
     enum class ObjectUnit_E : uint32_t {
       PORT_NUMBER, // unit to measure the performance per object-id

       Num_ObjectUnit_E
     };

     LeafObjectUnit(uint32_t id);
     ~LeafObjectUnit();

   }; // LeafObjectUnit

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/transceiver-measurement-objects/function
   // Description: the value to be recorded for transceiver-measurement
   //              by real value or log 10.
   // -----------------------------------------------------------------------------
   class LeafFunction : public YangLeaf {
    public:
     // the value to be recorded for transceiver-measurement
     // by real value or log 10.
     enum class Function_E : uint32_t {
       RAW, // the value is expressed by real value.
       LOG_10, // the value is expressed by logarithm with base 10.

       Num_Function_E
     };

     LeafFunction(uint32_t id);
     ~LeafFunction();

   }; // LeafFunction

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/transceiver-measurement-objects/bin-count
   // Description: the number of bin for the frequency table.
   //              This value shall be less than max-bin-count
   // -----------------------------------------------------------------------------
   class LeafBinCount : public YangLeaf {
    public:
     LeafBinCount(uint32_t id);
     ~LeafBinCount();

   }; // LeafBinCount

   // -----------------------------------------------------------------------------
   // Leaf: /measurement-group/transceiver-measurement-objects/lower-bound
   // Description: the lower value of the first bin of frequency table.
   // -----------------------------------------------------------------------------
   class LeafLowerBound : public YangLeaf {
    public:
     LeafLowerBound(uint32_t id);
     ~LeafLowerBound();

   }; // LeafLowerBound

   // -----------------------------------------------------------------------------
   // Leaf: /measurement-group/transceiver-measurement-objects/upper-bound
   // Description: the upper value of the last bin of frequency table.
   // -----------------------------------------------------------------------------
   class LeafUpperBound : public YangLeaf {
    public:
     LeafUpperBound(uint32_t id);
     ~LeafUpperBound();

   }; // LeafUpperBound

   // -----------------------------------------------------------------------------
   // List: /measurement-group/transceiver-measurement-objects/report-info
   // Description: The reporting info to the measurement object.
   // -----------------------------------------------------------------------------
   class LstReportInfo : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstReportInfo(uint32_t id);
     ~LstReportInfo();

     YangResult_E initialise(void);

   }; // LstReportInfo

 }; // LstTransceiverMeasurementObjects

 // -----------------------------------------------------------------------------
 // List:        /measurement-group/rx-window-measurement-objects
 // Description: optional list used to report RX Window measurements
 //              applicable to O-RAN WG4 define O-RU functions
 // -----------------------------------------------------------------------------
 class LstRxWindowMeasurementObjects : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_MEASUREMENT_OBJECT, // LeafMeasurementObject
     ITEM_ACTIVE, // LeafActive
     ITEM_OBJECT_UNIT, // LeafObjectUnit
     ITEM_REPORT_INFO, // LeafReportInfo
     ITEM_RX_WINDOW_MEASUREMENT_RESULT_GROUPING, // Use
                                                 // GrpRxWindowMeasurementResultGrouping
   };

   LstRxWindowMeasurementObjects(uint32_t id);
   ~LstRxWindowMeasurementObjects();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf: /measurement-group/rx-window-measurement-objects/measurement-object
   // Description: target reception window metric to measure the performance.
   // -----------------------------------------------------------------------------
   class LeafMeasurementObject : public YangLeaf {
    public:
     // target reception window metric to measure the performance.
     enum class MeasurementObject_E : uint32_t {
       RX_ON_TIME, // the number of data packets, received on time within
                   // the reception window.
       RX_EARLY, // the number of data packets, received before
                 // the reception window.
       RX_LATE, // the number of data packets, received after
                // the reception window.
       RX_CORRUPT, // the number of data packets, which are corrupt or whose
                   // header is incorrect.
       RX_DUPL, // the number of data packets, which is duplicated with other
                // packets, received within the measurement period.
       RX_TOTAL, // the total number of received data packets.

       Num_MeasurementObject_E
     };

     LeafMeasurementObject(uint32_t id);
     ~LeafMeasurementObject();

   }; // LeafMeasurementObject

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/rx-window-measurement-objects/active
   // Description: Enable/disable the performance measurement per reception
   // window
   //              measurement object.
   // -----------------------------------------------------------------------------
   class LeafActive : public YangLeaf {
    public:
     LeafActive(uint32_t id);
     ~LeafActive();

   }; // LeafActive

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/rx-window-measurement-objects/object-unit
   // Description: unit to measure the performance per object-id.
   // -----------------------------------------------------------------------------
   class LeafObjectUnit : public YangLeaf {
    public:
     // unit to measure the performance per object-id.
     enum class ObjectUnit_E : uint32_t {
       RU, // the reception window stats are counted per hardware component.
           // This may be the parent 'module' or child 'port' component.
       TRANSPORT, // the reception window stats are counted per transport flow.
                  // When there are multiple transport flows between O-DU and
                  // O-RU, e.g. multiple sets of o-du mac address, ru mac
                  // address and
                  //      vlan-id, the reception window stats per transport flow
                  //      are counted in this case.
                  // This configuration is allowed only when O-RU supports
                  // a feature GRANULARITY-TRANSPORT-MEASUREMENT.
       EAXC_ID, // the reception window stats are counted per eAxC ID, which is
                // used in the header of receivd data packet.
                // This configuration is allowed only when O-RU supports
                // a feature GRANULARITY-EAXC-ID-MEASUREMENT.

       Num_ObjectUnit_E
     };

     LeafObjectUnit(uint32_t id);
     ~LeafObjectUnit();

   }; // LeafObjectUnit

   // -----------------------------------------------------------------------------
   // Leaf:        /measurement-group/rx-window-measurement-objects/report-info
   // Description: The reporting info to the measurement object.
   // -----------------------------------------------------------------------------
   class LeafReportInfo : public YangLeaf {
    public:
     // The reporting info to the measurement object.
     enum class ReportInfo_E : uint32_t {
       COUNT, // the number of data packet are counted for the reception
              // window stats.

       Num_ReportInfo_E
     };

     LeafReportInfo(uint32_t id);
     ~LeafReportInfo();

   }; // LeafReportInfo

 }; // LstRxWindowMeasurementObjects

}; // GrpMeasurementGroup

// -----------------------------------------------------------------------------
// Grouping:    /measurement-notification
// Description: notification may contain measurement result for transceiver-stats
//              and/or rx-window-stats
// -----------------------------------------------------------------------------
class GrpMeasurementNotification : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TRANSCEIVER_STATS, // LstTransceiverStats
   ITEM_RX_WINDOW_STATS, // LstRxWindowStats
 };

 GrpMeasurementNotification(uint32_t id);
 ~GrpMeasurementNotification();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /measurement-notification/transceiver-stats
 // Description: measurement result of transceiver-measurement per
 // measurement-object
 // -----------------------------------------------------------------------------
 class LstTransceiverStats : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_MEASUREMENT_OBJECT, // RefMeasurementObject
     ITEM_START_AND_END_TIME, // Use GrpStartAndEndTime
     ITEM_TRANSCEIVER_MEASUREMENT_RESULT_GROUPING, // Use
                                                   // GrpTransceiverMeasurementResultGrouping
   };

   LstTransceiverStats(uint32_t id);
   ~LstTransceiverStats();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference: /measurement-notification/transceiver-stats/measurement-object
   // Description: measurement-object for the transceiver-measurement
   // -----------------------------------------------------------------------------
   class RefMeasurementObject : public YangReference {
    public:
     RefMeasurementObject(uint32_t id);
     ~RefMeasurementObject();

   }; // RefMeasurementObject

 }; // LstTransceiverStats

 // -----------------------------------------------------------------------------
 // List:        /measurement-notification/rx-window-stats
 // Description: measurement result for the reception window measurement per
 //              measurement-object
 // -----------------------------------------------------------------------------
 class LstRxWindowStats : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_MEASUREMENT_OBJECT, // RefMeasurementObject
     ITEM_START_AND_END_TIME, // Use GrpStartAndEndTime
     ITEM_RX_WINDOW_MEASUREMENT_RESULT_GROUPING, // Use
                                                 // GrpRxWindowMeasurementResultGrouping
   };

   LstRxWindowStats(uint32_t id);
   ~LstRxWindowStats();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:   /measurement-notification/rx-window-stats/measurement-object
   // Description: measurement-object for the reception window measurement
   // -----------------------------------------------------------------------------
   class RefMeasurementObject : public YangReference {
    public:
     RefMeasurementObject(uint32_t id);
     ~RefMeasurementObject();

   }; // RefMeasurementObject

 }; // LstRxWindowStats

}; // GrpMeasurementNotification


// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************
// -----------------------------------------------------------------------------
// Notification:/measurement-result-stats
// Description: Notification may contain measurement results for transceiver-stats
//              and/or rx-window-stats
// -----------------------------------------------------------------------------
class NotifMeasurementResultStats : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MEASUREMENT_NOTIFICATION, // Use GrpMeasurementNotification
 };

 NotifMeasurementResultStats(uint32_t id);
 ~NotifMeasurementResultStats();

 YangResult_E initialise(void);

}; // NotifMeasurementResultStats


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-performance-management
// Description: This module defines the configuration for performance
// measurement for
//              transceiver and rx-window measurement objects.
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//              CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
//              INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//              MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//              DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//              CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
//              USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//              AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//              LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//              IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//              THE POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following
//              conditions are met:
//
//              * Redistributions of source code must retain the above copyright
//              notice, this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above
//              copyright notice, this list of conditions and the above
//              disclaimer in the documentation and/or other materials provided
//              with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived
//              from this software without specific prior written permission.
// -----------------------------------------------------------------------------
class ModuleORanPerformanceManagement : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_GRANULARITY_TRANSPORT_MEASUREMENT, // Feature
   ITEM_GRANULARITY_EAXC_ID_MEASUREMENT, // Feature
   ITEM_PERFORMANCE_MEASUREMENT_OBJECTS, // CntPerformanceMeasurementObjects
   ITEM_MEASUREMENT_RESULT_STATS, // NotifMeasurementResultStats
 };

 ModuleORanPerformanceManagement(uint32_t id);
 ~ModuleORanPerformanceManagement();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanPerformanceManagement_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_PERFORMANCE_MANAGEMENT_H_ */
