/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanPerformanceManagement.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanPerformanceManagement.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanPerformanceManagement_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports an optional
// object-unit TRANSPORT in rx-window-measurement.
// -----------------------------------------------------------------------------
FeatureGRANULARITYTRANSPORTMEASUREMENT::FeatureGRANULARITYTRANSPORTMEASUREMENT(
    uint32_t id)
    : YangFeature("GRANULARITY-TRANSPORT-MEASUREMENT", id) {}

FeatureGRANULARITYTRANSPORTMEASUREMENT::
    ~FeatureGRANULARITYTRANSPORTMEASUREMENT() {}

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports an optional
// object-unit EAXC_ID in rx-window-measurement.
// -----------------------------------------------------------------------------
FeatureGRANULARITYEAXCIDMEASUREMENT::FeatureGRANULARITYEAXCIDMEASUREMENT(
    uint32_t id)
    : YangFeature("GRANULARITY-EAXC-ID-MEASUREMENT", id) {}

FeatureGRANULARITYEAXCIDMEASUREMENT::~FeatureGRANULARITYEAXCIDMEASUREMENT() {}

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
// Container:   performance-measurement-objects
// Description: configuration for performance management and measurement-result
// are
//              included
// -----------------------------------------------------------------------------
CntPerformanceMeasurementObjects::CntPerformanceMeasurementObjects(uint32_t id)
    : YangContainer("performance-measurement-objects", id) {}

CntPerformanceMeasurementObjects::~CntPerformanceMeasurementObjects() {}

