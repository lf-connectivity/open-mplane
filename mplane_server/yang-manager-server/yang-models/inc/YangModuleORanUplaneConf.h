#ifndef _MODULE_O_RAN_UPLANE_CONF_H_
#define _MODULE_O_RAN_UPLANE_CONF_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUplaneConf.h
 * \brief     Module ORanUplaneConf interface
 *
 *
 * \details   This file defines the YANG module o-ran-uplane-conf interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-uplane-conf"
 *            YANG Filename:    "o-ran-uplane-conf.yang"
 *            Module Prefix:    "o-ran-uplane-conf"
 *            Module namespace: "urn:o-ran:uplane-conf:1.0"
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

// Module:   o-ran-processing-element
// Revision:
// Notes:
#include "YangModuleORanProcessingElement.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   o-ran-module-cap
// Revision: 2019-07-03
// Notes:
#include "YangModuleORanModuleCap.h"

// Module:   o-ran-compression-factors
// Revision:
// Notes:
#include "YangModuleORanCompressionFactors.h"


namespace Mplane {

namespace ModuleORanUplaneConf_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// Type definition for polarisations
enum class PolarisationType_E : uint32_t {
  MINUS_45, // MINUS_45
  ZERO, // ZERO
  PLUS_45, // PLUS_45
  PLUS_90, // PLUS_90

  Num_PolarisationType_E
};

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
// Container:   /user-plane-configuration
// Description: top level container for user plane configuration
// -----------------------------------------------------------------------------
class CntUserPlaneConfiguration : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_UPLANE_CONF_GROUP, // Use GrpUplaneConfGroup
 };

 CntUserPlaneConfiguration(uint32_t id);
 ~CntUserPlaneConfiguration();

 YangResult_E initialise(void);

}; // CntUserPlaneConfiguration


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /laa-carrier-config
// Description: Carrier Configuration for support of LAA.
// -----------------------------------------------------------------------------
class GrpLaaCarrierConfig : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ED_THRESHOLD_PDSCH, // LeafEdThresholdPdsch
   ITEM_ED_THRESHOLD_DRS, // LeafEdThresholdDrs
   ITEM_TX_ANTENNA_PORTS, // LeafTxAntennaPorts
   ITEM_TRANSMISSION_POWER_FOR_DRS, // LeafTransmissionPowerForDrs
   ITEM_DMTC_PERIOD, // LeafDmtcPeriod
   ITEM_DMTC_OFFSET, // LeafDmtcOffset
   ITEM_LBT_TIMER, // LeafLbtTimer
   ITEM_MAX_CW_USAGE_COUNTER, // LstMaxCwUsageCounter
 };

 GrpLaaCarrierConfig(uint32_t id);
 ~GrpLaaCarrierConfig();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/ed-threshold-pdsch
 // Description: This value indicates Energy Detection(ED) threshold for LBT for
 // PDSCH and for measurements in dBm.
 // -----------------------------------------------------------------------------
 class LeafEdThresholdPdsch : public YangLeaf {
  public:
   LeafEdThresholdPdsch(uint32_t id);
   ~LeafEdThresholdPdsch();

 }; // LeafEdThresholdPdsch

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/ed-threshold-drs
 // Description: This value indicates Energy Detection(ED) threshold for LBT for
 // DRS in dBm.
 // -----------------------------------------------------------------------------
 class LeafEdThresholdDrs : public YangLeaf {
  public:
   LeafEdThresholdDrs(uint32_t id);
   ~LeafEdThresholdDrs();

 }; // LeafEdThresholdDrs

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/tx-antenna-ports
 // Description: This value indicates Tx antenna ports for DRS (1, 2, 4)
 // -----------------------------------------------------------------------------
 class LeafTxAntennaPorts : public YangLeaf {
  public:
   LeafTxAntennaPorts(uint32_t id);
   ~LeafTxAntennaPorts();

 }; // LeafTxAntennaPorts

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/transmission-power-for-drs
 // Description: This value indicates offset of Cell specific reference
 // Signal(CRS) power to reference signal power (dB).
 //              DRS signal consists of CRS, PSS, SSS, and optionally CSI-RS.
 // -----------------------------------------------------------------------------
 class LeafTransmissionPowerForDrs : public YangLeaf {
  public:
   LeafTransmissionPowerForDrs(uint32_t id);
   ~LeafTransmissionPowerForDrs();

 }; // LeafTransmissionPowerForDrs

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/dmtc-period
 // Description: This value indicates DRS measurement timing configuration
 // (DMTC) period in ms
 // -----------------------------------------------------------------------------
 class LeafDmtcPeriod : public YangLeaf {
  public:
   // This value indicates DRS measurement timing configuration (DMTC) period in
   // ms
   enum class DmtcPeriod_E : uint32_t {
     FORTY, // 40 ms
     EIGHTY, // 80 ms
     ONE_HUNDRED_SIXTY, // 160 ms

     Num_DmtcPeriod_E
   };

   LeafDmtcPeriod(uint32_t id);
   ~LeafDmtcPeriod();

 }; // LeafDmtcPeriod

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/dmtc-offset
 // Description: This value indicates dmtc offset in Subframes.
 // -----------------------------------------------------------------------------
 class LeafDmtcOffset : public YangLeaf {
  public:
   LeafDmtcOffset(uint32_t id);
   ~LeafDmtcOffset();

 }; // LeafDmtcOffset

 // -----------------------------------------------------------------------------
 // Leaf:        /laa-carrier-config/lbt-timer
 // Description: This value indicates LBT Timer in milliseconds.
 // -----------------------------------------------------------------------------
 class LeafLbtTimer : public YangLeaf {
  public:
   LeafLbtTimer(uint32_t id);
   ~LeafLbtTimer();

 }; // LeafLbtTimer

 // -----------------------------------------------------------------------------
 // List:        /laa-carrier-config/max-cw-usage-counter
 // Description:
 // -----------------------------------------------------------------------------
 class LstMaxCwUsageCounter : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_PRIORITY, // LeafPriority
     ITEM_COUNTER_VALUE, // LeafCounterValue
   };

   LstMaxCwUsageCounter(uint32_t id);
   ~LstMaxCwUsageCounter();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /laa-carrier-config/max-cw-usage-counter/priority
   // Description: This value provides the priority class traffic for
   // which the counter is calculated.
   // -----------------------------------------------------------------------------
   class LeafPriority : public YangLeaf {
    public:
     // This value provides the priority class traffic for which the
     // counter is calculated.
     enum class Priority_E : uint32_t {
       P1, // priority 1
       P2, // priority 2
       P3, // priority 3
       P4, // priority 4

       Num_Priority_E
     };

     LeafPriority(uint32_t id);
     ~LeafPriority();

   }; // LeafPriority

   // -----------------------------------------------------------------------------
   // Leaf:        /laa-carrier-config/max-cw-usage-counter/counter-value
   // Description: This value indicates the maximum value of counter
   //              which shows how many max congestion window value is
   //              used for backoff number of priority class traffic.
   //              This value is defined at 3GPP 36.213 section 15.1.3 as
   //              K.
   // -----------------------------------------------------------------------------
   class LeafCounterValue : public YangLeaf {
    public:
     LeafCounterValue(uint32_t id);
     ~LeafCounterValue();

   }; // LeafCounterValue

 }; // LstMaxCwUsageCounter

}; // GrpLaaCarrierConfig

// -----------------------------------------------------------------------------
// Grouping:    /eaxc
// Description: One eAxC identifier (eAxC ID) comprises a band and sector
//              identifier (BandSector_ID), a component-carrier identifier
//              (CC_ID) and a spatial stream identifier (RU_Port_ID).
//
//              In this version of the specification, one eAxC contains only one
//              spatial stream (i.e. one beam per subcarrier) at a time.
//
//              Bit allocation is subdivided as follows:
//              *    O_DU_Port_ID: Used to differentiate processing units at
//              O-DU
//              *    BandSector_ID: Aggregated cell identifier
//              *    CC_ID: distinguishes Carrier Components
//              *    RU_Port_ID: Used to differentiate spatial streams or beams
//              on the O-RU
//
//              The bitwidth of each of the above fields is variable this model
//              is supposed to check
//               if we are occpying bits continuously but we do not have to
//               occupy all 16 bits
// -----------------------------------------------------------------------------
class GrpEaxc : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_O_DU_PORT_BITMASK, // LeafODuPortBitmask
   ITEM_BAND_SECTOR_BITMASK, // LeafBandSectorBitmask
   ITEM_CCID_BITMASK, // LeafCcidBitmask
   ITEM_RU_PORT_BITMASK, // LeafRuPortBitmask
   ITEM_EAXC_ID, // LeafEaxcId
 };

 GrpEaxc(uint32_t id);
 ~GrpEaxc();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /eaxc/o-du-port-bitmask
 // Description: mask for eaxc-id bits used to encode O-DU Port ID
 // -----------------------------------------------------------------------------
 class LeafODuPortBitmask : public YangLeaf {
  public:
   LeafODuPortBitmask(uint32_t id);
   ~LeafODuPortBitmask();

 }; // LeafODuPortBitmask

 // -----------------------------------------------------------------------------
 // Leaf:        /eaxc/band-sector-bitmask
 // Description: mask for eaxc-id bits used to encode the band sector ID
 // -----------------------------------------------------------------------------
 class LeafBandSectorBitmask : public YangLeaf {
  public:
   LeafBandSectorBitmask(uint32_t id);
   ~LeafBandSectorBitmask();

 }; // LeafBandSectorBitmask

 // -----------------------------------------------------------------------------
 // Leaf:        /eaxc/ccid-bitmask
 // Description: mask for eaxc-id bits used to encode the component carrier id
 // -----------------------------------------------------------------------------
 class LeafCcidBitmask : public YangLeaf {
  public:
   LeafCcidBitmask(uint32_t id);
   ~LeafCcidBitmask();

 }; // LeafCcidBitmask

 // -----------------------------------------------------------------------------
 // Leaf:        /eaxc/ru-port-bitmask
 // Description: mask for eaxc-id bits used to encode the O-RU Port ID
 // -----------------------------------------------------------------------------
 class LeafRuPortBitmask : public YangLeaf {
  public:
   LeafRuPortBitmask(uint32_t id);
   ~LeafRuPortBitmask();

 }; // LeafRuPortBitmask

 // -----------------------------------------------------------------------------
 // Leaf:        /eaxc/eaxc-id
 // Description: encoded value of eaxcid to be read by CU-Plane
 // -----------------------------------------------------------------------------
 class LeafEaxcId : public YangLeaf {
  public:
   LeafEaxcId(uint32_t id);
   ~LeafEaxcId();

 }; // LeafEaxcId

}; // GrpEaxc

