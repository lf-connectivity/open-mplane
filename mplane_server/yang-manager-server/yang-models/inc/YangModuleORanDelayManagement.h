#ifndef _MODULE_O_RAN_DELAY_MANAGEMENT_H_
#define _MODULE_O_RAN_DELAY_MANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanDelayManagement.h
 * \brief     Module ORanDelayManagement interface
 *
 *
 * \details   This file defines the YANG module o-ran-delay-management
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-delay-management"
 *            YANG Filename:    "o-ran-delay-management.yang"
 *            Module Prefix:    "o-ran-delay"
 *            Module namespace: "urn:o-ran:delay:1.0"
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


namespace Mplane {

namespace ModuleORanDelayManagement_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************


// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports adaptive O-RU delay profile
//              based on information provided by the NETCONF client.
// -----------------------------------------------------------------------------
class FeatureADAPTIVERUPROFILE : public YangFeature
{
public:
 FeatureADAPTIVERUPROFILE(uint32_t id);
 ~FeatureADAPTIVERUPROFILE();

}; // FeatureADAPTIVERUPROFILE


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
// Container:   /delay-management
// Description: top level tree covering off O-DU to O-RU delay management
// -----------------------------------------------------------------------------
class CntDelayManagement : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_DELAY_MANAGEMENT_GROUP, // Use GrpDelayManagementGroup
 };

 CntDelayManagement(uint32_t id);
 ~CntDelayManagement();

 YangResult_E initialise(void);

}; // CntDelayManagement


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /bandwidth-configuration
// Description: Grouping for bandwidth and scs configuration
// -----------------------------------------------------------------------------
class GrpBandwidthConfiguration : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_BANDWIDTH, // LeafBandwidth
   ITEM_SUBCARRIER_SPACING, // LeafSubcarrierSpacing
 };

 GrpBandwidthConfiguration(uint32_t id);
 ~GrpBandwidthConfiguration();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /bandwidth-configuration/bandwidth
 // Description: transmission bandwidth configuration in units of kHz -
 //              covering NBIoT through to New Radio - see 38.104
 // -----------------------------------------------------------------------------
 class LeafBandwidth : public YangLeaf {
  public:
   LeafBandwidth(uint32_t id);
   ~LeafBandwidth();

 }; // LeafBandwidth

 // -----------------------------------------------------------------------------
 // Leaf:        /bandwidth-configuration/subcarrier-spacing
 // Description: subcarrier spacing in Hz
 // -----------------------------------------------------------------------------
 class LeafSubcarrierSpacing : public YangLeaf {
  public:
   LeafSubcarrierSpacing(uint32_t id);
   ~LeafSubcarrierSpacing();

 }; // LeafSubcarrierSpacing

}; // GrpBandwidthConfiguration

// -----------------------------------------------------------------------------
// Grouping:    /t2a-up
// Description: configuration of t2a for uplink
// -----------------------------------------------------------------------------
class GrpT2aUp : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T2A_MIN_UP, // LeafT2aMinUp
   ITEM_T2A_MAX_UP, // LeafT2aMaxUp
 };

 GrpT2aUp(uint32_t id);
 ~GrpT2aUp();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-up/t2a-min-up
 // Description: the minimum O-RU data processing delay between receiving IQ
 // data
 //              message over the fronthaul interface and transmitting
 //              the corresponding first IQ sample at the antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMinUp : public YangLeaf {
  public:
   LeafT2aMinUp(uint32_t id);
   ~LeafT2aMinUp();

 }; // LeafT2aMinUp

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-up/t2a-max-up
 // Description: the earliest allowable time when a data packet is received
 // before
 //              the corresponding first IQ sample is transmitted at the antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMaxUp : public YangLeaf {
  public:
   LeafT2aMaxUp(uint32_t id);
   ~LeafT2aMaxUp();

 }; // LeafT2aMaxUp

}; // GrpT2aUp

