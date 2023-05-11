/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAntennaCalibration.cpp
 * \brief     Module ORanAntennaCalibration interface
 *
 *
 * \details   This file defines the YANG module o-ran-antenna-calibration
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-antenna-calibration"
 *            YANG Filename:    "o-ran-antenna-calibration.yang"
 *            Module Prefix:    "o-ran-antcal"
 *            Module namespace: "urn:o-ran:antcal:1.0"
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
#include "YangModuleORanAntennaCalibration.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanAntennaCalibration_NS;

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
// -----------------------------------------------------------------------------
// Container:   antenna-calibration
// Description: Describes the antenna calibration top node
// -----------------------------------------------------------------------------
CntAntennaCalibration::CntAntennaCalibration(uint32_t id)
    : YangContainer("antenna-calibration", id) {}

CntAntennaCalibration::~CntAntennaCalibration() {}

YangResult_E
CntAntennaCalibration::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /antenna-calibration/antenna-calibration
  // Description:
  // -----------------------------------------------------------------------------
  GrpAntennaCalibration antennaCalibrationInst(ITEM_ANTENNA_CALIBRATION);
  antennaCalibrationInst.initialise();
  addGroup(antennaCalibrationInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    antenna-calibration-capabilities
// Description: container for collection of leafs for antenna calibration
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::GrpAntennaCalibrationCapabilities(
    uint32_t id)
    : YangGroup("antenna-calibration-capabilities", id) {}

GrpAntennaCalibrationCapabilities::~GrpAntennaCalibrationCapabilities() {}

YangResult_E
GrpAntennaCalibrationCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /antenna-calibration-capabilities/self-calibration-support
  // Description: Indicates whether O-RU supports self-calibration or not.
  //
  //              When true, indicates O-RU can initiate calibration without
  //              receiving an rpc
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafSelfCalibrationSupport selfCalibrationSupportInst(
      ITEM_SELF_CALIBRATION_SUPPORT);
  addLeaf(selfCalibrationSupportInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-dl
  // Description: Indicates how many consecutive symbols are required for DL
  // antenna
  //              calibration operation
  // Type:        uint8
  // Units:       symbols
  // -----------------------------------------------------------------------------
  LeafNumberOfCalibrationSymbolsPerBlockDl
      numberOfCalibrationSymbolsPerBlockDlInst(
          ITEM_NUMBER_OF_CALIBRATION_SYMBOLS_PER_BLOCK_DL);
  addLeaf(numberOfCalibrationSymbolsPerBlockDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-ul
  // Description: Indicates how many consecutive symbols are required for UL
  // antenna
  //              calibration operation
  // Type:        uint8
  // Units:       symbols
  // -----------------------------------------------------------------------------
  LeafNumberOfCalibrationSymbolsPerBlockUl
      numberOfCalibrationSymbolsPerBlockUlInst(
          ITEM_NUMBER_OF_CALIBRATION_SYMBOLS_PER_BLOCK_UL);
  addLeaf(numberOfCalibrationSymbolsPerBlockUlInst);

  // -----------------------------------------------------------------------------
  // Leaf: /antenna-calibration-capabilities/interval-between-calibration-blocks
  // Description: if time interval is required between consecutive antenna
  // calibration
  //              operation, defines this time value as unit of symbols.
  //
  //              A common value is used here for the intervals
  //              between DL-DL blocks, UL-UL blocks, DL-UL blocks and UL-DL
  //              blocks, which is the largest minimum interval required between
  //              any two adjacent calibration blocks.
  // Type:        uint8
  // Units:       symbols
  // -----------------------------------------------------------------------------
  LeafIntervalBetweenCalibrationBlocks intervalBetweenCalibrationBlocksInst(
      ITEM_INTERVAL_BETWEEN_CALIBRATION_BLOCKS);
  addLeaf(intervalBetweenCalibrationBlocksInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-dl
  // Description: Indicates how many blocks are required for one step of DL
  // antenna
  //              calibration operation
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfCalibrationBlocksPerStepDl numberOfCalibrationBlocksPerStepDlInst(
      ITEM_NUMBER_OF_CALIBRATION_BLOCKS_PER_STEP_DL);
  addLeaf(numberOfCalibrationBlocksPerStepDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-ul
  // Description: Indicates how many blocks are required for one step of UL
  // antenna
  //              calibration operation
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfCalibrationBlocksPerStepUl numberOfCalibrationBlocksPerStepUlInst(
      ITEM_NUMBER_OF_CALIBRATION_BLOCKS_PER_STEP_UL);
  addLeaf(numberOfCalibrationBlocksPerStepUlInst);

  // -----------------------------------------------------------------------------
  // Leaf: /antenna-calibration-capabilities/interval-between-calibration-steps
  // Description: If time interval is required between consecutive step of
  // antenna
  //              calibration operation, defines this time value as unit of
  //              radio frames
  // Type:        uint8
  // Units:       radio-frames
  // -----------------------------------------------------------------------------
  LeafIntervalBetweenCalibrationSteps intervalBetweenCalibrationStepsInst(
      ITEM_INTERVAL_BETWEEN_CALIBRATION_STEPS);
  addLeaf(intervalBetweenCalibrationStepsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /antenna-calibration-capabilities/number-of-calibration-steps
  // Description: Indicates how many steps are required for whole DL/UL antenna
  //              calibration operation
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfCalibrationSteps numberOfCalibrationStepsInst(
      ITEM_NUMBER_OF_CALIBRATION_STEPS);
  addLeaf(numberOfCalibrationStepsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /antenna-calibration-capabilities/self-calibration-support
// Description: Indicates whether O-RU supports self-calibration or not.
//
//              When true, indicates O-RU can initiate calibration without
//              receiving an rpc
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafSelfCalibrationSupport::
    LeafSelfCalibrationSupport(uint32_t id)
    : YangLeaf("self-calibration-support", id) {}

GrpAntennaCalibrationCapabilities::LeafSelfCalibrationSupport::
    ~LeafSelfCalibrationSupport() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-dl
// Description: Indicates how many consecutive symbols are required for DL
// antenna
//              calibration operation
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSymbolsPerBlockDl::
    LeafNumberOfCalibrationSymbolsPerBlockDl(uint32_t id)
    : YangLeaf("number-of-calibration-symbols-per-block-dl", id) {}

GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSymbolsPerBlockDl::
    ~LeafNumberOfCalibrationSymbolsPerBlockDl() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-capabilities/number-of-calibration-symbols-per-block-ul
// Description: Indicates how many consecutive symbols are required for UL
// antenna
//              calibration operation
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSymbolsPerBlockUl::
    LeafNumberOfCalibrationSymbolsPerBlockUl(uint32_t id)
    : YangLeaf("number-of-calibration-symbols-per-block-ul", id) {}

GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSymbolsPerBlockUl::
    ~LeafNumberOfCalibrationSymbolsPerBlockUl() {}

// -----------------------------------------------------------------------------
// Leaf: /antenna-calibration-capabilities/interval-between-calibration-blocks
// Description: if time interval is required between consecutive antenna
// calibration
//              operation, defines this time value as unit of symbols.
//
//              A common value is used here for the intervals
//              between DL-DL blocks, UL-UL blocks, DL-UL blocks and UL-DL
//              blocks, which is the largest minimum interval required between
//              any two adjacent calibration blocks.
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafIntervalBetweenCalibrationBlocks::
    LeafIntervalBetweenCalibrationBlocks(uint32_t id)
    : YangLeaf("interval-between-calibration-blocks", id) {}

GrpAntennaCalibrationCapabilities::LeafIntervalBetweenCalibrationBlocks::
    ~LeafIntervalBetweenCalibrationBlocks() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-dl
// Description: Indicates how many blocks are required for one step of DL
// antenna
//              calibration operation
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationBlocksPerStepDl::
    LeafNumberOfCalibrationBlocksPerStepDl(uint32_t id)
    : YangLeaf("number-of-calibration-blocks-per-step-dl", id) {}

GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationBlocksPerStepDl::
    ~LeafNumberOfCalibrationBlocksPerStepDl() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-capabilities/number-of-calibration-blocks-per-step-ul
// Description: Indicates how many blocks are required for one step of UL
// antenna
//              calibration operation
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationBlocksPerStepUl::
    LeafNumberOfCalibrationBlocksPerStepUl(uint32_t id)
    : YangLeaf("number-of-calibration-blocks-per-step-ul", id) {}

GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationBlocksPerStepUl::
    ~LeafNumberOfCalibrationBlocksPerStepUl() {}

// -----------------------------------------------------------------------------
// Leaf: /antenna-calibration-capabilities/interval-between-calibration-steps
// Description: If time interval is required between consecutive step of antenna
//              calibration operation, defines this time value as unit of radio
//              frames
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafIntervalBetweenCalibrationSteps::
    LeafIntervalBetweenCalibrationSteps(uint32_t id)
    : YangLeaf("interval-between-calibration-steps", id) {}

GrpAntennaCalibrationCapabilities::LeafIntervalBetweenCalibrationSteps::
    ~LeafIntervalBetweenCalibrationSteps() {}

// -----------------------------------------------------------------------------
// Leaf:        /antenna-calibration-capabilities/number-of-calibration-steps
// Description: Indicates how many steps are required for whole DL/UL antenna
//              calibration operation
// -----------------------------------------------------------------------------
GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSteps::
    LeafNumberOfCalibrationSteps(uint32_t id)
    : YangLeaf("number-of-calibration-steps", id) {}

GrpAntennaCalibrationCapabilities::LeafNumberOfCalibrationSteps::
    ~LeafNumberOfCalibrationSteps() {}

// -----------------------------------------------------------------------------
// Grouping:    antenna-calibration
// Description: Describe the grouping set of antenna calibration
// -----------------------------------------------------------------------------
GrpAntennaCalibration::GrpAntennaCalibration(uint32_t id)
    : YangGroup("antenna-calibration", id) {}

GrpAntennaCalibration::~GrpAntennaCalibration() {}

YangResult_E
GrpAntennaCalibration::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /antenna-calibration/antenna-calibration-capabilities
  // Description: Describes the antenna calibration capabilities
  // -----------------------------------------------------------------------------
  CntAntennaCalibrationCapabilities antennaCalibrationCapabilitiesInst(
      ITEM_ANTENNA_CALIBRATION_CAPABILITIES);
  antennaCalibrationCapabilitiesInst.initialise();
  addContainer(antennaCalibrationCapabilitiesInst);

  // -----------------------------------------------------------------------------
  // Container:   /antenna-calibration/self-calibration-policy
  // Description: Describes the self calibration policy of the operator
  // -----------------------------------------------------------------------------
  CntSelfCalibrationPolicy selfCalibrationPolicyInst(
      ITEM_SELF_CALIBRATION_POLICY);
  selfCalibrationPolicyInst.initialise();
  addContainer(selfCalibrationPolicyInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   antenna-calibration-capabilities
// Description: Describes the antenna calibration capabilities
// -----------------------------------------------------------------------------
GrpAntennaCalibration::CntAntennaCalibrationCapabilities::
    CntAntennaCalibrationCapabilities(uint32_t id)
    : YangContainer("antenna-calibration-capabilities", id) {}

GrpAntennaCalibration::CntAntennaCalibrationCapabilities::
    ~CntAntennaCalibrationCapabilities() {}

YangResult_E
GrpAntennaCalibration::CntAntennaCalibrationCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /antenna-calibration/antenna-calibration-capabilities/antenna-calibration-capabilities
  // Description:
  // -----------------------------------------------------------------------------
  GrpAntennaCalibrationCapabilities antennaCalibrationCapabilitiesInst(
      ITEM_ANTENNA_CALIBRATION_CAPABILITIES);
  antennaCalibrationCapabilitiesInst.initialise();
  addGroup(antennaCalibrationCapabilitiesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   self-calibration-policy
// Description: Describes the self calibration policy of the operator
// -----------------------------------------------------------------------------
GrpAntennaCalibration::CntSelfCalibrationPolicy::CntSelfCalibrationPolicy(
    uint32_t id)
    : YangContainer("self-calibration-policy", id) {}

GrpAntennaCalibration::CntSelfCalibrationPolicy::~CntSelfCalibrationPolicy() {}

YangResult_E
GrpAntennaCalibration::CntSelfCalibrationPolicy::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /antenna-calibration/self-calibration-policy/self-calibration-allowed
  // Description: whether the self-calibration is allowed configured by
  // operator. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafSelfCalibrationAllowed selfCalibrationAllowedInst(
      ITEM_SELF_CALIBRATION_ALLOWED);
  addLeaf(selfCalibrationAllowedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /antenna-calibration/self-calibration-policy/self-calibration-allowed
// Description: whether the self-calibration is allowed configured by operator.
// -----------------------------------------------------------------------------
GrpAntennaCalibration::CntSelfCalibrationPolicy::LeafSelfCalibrationAllowed::
    LeafSelfCalibrationAllowed(uint32_t id)
    : YangLeaf("self-calibration-allowed", id) {}

GrpAntennaCalibration::CntSelfCalibrationPolicy::LeafSelfCalibrationAllowed::
    ~LeafSelfCalibrationAllowed() {}

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
// Notification:antenna-calibration-required
// Description: this notification indicates that the antenna calibration is
// required in O-RU
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::NotifAntennaCalibrationRequired(uint32_t id)
    : YangNotif("antenna-calibration-required", id) {}

NotifAntennaCalibrationRequired::~NotifAntennaCalibrationRequired() {}

YangResult_E
NotifAntennaCalibrationRequired::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /antenna-calibration-required/dl-calibration-frequency-chunk
  // Description: min/max frequency of dl spectrum chunk affected by calibration
  // process Array Key:
  // -----------------------------------------------------------------------------
  LstDlCalibrationFrequencyChunk dlCalibrationFrequencyChunkInst(
      ITEM_DL_CALIBRATION_FREQUENCY_CHUNK);
  dlCalibrationFrequencyChunkInst.initialise();
  addList(dlCalibrationFrequencyChunkInst);

  // -----------------------------------------------------------------------------
  // List:        /antenna-calibration-required/ul-calibration-frequency-chunk
  // Description: min/max frequency of ul spectrum chunk affected by calibration
  // process Array Key:
  // -----------------------------------------------------------------------------
  LstUlCalibrationFrequencyChunk ulCalibrationFrequencyChunkInst(
      ITEM_UL_CALIBRATION_FREQUENCY_CHUNK);
  ulCalibrationFrequencyChunkInst.initialise();
  addList(ulCalibrationFrequencyChunkInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        dl-calibration-frequency-chunk
// Description: min/max frequency of dl spectrum chunk affected by calibration
// process
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    LstDlCalibrationFrequencyChunk(uint32_t id)
    : YangList("dl-calibration-frequency-chunk", id) {}

NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    ~LstDlCalibrationFrequencyChunk() {}

YangResult_E
NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-required/dl-calibration-frequency-chunk/start-calibration-frequency-dl
  // Description: lowest frequency value in Hz of the frequency range is
  // required for
  //              DL antenna calibration operation.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafStartCalibrationFrequencyDl startCalibrationFrequencyDlInst(
      ITEM_START_CALIBRATION_FREQUENCY_DL);
  addLeaf(startCalibrationFrequencyDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-required/dl-calibration-frequency-chunk/end-calibration-frequency-dl
  // Description: highest frequency value in Hz of the frequency range is
  // required for
  //              DL antenna calibration operation.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafEndCalibrationFrequencyDl endCalibrationFrequencyDlInst(
      ITEM_END_CALIBRATION_FREQUENCY_DL);
  addLeaf(endCalibrationFrequencyDlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-required/dl-calibration-frequency-chunk/start-calibration-frequency-dl
// Description: lowest frequency value in Hz of the frequency range is required
// for
//              DL antenna calibration operation.
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    LeafStartCalibrationFrequencyDl::LeafStartCalibrationFrequencyDl(
        uint32_t id)
    : YangLeaf("start-calibration-frequency-dl", id) {}

NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    LeafStartCalibrationFrequencyDl::~LeafStartCalibrationFrequencyDl() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-required/dl-calibration-frequency-chunk/end-calibration-frequency-dl
// Description: highest frequency value in Hz of the frequency range is required
// for
//              DL antenna calibration operation.
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    LeafEndCalibrationFrequencyDl::LeafEndCalibrationFrequencyDl(uint32_t id)
    : YangLeaf("end-calibration-frequency-dl", id) {}

NotifAntennaCalibrationRequired::LstDlCalibrationFrequencyChunk::
    LeafEndCalibrationFrequencyDl::~LeafEndCalibrationFrequencyDl() {}

// -----------------------------------------------------------------------------
// List:        ul-calibration-frequency-chunk
// Description: min/max frequency of ul spectrum chunk affected by calibration
// process
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    LstUlCalibrationFrequencyChunk(uint32_t id)
    : YangList("ul-calibration-frequency-chunk", id) {}

NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    ~LstUlCalibrationFrequencyChunk() {}

YangResult_E
NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-required/ul-calibration-frequency-chunk/start-calibration-frequency-ul
  // Description: lowest frequency value in Hz of the frequency range is
  // required for
  //              UL antenna calibration operation.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafStartCalibrationFrequencyUl startCalibrationFrequencyUlInst(
      ITEM_START_CALIBRATION_FREQUENCY_UL);
  addLeaf(startCalibrationFrequencyUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /antenna-calibration-required/ul-calibration-frequency-chunk/end-calibration-frequency-ul
  // Description: highest frequency value in Hz of the frequency range is
  // required for
  //              UL antenna calibration operation.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafEndCalibrationFrequencyUl endCalibrationFrequencyUlInst(
      ITEM_END_CALIBRATION_FREQUENCY_UL);
  addLeaf(endCalibrationFrequencyUlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-required/ul-calibration-frequency-chunk/start-calibration-frequency-ul
// Description: lowest frequency value in Hz of the frequency range is required
// for
//              UL antenna calibration operation.
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    LeafStartCalibrationFrequencyUl::LeafStartCalibrationFrequencyUl(
        uint32_t id)
    : YangLeaf("start-calibration-frequency-ul", id) {}

NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    LeafStartCalibrationFrequencyUl::~LeafStartCalibrationFrequencyUl() {}

// -----------------------------------------------------------------------------
// Leaf:
// /antenna-calibration-required/ul-calibration-frequency-chunk/end-calibration-frequency-ul
// Description: highest frequency value in Hz of the frequency range is required
// for
//              UL antenna calibration operation.
// -----------------------------------------------------------------------------
NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    LeafEndCalibrationFrequencyUl::LeafEndCalibrationFrequencyUl(uint32_t id)
    : YangLeaf("end-calibration-frequency-ul", id) {}

NotifAntennaCalibrationRequired::LstUlCalibrationFrequencyChunk::
    LeafEndCalibrationFrequencyUl::~LeafEndCalibrationFrequencyUl() {}

// -----------------------------------------------------------------------------
// Notification:antenna-calibration-result
// Description: This notification indicates the antenna calibration result
// -----------------------------------------------------------------------------
NotifAntennaCalibrationResult::NotifAntennaCalibrationResult(uint32_t id)
    : YangNotif("antenna-calibration-result", id) {}

NotifAntennaCalibrationResult::~NotifAntennaCalibrationResult() {}

YangResult_E
NotifAntennaCalibrationResult::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /antenna-calibration-result/status
  // Description: Status of the antenna calibration procedure which has been
  // triggered
  //              by accepting an start-antenna-calibration RPC.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /antenna-calibration-result/detailed-reason
  // Description: Detailed reason when the status is FAILURE, e.g.,
  //              O-RU cannot complete the antenna calibration
  //              because of lack of memory, self-calibration failure, etc
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafDetailedReason detailedReasonInst(ITEM_DETAILED_REASON);
  addLeaf(detailedReasonInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /antenna-calibration-result/status
// Description: Status of the antenna calibration procedure which has been
// triggered
//              by accepting an start-antenna-calibration RPC.
// -----------------------------------------------------------------------------
NotifAntennaCalibrationResult::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

NotifAntennaCalibrationResult::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /antenna-calibration-result/detailed-reason
// Description: Detailed reason when the status is FAILURE, e.g.,
//              O-RU cannot complete the antenna calibration
//              because of lack of memory, self-calibration failure, etc
// -----------------------------------------------------------------------------
NotifAntennaCalibrationResult::LeafDetailedReason::LeafDetailedReason(
    uint32_t id)
    : YangLeaf("detailed-reason", id) {}

NotifAntennaCalibrationResult::LeafDetailedReason::~LeafDetailedReason() {}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-antenna-calibration
// Description: This module defines the configuration required for supporting
// the optional
//              antenna calibration functionality.
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
ModuleORanAntennaCalibration::ModuleORanAntennaCalibration(uint32_t id)
    : YangModule(
          "o-ran-antenna-calibration",
          "o-ran-antenna-calibration.yang",
          "o-ran-antcal",
          "urn:o-ran:antcal:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /antenna-calibration
  // Description: Describes the antenna calibration top node
  // -----------------------------------------------------------------------------
  CntAntennaCalibration antennaCalibrationInst(ITEM_ANTENNA_CALIBRATION);
  antennaCalibrationInst.initialise();
  addContainer(antennaCalibrationInst);

  // -----------------------------------------------------------------------------
  // Notification:/antenna-calibration-required
  // Description: this notification indicates that the antenna calibration is
  // required in O-RU
  // -----------------------------------------------------------------------------
  NotifAntennaCalibrationRequired antennaCalibrationRequiredInst(
      ITEM_ANTENNA_CALIBRATION_REQUIRED);
  antennaCalibrationRequiredInst.initialise();
  addNotification(antennaCalibrationRequiredInst);

  // -----------------------------------------------------------------------------
  // Notification:/antenna-calibration-result
  // Description: This notification indicates the antenna calibration result
  // -----------------------------------------------------------------------------
  NotifAntennaCalibrationResult antennaCalibrationResultInst(
      ITEM_ANTENNA_CALIBRATION_RESULT);
  antennaCalibrationResultInst.initialise();
  addNotification(antennaCalibrationResultInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanAntennaCalibration::~ModuleORanAntennaCalibration() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanAntennaCalibration::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanAntennaCalibration>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanAntennaCalibration::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
