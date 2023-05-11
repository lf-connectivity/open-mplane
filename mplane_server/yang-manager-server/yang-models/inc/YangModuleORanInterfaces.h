#ifndef _MODULE_O_RAN_INTERFACES_H_
#define _MODULE_O_RAN_INTERFACES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanInterfaces.h
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

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   iana-if-type
// Revision:
// Notes:
#include "YangModuleIanaIfType.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   ietf-ip
// Revision:
// Notes:
#include "YangModuleIetfIp.h"

// Module:   ietf-hardware
// Revision:
// Notes:
#include "YangModuleIetfHardware.h"

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   iana-hardware
// Revision:
// Notes:
#include "YangModuleIanaHardware.h"


namespace Mplane {

namespace ModuleORanInterfaces_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************


// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the RU supports the UDP/IP based transport
//              for the CU plane.
// -----------------------------------------------------------------------------
class FeatureUDPIPBASEDCUPLANE : public YangFeature
{
public:
 FeatureUDPIPBASEDCUPLANE(uint32_t id);
 ~FeatureUDPIPBASEDCUPLANE();

}; // FeatureUDPIPBASEDCUPLANE

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the RU supports the alias MAC address
//              based transport for the CU plane.
// -----------------------------------------------------------------------------
class FeatureALIASMACBASEDCUPLANE : public YangFeature
{
public:
 FeatureALIASMACBASEDCUPLANE(uint32_t id);
 ~FeatureALIASMACBASEDCUPLANE();

}; // FeatureALIASMACBASEDCUPLANE


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
// Grouping:    /cos-marking
// Description: Configuration data for CU Plane ethernet CoS marking
// -----------------------------------------------------------------------------
class GrpCosMarking : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CLASS_OF_SERVICE, // CntClassOfService
 };

 GrpCosMarking(uint32_t id);
 ~GrpCosMarking();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /cos-marking/class-of-service
 // Description: CoS Configuration
 // -----------------------------------------------------------------------------
 class CntClassOfService : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_U_PLANE_MARKING, // LeafUPlaneMarking
     ITEM_C_PLANE_MARKING, // LeafCPlaneMarking
     ITEM_M_PLANE_MARKING, // LeafMPlaneMarking
     ITEM_S_PLANE_MARKING, // LeafSPlaneMarking
     ITEM_OTHER_MARKING, // LeafOtherMarking
     ITEM_ENHANCED_UPLANE_MARKINGS, // LstEnhancedUplaneMarkings
   };

   CntClassOfService(uint32_t id);
   ~CntClassOfService();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /cos-marking/class-of-service/u-plane-marking
   // Description: Marking used for default u-plane flows.
   //              7 represents highest priority for u-plane marking
   // -----------------------------------------------------------------------------
   class LeafUPlaneMarking : public YangLeaf {
    public:
     LeafUPlaneMarking(uint32_t id);
     ~LeafUPlaneMarking();

   }; // LeafUPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /cos-marking/class-of-service/c-plane-marking
   // Description: 7 represents highest priority for c-plane marking
   // -----------------------------------------------------------------------------
   class LeafCPlaneMarking : public YangLeaf {
    public:
     LeafCPlaneMarking(uint32_t id);
     ~LeafCPlaneMarking();

   }; // LeafCPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /cos-marking/class-of-service/m-plane-marking
   // Description: 2 represents highest excellent effort for m-plane marking
   // -----------------------------------------------------------------------------
   class LeafMPlaneMarking : public YangLeaf {
    public:
     LeafMPlaneMarking(uint32_t id);
     ~LeafMPlaneMarking();

   }; // LeafMPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /cos-marking/class-of-service/s-plane-marking
   // Description: 7 represents highest priority for s-plane marking
   // -----------------------------------------------------------------------------
   class LeafSPlaneMarking : public YangLeaf {
    public:
     LeafSPlaneMarking(uint32_t id);
     ~LeafSPlaneMarking();

   }; // LeafSPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /cos-marking/class-of-service/other-marking
   // Description: 1 represents best effort for other marking
   // -----------------------------------------------------------------------------
   class LeafOtherMarking : public YangLeaf {
    public:
     LeafOtherMarking(uint32_t id);
     ~LeafOtherMarking();

   }; // LeafOtherMarking

   // -----------------------------------------------------------------------------
   // List:        /cos-marking/class-of-service/enhanced-uplane-markings
   // Description: list of mappings for enhanced (non-default) u-plane markings
   // -----------------------------------------------------------------------------
   class LstEnhancedUplaneMarkings : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_UP_MARKING_NAME, // LeafUpMarkingName
       ITEM_ENHANCED_MARKING, // LeafEnhancedMarking
     };

     LstEnhancedUplaneMarkings(uint32_t id);
     ~LstEnhancedUplaneMarkings();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /cos-marking/class-of-service/enhanced-uplane-markings/up-marking-name
     // Description: The name of the marking
     // -----------------------------------------------------------------------------
     class LeafUpMarkingName : public YangLeaf {
      public:
       LeafUpMarkingName(uint32_t id);
       ~LeafUpMarkingName();

     }; // LeafUpMarkingName

     // -----------------------------------------------------------------------------
     // Leaf:
     // /cos-marking/class-of-service/enhanced-uplane-markings/enhanced-marking
     // Description: the enhanced u-plane marking
     // -----------------------------------------------------------------------------
     class LeafEnhancedMarking : public YangLeaf {
      public:
       LeafEnhancedMarking(uint32_t id);
       ~LeafEnhancedMarking();

     }; // LeafEnhancedMarking

   }; // LstEnhancedUplaneMarkings

 }; // CntClassOfService

}; // GrpCosMarking