// -----------------------------------------------------------------------------
// Grouping:    /t2a-cp-dl
// Description: Grouping for t2a CP for downlink
// -----------------------------------------------------------------------------
class GrpT2aCpDl : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T2A_MIN_CP_DL, // LeafT2aMinCpDl
   ITEM_T2A_MAX_CP_DL, // LeafT2aMaxCpDl
 };

 GrpT2aCpDl(uint32_t id);
 ~GrpT2aCpDl();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-cp-dl/t2a-min-cp-dl
 // Description: the minimum O-RU data processing delay between receiving
 // downlink
 //              real time control plane message over the fronthaul interface
 //              and transmitting the corresponding first IQ sample at the
 //              antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMinCpDl : public YangLeaf {
  public:
   LeafT2aMinCpDl(uint32_t id);
   ~LeafT2aMinCpDl();

 }; // LeafT2aMinCpDl

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-cp-dl/t2a-max-cp-dl
 // Description: the earliest allowable time when a downlink real time control
 // message
 //              is received before the corresponding first IQ sample is
 //              transmitted at the antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMaxCpDl : public YangLeaf {
  public:
   LeafT2aMaxCpDl(uint32_t id);
   ~LeafT2aMaxCpDl();

 }; // LeafT2aMaxCpDl

}; // GrpT2aCpDl

// -----------------------------------------------------------------------------
// Grouping:    /ta3
// Description: Grouping for ta3 configuration
// -----------------------------------------------------------------------------
class GrpTa3 : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TA3_MIN, // LeafTa3Min
   ITEM_TA3_MAX, // LeafTa3Max
 };

 GrpTa3(uint32_t id);
 ~GrpTa3();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /ta3/ta3-min
 // Description: the minimum O-RU data processing delay between receiving an IQ
 // sample
 //              at the antenna and transmitting the first data sample over the
 //              fronthaul interface
 // -----------------------------------------------------------------------------
 class LeafTa3Min : public YangLeaf {
  public:
   LeafTa3Min(uint32_t id);
   ~LeafTa3Min();

 }; // LeafTa3Min

 // -----------------------------------------------------------------------------
 // Leaf:        /ta3/ta3-max
 // Description: the maximum O-RU data processing delay between receiving an IQ
 // sample
 //              at the antenna and transmitting the last data sample over the
 //              fronthaul interface
 // -----------------------------------------------------------------------------
 class LeafTa3Max : public YangLeaf {
  public:
   LeafTa3Max(uint32_t id);
   ~LeafTa3Max();

 }; // LeafTa3Max

}; // GrpTa3

// -----------------------------------------------------------------------------
// Grouping:    /t2a-cp-ul
// Description: Grouping for t2a CP uplink
// -----------------------------------------------------------------------------
class GrpT2aCpUl : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T2A_MIN_CP_UL, // LeafT2aMinCpUl
   ITEM_T2A_MAX_CP_UL, // LeafT2aMaxCpUl
 };

 GrpT2aCpUl(uint32_t id);
 ~GrpT2aCpUl();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-cp-ul/t2a-min-cp-ul
 // Description: the minimum O-RU data processing delay between receiving real
 // time
 //              up-link control plane message over the fronthaul interface and
 //              recieving the first IQ sample at the antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMinCpUl : public YangLeaf {
  public:
   LeafT2aMinCpUl(uint32_t id);
   ~LeafT2aMinCpUl();

 }; // LeafT2aMinCpUl

 // -----------------------------------------------------------------------------
 // Leaf:        /t2a-cp-ul/t2a-max-cp-ul
 // Description: the earliest allowable time when a real time up-link control
 // message
 //              is received before the corresponding first IQ sample is
 //              received  at the antenna
 // -----------------------------------------------------------------------------
 class LeafT2aMaxCpUl : public YangLeaf {
  public:
   LeafT2aMaxCpUl(uint32_t id);
   ~LeafT2aMaxCpUl();

 }; // LeafT2aMaxCpUl

}; // GrpT2aCpUl

// -----------------------------------------------------------------------------
// Grouping:    /ru-delay-profile
// Description: Grouping for ru delay profile
// -----------------------------------------------------------------------------
class GrpRuDelayProfile : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TCP_ADV_DL, // LeafTcpAdvDl
   ITEM_T2A_UP, // Use GrpT2aUp
   ITEM_T2A_CP_DL, // Use GrpT2aCpDl
   ITEM_TA3, // Use GrpTa3
   ITEM_T2A_CP_UL, // Use GrpT2aCpUl
 };

 GrpRuDelayProfile(uint32_t id);
 ~GrpRuDelayProfile();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-delay-profile/tcp-adv-dl
 // Description: the time difference (advance) between the reception window for
 //              downlink real time Control messages and reception window for
 //              the corresponding IQ data messages.
 // -----------------------------------------------------------------------------
 class LeafTcpAdvDl : public YangLeaf {
  public:
   LeafTcpAdvDl(uint32_t id);
   ~LeafTcpAdvDl();

 }; // LeafTcpAdvDl

}; // GrpRuDelayProfile

