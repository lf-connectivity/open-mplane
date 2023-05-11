#ifndef _MODULE_O_RAN_MODULE_CAP_H_
#define _MODULE_O_RAN_MODULE_CAP_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanModuleCap.h
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

// Module:   o-ran-compression-factors
// Revision:
// Notes:
#include "YangModuleORanCompressionFactors.h"


namespace Mplane {

namespace ModuleORanModuleCap_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// Scs configuration type definition
enum class ScsConfigType_E : uint32_t {
  KHZ_15, // 15kHz sub carrier spacing
  KHZ_30, // 30kHz sub carrier spacing
  KHZ_60, // 60kHz sub carrier spacing
  KHZ_120, // 120kHz sub carrier spacing
  KHZ_240, // 240kHz sub carrier spacing
  KHZ_1_25, // 1,25kHz sub carrier spacing
  KHZ_3_75, // 3.75kHz sub carrier spacing
  KHZ_5, // 5kHz sub carrier spacing
  KHZ_7_5, // 7.5kHz sub carrier spacing

  Num_ScsConfigType_E
};

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: Indicates that the Radio Unit supports LAA.
// -----------------------------------------------------------------------------
class FeatureLAA : public YangFeature
{
public:
 FeatureLAA(uint32_t id);
 ~FeatureLAA();

}; // FeatureLAA

// -----------------------------------------------------------------------------
// Feature
// Description: This leaf is used to indicate whether the O-RU supports O-RAN Radio Transport Fragmentation
// -----------------------------------------------------------------------------
class FeatureTRANSPORTFRAGMENTATION : public YangFeature
{
public:
 FeatureTRANSPORTFRAGMENTATION(uint32_t id);
 ~FeatureTRANSPORTFRAGMENTATION();

}; // FeatureTRANSPORTFRAGMENTATION


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
// Container:   /module-capability
// Description: module capability object responsible for providing module capability.
// -----------------------------------------------------------------------------
class CntModuleCapability : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_RU_CAPABILITIES, // CntRuCapabilities
   ITEM_RW_SUB_BAND_INFO, // CntRwSubBandInfo
   ITEM_BAND_CAPABILITIES, // LstBandCapabilities
 };

 CntModuleCapability(uint32_t id);
 ~CntModuleCapability();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /module-capability/ru-capabilities
 // Description: Structure representing set of capabilities.
 // -----------------------------------------------------------------------------
 class CntRuCapabilities : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_RU_CAPABILITIES, // Use GrpRuCapabilities
   };

   CntRuCapabilities(uint32_t id);
   ~CntRuCapabilities();

   YangResult_E initialise(void);

 }; // CntRuCapabilities

 // -----------------------------------------------------------------------------
 // Container:   /module-capability/rw-sub-band-info
 // Description: config true leafrefs for use as constraints for config true
 // leafs
 // -----------------------------------------------------------------------------
 class CntRwSubBandInfo : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_RW_NUMBER_OF_LAA_SCARRIERS, // RefRwNumberOfLaaScarriers
     ITEM_RW_SELF_CONFIGURE, // RefRwSelfConfigure
   };

   CntRwSubBandInfo(uint32_t id);
   ~CntRwSubBandInfo();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference: /module-capability/rw-sub-band-info/rw-number-of-laa-scarriers
   // Description: This value indicates the number of LAA secondary carriers
   // supported at O-RU.
   // -----------------------------------------------------------------------------
   class RefRwNumberOfLaaScarriers : public YangReference {
    public:
     RefRwNumberOfLaaScarriers(uint32_t id);
     ~RefRwNumberOfLaaScarriers();

   }; // RefRwNumberOfLaaScarriers

   // -----------------------------------------------------------------------------
   // Reference:   /module-capability/rw-sub-band-info/rw-self-configure
   // Description: This value indicates that the O-RU can manage the contention
   // window locally.
   // -----------------------------------------------------------------------------
   class RefRwSelfConfigure : public YangReference {
    public:
     RefRwSelfConfigure(uint32_t id);
     ~RefRwSelfConfigure();

   }; // RefRwSelfConfigure

 }; // CntRwSubBandInfo

 // -----------------------------------------------------------------------------
 // List:        /module-capability/band-capabilities
 // Description: Capabilities that are needed to be defined per each band
 // -----------------------------------------------------------------------------
 class LstBandCapabilities : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_BAND_CAPABILITIES, // Use GrpBandCapabilities
   };

   LstBandCapabilities(uint32_t id);
   ~LstBandCapabilities();

   YangResult_E initialise(void);

 }; // LstBandCapabilities

}; // CntModuleCapability


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /compression-method-grouping
// Description: Grouping for compression method.
// -----------------------------------------------------------------------------
class GrpCompressionMethodGrouping : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_COMPRESSION_METHOD, // LeafCompressionMethod
 };

 GrpCompressionMethodGrouping(uint32_t id);
 ~GrpCompressionMethodGrouping();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /compression-method-grouping/compression-method
 // Description: Compression method which can be supported by the O-RU
 // -----------------------------------------------------------------------------
 class LeafCompressionMethod : public YangLeaf {
  public:
   // Compression method which can be supported by the O-RU
   enum class CompressionMethod_E : uint32_t {
     BLOCK_FLOATING_POINT, // Block floating point compression and
                           // decompression will be used
     BLOCK_SCALING, // Block scaling compression and decompresion will be
                    // used
     U_LAW, // u-Law compression and decompresion method will be used
     BEAMSPACE, // Beamspace compression and decompression will be used
     MODULATION, // Modulation compression and decompression will be used

     Num_CompressionMethod_E
   };

   LeafCompressionMethod(uint32_t id);
   ~LeafCompressionMethod();

 }; // LeafCompressionMethod

}; // GrpCompressionMethodGrouping

