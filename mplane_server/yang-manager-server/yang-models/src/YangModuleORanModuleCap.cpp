/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanModuleCap.cpp
 * \brief     Module ORanModuleCap interface
 *
 *
 * \details   This file defines the YANG module o-ran-module-cap interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-module-cap"
 *            YANG Filename:    "o-ran-module-cap.yang"
 *            Module Prefix:    "o-ran-module-cap"
 *            Module namespace: "urn:o-ran:module-cap:1.0"
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
#include "YangModuleORanModuleCap.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanModuleCap_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that the Radio Unit supports LAA.
// -----------------------------------------------------------------------------
FeatureLAA::FeatureLAA(uint32_t id) : YangFeature("LAA", id) {}

FeatureLAA::~FeatureLAA() {}

// -----------------------------------------------------------------------------
// Feature
// Description: This leaf is used to indicate whether the O-RU supports O-RAN
// Radio Transport Fragmentation
// -----------------------------------------------------------------------------
FeatureTRANSPORTFRAGMENTATION::FeatureTRANSPORTFRAGMENTATION(uint32_t id)
    : YangFeature("TRANSPORT-FRAGMENTATION", id) {}

FeatureTRANSPORTFRAGMENTATION::~FeatureTRANSPORTFRAGMENTATION() {}

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
// Container:   module-capability
// Description: module capability object responsible for providing module
// capability.
// -----------------------------------------------------------------------------
CntModuleCapability::CntModuleCapability(uint32_t id)
    : YangContainer("module-capability", id) {}

CntModuleCapability::~CntModuleCapability() {}