// -----------------------------------------------------------------------------
// Grouping:    /o-du-delay-profile
// Description: Grouping for O-DU delay profile
// -----------------------------------------------------------------------------
class GrpODuDelayProfile : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T1A_MAX_UP, // LeafT1aMaxUp
   ITEM_TX_MAX, // LeafTxMax
   ITEM_TA4_MAX, // LeafTa4Max
   ITEM_RX_MAX, // LeafRxMax
 };

 GrpODuDelayProfile(uint32_t id);
 ~GrpODuDelayProfile();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /o-du-delay-profile/t1a-max-up
 // Description: the earliest possible time which the O-DU can support
 // transmiting
 //              an IQ data message prior to transmission of the corresponding
 //              IQ samples at the antenna
 // -----------------------------------------------------------------------------
 class LeafT1aMaxUp : public YangLeaf {
  public:
   LeafT1aMaxUp(uint32_t id);
   ~LeafT1aMaxUp();

 }; // LeafT1aMaxUp

 // -----------------------------------------------------------------------------
 // Leaf:        /o-du-delay-profile/tx-max
 // Description: The maximum amount of time which the O-DU requires to transmit
 //              all downlink user plane IQ data message for a symbol
 // -----------------------------------------------------------------------------
 class LeafTxMax : public YangLeaf {
  public:
   LeafTxMax(uint32_t id);
   ~LeafTxMax();

 }; // LeafTxMax

 // -----------------------------------------------------------------------------
 // Leaf:        /o-du-delay-profile/ta4-max
 // Description: the latest possible time which the O-DU can support receiving
 // the
 //              last uplink user plane IQ data message for a symbol.
 // -----------------------------------------------------------------------------
 class LeafTa4Max : public YangLeaf {
  public:
   LeafTa4Max(uint32_t id);
   ~LeafTa4Max();

 }; // LeafTa4Max

 // -----------------------------------------------------------------------------
 // Leaf:        /o-du-delay-profile/rx-max
 // Description: The maximum time difference the O-DU can support between
 //              receiving the first user plane IQ data message for a symbol and
 //              receiving the last user plane IQ data message for the same
 //              symbol
 // -----------------------------------------------------------------------------
 class LeafRxMax : public YangLeaf {
  public:
   LeafRxMax(uint32_t id);
   ~LeafRxMax();

 }; // LeafRxMax

}; // GrpODuDelayProfile

// -----------------------------------------------------------------------------
// Grouping:    /t12
// Description: Grouping for t12
// -----------------------------------------------------------------------------
class GrpT12 : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T12_MIN, // LeafT12Min
   ITEM_T12_MAX, // LeafT12Max
 };

 GrpT12(uint32_t id);
 ~GrpT12();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /t12/t12-min
 // Description: the minimum measured delay between DU port-ID and O-RU port-ID
 // -----------------------------------------------------------------------------
 class LeafT12Min : public YangLeaf {
  public:
   LeafT12Min(uint32_t id);
   ~LeafT12Min();

 }; // LeafT12Min

 // -----------------------------------------------------------------------------
 // Leaf:        /t12/t12-max
 // Description: the maximum measured delay between CU port-ID and O-RU port-ID
 // -----------------------------------------------------------------------------
 class LeafT12Max : public YangLeaf {
  public:
   LeafT12Max(uint32_t id);
   ~LeafT12Max();

 }; // LeafT12Max

}; // GrpT12

// -----------------------------------------------------------------------------
// Grouping:    /t34
// Description: Grouping for t34
// -----------------------------------------------------------------------------
class GrpT34 : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_T34_MIN, // LeafT34Min
   ITEM_T34_MAX, // LeafT34Max
 };

 GrpT34(uint32_t id);
 ~GrpT34();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /t34/t34-min
 // Description: the minimum measured delay between O-RU port-ID and CU port-ID
 // -----------------------------------------------------------------------------
 class LeafT34Min : public YangLeaf {
  public:
   LeafT34Min(uint32_t id);
   ~LeafT34Min();

 }; // LeafT34Min

 // -----------------------------------------------------------------------------
 // Leaf:        /t34/t34-max
 // Description: the maximum measured delay between O-RU port-ID and CU port-ID
 // -----------------------------------------------------------------------------
 class LeafT34Max : public YangLeaf {
  public:
   LeafT34Max(uint32_t id);
   ~LeafT34Max();

 }; // LeafT34Max

}; // GrpT34

