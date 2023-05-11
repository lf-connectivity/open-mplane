/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLaaOperations.cpp
 * \brief     Module ORanLaaOperations interface
 *
 *
 * \details   This file defines the YANG module o-ran-laa-operations interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-laa-operations"
 *            YANG Filename:    "o-ran-laa-operations.yang"
 *            Module Prefix:    "o-ran-laa-operations"
 *            Module namespace: "urn:o-ran:laa-operations:1.0"
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
#include "YangModuleORanLaaOperations.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanLaaOperations_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************

// *****************************************************************************
// Leafs
// *****************************************************************************

// *****************************************************************************
// References
// *****************************************************************************

// *****************************************************************************
// Containers
// *****************************************************************************

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    band-configuration
// Description: Grouping for band configuration
// -----------------------------------------------------------------------------
GrpBandConfiguration::GrpBandConfiguration(uint32_t id)
    : YangGroup("band-configuration", id) {}

GrpBandConfiguration::~GrpBandConfiguration() {}

YangResult_E
GrpBandConfiguration::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /band-configuration/band-number
  // Description: This value indicates the list of bands supported as per the
  // document,
  //              3GPP TS 36.104 V14.2.0 (2016-12), 'Section 5.5 Operation
  //              bands'.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafBandNumber bandNumberInst(ITEM_BAND_NUMBER);
  addLeaf(bandNumberInst);

  // -----------------------------------------------------------------------------
  // List:        /band-configuration/channel-center-frequency
  // Description: This value indicates carrier center frequency in KHz
  // Array Key:
  // -----------------------------------------------------------------------------
  LstChannelCenterFrequency channelCenterFrequencyInst(
      ITEM_CHANNEL_CENTER_FREQUENCY);
  channelCenterFrequencyInst.initialise();
  addList(channelCenterFrequencyInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /band-configuration/band-number
// Description: This value indicates the list of bands supported as per the
// document,
//              3GPP TS 36.104 V14.2.0 (2016-12), 'Section 5.5 Operation bands'.
// -----------------------------------------------------------------------------
GrpBandConfiguration::LeafBandNumber::LeafBandNumber(uint32_t id)
    : YangLeaf("band-number", id) {}

GrpBandConfiguration::LeafBandNumber::~LeafBandNumber() {}

// -----------------------------------------------------------------------------
// List:        channel-center-frequency
// Description: This value indicates carrier center frequency in KHz
// -----------------------------------------------------------------------------
GrpBandConfiguration::LstChannelCenterFrequency::LstChannelCenterFrequency(
    uint32_t id)
    : YangList("channel-center-frequency", id) {}

GrpBandConfiguration::LstChannelCenterFrequency::~LstChannelCenterFrequency() {}

YangResult_E
GrpBandConfiguration::LstChannelCenterFrequency::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    measurement-parameters
// Description: Grouping for measurement parameters
// -----------------------------------------------------------------------------
GrpMeasurementParameters::GrpMeasurementParameters(uint32_t id)
    : YangGroup("measurement-parameters", id) {}

GrpMeasurementParameters::~GrpMeasurementParameters() {}

YangResult_E
GrpMeasurementParameters::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-parameters/duration-per-channel
  // Description: This value indicates measurement duration per channel in
  // milliseconds. Type:        uint16 Units:       milliseconds
  // -----------------------------------------------------------------------------
  LeafDurationPerChannel durationPerChannelInst(ITEM_DURATION_PER_CHANNEL);
  addLeaf(durationPerChannelInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /measurement-parameters/maximum-response-time
  // Description: This value indicates maximum response time (i.e., timer) in
  // seconds. Type:        uint16 Units:       seconds
  // -----------------------------------------------------------------------------
  LeafMaximumResponseTime maximumResponseTimeInst(ITEM_MAXIMUM_RESPONSE_TIME);
  addLeaf(maximumResponseTimeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-parameters/duration-per-channel
// Description: This value indicates measurement duration per channel in
// milliseconds.
// -----------------------------------------------------------------------------
GrpMeasurementParameters::LeafDurationPerChannel::LeafDurationPerChannel(
    uint32_t id)
    : YangLeaf("duration-per-channel", id) {}

GrpMeasurementParameters::LeafDurationPerChannel::~LeafDurationPerChannel() {}

// -----------------------------------------------------------------------------
// Leaf:        /measurement-parameters/maximum-response-time
// Description: This value indicates maximum response time (i.e., timer) in
// seconds.
// -----------------------------------------------------------------------------
GrpMeasurementParameters::LeafMaximumResponseTime::LeafMaximumResponseTime(
    uint32_t id)
    : YangLeaf("maximum-response-time", id) {}

GrpMeasurementParameters::LeafMaximumResponseTime::~LeafMaximumResponseTime() {}

// -----------------------------------------------------------------------------
// Grouping:    channel-result-element
// Description: Grouping for channel result element
// -----------------------------------------------------------------------------
GrpChannelResultElement::GrpChannelResultElement(uint32_t id)
    : YangGroup("channel-result-element", id) {}

GrpChannelResultElement::~GrpChannelResultElement() {}

YangResult_E
GrpChannelResultElement::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /channel-result-element/measured-channel
  // Description: This value indicates carrier center frequency for which the
  // result is computed in KHz. Type:        uint16 Units:       kilohertz
  // -----------------------------------------------------------------------------
  LeafMeasuredChannel measuredChannelInst(ITEM_MEASURED_CHANNEL);
  addLeaf(measuredChannelInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /channel-result-element/occupancy-ratio
  // Description: This value indicates occupancy ratio in percentage.
  // Type:        uint8
  // Units:       percent
  // -----------------------------------------------------------------------------
  LeafOccupancyRatio occupancyRatioInst(ITEM_OCCUPANCY_RATIO);
  addLeaf(occupancyRatioInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /channel-result-element/average-rssi
  // Description: This value indicates average RSSI in dBm
  // Type:        int8
  // Units:       dBm
  // -----------------------------------------------------------------------------
  LeafAverageRssi averageRssiInst(ITEM_AVERAGE_RSSI);
  addLeaf(averageRssiInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /channel-result-element/measured-channel
// Description: This value indicates carrier center frequency for which the
// result is computed in KHz.
// -----------------------------------------------------------------------------
GrpChannelResultElement::LeafMeasuredChannel::LeafMeasuredChannel(uint32_t id)
    : YangLeaf("measured-channel", id) {}

GrpChannelResultElement::LeafMeasuredChannel::~LeafMeasuredChannel() {}

// -----------------------------------------------------------------------------
// Leaf:        /channel-result-element/occupancy-ratio
// Description: This value indicates occupancy ratio in percentage.
// -----------------------------------------------------------------------------
GrpChannelResultElement::LeafOccupancyRatio::LeafOccupancyRatio(uint32_t id)
    : YangLeaf("occupancy-ratio", id) {}

GrpChannelResultElement::LeafOccupancyRatio::~LeafOccupancyRatio() {}

// -----------------------------------------------------------------------------
// Leaf:        /channel-result-element/average-rssi
// Description: This value indicates average RSSI in dBm
// -----------------------------------------------------------------------------
GrpChannelResultElement::LeafAverageRssi::LeafAverageRssi(uint32_t id)
    : YangLeaf("average-rssi", id) {}

GrpChannelResultElement::LeafAverageRssi::~LeafAverageRssi() {}

// -----------------------------------------------------------------------------
// Grouping:    band-result-element
// Description: Grouping for band result element
// -----------------------------------------------------------------------------
GrpBandResultElement::GrpBandResultElement(uint32_t id)
    : YangGroup("band-result-element", id) {}

GrpBandResultElement::~GrpBandResultElement() {}

YangResult_E
GrpBandResultElement::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /band-result-element/band-number
  // Description: This value indicates the band for which the result is
  // computed. Type:        enum Units:
  // -----------------------------------------------------------------------------
  LeafBandNumber bandNumberInst(ITEM_BAND_NUMBER);
  addLeaf(bandNumberInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-result-element/measurement-success
  // Description: This value indicates whether the measurement is successful for
  // the given band. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafMeasurementSuccess measurementSuccessInst(ITEM_MEASUREMENT_SUCCESS);
  addLeaf(measurementSuccessInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-result-element/failure-message
  // Description: This value indicates the detailed error message for failure of
  // the measurement at O-RU. Type:        enum Units:
  // -----------------------------------------------------------------------------
  LeafFailureMessage failureMessageInst(ITEM_FAILURE_MESSAGE);
  addLeaf(failureMessageInst);

  // -----------------------------------------------------------------------------
  // List:        /band-result-element/channel-result
  // Description: Results for a particular channel
  // Array Key:
  // -----------------------------------------------------------------------------
  LstChannelResult channelResultInst(ITEM_CHANNEL_RESULT);
  channelResultInst.initialise();
  addList(channelResultInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /band-result-element/band-number
// Description: This value indicates the band for which the result is computed.
// -----------------------------------------------------------------------------
GrpBandResultElement::LeafBandNumber::LeafBandNumber(uint32_t id)
    : YangLeaf("band-number", id) {}

GrpBandResultElement::LeafBandNumber::~LeafBandNumber() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-result-element/measurement-success
// Description: This value indicates whether the measurement is successful for
// the given band.
// -----------------------------------------------------------------------------
GrpBandResultElement::LeafMeasurementSuccess::LeafMeasurementSuccess(
    uint32_t id)
    : YangLeaf("measurement-success", id) {}

GrpBandResultElement::LeafMeasurementSuccess::~LeafMeasurementSuccess() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-result-element/failure-message
// Description: This value indicates the detailed error message for failure of
// the measurement at O-RU.
// -----------------------------------------------------------------------------
GrpBandResultElement::LeafFailureMessage::LeafFailureMessage(uint32_t id)
    : YangLeaf("failure-message", id) {}

GrpBandResultElement::LeafFailureMessage::~LeafFailureMessage() {}

// -----------------------------------------------------------------------------
// List:        channel-result
// Description: Results for a particular channel
// -----------------------------------------------------------------------------
GrpBandResultElement::LstChannelResult::LstChannelResult(uint32_t id)
    : YangList("channel-result", id) {}

GrpBandResultElement::LstChannelResult::~LstChannelResult() {}

YangResult_E
GrpBandResultElement::LstChannelResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /band-result-element/channel-result/channel-result-element
  // Description:
  // -----------------------------------------------------------------------------
  GrpChannelResultElement channelResultElementInst(ITEM_CHANNEL_RESULT_ELEMENT);
  channelResultElementInst.initialise();
  addGroup(channelResultElementInst);

  return YangResult_E::OK;
}

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
// Notification:measurement-result
// Description: Notification to provide the results of carrier selection and
// DFS.
// -----------------------------------------------------------------------------
NotifMeasurementResult::NotifMeasurementResult(uint32_t id)
    : YangNotif("measurement-result", id) {}

NotifMeasurementResult::~NotifMeasurementResult() {}

YangResult_E
NotifMeasurementResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /measurement-result/band-result
  // Description: Results for a particular sub band under band 46.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstBandResult bandResultInst(ITEM_BAND_RESULT);
  bandResultInst.initialise();
  addList(bandResultInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        band-result
// Description: Results for a particular sub band under band 46.
// -----------------------------------------------------------------------------
NotifMeasurementResult::LstBandResult::LstBandResult(uint32_t id)
    : YangList("band-result", id) {}

NotifMeasurementResult::LstBandResult::~LstBandResult() {}

YangResult_E
NotifMeasurementResult::LstBandResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /measurement-result/band-result/band-result-element
  // Description:
  // -----------------------------------------------------------------------------
  GrpBandResultElement bandResultElementInst(ITEM_BAND_RESULT_ELEMENT);
  bandResultElementInst.initialise();
  addGroup(bandResultElementInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-laa-operations
// Description: This module defines the operations for DFS measurement.
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
ModuleORanLaaOperations::ModuleORanLaaOperations(uint32_t id)
    : YangModule(
          "o-ran-laa-operations",
          "o-ran-laa-operations.yang",
          "o-ran-laa-operations",
          "urn:o-ran:laa-operations:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Notification:/measurement-result
  // Description: Notification to provide the results of carrier selection and
  // DFS.
  // -----------------------------------------------------------------------------
  NotifMeasurementResult measurementResultInst(ITEM_MEASUREMENT_RESULT);
  measurementResultInst.initialise();
  addNotification(measurementResultInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanLaaOperations::~ModuleORanLaaOperations() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanLaaOperations::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanLaaOperations>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanLaaOperations::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