YangResult_E
CntPerformanceMeasurementObjects::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /performance-measurement-objects/measurement-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpMeasurementGroup measurementGroupInst(ITEM_MEASUREMENT_GROUP);
  measurementGroupInst.initialise();
  addGroup(measurementGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    start-and-end-time
// Description: Definition for start and end time for an event
// -----------------------------------------------------------------------------
GrpStartAndEndTime::GrpStartAndEndTime(uint32_t id)
    : YangGroup("start-and-end-time", id) {}

GrpStartAndEndTime::~GrpStartAndEndTime() {}

YangResult_E
GrpStartAndEndTime::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /start-and-end-time/start-time
  // Description: Start time for measurement of object stats
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafStartTime startTimeInst(ITEM_START_TIME);
  addLeaf(startTimeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /start-and-end-time/end-time
  // Description: End time for measurement of object stats
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafEndTime endTimeInst(ITEM_END_TIME);
  addLeaf(endTimeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /start-and-end-time/start-time
// Description: Start time for measurement of object stats
// -----------------------------------------------------------------------------
GrpStartAndEndTime::LeafStartTime::LeafStartTime(uint32_t id)
    : YangLeaf("start-time", id) {}

GrpStartAndEndTime::LeafStartTime::~LeafStartTime() {}

// -----------------------------------------------------------------------------
// Leaf:        /start-and-end-time/end-time
// Description: End time for measurement of object stats
// -----------------------------------------------------------------------------
GrpStartAndEndTime::LeafEndTime::LeafEndTime(uint32_t id)
    : YangLeaf("end-time", id) {}

GrpStartAndEndTime::LeafEndTime::~LeafEndTime() {}

// -----------------------------------------------------------------------------
// Grouping:    transceiver-measurement-result-grouping
// Description: transceiver-measurement-result are listed per port-number
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::
    GrpTransceiverMeasurementResultGrouping(uint32_t id)
    : YangGroup("transceiver-measurement-result-grouping", id) {}

GrpTransceiverMeasurementResultGrouping::
    ~GrpTransceiverMeasurementResultGrouping() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result
  // Description: List of transceiver measurement results
  // Array Key:
  // -----------------------------------------------------------------------------
  LstTransceiverMeasurementResult transceiverMeasurementResultInst(
      ITEM_TRANSCEIVER_MEASUREMENT_RESULT);
  transceiverMeasurementResultInst.initialise();
  addList(transceiverMeasurementResultInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        transceiver-measurement-result
// Description: List of transceiver measurement results
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    LstTransceiverMeasurementResult(uint32_t id)
    : YangList("transceiver-measurement-result", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    ~LstTransceiverMeasurementResult() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/object-unit-id
  // Description: port-number is used for the object-unit-id for the
  //              transceiver-measurement-result, for which object-unit is
  //              PORT_NUMBER only
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:port-reference/o-ran-interfaces:port-number
  // Units:
  // -----------------------------------------------------------------------------
  RefObjectUnitId objectUnitIdInst(ITEM_OBJECT_UNIT_ID);
  addReference(objectUnitIdInst);

  // -----------------------------------------------------------------------------
  // List:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/frequeny-table
  // Description: frequency-table for the measurment-object are included per
  // bin.
  //              The configuration parameters for this frequency-table are
  //              defined by bin-count, lower-bound and upper-bound
  // Array Key:
  // -----------------------------------------------------------------------------
  LstFrequenyTable frequenyTableInst(ITEM_FREQUENY_TABLE);
  frequenyTableInst.initialise();
  addList(frequenyTableInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/min
  // Description: minimum value with recorded time are included for the
  //              measurement-object
  // -----------------------------------------------------------------------------
  CntMin minInst(ITEM_MIN);
  minInst.initialise();
  addContainer(minInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/max
  // Description: maximum value with recorded time are included for the
  //              measurement-object
  // -----------------------------------------------------------------------------
  CntMax maxInst(ITEM_MAX);
  maxInst.initialise();
  addContainer(maxInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/first
  // Description: first value with the recorded time are included for the
  //              measurement-object
  // -----------------------------------------------------------------------------
  CntFirst firstInst(ITEM_FIRST);
  firstInst.initialise();
  addContainer(firstInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest
  // Description: latest value with the recorded time are included for the
  //              measurement-object
  // -----------------------------------------------------------------------------
  CntLatest latestInst(ITEM_LATEST);
  latestInst.initialise();
  addContainer(latestInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/object-unit-id
// Description: port-number is used for the object-unit-id for the
//              transceiver-measurement-result, for which object-unit is
//              PORT_NUMBER only
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    RefObjectUnitId::RefObjectUnitId(uint32_t id)
    : YangReference(
          "object-unit-id",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "o-ran-interfaces:port-reference/o-ran-interfaces:port-number") {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    RefObjectUnitId::~RefObjectUnitId() {}

// -----------------------------------------------------------------------------
// List:        frequeny-table
// Description: frequency-table for the measurment-object are included per bin.
//              The configuration parameters for this frequency-table are
//              defined by bin-count, lower-bound and upper-bound
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    LstFrequenyTable::LstFrequenyTable(uint32_t id)
    : YangList("frequeny-table", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    LstFrequenyTable::~LstFrequenyTable() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    LstFrequenyTable::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   min
// Description: minimum value with recorded time are included for the
//              measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::CntMin(uint32_t id)
    : YangContainer("min", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::~CntMin() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/min/value
  // Description: minimum value for the measurment-object
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafValue valueInst(ITEM_VALUE);
  addLeaf(valueInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/min/time
  // Description: recorded time for the minimum value
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafTime timeInst(ITEM_TIME);
  addLeaf(timeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/min/value
// Description: minimum value for the measurment-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::LeafValue::LeafValue(uint32_t id)
    : YangLeaf("value", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::LeafValue::~LeafValue() {}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/min/time
// Description: recorded time for the minimum value
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::LeafTime::LeafTime(uint32_t id)
    : YangLeaf("time", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMin::LeafTime::~LeafTime() {}

// -----------------------------------------------------------------------------
// Container:   max
// Description: maximum value with recorded time are included for the
//              measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::CntMax(uint32_t id)
    : YangContainer("max", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::~CntMax() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/max/value
  // Description: maximum value for the measurment-object
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafValue valueInst(ITEM_VALUE);
  addLeaf(valueInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/max/time
  // Description: recorded time for the maximum value
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafTime timeInst(ITEM_TIME);
  addLeaf(timeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/max/value
// Description: maximum value for the measurment-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::LeafValue::LeafValue(uint32_t id)
    : YangLeaf("value", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::LeafValue::~LeafValue() {}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/max/time
// Description: recorded time for the maximum value
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::LeafTime::LeafTime(uint32_t id)
    : YangLeaf("time", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntMax::LeafTime::~LeafTime() {}

// -----------------------------------------------------------------------------
// Container:   first
// Description: first value with the recorded time are included for the
//              measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::CntFirst(uint32_t id)
    : YangContainer("first", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::~CntFirst() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/first/value
  // Description: first value of the measurement-object
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafValue valueInst(ITEM_VALUE);
  addLeaf(valueInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/first/time
  // Description: recorded time for the first value
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafTime timeInst(ITEM_TIME);
  addLeaf(timeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/first/value
// Description: first value of the measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::LeafValue::LeafValue(uint32_t id)
    : YangLeaf("value", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::LeafValue::~LeafValue() {}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/first/time
// Description: recorded time for the first value
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::LeafTime::LeafTime(uint32_t id)
    : YangLeaf("time", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntFirst::LeafTime::~LeafTime() {}

// -----------------------------------------------------------------------------
// Container:   latest
// Description: latest value with the recorded time are included for the
//              measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::CntLatest(uint32_t id)
    : YangContainer("latest", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::~CntLatest() {}

YangResult_E
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/value
  // Description: latest value of the measurement-object
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafValue valueInst(ITEM_VALUE);
  addLeaf(valueInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/time
  // Description: recorded time for the latest value
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafTime timeInst(ITEM_TIME);
  addLeaf(timeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/value
// Description: latest value of the measurement-object
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::LeafValue::LeafValue(uint32_t id)
    : YangLeaf("value", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::LeafValue::~LeafValue() {}

// -----------------------------------------------------------------------------
// Leaf:
// /transceiver-measurement-result-grouping/transceiver-measurement-result/latest/time
// Description: recorded time for the latest value
// -----------------------------------------------------------------------------
GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::LeafTime::LeafTime(uint32_t id)
    : YangLeaf("time", id) {}

GrpTransceiverMeasurementResultGrouping::LstTransceiverMeasurementResult::
    CntLatest::LeafTime::~LeafTime() {}

// -----------------------------------------------------------------------------
// Grouping:    rx-window-measurement-result-grouping
// Description: Group of measurement reasults for rx window measurements
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::GrpRxWindowMeasurementResultGrouping(
    uint32_t id)
    : YangGroup("rx-window-measurement-result-grouping", id) {}

GrpRxWindowMeasurementResultGrouping::~GrpRxWindowMeasurementResultGrouping() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Choice:      /rx-window-measurement-result-grouping/object-unit-id
  // Description: measurement-result for the reception window stats depends on
  // the
  //              configured object-unit, RU, TRANSPORT or EAXC_ID
  // Type:        ObjectUnitId_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceObjectUnitId objectUnitIdInst(ITEM_OBJECT_UNIT_ID);
  objectUnitIdInst.initialise();
  addChoice(objectUnitIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Choice:      object-unit-id
// Description: measurement-result for the reception window stats depends on the
//              configured object-unit, RU, TRANSPORT or EAXC_ID
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::ChoiceObjectUnitId(
    uint32_t id)
    : YangChoice("object-unit-id", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::
    ~ChoiceObjectUnitId() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptRU RU(ITEM_RU);
  RU.initialise();
  addOption(RU);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptTRANSPORT TRANSPORT(ITEM_TRANSPORT);
  TRANSPORT.initialise();
  addOption(TRANSPORT);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptEAXCID EAXCID(ITEM_EAXC_ID);
  EAXCID.initialise();
  addOption(EAXCID);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /rx-window-measurement-result-grouping/object-unit-id[RU]
// -------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::OptRU(
    uint32_t id)
    : YangChoiceOption("RU", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::~OptRU() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf: /rx-window-measurement-result-grouping/object-unit-id[RU]/count
  // Description: the number of data packet are counted for the reception
  //              window stats per O-RU.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafCount countInst(ITEM_COUNT);
  addLeaf(countInst);

  // -----------------------------------------------------------------------------
  // Reference:   /rx-window-measurement-result-grouping/object-unit-id[RU]/name
  // Description: the name of O-RU module or one of its child ports
  //              in ietf-hardware/component is used when O-RU is selected as
  //              object-unit for the reception window stats.
  // Ref: /ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /rx-window-measurement-result-grouping/object-unit-id[RU]/count
// Description: the number of data packet are counted for the reception
//              window stats per O-RU.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::LeafCount::
    LeafCount(uint32_t id)
    : YangLeaf("count", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::LeafCount::
    ~LeafCount() {}

// -----------------------------------------------------------------------------
// Reference:   /rx-window-measurement-result-grouping/object-unit-id[RU]/name
// Description: the name of O-RU module or one of its child ports
//              in ietf-hardware/component is used when O-RU is selected as
//              object-unit for the reception window stats.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::RefName::
    RefName(uint32_t id)
    : YangReference(
          "name",
          id,
          "/ietf-hardware:hardware/ietf-hardware:component/"
          "ietf-hardware:name") {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptRU::RefName::
    ~RefName() {}

// -------------------------------------------------------------------------
// Option:      /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]
// -------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    OptTRANSPORT(uint32_t id)
    : YangChoiceOption("TRANSPORT", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    ~OptTRANSPORT() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // List:
  // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result
  // Description: the number of data packet are counted for the reception
  //              window stats per TRANSPORT.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstTrMeasuredResult trMeasuredResultInst(ITEM_TR_MEASURED_RESULT);
  trMeasuredResultInst.initialise();
  addList(trMeasuredResultInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        tr-measured-result
// Description: the number of data packet are counted for the reception
//              window stats per TRANSPORT.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::LstTrMeasuredResult(uint32_t id)
    : YangList("tr-measured-result", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::~LstTrMeasuredResult() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/count
  // Description: the number of data packet are counted for the reception
  //              window stats.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafCount countInst(ITEM_COUNT);
  addLeaf(countInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/name
  // Description: the name of ru-elements in o-ran-processing-elements
  //              when TRANSPORT is selected as object-unit for the reception
  //              window stats.
  // Ref:
  // /o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/count
// Description: the number of data packet are counted for the reception
//              window stats.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::LeafCount::LeafCount(uint32_t id)
    : YangLeaf("count", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::LeafCount::~LeafCount() {}

// -----------------------------------------------------------------------------
// Reference:
// /rx-window-measurement-result-grouping/object-unit-id[TRANSPORT]/tr-measured-result/name
// Description: the name of ru-elements in o-ran-processing-elements
//              when TRANSPORT is selected as object-unit for the reception
//              window stats.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::RefName::RefName(uint32_t id)
    : YangReference(
          "name",
          id,
          "/o-ran-processing-element:processing-elements/"
          "o-ran-processing-element:ru-elements/"
          "o-ran-processing-element:name") {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptTRANSPORT::
    LstTrMeasuredResult::RefName::~RefName() {}

// -------------------------------------------------------------------------
// Option:      /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]
// -------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::OptEAXCID(
    uint32_t id)
    : YangChoiceOption("EAXC_ID", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    ~OptEAXCID() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // List:
  // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result
  // Description: the number of data packet are counted for the reception
  //              window stats per EAXC-ID.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstEaxcMeasuredResult eaxcMeasuredResultInst(ITEM_EAXC_MEASURED_RESULT);
  eaxcMeasuredResultInst.initialise();
  addList(eaxcMeasuredResultInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        eaxc-measured-result
// Description: the number of data packet are counted for the reception
//              window stats per EAXC-ID.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::LstEaxcMeasuredResult(uint32_t id)
    : YangList("eaxc-measured-result", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::~LstEaxcMeasuredResult() {}

YangResult_E
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/eaxc-id
  // Description: eaxc-id is used
  //              when EAXC_ID is selected as object-unit for the reception
  //              window stats.
  //              EAXC_ID consists of DU-Port-Id, Band-Selector, CC-id and
  //              RU-Port-Id to be used in header of C/U-plane data packet.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafEaxcId eaxcIdInst(ITEM_EAXC_ID);
  addLeaf(eaxcIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/count
  // Description: the number of data packet are counted for the reception
  //              window stats.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafCount countInst(ITEM_COUNT);
  addLeaf(countInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/transport-name
  // Description: the name of ru-elements in o-ran-processing-elements for the
  //              transport information corresponding to this eaxc-id
  // Ref:
  // /o-ran-processing-element:processing-elements/o-ran-processing-element:ru-elements/o-ran-processing-element:name
  // Units:
  // -----------------------------------------------------------------------------
  RefTransportName transportNameInst(ITEM_TRANSPORT_NAME);
  addReference(transportNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/eaxc-id
// Description: eaxc-id is used
//              when EAXC_ID is selected as object-unit for the reception
//              window stats.
//              EAXC_ID consists of DU-Port-Id, Band-Selector, CC-id and
//              RU-Port-Id to be used in header of C/U-plane data packet.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::LeafEaxcId::LeafEaxcId(uint32_t id)
    : YangLeaf("eaxc-id", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::LeafEaxcId::~LeafEaxcId() {}

// -----------------------------------------------------------------------------
// Leaf:
// /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/count
// Description: the number of data packet are counted for the reception
//              window stats.
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::LeafCount::LeafCount(uint32_t id)
    : YangLeaf("count", id) {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::LeafCount::~LeafCount() {}

// -----------------------------------------------------------------------------
// Reference:
// /rx-window-measurement-result-grouping/object-unit-id[EAXC_ID]/eaxc-measured-result/transport-name
// Description: the name of ru-elements in o-ran-processing-elements for the
//              transport information corresponding to this eaxc-id
// -----------------------------------------------------------------------------
GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::RefTransportName::RefTransportName(uint32_t id)
    : YangReference(
          "transport-name",
          id,
          "/o-ran-processing-element:processing-elements/"
          "o-ran-processing-element:ru-elements/"
          "o-ran-processing-element:name") {}

GrpRxWindowMeasurementResultGrouping::ChoiceObjectUnitId::OptEAXCID::
    LstEaxcMeasuredResult::RefTransportName::~RefTransportName() {}

// -----------------------------------------------------------------------------
// Grouping:    measurement-group
// Description: Group of measurement results
// -----------------------------------------------------------------------------
GrpMeasurementGroup::GrpMeasurementGroup(uint32_t id)
    : YangGroup("measurement-group", id) {}

GrpMeasurementGroup::~GrpMeasurementGroup() {}

YangResult_E
GrpMeasurementGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/enable-SFTP-upload
  // Description: Flag to enable upload of performance measurement result files.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnableSFTPUpload enableSFTPUploadInst(ITEM_ENABLE_SFTP_UPLOAD);
  addLeaf(enableSFTPUploadInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/enable-random-file-upload
  // Description: Flag to enable upload of performance measurement result files
  // at
  //              random within file-upload-interval.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnableRandomFileUpload enableRandomFileUploadInst(
      ITEM_ENABLE_RANDOM_FILE_UPLOAD);
  addLeaf(enableRandomFileUploadInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-interval
  // Description: measurement interval to measure the performance of transceiver
  //              measurement objects periodically.
  // Type:        uint16
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafTransceiverMeasurementInterval transceiverMeasurementIntervalInst(
      ITEM_TRANSCEIVER_MEASUREMENT_INTERVAL);
  addLeaf(transceiverMeasurementIntervalInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/rx-window-measurement-interval
  // Description: measurement interval to measure the performance of reception
  //              window measurement objects periodically.
  // Type:        uint16
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafRxWindowMeasurementInterval rxWindowMeasurementIntervalInst(
      ITEM_RX_WINDOW_MEASUREMENT_INTERVAL);
  addLeaf(rxWindowMeasurementIntervalInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/notification-interval
  // Description: notification interval for the measurement result to be
  // notified
  //              periodically.
  // Type:        uint16
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafNotificationInterval notificationIntervalInst(ITEM_NOTIFICATION_INTERVAL);
  addLeaf(notificationIntervalInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/file-upload-interval
  // Description: file upload interval for the measurement result file to be
  //              uploaded periodically.
  // Type:        uint16
  // Units:       seconds
  // -----------------------------------------------------------------------------
  LeafFileUploadInterval fileUploadIntervalInst(ITEM_FILE_UPLOAD_INTERVAL);
  addLeaf(fileUploadIntervalInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/max-bin-count
  // Description: indicates the maximum value of configurable bin-count for
  // frequency
  //              table in transceiver-measurement-objects as one of module
  //              capabilities.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaxBinCount maxBinCountInst(ITEM_MAX_BIN_COUNT);
  addLeaf(maxBinCountInst);

  // -----------------------------------------------------------------------------
  // List:        /measurement-group/remote-SFTP-uploads
  // Description: SFTP upload can be done to one or more than one SFTP servers
  // Array Key:
  // -----------------------------------------------------------------------------
  LstRemoteSFTPUploads remoteSFTPUploadsInst(ITEM_REMOTE_SFTP_UPLOADS);
  remoteSFTPUploadsInst.initialise();
  addList(remoteSFTPUploadsInst);

  // -----------------------------------------------------------------------------
  // List:        /measurement-group/transceiver-measurement-objects
  // Description: optional list used to report transceiver measurements
  //              applicable to any O-RAN defined hardware function
  // Array Key:
  // -----------------------------------------------------------------------------
  LstTransceiverMeasurementObjects transceiverMeasurementObjectsInst(
      ITEM_TRANSCEIVER_MEASUREMENT_OBJECTS);
  transceiverMeasurementObjectsInst.initialise();
  addList(transceiverMeasurementObjectsInst);

  // -----------------------------------------------------------------------------
  // List:        /measurement-group/rx-window-measurement-objects
  // Description: optional list used to report RX Window measurements
  //              applicable to O-RAN WG4 define O-RU functions
  // Array Key:
  // -----------------------------------------------------------------------------
  LstRxWindowMeasurementObjects rxWindowMeasurementObjectsInst(
      ITEM_RX_WINDOW_MEASUREMENT_OBJECTS);
  rxWindowMeasurementObjectsInst.initialise();
  addList(rxWindowMeasurementObjectsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/enable-SFTP-upload
// Description: Flag to enable upload of performance measurement result files.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafEnableSFTPUpload::LeafEnableSFTPUpload(uint32_t id)
    : YangLeaf("enable-SFTP-upload", id) {}

GrpMeasurementGroup::LeafEnableSFTPUpload::~LeafEnableSFTPUpload() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/enable-random-file-upload
// Description: Flag to enable upload of performance measurement result files at
//              random within file-upload-interval.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafEnableRandomFileUpload::LeafEnableRandomFileUpload(
    uint32_t id)
    : YangLeaf("enable-random-file-upload", id) {}

GrpMeasurementGroup::LeafEnableRandomFileUpload::~LeafEnableRandomFileUpload() {
}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-interval
// Description: measurement interval to measure the performance of transceiver
//              measurement objects periodically.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafTransceiverMeasurementInterval::
    LeafTransceiverMeasurementInterval(uint32_t id)
    : YangLeaf("transceiver-measurement-interval", id) {}

GrpMeasurementGroup::LeafTransceiverMeasurementInterval::
    ~LeafTransceiverMeasurementInterval() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/rx-window-measurement-interval
// Description: measurement interval to measure the performance of reception
//              window measurement objects periodically.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafRxWindowMeasurementInterval::
    LeafRxWindowMeasurementInterval(uint32_t id)
    : YangLeaf("rx-window-measurement-interval", id) {}

GrpMeasurementGroup::LeafRxWindowMeasurementInterval::
    ~LeafRxWindowMeasurementInterval() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/notification-interval
// Description: notification interval for the measurement result to be notified
//              periodically.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafNotificationInterval::LeafNotificationInterval(
    uint32_t id)
    : YangLeaf("notification-interval", id) {}

GrpMeasurementGroup::LeafNotificationInterval::~LeafNotificationInterval() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/file-upload-interval
// Description: file upload interval for the measurement result file to be
//              uploaded periodically.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafFileUploadInterval::LeafFileUploadInterval(uint32_t id)
    : YangLeaf("file-upload-interval", id) {}

GrpMeasurementGroup::LeafFileUploadInterval::~LeafFileUploadInterval() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/max-bin-count
// Description: indicates the maximum value of configurable bin-count for
// frequency
//              table in transceiver-measurement-objects as one of module
//              capabilities.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LeafMaxBinCount::LeafMaxBinCount(uint32_t id)
    : YangLeaf("max-bin-count", id) {}

GrpMeasurementGroup::LeafMaxBinCount::~LeafMaxBinCount() {}

// -----------------------------------------------------------------------------
// List:        remote-SFTP-uploads
// Description: SFTP upload can be done to one or more than one SFTP servers
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRemoteSFTPUploads::LstRemoteSFTPUploads(uint32_t id)
    : YangList("remote-SFTP-uploads", id) {}

GrpMeasurementGroup::LstRemoteSFTPUploads::~LstRemoteSFTPUploads() {}

YangResult_E
GrpMeasurementGroup::LstRemoteSFTPUploads::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/remote-SFTP-uploads/remote-SFTP-upload-path
  // Description: URI specifying the remote location where the files are to
  // uploaded.
  //              The following format is possible:
  //              sftp://<username>@<host>[:<port>]/path
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafRemoteSFTPUploadPath remoteSFTPUploadPathInst(
      ITEM_REMOTE_SFTP_UPLOAD_PATH);
  addLeaf(remoteSFTPUploadPathInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /measurement-group/remote-SFTP-uploads/o-ran-fm:credential-information
  // Module: o-ran-file-management
  // Description:
  // -----------------------------------------------------------------------------
  ModuleORanFileManagement_NS::GrpCredentialInformation
      oRanFmCredentialInformationInst(ITEM_O_RAN_FM_CREDENTIAL_INFORMATION);
  oRanFmCredentialInformationInst.initialise();
  addGroup(oRanFmCredentialInformationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/remote-SFTP-uploads/remote-SFTP-upload-path
// Description: URI specifying the remote location where the files are to
// uploaded.
//              The following format is possible:
//              sftp://<username>@<host>[:<port>]/path
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRemoteSFTPUploads::LeafRemoteSFTPUploadPath::
    LeafRemoteSFTPUploadPath(uint32_t id)
    : YangLeaf("remote-SFTP-upload-path", id) {}

GrpMeasurementGroup::LstRemoteSFTPUploads::LeafRemoteSFTPUploadPath::
    ~LeafRemoteSFTPUploadPath() {}

// -----------------------------------------------------------------------------
// List:        transceiver-measurement-objects
// Description: optional list used to report transceiver measurements
//              applicable to any O-RAN defined hardware function
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::
    LstTransceiverMeasurementObjects(uint32_t id)
    : YangList("transceiver-measurement-objects", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::
    ~LstTransceiverMeasurementObjects() {}

YangResult_E
GrpMeasurementGroup::LstTransceiverMeasurementObjects::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /measurement-group/transceiver-measurement-objects/measurement-object
  // Description: Target metric to measure the performance
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafMeasurementObject measurementObjectInst(ITEM_MEASUREMENT_OBJECT);
  addLeaf(measurementObjectInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/active
  // Description: Enable/disable the performance measurement per Object
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafActive activeInst(ITEM_ACTIVE);
  addLeaf(activeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/object-unit
  // Description: unit to measure the performance per object-id.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafObjectUnit objectUnitInst(ITEM_OBJECT_UNIT);
  addLeaf(objectUnitInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/function
  // Description: the value to be recorded for transceiver-measurement
  //              by real value or log 10.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafFunction functionInst(ITEM_FUNCTION);
  addLeaf(functionInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/bin-count
  // Description: the number of bin for the frequency table.
  //              This value shall be less than max-bin-count
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafBinCount binCountInst(ITEM_BIN_COUNT);
  addLeaf(binCountInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/lower-bound
  // Description: the lower value of the first bin of frequency table.
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafLowerBound lowerBoundInst(ITEM_LOWER_BOUND);
  addLeaf(lowerBoundInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/transceiver-measurement-objects/upper-bound
  // Description: the upper value of the last bin of frequency table.
  // Type:        dec64
  // Units:
  // -----------------------------------------------------------------------------
  LeafUpperBound upperBoundInst(ITEM_UPPER_BOUND);
  addLeaf(upperBoundInst);

  // -----------------------------------------------------------------------------
  // List:        /measurement-group/transceiver-measurement-objects/report-info
  // Description: The reporting info to the measurement object.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstReportInfo reportInfoInst(ITEM_REPORT_INFO);
  reportInfoInst.initialise();
  addList(reportInfoInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /measurement-group/transceiver-measurement-objects/transceiver-measurement-result-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpTransceiverMeasurementResultGrouping
      transceiverMeasurementResultGroupingInst(
          ITEM_TRANSCEIVER_MEASUREMENT_RESULT_GROUPING);
  transceiverMeasurementResultGroupingInst.initialise();
  addGroup(transceiverMeasurementResultGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /measurement-group/transceiver-measurement-objects/measurement-object
// Description: Target metric to measure the performance
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafMeasurementObject::
    LeafMeasurementObject(uint32_t id)
    : YangLeaf("measurement-object", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafMeasurementObject::
    ~LeafMeasurementObject() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/active
// Description: Enable/disable the performance measurement per Object
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafActive::LeafActive(
    uint32_t id)
    : YangLeaf("active", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafActive::
    ~LeafActive() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/object-unit
// Description: unit to measure the performance per object-id.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafObjectUnit::
    LeafObjectUnit(uint32_t id)
    : YangLeaf("object-unit", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafObjectUnit::
    ~LeafObjectUnit() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/function
// Description: the value to be recorded for transceiver-measurement
//              by real value or log 10.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafFunction::
    LeafFunction(uint32_t id)
    : YangLeaf("function", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafFunction::
    ~LeafFunction() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/bin-count
// Description: the number of bin for the frequency table.
//              This value shall be less than max-bin-count
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafBinCount::
    LeafBinCount(uint32_t id)
    : YangLeaf("bin-count", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafBinCount::
    ~LeafBinCount() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/lower-bound
// Description: the lower value of the first bin of frequency table.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafLowerBound::
    LeafLowerBound(uint32_t id)
    : YangLeaf("lower-bound", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafLowerBound::
    ~LeafLowerBound() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/transceiver-measurement-objects/upper-bound
// Description: the upper value of the last bin of frequency table.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafUpperBound::
    LeafUpperBound(uint32_t id)
    : YangLeaf("upper-bound", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LeafUpperBound::
    ~LeafUpperBound() {}

// -----------------------------------------------------------------------------
// List:        report-info
// Description: The reporting info to the measurement object.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LstReportInfo::
    LstReportInfo(uint32_t id)
    : YangList("report-info", id) {}

GrpMeasurementGroup::LstTransceiverMeasurementObjects::LstReportInfo::
    ~LstReportInfo() {}

YangResult_E
GrpMeasurementGroup::LstTransceiverMeasurementObjects::LstReportInfo::
    initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        rx-window-measurement-objects
// Description: optional list used to report RX Window measurements
//              applicable to O-RAN WG4 define O-RU functions
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRxWindowMeasurementObjects::
    LstRxWindowMeasurementObjects(uint32_t id)
    : YangList("rx-window-measurement-objects", id) {}

GrpMeasurementGroup::LstRxWindowMeasurementObjects::
    ~LstRxWindowMeasurementObjects() {}

YangResult_E
GrpMeasurementGroup::LstRxWindowMeasurementObjects::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /measurement-group/rx-window-measurement-objects/measurement-object
  // Description: target reception window metric to measure the performance.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafMeasurementObject measurementObjectInst(ITEM_MEASUREMENT_OBJECT);
  addLeaf(measurementObjectInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/rx-window-measurement-objects/active
  // Description: Enable/disable the performance measurement per reception
  // window
  //              measurement object.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafActive activeInst(ITEM_ACTIVE);
  addLeaf(activeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/rx-window-measurement-objects/object-unit
  // Description: unit to measure the performance per object-id.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafObjectUnit objectUnitInst(ITEM_OBJECT_UNIT);
  addLeaf(objectUnitInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-group/rx-window-measurement-objects/report-info
  // Description: The reporting info to the measurement object.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafReportInfo reportInfoInst(ITEM_REPORT_INFO);
  addLeaf(reportInfoInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /measurement-group/rx-window-measurement-objects/rx-window-measurement-result-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpRxWindowMeasurementResultGrouping rxWindowMeasurementResultGroupingInst(
      ITEM_RX_WINDOW_MEASUREMENT_RESULT_GROUPING);
  rxWindowMeasurementResultGroupingInst.initialise();
  addGroup(rxWindowMeasurementResultGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /measurement-group/rx-window-measurement-objects/measurement-object
// Description: target reception window metric to measure the performance.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafMeasurementObject::
    LeafMeasurementObject(uint32_t id)
    : YangLeaf("measurement-object", id) {}

GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafMeasurementObject::
    ~LeafMeasurementObject() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/rx-window-measurement-objects/active
// Description: Enable/disable the performance measurement per reception window
//              measurement object.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafActive::LeafActive(
    uint32_t id)
    : YangLeaf("active", id) {}

GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafActive::~LeafActive() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/rx-window-measurement-objects/object-unit
// Description: unit to measure the performance per object-id.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafObjectUnit::
    LeafObjectUnit(uint32_t id)
    : YangLeaf("object-unit", id) {}

GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafObjectUnit::
    ~LeafObjectUnit() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-group/rx-window-measurement-objects/report-info
// Description: The reporting info to the measurement object.
// -----------------------------------------------------------------------------
GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafReportInfo::
    LeafReportInfo(uint32_t id)
    : YangLeaf("report-info", id) {}

GrpMeasurementGroup::LstRxWindowMeasurementObjects::LeafReportInfo::
    ~LeafReportInfo() {}

// -----------------------------------------------------------------------------
// Grouping:    measurement-notification
// Description: notification may contain measurement result for
// transceiver-stats
//              and/or rx-window-stats
// -----------------------------------------------------------------------------
GrpMeasurementNotification::GrpMeasurementNotification(uint32_t id)
    : YangGroup("measurement-notification", id) {}

GrpMeasurementNotification::~GrpMeasurementNotification() {}

YangResult_E
GrpMeasurementNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /measurement-notification/transceiver-stats
  // Description: measurement result of transceiver-measurement per
  // measurement-object Array Key:
  // -----------------------------------------------------------------------------
  LstTransceiverStats transceiverStatsInst(ITEM_TRANSCEIVER_STATS);
  transceiverStatsInst.initialise();
  addList(transceiverStatsInst);

  // -----------------------------------------------------------------------------
  // List:        /measurement-notification/rx-window-stats
  // Description: measurement result for the reception window measurement per
  //              measurement-object
  // Array Key:
  // -----------------------------------------------------------------------------
  LstRxWindowStats rxWindowStatsInst(ITEM_RX_WINDOW_STATS);
  rxWindowStatsInst.initialise();
  addList(rxWindowStatsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        transceiver-stats
// Description: measurement result of transceiver-measurement per
// measurement-object
// -----------------------------------------------------------------------------
GrpMeasurementNotification::LstTransceiverStats::LstTransceiverStats(
    uint32_t id)
    : YangList("transceiver-stats", id) {}

GrpMeasurementNotification::LstTransceiverStats::~LstTransceiverStats() {}

YangResult_E
GrpMeasurementNotification::LstTransceiverStats::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /measurement-notification/transceiver-stats/measurement-object
  // Description: measurement-object for the transceiver-measurement
  // Ref:
  // /performance-measurement-objects/transceiver-measurement-objects/measurement-object
  // Units:
  // -----------------------------------------------------------------------------
  RefMeasurementObject measurementObjectInst(ITEM_MEASUREMENT_OBJECT);
  addReference(measurementObjectInst);

  // -----------------------------------------------------------------------------
  // Uses:        /measurement-notification/transceiver-stats/start-and-end-time
  // Description:
  // -----------------------------------------------------------------------------
  GrpStartAndEndTime startAndEndTimeInst(ITEM_START_AND_END_TIME);
  startAndEndTimeInst.initialise();
  addGroup(startAndEndTimeInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /measurement-notification/transceiver-stats/transceiver-measurement-result-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpTransceiverMeasurementResultGrouping
      transceiverMeasurementResultGroupingInst(
          ITEM_TRANSCEIVER_MEASUREMENT_RESULT_GROUPING);
  transceiverMeasurementResultGroupingInst.initialise();
  addGroup(transceiverMeasurementResultGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /measurement-notification/transceiver-stats/measurement-object
// Description: measurement-object for the transceiver-measurement
// -----------------------------------------------------------------------------
GrpMeasurementNotification::LstTransceiverStats::RefMeasurementObject::
    RefMeasurementObject(uint32_t id)
    : YangReference(
          "measurement-object",
          id,
          "/performance-measurement-objects/transceiver-measurement-objects/"
          "measurement-object") {}

GrpMeasurementNotification::LstTransceiverStats::RefMeasurementObject::
    ~RefMeasurementObject() {}

// -----------------------------------------------------------------------------
// List:        rx-window-stats
// Description: measurement result for the reception window measurement per
//              measurement-object
// -----------------------------------------------------------------------------
GrpMeasurementNotification::LstRxWindowStats::LstRxWindowStats(uint32_t id)
    : YangList("rx-window-stats", id) {}

GrpMeasurementNotification::LstRxWindowStats::~LstRxWindowStats() {}

YangResult_E
GrpMeasurementNotification::LstRxWindowStats::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /measurement-notification/rx-window-stats/measurement-object
  // Description: measurement-object for the reception window measurement
  // Ref:
  // /performance-measurement-objects/rx-window-measurement-objects/measurement-object
  // Units:
  // -----------------------------------------------------------------------------
  RefMeasurementObject measurementObjectInst(ITEM_MEASUREMENT_OBJECT);
  addReference(measurementObjectInst);

  // -----------------------------------------------------------------------------
  // Uses:        /measurement-notification/rx-window-stats/start-and-end-time
  // Description:
  // -----------------------------------------------------------------------------
  GrpStartAndEndTime startAndEndTimeInst(ITEM_START_AND_END_TIME);
  startAndEndTimeInst.initialise();
  addGroup(startAndEndTimeInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /measurement-notification/rx-window-stats/rx-window-measurement-result-grouping
  // Description:
  // -----------------------------------------------------------------------------
  GrpRxWindowMeasurementResultGrouping rxWindowMeasurementResultGroupingInst(
      ITEM_RX_WINDOW_MEASUREMENT_RESULT_GROUPING);
  rxWindowMeasurementResultGroupingInst.initialise();
  addGroup(rxWindowMeasurementResultGroupingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /measurement-notification/rx-window-stats/measurement-object
// Description: measurement-object for the reception window measurement
// -----------------------------------------------------------------------------
GrpMeasurementNotification::LstRxWindowStats::RefMeasurementObject::
    RefMeasurementObject(uint32_t id)
    : YangReference(
          "measurement-object",
          id,
          "/performance-measurement-objects/rx-window-measurement-objects/"
          "measurement-object") {}

GrpMeasurementNotification::LstRxWindowStats::RefMeasurementObject::
    ~RefMeasurementObject() {}

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
// Notification:measurement-result-stats
// Description: Notification may contain measurement results for
// transceiver-stats
//              and/or rx-window-stats
// -----------------------------------------------------------------------------
NotifMeasurementResultStats::NotifMeasurementResultStats(uint32_t id)
    : YangNotif("measurement-result-stats", id) {}

NotifMeasurementResultStats::~NotifMeasurementResultStats() {}

YangResult_E
NotifMeasurementResultStats::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /measurement-result-stats/measurement-notification
  // Description:
  // -----------------------------------------------------------------------------
  GrpMeasurementNotification measurementNotificationInst(
      ITEM_MEASUREMENT_NOTIFICATION);
  measurementNotificationInst.initialise();
  addGroup(measurementNotificationInst);

  return YangResult_E::OK;
}

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
ModuleORanPerformanceManagement::ModuleORanPerformanceManagement(uint32_t id)
    : YangModule(
          "o-ran-performance-management",
          "o-ran-performance-management.yang",
          "o-ran-pm",
          "urn:o-ran:performance-management:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the O-RU supports an optional
  // object-unit TRANSPORT in rx-window-measurement.
  // -----------------------------------------------------------------------------
  FeatureGRANULARITYTRANSPORTMEASUREMENT GRANULARITYTRANSPORTMEASUREMENTInst(
      ITEM_GRANULARITY_TRANSPORT_MEASUREMENT);
  addFeature(GRANULARITYTRANSPORTMEASUREMENTInst);

  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the O-RU supports an optional
  // object-unit EAXC_ID in rx-window-measurement.
  // -----------------------------------------------------------------------------
  FeatureGRANULARITYEAXCIDMEASUREMENT GRANULARITYEAXCIDMEASUREMENTInst(
      ITEM_GRANULARITY_EAXC_ID_MEASUREMENT);
  addFeature(GRANULARITYEAXCIDMEASUREMENTInst);

  // -----------------------------------------------------------------------------
  // Container:   /performance-measurement-objects
  // Description: configuration for performance management and
  // measurement-result are
  //              included
  // -----------------------------------------------------------------------------
  CntPerformanceMeasurementObjects performanceMeasurementObjectsInst(
      ITEM_PERFORMANCE_MEASUREMENT_OBJECTS);
  performanceMeasurementObjectsInst.initialise();
  addContainer(performanceMeasurementObjectsInst);

  // -----------------------------------------------------------------------------
  // Notification:/measurement-result-stats
  // Description: Notification may contain measurement results for
  // transceiver-stats
  //              and/or rx-window-stats
  // -----------------------------------------------------------------------------
  NotifMeasurementResultStats measurementResultStatsInst(
      ITEM_MEASUREMENT_RESULT_STATS);
  measurementResultStatsInst.initialise();
  addNotification(measurementResultStatsInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanPerformanceManagement::~ModuleORanPerformanceManagement() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanPerformanceManagement::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanPerformanceManagement>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanPerformanceManagement::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