// -----------------------------------------------------------------------------
// Grouping:    /parameters
// Description: Grouping of all parameters common between UL and DL
// -----------------------------------------------------------------------------
class GrpParameters : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NAME, // LeafName
   ITEM_NUMBER_OF_ROWS, // LeafNumberOfRows
   ITEM_NUMBER_OF_COLUMNS, // LeafNumberOfColumns
   ITEM_NUMBER_OF_ARRAY_LAYERS, // LeafNumberOfArrayLayers
   ITEM_HORIZONTAL_SPACING, // LeafHorizontalSpacing
   ITEM_VERTICAL_SPACING, // LeafVerticalSpacing
   ITEM_BAND_NUMBER, // RefBandNumber
   ITEM_NORMAL_VECTOR_DIRECTION, // CntNormalVectorDirection
   ITEM_LEFTMOST_BOTTOM_ARRAY_ELEMENT_POSITION, // CntLeftmostBottomArrayElementPosition
   ITEM_POLARISATIONS, // LstPolarisations
 };

 GrpParameters(uint32_t id);
 ~GrpParameters();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/name
 // Description: Unique name of array antenna
 // -----------------------------------------------------------------------------
 class LeafName : public YangLeaf {
  public:
   LeafName(uint32_t id);
   ~LeafName();

 }; // LeafName

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/number-of-rows
 // Description: Number of rows array elements are shaped into - M
 // -----------------------------------------------------------------------------
 class LeafNumberOfRows : public YangLeaf {
  public:
   LeafNumberOfRows(uint32_t id);
   ~LeafNumberOfRows();

 }; // LeafNumberOfRows

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/number-of-columns
 // Description: Number of columns array elements are shaped into - N
 // -----------------------------------------------------------------------------
 class LeafNumberOfColumns : public YangLeaf {
  public:
   LeafNumberOfColumns(uint32_t id);
   ~LeafNumberOfColumns();

 }; // LeafNumberOfColumns

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/number-of-array-layers
 // Description: Number of array layers array elements are shaped into - Q
 // -----------------------------------------------------------------------------
 class LeafNumberOfArrayLayers : public YangLeaf {
  public:
   LeafNumberOfArrayLayers(uint32_t id);
   ~LeafNumberOfArrayLayers();

 }; // LeafNumberOfArrayLayers

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/horizontal-spacing
 // Description: Average distance between centers of nearby AE in horizontal
 // direction (in array coordinates system)
 // -----------------------------------------------------------------------------
 class LeafHorizontalSpacing : public YangLeaf {
  public:
   LeafHorizontalSpacing(uint32_t id);
   ~LeafHorizontalSpacing();

 }; // LeafHorizontalSpacing

 // -----------------------------------------------------------------------------
 // Leaf:        /parameters/vertical-spacing
 // Description: Average distance between centers of nearby AE in vertical
 // direction (in array coordinates system)
 // -----------------------------------------------------------------------------
 class LeafVerticalSpacing : public YangLeaf {
  public:
   LeafVerticalSpacing(uint32_t id);
   ~LeafVerticalSpacing();

 }; // LeafVerticalSpacing

 // -----------------------------------------------------------------------------
 // Reference:   /parameters/band-number
 // Description: This parameter informing which frequency band particular
 // antenna
 //              array is serving for.
 //              Intended use is to deal with multiband solutions.
 // -----------------------------------------------------------------------------
 class RefBandNumber : public YangReference {
  public:
   RefBandNumber(uint32_t id);
   ~RefBandNumber();

 }; // RefBandNumber

 // -----------------------------------------------------------------------------
 // Container:   /parameters/normal-vector-direction
 // Description: Counter-clockwise rotation around z and y axis.
 // -----------------------------------------------------------------------------
 class CntNormalVectorDirection : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_AZIMUTH_ANGLE, // LeafAzimuthAngle
     ITEM_ZENITH_ANGLE, // LeafZenithAngle
   };

   CntNormalVectorDirection(uint32_t id);
   ~CntNormalVectorDirection();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/normal-vector-direction/azimuth-angle
   // Description: Azimuth angle, counter-clockwise rotation around z-axis.
   // Value 'zero' points to broad-side, value '90' points to y-axis
   // -----------------------------------------------------------------------------
   class LeafAzimuthAngle : public YangLeaf {
    public:
     LeafAzimuthAngle(uint32_t id);
     ~LeafAzimuthAngle();

   }; // LeafAzimuthAngle

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/normal-vector-direction/zenith-angle
   // Description: Zenith angle, counter-clockwise rotation around y-axis. Value
   // 'zero' points to zenith, value '90' points to horizon
   // -----------------------------------------------------------------------------
   class LeafZenithAngle : public YangLeaf {
    public:
     LeafZenithAngle(uint32_t id);
     ~LeafZenithAngle();

   }; // LeafZenithAngle

 }; // CntNormalVectorDirection

 // -----------------------------------------------------------------------------
 // Container:   /parameters/leftmost-bottom-array-element-position
 // Description: Structure describing position of leftmost, bottom array
 // element.
 // -----------------------------------------------------------------------------
 class CntLeftmostBottomArrayElementPosition : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_X, // LeafX
     ITEM_Y, // LeafY
     ITEM_Z, // LeafZ
   };

   CntLeftmostBottomArrayElementPosition(uint32_t id);
   ~CntLeftmostBottomArrayElementPosition();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/leftmost-bottom-array-element-position/x
   // Description: X dimension of position of leftmost, bottom array element
   // -----------------------------------------------------------------------------
   class LeafX : public YangLeaf {
    public:
     LeafX(uint32_t id);
     ~LeafX();

   }; // LeafX

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/leftmost-bottom-array-element-position/y
   // Description: Y dimension of position of leftmost, bottom array element
   // -----------------------------------------------------------------------------
   class LeafY : public YangLeaf {
    public:
     LeafY(uint32_t id);
     ~LeafY();

   }; // LeafY

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/leftmost-bottom-array-element-position/z
   // Description: Z dimension of position of leftmost, bottom array element
   // -----------------------------------------------------------------------------
   class LeafZ : public YangLeaf {
    public:
     LeafZ(uint32_t id);
     ~LeafZ();

   }; // LeafZ

 }; // CntLeftmostBottomArrayElementPosition

 // -----------------------------------------------------------------------------
 // List:        /parameters/polarisations
 // Description: List of supported polarisations.
 // -----------------------------------------------------------------------------
 class LstPolarisations : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_P, // LeafP
     ITEM_POLARISATION, // LeafPolarisation
   };

   LstPolarisations(uint32_t id);
   ~LstPolarisations();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/polarisations/p
   // Description: Polarisation index. See CUS-plane
   // -----------------------------------------------------------------------------
   class LeafP : public YangLeaf {
    public:
     LeafP(uint32_t id);
     ~LeafP();

   }; // LeafP

   // -----------------------------------------------------------------------------
   // Leaf:        /parameters/polarisations/polarisation
   // Description: Type of polarisation supported by array.
   // -----------------------------------------------------------------------------
   class LeafPolarisation : public YangLeaf {
    public:
     // Type of polarisation supported by array.
     enum class Polarisation_E : uint32_t {

       Num_Polarisation_E
     };

     LeafPolarisation(uint32_t id);
     ~LeafPolarisation();

   }; // LeafPolarisation

 }; // LstPolarisations

}; // GrpParameters

// -----------------------------------------------------------------------------
// Grouping:    /array-choice
// Description: Elements which groups choice for antenna type
// -----------------------------------------------------------------------------
class GrpArrayChoice : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ANTENNA_TYPE, // ChoiceAntennaType
 };

 GrpArrayChoice(uint32_t id);
 ~GrpArrayChoice();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Choice:      /array-choice/antenna-type
 // Description: Choice for antenna type
 // -----------------------------------------------------------------------------
 class ChoiceAntennaType : public YangChoice {
  public:
   // Choice Option
   enum : uint32_t {
     ITEM_TX, // OptTx
     ITEM_RX, // OptRx
   };

   ChoiceAntennaType(uint32_t id);
   ~ChoiceAntennaType();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Option: /array-choice/antenna-type[tx]
   // -----------------------------------------------------------------------------
   class OptTx : public YangChoiceOption {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_TX_ARRAY_NAME, // RefTxArrayName
     };

     OptTx(uint32_t id);
     ~OptTx();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Reference:   /array-choice/antenna-type[tx]/tx-array-name
     // Description: Leafref to tx array if such is chosen
     // -----------------------------------------------------------------------------
     class RefTxArrayName : public YangReference {
      public:
       RefTxArrayName(uint32_t id);
       ~RefTxArrayName();

     }; // RefTxArrayName

   }; // OptTx

   // -----------------------------------------------------------------------------
   // Option: /array-choice/antenna-type[rx]
   // -----------------------------------------------------------------------------
   class OptRx : public YangChoiceOption {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_RX_ARRAY_NAME, // RefRxArrayName
     };

     OptRx(uint32_t id);
     ~OptRx();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Reference:
     // /array-choice/antenna-type[rx]/rx-array-name
     // Description: Leafref to rx array if such is chosen
     // -----------------------------------------------------------------------------
     class RefRxArrayName : public YangReference {
      public:
       RefRxArrayName(uint32_t id);
       ~RefRxArrayName();

     }; // RefRxArrayName

   }; // OptRx

 }; // ChoiceAntennaType

}; // GrpArrayChoice