// -----------------------------------------------------------------------------
// Grouping:    /sub-band-max-min-ul-dl-frequency
// Description: Grouping for defining max and min supported frequency - dl and ul.
// -----------------------------------------------------------------------------
class GrpSubBandMaxMinUlDlFrequency : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_SUPPORTED_FREQUENCY_DL, // LeafMaxSupportedFrequencyDl
   ITEM_MIN_SUPPORTED_FREQUENCY_DL, // LeafMinSupportedFrequencyDl
 };

 GrpSubBandMaxMinUlDlFrequency(uint32_t id);
 ~GrpSubBandMaxMinUlDlFrequency();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-max-min-ul-dl-frequency/max-supported-frequency-dl
 // Description: This value indicates Maximum supported downlink frequency in
 // the
 //              LAA subband. Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxSupportedFrequencyDl : public YangLeaf {
  public:
   LeafMaxSupportedFrequencyDl(uint32_t id);
   ~LeafMaxSupportedFrequencyDl();

 }; // LeafMaxSupportedFrequencyDl

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-max-min-ul-dl-frequency/min-supported-frequency-dl
 // Description: This value indicates Minimum supported downlink frequency in
 // the
 //              LAA subband. Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMinSupportedFrequencyDl : public YangLeaf {
  public:
   LeafMinSupportedFrequencyDl(uint32_t id);
   ~LeafMinSupportedFrequencyDl();

 }; // LeafMinSupportedFrequencyDl

}; // GrpSubBandMaxMinUlDlFrequency

// -----------------------------------------------------------------------------
// Grouping:    /format-of-iq-sample
// Description: Indicates module capabilities about IQ samples
// -----------------------------------------------------------------------------
class GrpFormatOfIqSample : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_DYNAMIC_COMPRESSION_SUPPORTED, // LeafDynamicCompressionSupported
   ITEM_REALTIME_VARIABLE_BIT_WIDTH_SUPPORTED, // LeafRealtimeVariableBitWidthSupported
   ITEM_VARIABLE_BIT_WIDTH_PER_CHANNEL_SUPPORTED, // LeafVariableBitWidthPerChannelSupported
   ITEM_SYMINC_SUPPORTED, // LeafSymincSupported
   ITEM_COMPRESSION_METHOD_SUPPORTED, // LstCompressionMethodSupported
 };

 GrpFormatOfIqSample(uint32_t id);
 ~GrpFormatOfIqSample();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /format-of-iq-sample/dynamic-compression-supported
 // Description: Informs if radio supports dynamic compression method
 // -----------------------------------------------------------------------------
 class LeafDynamicCompressionSupported : public YangLeaf {
  public:
   LeafDynamicCompressionSupported(uint32_t id);
   ~LeafDynamicCompressionSupported();

 }; // LeafDynamicCompressionSupported

 // -----------------------------------------------------------------------------
 // Leaf:        /format-of-iq-sample/realtime-variable-bit-width-supported
 // Description: Informs if O-RU supports realtime variable bit with
 // -----------------------------------------------------------------------------
 class LeafRealtimeVariableBitWidthSupported : public YangLeaf {
  public:
   LeafRealtimeVariableBitWidthSupported(uint32_t id);
   ~LeafRealtimeVariableBitWidthSupported();

 }; // LeafRealtimeVariableBitWidthSupported

 // -----------------------------------------------------------------------------
 // Leaf:        /format-of-iq-sample/variable-bit-width-per-channel-supported
 // Description: Informs if variable bit width per channel is supported or not
 // -----------------------------------------------------------------------------
 class LeafVariableBitWidthPerChannelSupported : public YangLeaf {
  public:
   LeafVariableBitWidthPerChannelSupported(uint32_t id);
   ~LeafVariableBitWidthPerChannelSupported();

 }; // LeafVariableBitWidthPerChannelSupported

 // -----------------------------------------------------------------------------
 // Leaf:        /format-of-iq-sample/syminc-supported
 // Description: Informs if symbol number increment command in a C-Plane is
 //              supported or not
 // -----------------------------------------------------------------------------
 class LeafSymincSupported : public YangLeaf {
  public:
   LeafSymincSupported(uint32_t id);
   ~LeafSymincSupported();

 }; // LeafSymincSupported

 // -----------------------------------------------------------------------------
 // List:        /format-of-iq-sample/compression-method-supported
 // Description: List of supported compression methods by O-RU
 // -----------------------------------------------------------------------------
 class LstCompressionMethodSupported : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_CF_COMPRESSION_DETAILS, // Use GrpCfCompressionDetails
   };

   LstCompressionMethodSupported(uint32_t id);
   ~LstCompressionMethodSupported();

   YangResult_E initialise(void);

 }; // LstCompressionMethodSupported

}; // GrpFormatOfIqSample