// -----------------------------------------------------------------------------
// Grouping:    /dscp-marking
// Description: Configuration data for CU Plane DSCP marking
// -----------------------------------------------------------------------------
class GrpDscpMarking : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_DIFFSERV_MARKINGS, // CntDiffservMarkings
 };

 GrpDscpMarking(uint32_t id);
 ~GrpDscpMarking();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /dscp-marking/diffserv-markings
 // Description: DSCP Configuration
 // -----------------------------------------------------------------------------
 class CntDiffservMarkings : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_U_PLANE_MARKING, // LeafUPlaneMarking
     ITEM_C_PLANE_MARKING, // LeafCPlaneMarking
     ITEM_S_PLANE_MARKING, // LeafSPlaneMarking
     ITEM_OTHER_MARKING, // LeafOtherMarking
     ITEM_ENHANCED_UPLANE_MARKINGS, // LstEnhancedUplaneMarkings
   };

   CntDiffservMarkings(uint32_t id);
   ~CntDiffservMarkings();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /dscp-marking/diffserv-markings/u-plane-marking
   // Description: Marking used for default u-plane flows.
   //              46 represents expedited forwarding
   // -----------------------------------------------------------------------------
   class LeafUPlaneMarking : public YangLeaf {
    public:
     LeafUPlaneMarking(uint32_t id);
     ~LeafUPlaneMarking();

   }; // LeafUPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /dscp-marking/diffserv-markings/c-plane-marking
   // Description: 46 represents expedited forwarding
   // -----------------------------------------------------------------------------
   class LeafCPlaneMarking : public YangLeaf {
    public:
     LeafCPlaneMarking(uint32_t id);
     ~LeafCPlaneMarking();

   }; // LeafCPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /dscp-marking/diffserv-markings/s-plane-marking
   // Description: 46 represents expedited forwarding
   // -----------------------------------------------------------------------------
   class LeafSPlaneMarking : public YangLeaf {
    public:
     LeafSPlaneMarking(uint32_t id);
     ~LeafSPlaneMarking();

   }; // LeafSPlaneMarking

   // -----------------------------------------------------------------------------
   // Leaf:        /dscp-marking/diffserv-markings/other-marking
   // Description: 0 represents best effort forwarding
   // -----------------------------------------------------------------------------
   class LeafOtherMarking : public YangLeaf {
    public:
     LeafOtherMarking(uint32_t id);
     ~LeafOtherMarking();

   }; // LeafOtherMarking

   // -----------------------------------------------------------------------------
   // List:        /dscp-marking/diffserv-markings/enhanced-uplane-markings
   // Description: list of mappings for enhanced (non-default) u-plane markings
   // -----------------------------------------------------------------------------
   class LstEnhancedUplaneMarkings : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_UP_MARKING_NAME, // LeafUpMarkingName
       ITEM_ENHANCED_MARKING, // LeafEnhancedMarking
     };

     LstEnhancedUplaneMarkings(uint32_t id);
     ~LstEnhancedUplaneMarkings();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /dscp-marking/diffserv-markings/enhanced-uplane-markings/up-marking-name
     // Description: The name of the marking
     // -----------------------------------------------------------------------------
     class LeafUpMarkingName : public YangLeaf {
      public:
       LeafUpMarkingName(uint32_t id);
       ~LeafUpMarkingName();

     }; // LeafUpMarkingName

     // -----------------------------------------------------------------------------
     // Leaf:
     // /dscp-marking/diffserv-markings/enhanced-uplane-markings/enhanced-marking
     // Description: the enhanced u-plane marking
     // -----------------------------------------------------------------------------
     class LeafEnhancedMarking : public YangLeaf {
      public:
       LeafEnhancedMarking(uint32_t id);
       ~LeafEnhancedMarking();

     }; // LeafEnhancedMarking

   }; // LstEnhancedUplaneMarkings

 }; // CntDiffservMarkings

}; // GrpDscpMarking


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
class ModuleORanInterfaces : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_UDPIP_BASED_CU_PLANE, // Feature
   ITEM_ALIASMAC_BASED_CU_PLANE, // Feature
 };

 ModuleORanInterfaces(uint32_t id);
 ~ModuleORanInterfaces();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanInterfaces_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_INTERFACES_H_ */
