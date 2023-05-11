/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanDelayManagement.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanDelayManagement.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanDelayManagement_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the O-RU supports adaptive O-RU
// delay profile
//              based on information provided by the NETCONF client.
// -----------------------------------------------------------------------------
FeatureADAPTIVERUPROFILE::FeatureADAPTIVERUPROFILE(uint32_t id)
    : YangFeature("ADAPTIVE-RU-PROFILE", id) {}

FeatureADAPTIVERUPROFILE::~FeatureADAPTIVERUPROFILE() {}

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
// Container:   delay-management
// Description: top level tree covering off O-DU to O-RU delay management
// -----------------------------------------------------------------------------
CntDelayManagement::CntDelayManagement(uint32_t id)
    : YangContainer("delay-management", id) {}

CntDelayManagement::~CntDelayManagement() {}

YangResult_E
CntDelayManagement::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /delay-management/delay-management-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpDelayManagementGroup delayManagementGroupInst(ITEM_DELAY_MANAGEMENT_GROUP);
  delayManagementGroupInst.initialise();
  addGroup(delayManagementGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    bandwidth-configuration
// Description: Grouping for bandwidth and scs configuration
// -----------------------------------------------------------------------------
GrpBandwidthConfiguration::GrpBandwidthConfiguration(uint32_t id)
    : YangGroup("bandwidth-configuration", id) {}

GrpBandwidthConfiguration::~GrpBandwidthConfiguration() {}

YangResult_E
GrpBandwidthConfiguration::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /bandwidth-configuration/bandwidth
  // Description: transmission bandwidth configuration in units of kHz -
  //              covering NBIoT through to New Radio - see 38.104
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafBandwidth bandwidthInst(ITEM_BANDWIDTH);
  addLeaf(bandwidthInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /bandwidth-configuration/subcarrier-spacing
  // Description: subcarrier spacing in Hz
  // Type:        uint32
  // Units:       Hertz
  // -----------------------------------------------------------------------------
  LeafSubcarrierSpacing subcarrierSpacingInst(ITEM_SUBCARRIER_SPACING);
  addLeaf(subcarrierSpacingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /bandwidth-configuration/bandwidth
// Description: transmission bandwidth configuration in units of kHz -
//              covering NBIoT through to New Radio - see 38.104
// -----------------------------------------------------------------------------
GrpBandwidthConfiguration::LeafBandwidth::LeafBandwidth(uint32_t id)
    : YangLeaf("bandwidth", id) {}

GrpBandwidthConfiguration::LeafBandwidth::~LeafBandwidth() {}

// -----------------------------------------------------------------------------
// Leaf:        /bandwidth-configuration/subcarrier-spacing
// Description: subcarrier spacing in Hz
// -----------------------------------------------------------------------------
GrpBandwidthConfiguration::LeafSubcarrierSpacing::LeafSubcarrierSpacing(
    uint32_t id)
    : YangLeaf("subcarrier-spacing", id) {}

GrpBandwidthConfiguration::LeafSubcarrierSpacing::~LeafSubcarrierSpacing() {}

// -----------------------------------------------------------------------------
// Grouping:    t2a-up
// Description: configuration of t2a for uplink
// -----------------------------------------------------------------------------
GrpT2aUp::GrpT2aUp(uint32_t id) : YangGroup("t2a-up", id) {}

GrpT2aUp::~GrpT2aUp() {}

YangResult_E
GrpT2aUp::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-up/t2a-min-up
  // Description: the minimum O-RU data processing delay between receiving IQ
  // data
  //              message over the fronthaul interface and transmitting
  //              the corresponding first IQ sample at the antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMinUp t2aMinUpInst(ITEM_T2A_MIN_UP);
  addLeaf(t2aMinUpInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-up/t2a-max-up
  // Description: the earliest allowable time when a data packet is received
  // before
  //              the corresponding first IQ sample is transmitted at the
  //              antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMaxUp t2aMaxUpInst(ITEM_T2A_MAX_UP);
  addLeaf(t2aMaxUpInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-up/t2a-min-up
// Description: the minimum O-RU data processing delay between receiving IQ data
//              message over the fronthaul interface and transmitting
//              the corresponding first IQ sample at the antenna
// -----------------------------------------------------------------------------
GrpT2aUp::LeafT2aMinUp::LeafT2aMinUp(uint32_t id)
    : YangLeaf("t2a-min-up", id) {}

GrpT2aUp::LeafT2aMinUp::~LeafT2aMinUp() {}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-up/t2a-max-up
// Description: the earliest allowable time when a data packet is received
// before
//              the corresponding first IQ sample is transmitted at the antenna
// -----------------------------------------------------------------------------
GrpT2aUp::LeafT2aMaxUp::LeafT2aMaxUp(uint32_t id)
    : YangLeaf("t2a-max-up", id) {}

GrpT2aUp::LeafT2aMaxUp::~LeafT2aMaxUp() {}

// -----------------------------------------------------------------------------
// Grouping:    t2a-cp-dl
// Description: Grouping for t2a CP for downlink
// -----------------------------------------------------------------------------
GrpT2aCpDl::GrpT2aCpDl(uint32_t id) : YangGroup("t2a-cp-dl", id) {}

GrpT2aCpDl::~GrpT2aCpDl() {}

YangResult_E
GrpT2aCpDl::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-cp-dl/t2a-min-cp-dl
  // Description: the minimum O-RU data processing delay between receiving
  // downlink
  //              real time control plane message over the fronthaul interface
  //              and transmitting the corresponding first IQ sample at the
  //              antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMinCpDl t2aMinCpDlInst(ITEM_T2A_MIN_CP_DL);
  addLeaf(t2aMinCpDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-cp-dl/t2a-max-cp-dl
  // Description: the earliest allowable time when a downlink real time control
  // message
  //              is received before the corresponding first IQ sample is
  //              transmitted at the antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMaxCpDl t2aMaxCpDlInst(ITEM_T2A_MAX_CP_DL);
  addLeaf(t2aMaxCpDlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-cp-dl/t2a-min-cp-dl
// Description: the minimum O-RU data processing delay between receiving
// downlink
//              real time control plane message over the fronthaul interface and
//              transmitting the corresponding first IQ sample at the antenna
// -----------------------------------------------------------------------------
GrpT2aCpDl::LeafT2aMinCpDl::LeafT2aMinCpDl(uint32_t id)
    : YangLeaf("t2a-min-cp-dl", id) {}

GrpT2aCpDl::LeafT2aMinCpDl::~LeafT2aMinCpDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-cp-dl/t2a-max-cp-dl
// Description: the earliest allowable time when a downlink real time control
// message
//              is received before the corresponding first IQ sample is
//              transmitted at the antenna
// -----------------------------------------------------------------------------
GrpT2aCpDl::LeafT2aMaxCpDl::LeafT2aMaxCpDl(uint32_t id)
    : YangLeaf("t2a-max-cp-dl", id) {}

GrpT2aCpDl::LeafT2aMaxCpDl::~LeafT2aMaxCpDl() {}

// -----------------------------------------------------------------------------
// Grouping:    ta3
// Description: Grouping for ta3 configuration
// -----------------------------------------------------------------------------
GrpTa3::GrpTa3(uint32_t id) : YangGroup("ta3", id) {}

GrpTa3::~GrpTa3() {}

YangResult_E
GrpTa3::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ta3/ta3-min
  // Description: the minimum O-RU data processing delay between receiving an IQ
  // sample
  //              at the antenna and transmitting the first data sample over the
  //              fronthaul interface
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTa3Min ta3MinInst(ITEM_TA3_MIN);
  addLeaf(ta3MinInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ta3/ta3-max
  // Description: the maximum O-RU data processing delay between receiving an IQ
  // sample
  //              at the antenna and transmitting the last data sample over the
  //              fronthaul interface
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTa3Max ta3MaxInst(ITEM_TA3_MAX);
  addLeaf(ta3MaxInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ta3/ta3-min
// Description: the minimum O-RU data processing delay between receiving an IQ
// sample
//              at the antenna and transmitting the first data sample over the
//              fronthaul interface
// -----------------------------------------------------------------------------
GrpTa3::LeafTa3Min::LeafTa3Min(uint32_t id) : YangLeaf("ta3-min", id) {}

GrpTa3::LeafTa3Min::~LeafTa3Min() {}

// -----------------------------------------------------------------------------
// Leaf:        /ta3/ta3-max
// Description: the maximum O-RU data processing delay between receiving an IQ
// sample
//              at the antenna and transmitting the last data sample over the
//              fronthaul interface
// -----------------------------------------------------------------------------
GrpTa3::LeafTa3Max::LeafTa3Max(uint32_t id) : YangLeaf("ta3-max", id) {}

GrpTa3::LeafTa3Max::~LeafTa3Max() {}

// -----------------------------------------------------------------------------
// Grouping:    t2a-cp-ul
// Description: Grouping for t2a CP uplink
// -----------------------------------------------------------------------------
GrpT2aCpUl::GrpT2aCpUl(uint32_t id) : YangGroup("t2a-cp-ul", id) {}

GrpT2aCpUl::~GrpT2aCpUl() {}

YangResult_E
GrpT2aCpUl::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-cp-ul/t2a-min-cp-ul
  // Description: the minimum O-RU data processing delay between receiving real
  // time
  //              up-link control plane message over the fronthaul interface and
  //              recieving the first IQ sample at the antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMinCpUl t2aMinCpUlInst(ITEM_T2A_MIN_CP_UL);
  addLeaf(t2aMinCpUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /t2a-cp-ul/t2a-max-cp-ul
  // Description: the earliest allowable time when a real time up-link control
  // message
  //              is received before the corresponding first IQ sample is
  //              received  at the antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT2aMaxCpUl t2aMaxCpUlInst(ITEM_T2A_MAX_CP_UL);
  addLeaf(t2aMaxCpUlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-cp-ul/t2a-min-cp-ul
// Description: the minimum O-RU data processing delay between receiving real
// time
//              up-link control plane message over the fronthaul interface and
//              recieving the first IQ sample at the antenna
// -----------------------------------------------------------------------------
GrpT2aCpUl::LeafT2aMinCpUl::LeafT2aMinCpUl(uint32_t id)
    : YangLeaf("t2a-min-cp-ul", id) {}

GrpT2aCpUl::LeafT2aMinCpUl::~LeafT2aMinCpUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /t2a-cp-ul/t2a-max-cp-ul
// Description: the earliest allowable time when a real time up-link control
// message
//              is received before the corresponding first IQ sample is received
//              at the antenna
// -----------------------------------------------------------------------------
GrpT2aCpUl::LeafT2aMaxCpUl::LeafT2aMaxCpUl(uint32_t id)
    : YangLeaf("t2a-max-cp-ul", id) {}

GrpT2aCpUl::LeafT2aMaxCpUl::~LeafT2aMaxCpUl() {}

// -----------------------------------------------------------------------------
// Grouping:    ru-delay-profile
// Description: Grouping for ru delay profile
// -----------------------------------------------------------------------------
GrpRuDelayProfile::GrpRuDelayProfile(uint32_t id)
    : YangGroup("ru-delay-profile", id) {}

GrpRuDelayProfile::~GrpRuDelayProfile() {}

YangResult_E
GrpRuDelayProfile::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ru-delay-profile/tcp-adv-dl
  // Description: the time difference (advance) between the reception window for
  //              downlink real time Control messages and reception window for
  //              the corresponding IQ data messages.
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTcpAdvDl tcpAdvDlInst(ITEM_TCP_ADV_DL);
  addLeaf(tcpAdvDlInst);

  // -----------------------------------------------------------------------------
  // Uses:        /ru-delay-profile/t2a-up
  // Description:
  // -----------------------------------------------------------------------------
  GrpT2aUp t2aUpInst(ITEM_T2A_UP);
  t2aUpInst.initialise();
  addGroup(t2aUpInst);

  // -----------------------------------------------------------------------------
  // Uses:        /ru-delay-profile/t2a-cp-dl
  // Description:
  // -----------------------------------------------------------------------------
  GrpT2aCpDl t2aCpDlInst(ITEM_T2A_CP_DL);
  t2aCpDlInst.initialise();
  addGroup(t2aCpDlInst);

  // -----------------------------------------------------------------------------
  // Uses:        /ru-delay-profile/ta3
  // Description:
  // -----------------------------------------------------------------------------
  GrpTa3 ta3Inst(ITEM_TA3);
  ta3Inst.initialise();
  addGroup(ta3Inst);

  // -----------------------------------------------------------------------------
  // Uses:        /ru-delay-profile/t2a-cp-ul
  // Description:
  // -----------------------------------------------------------------------------
  GrpT2aCpUl t2aCpUlInst(ITEM_T2A_CP_UL);
  t2aCpUlInst.initialise();
  addGroup(t2aCpUlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ru-delay-profile/tcp-adv-dl
// Description: the time difference (advance) between the reception window for
//              downlink real time Control messages and reception window for the
//              corresponding IQ data messages.
// -----------------------------------------------------------------------------
GrpRuDelayProfile::LeafTcpAdvDl::LeafTcpAdvDl(uint32_t id)
    : YangLeaf("tcp-adv-dl", id) {}

GrpRuDelayProfile::LeafTcpAdvDl::~LeafTcpAdvDl() {}

// -----------------------------------------------------------------------------
// Grouping:    o-du-delay-profile
// Description: Grouping for O-DU delay profile
// -----------------------------------------------------------------------------
GrpODuDelayProfile::GrpODuDelayProfile(uint32_t id)
    : YangGroup("o-du-delay-profile", id) {}

GrpODuDelayProfile::~GrpODuDelayProfile() {}

YangResult_E
GrpODuDelayProfile::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /o-du-delay-profile/t1a-max-up
  // Description: the earliest possible time which the O-DU can support
  // transmiting
  //              an IQ data message prior to transmission of the corresponding
  //              IQ samples at the antenna
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT1aMaxUp t1aMaxUpInst(ITEM_T1A_MAX_UP);
  addLeaf(t1aMaxUpInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /o-du-delay-profile/tx-max
  // Description: The maximum amount of time which the O-DU requires to transmit
  //              all downlink user plane IQ data message for a symbol
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTxMax txMaxInst(ITEM_TX_MAX);
  addLeaf(txMaxInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /o-du-delay-profile/ta4-max
  // Description: the latest possible time which the O-DU can support receiving
  // the
  //              last uplink user plane IQ data message for a symbol.
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafTa4Max ta4MaxInst(ITEM_TA4_MAX);
  addLeaf(ta4MaxInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /o-du-delay-profile/rx-max
  // Description: The maximum time difference the O-DU can support between
  //              receiving the first user plane IQ data message for a symbol
  //              and receiving the last user plane IQ data message for the same
  //              symbol
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafRxMax rxMaxInst(ITEM_RX_MAX);
  addLeaf(rxMaxInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /o-du-delay-profile/t1a-max-up
// Description: the earliest possible time which the O-DU can support
// transmiting
//              an IQ data message prior to transmission of the corresponding IQ
//              samples at the antenna
// -----------------------------------------------------------------------------
GrpODuDelayProfile::LeafT1aMaxUp::LeafT1aMaxUp(uint32_t id)
    : YangLeaf("t1a-max-up", id) {}

GrpODuDelayProfile::LeafT1aMaxUp::~LeafT1aMaxUp() {}

// -----------------------------------------------------------------------------
// Leaf:        /o-du-delay-profile/tx-max
// Description: The maximum amount of time which the O-DU requires to transmit
//              all downlink user plane IQ data message for a symbol
// -----------------------------------------------------------------------------
GrpODuDelayProfile::LeafTxMax::LeafTxMax(uint32_t id)
    : YangLeaf("tx-max", id) {}

GrpODuDelayProfile::LeafTxMax::~LeafTxMax() {}

// -----------------------------------------------------------------------------
// Leaf:        /o-du-delay-profile/ta4-max
// Description: the latest possible time which the O-DU can support receiving
// the
//              last uplink user plane IQ data message for a symbol.
// -----------------------------------------------------------------------------
GrpODuDelayProfile::LeafTa4Max::LeafTa4Max(uint32_t id)
    : YangLeaf("ta4-max", id) {}

GrpODuDelayProfile::LeafTa4Max::~LeafTa4Max() {}

// -----------------------------------------------------------------------------
// Leaf:        /o-du-delay-profile/rx-max
// Description: The maximum time difference the O-DU can support between
//              receiving the first user plane IQ data message for a symbol and
//              receiving the last user plane IQ data message for the same
//              symbol
// -----------------------------------------------------------------------------
GrpODuDelayProfile::LeafRxMax::LeafRxMax(uint32_t id)
    : YangLeaf("rx-max", id) {}

GrpODuDelayProfile::LeafRxMax::~LeafRxMax() {}

// -----------------------------------------------------------------------------
// Grouping:    t12
// Description: Grouping for t12
// -----------------------------------------------------------------------------
GrpT12::GrpT12(uint32_t id) : YangGroup("t12", id) {}

GrpT12::~GrpT12() {}

YangResult_E
GrpT12::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /t12/t12-min
  // Description: the minimum measured delay between DU port-ID and O-RU port-ID
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT12Min t12MinInst(ITEM_T12_MIN);
  addLeaf(t12MinInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /t12/t12-max
  // Description: the maximum measured delay between CU port-ID and O-RU port-ID
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT12Max t12MaxInst(ITEM_T12_MAX);
  addLeaf(t12MaxInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /t12/t12-min
// Description: the minimum measured delay between DU port-ID and O-RU port-ID
// -----------------------------------------------------------------------------
GrpT12::LeafT12Min::LeafT12Min(uint32_t id) : YangLeaf("t12-min", id) {}

GrpT12::LeafT12Min::~LeafT12Min() {}

// -----------------------------------------------------------------------------
// Leaf:        /t12/t12-max
// Description: the maximum measured delay between CU port-ID and O-RU port-ID
// -----------------------------------------------------------------------------
GrpT12::LeafT12Max::LeafT12Max(uint32_t id) : YangLeaf("t12-max", id) {}

GrpT12::LeafT12Max::~LeafT12Max() {}

// -----------------------------------------------------------------------------
// Grouping:    t34
// Description: Grouping for t34
// -----------------------------------------------------------------------------
GrpT34::GrpT34(uint32_t id) : YangGroup("t34", id) {}

GrpT34::~GrpT34() {}

YangResult_E
GrpT34::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /t34/t34-min
  // Description: the minimum measured delay between O-RU port-ID and CU port-ID
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT34Min t34MinInst(ITEM_T34_MIN);
  addLeaf(t34MinInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /t34/t34-max
  // Description: the maximum measured delay between O-RU port-ID and CU port-ID
  // Type:        uint32
  // Units:       nanoseconds
  // -----------------------------------------------------------------------------
  LeafT34Max t34MaxInst(ITEM_T34_MAX);
  addLeaf(t34MaxInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /t34/t34-min
// Description: the minimum measured delay between O-RU port-ID and CU port-ID
// -----------------------------------------------------------------------------
GrpT34::LeafT34Min::LeafT34Min(uint32_t id) : YangLeaf("t34-min", id) {}

GrpT34::LeafT34Min::~LeafT34Min() {}

// -----------------------------------------------------------------------------
// Leaf:        /t34/t34-max
// Description: the maximum measured delay between O-RU port-ID and CU port-ID
// -----------------------------------------------------------------------------
GrpT34::LeafT34Max::LeafT34Max(uint32_t id) : YangLeaf("t34-max", id) {}

GrpT34::LeafT34Max::~LeafT34Max() {}

// -----------------------------------------------------------------------------
// Grouping:    delay-management-group
// Description:
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::GrpDelayManagementGroup(uint32_t id)
    : YangGroup("delay-management-group", id) {}

GrpDelayManagementGroup::~GrpDelayManagementGroup() {}

YangResult_E
GrpDelayManagementGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /delay-management-group/bandwidth-scs-delay-state
  // Description: Array of structures containing sets of parameters for delay
  // management. Array Key:
  // -----------------------------------------------------------------------------
  LstBandwidthScsDelayState bandwidthScsDelayStateInst(
      ITEM_BANDWIDTH_SCS_DELAY_STATE);
  bandwidthScsDelayStateInst.initialise();
  addList(bandwidthScsDelayStateInst);

  // -----------------------------------------------------------------------------
  // Container:   /delay-management-group/adaptive-delay-configuration
  // Description: container for adaptive delay parameters
  // -----------------------------------------------------------------------------
  CntAdaptiveDelayConfiguration adaptiveDelayConfigurationInst(
      ITEM_ADAPTIVE_DELAY_CONFIGURATION);
  adaptiveDelayConfigurationInst.initialise();
  addContainer(adaptiveDelayConfigurationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        bandwidth-scs-delay-state
// Description: Array of structures containing sets of parameters for delay
// management.
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::LstBandwidthScsDelayState::LstBandwidthScsDelayState(
    uint32_t id)
    : YangList("bandwidth-scs-delay-state", id) {}

GrpDelayManagementGroup::LstBandwidthScsDelayState::
    ~LstBandwidthScsDelayState() {}

YangResult_E
GrpDelayManagementGroup::LstBandwidthScsDelayState::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:
  // /delay-management-group/bandwidth-scs-delay-state/ru-delay-profile
  // Description: container for O-RU delay parameters
  // -----------------------------------------------------------------------------
  CntRuDelayProfile ruDelayProfileInst(ITEM_RU_DELAY_PROFILE);
  ruDelayProfileInst.initialise();
  addContainer(ruDelayProfileInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/bandwidth-scs-delay-state/bandwidth-configuration
  // Description:
  // -----------------------------------------------------------------------------
  GrpBandwidthConfiguration bandwidthConfigurationInst(
      ITEM_BANDWIDTH_CONFIGURATION);
  bandwidthConfigurationInst.initialise();
  addGroup(bandwidthConfigurationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   ru-delay-profile
// Description: container for O-RU delay parameters
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::LstBandwidthScsDelayState::CntRuDelayProfile::
    CntRuDelayProfile(uint32_t id)
    : YangContainer("ru-delay-profile", id) {}

GrpDelayManagementGroup::LstBandwidthScsDelayState::CntRuDelayProfile::
    ~CntRuDelayProfile() {}

YangResult_E
GrpDelayManagementGroup::LstBandwidthScsDelayState::CntRuDelayProfile::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/bandwidth-scs-delay-state/ru-delay-profile/ru-delay-profile
  // Description:
  // -----------------------------------------------------------------------------
  GrpRuDelayProfile ruDelayProfileInst(ITEM_RU_DELAY_PROFILE);
  ruDelayProfileInst.initialise();
  addGroup(ruDelayProfileInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   adaptive-delay-configuration
// Description: container for adaptive delay parameters
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    CntAdaptiveDelayConfiguration(uint32_t id)
    : YangContainer("adaptive-delay-configuration", id) {}

GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    ~CntAdaptiveDelayConfiguration() {}

YangResult_E
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:
  // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state
  // Description: Array of structures containing sets of parameters for delay
  // management. Array Key:
  // -----------------------------------------------------------------------------
  LstBandwidthScsDelayState bandwidthScsDelayStateInst(
      ITEM_BANDWIDTH_SCS_DELAY_STATE);
  bandwidthScsDelayStateInst.initialise();
  addList(bandwidthScsDelayStateInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /delay-management-group/adaptive-delay-configuration/transport-delay
  // Description: O-DU provided transport-delay parameters
  // -----------------------------------------------------------------------------
  CntTransportDelay transportDelayInst(ITEM_TRANSPORT_DELAY);
  transportDelayInst.initialise();
  addContainer(transportDelayInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        bandwidth-scs-delay-state
// Description: Array of structures containing sets of parameters for delay
// management.
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::LstBandwidthScsDelayState(uint32_t id)
    : YangList("bandwidth-scs-delay-state", id) {}

GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::~LstBandwidthScsDelayState() {}

YangResult_E
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:
  // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state/o-du-delay-profile
  // Description: O-DU provided delay profile for adaptive delay configuration
  // -----------------------------------------------------------------------------
  CntODuDelayProfile oDuDelayProfileInst(ITEM_O_DU_DELAY_PROFILE);
  oDuDelayProfileInst.initialise();
  addContainer(oDuDelayProfileInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state/bandwidth-configuration
  // Description:
  // -----------------------------------------------------------------------------
  GrpBandwidthConfiguration bandwidthConfigurationInst(
      ITEM_BANDWIDTH_CONFIGURATION);
  bandwidthConfigurationInst.initialise();
  addGroup(bandwidthConfigurationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   o-du-delay-profile
// Description: O-DU provided delay profile for adaptive delay configuration
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::CntODuDelayProfile::CntODuDelayProfile(
        uint32_t id)
    : YangContainer("o-du-delay-profile", id) {}

GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::CntODuDelayProfile::~CntODuDelayProfile() {}

YangResult_E
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::
    LstBandwidthScsDelayState::CntODuDelayProfile::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/adaptive-delay-configuration/bandwidth-scs-delay-state/o-du-delay-profile/o-du-delay-profile
  // Description:
  // -----------------------------------------------------------------------------
  GrpODuDelayProfile oDuDelayProfileInst(ITEM_O_DU_DELAY_PROFILE);
  oDuDelayProfileInst.initialise();
  addGroup(oDuDelayProfileInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   transport-delay
// Description: O-DU provided transport-delay parameters
// -----------------------------------------------------------------------------
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::CntTransportDelay::
    CntTransportDelay(uint32_t id)
    : YangContainer("transport-delay", id) {}

GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::CntTransportDelay::
    ~CntTransportDelay() {}

YangResult_E
GrpDelayManagementGroup::CntAdaptiveDelayConfiguration::CntTransportDelay::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/adaptive-delay-configuration/transport-delay/t12
  // Description:
  // -----------------------------------------------------------------------------
  GrpT12 t12Inst(ITEM_T12);
  t12Inst.initialise();
  addGroup(t12Inst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /delay-management-group/adaptive-delay-configuration/transport-delay/t34
  // Description:
  // -----------------------------------------------------------------------------
  GrpT34 t34Inst(ITEM_T34);
  t34Inst.initialise();
  addGroup(t34Inst);

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
ModuleORanDelayManagement::ModuleORanDelayManagement(uint32_t id)
    : YangModule(
          "o-ran-delay-management",
          "o-ran-delay-management.yang",
          "o-ran-delay",
          "urn:o-ran:delay:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the O-RU supports adaptive O-RU
  // delay profile
  //              based on information provided by the NETCONF client.
  // -----------------------------------------------------------------------------
  FeatureADAPTIVERUPROFILE ADAPTIVERUPROFILEInst(ITEM_ADAPTIVE_RU_PROFILE);
  addFeature(ADAPTIVERUPROFILEInst);

  // -----------------------------------------------------------------------------
  // Container:   /delay-management
  // Description: top level tree covering off O-DU to O-RU delay management
  // -----------------------------------------------------------------------------
  CntDelayManagement delayManagementInst(ITEM_DELAY_MANAGEMENT);
  delayManagementInst.initialise();
  addContainer(delayManagementInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanDelayManagement::~ModuleORanDelayManagement() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanDelayManagement::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanDelayManagement>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanDelayManagement::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