// -----------------------------------------------------------------------------
// Grouping:    /scs-a-b
// Description: Grouping for scs-a and scs-b
// -----------------------------------------------------------------------------
class GrpScsAB : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_SCS_A, // LeafScsA
   ITEM_SCS_B, // LeafScsB
 };

 GrpScsAB(uint32_t id);
 ~GrpScsAB();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-a-b/scs-a
 // Description: Sub-carrier spacing configuration
 // -----------------------------------------------------------------------------
 class LeafScsA : public YangLeaf {
  public:
   // Sub-carrier spacing configuration
   enum class ScsA_E : uint32_t {

     Num_ScsA_E
   };

   LeafScsA(uint32_t id);
   ~LeafScsA();

 }; // LeafScsA

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-a-b/scs-b
 // Description: Sub-carrier spacing configuration
 // -----------------------------------------------------------------------------
 class LeafScsB : public YangLeaf {
  public:
   // Sub-carrier spacing configuration
   enum class ScsB_E : uint32_t {

     Num_ScsB_E
   };

   LeafScsB(uint32_t id);
   ~LeafScsB();

 }; // LeafScsB

}; // GrpScsAB

// -----------------------------------------------------------------------------
// Grouping:    /ul-mixed-num-required-guard-rbs
// Description: Required number of guard resource blocks for the combination of
//              subcarrier spacing values for uplink
// -----------------------------------------------------------------------------
class GrpUlMixedNumRequiredGuardRbs : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NUMBER_OF_GUARD_RBS_UL, // LeafNumberOfGuardRbsUl
   ITEM_SCS_A_B, // Use GrpScsAB
 };

 GrpUlMixedNumRequiredGuardRbs(uint32_t id);
 ~GrpUlMixedNumRequiredGuardRbs();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /ul-mixed-num-required-guard-rbs/number-of-guard-rbs-ul
 // Description: This value indicates the required number of guard resource
 // blocks
 //              between the mixed numerologies, the RB using scs-a and the RB
 //              using scs-b. It's number is based on scs-a
 // -----------------------------------------------------------------------------
 class LeafNumberOfGuardRbsUl : public YangLeaf {
  public:
   LeafNumberOfGuardRbsUl(uint32_t id);
   ~LeafNumberOfGuardRbsUl();

 }; // LeafNumberOfGuardRbsUl

}; // GrpUlMixedNumRequiredGuardRbs

// -----------------------------------------------------------------------------
// Grouping:    /dl-mixed-num-required-guard-rbs
// Description: Required number of guard resource blocks for the combination of
//              subcarrier spacing values for uplink
// -----------------------------------------------------------------------------
class GrpDlMixedNumRequiredGuardRbs : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NUMBER_OF_GUARD_RBS_DL, // LeafNumberOfGuardRbsDl
   ITEM_SCS_A_B, // Use GrpScsAB
 };

 GrpDlMixedNumRequiredGuardRbs(uint32_t id);
 ~GrpDlMixedNumRequiredGuardRbs();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /dl-mixed-num-required-guard-rbs/number-of-guard-rbs-dl
 // Description: This value indicates the required number of guard resource
 // blocks
 //              between the mixed numerologies, the RB using scs-a and the RB
 //              using scs-b. It's number is based on scs-a
 // -----------------------------------------------------------------------------
 class LeafNumberOfGuardRbsDl : public YangLeaf {
  public:
   LeafNumberOfGuardRbsDl(uint32_t id);
   ~LeafNumberOfGuardRbsDl();

 }; // LeafNumberOfGuardRbsDl

}; // GrpDlMixedNumRequiredGuardRbs