// -----------------------------------------------------------------------------
// Grouping:    /scs-config
// Description: It groups all parameters related to SCS configuration
// -----------------------------------------------------------------------------
class GrpScsConfig : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_FRAME_STRUCTURE, // LeafFrameStructure
   ITEM_CP_TYPE, // LeafCpType
   ITEM_CP_LENGTH, // LeafCpLength
   ITEM_CP_LENGTH_OTHER, // LeafCpLengthOther
   ITEM_OFFSET_TO_ABSOLUTE_FREQUENCY_CENTER, // LeafOffsetToAbsoluteFrequencyCenter
   ITEM_NUMBER_OF_PRB_PER_SCS, // LstNumberOfPrbPerScs
 };

 GrpScsConfig(uint32_t id);
 ~GrpScsConfig();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-config/frame-structure
 // Description: This parameter defines the frame structure. The first 4 bits
 // define the FFT/iFFT size
 //              being used for all IQ data processing related to this message.
 //              The second 4 bits define the sub carrier spacing as well as the
 //              number of slots per 1ms sub-frame according to 3GPP TS 38.211,
 //              taking for completeness also 3GPP TS 36.211 into account
 // -----------------------------------------------------------------------------
 class LeafFrameStructure : public YangLeaf {
  public:
   LeafFrameStructure(uint32_t id);
   ~LeafFrameStructure();

 }; // LeafFrameStructure

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-config/cp-type
 // Description: Provides type of CP (cyclic prefix) if section type 3 is not
 // used or type of CP cannot be determined from cpLength.
 // -----------------------------------------------------------------------------
 class LeafCpType : public YangLeaf {
  public:
   // Provides type of CP (cyclic prefix) if section type 3 is not used or type
   // of CP cannot be determined from cpLength.
   enum class CpType_E : uint32_t {
     NORMAL, // Normal cyclic prefix
     EXTENDED, // Extended cyclic prefix

     Num_CpType_E
   };

   LeafCpType(uint32_t id);
   ~LeafCpType();

 }; // LeafCpType

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-config/cp-length
 // Description: Used for symbol 0 for NR & LTE, and symbol 7*2u for NR.
 //              See CUS-plane
 // -----------------------------------------------------------------------------
 class LeafCpLength : public YangLeaf {
  public:
   LeafCpLength(uint32_t id);
   ~LeafCpLength();

 }; // LeafCpLength

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-config/cp-length-other
 // Description: Used for other symbols than by cp-length above
 // -----------------------------------------------------------------------------
 class LeafCpLengthOther : public YangLeaf {
  public:
   LeafCpLengthOther(uint32_t id);
   ~LeafCpLengthOther();

 }; // LeafCpLengthOther

 // -----------------------------------------------------------------------------
 // Leaf:        /scs-config/offset-to-absolute-frequency-center
 // Description: This provides value of freqOffset to be used if section type 3
 // is not used. See freqOffset in CUS-plane.
 // -----------------------------------------------------------------------------
 class LeafOffsetToAbsoluteFrequencyCenter : public YangLeaf {
  public:
   LeafOffsetToAbsoluteFrequencyCenter(uint32_t id);
   ~LeafOffsetToAbsoluteFrequencyCenter();

 }; // LeafOffsetToAbsoluteFrequencyCenter

 // -----------------------------------------------------------------------------
 // List:        /scs-config/number-of-prb-per-scs
 // Description: List of configured for each SCS that will be used.
 // -----------------------------------------------------------------------------
 class LstNumberOfPrbPerScs : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_SCS, // LeafScs
     ITEM_NUMBER_OF_PRB, // LeafNumberOfPrb
   };

   LstNumberOfPrbPerScs(uint32_t id);
   ~LstNumberOfPrbPerScs();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /scs-config/number-of-prb-per-scs/scs
   // Description: Value corresponds to SCS values defined for frameStructure in
   // C-plane.
   //              Note: set of allowed values is restricted by SCS derived from
   //              values in supported-frame-structures.
   // -----------------------------------------------------------------------------
   class LeafScs : public YangLeaf {
    public:
     // Value corresponds to SCS values defined for frameStructure in C-plane.
     // Note: set of allowed values is restricted by SCS derived from values in
     // supported-frame-structures.
     enum class Scs_E : uint32_t {

       Num_Scs_E
     };

     LeafScs(uint32_t id);
     ~LeafScs();

   }; // LeafScs

   // -----------------------------------------------------------------------------
   // Leaf:        /scs-config/number-of-prb-per-scs/number-of-prb
   // Description: Determines max number of PRBs that will be used in all
   // sections per one symbol.
   //              This is affecting allocation of resources to endpoint. Value
   //              shall not exceed constrains defined by max-prb-per-symbol of
   //              endpoint type. In addition sum (over all used epoints within
   //              a group of endpoints sharing resources) of number-of-prb
   //              rounded up to nearest value from
   //              prb-capacity-allocation-granularity shall not exceed
   //              max-prb-per-symbol of the group.
   // -----------------------------------------------------------------------------
   class LeafNumberOfPrb : public YangLeaf {
    public:
     LeafNumberOfPrb(uint32_t id);
     ~LeafNumberOfPrb();

   }; // LeafNumberOfPrb

 }; // LstNumberOfPrbPerScs

}; // GrpScsConfig

// -----------------------------------------------------------------------------
// Grouping:    /tx-common-array-carrier-elements
// Description: This grouping contains all common parameters for
// tx-array-carriers and rx-array-carriers
// -----------------------------------------------------------------------------
class GrpTxCommonArrayCarrierElements : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ABSOLUTE_FREQUENCY_CENTER, // LeafAbsoluteFrequencyCenter
   ITEM_CENTER_OF_CHANNEL_BANDWIDTH, // LeafCenterOfChannelBandwidth
   ITEM_CHANNEL_BANDWIDTH, // LeafChannelBandwidth
   ITEM_ACTIVE, // LeafActive
   ITEM_STATE, // LeafState
   ITEM_TYPE, // LeafType
   ITEM_DUPLEX_SCHEME, // LeafDuplexScheme
   ITEM_RW_DUPLEX_SCHEME, // RefRwDuplexScheme
   ITEM_RW_TYPE, // RefRwType
 };

 GrpTxCommonArrayCarrierElements(uint32_t id);
 ~GrpTxCommonArrayCarrierElements();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/absolute-frequency-center
 // Description: Absolute Radio Frequency Channel Number - indirectly indicates
 // RF center carrier frequency of signal.
 //              Reflected in arfcn.
 // -----------------------------------------------------------------------------
 class LeafAbsoluteFrequencyCenter : public YangLeaf {
  public:
   LeafAbsoluteFrequencyCenter(uint32_t id);
   ~LeafAbsoluteFrequencyCenter();

 }; // LeafAbsoluteFrequencyCenter

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/center-of-channel-bandwidth
 // Description: Center frequency of channel bandwidth in Hz. Common for all
 // numerologies.
 // -----------------------------------------------------------------------------
 class LeafCenterOfChannelBandwidth : public YangLeaf {
  public:
   LeafCenterOfChannelBandwidth(uint32_t id);
   ~LeafCenterOfChannelBandwidth();

 }; // LeafCenterOfChannelBandwidth

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/channel-bandwidth
 // Description: Width of carrier given in Hertz
 // -----------------------------------------------------------------------------
 class LeafChannelBandwidth : public YangLeaf {
  public:
   LeafChannelBandwidth(uint32_t id);
   ~LeafChannelBandwidth();

 }; // LeafChannelBandwidth

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/active
 // Description: Indicates if transmission is enabled for this array carriers.
 // Note that Netconf server uses state parameter
 //              to indicate actual state of array carriers operation. When
 //              array carriers is in sleep status, Netconf server rejects all
 //              other operation request to tx-array-carriers object except
 //              either request to change from sleep to active status or delete
 //              MO operation (see 4.8) to the object.
 // -----------------------------------------------------------------------------
 class LeafActive : public YangLeaf {
  public:
   // Indicates if transmission is enabled for this array carriers. Note that
   // Netconf server uses state parameter to indicate actual state of array
   // carriers operation. When array carriers is in sleep status, Netconf server
   // rejects all other operation request to tx-array-carriers object except
   // either request to change from sleep to active status or delete MO
   // operation (see 4.8) to the object.
   enum class Active_E : uint32_t {
     INACTIVE, // carrier does not provide signal - transmission is disabled
     SLEEP, // carrier is fully configured and was active but is energy saving
            // mode
     ACTIVE, // carrier is fully configured and properly providing the signal

     Num_Active_E
   };

   LeafActive(uint32_t id);
   ~LeafActive();

 }; // LeafActive

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/state
 // Description: Indicates state of array carriers activation operation
 // -----------------------------------------------------------------------------
 class LeafState : public YangLeaf {
  public:
   // Indicates state of array carriers activation operation
   enum class State_E : uint32_t {
     DISABLED, // array carrier is not active - transmission of signal is
               // disabled.
     BUSY, // array carrier is processing an operation requested by change of
           // active parameter. When array carriers is BUSY the transmission of
           // signal is not guaranteed.
     READY, // array carrier had completed activation operation - is active and
            // transmission of signal is ongoing.

     Num_State_E
   };

   LeafState(uint32_t id);
   ~LeafState();

 }; // LeafState

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/type
 // Description: Type of carrier. Indicates array-carrier technology.
 // -----------------------------------------------------------------------------
 class LeafType : public YangLeaf {
  public:
   // Type of carrier. Indicates array-carrier technology.
   enum class Type_E : uint32_t {
     NR, // 5G technology
     LTE, // LTE technology

     Num_Type_E
   };

   LeafType(uint32_t id);
   ~LeafType();

 }; // LeafType

 // -----------------------------------------------------------------------------
 // Leaf:        /tx-common-array-carrier-elements/duplex-scheme
 // Description: Type of duplex scheme O-RU supports.
 // -----------------------------------------------------------------------------
 class LeafDuplexScheme : public YangLeaf {
  public:
   // Type of duplex scheme O-RU supports.
   enum class DuplexScheme_E : uint32_t {
     TDD, // TDD scheme
     FDD, // FDD scheme

     Num_DuplexScheme_E
   };

   LeafDuplexScheme(uint32_t id);
   ~LeafDuplexScheme();

 }; // LeafDuplexScheme

 // -----------------------------------------------------------------------------
 // Reference:   /tx-common-array-carrier-elements/rw-duplex-scheme
 // Description: Config true type of duplex scheme.
 // -----------------------------------------------------------------------------
 class RefRwDuplexScheme : public YangReference {
  public:
   RefRwDuplexScheme(uint32_t id);
   ~RefRwDuplexScheme();

 }; // RefRwDuplexScheme

 // -----------------------------------------------------------------------------
 // Reference:   /tx-common-array-carrier-elements/rw-type
 // Description: Config true type of carrier.
 // -----------------------------------------------------------------------------
 class RefRwType : public YangReference {
  public:
   RefRwType(uint32_t id);
   ~RefRwType();

 }; // RefRwType

}; // GrpTxCommonArrayCarrierElements

