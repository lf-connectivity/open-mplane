/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanInterfaces.cpp
 * \brief     Module ORanInterfaces interface
 *
 *
 * \details   This file defines the YANG module o-ran-interfaces interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-interfaces"
 *            YANG Filename:    "o-ran-interfaces.yang"
 *            Module Prefix:    "o-ran-int"
 *            Module namespace: "urn:o-ran:interfaces:1.0"
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
#include "YangModuleORanInterfaces.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanInterfaces_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the RU supports the UDP/IP based
// transport
//              for the CU plane.
// -----------------------------------------------------------------------------
FeatureUDPIPBASEDCUPLANE::FeatureUDPIPBASEDCUPLANE(uint32_t id)
    : YangFeature("UDPIP-BASED-CU-PLANE", id) {}

FeatureUDPIPBASEDCUPLANE::~FeatureUDPIPBASEDCUPLANE() {}

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the RU supports the alias MAC
// address
//              based transport for the CU plane.
// -----------------------------------------------------------------------------
FeatureALIASMACBASEDCUPLANE::FeatureALIASMACBASEDCUPLANE(uint32_t id)
    : YangFeature("ALIASMAC-BASED-CU-PLANE", id) {}

FeatureALIASMACBASEDCUPLANE::~FeatureALIASMACBASEDCUPLANE() {}

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
// Grouping:    cos-marking
// Description: Configuration data for CU Plane ethernet CoS marking
// -----------------------------------------------------------------------------
GrpCosMarking::GrpCosMarking(uint32_t id) : YangGroup("cos-marking", id) {}

GrpCosMarking::~GrpCosMarking() {}