// -----------------------------------------------------------------------------
// Grouping:    /delay-management-group
// Description:
// -----------------------------------------------------------------------------
class GrpDelayManagementGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ADAPTIVE_DELAY_CONFIGURATION, // CntAdaptiveDelayConfiguration
   ITEM_BANDWIDTH_SCS_DELAY_STATE, // LstBandwidthScsDelayState
 };

 GrpDelayManagementGroup(uint32_t id);
 ~GrpDelayManagementGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /delay-management-group/adaptive-delay-configuration
 // Description: container for adaptive delay parameters
 // -----------------------------------------------------------------------------
 class CntAdaptiveDelayConfiguration : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_TRANSPORT_DELAY, // CntTransportDelay
     ITEM_BANDWIDTH_SCS_DELAY_STATE, // LstBandwidthScsDelayState
   };

   CntAdaptiveDelayConfiguration(uint32_t id);
   ~CntAdaptiveDelayConfiguration();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Container:
   // /delay-management-group/adaptive-delay-configuration/transport-delay
   // Description: O-DU provided transport-delay parameters
   // -----------------------------------------------------------------------------
   class CntTransportDelay : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_T12, // Use GrpT12
       ITEM_T34, // Use GrpT34
     };

     CntTransportDelay(uint32_t id);
     ~CntTransportDelay();

     YangResult_E initialise(void);

   }; // CntTransportDelay

   // -----------------------------------------------------------------------------
   // List:
   // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state
   // Description: Array of structures containing sets of parameters for delay
   // management.
   // -----------------------------------------------------------------------------
   class LstBandwidthScsDelayState : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_O_DU_DELAY_PROFILE, // CntODuDelayProfile
       ITEM_BANDWIDTH_CONFIGURATION, // Use GrpBandwidthConfiguration
     };

     LstBandwidthScsDelayState(uint32_t id);
     ~LstBandwidthScsDelayState();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Container:
     // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state/o-du-delay-profile
     // Description: O-DU provided delay profile for adaptive delay
     // configuration
     // -----------------------------------------------------------------------------
     class CntODuDelayProfile : public YangContainer {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_O_DU_DELAY_PROFILE, // Use GrpODuDelayProfile
       };

       CntODuDelayProfile(uint32_t id);
       ~CntODuDelayProfile();

       YangResult_E initialise(void);

     }; // CntODuDelayProfile

   }; // LstBandwidthScsDelayState

 }; // CntAdaptiveDelayConfiguration

 // -----------------------------------------------------------------------------
 // List:        /delay-management-group/bandwidth-scs-delay-state
 // Description: Array of structures containing sets of parameters for delay
 // management.
 // -----------------------------------------------------------------------------
 class LstBandwidthScsDelayState : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_RU_DELAY_PROFILE, // CntRuDelayProfile
     ITEM_BANDWIDTH_CONFIGURATION, // Use GrpBandwidthConfiguration
   };

   LstBandwidthScsDelayState(uint32_t id);
   ~LstBandwidthScsDelayState();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Container:
   // /delay-management-group/bandwidth-scs-delay-state/ru-delay-profile
   // Description: container for O-RU delay parameters
   // -----------------------------------------------------------------------------
   class CntRuDelayProfile : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_RU_DELAY_PROFILE, // Use GrpRuDelayProfile
     };

     CntRuDelayProfile(uint32_t id);
     ~CntRuDelayProfile();

     YangResult_E initialise(void);

   }; // CntRuDelayProfile

 }; // LstBandwidthScsDelayState

}; // GrpDelayManagementGroup


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
// Module:      o-ran-delay-management
// Description: This module covers off aspects of O-DU to O-RU delay management,
//              including config data related to O-RU transmission and reception
//              windows.
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
class ModuleORanDelayManagement : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ADAPTIVE_RU_PROFILE, // Feature
   ITEM_DELAY_MANAGEMENT, // CntDelayManagement
 };

 ModuleORanDelayManagement(uint32_t id);
 ~ModuleORanDelayManagement();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanDelayManagement_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_DELAY_MANAGEMENT_H_ */