YangResult_E
CntModuleCapability::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /module-capability/band-capabilities
  // Description: Capabilities that are needed to be defined per each band
  // Array Key:
  // -----------------------------------------------------------------------------
  LstBandCapabilities bandCapabilitiesInst(ITEM_BAND_CAPABILITIES);
  bandCapabilitiesInst.initialise();
  addList(bandCapabilitiesInst);

  // -----------------------------------------------------------------------------
  // Container:   /module-capability/ru-capabilities
  // Description: Structure representing set of capabilities.
  // -----------------------------------------------------------------------------
  CntRuCapabilities ruCapabilitiesInst(ITEM_RU_CAPABILITIES);
  ruCapabilitiesInst.initialise();
  addContainer(ruCapabilitiesInst);

  // -----------------------------------------------------------------------------
  // Container:   /module-capability/rw-sub-band-info
  // Description: config true leafrefs for use as constraints for config true
  // leafs
  // -----------------------------------------------------------------------------
  CntRwSubBandInfo rwSubBandInfoInst(ITEM_RW_SUB_BAND_INFO);
  rwSubBandInfoInst.initialise();
  addContainer(rwSubBandInfoInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        band-capabilities
// Description: Capabilities that are needed to be defined per each band
// -----------------------------------------------------------------------------
CntModuleCapability::LstBandCapabilities::LstBandCapabilities(uint32_t id)
    : YangList("band-capabilities", id) {}

CntModuleCapability::LstBandCapabilities::~LstBandCapabilities() {}

YangResult_E
CntModuleCapability::LstBandCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /module-capability/band-capabilities/band-capabilities
  // Description:
  // -----------------------------------------------------------------------------
  GrpBandCapabilities bandCapabilitiesInst(ITEM_BAND_CAPABILITIES);
  bandCapabilitiesInst.initialise();
  addGroup(bandCapabilitiesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   ru-capabilities
// Description: Structure representing set of capabilities.
// -----------------------------------------------------------------------------
CntModuleCapability::CntRuCapabilities::CntRuCapabilities(uint32_t id)
    : YangContainer("ru-capabilities", id) {}

CntModuleCapability::CntRuCapabilities::~CntRuCapabilities() {}

YangResult_E
CntModuleCapability::CntRuCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /module-capability/ru-capabilities/ru-capabilities
  // Description:
  // -----------------------------------------------------------------------------
  GrpRuCapabilities ruCapabilitiesInst(ITEM_RU_CAPABILITIES);
  ruCapabilitiesInst.initialise();
  addGroup(ruCapabilitiesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   rw-sub-band-info
// Description: config true leafrefs for use as constraints for config true
// leafs
// -----------------------------------------------------------------------------
CntModuleCapability::CntRwSubBandInfo::CntRwSubBandInfo(uint32_t id)
    : YangContainer("rw-sub-band-info", id) {}

CntModuleCapability::CntRwSubBandInfo::~CntRwSubBandInfo() {}

YangResult_E
CntModuleCapability::CntRwSubBandInfo::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /module-capability/rw-sub-band-info/rw-number-of-laa-scarriers
  // Description: This value indicates the number of LAA secondary carriers
  // supported at O-RU. Ref:
  // /module-capability/band-capabilities/sub-band-info/number-of-laa-scarriers
  // Units:
  // -----------------------------------------------------------------------------
  RefRwNumberOfLaaScarriers rwNumberOfLaaScarriersInst(
      ITEM_RW_NUMBER_OF_LAA_SCARRIERS);
  addReference(rwNumberOfLaaScarriersInst);

  // -----------------------------------------------------------------------------
  // Reference:   /module-capability/rw-sub-band-info/rw-self-configure
  // Description: This value indicates that the O-RU can manage the contention
  // window locally. Ref:
  // /module-capability/band-capabilities/sub-band-info/self-configure Units:
  // -----------------------------------------------------------------------------
  RefRwSelfConfigure rwSelfConfigureInst(ITEM_RW_SELF_CONFIGURE);
  addReference(rwSelfConfigureInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /module-capability/rw-sub-band-info/rw-number-of-laa-scarriers
// Description: This value indicates the number of LAA secondary carriers
// supported at O-RU.
// -----------------------------------------------------------------------------
CntModuleCapability::CntRwSubBandInfo::RefRwNumberOfLaaScarriers::
    RefRwNumberOfLaaScarriers(uint32_t id)
    : YangReference(
          "rw-number-of-laa-scarriers",
          id,
          "/module-capability/band-capabilities/sub-band-info/"
          "number-of-laa-scarriers") {}

CntModuleCapability::CntRwSubBandInfo::RefRwNumberOfLaaScarriers::
    ~RefRwNumberOfLaaScarriers() {}

// -----------------------------------------------------------------------------
// Reference:   /module-capability/rw-sub-band-info/rw-self-configure
// Description: This value indicates that the O-RU can manage the contention
// window locally.
// -----------------------------------------------------------------------------
CntModuleCapability::CntRwSubBandInfo::RefRwSelfConfigure::RefRwSelfConfigure(
    uint32_t id)
    : YangReference(
          "rw-self-configure",
          id,
          "/module-capability/band-capabilities/sub-band-info/self-configure") {
}

CntModuleCapability::CntRwSubBandInfo::RefRwSelfConfigure::
    ~RefRwSelfConfigure() {}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    compression-method-grouping
// Description: Grouping for compression method.
// -----------------------------------------------------------------------------
GrpCompressionMethodGrouping::GrpCompressionMethodGrouping(uint32_t id)
    : YangGroup("compression-method-grouping", id) {}

GrpCompressionMethodGrouping::~GrpCompressionMethodGrouping() {}

YangResult_E
GrpCompressionMethodGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /compression-method-grouping/compression-method
  // Description: Compression method which can be supported by the O-RU
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafCompressionMethod compressionMethodInst(ITEM_COMPRESSION_METHOD);
  addLeaf(compressionMethodInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /compression-method-grouping/compression-method
// Description: Compression method which can be supported by the O-RU
// -----------------------------------------------------------------------------
GrpCompressionMethodGrouping::LeafCompressionMethod::LeafCompressionMethod(
    uint32_t id)
    : YangLeaf("compression-method", id) {}

GrpCompressionMethodGrouping::LeafCompressionMethod::~LeafCompressionMethod() {}

// -----------------------------------------------------------------------------
// Grouping:    sub-band-max-min-ul-dl-frequency
// Description: Grouping for defining max and min supported frequency - dl and
// ul.
// -----------------------------------------------------------------------------
GrpSubBandMaxMinUlDlFrequency::GrpSubBandMaxMinUlDlFrequency(uint32_t id)
    : YangGroup("sub-band-max-min-ul-dl-frequency", id) {}

GrpSubBandMaxMinUlDlFrequency::~GrpSubBandMaxMinUlDlFrequency() {}

YangResult_E
GrpSubBandMaxMinUlDlFrequency::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-max-min-ul-dl-frequency/max-supported-frequency-dl
  // Description: This value indicates Maximum supported downlink frequency in
  // the
  //              LAA subband. Value unit is Hz.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaxSupportedFrequencyDl maxSupportedFrequencyDlInst(
      ITEM_MAX_SUPPORTED_FREQUENCY_DL);
  addLeaf(maxSupportedFrequencyDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-max-min-ul-dl-frequency/min-supported-frequency-dl
  // Description: This value indicates Minimum supported downlink frequency in
  // the
  //              LAA subband. Value unit is Hz.
  // Type:        uint64
  // Units:
  // -----------------------------------------------------------------------------
  LeafMinSupportedFrequencyDl minSupportedFrequencyDlInst(
      ITEM_MIN_SUPPORTED_FREQUENCY_DL);
  addLeaf(minSupportedFrequencyDlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-max-min-ul-dl-frequency/max-supported-frequency-dl
// Description: This value indicates Maximum supported downlink frequency in the
//              LAA subband. Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSubBandMaxMinUlDlFrequency::LeafMaxSupportedFrequencyDl::
    LeafMaxSupportedFrequencyDl(uint32_t id)
    : YangLeaf("max-supported-frequency-dl", id) {}

GrpSubBandMaxMinUlDlFrequency::LeafMaxSupportedFrequencyDl::
    ~LeafMaxSupportedFrequencyDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-max-min-ul-dl-frequency/min-supported-frequency-dl
// Description: This value indicates Minimum supported downlink frequency in the
//              LAA subband. Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSubBandMaxMinUlDlFrequency::LeafMinSupportedFrequencyDl::
    LeafMinSupportedFrequencyDl(uint32_t id)
    : YangLeaf("min-supported-frequency-dl", id) {}

GrpSubBandMaxMinUlDlFrequency::LeafMinSupportedFrequencyDl::
    ~LeafMinSupportedFrequencyDl() {}

// -----------------------------------------------------------------------------
// Grouping:    format-of-iq-sample
// Description: Indicates module capabilities about IQ samples
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::GrpFormatOfIqSample(uint32_t id)
    : YangGroup("format-of-iq-sample", id) {}

GrpFormatOfIqSample::~GrpFormatOfIqSample() {}

YangResult_E
GrpFormatOfIqSample::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /format-of-iq-sample/dynamic-compression-supported
  // Description: Informs if radio supports dynamic compression method
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafDynamicCompressionSupported dynamicCompressionSupportedInst(
      ITEM_DYNAMIC_COMPRESSION_SUPPORTED);
  addLeaf(dynamicCompressionSupportedInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /format-of-iq-sample/realtime-variable-bit-width-supported
  // Description: Informs if O-RU supports realtime variable bit with
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafRealtimeVariableBitWidthSupported realtimeVariableBitWidthSupportedInst(
      ITEM_REALTIME_VARIABLE_BIT_WIDTH_SUPPORTED);
  addLeaf(realtimeVariableBitWidthSupportedInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /format-of-iq-sample/variable-bit-width-per-channel-supported
  // Description: Informs if variable bit width per channel is supported or not
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafVariableBitWidthPerChannelSupported
      variableBitWidthPerChannelSupportedInst(
          ITEM_VARIABLE_BIT_WIDTH_PER_CHANNEL_SUPPORTED);
  addLeaf(variableBitWidthPerChannelSupportedInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /format-of-iq-sample/syminc-supported
  // Description: Informs if symbol number increment command in a C-Plane is
  //              supported or not
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafSymincSupported symincSupportedInst(ITEM_SYMINC_SUPPORTED);
  addLeaf(symincSupportedInst);

  // -----------------------------------------------------------------------------
  // List:        /format-of-iq-sample/compression-method-supported
  // Description: List of supported compression methods by O-RU
  // Array Key:
  // -----------------------------------------------------------------------------
  LstCompressionMethodSupported compressionMethodSupportedInst(
      ITEM_COMPRESSION_METHOD_SUPPORTED);
  compressionMethodSupportedInst.initialise();
  addList(compressionMethodSupportedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /format-of-iq-sample/dynamic-compression-supported
// Description: Informs if radio supports dynamic compression method
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::LeafDynamicCompressionSupported::
    LeafDynamicCompressionSupported(uint32_t id)
    : YangLeaf("dynamic-compression-supported", id) {}

GrpFormatOfIqSample::LeafDynamicCompressionSupported::
    ~LeafDynamicCompressionSupported() {}

// -----------------------------------------------------------------------------
// Leaf:        /format-of-iq-sample/realtime-variable-bit-width-supported
// Description: Informs if O-RU supports realtime variable bit with
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::LeafRealtimeVariableBitWidthSupported::
    LeafRealtimeVariableBitWidthSupported(uint32_t id)
    : YangLeaf("realtime-variable-bit-width-supported", id) {}

GrpFormatOfIqSample::LeafRealtimeVariableBitWidthSupported::
    ~LeafRealtimeVariableBitWidthSupported() {}

// -----------------------------------------------------------------------------
// Leaf:        /format-of-iq-sample/variable-bit-width-per-channel-supported
// Description: Informs if variable bit width per channel is supported or not
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::LeafVariableBitWidthPerChannelSupported::
    LeafVariableBitWidthPerChannelSupported(uint32_t id)
    : YangLeaf("variable-bit-width-per-channel-supported", id) {}

GrpFormatOfIqSample::LeafVariableBitWidthPerChannelSupported::
    ~LeafVariableBitWidthPerChannelSupported() {}

// -----------------------------------------------------------------------------
// Leaf:        /format-of-iq-sample/syminc-supported
// Description: Informs if symbol number increment command in a C-Plane is
//              supported or not
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::LeafSymincSupported::LeafSymincSupported(uint32_t id)
    : YangLeaf("syminc-supported", id) {}

GrpFormatOfIqSample::LeafSymincSupported::~LeafSymincSupported() {}

// -----------------------------------------------------------------------------
// List:        compression-method-supported
// Description: List of supported compression methods by O-RU
// -----------------------------------------------------------------------------
GrpFormatOfIqSample::LstCompressionMethodSupported::
    LstCompressionMethodSupported(uint32_t id)
    : YangList("compression-method-supported", id) {}

GrpFormatOfIqSample::LstCompressionMethodSupported::
    ~LstCompressionMethodSupported() {}

YangResult_E
GrpFormatOfIqSample::LstCompressionMethodSupported::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /format-of-iq-sample/compression-method-supported/cf:compression-details
  // Module: o-ran-compression-factors
  // Description:
  // -----------------------------------------------------------------------------
  ModuleORanCompressionFactors_NS::GrpCompressionDetails
      cfCompressionDetailsInst(ITEM_CF_COMPRESSION_DETAILS);
  cfCompressionDetailsInst.initialise();
  addGroup(cfCompressionDetailsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    scs-a-b
// Description: Grouping for scs-a and scs-b
// -----------------------------------------------------------------------------
GrpScsAB::GrpScsAB(uint32_t id) : YangGroup("scs-a-b", id) {}

GrpScsAB::~GrpScsAB() {}

YangResult_E
GrpScsAB::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /scs-a-b/scs-a
  // Description: Sub-carrier spacing configuration
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafScsA scsAInst(ITEM_SCS_A);
  addLeaf(scsAInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /scs-a-b/scs-b
  // Description: Sub-carrier spacing configuration
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafScsB scsBInst(ITEM_SCS_B);
  addLeaf(scsBInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /scs-a-b/scs-a
// Description: Sub-carrier spacing configuration
// -----------------------------------------------------------------------------
GrpScsAB::LeafScsA::LeafScsA(uint32_t id) : YangLeaf("scs-a", id) {}

GrpScsAB::LeafScsA::~LeafScsA() {}

// -----------------------------------------------------------------------------
// Leaf:        /scs-a-b/scs-b
// Description: Sub-carrier spacing configuration
// -----------------------------------------------------------------------------
GrpScsAB::LeafScsB::LeafScsB(uint32_t id) : YangLeaf("scs-b", id) {}

GrpScsAB::LeafScsB::~LeafScsB() {}

// -----------------------------------------------------------------------------
// Grouping:    ul-mixed-num-required-guard-rbs
// Description: Required number of guard resource blocks for the combination of
//              subcarrier spacing values for uplink
// -----------------------------------------------------------------------------
GrpUlMixedNumRequiredGuardRbs::GrpUlMixedNumRequiredGuardRbs(uint32_t id)
    : YangGroup("ul-mixed-num-required-guard-rbs", id) {}

GrpUlMixedNumRequiredGuardRbs::~GrpUlMixedNumRequiredGuardRbs() {}

YangResult_E
GrpUlMixedNumRequiredGuardRbs::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ul-mixed-num-required-guard-rbs/number-of-guard-rbs-ul
  // Description: This value indicates the required number of guard resource
  // blocks
  //              between the mixed numerologies, the RB using scs-a and the RB
  //              using scs-b. It's number is based on scs-a
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfGuardRbsUl numberOfGuardRbsUlInst(ITEM_NUMBER_OF_GUARD_RBS_UL);
  addLeaf(numberOfGuardRbsUlInst);

  // -----------------------------------------------------------------------------
  // Uses:        /ul-mixed-num-required-guard-rbs/scs-a-b
  // Description:
  // -----------------------------------------------------------------------------
  GrpScsAB scsABInst(ITEM_SCS_A_B);
  scsABInst.initialise();
  addGroup(scsABInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ul-mixed-num-required-guard-rbs/number-of-guard-rbs-ul
// Description: This value indicates the required number of guard resource
// blocks
//              between the mixed numerologies, the RB using scs-a and the RB
//              using scs-b. It's number is based on scs-a
// -----------------------------------------------------------------------------
GrpUlMixedNumRequiredGuardRbs::LeafNumberOfGuardRbsUl::LeafNumberOfGuardRbsUl(
    uint32_t id)
    : YangLeaf("number-of-guard-rbs-ul", id) {}

GrpUlMixedNumRequiredGuardRbs::LeafNumberOfGuardRbsUl::
    ~LeafNumberOfGuardRbsUl() {}

// -----------------------------------------------------------------------------
// Grouping:    dl-mixed-num-required-guard-rbs
// Description: Required number of guard resource blocks for the combination of
//              subcarrier spacing values for uplink
// -----------------------------------------------------------------------------
GrpDlMixedNumRequiredGuardRbs::GrpDlMixedNumRequiredGuardRbs(uint32_t id)
    : YangGroup("dl-mixed-num-required-guard-rbs", id) {}

GrpDlMixedNumRequiredGuardRbs::~GrpDlMixedNumRequiredGuardRbs() {}

YangResult_E
GrpDlMixedNumRequiredGuardRbs::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /dl-mixed-num-required-guard-rbs/number-of-guard-rbs-dl
  // Description: This value indicates the required number of guard resource
  // blocks
  //              between the mixed numerologies, the RB using scs-a and the RB
  //              using scs-b. It's number is based on scs-a
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfGuardRbsDl numberOfGuardRbsDlInst(ITEM_NUMBER_OF_GUARD_RBS_DL);
  addLeaf(numberOfGuardRbsDlInst);

  // -----------------------------------------------------------------------------
  // Uses:        /dl-mixed-num-required-guard-rbs/scs-a-b
  // Description:
  // -----------------------------------------------------------------------------
  GrpScsAB scsABInst(ITEM_SCS_A_B);
  scsABInst.initialise();
  addGroup(scsABInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dl-mixed-num-required-guard-rbs/number-of-guard-rbs-dl
// Description: This value indicates the required number of guard resource
// blocks
//              between the mixed numerologies, the RB using scs-a and the RB
//              using scs-b. It's number is based on scs-a
// -----------------------------------------------------------------------------
GrpDlMixedNumRequiredGuardRbs::LeafNumberOfGuardRbsDl::LeafNumberOfGuardRbsDl(
    uint32_t id)
    : YangLeaf("number-of-guard-rbs-dl", id) {}

GrpDlMixedNumRequiredGuardRbs::LeafNumberOfGuardRbsDl::
    ~LeafNumberOfGuardRbsDl() {}

// -----------------------------------------------------------------------------
// Grouping:    ru-capabilities
// Description: Structure representing set of capabilities.
// -----------------------------------------------------------------------------
GrpRuCapabilities::GrpRuCapabilities(uint32_t id)
    : YangGroup("ru-capabilities", id) {}

GrpRuCapabilities::~GrpRuCapabilities() {}

YangResult_E
GrpRuCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/ru-supported-category
  // Description: Informs about which category O-RU supports
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafRuSupportedCategory ruSupportedCategoryInst(ITEM_RU_SUPPORTED_CATEGORY);
  addLeaf(ruSupportedCategoryInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/number-of-ru-ports
  // Description: Assuming all endpoints support time-managed traffic AND
  // non-time-managed traffic (choice is as per configuration)
  //              - the number of O-RU ports is the product of number of spatial
  //              streams (leaf number-of-spatial-streams) and number of
  //              numerologies O-RU supports. For example, if the number of
  //              spatial streams is 4 then the number of O-RU ports is 8 when
  //              PUSCH and PRACH are processed in the different endpoints. In
  //              case there are specific endpoints that support
  //              non-time-managed traffic only
  //              - the number of O-RU ports calculated with above mentioned
  //              equation is extended by number of endpoints supporting only
  //              non-time-managed traffic.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfRuPorts numberOfRuPortsInst(ITEM_NUMBER_OF_RU_PORTS);
  addLeaf(numberOfRuPortsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/number-of-spatial-streams
  // Description: This value indicates the number of spatial streams supported
  // at O-RU for DL and UL.
  //              For DL, it is same as the number of antenna ports specified in
  //              3GPP TS38.214, Section 5.2 and 3GPP TS36.213, Section 5.2.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfSpatialStreams numberOfSpatialStreamsInst(
      ITEM_NUMBER_OF_SPATIAL_STREAMS);
  addLeaf(numberOfSpatialStreamsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/max-power-per-pa-antenna
  // Description: This value indicates Maximum Power per PA per antenna. Value
  // unit is dBm. Type:        dec64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxPowerPerPaAntenna maxPowerPerPaAntennaInst(
      ITEM_MAX_POWER_PER_PA_ANTENNA);
  addLeaf(maxPowerPerPaAntennaInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/min-power-per-pa-antenna
  // Description: This value indicates Minimum Power per PA per antenna. Value
  // unit is dBm. Type:        dec64 Units:
  // -----------------------------------------------------------------------------
  LeafMinPowerPerPaAntenna minPowerPerPaAntennaInst(
      ITEM_MIN_POWER_PER_PA_ANTENNA);
  addLeaf(minPowerPerPaAntennaInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/fronthaul-split-option
  // Description: This value indicates the Fronthaul Split Option, i.e., 2 or 7
  // in this release. Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafFronthaulSplitOption fronthaulSplitOptionInst(
      ITEM_FRONTHAUL_SPLIT_OPTION);
  addLeaf(fronthaulSplitOptionInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/energy-saving-by-transmission-blanks
  // Description: Parameter informs if unit supports energy saving by
  // transmission blanking Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafEnergySavingByTransmissionBlanks energySavingByTransmissionBlanksInst(
      ITEM_ENERGY_SAVING_BY_TRANSMISSION_BLANKS);
  addLeaf(energySavingByTransmissionBlanksInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /ru-capabilities/dynamic-transport-delay-management-supported
  // Description: Parameter informs if unit supports dynamic transport delay
  // management through eCPRI Msg 5 Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafDynamicTransportDelayManagementSupported
      dynamicTransportDelayManagementSupportedInst(
          ITEM_DYNAMIC_TRANSPORT_DELAY_MANAGEMENT_SUPPORTED);
  addLeaf(dynamicTransportDelayManagementSupportedInst);

  // -----------------------------------------------------------------------------
  // List:        /ru-capabilities/ul-mixed-num-required-guard-rbs
  // Description: List of required number of guard resource blocks
  //              for the combination of subcarrier spacing values for downlink
  // Array Key:
  // -----------------------------------------------------------------------------
  LstUlMixedNumRequiredGuardRbs ulMixedNumRequiredGuardRbsInst(
      ITEM_UL_MIXED_NUM_REQUIRED_GUARD_RBS);
  ulMixedNumRequiredGuardRbsInst.initialise();
  addList(ulMixedNumRequiredGuardRbsInst);

  // -----------------------------------------------------------------------------
  // List:        /ru-capabilities/dl-mixed-num-required-guard-rbs
  // Description: List of required number of guard resource blocks
  //              for the combination of subcarrier spacing values for uplink
  // Array Key:
  // -----------------------------------------------------------------------------
  LstDlMixedNumRequiredGuardRbs dlMixedNumRequiredGuardRbsInst(
      ITEM_DL_MIXED_NUM_REQUIRED_GUARD_RBS);
  dlMixedNumRequiredGuardRbsInst.initialise();
  addList(dlMixedNumRequiredGuardRbsInst);

  // -----------------------------------------------------------------------------
  // Container:   /ru-capabilities/format-of-iq-sample
  // Description: Indicates module capabilities about IQ samples
  // -----------------------------------------------------------------------------
  CntFormatOfIqSample formatOfIqSampleInst(ITEM_FORMAT_OF_IQ_SAMPLE);
  formatOfIqSampleInst.initialise();
  addContainer(formatOfIqSampleInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/ru-supported-category
// Description: Informs about which category O-RU supports
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafRuSupportedCategory::LeafRuSupportedCategory(uint32_t id)
    : YangLeaf("ru-supported-category", id) {}

GrpRuCapabilities::LeafRuSupportedCategory::~LeafRuSupportedCategory() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/number-of-ru-ports
// Description: Assuming all endpoints support time-managed traffic AND
// non-time-managed traffic (choice is as per configuration)
//              - the number of O-RU ports is the product of number of spatial
//              streams (leaf number-of-spatial-streams) and number of
//              numerologies O-RU supports. For example, if the number of
//              spatial streams is 4 then the number of O-RU ports is 8 when
//              PUSCH and PRACH are processed in the different endpoints. In
//              case there are specific endpoints that support non-time-managed
//              traffic only
//              - the number of O-RU ports calculated with above mentioned
//              equation is extended by number of endpoints supporting only
//              non-time-managed traffic.
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafNumberOfRuPorts::LeafNumberOfRuPorts(uint32_t id)
    : YangLeaf("number-of-ru-ports", id) {}

GrpRuCapabilities::LeafNumberOfRuPorts::~LeafNumberOfRuPorts() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/number-of-spatial-streams
// Description: This value indicates the number of spatial streams supported at
// O-RU for DL and UL.
//              For DL, it is same as the number of antenna ports specified in
//              3GPP TS38.214, Section 5.2 and 3GPP TS36.213, Section 5.2.
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafNumberOfSpatialStreams::LeafNumberOfSpatialStreams(
    uint32_t id)
    : YangLeaf("number-of-spatial-streams", id) {}

GrpRuCapabilities::LeafNumberOfSpatialStreams::~LeafNumberOfSpatialStreams() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/max-power-per-pa-antenna
// Description: This value indicates Maximum Power per PA per antenna. Value
// unit is dBm.
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafMaxPowerPerPaAntenna::LeafMaxPowerPerPaAntenna(
    uint32_t id)
    : YangLeaf("max-power-per-pa-antenna", id) {}

GrpRuCapabilities::LeafMaxPowerPerPaAntenna::~LeafMaxPowerPerPaAntenna() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/min-power-per-pa-antenna
// Description: This value indicates Minimum Power per PA per antenna. Value
// unit is dBm.
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafMinPowerPerPaAntenna::LeafMinPowerPerPaAntenna(
    uint32_t id)
    : YangLeaf("min-power-per-pa-antenna", id) {}

GrpRuCapabilities::LeafMinPowerPerPaAntenna::~LeafMinPowerPerPaAntenna() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/fronthaul-split-option
// Description: This value indicates the Fronthaul Split Option, i.e., 2 or 7 in
// this release.
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafFronthaulSplitOption::LeafFronthaulSplitOption(
    uint32_t id)
    : YangLeaf("fronthaul-split-option", id) {}

GrpRuCapabilities::LeafFronthaulSplitOption::~LeafFronthaulSplitOption() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/energy-saving-by-transmission-blanks
// Description: Parameter informs if unit supports energy saving by transmission
// blanking
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafEnergySavingByTransmissionBlanks::
    LeafEnergySavingByTransmissionBlanks(uint32_t id)
    : YangLeaf("energy-saving-by-transmission-blanks", id) {}

GrpRuCapabilities::LeafEnergySavingByTransmissionBlanks::
    ~LeafEnergySavingByTransmissionBlanks() {}

// -----------------------------------------------------------------------------
// Leaf:        /ru-capabilities/dynamic-transport-delay-management-supported
// Description: Parameter informs if unit supports dynamic transport delay
// management through eCPRI Msg 5
// -----------------------------------------------------------------------------
GrpRuCapabilities::LeafDynamicTransportDelayManagementSupported::
    LeafDynamicTransportDelayManagementSupported(uint32_t id)
    : YangLeaf("dynamic-transport-delay-management-supported", id) {}

GrpRuCapabilities::LeafDynamicTransportDelayManagementSupported::
    ~LeafDynamicTransportDelayManagementSupported() {}

// -----------------------------------------------------------------------------
// List:        ul-mixed-num-required-guard-rbs
// Description: List of required number of guard resource blocks
//              for the combination of subcarrier spacing values for downlink
// -----------------------------------------------------------------------------
GrpRuCapabilities::LstUlMixedNumRequiredGuardRbs::LstUlMixedNumRequiredGuardRbs(
    uint32_t id)
    : YangList("ul-mixed-num-required-guard-rbs", id) {}

GrpRuCapabilities::LstUlMixedNumRequiredGuardRbs::
    ~LstUlMixedNumRequiredGuardRbs() {}

YangResult_E
GrpRuCapabilities::LstUlMixedNumRequiredGuardRbs::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /ru-capabilities/ul-mixed-num-required-guard-rbs/ul-mixed-num-required-guard-rbs
  // Description:
  // -----------------------------------------------------------------------------
  GrpUlMixedNumRequiredGuardRbs ulMixedNumRequiredGuardRbsInst(
      ITEM_UL_MIXED_NUM_REQUIRED_GUARD_RBS);
  ulMixedNumRequiredGuardRbsInst.initialise();
  addGroup(ulMixedNumRequiredGuardRbsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        dl-mixed-num-required-guard-rbs
// Description: List of required number of guard resource blocks
//              for the combination of subcarrier spacing values for uplink
// -----------------------------------------------------------------------------
GrpRuCapabilities::LstDlMixedNumRequiredGuardRbs::LstDlMixedNumRequiredGuardRbs(
    uint32_t id)
    : YangList("dl-mixed-num-required-guard-rbs", id) {}

GrpRuCapabilities::LstDlMixedNumRequiredGuardRbs::
    ~LstDlMixedNumRequiredGuardRbs() {}

YangResult_E
GrpRuCapabilities::LstDlMixedNumRequiredGuardRbs::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /ru-capabilities/dl-mixed-num-required-guard-rbs/dl-mixed-num-required-guard-rbs
  // Description:
  // -----------------------------------------------------------------------------
  GrpDlMixedNumRequiredGuardRbs dlMixedNumRequiredGuardRbsInst(
      ITEM_DL_MIXED_NUM_REQUIRED_GUARD_RBS);
  dlMixedNumRequiredGuardRbsInst.initialise();
  addGroup(dlMixedNumRequiredGuardRbsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   format-of-iq-sample
// Description: Indicates module capabilities about IQ samples
// -----------------------------------------------------------------------------
GrpRuCapabilities::CntFormatOfIqSample::CntFormatOfIqSample(uint32_t id)
    : YangContainer("format-of-iq-sample", id) {}

GrpRuCapabilities::CntFormatOfIqSample::~CntFormatOfIqSample() {}

YangResult_E
GrpRuCapabilities::CntFormatOfIqSample::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /ru-capabilities/format-of-iq-sample/format-of-iq-sample
  // Description:
  // -----------------------------------------------------------------------------
  GrpFormatOfIqSample formatOfIqSampleInst(ITEM_FORMAT_OF_IQ_SAMPLE);
  formatOfIqSampleInst.initialise();
  addGroup(formatOfIqSampleInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    sub-band-info
// Description: container for collection of leafs for LAA subband 46
// -----------------------------------------------------------------------------
GrpSubBandInfo::GrpSubBandInfo(uint32_t id) : YangGroup("sub-band-info", id) {}

GrpSubBandInfo::~GrpSubBandInfo() {}

YangResult_E
GrpSubBandInfo::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-info/number-of-laa-scarriers
  // Description: This value indicates the number of LAA secondary carriers
  // supported at O-RU. Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafNumberOfLaaScarriers numberOfLaaScarriersInst(
      ITEM_NUMBER_OF_LAA_SCARRIERS);
  addLeaf(numberOfLaaScarriersInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-info/maximum-laa-buffer-size
  // Description: Maximum O-RU buffer size in Kilobytes (KB) per CC. This
  // parameter is
  //              needed at the O-DU to know how much data can be sent in
  //              advance and stored at the O-RU to address the LBT
  //              uncertainity.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaximumLaaBufferSize maximumLaaBufferSizeInst(
      ITEM_MAXIMUM_LAA_BUFFER_SIZE);
  addLeaf(maximumLaaBufferSizeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-info/maximum-processing-time
  // Description: Maximum O-RU Processing time in microseconds at the O-RU to
  // handle the
  //              received/transmitted packets from/to the O-DU. This parameter
  //              is needed at the O-DU to determine the time where it needs to
  //              send the data to the O-RU.
  // Type:        uint16
  // Units:       microseconds
  // -----------------------------------------------------------------------------
  LeafMaximumProcessingTime maximumProcessingTimeInst(
      ITEM_MAXIMUM_PROCESSING_TIME);
  addLeaf(maximumProcessingTimeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-info/self-configure
  // Description: This value indicates that the O-RU can manage the contention
  // window locally. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafSelfConfigure selfConfigureInst(ITEM_SELF_CONFIGURE);
  addLeaf(selfConfigureInst);

  // -----------------------------------------------------------------------------
  // List:        /sub-band-info/sub-band-frequency-ranges
  // Description: frequency information on a per sub-band basis
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSubBandFrequencyRanges subBandFrequencyRangesInst(
      ITEM_SUB_BAND_FREQUENCY_RANGES);
  subBandFrequencyRangesInst.initialise();
  addList(subBandFrequencyRangesInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-info/number-of-laa-scarriers
// Description: This value indicates the number of LAA secondary carriers
// supported at O-RU.
// -----------------------------------------------------------------------------
GrpSubBandInfo::LeafNumberOfLaaScarriers::LeafNumberOfLaaScarriers(uint32_t id)
    : YangLeaf("number-of-laa-scarriers", id) {}

GrpSubBandInfo::LeafNumberOfLaaScarriers::~LeafNumberOfLaaScarriers() {}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-info/maximum-laa-buffer-size
// Description: Maximum O-RU buffer size in Kilobytes (KB) per CC. This
// parameter is
//              needed at the O-DU to know how much data can be sent in advance
//              and stored at the O-RU to address the LBT uncertainity.
// -----------------------------------------------------------------------------
GrpSubBandInfo::LeafMaximumLaaBufferSize::LeafMaximumLaaBufferSize(uint32_t id)
    : YangLeaf("maximum-laa-buffer-size", id) {}

GrpSubBandInfo::LeafMaximumLaaBufferSize::~LeafMaximumLaaBufferSize() {}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-info/maximum-processing-time
// Description: Maximum O-RU Processing time in microseconds at the O-RU to
// handle the
//              received/transmitted packets from/to the O-DU. This parameter is
//              needed at the O-DU to determine the time where it needs to send
//              the data to the O-RU.
// -----------------------------------------------------------------------------
GrpSubBandInfo::LeafMaximumProcessingTime::LeafMaximumProcessingTime(
    uint32_t id)
    : YangLeaf("maximum-processing-time", id) {}

GrpSubBandInfo::LeafMaximumProcessingTime::~LeafMaximumProcessingTime() {}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-info/self-configure
// Description: This value indicates that the O-RU can manage the contention
// window locally.
// -----------------------------------------------------------------------------
GrpSubBandInfo::LeafSelfConfigure::LeafSelfConfigure(uint32_t id)
    : YangLeaf("self-configure", id) {}

GrpSubBandInfo::LeafSelfConfigure::~LeafSelfConfigure() {}

// -----------------------------------------------------------------------------
// List:        sub-band-frequency-ranges
// Description: frequency information on a per sub-band basis
// -----------------------------------------------------------------------------
GrpSubBandInfo::LstSubBandFrequencyRanges::LstSubBandFrequencyRanges(
    uint32_t id)
    : YangList("sub-band-frequency-ranges", id) {}

GrpSubBandInfo::LstSubBandFrequencyRanges::~LstSubBandFrequencyRanges() {}

YangResult_E
GrpSubBandInfo::LstSubBandFrequencyRanges::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /sub-band-info/sub-band-frequency-ranges/sub-band
  // Description: Sub band when band 46
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafSubBand subBandInst(ITEM_SUB_BAND);
  addLeaf(subBandInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /sub-band-info/sub-band-frequency-ranges/sub-band-max-min-ul-dl-frequency
  // Description:
  // -----------------------------------------------------------------------------
  GrpSubBandMaxMinUlDlFrequency subBandMaxMinUlDlFrequencyInst(
      ITEM_SUB_BAND_MAX_MIN_UL_DL_FREQUENCY);
  subBandMaxMinUlDlFrequencyInst.initialise();
  addGroup(subBandMaxMinUlDlFrequencyInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /sub-band-info/sub-band-frequency-ranges/sub-band
// Description: Sub band when band 46
// -----------------------------------------------------------------------------
GrpSubBandInfo::LstSubBandFrequencyRanges::LeafSubBand::LeafSubBand(uint32_t id)
    : YangLeaf("sub-band", id) {}

GrpSubBandInfo::LstSubBandFrequencyRanges::LeafSubBand::~LeafSubBand() {}

// -----------------------------------------------------------------------------
// Grouping:    support-for-dl
// Description: Grouping for DL specific parameters
// -----------------------------------------------------------------------------
GrpSupportForDl::GrpSupportForDl(uint32_t id)
    : YangGroup("support-for-dl", id) {}

GrpSupportForDl::~GrpSupportForDl() {}

YangResult_E
GrpSupportForDl::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/max-supported-frequency-dl
  // Description: This value indicates Maximum supported downlink frequency.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxSupportedFrequencyDl maxSupportedFrequencyDlInst(
      ITEM_MAX_SUPPORTED_FREQUENCY_DL);
  addLeaf(maxSupportedFrequencyDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/min-supported-frequency-dl
  // Description: This value indicates Minimum supported downlink frequency.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMinSupportedFrequencyDl minSupportedFrequencyDlInst(
      ITEM_MIN_SUPPORTED_FREQUENCY_DL);
  addLeaf(minSupportedFrequencyDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/max-supported-bandwidth-dl
  // Description: This value indicates Maximum total downlink bandwidth in
  // module. Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxSupportedBandwidthDl maxSupportedBandwidthDlInst(
      ITEM_MAX_SUPPORTED_BANDWIDTH_DL);
  addLeaf(maxSupportedBandwidthDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/max-num-carriers-dl
  // Description: This value indicates Maximum number of downlink carriers in
  // module. Type:        uint32 Units:
  // -----------------------------------------------------------------------------
  LeafMaxNumCarriersDl maxNumCarriersDlInst(ITEM_MAX_NUM_CARRIERS_DL);
  addLeaf(maxNumCarriersDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/max-carrier-bandwidth-dl
  // Description: This value indicates Maximum bandwidth per downlink carrier.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxCarrierBandwidthDl maxCarrierBandwidthDlInst(
      ITEM_MAX_CARRIER_BANDWIDTH_DL);
  addLeaf(maxCarrierBandwidthDlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-dl/min-carrier-bandwidth-dl
  // Description: This value indicates Minimum bandwidth per downlink carrier.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMinCarrierBandwidthDl minCarrierBandwidthDlInst(
      ITEM_MIN_CARRIER_BANDWIDTH_DL);
  addLeaf(minCarrierBandwidthDlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/max-supported-frequency-dl
// Description: This value indicates Maximum supported downlink frequency. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMaxSupportedFrequencyDl::LeafMaxSupportedFrequencyDl(
    uint32_t id)
    : YangLeaf("max-supported-frequency-dl", id) {}

GrpSupportForDl::LeafMaxSupportedFrequencyDl::~LeafMaxSupportedFrequencyDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/min-supported-frequency-dl
// Description: This value indicates Minimum supported downlink frequency. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMinSupportedFrequencyDl::LeafMinSupportedFrequencyDl(
    uint32_t id)
    : YangLeaf("min-supported-frequency-dl", id) {}

GrpSupportForDl::LeafMinSupportedFrequencyDl::~LeafMinSupportedFrequencyDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/max-supported-bandwidth-dl
// Description: This value indicates Maximum total downlink bandwidth in module.
// Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMaxSupportedBandwidthDl::LeafMaxSupportedBandwidthDl(
    uint32_t id)
    : YangLeaf("max-supported-bandwidth-dl", id) {}

GrpSupportForDl::LeafMaxSupportedBandwidthDl::~LeafMaxSupportedBandwidthDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/max-num-carriers-dl
// Description: This value indicates Maximum number of downlink carriers in
// module.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMaxNumCarriersDl::LeafMaxNumCarriersDl(uint32_t id)
    : YangLeaf("max-num-carriers-dl", id) {}

GrpSupportForDl::LeafMaxNumCarriersDl::~LeafMaxNumCarriersDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/max-carrier-bandwidth-dl
// Description: This value indicates Maximum bandwidth per downlink carrier.
// Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMaxCarrierBandwidthDl::LeafMaxCarrierBandwidthDl(
    uint32_t id)
    : YangLeaf("max-carrier-bandwidth-dl", id) {}

GrpSupportForDl::LeafMaxCarrierBandwidthDl::~LeafMaxCarrierBandwidthDl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-dl/min-carrier-bandwidth-dl
// Description: This value indicates Minimum bandwidth per downlink carrier.
// Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForDl::LeafMinCarrierBandwidthDl::LeafMinCarrierBandwidthDl(
    uint32_t id)
    : YangLeaf("min-carrier-bandwidth-dl", id) {}

GrpSupportForDl::LeafMinCarrierBandwidthDl::~LeafMinCarrierBandwidthDl() {}

// -----------------------------------------------------------------------------
// Grouping:    support-for-ul
// Description: Grouping for UL specific parameters
// -----------------------------------------------------------------------------
GrpSupportForUl::GrpSupportForUl(uint32_t id)
    : YangGroup("support-for-ul", id) {}

GrpSupportForUl::~GrpSupportForUl() {}

YangResult_E
GrpSupportForUl::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/max-supported-frequency-ul
  // Description: This value indicates Maximum supported uplink frequency. Value
  // unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxSupportedFrequencyUl maxSupportedFrequencyUlInst(
      ITEM_MAX_SUPPORTED_FREQUENCY_UL);
  addLeaf(maxSupportedFrequencyUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/min-supported-frequency-ul
  // Description: This value indicates Minimum supported uplink frequency. Value
  // unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMinSupportedFrequencyUl minSupportedFrequencyUlInst(
      ITEM_MIN_SUPPORTED_FREQUENCY_UL);
  addLeaf(minSupportedFrequencyUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/max-supported-bandwidth-ul
  // Description: This value indicates Maximum total uplink bandwidth in module.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxSupportedBandwidthUl maxSupportedBandwidthUlInst(
      ITEM_MAX_SUPPORTED_BANDWIDTH_UL);
  addLeaf(maxSupportedBandwidthUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/max-num-carriers-ul
  // Description: This value indicates Maximum number of uplink carriers in
  // module. Type:        uint32 Units:
  // -----------------------------------------------------------------------------
  LeafMaxNumCarriersUl maxNumCarriersUlInst(ITEM_MAX_NUM_CARRIERS_UL);
  addLeaf(maxNumCarriersUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/max-carrier-bandwidth-ul
  // Description: This value indicates Maximum bandwidth per uplink carrier.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxCarrierBandwidthUl maxCarrierBandwidthUlInst(
      ITEM_MAX_CARRIER_BANDWIDTH_UL);
  addLeaf(maxCarrierBandwidthUlInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /support-for-ul/min-carrier-bandwidth-ul
  // Description: This value indicates Minimum bandwidth per uplink carrier.
  // Value unit is Hz. Type:        uint64 Units:
  // -----------------------------------------------------------------------------
  LeafMinCarrierBandwidthUl minCarrierBandwidthUlInst(
      ITEM_MIN_CARRIER_BANDWIDTH_UL);
  addLeaf(minCarrierBandwidthUlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/max-supported-frequency-ul
// Description: This value indicates Maximum supported uplink frequency. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMaxSupportedFrequencyUl::LeafMaxSupportedFrequencyUl(
    uint32_t id)
    : YangLeaf("max-supported-frequency-ul", id) {}

GrpSupportForUl::LeafMaxSupportedFrequencyUl::~LeafMaxSupportedFrequencyUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/min-supported-frequency-ul
// Description: This value indicates Minimum supported uplink frequency. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMinSupportedFrequencyUl::LeafMinSupportedFrequencyUl(
    uint32_t id)
    : YangLeaf("min-supported-frequency-ul", id) {}

GrpSupportForUl::LeafMinSupportedFrequencyUl::~LeafMinSupportedFrequencyUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/max-supported-bandwidth-ul
// Description: This value indicates Maximum total uplink bandwidth in module.
// Value unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMaxSupportedBandwidthUl::LeafMaxSupportedBandwidthUl(
    uint32_t id)
    : YangLeaf("max-supported-bandwidth-ul", id) {}

GrpSupportForUl::LeafMaxSupportedBandwidthUl::~LeafMaxSupportedBandwidthUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/max-num-carriers-ul
// Description: This value indicates Maximum number of uplink carriers in
// module.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMaxNumCarriersUl::LeafMaxNumCarriersUl(uint32_t id)
    : YangLeaf("max-num-carriers-ul", id) {}

GrpSupportForUl::LeafMaxNumCarriersUl::~LeafMaxNumCarriersUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/max-carrier-bandwidth-ul
// Description: This value indicates Maximum bandwidth per uplink carrier. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMaxCarrierBandwidthUl::LeafMaxCarrierBandwidthUl(
    uint32_t id)
    : YangLeaf("max-carrier-bandwidth-ul", id) {}

GrpSupportForUl::LeafMaxCarrierBandwidthUl::~LeafMaxCarrierBandwidthUl() {}

// -----------------------------------------------------------------------------
// Leaf:        /support-for-ul/min-carrier-bandwidth-ul
// Description: This value indicates Minimum bandwidth per uplink carrier. Value
// unit is Hz.
// -----------------------------------------------------------------------------
GrpSupportForUl::LeafMinCarrierBandwidthUl::LeafMinCarrierBandwidthUl(
    uint32_t id)
    : YangLeaf("min-carrier-bandwidth-ul", id) {}

GrpSupportForUl::LeafMinCarrierBandwidthUl::~LeafMinCarrierBandwidthUl() {}

// -----------------------------------------------------------------------------
// Grouping:    band-capabilities
// Description: Capabilities that are needed to be defined per each band
// -----------------------------------------------------------------------------
GrpBandCapabilities::GrpBandCapabilities(uint32_t id)
    : YangGroup("band-capabilities", id) {}

GrpBandCapabilities::~GrpBandCapabilities() {}

YangResult_E
GrpBandCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/band-number
  // Description: Band number
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafBandNumber bandNumberInst(ITEM_BAND_NUMBER);
  addLeaf(bandNumberInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/max-num-component-carriers
  // Description: maximum number of component carriers supported by the O-RU
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaxNumComponentCarriers maxNumComponentCarriersInst(
      ITEM_MAX_NUM_COMPONENT_CARRIERS);
  addLeaf(maxNumComponentCarriersInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/max-num-bands
  // Description: maximum number of bands supported by the O-RU
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaxNumBands maxNumBandsInst(ITEM_MAX_NUM_BANDS);
  addLeaf(maxNumBandsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/max-num-sectors
  // Description: maximum number of sectors supported by the O-RU
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafMaxNumSectors maxNumSectorsInst(ITEM_MAX_NUM_SECTORS);
  addLeaf(maxNumSectorsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/max-power-per-antenna
  // Description: This value indicates Maximum Power per band per antenna. Value
  // unit is dBm. Type:        dec64 Units:
  // -----------------------------------------------------------------------------
  LeafMaxPowerPerAntenna maxPowerPerAntennaInst(ITEM_MAX_POWER_PER_ANTENNA);
  addLeaf(maxPowerPerAntennaInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/min-power-per-antenna
  // Description: This value indicates Minimum Power per band per antenna. Value
  // unit is dBm. Type:        dec64 Units:
  // -----------------------------------------------------------------------------
  LeafMinPowerPerAntenna minPowerPerAntennaInst(ITEM_MIN_POWER_PER_ANTENNA);
  addLeaf(minPowerPerAntennaInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/codebook-configuration_ng
  // Description: This parameter informs the precoder codebook_ng that are used
  // for precoding Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafCodebookConfigurationNg codebookConfigurationNgInst(
      ITEM_CODEBOOK_CONFIGURATION_NG);
  addLeaf(codebookConfigurationNgInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/codebook-configuration_n1
  // Description: This parameter informs the precoder codebook_n1 that are used
  // for precoding Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafCodebookConfigurationN1 codebookConfigurationN1Inst(
      ITEM_CODEBOOK_CONFIGURATION_N1);
  addLeaf(codebookConfigurationN1Inst);

  // -----------------------------------------------------------------------------
  // Leaf:        /band-capabilities/codebook-configuration_n2
  // Description: This parameter informs the precoder codebook_n2 that are used
  // for precoding Type:        uint8 Units:
  // -----------------------------------------------------------------------------
  LeafCodebookConfigurationN2 codebookConfigurationN2Inst(
      ITEM_CODEBOOK_CONFIGURATION_N2);
  addLeaf(codebookConfigurationN2Inst);

  // -----------------------------------------------------------------------------
  // Container:   /band-capabilities/sub-band-info
  // Description: container for collection of leafs for LAA subband 46
  // -----------------------------------------------------------------------------
  CntSubBandInfo subBandInfoInst(ITEM_SUB_BAND_INFO);
  subBandInfoInst.initialise();
  addContainer(subBandInfoInst);

  // -----------------------------------------------------------------------------
  // Uses:        /band-capabilities/support-for-dl
  // Description:
  // -----------------------------------------------------------------------------
  GrpSupportForDl supportForDlInst(ITEM_SUPPORT_FOR_DL);
  supportForDlInst.initialise();
  addGroup(supportForDlInst);

  // -----------------------------------------------------------------------------
  // Uses:        /band-capabilities/support-for-ul
  // Description:
  // -----------------------------------------------------------------------------
  GrpSupportForUl supportForUlInst(ITEM_SUPPORT_FOR_UL);
  supportForUlInst.initialise();
  addGroup(supportForUlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/band-number
// Description: Band number
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafBandNumber::LeafBandNumber(uint32_t id)
    : YangLeaf("band-number", id) {}

GrpBandCapabilities::LeafBandNumber::~LeafBandNumber() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/max-num-component-carriers
// Description: maximum number of component carriers supported by the O-RU
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafMaxNumComponentCarriers::LeafMaxNumComponentCarriers(
    uint32_t id)
    : YangLeaf("max-num-component-carriers", id) {}

GrpBandCapabilities::LeafMaxNumComponentCarriers::
    ~LeafMaxNumComponentCarriers() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/max-num-bands
// Description: maximum number of bands supported by the O-RU
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafMaxNumBands::LeafMaxNumBands(uint32_t id)
    : YangLeaf("max-num-bands", id) {}

GrpBandCapabilities::LeafMaxNumBands::~LeafMaxNumBands() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/max-num-sectors
// Description: maximum number of sectors supported by the O-RU
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafMaxNumSectors::LeafMaxNumSectors(uint32_t id)
    : YangLeaf("max-num-sectors", id) {}

GrpBandCapabilities::LeafMaxNumSectors::~LeafMaxNumSectors() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/max-power-per-antenna
// Description: This value indicates Maximum Power per band per antenna. Value
// unit is dBm.
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafMaxPowerPerAntenna::LeafMaxPowerPerAntenna(uint32_t id)
    : YangLeaf("max-power-per-antenna", id) {}

GrpBandCapabilities::LeafMaxPowerPerAntenna::~LeafMaxPowerPerAntenna() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/min-power-per-antenna
// Description: This value indicates Minimum Power per band per antenna. Value
// unit is dBm.
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafMinPowerPerAntenna::LeafMinPowerPerAntenna(uint32_t id)
    : YangLeaf("min-power-per-antenna", id) {}

GrpBandCapabilities::LeafMinPowerPerAntenna::~LeafMinPowerPerAntenna() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/codebook-configuration_ng
// Description: This parameter informs the precoder codebook_ng that are used
// for precoding
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafCodebookConfigurationNg::LeafCodebookConfigurationNg(
    uint32_t id)
    : YangLeaf("codebook-configuration_ng", id) {}

GrpBandCapabilities::LeafCodebookConfigurationNg::
    ~LeafCodebookConfigurationNg() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/codebook-configuration_n1
// Description: This parameter informs the precoder codebook_n1 that are used
// for precoding
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafCodebookConfigurationN1::LeafCodebookConfigurationN1(
    uint32_t id)
    : YangLeaf("codebook-configuration_n1", id) {}

GrpBandCapabilities::LeafCodebookConfigurationN1::
    ~LeafCodebookConfigurationN1() {}

// -----------------------------------------------------------------------------
// Leaf:        /band-capabilities/codebook-configuration_n2
// Description: This parameter informs the precoder codebook_n2 that are used
// for precoding
// -----------------------------------------------------------------------------
GrpBandCapabilities::LeafCodebookConfigurationN2::LeafCodebookConfigurationN2(
    uint32_t id)
    : YangLeaf("codebook-configuration_n2", id) {}

GrpBandCapabilities::LeafCodebookConfigurationN2::
    ~LeafCodebookConfigurationN2() {}

// -----------------------------------------------------------------------------
// Container:   sub-band-info
// Description: container for collection of leafs for LAA subband 46
// -----------------------------------------------------------------------------
GrpBandCapabilities::CntSubBandInfo::CntSubBandInfo(uint32_t id)
    : YangContainer("sub-band-info", id) {}

GrpBandCapabilities::CntSubBandInfo::~CntSubBandInfo() {}

YangResult_E
GrpBandCapabilities::CntSubBandInfo::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /band-capabilities/sub-band-info/sub-band-info
  // Description:
  // -----------------------------------------------------------------------------
  GrpSubBandInfo subBandInfoInst(ITEM_SUB_BAND_INFO);
  subBandInfoInst.initialise();
  addGroup(subBandInfoInst);

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
// Module:      o-ran-module-cap
// Description: This module defines the module capabilities for
//              the O-RAN Radio Unit.
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
ModuleORanModuleCap::ModuleORanModuleCap(uint32_t id)
    : YangModule(
          "o-ran-module-cap",
          "o-ran-module-cap.yang",
          "o-ran-module-cap",
          "urn:o-ran:module-cap:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: Indicates that the Radio Unit supports LAA.
  // -----------------------------------------------------------------------------
  FeatureLAA LAAInst(ITEM_LAA);
  addFeature(LAAInst);

  // -----------------------------------------------------------------------------
  // Feature
  // Description: This leaf is used to indicate whether the O-RU supports O-RAN
  // Radio Transport Fragmentation
  // -----------------------------------------------------------------------------
  FeatureTRANSPORTFRAGMENTATION TRANSPORTFRAGMENTATIONInst(
      ITEM_TRANSPORT_FRAGMENTATION);
  addFeature(TRANSPORTFRAGMENTATIONInst);

  // -----------------------------------------------------------------------------
  // Container:   /module-capability
  // Description: module capability object responsible for providing module
  // capability.
  // -----------------------------------------------------------------------------
  CntModuleCapability moduleCapabilityInst(ITEM_MODULE_CAPABILITY);
  moduleCapabilityInst.initialise();
  addContainer(moduleCapabilityInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanModuleCap::~ModuleORanModuleCap() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanModuleCap::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanModuleCap>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanModuleCap::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