// -----------------------------------------------------------------------------
// Grouping:    /ru-capabilities
// Description: Structure representing set of capabilities.
// -----------------------------------------------------------------------------
class GrpRuCapabilities : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_RU_SUPPORTED_CATEGORY, // LeafRuSupportedCategory
   ITEM_NUMBER_OF_RU_PORTS, // LeafNumberOfRuPorts
   ITEM_NUMBER_OF_SPATIAL_STREAMS, // LeafNumberOfSpatialStreams
   ITEM_MAX_POWER_PER_PA_ANTENNA, // LeafMaxPowerPerPaAntenna
   ITEM_MIN_POWER_PER_PA_ANTENNA, // LeafMinPowerPerPaAntenna
   ITEM_FRONTHAUL_SPLIT_OPTION, // LeafFronthaulSplitOption
   ITEM_ENERGY_SAVING_BY_TRANSMISSION_BLANKS, // LeafEnergySavingByTransmissionBlanks
   ITEM_DYNAMIC_TRANSPORT_DELAY_MANAGEMENT_SUPPORTED, // LeafDynamicTransportDelayManagementSupported
   ITEM_FORMAT_OF_IQ_SAMPLE, // CntFormatOfIqSample
   ITEM_UL_MIXED_NUM_REQUIRED_GUARD_RBS, // LstUlMixedNumRequiredGuardRbs
   ITEM_DL_MIXED_NUM_REQUIRED_GUARD_RBS, // LstDlMixedNumRequiredGuardRbs
 };

 GrpRuCapabilities(uint32_t id);
 ~GrpRuCapabilities();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/ru-supported-category
 // Description: Informs about which category O-RU supports
 // -----------------------------------------------------------------------------
 class LeafRuSupportedCategory : public YangLeaf {
  public:
   // Informs about which category O-RU supports
   enum class RuSupportedCategory_E : uint32_t {
     CAT_A, // Informs that precoding is not supported in O-RU
     CAT_B, // Informs that precoding is supported in O-RU

     Num_RuSupportedCategory_E
   };

   LeafRuSupportedCategory(uint32_t id);
   ~LeafRuSupportedCategory();

 }; // LeafRuSupportedCategory

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
 class LeafNumberOfRuPorts : public YangLeaf {
  public:
   LeafNumberOfRuPorts(uint32_t id);
   ~LeafNumberOfRuPorts();

 }; // LeafNumberOfRuPorts

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/number-of-spatial-streams
 // Description: This value indicates the number of spatial streams supported at
 // O-RU for DL and UL.
 //              For DL, it is same as the number of antenna ports specified in
 //              3GPP TS38.214, Section 5.2 and 3GPP TS36.213, Section 5.2.
 // -----------------------------------------------------------------------------
 class LeafNumberOfSpatialStreams : public YangLeaf {
  public:
   LeafNumberOfSpatialStreams(uint32_t id);
   ~LeafNumberOfSpatialStreams();

 }; // LeafNumberOfSpatialStreams

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/max-power-per-pa-antenna
 // Description: This value indicates Maximum Power per PA per antenna. Value
 // unit is dBm.
 // -----------------------------------------------------------------------------
 class LeafMaxPowerPerPaAntenna : public YangLeaf {
  public:
   LeafMaxPowerPerPaAntenna(uint32_t id);
   ~LeafMaxPowerPerPaAntenna();

 }; // LeafMaxPowerPerPaAntenna

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/min-power-per-pa-antenna
 // Description: This value indicates Minimum Power per PA per antenna. Value
 // unit is dBm.
 // -----------------------------------------------------------------------------
 class LeafMinPowerPerPaAntenna : public YangLeaf {
  public:
   LeafMinPowerPerPaAntenna(uint32_t id);
   ~LeafMinPowerPerPaAntenna();

 }; // LeafMinPowerPerPaAntenna

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/fronthaul-split-option
 // Description: This value indicates the Fronthaul Split Option, i.e., 2 or 7
 // in this release.
 // -----------------------------------------------------------------------------
 class LeafFronthaulSplitOption : public YangLeaf {
  public:
   LeafFronthaulSplitOption(uint32_t id);
   ~LeafFronthaulSplitOption();

 }; // LeafFronthaulSplitOption

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/energy-saving-by-transmission-blanks
 // Description: Parameter informs if unit supports energy saving by
 // transmission blanking
 // -----------------------------------------------------------------------------
 class LeafEnergySavingByTransmissionBlanks : public YangLeaf {
  public:
   LeafEnergySavingByTransmissionBlanks(uint32_t id);
   ~LeafEnergySavingByTransmissionBlanks();

 }; // LeafEnergySavingByTransmissionBlanks

 // -----------------------------------------------------------------------------
 // Leaf:        /ru-capabilities/dynamic-transport-delay-management-supported
 // Description: Parameter informs if unit supports dynamic transport delay
 // management through eCPRI Msg 5
 // -----------------------------------------------------------------------------
 class LeafDynamicTransportDelayManagementSupported : public YangLeaf {
  public:
   LeafDynamicTransportDelayManagementSupported(uint32_t id);
   ~LeafDynamicTransportDelayManagementSupported();

 }; // LeafDynamicTransportDelayManagementSupported

 // -----------------------------------------------------------------------------
 // Container:   /ru-capabilities/format-of-iq-sample
 // Description: Indicates module capabilities about IQ samples
 // -----------------------------------------------------------------------------
 class CntFormatOfIqSample : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_FORMAT_OF_IQ_SAMPLE, // Use GrpFormatOfIqSample
   };

   CntFormatOfIqSample(uint32_t id);
   ~CntFormatOfIqSample();

   YangResult_E initialise(void);

 }; // CntFormatOfIqSample

 // -----------------------------------------------------------------------------
 // List:        /ru-capabilities/ul-mixed-num-required-guard-rbs
 // Description: List of required number of guard resource blocks
 //              for the combination of subcarrier spacing values for downlink
 // -----------------------------------------------------------------------------
 class LstUlMixedNumRequiredGuardRbs : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_UL_MIXED_NUM_REQUIRED_GUARD_RBS, // Use GrpUlMixedNumRequiredGuardRbs
   };

   LstUlMixedNumRequiredGuardRbs(uint32_t id);
   ~LstUlMixedNumRequiredGuardRbs();

   YangResult_E initialise(void);

 }; // LstUlMixedNumRequiredGuardRbs

 // -----------------------------------------------------------------------------
 // List:        /ru-capabilities/dl-mixed-num-required-guard-rbs
 // Description: List of required number of guard resource blocks
 //              for the combination of subcarrier spacing values for uplink
 // -----------------------------------------------------------------------------
 class LstDlMixedNumRequiredGuardRbs : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_DL_MIXED_NUM_REQUIRED_GUARD_RBS, // Use GrpDlMixedNumRequiredGuardRbs
   };

   LstDlMixedNumRequiredGuardRbs(uint32_t id);
   ~LstDlMixedNumRequiredGuardRbs();

   YangResult_E initialise(void);

 }; // LstDlMixedNumRequiredGuardRbs

}; // GrpRuCapabilities

