#ifndef _MODULE_O_RAN_TRANSCEIVER_H_
#define _MODULE_O_RAN_TRANSCEIVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTransceiver.h
 * \brief     Module ORanTransceiver interface
 *
 *
 * \details   This file defines the YANG module o-ran-transceiver interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-transceiver"
 *            YANG Filename:    "o-ran-transceiver.yang"
 *            Module Prefix:    "o-ran-transceiver"
 *            Module namespace: "urn:o-ran:transceiver:1.0"
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

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"


namespace Mplane {

namespace ModuleORanTransceiver_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

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
// Container:   /port-transceivers
// Description: Container for Port transceiver information.
//              Leaf nodes providing  parameters status and diagnostic
//              information for pluggable transceiver module (like SFP,
//              SFP+, SFP28)
// -----------------------------------------------------------------------------
class CntPortTransceivers : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_TRANSCEIVER_GROUP, // Use GrpTransceiverGroup
 };

 CntPortTransceivers(uint32_t id);
 ~CntPortTransceivers();

 YangResult_E initialise(void);

}; // CntPortTransceivers


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /transceiver-group
// Description:
// -----------------------------------------------------------------------------
class GrpTransceiverGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_PORT_TRANSCEIVER_DATA, // LstPortTransceiverData
 };

 GrpTransceiverGroup(uint32_t id);
 ~GrpTransceiverGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /transceiver-group/port-transceiver-data
 // Description: data recovered from port transceivers
 // -----------------------------------------------------------------------------
 class LstPortTransceiverData : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PRESENT, // LeafPresent
     ITEM_VENDOR_ID, // LeafVendorId
     ITEM_VENDOR_PART, // LeafVendorPart
     ITEM_VENDOR_REV, // LeafVendorRev
     ITEM_SERIAL_NO, // LeafSerialNo
     ITEM_SFF8472_COMPLIANCE_CODE, // LeafSFF8472ComplianceCode
     ITEM_CONNECTOR_TYPE, // LeafConnectorType
     ITEM_IDENTIFIER, // LeafIdentifier
     ITEM_NOMINAL_BITRATE, // LeafNominalBitrate
     ITEM_LOW_BITRATE_MARGIN, // LeafLowBitrateMargin
     ITEM_HIGH_BITRATE_MARGIN, // LeafHighBitrateMargin
     ITEM_RX_POWER_TYPE, // LeafRxPowerType
     ITEM_RX_POWER, // LeafRxPower
     ITEM_TX_POWER, // LeafTxPower
     ITEM_TX_BIAS_CURRENT, // LeafTxBiasCurrent
     ITEM_VOLTAGE, // LeafVoltage
     ITEM_TEMPERATURE, // LeafTemperature
     ITEM_INTERFACE_NAME, // RefInterfaceName
     ITEM_PORT_NUMBER, // RefPortNumber
     ITEM_ADDITIONAL_MULTI_LANE_REPORTING, // LstAdditionalMultiLaneReporting
   };

   LstPortTransceiverData(uint32_t id);
   ~LstPortTransceiverData();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /transceiver-group/port-transceiver-data/name
   // Description: A name that is unique across the O-RU that identifies a
   // transceiver instance.
   //              This name may be used in fault management to refer to a fault
   //              source or affected object
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /transceiver-group/port-transceiver-data/present
   // Description: Indicates if pluggable transceiver module is present.
   // -----------------------------------------------------------------------------
   class LeafPresent : public YangLeaf {
    public:
     LeafPresent(uint32_t id);
     ~LeafPresent();

   }; // LeafPresent

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/vendor-id
   // Description: Name of the transciever vendor Full name of
   // transceiver vendor,
   //              that contains ASCII characters, left-aligned
   //              with any padding on the right with ASCII spaces
   //              (20h), or ASCII nul (00h) removed, and ASCII
   //              less-than (3Ch) replaced with ASCII open-brace
   //              (7Bh) and ASCII more-than (3Eh) replaced with
   //              ASCII close-brace (7Dh).
   //
   //              Optional node included when the NETCONF Server
   //              has determined the vendor ID.
   // -----------------------------------------------------------------------------
   class LeafVendorId : public YangLeaf {
    public:
     LeafVendorId(uint32_t id);
     ~LeafVendorId();

   }; // LeafVendorId

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/vendor-part
   // Description: Transceiver vendors part number, that contains
   // ASCII characters,
   //              left-aligned with any padding on the right with
   //              ASCII spaces (20h), or ASCII nul (00h) removed,
   //              and ASCII less-than (3Ch) replaced with ASCII
   //              open-brace (7Bh) and ASCII more-than (3Eh)
   //              replaced with ASCII close-brace (7Dh).
   //
   //              Optional node included when the NETCONF Server
   //              has determined the vendor part number.
   // -----------------------------------------------------------------------------
   class LeafVendorPart : public YangLeaf {
    public:
     LeafVendorPart(uint32_t id);
     ~LeafVendorPart();

   }; // LeafVendorPart

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/vendor-rev
   // Description: Transceiver vendors revision number. 2-octet
   // field that
   //              contains ASCII characters.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the vendor revision number
   // -----------------------------------------------------------------------------
   class LeafVendorRev : public YangLeaf {
    public:
     LeafVendorRev(uint32_t id);
     ~LeafVendorRev();

   }; // LeafVendorRev

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/serial-no
   // Description: Transceiver serial number encoded using ASCII
   // characters,
   //              left-aligned with any padding on the right with
   //              ASCII spaces (20h), or ASCII nul (00h) removed,
   //              and ASCII less-than (3Ch) replaced with ASCII
   //              open-brace (7Bh) and ASCII more-than (3Eh)
   //              replaced with ASCII close-brace (7Dh).
   //
   //              Optional node included when the NETCONF Server
   //              has determined the serial number.
   // -----------------------------------------------------------------------------
   class LeafSerialNo : public YangLeaf {
    public:
     LeafSerialNo(uint32_t id);
     ~LeafSerialNo();

   }; // LeafSerialNo

   // -----------------------------------------------------------------------------
   // Leaf:
   // /transceiver-group/port-transceiver-data/SFF8472-compliance-code
   // Description: Indication of which feature set(s) are
   //              implemented in the transceiver from Byte 94 of
   //              address A0h
   //              https://ta.snia.org/higherlogic/ws/public/download/294/SFF-8472.PDF
   //
   //              Optional node included when the NETCONF Server
   //              has determined the compliance code.
   // -----------------------------------------------------------------------------
   class LeafSFF8472ComplianceCode : public YangLeaf {
    public:
     // Indication of which feature set(s) are
     // implemented in the transceiver from Byte 94 of address A0h
     // https://ta.snia.org/higherlogic/ws/public/download/294/SFF-8472.PDF
     //
     // Optional node included when the NETCONF Server has
     // determined the compliance code.
     enum class SFF8472ComplianceCode_E : uint32_t {
       DIAGNOSTICS_UNDEFINED, // undefined compliance code
       REV9_3_DIAGNOSTICS, // diagnostics published 08-01-02
       REV9_5_DIAGNOSTICS, // diagnostics published 06-01-04
       REV10_2_DIAGNOSTICS, // diagnostics published 06-01-07
       REV11_0_DIAGNOSTICS, // diagnostics published 05-21-10
       REV11_3_DIAGNOSTICS, // diagnostics published 06-11-13
       REV11_4_DIAGNOSTICS, // diagnostics published 07-24-14
       REV12_0_DIAGNOSTICS, // diagnostics published 08-28-14

       Num_SFF8472ComplianceCode_E
     };

     LeafSFF8472ComplianceCode(uint32_t id);
     ~LeafSFF8472ComplianceCode();

   }; // LeafSFF8472ComplianceCode

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/connector-type
   // Description: Connector-type indicates the external optical or
   // electrical cable
   //              connector provided as the media interface as
   //              defined in the connector types derived from
   //              table 4-3 in SFF-8024.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the connector type.
   // -----------------------------------------------------------------------------
   class LeafConnectorType : public YangLeaf {
    public:
     // Connector-type indicates the external optical or electrical
     // cable connector provided as the media interface as defined
     // in the connector types derived from table 4-3 in SFF-8024.
     //
     // Optional node included when the NETCONF Server has
     // determined the connector type.
     enum class ConnectorType_E : uint32_t {
       UNKNOWN, // encoded as 00h in Table 4-3 of SFF-8024
       SUBSCRBER_CONNECTOR, // encoded as 01h in Table 4-3 of
                            // SFF-8024
       FIBER_JACK, // encoded as 06h in Table 4-3 of SFF-8024
       LUCENT_CONNECTOR, // encoded as 07h in Table 4-3 of SFF-8024
       MT_RJ, // encoded as 08h in Table 4-3 of SFF-8024
       MULTIPLE_OPTICAL, // encoded as 09h in Table 4-3 of SFF-8024
       SG, // encoded as 0Ah in Table 4-3 of SFF-8024
       OPTICAL_PIGTAIL, // encoded as 0Bh in Table 4-3 of SFF-8024
       MULTI_FIBER_PARRALEL_OPTIC_1X12, // encoded as 0Ch in Table
                                        // 4-3 of SFF-8024
       MULTI_FIBER_PARRALEL_OPTIC_2X16, // encoded as 0Dh in Table
                                        // 4-3 of SFF-8024
       HSSDC_2, // encoded as 20h in Table 4-3 of SFF-8024
       COPPER_PIGTAIL, // encoded as 21h in Table 4-3 of SFF-8024
       RJ45, // encoded as 22h in Table 4-3 of SFF-8024
       NO_SEPARABLE_CONNECTOR, // encoded as 23h in Table 4-3 of
                               // SFF-8024
       MXC_2X16, // encoded as 24h in Table 4-3 of SFF-8024

       Num_ConnectorType_E
     };

     LeafConnectorType(uint32_t id);
     ~LeafConnectorType();

   }; // LeafConnectorType

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/identifier
   // Description: Connector identifier as defined in the identifer
   //              types derived from table 4-1 in SFF-8024.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the identifier type.
   // -----------------------------------------------------------------------------
   class LeafIdentifier : public YangLeaf {
    public:
     // Connector identifier as defined in the identifer
     // types derived from table 4-1 in SFF-8024.
     //
     // Optional node included when the NETCONF Server has
     // determined the identifier type.
     enum class Identifier_E : uint32_t {
       UNKNOWN, // encoded as 00h in Table 4-1 of SFF-8024
       GBIC, // encoded as 01h in Table 4-1 of SFF-8024
       SOLDERED, // encoded as 02h in Table 4-1 of SFF-8024
       SFP, // encoded as 03h in Table 4-1 of SFF-8024
       XBI, // encoded as 04h in Table 4-1 of SFF-8024
       XENPACK, // encoded as 05h in Table 4-1 of SFF-8024
       XFP, // encoded as 06h in Table 4-1 of SFF-8024
       XFF, // encoded as 07h in Table 4-1 of SFF-8024
       XFP_E, // encoded as 08h in Table 4-1 of SFF-8024
       XPAK, // encoded as 09h in Table 4-1 of SFF-8024
       X2, // encoded as 0Ah in Table 4-1 of SFF-8024
       DWDM_SFP, // encoded as 0Bh in Table 4-1 of SFF-8024
       QSFP, // encoded as 0Ch in Table 4-1 of SFF-8024
       QSFP_, // encoded as 0Dh in Table 4-1 of SFF-8024

       Num_Identifier_E
     };

     LeafIdentifier(uint32_t id);
     ~LeafIdentifier();

   }; // LeafIdentifier

   // -----------------------------------------------------------------------------
   // Leaf:
   // /transceiver-group/port-transceiver-data/nominal-bitrate
   // Description: Nominal bitrate in Mb/s (10^6 bits per second).
   //              If needed actual value is rounded to nearest
   //              integer.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the nominal bit rate.
   // -----------------------------------------------------------------------------
   class LeafNominalBitrate : public YangLeaf {
    public:
     LeafNominalBitrate(uint32_t id);
     ~LeafNominalBitrate();

   }; // LeafNominalBitrate

   // -----------------------------------------------------------------------------
   // Leaf:
   // /transceiver-group/port-transceiver-data/low-bitrate-margin
   // Description: Minimum supported bitrate as percentage of
   // nominal bitrate
   //              below nominal bitrate.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the low bit rate margin
   // -----------------------------------------------------------------------------
   class LeafLowBitrateMargin : public YangLeaf {
    public:
     LeafLowBitrateMargin(uint32_t id);
     ~LeafLowBitrateMargin();

   }; // LeafLowBitrateMargin

   // -----------------------------------------------------------------------------
   // Leaf:
   // /transceiver-group/port-transceiver-data/high-bitrate-margin
   // Description: Maximum supported bitrate as percentage of
   // nominal bitrate
   //              above nominal bitrate.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the high bitrate margin.
   // -----------------------------------------------------------------------------
   class LeafHighBitrateMargin : public YangLeaf {
    public:
     LeafHighBitrateMargin(uint32_t id);
     ~LeafHighBitrateMargin();

   }; // LeafHighBitrateMargin

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/rx-power-type
   // Description: Receieved power measurement type
   //              oma = optical modulation amplitude
   //              avp = average power
   //
   //              Optional node included when the NETCONF Server
   //              has determined the rx power type.
   // -----------------------------------------------------------------------------
   class LeafRxPowerType : public YangLeaf {
    public:
     // Receieved power measurement type
     // oma = optical modulation amplitude
     // avp = average power
     //
     // Optional node included when the NETCONF Server has
     // determined the rx power type.
     enum class RxPowerType_E : uint32_t {
       OMA, // oma = optical modulation amplitude
       AVP, // avp = average power

       Num_RxPowerType_E
     };

     LeafRxPowerType(uint32_t id);
     ~LeafRxPowerType();

   }; // LeafRxPowerType

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/rx-power
   // Description: Measured RX input power in mW.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the measured RX power.
   //
   //              If operating with QSFP, this power corresponds
   //              to that of Lane/Channel 1.
   // -----------------------------------------------------------------------------
   class LeafRxPower : public YangLeaf {
    public:
     LeafRxPower(uint32_t id);
     ~LeafRxPower();

   }; // LeafRxPower

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/tx-power
   // Description: Measured coupled TX output power in mW.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the measured coupled TX power.
   // -----------------------------------------------------------------------------
   class LeafTxPower : public YangLeaf {
    public:
     LeafTxPower(uint32_t id);
     ~LeafTxPower();

   }; // LeafTxPower

   // -----------------------------------------------------------------------------
   // Leaf:
   // /transceiver-group/port-transceiver-data/tx-bias-current
   // Description: Measured transmitter laser bias current in mA.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the tx bias current.
   //
   //              If operating with QSFP, this bias current
   //              corresponds to that of Lane/Channel 1.
   // -----------------------------------------------------------------------------
   class LeafTxBiasCurrent : public YangLeaf {
    public:
     LeafTxBiasCurrent(uint32_t id);
     ~LeafTxBiasCurrent();

   }; // LeafTxBiasCurrent

   // -----------------------------------------------------------------------------
   // Leaf:        /transceiver-group/port-transceiver-data/voltage
   // Description: Internally measured supply voltage in mV.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the internally measured voltage.
   // -----------------------------------------------------------------------------
   class LeafVoltage : public YangLeaf {
    public:
     LeafVoltage(uint32_t id);
     ~LeafVoltage();

   }; // LeafVoltage

   // -----------------------------------------------------------------------------
   // Leaf: /transceiver-group/port-transceiver-data/temperature
   // Description: Internally measured module temperature in
   // degrees Celcius.
   //
   //              Optional node included when the NETCONF Server
   //              has determined the temperature.
   // -----------------------------------------------------------------------------
   class LeafTemperature : public YangLeaf {
    public:
     LeafTemperature(uint32_t id);
     ~LeafTemperature();

   }; // LeafTemperature

   // -----------------------------------------------------------------------------
   // Reference:
   // /transceiver-group/port-transceiver-data/interface-name
   // Description: Name of interface
   // -----------------------------------------------------------------------------
   class RefInterfaceName : public YangReference {
    public:
     RefInterfaceName(uint32_t id);
     ~RefInterfaceName();

   }; // RefInterfaceName

   // -----------------------------------------------------------------------------
   // Reference:
   // /transceiver-group/port-transceiver-data/port-number
   // Description: A number which identifies a port. In case of
   // SFP/SFP+
   //              port, port number value is 0 to N-1 where N is
   //              number of ports in the device. Numbers 0 to N-1
   //              are assigned to ports in order following order
   //              of labels on the device (labels for ports are
   //              not necessarily numbers starting from zero)
   // -----------------------------------------------------------------------------
   class RefPortNumber : public YangReference {
    public:
     RefPortNumber(uint32_t id);
     ~RefPortNumber();

   }; // RefPortNumber

   // -----------------------------------------------------------------------------
   // List:
   // /transceiver-group/port-transceiver-data/additional-multi-lane-reporting
   // Description: Additional reporting according to SFF8436 which
   // specifies real time
   //              channel monitoring for each transmit and receive
   //              channel and includes optical input power and Tx
   //              bias current.
   // -----------------------------------------------------------------------------
   class LstAdditionalMultiLaneReporting : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_LANE, // LeafLane
       ITEM_RX_POWER, // LeafRxPower
       ITEM_TX_BIAS_CURRENT, // LeafTxBiasCurrent
       ITEM_TX_POWER, // LeafTxPower
     };

     LstAdditionalMultiLaneReporting(uint32_t id);
     ~LstAdditionalMultiLaneReporting();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/lane
     // Description: the specific lane/channel associated with the
     // report parameters
     // -----------------------------------------------------------------------------
     class LeafLane : public YangLeaf {
      public:
       LeafLane(uint32_t id);
       ~LeafLane();

     }; // LeafLane

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/rx-power
     // Description: Measured RX input power in mW.
     //
     //              Optional node included when the NETCONF
     //              Server has determined the measured RX
     //              power for a particular lane/channel
     //              - see tabel 7-10 of SFF-8636.
     // -----------------------------------------------------------------------------
     class LeafRxPower : public YangLeaf {
      public:
       LeafRxPower(uint32_t id);
       ~LeafRxPower();

     }; // LeafRxPower

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-bias-current
     // Description: Measured transmitter laser bias current
     // in mA.
     //
     //              Optional node included when the NETCONF
     //              Server has determined the tx bias
     //              current for a particular lane/channel
     //              - see tabel 7-10 of SFF-8636.
     // -----------------------------------------------------------------------------
     class LeafTxBiasCurrent : public YangLeaf {
      public:
       LeafTxBiasCurrent(uint32_t id);
       ~LeafTxBiasCurrent();

     }; // LeafTxBiasCurrent

     // -----------------------------------------------------------------------------
     // Leaf:
     // /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-power
     // Description: Measured coupled TX output power in mW.
     //
     //              Optional node included when the NETCONF
     //              Server has determined the measured
     //              coupled TX power or a particular
     //              lane/channel
     //              - see tabel 7010 of SFF-8636.
     // -----------------------------------------------------------------------------
     class LeafTxPower : public YangLeaf {
      public:
       LeafTxPower(uint32_t id);
       ~LeafTxPower();

     }; // LeafTxPower

   }; // LstAdditionalMultiLaneReporting

 }; // LstPortTransceiverData

}; // GrpTransceiverGroup


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
// Module:      o-ran-transceiver
// Description: This module defines the operational state data for SFP
// transceivers used in
//              an O-RAN Radio Unit.
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
class ModuleORanTransceiver : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_PORT_TRANSCEIVERS, // CntPortTransceivers
 };

 ModuleORanTransceiver(uint32_t id);
 ~ModuleORanTransceiver();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanTransceiver_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_TRANSCEIVER_H_ */