// -----------------------------------------------------------------------------
// Grouping:    /rx-common-array-carrier-elements
// Description: This grouping contains all common parameters for
// tx-array-carriers and rx-array-carriers
// -----------------------------------------------------------------------------
class GrpRxCommonArrayCarrierElements : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ABSOLUTE_FREQUENCY_CENTER, // LeafAbsoluteFrequencyCenter
   ITEM_CENTER_OF_CHANNEL_BANDWIDTH, // LeafCenterOfChannelBandwidth
   ITEM_CHANNEL_BANDWIDTH, // LeafChannelBandwidth
   ITEM_ACTIVE, // LeafActive
   ITEM_STATE, // LeafState
   ITEM_TYPE, // LeafType
   ITEM_DUPLEX_SCHEME, // LeafDuplexScheme
 };

 GrpRxCommonArrayCarrierElements(uint32_t id);
 ~GrpRxCommonArrayCarrierElements();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/absolute-frequency-center
 // Description: Absolute Radio Frequency Channel Number - indirectly indicates
 // RF center carrier frequency of signal.
 //              Reflected in arfcn.
 // -----------------------------------------------------------------------------
 class LeafAbsoluteFrequencyCenter : public YangLeaf {
  public:
   LeafAbsoluteFrequencyCenter(uint32_t id);
   ~LeafAbsoluteFrequencyCenter();

 }; // LeafAbsoluteFrequencyCenter

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/center-of-channel-bandwidth
 // Description: Center frequency of channel bandwidth in Hz. Common for all
 // numerologies.
 // -----------------------------------------------------------------------------
 class LeafCenterOfChannelBandwidth : public YangLeaf {
  public:
   LeafCenterOfChannelBandwidth(uint32_t id);
   ~LeafCenterOfChannelBandwidth();

 }; // LeafCenterOfChannelBandwidth

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/channel-bandwidth
 // Description: Width of carrier given in Hertz
 // -----------------------------------------------------------------------------
 class LeafChannelBandwidth : public YangLeaf {
  public:
   LeafChannelBandwidth(uint32_t id);
   ~LeafChannelBandwidth();

 }; // LeafChannelBandwidth

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/active
 // Description: Indicates if transmission is enabled for this array carriers.
 // Note that Netconf server uses state parameter
 //              to indicate actual state of array carriers operation. When
 //              array carriers is in sleep status, Netconf server rejects all
 //              other operation request to tx-array-carriers object except
 //              either request to change from sleep to active status or delete
 //              MO operation (see 4.8) to the object.
 // -----------------------------------------------------------------------------
 class LeafActive : public YangLeaf {
  public:
   // Indicates if transmission is enabled for this array carriers. Note that
   // Netconf server uses state parameter to indicate actual state of array
   // carriers operation. When array carriers is in sleep status, Netconf server
   // rejects all other operation request to tx-array-carriers object except
   // either request to change from sleep to active status or delete MO
   // operation (see 4.8) to the object.
   enum class Active_E : uint32_t {
     INACTIVE, // carrier does not provide signal - transmission is disabled
     SLEEP, // carrier is fully configured and was active but is energy saving
            // mode
     ACTIVE, // carrier is fully configured and properly providing the signal

     Num_Active_E
   };

   LeafActive(uint32_t id);
   ~LeafActive();

 }; // LeafActive

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/state
 // Description: Indicates state of array carriers activation operation
 // -----------------------------------------------------------------------------
 class LeafState : public YangLeaf {
  public:
   // Indicates state of array carriers activation operation
   enum class State_E : uint32_t {
     DISABLED, // array carrier is not active - transmission of signal is
               // disabled.
     BUSY, // array carrier is processing an operation requested by change of
           // active parameter. When array carriers is BUSY the transmission of
           // signal is not guaranteed.
     READY, // array carrier had completed activation operation - is active and
            // transmission of signal is ongoing.

     Num_State_E
   };

   LeafState(uint32_t id);
   ~LeafState();

 }; // LeafState

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/type
 // Description: Type of carrier. Indicates array-carrier technology.
 // -----------------------------------------------------------------------------
 class LeafType : public YangLeaf {
  public:
   // Type of carrier. Indicates array-carrier technology.
   enum class Type_E : uint32_t {
     NR, // 5G technology
     LTE, // LTE technology

     Num_Type_E
   };

   LeafType(uint32_t id);
   ~LeafType();

 }; // LeafType

 // -----------------------------------------------------------------------------
 // Leaf:        /rx-common-array-carrier-elements/duplex-scheme
 // Description: Type of duplex scheme O-RU supports.
 // -----------------------------------------------------------------------------
 class LeafDuplexScheme : public YangLeaf {
  public:
   // Type of duplex scheme O-RU supports.
   enum class DuplexScheme_E : uint32_t {
     TDD, // TDD scheme
     FDD, // FDD scheme

     Num_DuplexScheme_E
   };

   LeafDuplexScheme(uint32_t id);
   ~LeafDuplexScheme();

 }; // LeafDuplexScheme

}; // GrpRxCommonArrayCarrierElements

// -----------------------------------------------------------------------------
// Grouping:    /endpoint-section-capacity
// Description: Parameters describing section capacity where section is undestood as number of different sectionId values
// -----------------------------------------------------------------------------
class GrpEndpointSectionCapacity : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_CONTROL_SECTIONS_PER_DATA_SECTION, // LeafMaxControlSectionsPerDataSection
   ITEM_MAX_SECTIONS_PER_SYMBOL, // LeafMaxSectionsPerSymbol
   ITEM_MAX_SECTIONS_PER_SLOT, // LeafMaxSectionsPerSlot
 };

 GrpEndpointSectionCapacity(uint32_t id);
 ~GrpEndpointSectionCapacity();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf: /endpoint-section-capacity/max-control-sections-per-data-section
 // Description: Max number of C-plane sections (C-plane section is part of
 // C-plane message that carries 'section fields')
 //              referring to same U-plane section (U-plane section is part of
 //              U-plane message that carries 'section header fields' and 'PRB
 //              fields') that is supported by endpoint. Note that additional
 //              limitations specific for each section type apply on top of this
 //              number.
 // -----------------------------------------------------------------------------
 class LeafMaxControlSectionsPerDataSection : public YangLeaf {
  public:
   LeafMaxControlSectionsPerDataSection(uint32_t id);
   ~LeafMaxControlSectionsPerDataSection();

 }; // LeafMaxControlSectionsPerDataSection

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-section-capacity/max-sections-per-symbol
 // Description: Max number of sections within one symbol that can be processed
 // by endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity
 // -----------------------------------------------------------------------------
 class LeafMaxSectionsPerSymbol : public YangLeaf {
  public:
   LeafMaxSectionsPerSymbol(uint32_t id);
   ~LeafMaxSectionsPerSymbol();

 }; // LeafMaxSectionsPerSymbol

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-section-capacity/max-sections-per-slot
 // Description: Max number of sections within one slot that can be processed by
 // endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity.
 // -----------------------------------------------------------------------------
 class LeafMaxSectionsPerSlot : public YangLeaf {
  public:
   LeafMaxSectionsPerSlot(uint32_t id);
   ~LeafMaxSectionsPerSlot();

 }; // LeafMaxSectionsPerSlot

}; // GrpEndpointSectionCapacity

// -----------------------------------------------------------------------------
// Grouping:    /endpoint-beam-capacity
// Description: Parameters describing beam capacity where number of beams is understood as number of different beamId values
// -----------------------------------------------------------------------------
class GrpEndpointBeamCapacity : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_BEAMS_PER_SYMBOL, // LeafMaxBeamsPerSymbol
   ITEM_MAX_BEAMS_PER_SLOT, // LeafMaxBeamsPerSlot
 };

 GrpEndpointBeamCapacity(uint32_t id);
 ~GrpEndpointBeamCapacity();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-beam-capacity/max-beams-per-symbol
 // Description: Max number of beams within one symbol that can be processed by
 // endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity
 // -----------------------------------------------------------------------------
 class LeafMaxBeamsPerSymbol : public YangLeaf {
  public:
   LeafMaxBeamsPerSymbol(uint32_t id);
   ~LeafMaxBeamsPerSymbol();

 }; // LeafMaxBeamsPerSymbol

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-beam-capacity/max-beams-per-slot
 // Description: Max number of beams within one slot that can be processed by
 // endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity
 // -----------------------------------------------------------------------------
 class LeafMaxBeamsPerSlot : public YangLeaf {
  public:
   LeafMaxBeamsPerSlot(uint32_t id);
   ~LeafMaxBeamsPerSlot();

 }; // LeafMaxBeamsPerSlot

}; // GrpEndpointBeamCapacity

// -----------------------------------------------------------------------------
// Grouping:    /endpoint-prb-capacity
// Description: Attributes presenting processing capacity related to PRB.
// -----------------------------------------------------------------------------
class GrpEndpointPrbCapacity : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_PRB_PER_SYMBOL, // LeafMaxPrbPerSymbol
 };

 GrpEndpointPrbCapacity(uint32_t id);
 ~GrpEndpointPrbCapacity();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-prb-capacity/max-prb-per-symbol
 // Description: Max number of prbs within one symbol that can be processed by
 // endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity
 // -----------------------------------------------------------------------------
 class LeafMaxPrbPerSymbol : public YangLeaf {
  public:
   LeafMaxPrbPerSymbol(uint32_t id);
   ~LeafMaxPrbPerSymbol();

 }; // LeafMaxPrbPerSymbol

}; // GrpEndpointPrbCapacity

// -----------------------------------------------------------------------------
// Grouping:    /endpoint-numerology-capacity
// Description: Attributes presenting processing capacity related to numerology.
//
//              This leaf contains valid data only when
//              multiple-numerology-supported is set to true.
// -----------------------------------------------------------------------------
class GrpEndpointNumerologyCapacity : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_MAX_NUMEROLOGIES_PER_SYMBOL, // LeafMaxNumerologiesPerSymbol
 };

 GrpEndpointNumerologyCapacity(uint32_t id);
 ~GrpEndpointNumerologyCapacity();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /endpoint-numerology-capacity/max-numerologies-per-symbol
 // Description: Max number of numerologies within one symbol that can be
 // processed by endpoint
 //              or processed collectively by group of endpoints sharing
 //              capacity
 // -----------------------------------------------------------------------------
 class LeafMaxNumerologiesPerSymbol : public YangLeaf {
  public:
   LeafMaxNumerologiesPerSymbol(uint32_t id);
   ~LeafMaxNumerologiesPerSymbol();

 }; // LeafMaxNumerologiesPerSymbol

}; // GrpEndpointNumerologyCapacity