// -----------------------------------------------------------------------------
// Grouping:    /sub-band-info
// Description: container for collection of leafs for LAA subband 46
// -----------------------------------------------------------------------------
class GrpSubBandInfo : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NUMBER_OF_LAA_SCARRIERS, // LeafNumberOfLaaScarriers
   ITEM_MAXIMUM_LAA_BUFFER_SIZE, // LeafMaximumLaaBufferSize
   ITEM_MAXIMUM_PROCESSING_TIME, // LeafMaximumProcessingTime
   ITEM_SELF_CONFIGURE, // LeafSelfConfigure
   ITEM_SUB_BAND_FREQUENCY_RANGES, // LstSubBandFrequencyRanges
 };

 GrpSubBandInfo(uint32_t id);
 ~GrpSubBandInfo();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-info/number-of-laa-scarriers
 // Description: This value indicates the number of LAA secondary carriers
 // supported at O-RU.
 // -----------------------------------------------------------------------------
 class LeafNumberOfLaaScarriers : public YangLeaf {
  public:
   LeafNumberOfLaaScarriers(uint32_t id);
   ~LeafNumberOfLaaScarriers();

 }; // LeafNumberOfLaaScarriers

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-info/maximum-laa-buffer-size
 // Description: Maximum O-RU buffer size in Kilobytes (KB) per CC. This
 // parameter is
 //              needed at the O-DU to know how much data can be sent in advance
 //              and stored at the O-RU to address the LBT uncertainity.
 // -----------------------------------------------------------------------------
 class LeafMaximumLaaBufferSize : public YangLeaf {
  public:
   LeafMaximumLaaBufferSize(uint32_t id);
   ~LeafMaximumLaaBufferSize();

 }; // LeafMaximumLaaBufferSize

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-info/maximum-processing-time
 // Description: Maximum O-RU Processing time in microseconds at the O-RU to
 // handle the
 //              received/transmitted packets from/to the O-DU. This parameter
 //              is needed at the O-DU to determine the time where it needs to
 //              send the data to the O-RU.
 // -----------------------------------------------------------------------------
 class LeafMaximumProcessingTime : public YangLeaf {
  public:
   LeafMaximumProcessingTime(uint32_t id);
   ~LeafMaximumProcessingTime();

 }; // LeafMaximumProcessingTime

 // -----------------------------------------------------------------------------
 // Leaf:        /sub-band-info/self-configure
 // Description: This value indicates that the O-RU can manage the
 // contention window locally.
 // -----------------------------------------------------------------------------
 class LeafSelfConfigure : public YangLeaf {
  public:
   LeafSelfConfigure(uint32_t id);
   ~LeafSelfConfigure();

 }; // LeafSelfConfigure

 // -----------------------------------------------------------------------------
 // List:        /sub-band-info/sub-band-frequency-ranges
 // Description: frequency information on a per sub-band basis
 // -----------------------------------------------------------------------------
 class LstSubBandFrequencyRanges : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_SUB_BAND, // LeafSubBand
     ITEM_SUB_BAND_MAX_MIN_UL_DL_FREQUENCY, // Use
                                            // GrpSubBandMaxMinUlDlFrequency
   };

   LstSubBandFrequencyRanges(uint32_t id);
   ~LstSubBandFrequencyRanges();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /sub-band-info/sub-band-frequency-ranges/sub-band
   // Description: Sub band when band 46
   // -----------------------------------------------------------------------------
   class LeafSubBand : public YangLeaf {
    public:
     LeafSubBand(uint32_t id);
     ~LeafSubBand();

   }; // LeafSubBand

 }; // LstSubBandFrequencyRanges

}; // GrpSubBandInfo

