/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLaa.cpp
 * \brief     Module ORanLaa interface
 *
 *
 * \details   This file defines the YANG module o-ran-laa interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-laa"
 *            YANG Filename:    "o-ran-laa.yang"
 *            Module Prefix:    "o-ran-laa"
 *            Module namespace: "urn:o-ran:laa:1.0"
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
#include "YangModuleORanLaa.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanLaa_NS;

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
// Container:   laa-config
// Description: Container to specify all LAA specific configuration
// -----------------------------------------------------------------------------
CntLaaConfig::CntLaaConfig(uint32_t id) : YangContainer("laa-config", id) {}

CntLaaConfig::~CntLaaConfig() {}

YangResult_E
CntLaaConfig::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /laa-config/laa-configuration
  // Description:
  // -----------------------------------------------------------------------------
  GrpLaaConfiguration laaConfigurationInst(ITEM_LAA_CONFIGURATION);
  laaConfigurationInst.initialise();
  addGroup(laaConfigurationInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    laa-configuration
// Description: Grouping for LAA configuration
// -----------------------------------------------------------------------------
GrpLaaConfiguration::GrpLaaConfiguration(uint32_t id)
    : YangGroup("laa-configuration", id) {}

GrpLaaConfiguration::~GrpLaaConfiguration() {}

YangResult_E
GrpLaaConfiguration::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/number-of-laa-scarriers
  // Description: Number of LAA secondary carriers to be supported at O-RU.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfLaaScarriers numberOfLaaScarriersInst(
      ITEM_NUMBER_OF_LAA_SCARRIERS);
  addLeaf(numberOfLaaScarriersInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/multi-carrier-type
  // Description: This value indicates the list of multi carrier types which as
  // per the document,
  //              3GPP TS 36.213 V13.6.0 (2017-06) 15.1.5 Channel access
  //              procedure for transmission(s) on multiple carriers.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafMultiCarrierType multiCarrierTypeInst(ITEM_MULTI_CARRIER_TYPE);
  addLeaf(multiCarrierTypeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/multi-carrier-tx
  // Description: This value indicates whether self-deferral is activated or
  // not. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafMultiCarrierTx multiCarrierTxInst(ITEM_MULTI_CARRIER_TX);
  addLeaf(multiCarrierTxInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/multi-carrier-freeze
  // Description: This value indicates if the absence of other technology in the
  // unlicensed band can be guaranteed. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafMultiCarrierFreeze multiCarrierFreezeInst(ITEM_MULTI_CARRIER_FREEZE);
  addLeaf(multiCarrierFreezeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/laa-ending-dwpts-supported
  // Description: This value indicates whether LAA ending in DwPTS is supported.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafLaaEndingDwptsSupported laaEndingDwptsSupportedInst(
      ITEM_LAA_ENDING_DWPTS_SUPPORTED);
  addLeaf(laaEndingDwptsSupportedInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /laa-configuration/laa-starting-in-second-slot-supported
  // Description: This value indicates whether LAA starting in second slot is
  // supported Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafLaaStartingInSecondSlotSupported laaStartingInSecondSlotSupportedInst(
      ITEM_LAA_STARTING_IN_SECOND_SLOT_SUPPORTED);
  addLeaf(laaStartingInSecondSlotSupportedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/number-of-laa-scarriers
// Description: Number of LAA secondary carriers to be supported at O-RU.
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafNumberOfLaaScarriers::LeafNumberOfLaaScarriers(
    uint32_t id)
    : YangLeaf("number-of-laa-scarriers", id) {}

GrpLaaConfiguration::LeafNumberOfLaaScarriers::~LeafNumberOfLaaScarriers() {}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/multi-carrier-type
// Description: This value indicates the list of multi carrier types which as
// per the document,
//              3GPP TS 36.213 V13.6.0 (2017-06) 15.1.5 Channel access procedure
//              for transmission(s) on multiple carriers.
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafMultiCarrierType::LeafMultiCarrierType(uint32_t id)
    : YangLeaf("multi-carrier-type", id) {}

GrpLaaConfiguration::LeafMultiCarrierType::~LeafMultiCarrierType() {}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/multi-carrier-tx
// Description: This value indicates whether self-deferral is activated or not.
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafMultiCarrierTx::LeafMultiCarrierTx(uint32_t id)
    : YangLeaf("multi-carrier-tx", id) {}

GrpLaaConfiguration::LeafMultiCarrierTx::~LeafMultiCarrierTx() {}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/multi-carrier-freeze
// Description: This value indicates if the absence of other technology in the
// unlicensed band can be guaranteed.
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafMultiCarrierFreeze::LeafMultiCarrierFreeze(uint32_t id)
    : YangLeaf("multi-carrier-freeze", id) {}

GrpLaaConfiguration::LeafMultiCarrierFreeze::~LeafMultiCarrierFreeze() {}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/laa-ending-dwpts-supported
// Description: This value indicates whether LAA ending in DwPTS is supported.
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafLaaEndingDwptsSupported::LeafLaaEndingDwptsSupported(
    uint32_t id)
    : YangLeaf("laa-ending-dwpts-supported", id) {}

GrpLaaConfiguration::LeafLaaEndingDwptsSupported::
    ~LeafLaaEndingDwptsSupported() {}

// -----------------------------------------------------------------------------
// Leaf:        /laa-configuration/laa-starting-in-second-slot-supported
// Description: This value indicates whether LAA starting in second slot is
// supported
// -----------------------------------------------------------------------------
GrpLaaConfiguration::LeafLaaStartingInSecondSlotSupported::
    LeafLaaStartingInSecondSlotSupported(uint32_t id)
    : YangLeaf("laa-starting-in-second-slot-supported", id) {}

GrpLaaConfiguration::LeafLaaStartingInSecondSlotSupported::
    ~LeafLaaStartingInSecondSlotSupported() {}

// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-laa
// Description: This module defines the configuration for Carrier-selection and
// dynamic frequency selection (DFS).
//              Also this module defines operations for DFS measurement.
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
ModuleORanLaa::ModuleORanLaa(uint32_t id)
    : YangModule(
          "o-ran-laa", "o-ran-laa.yang", "o-ran-laa", "urn:o-ran:laa:1.0", id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /laa-config
  // Description: Container to specify all LAA specific configuration
  // -----------------------------------------------------------------------------
  CntLaaConfig laaConfigInst(ITEM_LAA_CONFIG);
  laaConfigInst.initialise();
  addContainer(laaConfigInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanLaa::~ModuleORanLaa() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanLaa::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanLaa>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanLaa::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