YangResult_E
GrpCosMarking::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /cos-marking/class-of-service
  // Description: CoS Configuration
  // -----------------------------------------------------------------------------
  CntClassOfService classOfServiceInst(ITEM_CLASS_OF_SERVICE);
  classOfServiceInst.initialise();
  addContainer(classOfServiceInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   class-of-service
// Description: CoS Configuration
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::CntClassOfService(uint32_t id)
    : YangContainer("class-of-service", id) {}

GrpCosMarking::CntClassOfService::~CntClassOfService() {}

YangResult_E
GrpCosMarking::CntClassOfService::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /cos-marking/class-of-service/u-plane-marking
  // Description: Marking used for default u-plane flows.
  //              7 represents highest priority for u-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafUPlaneMarking uPlaneMarkingInst(ITEM_U_PLANE_MARKING);
  addLeaf(uPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /cos-marking/class-of-service/c-plane-marking
  // Description: 7 represents highest priority for c-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafCPlaneMarking cPlaneMarkingInst(ITEM_C_PLANE_MARKING);
  addLeaf(cPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /cos-marking/class-of-service/m-plane-marking
  // Description: 2 represents highest excellent effort for m-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafMPlaneMarking mPlaneMarkingInst(ITEM_M_PLANE_MARKING);
  addLeaf(mPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /cos-marking/class-of-service/s-plane-marking
  // Description: 7 represents highest priority for s-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafSPlaneMarking sPlaneMarkingInst(ITEM_S_PLANE_MARKING);
  addLeaf(sPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /cos-marking/class-of-service/other-marking
  // Description: 1 represents best effort for other marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafOtherMarking otherMarkingInst(ITEM_OTHER_MARKING);
  addLeaf(otherMarkingInst);

  // -----------------------------------------------------------------------------
  // List:        /cos-marking/class-of-service/enhanced-uplane-markings
  // Description: list of mappings for enhanced (non-default) u-plane markings
  // Array Key:
  // -----------------------------------------------------------------------------
  LstEnhancedUplaneMarkings enhancedUplaneMarkingsInst(
      ITEM_ENHANCED_UPLANE_MARKINGS);
  enhancedUplaneMarkingsInst.initialise();
  addList(enhancedUplaneMarkingsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /cos-marking/class-of-service/u-plane-marking
// Description: Marking used for default u-plane flows.
//              7 represents highest priority for u-plane marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LeafUPlaneMarking::LeafUPlaneMarking(
    uint32_t id)
    : YangLeaf("u-plane-marking", id) {}

GrpCosMarking::CntClassOfService::LeafUPlaneMarking::~LeafUPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /cos-marking/class-of-service/c-plane-marking
// Description: 7 represents highest priority for c-plane marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LeafCPlaneMarking::LeafCPlaneMarking(
    uint32_t id)
    : YangLeaf("c-plane-marking", id) {}

GrpCosMarking::CntClassOfService::LeafCPlaneMarking::~LeafCPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /cos-marking/class-of-service/m-plane-marking
// Description: 2 represents highest excellent effort for m-plane marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LeafMPlaneMarking::LeafMPlaneMarking(
    uint32_t id)
    : YangLeaf("m-plane-marking", id) {}

GrpCosMarking::CntClassOfService::LeafMPlaneMarking::~LeafMPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /cos-marking/class-of-service/s-plane-marking
// Description: 7 represents highest priority for s-plane marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LeafSPlaneMarking::LeafSPlaneMarking(
    uint32_t id)
    : YangLeaf("s-plane-marking", id) {}

GrpCosMarking::CntClassOfService::LeafSPlaneMarking::~LeafSPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /cos-marking/class-of-service/other-marking
// Description: 1 represents best effort for other marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LeafOtherMarking::LeafOtherMarking(
    uint32_t id)
    : YangLeaf("other-marking", id) {}

GrpCosMarking::CntClassOfService::LeafOtherMarking::~LeafOtherMarking() {}

// -----------------------------------------------------------------------------
// List:        enhanced-uplane-markings
// Description: list of mappings for enhanced (non-default) u-plane markings
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::
    LstEnhancedUplaneMarkings(uint32_t id)
    : YangList("enhanced-uplane-markings", id) {}

GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::
    ~LstEnhancedUplaneMarkings() {}

YangResult_E
GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /cos-marking/class-of-service/enhanced-uplane-markings/up-marking-name
  // Description: The name of the marking
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUpMarkingName upMarkingNameInst(ITEM_UP_MARKING_NAME);
  addLeaf(upMarkingNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /cos-marking/class-of-service/enhanced-uplane-markings/enhanced-marking
  // Description: the enhanced u-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnhancedMarking enhancedMarkingInst(ITEM_ENHANCED_MARKING);
  addLeaf(enhancedMarkingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /cos-marking/class-of-service/enhanced-uplane-markings/up-marking-name
// Description: The name of the marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::LeafUpMarkingName::
    LeafUpMarkingName(uint32_t id)
    : YangLeaf("up-marking-name", id) {}

GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::LeafUpMarkingName::
    ~LeafUpMarkingName() {}

// -----------------------------------------------------------------------------
// Leaf: /cos-marking/class-of-service/enhanced-uplane-markings/enhanced-marking
// Description: the enhanced u-plane marking
// -----------------------------------------------------------------------------
GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::
    LeafEnhancedMarking::LeafEnhancedMarking(uint32_t id)
    : YangLeaf("enhanced-marking", id) {}

GrpCosMarking::CntClassOfService::LstEnhancedUplaneMarkings::
    LeafEnhancedMarking::~LeafEnhancedMarking() {}

// -----------------------------------------------------------------------------
// Grouping:    dscp-marking
// Description: Configuration data for CU Plane DSCP marking
// -----------------------------------------------------------------------------
GrpDscpMarking::GrpDscpMarking(uint32_t id) : YangGroup("dscp-marking", id) {}

GrpDscpMarking::~GrpDscpMarking() {}

YangResult_E
GrpDscpMarking::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /dscp-marking/diffserv-markings
  // Description: DSCP Configuration
  // -----------------------------------------------------------------------------
  CntDiffservMarkings diffservMarkingsInst(ITEM_DIFFSERV_MARKINGS);
  diffservMarkingsInst.initialise();
  addContainer(diffservMarkingsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   diffserv-markings
// Description: DSCP Configuration
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::CntDiffservMarkings(uint32_t id)
    : YangContainer("diffserv-markings", id) {}

GrpDscpMarking::CntDiffservMarkings::~CntDiffservMarkings() {}

YangResult_E
GrpDscpMarking::CntDiffservMarkings::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /dscp-marking/diffserv-markings/u-plane-marking
  // Description: Marking used for default u-plane flows.
  //              46 represents expedited forwarding
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafUPlaneMarking uPlaneMarkingInst(ITEM_U_PLANE_MARKING);
  addLeaf(uPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /dscp-marking/diffserv-markings/c-plane-marking
  // Description: 46 represents expedited forwarding
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafCPlaneMarking cPlaneMarkingInst(ITEM_C_PLANE_MARKING);
  addLeaf(cPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /dscp-marking/diffserv-markings/s-plane-marking
  // Description: 46 represents expedited forwarding
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafSPlaneMarking sPlaneMarkingInst(ITEM_S_PLANE_MARKING);
  addLeaf(sPlaneMarkingInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /dscp-marking/diffserv-markings/other-marking
  // Description: 0 represents best effort forwarding
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafOtherMarking otherMarkingInst(ITEM_OTHER_MARKING);
  addLeaf(otherMarkingInst);

  // -----------------------------------------------------------------------------
  // List:        /dscp-marking/diffserv-markings/enhanced-uplane-markings
  // Description: list of mappings for enhanced (non-default) u-plane markings
  // Array Key:
  // -----------------------------------------------------------------------------
  LstEnhancedUplaneMarkings enhancedUplaneMarkingsInst(
      ITEM_ENHANCED_UPLANE_MARKINGS);
  enhancedUplaneMarkingsInst.initialise();
  addList(enhancedUplaneMarkingsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dscp-marking/diffserv-markings/u-plane-marking
// Description: Marking used for default u-plane flows.
//              46 represents expedited forwarding
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LeafUPlaneMarking::LeafUPlaneMarking(
    uint32_t id)
    : YangLeaf("u-plane-marking", id) {}

GrpDscpMarking::CntDiffservMarkings::LeafUPlaneMarking::~LeafUPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /dscp-marking/diffserv-markings/c-plane-marking
// Description: 46 represents expedited forwarding
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LeafCPlaneMarking::LeafCPlaneMarking(
    uint32_t id)
    : YangLeaf("c-plane-marking", id) {}

GrpDscpMarking::CntDiffservMarkings::LeafCPlaneMarking::~LeafCPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /dscp-marking/diffserv-markings/s-plane-marking
// Description: 46 represents expedited forwarding
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LeafSPlaneMarking::LeafSPlaneMarking(
    uint32_t id)
    : YangLeaf("s-plane-marking", id) {}

GrpDscpMarking::CntDiffservMarkings::LeafSPlaneMarking::~LeafSPlaneMarking() {}

// -----------------------------------------------------------------------------
// Leaf:        /dscp-marking/diffserv-markings/other-marking
// Description: 0 represents best effort forwarding
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LeafOtherMarking::LeafOtherMarking(
    uint32_t id)
    : YangLeaf("other-marking", id) {}

GrpDscpMarking::CntDiffservMarkings::LeafOtherMarking::~LeafOtherMarking() {}

// -----------------------------------------------------------------------------
// List:        enhanced-uplane-markings
// Description: list of mappings for enhanced (non-default) u-plane markings
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    LstEnhancedUplaneMarkings(uint32_t id)
    : YangList("enhanced-uplane-markings", id) {}

GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    ~LstEnhancedUplaneMarkings() {}

YangResult_E
GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /dscp-marking/diffserv-markings/enhanced-uplane-markings/up-marking-name
  // Description: The name of the marking
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUpMarkingName upMarkingNameInst(ITEM_UP_MARKING_NAME);
  addLeaf(upMarkingNameInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /dscp-marking/diffserv-markings/enhanced-uplane-markings/enhanced-marking
  // Description: the enhanced u-plane marking
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafEnhancedMarking enhancedMarkingInst(ITEM_ENHANCED_MARKING);
  addLeaf(enhancedMarkingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /dscp-marking/diffserv-markings/enhanced-uplane-markings/up-marking-name
// Description: The name of the marking
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    LeafUpMarkingName::LeafUpMarkingName(uint32_t id)
    : YangLeaf("up-marking-name", id) {}

GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    LeafUpMarkingName::~LeafUpMarkingName() {}

// -----------------------------------------------------------------------------
// Leaf:
// /dscp-marking/diffserv-markings/enhanced-uplane-markings/enhanced-marking
// Description: the enhanced u-plane marking
// -----------------------------------------------------------------------------
GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    LeafEnhancedMarking::LeafEnhancedMarking(uint32_t id)
    : YangLeaf("enhanced-marking", id) {}

GrpDscpMarking::CntDiffservMarkings::LstEnhancedUplaneMarkings::
    LeafEnhancedMarking::~LeafEnhancedMarking() {}

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
// Module:      o-ran-interfaces
// Description: This module defines the YANG definitions for managng the O-RAN
//              interfaces.
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
ModuleORanInterfaces::ModuleORanInterfaces(uint32_t id)
    : YangModule(
          "o-ran-interfaces",
          "o-ran-interfaces.yang",
          "o-ran-int",
          "urn:o-ran:interfaces:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the RU supports the UDP/IP based
  // transport
  //              for the CU plane.
  // -----------------------------------------------------------------------------
  FeatureUDPIPBASEDCUPLANE UDPIPBASEDCUPLANEInst(ITEM_UDPIP_BASED_CU_PLANE);
  addFeature(UDPIPBASEDCUPLANEInst);

  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the RU supports the alias MAC
  // address
  //              based transport for the CU plane.
  // -----------------------------------------------------------------------------
  FeatureALIASMACBASEDCUPLANE ALIASMACBASEDCUPLANEInst(
      ITEM_ALIASMAC_BASED_CU_PLANE);
  addFeature(ALIASMACBASEDCUPLANEInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanInterfaces::~ModuleORanInterfaces() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanInterfaces::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanInterfaces>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanInterfaces::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