// -----------------------------------------------------------------------------
// Grouping:    /uplane-conf-group
// Description: Grouping for uplane configuration related parameters
// -----------------------------------------------------------------------------
class GrpUplaneConfGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_LOW_LEVEL_TX_LINKS, // LstLowLevelTxLinks
   ITEM_LOW_LEVEL_RX_LINKS, // LstLowLevelRxLinks
   ITEM_ENDPOINT_TYPES, // LstEndpointTypes
   ITEM_ENDPOINT_CAPACITY_SHARING_GROUPS, // LstEndpointCapacitySharingGroups
   ITEM_STATIC_LOW_LEVEL_TX_ENDPOINTS, // LstStaticLowLevelTxEndpoints
   ITEM_STATIC_LOW_LEVEL_RX_ENDPOINTS, // LstStaticLowLevelRxEndpoints
   ITEM_LOW_LEVEL_TX_ENDPOINTS, // LstLowLevelTxEndpoints
   ITEM_LOW_LEVEL_RX_ENDPOINTS, // LstLowLevelRxEndpoints
   ITEM_TX_ARRAY_CARRIERS, // LstTxArrayCarriers
   ITEM_RX_ARRAY_CARRIERS, // LstRxArrayCarriers
   ITEM_TX_ARRAYS, // LstTxArrays
   ITEM_RX_ARRAYS, // LstRxArrays
   ITEM_RELATIONS, // LstRelations
 };

 GrpUplaneConfGroup(uint32_t id);
 ~GrpUplaneConfGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/low-level-tx-links
 // Description: Object model for low-level-tx-link configuration
 // -----------------------------------------------------------------------------
 class LstLowLevelTxLinks : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PROCESSING_ELEMENT, // RefProcessingElement
     ITEM_TX_ARRAY_CARRIER, // RefTxArrayCarrier
     ITEM_LOW_LEVEL_TX_ENDPOINT, // RefLowLevelTxEndpoint
   };

   LstLowLevelTxLinks(uint32_t id);
   ~LstLowLevelTxLinks();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/low-level-tx-links/name
   // Description: Unique name of low-level-tx-link object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-tx-links/processing-element
   // Description: Contains name of processing-element to be used as transport
   // by low-level-tx-link
   // -----------------------------------------------------------------------------
   class RefProcessingElement : public YangReference {
    public:
     RefProcessingElement(uint32_t id);
     ~RefProcessingElement();

   }; // RefProcessingElement

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-tx-links/tx-array-carrier
   // Description: Contains name of tx-array-carriers MO to be used as transport
   // by low-level-tx-link
   // -----------------------------------------------------------------------------
   class RefTxArrayCarrier : public YangReference {
    public:
     RefTxArrayCarrier(uint32_t id);
     ~RefTxArrayCarrier();

   }; // RefTxArrayCarrier

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-tx-links/low-level-tx-endpoint
   // Description: Contains name of low-level-tx-endpoints MO to be used as
   // transport by low-level-tx-link
   // -----------------------------------------------------------------------------
   class RefLowLevelTxEndpoint : public YangReference {
    public:
     RefLowLevelTxEndpoint(uint32_t id);
     ~RefLowLevelTxEndpoint();

   }; // RefLowLevelTxEndpoint

 }; // LstLowLevelTxLinks

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/low-level-rx-links
 // Description: Object model for low-level-rx-links configuration
 // -----------------------------------------------------------------------------
 class LstLowLevelRxLinks : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PROCESSING_ELEMENT, // RefProcessingElement
     ITEM_RX_ARRAY_CARRIER, // RefRxArrayCarrier
     ITEM_LOW_LEVEL_RX_ENDPOINT, // RefLowLevelRxEndpoint
     ITEM_USER_PLANE_UPLINK_MARKING, // RefUserPlaneUplinkMarking
   };

   LstLowLevelRxLinks(uint32_t id);
   ~LstLowLevelRxLinks();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/low-level-rx-links/name
   // Description: Unique name of low-level-rx-links object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-rx-links/processing-element
   // Description: Contains name of processing-element to be used as transport
   // by LowLevelTxLink
   // -----------------------------------------------------------------------------
   class RefProcessingElement : public YangReference {
    public:
     RefProcessingElement(uint32_t id);
     ~RefProcessingElement();

   }; // RefProcessingElement

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-rx-links/rx-array-carrier
   // Description: Contains name of rx-array-carriers MO to be used as transport
   // by low-level-rx-links
   // -----------------------------------------------------------------------------
   class RefRxArrayCarrier : public YangReference {
    public:
     RefRxArrayCarrier(uint32_t id);
     ~RefRxArrayCarrier();

   }; // RefRxArrayCarrier

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-rx-links/low-level-rx-endpoint
   // Description: Contains name of low-level-rx-endpoints MO to be used as
   // transport by low-level-rx-links
   // -----------------------------------------------------------------------------
   class RefLowLevelRxEndpoint : public YangReference {
    public:
     RefLowLevelRxEndpoint(uint32_t id);
     ~RefLowLevelRxEndpoint();

   }; // RefLowLevelRxEndpoint

   // -----------------------------------------------------------------------------
   // Reference: /uplane-conf-group/low-level-rx-links/user-plane-uplink-marking
   // Description: Parameter to set the non-default marking for user-plane
   // -----------------------------------------------------------------------------
   class RefUserPlaneUplinkMarking : public YangReference {
    public:
     RefUserPlaneUplinkMarking(uint32_t id);
     ~RefUserPlaneUplinkMarking();

   }; // RefUserPlaneUplinkMarking

 }; // LstLowLevelRxLinks

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/endpoint-types
 // Description: Properties of endpoint that are common to multiple endpoints if
 // such are identified
 // -----------------------------------------------------------------------------
 class LstEndpointTypes : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_ID, // LeafId
     ITEM_MANAGED_DELAY_SUPPORT, // LeafManagedDelaySupport
     ITEM_MULTIPLE_NUMEROLOGY_SUPPORTED, // LeafMultipleNumerologySupported
     ITEM_MAX_NUMEROLOGY_CHANGE_DURATION, // LeafMaxNumerologyChangeDuration
     ITEM_SUPPORTED_FRAME_STRUCTURES, // LstSupportedFrameStructures
     ITEM_PRB_CAPACITY_ALLOCATION_GRANULARITY, // LstPrbCapacityAllocationGranularity
     ITEM_SUPPORTED_SECTION_TYPES, // LstSupportedSectionTypes
     ITEM_ENDPOINT_SECTION_CAPACITY, // Use GrpEndpointSectionCapacity
     ITEM_ENDPOINT_BEAM_CAPACITY, // Use GrpEndpointBeamCapacity
     ITEM_ENDPOINT_PRB_CAPACITY, // Use GrpEndpointPrbCapacity
     ITEM_ENDPOINT_NUMEROLOGY_CAPACITY, // Use GrpEndpointNumerologyCapacity
   };

   LstEndpointTypes(uint32_t id);
   ~LstEndpointTypes();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/endpoint-types/id
   // Description: Identifies type of endpoints sharing same properties. Values
   // shall start with 0 and shall be allocated without gaps.
   // -----------------------------------------------------------------------------
   class LeafId : public YangLeaf {
    public:
     LeafId(uint32_t id);
     ~LeafId();

   }; // LeafId

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/endpoint-types/managed-delay-support
   // Description: Type of delay supported by the endpoint
   // -----------------------------------------------------------------------------
   class LeafManagedDelaySupport : public YangLeaf {
    public:
     // Type of delay supported by the endpoint
     enum class ManagedDelaySupport_E : uint32_t {
       MANAGED, // Time managed delays are supported
       NON_MANAGED, // Non time managed delays are not supported
       BOTH, // Both time managed and non time managed delays are supported

       Num_ManagedDelaySupport_E
     };

     LeafManagedDelaySupport(uint32_t id);
     ~LeafManagedDelaySupport();

   }; // LeafManagedDelaySupport

   // -----------------------------------------------------------------------------
   // Leaf: /uplane-conf-group/endpoint-types/multiple-numerology-supported
   // Description: Indicates whether the endpoint type supports multiple
   // numerologies
   // -----------------------------------------------------------------------------
   class LeafMultipleNumerologySupported : public YangLeaf {
    public:
     LeafMultipleNumerologySupported(uint32_t id);
     ~LeafMultipleNumerologySupported();

   }; // LeafMultipleNumerologySupported

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/endpoint-types/max-numerology-change-duration
   // Description: Maximum gap of endpoint operation that will be
   // caused by changing of
   //              numerology.
   //
   //              This time is required for reconfiguration and
   //              flushing of pipes.
   //
   //              This leaf contains valid data only when
   //              multiple-numerology-supported is set to true.
   // -----------------------------------------------------------------------------
   class LeafMaxNumerologyChangeDuration : public YangLeaf {
    public:
     LeafMaxNumerologyChangeDuration(uint32_t id);
     ~LeafMaxNumerologyChangeDuration();

   }; // LeafMaxNumerologyChangeDuration

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/endpoint-types/supported-frame-structures
   // Description: List of supported values of frame structure
   // -----------------------------------------------------------------------------
   class LstSupportedFrameStructures : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstSupportedFrameStructures(uint32_t id);
     ~LstSupportedFrameStructures();

     YangResult_E initialise(void);

   }; // LstSupportedFrameStructures

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/endpoint-types/prb-capacity-allocation-granularity
   // Description: List of capacity allocation steps. O-RU
   // allocates PRB capacity rounding it up to nearest value N
   //              from prb-capacity-allocation-granularity such
   //              that M >= number-of-prb-per-scs. See also
   //              number-of-prb-per-scs/number-of-prb.
   // -----------------------------------------------------------------------------
   class LstPrbCapacityAllocationGranularity : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstPrbCapacityAllocationGranularity(uint32_t id);
     ~LstPrbCapacityAllocationGranularity();

     YangResult_E initialise(void);

   }; // LstPrbCapacityAllocationGranularity

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/endpoint-types/supported-section-types
   // Description: Indicates section types and extensions endpoints
   // of this type support
   // -----------------------------------------------------------------------------
   class LstSupportedSectionTypes : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_SECTION_TYPE, // LeafSectionType
       ITEM_SUPPORTED_SECTION_EXTENSIONS, // LstSupportedSectionExtensions
     };

     LstSupportedSectionTypes(uint32_t id);
     ~LstSupportedSectionTypes();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /uplane-conf-group/endpoint-types/supported-section-types/section-type
     // Description: This parameter determines the characteristics
     // of U-plane data to be transferred or received from a beam
     // with one pattern id.
     // -----------------------------------------------------------------------------
     class LeafSectionType : public YangLeaf {
      public:
       LeafSectionType(uint32_t id);
       ~LeafSectionType();

     }; // LeafSectionType

     // -----------------------------------------------------------------------------
     // List:
     // /uplane-conf-group/endpoint-types/supported-section-types/supported-section-extensions
     // Description: This parameter provides the extension types
     // supported by the O-RU
     //              which provides additional parameters specific
     //              to the subject data extension
     // -----------------------------------------------------------------------------
     class LstSupportedSectionExtensions : public YangList {
      public:
       // Item IDs
       enum : uint32_t {};

       LstSupportedSectionExtensions(uint32_t id);
       ~LstSupportedSectionExtensions();

       YangResult_E initialise(void);

     }; // LstSupportedSectionExtensions

   }; // LstSupportedSectionTypes

 }; // LstEndpointTypes

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/endpoint-capacity-sharing-groups
 // Description: Represents groups of endpoints that share capacity.
 // Depending on O-RU implementation,
 //              processing resources that handle CU-plane (e.g. memory
 //              to keep sections and beams) could be allocated per
 //              endpoint or shared between several endpoints. To address
 //              this O-RU shall reports own capability per endpoint (see
 //              endpoint-types) and per group of endpoints sharing
 //              capacity. If endpoint is in multiple groups then
 //              resulting constraint is minimum over all groups. Note:
 //              values of parameters representing capacity that is not
 //              shared between endpoints in a group shall be set to max
 //              value of specific parameter; this effectively removes
 //              related constraint.
 //
 // -----------------------------------------------------------------------------
 class LstEndpointCapacitySharingGroups : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_ID, // LeafId
     ITEM_MAX_ENDPOINTS, // LeafMaxEndpoints
     ITEM_MAX_MANAGED_DELAY_ENDPOINTS, // LeafMaxManagedDelayEndpoints
     ITEM_MAX_NON_MANAGED_DELAY_ENDPOINTS, // LeafMaxNonManagedDelayEndpoints
     ITEM_ENDPOINT_SECTION_CAPACITY, // Use GrpEndpointSectionCapacity
     ITEM_ENDPOINT_BEAM_CAPACITY, // Use GrpEndpointBeamCapacity
     ITEM_ENDPOINT_PRB_CAPACITY, // Use GrpEndpointPrbCapacity
     ITEM_ENDPOINT_NUMEROLOGY_CAPACITY, // Use
                                        // GrpEndpointNumerologyCapacity
   };

   LstEndpointCapacitySharingGroups(uint32_t id);
   ~LstEndpointCapacitySharingGroups();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/endpoint-capacity-sharing-groups/id
   // Description: Identifies group of endpoints sharing resources.
   //              Values shall start with 0 and shall be allocated
   //              without gaps.
   // -----------------------------------------------------------------------------
   class LeafId : public YangLeaf {
    public:
     LeafId(uint32_t id);
     ~LeafId();

   }; // LeafId

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/endpoint-capacity-sharing-groups/max-endpoints
   // Description: Indicates how many endpoints in the group can be used4
   // simultaneously
   // -----------------------------------------------------------------------------
   class LeafMaxEndpoints : public YangLeaf {
    public:
     LeafMaxEndpoints(uint32_t id);
     ~LeafMaxEndpoints();

   }; // LeafMaxEndpoints

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/endpoint-capacity-sharing-groups/max-managed-delay-endpoints
   // Description: Number of endpoints supporting managed delay that can
   // be used (configured for use) at a time
   // -----------------------------------------------------------------------------
   class LeafMaxManagedDelayEndpoints : public YangLeaf {
    public:
     LeafMaxManagedDelayEndpoints(uint32_t id);
     ~LeafMaxManagedDelayEndpoints();

   }; // LeafMaxManagedDelayEndpoints

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/endpoint-capacity-sharing-groups/max-non-managed-delay-endpoints
   // Description: Number of endpoints supporting non-managed delay that
   // can be used (configured for use) at a time
   // -----------------------------------------------------------------------------
   class LeafMaxNonManagedDelayEndpoints : public YangLeaf {
    public:
     LeafMaxNonManagedDelayEndpoints(uint32_t id);
     ~LeafMaxNonManagedDelayEndpoints();

   }; // LeafMaxNonManagedDelayEndpoints

 }; // LstEndpointCapacitySharingGroups

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/static-low-level-tx-endpoints
 // Description: Object model for static-low-level-tx-endpoints
 // configuration
 // -----------------------------------------------------------------------------
 class LstStaticLowLevelTxEndpoints : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_ARRAY, // RefArray
     ITEM_ENDPOINT_TYPE, // RefEndpointType
     ITEM_RESTRICTED_INTERFACES, // LstRestrictedInterfaces
     ITEM_CAPACITY_SHARING_GROUPS, // LstCapacitySharingGroups
   };

   LstStaticLowLevelTxEndpoints(uint32_t id);
   ~LstStaticLowLevelTxEndpoints();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/static-low-level-tx-endpoints/name
   // Description: Unique name of static-low-level-tx-endpoints object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/static-low-level-tx-endpoints/array
   // Description: Contains distname of tx-arrays, particular
   // low-level-tx-endpoints is in hardware dependency with.
   //              Note: single instance of tx-arrays can be referenced
   //              by many instances of low-level-tx-endpoints (e.g. to
   //              allow DU to handle multiple fronthauls and multiple
   //              component carriers).
   // -----------------------------------------------------------------------------
   class RefArray : public YangReference {
    public:
     RefArray(uint32_t id);
     ~RefArray();

   }; // RefArray

   // -----------------------------------------------------------------------------
   // Reference:
   // /uplane-conf-group/static-low-level-tx-endpoints/endpoint-type
   // Description: Reference to endpoint type capabilities list element
   // supported by this endpoint
   // -----------------------------------------------------------------------------
   class RefEndpointType : public YangReference {
    public:
     RefEndpointType(uint32_t id);
     ~RefEndpointType();

   }; // RefEndpointType

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/static-low-level-tx-endpoints/restricted-interfaces
   // Description: Optionally used to indicate that a low-level link is
   // constrained to operate only via a subset of the available
   // interfaces.
   // -----------------------------------------------------------------------------
   class LstRestrictedInterfaces : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstRestrictedInterfaces(uint32_t id);
     ~LstRestrictedInterfaces();

     YangResult_E initialise(void);

   }; // LstRestrictedInterfaces

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/static-low-level-tx-endpoints/capacity-sharing-groups
   // Description: Reference to capacities of sharing-groups supported by
   // this endpoint
   // -----------------------------------------------------------------------------
   class LstCapacitySharingGroups : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstCapacitySharingGroups(uint32_t id);
     ~LstCapacitySharingGroups();

     YangResult_E initialise(void);

   }; // LstCapacitySharingGroups

 }; // LstStaticLowLevelTxEndpoints

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/static-low-level-rx-endpoints
 // Description: Object model for static-low-level-rx-endpoints
 // configuration
 // -----------------------------------------------------------------------------
 class LstStaticLowLevelRxEndpoints : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_ARRAY, // RefArray
     ITEM_ENDPOINT_TYPE, // RefEndpointType
     ITEM_RESTRICTED_INTERFACES, // LstRestrictedInterfaces
     ITEM_CAPACITY_SHARING_GROUPS, // LstCapacitySharingGroups
   };

   LstStaticLowLevelRxEndpoints(uint32_t id);
   ~LstStaticLowLevelRxEndpoints();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/static-low-level-rx-endpoints/name
   // Description: Unique name of static-low-level-rx-endpoints object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/static-low-level-rx-endpoints/array
   // Description: Contains distname of rx-arrays, particular
   // low-level-rx-endpoints is in hardware dependency with.
   //              Note: single instance of rx-arrays can be referenced
   //              by many instances of low-level-rx-endpoints (e.g. to
   //              allow DU to handle multiple fronthauls and multiple
   //              component carriers).
   // -----------------------------------------------------------------------------
   class RefArray : public YangReference {
    public:
     RefArray(uint32_t id);
     ~RefArray();

   }; // RefArray

   // -----------------------------------------------------------------------------
   // Reference:
   // /uplane-conf-group/static-low-level-rx-endpoints/endpoint-type
   // Description: Reference to endpoint type capabilities list element
   // supported by this endpoint
   // -----------------------------------------------------------------------------
   class RefEndpointType : public YangReference {
    public:
     RefEndpointType(uint32_t id);
     ~RefEndpointType();

   }; // RefEndpointType

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/static-low-level-rx-endpoints/restricted-interfaces
   // Description: Optionally used to indicate that a low-level link is
   // constrained to operate only via a subset of the available
   // interfaces.
   // -----------------------------------------------------------------------------
   class LstRestrictedInterfaces : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstRestrictedInterfaces(uint32_t id);
     ~LstRestrictedInterfaces();

     YangResult_E initialise(void);

   }; // LstRestrictedInterfaces

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/static-low-level-rx-endpoints/capacity-sharing-groups
   // Description: Reference to capacities of sharing-groups supported by
   // this endpoint
   // -----------------------------------------------------------------------------
   class LstCapacitySharingGroups : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstCapacitySharingGroups(uint32_t id);
     ~LstCapacitySharingGroups();

     YangResult_E initialise(void);

   }; // LstCapacitySharingGroups

 }; // LstStaticLowLevelRxEndpoints

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/low-level-tx-endpoints
 // Description: Object model for low-level-tx-endpoints configuration -
 // augmented static-low-level-tx-endpoints by local-address
 //              which cannot be added to static low-level-tx-endpoints
 //              as we cannot have modificable element in static object
 // -----------------------------------------------------------------------------
 class LstLowLevelTxEndpoints : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // RefName
     ITEM_COMPRESSION, // CntCompression
     ITEM_E_AXCID, // CntEAxcid
     ITEM_SCS_CONFIG, // Use GrpScsConfig
   };

   LstLowLevelTxEndpoints(uint32_t id);
   ~LstLowLevelTxEndpoints();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-tx-endpoints/name
   // Description: Unique name of low-level-tx-endpoint object. Reference
   // to static object
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/low-level-tx-endpoints/compression
   // Description: Container which consists of global configurable
   // parameters for compression
   // -----------------------------------------------------------------------------
   class CntCompression : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_CF_COMPRESSION_DETAILS, // Use GrpCfCompressionDetails
     };

     CntCompression(uint32_t id);
     ~CntCompression();

     YangResult_E initialise(void);

   }; // CntCompression

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/low-level-tx-endpoints/e-axcid
   // Description: Contains local address of low level TX endpoint
   // offered by Netconf server.
   // -----------------------------------------------------------------------------
   class CntEAxcid : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_EAXC, // Use GrpEaxc
     };

     CntEAxcid(uint32_t id);
     ~CntEAxcid();

     YangResult_E initialise(void);

   }; // CntEAxcid

 }; // LstLowLevelTxEndpoints

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/low-level-rx-endpoints
 // Description: Object model for low-level-rx-endpoint configuration -
 // augmented static-low-level-rx-endpoints by local-address
 //              which cannot be added to static low-level-rx-endpoints
 //              as we cannot have modificable element in static object
 // -----------------------------------------------------------------------------
 class LstLowLevelRxEndpoints : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NON_TIME_MANAGED_DELAY_ENABLED, // LeafNonTimeManagedDelayEnabled
     ITEM_NAME, // RefName
     ITEM_COMPRESSION, // CntCompression
     ITEM_E_AXCID, // CntEAxcid
     ITEM_UL_FFT_SAMPLING_OFFSETS, // LstUlFftSamplingOffsets
     ITEM_SCS_CONFIG, // Use GrpScsConfig
   };

   LstLowLevelRxEndpoints(uint32_t id);
   ~LstLowLevelRxEndpoints();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/low-level-rx-endpoints/non-time-managed-delay-enabled
   // Description: Tells if non time managed delay shall be enabled
   // -----------------------------------------------------------------------------
   class LeafNonTimeManagedDelayEnabled : public YangLeaf {
    public:
     LeafNonTimeManagedDelayEnabled(uint32_t id);
     ~LeafNonTimeManagedDelayEnabled();

   }; // LeafNonTimeManagedDelayEnabled

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/low-level-rx-endpoints/name
   // Description: Unique name of low-level-rx-endpoint object. Reference
   // to static object
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/low-level-rx-endpoints/compression
   // Description: Container which consists of global configurable
   // parameters for compression
   // -----------------------------------------------------------------------------
   class CntCompression : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_CF_COMPRESSION_DETAILS, // Use GrpCfCompressionDetails
     };

     CntCompression(uint32_t id);
     ~CntCompression();

     YangResult_E initialise(void);

   }; // CntCompression

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/low-level-rx-endpoints/e-axcid
   // Description: Contains local address of low level RX endpoint
   // offered by Netconf server.
   // -----------------------------------------------------------------------------
   class CntEAxcid : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_EAXC, // Use GrpEaxc
     };

     CntEAxcid(uint32_t id);
     ~CntEAxcid();

     YangResult_E initialise(void);

   }; // CntEAxcid

   // -----------------------------------------------------------------------------
   // List:
   // /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets
   // Description: List of FFT sampling offsets configured for each SCS
   // that will be used.
   //              Client shall configure one element for each SCS that
   //              will be used.
   // -----------------------------------------------------------------------------
   class LstUlFftSamplingOffsets : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_SCS, // LeafScs
       ITEM_UL_FFT_SAMPLING_OFFSET, // LeafUlFftSamplingOffset
     };

     LstUlFftSamplingOffsets(uint32_t id);
     ~LstUlFftSamplingOffsets();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/scs
     // Description: Value corresponds to SCS values defined for
     // frameStructure in C-plane
     //              Note: set of allowed values is restricted by SCS
     //              derived from values in supported-frame-structures.
     // -----------------------------------------------------------------------------
     class LeafScs : public YangLeaf {
      public:
       // Value corresponds to SCS values defined for frameStructure in
       // C-plane Note: set of allowed values is restricted by SCS
       // derived from values in supported-frame-structures.
       enum class Scs_E : uint32_t {

         Num_Scs_E
       };

       LeafScs(uint32_t id);
       ~LeafScs();

     }; // LeafScs

     // -----------------------------------------------------------------------------
     // Leaf:
     // /uplane-conf-group/low-level-rx-endpoints/ul-fft-sampling-offsets/ul-fft-sampling-offset
     // Description: Determines time advance of capture window for FFT.
     //              Value represents time advance of capture window
     //              start in relation to the end of CP. Unit is Ts.
     //              Note: value of this parameter is usually set to '0'
     //              (zero) for PRACH channels. Any phase offset
     //              resulting from the non-zero value of this parameter
     //              is handled in O-DU.
     // -----------------------------------------------------------------------------
     class LeafUlFftSamplingOffset : public YangLeaf {
      public:
       LeafUlFftSamplingOffset(uint32_t id);
       ~LeafUlFftSamplingOffset();

     }; // LeafUlFftSamplingOffset

   }; // LstUlFftSamplingOffsets

 }; // LstLowLevelRxEndpoints

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/tx-array-carriers
 // Description: Object model for tx-array-carriers configuration
 // -----------------------------------------------------------------------------
 class LstTxArrayCarriers : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_GAIN, // LeafGain
     ITEM_DOWNLINK_RADIO_FRAME_OFFSET, // LeafDownlinkRadioFrameOffset
     ITEM_DOWNLINK_SFN_OFFSET, // LeafDownlinkSfnOffset
     ITEM_BAND_NUMBER, // RefBandNumber
     ITEM_LTE_TDD_FRAME, // CntLteTddFrame
     ITEM_LAA_CARRIER_CONFIGURATION, // CntLaaCarrierConfiguration
     ITEM_TX_COMMON_ARRAY_CARRIER_ELEMENTS, // Use
                                            // GrpTxCommonArrayCarrierElements
   };

   LstTxArrayCarriers(uint32_t id);
   ~LstTxArrayCarriers();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/tx-array-carriers/name
   // Description: Unique name of tx-array-carriers object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/tx-array-carriers/gain
   // Description: Transmission gain in dB. Value applicable to each
   // array element carrier belonging to array carrier.
   // -----------------------------------------------------------------------------
   class LeafGain : public YangLeaf {
    public:
     LeafGain(uint32_t id);
     ~LeafGain();

   }; // LeafGain

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/tx-array-carriers/downlink-radio-frame-offset
   // Description: This parameter is used for offsetting the starting
   // position of 10ms radio frame.
   //              Note: The value should have same value within DU to
   //              all tx-array-carrierss that have same frequency and
   //              bandwidth. Note2: Unit is 1/1.2288e9 Hz and accuracy
   //              is 1/4 Tc. Then, its range is calculated 0..12288000.
   // -----------------------------------------------------------------------------
   class LeafDownlinkRadioFrameOffset : public YangLeaf {
    public:
     LeafDownlinkRadioFrameOffset(uint32_t id);
     ~LeafDownlinkRadioFrameOffset();

   }; // LeafDownlinkRadioFrameOffset

   // -----------------------------------------------------------------------------
   // Leaf: /uplane-conf-group/tx-array-carriers/downlink-sfn-offset
   // Description: This parameter is used for offsetting SFN value.
   //              Unit is in 10ms.
   //              Note: The value should have same value within DU to
   //              all tx-array-carrierss that have same frequency and
   //              bandwidth.
   // -----------------------------------------------------------------------------
   class LeafDownlinkSfnOffset : public YangLeaf {
    public:
     LeafDownlinkSfnOffset(uint32_t id);
     ~LeafDownlinkSfnOffset();

   }; // LeafDownlinkSfnOffset

   // -----------------------------------------------------------------------------
   // Reference:   /uplane-conf-group/tx-array-carriers/band-number
   // Description: This parameter informing which frequency band
   // particular antenna
   //              array is serving for.
   //              Intended use is to deal with multiband solutions.
   // -----------------------------------------------------------------------------
   class RefBandNumber : public YangReference {
    public:
     RefBandNumber(uint32_t id);
     ~RefBandNumber();

   }; // RefBandNumber

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/tx-array-carriers/lte-tdd-frame
   // Description: Container which consists of global configurable
   // parameters for tdd Frame
   // -----------------------------------------------------------------------------
   class CntLteTddFrame : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_SUBFRAME_ASSIGNMENT, // LeafSubframeAssignment
       ITEM_SPECIAL_SUBFRAME_PATTERN, // LeafSpecialSubframePattern
     };

     CntLteTddFrame(uint32_t id);
     ~CntLteTddFrame();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /uplane-conf-group/tx-array-carriers/lte-tdd-frame/subframe-assignment
     // Description: Indicates DL/UL subframe configuration as specified
     // in
     //              3GPP TS 36.211 [v15.3.0, table 4.2-2]
     // -----------------------------------------------------------------------------
     class LeafSubframeAssignment : public YangLeaf {
      public:
       // Indicates DL/UL subframe configuration as specified in
       // 3GPP TS 36.211 [v15.3.0, table 4.2-2]
       enum class SubframeAssignment_E : uint32_t {
         SAO, // subframe assignment configuration 0
         SA1, // subframe assignment configuration 1
         SA2, // subframe assignment configuration 2
         SA3, // subframe assignment configuration 3
         SA4, // subframe assignment configuration 4
         SA5, // subframe assignment configuration 5
         SA6, // subframe assignment configuration 6

         Num_SubframeAssignment_E
       };

       LeafSubframeAssignment(uint32_t id);
       ~LeafSubframeAssignment();

     }; // LeafSubframeAssignment

     // -----------------------------------------------------------------------------
     // Leaf:
     // /uplane-conf-group/tx-array-carriers/lte-tdd-frame/special-subframe-pattern
     // Description: Indicates TDD special subframe
     // configuration as in TS 36.211
     //              [v15.3.0, table 4.2-1]
     // -----------------------------------------------------------------------------
     class LeafSpecialSubframePattern : public YangLeaf {
      public:
       // Indicates TDD special subframe configuration as in
       // TS 36.211 [v15.3.0, table 4.2-1]
       enum class SpecialSubframePattern_E : uint32_t {
         SPP0, // special subframe pattern configuration 0
         SPP1, // special subframe pattern configuration 1
         SPP2, // special subframe pattern configuration 2
         SPP3, // special subframe pattern configuration 3
         SPP4, // special subframe pattern configuration 4
         SPP5, // special subframe pattern configuration 5
         SPP6, // special subframe pattern configuration 6
         SPP7, // special subframe pattern configuration 7
         SPP8, // special subframe pattern configuration 8
         SPP9, // special subframe pattern configuration 9
         SPP10, // special subframe pattern configuration 10

         Num_SpecialSubframePattern_E
       };

       LeafSpecialSubframePattern(uint32_t id);
       ~LeafSpecialSubframePattern();

     }; // LeafSpecialSubframePattern

   }; // CntLteTddFrame

   // -----------------------------------------------------------------------------
   // Container:
   // /uplane-conf-group/tx-array-carriers/laa-carrier-configuration
   // Description: Container to specify LAA feature related carrier
   // configuration.
   // -----------------------------------------------------------------------------
   class CntLaaCarrierConfiguration : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_LAA_CARRIER_CONFIG, // Use GrpLaaCarrierConfig
     };

     CntLaaCarrierConfiguration(uint32_t id);
     ~CntLaaCarrierConfiguration();

     YangResult_E initialise(void);

   }; // CntLaaCarrierConfiguration

 }; // LstTxArrayCarriers

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/rx-array-carriers
 // Description: Object model for rx-array-carriers configuration
 // -----------------------------------------------------------------------------
 class LstRxArrayCarriers : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_DOWNLINK_RADIO_FRAME_OFFSET, // LeafDownlinkRadioFrameOffset
     ITEM_DOWNLINK_SFN_OFFSET, // LeafDownlinkSfnOffset
     ITEM_GAIN_CORRECTION, // LeafGainCorrection
     ITEM_N_TA_OFFSET, // LeafNTaOffset
     ITEM_RX_COMMON_ARRAY_CARRIER_ELEMENTS, // Use
                                            // GrpRxCommonArrayCarrierElements
   };

   LstRxArrayCarriers(uint32_t id);
   ~LstRxArrayCarriers();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/rx-array-carriers/name
   // Description: Unique name of rx-array-carriers object.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:
   // /uplane-conf-group/rx-array-carriers/downlink-radio-frame-offset
   // Description: This parameter is used for offsetting the starting
   // position of 10ms radio frame.
   //              Note: The value should have same value within DU to
   //              all tx-array-carrierss that have same frequency and
   //              bandwidth. Note2: Unit is 1/1.2288e9 Hz and accuracy
   //              is 1/4 Tc. Then, its range is calculated 0..12288000.
   // -----------------------------------------------------------------------------
   class LeafDownlinkRadioFrameOffset : public YangLeaf {
    public:
     LeafDownlinkRadioFrameOffset(uint32_t id);
     ~LeafDownlinkRadioFrameOffset();

   }; // LeafDownlinkRadioFrameOffset

   // -----------------------------------------------------------------------------
   // Leaf: /uplane-conf-group/rx-array-carriers/downlink-sfn-offset
   // Description: This parameter is used for offsetting SFN value.
   //              Unit is in 10ms.
   //              Note: The value should have same value within DU to
   //              all tx-array-carrierss that have same frequency and
   //              bandwidth.
   // -----------------------------------------------------------------------------
   class LeafDownlinkSfnOffset : public YangLeaf {
    public:
     LeafDownlinkSfnOffset(uint32_t id);
     ~LeafDownlinkSfnOffset();

   }; // LeafDownlinkSfnOffset

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/rx-array-carriers/gain-correction
   // Description: Gain correction of RF path linked with array element
   // or array layers
   // -----------------------------------------------------------------------------
   class LeafGainCorrection : public YangLeaf {
    public:
     LeafGainCorrection(uint32_t id);
     ~LeafGainCorrection();

   }; // LeafGainCorrection

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/rx-array-carriers/n-ta-offset
   // Description: Value of configurable N-TA offset
   //              units are Tc=~0.5ns=1/1.96608GHz
   // -----------------------------------------------------------------------------
   class LeafNTaOffset : public YangLeaf {
    public:
     LeafNTaOffset(uint32_t id);
     ~LeafNTaOffset();

   }; // LeafNTaOffset

 }; // LstRxArrayCarriers

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/tx-arrays
 // Description: Structure describing TX array parameters
 // -----------------------------------------------------------------------------
 class LstTxArrays : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_MAX_GAIN, // LeafMaxGain
     ITEM_INDEPENDENT_POWER_BUDGET, // LeafIndependentPowerBudget
     ITEM_CAPABILITIES, // LstCapabilities
     ITEM_PARAMETERS, // Use GrpParameters
   };

   LstTxArrays(uint32_t id);
   ~LstTxArrays();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/tx-arrays/max-gain
   // Description: Max gain of RF path linked with array element (minimum
   // over elements of array) or array layers
   // -----------------------------------------------------------------------------
   class LeafMaxGain : public YangLeaf {
    public:
     LeafMaxGain(uint32_t id);
     ~LeafMaxGain();

   }; // LeafMaxGain

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/tx-arrays/independent-power-budget
   // Description: If true then every element of array has own, power
   // budget independent from power budget of other elements.
   //              Else all elements of array that are at same row and
   //              column and have same polarization share power budget
   // -----------------------------------------------------------------------------
   class LeafIndependentPowerBudget : public YangLeaf {
    public:
     LeafIndependentPowerBudget(uint32_t id);
     ~LeafIndependentPowerBudget();

   }; // LeafIndependentPowerBudget

   // -----------------------------------------------------------------------------
   // List:        /uplane-conf-group/tx-arrays/capabilities
   // Description: List of capabilities related to this tx-array
   // -----------------------------------------------------------------------------
   class LstCapabilities : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_MCAP_SUPPORT_FOR_DL, // Use GrpMcapSupportForDl
     };

     LstCapabilities(uint32_t id);
     ~LstCapabilities();

     YangResult_E initialise(void);

   }; // LstCapabilities

 }; // LstTxArrays

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/rx-arrays
 // Description: Structure describing RX array parameters
 // -----------------------------------------------------------------------------
 class LstRxArrays : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_GAIN_CORRECTION_RANGE, // CntGainCorrectionRange
     ITEM_CAPABILITIES, // LstCapabilities
     ITEM_PARAMETERS, // Use GrpParameters
   };

   LstRxArrays(uint32_t id);
   ~LstRxArrays();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/rx-arrays/gain-correction-range
   // Description: Array gain correction factor
   // -----------------------------------------------------------------------------
   class CntGainCorrectionRange : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_MAX, // LeafMax
       ITEM_MIN, // LeafMin
     };

     CntGainCorrectionRange(uint32_t id);
     ~CntGainCorrectionRange();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf: /uplane-conf-group/rx-arrays/gain-correction-range/max
     // Description: Array gain correction factor - maximum allowed value
     // -----------------------------------------------------------------------------
     class LeafMax : public YangLeaf {
      public:
       LeafMax(uint32_t id);
       ~LeafMax();

     }; // LeafMax

     // -----------------------------------------------------------------------------
     // Leaf: /uplane-conf-group/rx-arrays/gain-correction-range/min
     // Description: Array gain correction factor - minimum allowed value
     // -----------------------------------------------------------------------------
     class LeafMin : public YangLeaf {
      public:
       LeafMin(uint32_t id);
       ~LeafMin();

     }; // LeafMin

   }; // CntGainCorrectionRange

   // -----------------------------------------------------------------------------
   // List:        /uplane-conf-group/rx-arrays/capabilities
   // Description: List of capabilities related to this rx-array
   // -----------------------------------------------------------------------------
   class LstCapabilities : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_MCAP_SUPPORT_FOR_UL, // Use GrpMcapSupportForUl
     };

     LstCapabilities(uint32_t id);
     ~LstCapabilities();

     YangResult_E initialise(void);

   }; // LstCapabilities

 }; // LstRxArrays

 // -----------------------------------------------------------------------------
 // List:        /uplane-conf-group/relations
 // Description: Structure describing relations between array elements
 // -----------------------------------------------------------------------------
 class LstRelations : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_ENTITY, // LeafEntity
     ITEM_ARRAY1, // CntArray1
     ITEM_ARRAY2, // CntArray2
     ITEM_TYPES, // LstTypes
   };

   LstRelations(uint32_t id);
   ~LstRelations();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /uplane-conf-group/relations/entity
   // Description: Relation entity. Used as a key for list of relations.
   // -----------------------------------------------------------------------------
   class LeafEntity : public YangLeaf {
    public:
     LeafEntity(uint32_t id);
     ~LeafEntity();

   }; // LeafEntity

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/relations/array1
   // Description: Defnes name for first array
   // -----------------------------------------------------------------------------
   class CntArray1 : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_ARRAY_CHOICE, // Use GrpArrayChoice
     };

     CntArray1(uint32_t id);
     ~CntArray1();

     YangResult_E initialise(void);

   }; // CntArray1

   // -----------------------------------------------------------------------------
   // Container:   /uplane-conf-group/relations/array2
   // Description: Defnes name for second array
   // -----------------------------------------------------------------------------
   class CntArray2 : public YangContainer {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_ARRAY_CHOICE, // Use GrpArrayChoice
     };

     CntArray2(uint32_t id);
     ~CntArray2();

     YangResult_E initialise(void);

   }; // CntArray2

   // -----------------------------------------------------------------------------
   // List:        /uplane-conf-group/relations/types
   // Description: Defines relation type and pairs for array elements for
   // given arrays
   // -----------------------------------------------------------------------------
   class LstTypes : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_RELATION_TYPE, // LeafRelationType
       ITEM_PAIRS, // LstPairs
     };

     LstTypes(uint32_t id);
     ~LstTypes();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:        /uplane-conf-group/relations/types/relation-type
     // Description: Type of relation between array elements
     // -----------------------------------------------------------------------------
     class LeafRelationType : public YangLeaf {
      public:
       // Type of relation between array elements
       enum class RelationType_E : uint32_t {
         SHARED, // SHARED
         COALOCATED, // COALOCATED

         Num_RelationType_E
       };

       LeafRelationType(uint32_t id);
       ~LeafRelationType();

     }; // LeafRelationType

     // -----------------------------------------------------------------------------
     // List:        /uplane-conf-group/relations/types/pairs
     // Description: defines related array elements
     // -----------------------------------------------------------------------------
     class LstPairs : public YangList {
      public:
       // Item IDs
       enum : uint32_t {
         ITEM_ELEMENT_ARRAY1, // LeafElementArray1
         ITEM_ELEMENT_ARRAY2, // LeafElementArray2
       };

       LstPairs(uint32_t id);
       ~LstPairs();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Leaf: /uplane-conf-group/relations/types/pairs/element-array1
       // Description: Tells about id of element from array1
       // -----------------------------------------------------------------------------
       class LeafElementArray1 : public YangLeaf {
        public:
         LeafElementArray1(uint32_t id);
         ~LeafElementArray1();

       }; // LeafElementArray1

       // -----------------------------------------------------------------------------
       // Leaf: /uplane-conf-group/relations/types/pairs/element-array2
       // Description: Tells about id of element from array2
       // -----------------------------------------------------------------------------
       class LeafElementArray2 : public YangLeaf {
        public:
         LeafElementArray2(uint32_t id);
         ~LeafElementArray2();

       }; // LeafElementArray2

     }; // LstPairs

   }; // LstTypes

 }; // LstRelations

}; // GrpUplaneConfGroup