// -----------------------------------------------------------------------------
// Grouping:    /support-for-dl
// Description: Grouping for DL specific parameters
// -----------------------------------------------------------------------------
class GrpSupportForDl : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_SUPPORTED_FREQUENCY_DL, // LeafMaxSupportedFrequencyDl
   ITEM_MIN_SUPPORTED_FREQUENCY_DL, // LeafMinSupportedFrequencyDl
   ITEM_MAX_SUPPORTED_BANDWIDTH_DL, // LeafMaxSupportedBandwidthDl
   ITEM_MAX_NUM_CARRIERS_DL, // LeafMaxNumCarriersDl
   ITEM_MAX_CARRIER_BANDWIDTH_DL, // LeafMaxCarrierBandwidthDl
   ITEM_MIN_CARRIER_BANDWIDTH_DL, // LeafMinCarrierBandwidthDl
 };

 GrpSupportForDl(uint32_t id);
 ~GrpSupportForDl();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/max-supported-frequency-dl
 // Description: This value indicates Maximum supported downlink frequency.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxSupportedFrequencyDl : public YangLeaf {
  public:
   LeafMaxSupportedFrequencyDl(uint32_t id);
   ~LeafMaxSupportedFrequencyDl();

 }; // LeafMaxSupportedFrequencyDl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/min-supported-frequency-dl
 // Description: This value indicates Minimum supported downlink frequency.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMinSupportedFrequencyDl : public YangLeaf {
  public:
   LeafMinSupportedFrequencyDl(uint32_t id);
   ~LeafMinSupportedFrequencyDl();

 }; // LeafMinSupportedFrequencyDl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/max-supported-bandwidth-dl
 // Description: This value indicates Maximum total downlink bandwidth in
 // module. Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxSupportedBandwidthDl : public YangLeaf {
  public:
   LeafMaxSupportedBandwidthDl(uint32_t id);
   ~LeafMaxSupportedBandwidthDl();

 }; // LeafMaxSupportedBandwidthDl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/max-num-carriers-dl
 // Description: This value indicates Maximum number of downlink carriers in
 // module.
 // -----------------------------------------------------------------------------
 class LeafMaxNumCarriersDl : public YangLeaf {
  public:
   LeafMaxNumCarriersDl(uint32_t id);
   ~LeafMaxNumCarriersDl();

 }; // LeafMaxNumCarriersDl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/max-carrier-bandwidth-dl
 // Description: This value indicates Maximum bandwidth per downlink carrier.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxCarrierBandwidthDl : public YangLeaf {
  public:
   LeafMaxCarrierBandwidthDl(uint32_t id);
   ~LeafMaxCarrierBandwidthDl();

 }; // LeafMaxCarrierBandwidthDl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-dl/min-carrier-bandwidth-dl
 // Description: This value indicates Minimum bandwidth per downlink carrier.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMinCarrierBandwidthDl : public YangLeaf {
  public:
   LeafMinCarrierBandwidthDl(uint32_t id);
   ~LeafMinCarrierBandwidthDl();

 }; // LeafMinCarrierBandwidthDl

}; // GrpSupportForDl

// -----------------------------------------------------------------------------
// Grouping:    /support-for-ul
// Description: Grouping for UL specific parameters
// -----------------------------------------------------------------------------
class GrpSupportForUl : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_SUPPORTED_FREQUENCY_UL, // LeafMaxSupportedFrequencyUl
   ITEM_MIN_SUPPORTED_FREQUENCY_UL, // LeafMinSupportedFrequencyUl
   ITEM_MAX_SUPPORTED_BANDWIDTH_UL, // LeafMaxSupportedBandwidthUl
   ITEM_MAX_NUM_CARRIERS_UL, // LeafMaxNumCarriersUl
   ITEM_MAX_CARRIER_BANDWIDTH_UL, // LeafMaxCarrierBandwidthUl
   ITEM_MIN_CARRIER_BANDWIDTH_UL, // LeafMinCarrierBandwidthUl
 };

 GrpSupportForUl(uint32_t id);
 ~GrpSupportForUl();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/max-supported-frequency-ul
 // Description: This value indicates Maximum supported uplink frequency. Value
 // unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxSupportedFrequencyUl : public YangLeaf {
  public:
   LeafMaxSupportedFrequencyUl(uint32_t id);
   ~LeafMaxSupportedFrequencyUl();

 }; // LeafMaxSupportedFrequencyUl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/min-supported-frequency-ul
 // Description: This value indicates Minimum supported uplink frequency. Value
 // unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMinSupportedFrequencyUl : public YangLeaf {
  public:
   LeafMinSupportedFrequencyUl(uint32_t id);
   ~LeafMinSupportedFrequencyUl();

 }; // LeafMinSupportedFrequencyUl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/max-supported-bandwidth-ul
 // Description: This value indicates Maximum total uplink bandwidth in module.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxSupportedBandwidthUl : public YangLeaf {
  public:
   LeafMaxSupportedBandwidthUl(uint32_t id);
   ~LeafMaxSupportedBandwidthUl();

 }; // LeafMaxSupportedBandwidthUl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/max-num-carriers-ul
 // Description: This value indicates Maximum number of uplink carriers in
 // module.
 // -----------------------------------------------------------------------------
 class LeafMaxNumCarriersUl : public YangLeaf {
  public:
   LeafMaxNumCarriersUl(uint32_t id);
   ~LeafMaxNumCarriersUl();

 }; // LeafMaxNumCarriersUl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/max-carrier-bandwidth-ul
 // Description: This value indicates Maximum bandwidth per uplink carrier.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMaxCarrierBandwidthUl : public YangLeaf {
  public:
   LeafMaxCarrierBandwidthUl(uint32_t id);
   ~LeafMaxCarrierBandwidthUl();

 }; // LeafMaxCarrierBandwidthUl

 // -----------------------------------------------------------------------------
 // Leaf:        /support-for-ul/min-carrier-bandwidth-ul
 // Description: This value indicates Minimum bandwidth per uplink carrier.
 // Value unit is Hz.
 // -----------------------------------------------------------------------------
 class LeafMinCarrierBandwidthUl : public YangLeaf {
  public:
   LeafMinCarrierBandwidthUl(uint32_t id);
   ~LeafMinCarrierBandwidthUl();

 }; // LeafMinCarrierBandwidthUl

}; // GrpSupportForUl