// -----------------------------------------------------------------------------
// Grouping:    /tx-array-notification-group
// Description: Grouping for tx-array for notification
// -----------------------------------------------------------------------------
class GrpTxArrayNotificationGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TX_ARRAY_CARRIERS, // LstTxArrayCarriers
 };

 GrpTxArrayNotificationGroup(uint32_t id);
 ~GrpTxArrayNotificationGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /tx-array-notification-group/tx-array-carriers
 // Description: notification of state change for tx-array-carriers
 // -----------------------------------------------------------------------------
 class LstTxArrayCarriers : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // RefName
     ITEM_STATE, // RefState
   };

   LstTxArrayCarriers(uint32_t id);
   ~LstTxArrayCarriers();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:   /tx-array-notification-group/tx-array-carriers/name
   // Description: name of tx-array-carriers is notified at state change
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

   // -----------------------------------------------------------------------------
   // Reference:   /tx-array-notification-group/tx-array-carriers/state
   // Description: state of tx-array-carriers is notified at state change
   // -----------------------------------------------------------------------------
   class RefState : public YangReference {
    public:
     RefState(uint32_t id);
     ~RefState();

   }; // RefState

 }; // LstTxArrayCarriers

}; // GrpTxArrayNotificationGroup

// -----------------------------------------------------------------------------
// Grouping:    /rx-array-notification-group
// Description: Grouping for rx-array for notification
// -----------------------------------------------------------------------------
class GrpRxArrayNotificationGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_RX_ARRAY_CARRIERS, // LstRxArrayCarriers
 };

 GrpRxArrayNotificationGroup(uint32_t id);
 ~GrpRxArrayNotificationGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /rx-array-notification-group/rx-array-carriers
 // Description: Notification used to inform about state change of
 // rx-array-carriers
 // -----------------------------------------------------------------------------
 class LstRxArrayCarriers : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // RefName
     ITEM_STATE, // RefState
   };

   LstRxArrayCarriers(uint32_t id);
   ~LstRxArrayCarriers();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:   /rx-array-notification-group/rx-array-carriers/name
   // Description: name of rx-array-carriers is notified at state change
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

   // -----------------------------------------------------------------------------
   // Reference:   /rx-array-notification-group/rx-array-carriers/state
   // Description: state of rx-array-carriers is notified at state change
   // -----------------------------------------------------------------------------
   class RefState : public YangReference {
    public:
     RefState(uint32_t id);
     ~RefState();

   }; // RefState

 }; // LstRxArrayCarriers

}; // GrpRxArrayNotificationGroup


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
// Notification:/tx-array-carriers-state-change
// Description: Notification used to inform about state change of tx-array-carriers
// -----------------------------------------------------------------------------
class NotifTxArrayCarriersStateChange : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TX_ARRAY_NOTIFICATION_GROUP, // Use GrpTxArrayNotificationGroup
 };

 NotifTxArrayCarriersStateChange(uint32_t id);
 ~NotifTxArrayCarriersStateChange();

 YangResult_E initialise(void);

}; // NotifTxArrayCarriersStateChange

// -----------------------------------------------------------------------------
// Notification:/rx-array-carriers-state-change
// Description: Notification used to inform about state change of tx-array-carriers
// -----------------------------------------------------------------------------
class NotifRxArrayCarriersStateChange : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_RX_ARRAY_NOTIFICATION_GROUP, // Use GrpRxArrayNotificationGroup
 };

 NotifRxArrayCarriersStateChange(uint32_t id);
 ~NotifRxArrayCarriersStateChange();

 YangResult_E initialise(void);

}; // NotifRxArrayCarriersStateChange


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-uplane-conf
// Description: This module defines the module capabilities for
//              the O-RAN Radio Unit U-Plane configuration.
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
class ModuleORanUplaneConf : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_USER_PLANE_CONFIGURATION, // CntUserPlaneConfiguration
   ITEM_TX_ARRAY_CARRIERS_STATE_CHANGE, // NotifTxArrayCarriersStateChange
   ITEM_RX_ARRAY_CARRIERS_STATE_CHANGE, // NotifRxArrayCarriersStateChange
 };

 ModuleORanUplaneConf(uint32_t id);
 ~ModuleORanUplaneConf();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanUplaneConf_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_UPLANE_CONF_H_ */