// -----------------------------------------------------------------------------
// Grouping:    /band-capabilities
// Description: Capabilities that are needed to be defined per each band
// -----------------------------------------------------------------------------
class GrpBandCapabilities : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_BAND_NUMBER, // LeafBandNumber
   ITEM_MAX_NUM_COMPONENT_CARRIERS, // LeafMaxNumComponentCarriers
   ITEM_MAX_NUM_BANDS, // LeafMaxNumBands
   ITEM_MAX_NUM_SECTORS, // LeafMaxNumSectors
   ITEM_MAX_POWER_PER_ANTENNA, // LeafMaxPowerPerAntenna
   ITEM_MIN_POWER_PER_ANTENNA, // LeafMinPowerPerAntenna
   ITEM_CODEBOOK_CONFIGURATION_NG, // LeafCodebookConfigurationNg
   ITEM_CODEBOOK_CONFIGURATION_N1, // LeafCodebookConfigurationN1
   ITEM_CODEBOOK_CONFIGURATION_N2, // LeafCodebookConfigurationN2
   ITEM_SUB_BAND_INFO, // CntSubBandInfo
   ITEM_SUPPORT_FOR_DL, // Use GrpSupportForDl
   ITEM_SUPPORT_FOR_UL, // Use GrpSupportForUl
 };

 GrpBandCapabilities(uint32_t id);
 ~GrpBandCapabilities();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/band-number
 // Description: Band number
 // -----------------------------------------------------------------------------
 class LeafBandNumber : public YangLeaf {
  public:
   LeafBandNumber(uint32_t id);
   ~LeafBandNumber();

 }; // LeafBandNumber

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/max-num-component-carriers
 // Description: maximum number of component carriers supported by the O-RU
 // -----------------------------------------------------------------------------
 class LeafMaxNumComponentCarriers : public YangLeaf {
  public:
   LeafMaxNumComponentCarriers(uint32_t id);
   ~LeafMaxNumComponentCarriers();

 }; // LeafMaxNumComponentCarriers

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/max-num-bands
 // Description: maximum number of bands supported by the O-RU
 // -----------------------------------------------------------------------------
 class LeafMaxNumBands : public YangLeaf {
  public:
   LeafMaxNumBands(uint32_t id);
   ~LeafMaxNumBands();

 }; // LeafMaxNumBands

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/max-num-sectors
 // Description: maximum number of sectors supported by the O-RU
 // -----------------------------------------------------------------------------
 class LeafMaxNumSectors : public YangLeaf {
  public:
   LeafMaxNumSectors(uint32_t id);
   ~LeafMaxNumSectors();

 }; // LeafMaxNumSectors

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/max-power-per-antenna
 // Description: This value indicates Maximum Power per band per antenna. Value
 // unit is dBm.
 // -----------------------------------------------------------------------------
 class LeafMaxPowerPerAntenna : public YangLeaf {
  public:
   LeafMaxPowerPerAntenna(uint32_t id);
   ~LeafMaxPowerPerAntenna();

 }; // LeafMaxPowerPerAntenna

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/min-power-per-antenna
 // Description: This value indicates Minimum Power per band per antenna. Value
 // unit is dBm.
 // -----------------------------------------------------------------------------
 class LeafMinPowerPerAntenna : public YangLeaf {
  public:
   LeafMinPowerPerAntenna(uint32_t id);
   ~LeafMinPowerPerAntenna();

 }; // LeafMinPowerPerAntenna

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/codebook-configuration_ng
 // Description: This parameter informs the precoder codebook_ng that are used
 // for precoding
 // -----------------------------------------------------------------------------
 class LeafCodebookConfigurationNg : public YangLeaf {
  public:
   LeafCodebookConfigurationNg(uint32_t id);
   ~LeafCodebookConfigurationNg();

 }; // LeafCodebookConfigurationNg

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/codebook-configuration_n1
 // Description: This parameter informs the precoder codebook_n1 that are used
 // for precoding
 // -----------------------------------------------------------------------------
 class LeafCodebookConfigurationN1 : public YangLeaf {
  public:
   LeafCodebookConfigurationN1(uint32_t id);
   ~LeafCodebookConfigurationN1();

 }; // LeafCodebookConfigurationN1

 // -----------------------------------------------------------------------------
 // Leaf:        /band-capabilities/codebook-configuration_n2
 // Description: This parameter informs the precoder codebook_n2 that are used
 // for precoding
 // -----------------------------------------------------------------------------
 class LeafCodebookConfigurationN2 : public YangLeaf {
  public:
   LeafCodebookConfigurationN2(uint32_t id);
   ~LeafCodebookConfigurationN2();

 }; // LeafCodebookConfigurationN2

 // -----------------------------------------------------------------------------
 // Container:   /band-capabilities/sub-band-info
 // Description: container for collection of leafs for LAA subband 46
 // -----------------------------------------------------------------------------
 class CntSubBandInfo : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_SUB_BAND_INFO, // Use GrpSubBandInfo
   };

   CntSubBandInfo(uint32_t id);
   ~CntSubBandInfo();

   YangResult_E initialise(void);

 }; // CntSubBandInfo

}; // GrpBandCapabilities


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
class ModuleORanModuleCap : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_LAA, // Feature
   ITEM_TRANSPORT_FRAGMENTATION, // Feature
   ITEM_MODULE_CAPABILITY, // CntModuleCapability
 };

 ModuleORanModuleCap(uint32_t id);
 ~ModuleORanModuleCap();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanModuleCap_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_MODULE_CAP_H_ */
