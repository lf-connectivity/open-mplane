/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTransceiver.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanTransceiver.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanTransceiver_NS;

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
// Container:   port-transceivers
// Description: Container for Port transceiver information.
//              Leaf nodes providing  parameters status and diagnostic
//              information for pluggable transceiver module (like SFP,
//              SFP+, SFP28)
// -----------------------------------------------------------------------------
CntPortTransceivers::CntPortTransceivers(uint32_t id)
	: YangContainer("port-transceivers", id)
{
}

CntPortTransceivers::~CntPortTransceivers()
{
}

YangResult_E CntPortTransceivers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /port-transceivers/transceiver-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpTransceiverGroup transceiverGroupInst(ITEM_TRANSCEIVER_GROUP);
	transceiverGroupInst.initialise();
	addGroup(transceiverGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    transceiver-group
// Description:
// -----------------------------------------------------------------------------
GrpTransceiverGroup::GrpTransceiverGroup(uint32_t id)
	: YangGroup("transceiver-group", id)
{
}

GrpTransceiverGroup::~GrpTransceiverGroup()
{
}

YangResult_E GrpTransceiverGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /transceiver-group/port-transceiver-data
	// Description: data recovered from port transceivers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstPortTransceiverData portTransceiverDataInst(ITEM_PORT_TRANSCEIVER_DATA);
	portTransceiverDataInst.initialise();
	addList(portTransceiverDataInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        port-transceiver-data
// Description: data recovered from port transceivers
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstPortTransceiverData(uint32_t id)
	: YangList("port-transceiver-data", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::~LstPortTransceiverData()
{
}

YangResult_E GrpTransceiverGroup::LstPortTransceiverData::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/name
	// Description: A name that is unique across the O-RU that identifies a transceiver instance.
	//              This name may be used in fault management to refer to a fault source
	//              or affected object
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/present
	// Description: Indicates if pluggable transceiver module is present.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafPresent presentInst(ITEM_PRESENT);
	addLeaf(presentInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/vendor-id
	// Description: Name of the transciever vendor Full name of transceiver vendor,
	//              that contains ASCII characters, left-aligned with
	//              any padding on the right with ASCII spaces (20h), or ASCII nul
	//              (00h) removed, and ASCII less-than (3Ch) replaced with ASCII
	//              open-brace (7Bh) and ASCII more-than (3Eh) replaced with ASCII
	//              close-brace (7Dh).
	//
	//              Optional node included when the NETCONF Server has determined
	//              the vendor ID.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafVendorId vendorIdInst(ITEM_VENDOR_ID);
	addLeaf(vendorIdInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/vendor-part
	// Description: Transceiver vendors part number, that contains ASCII characters,
	//              left-aligned with any padding on the right with ASCII spaces
	//              (20h), or ASCII nul (00h) removed, and ASCII less-than (3Ch)
	//              replaced with ASCII open-brace (7Bh) and ASCII more-than (3Eh)
	//              replaced with ASCII close-brace (7Dh).
	//
	//              Optional node included when the NETCONF Server has determined
	//              the vendor part number.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafVendorPart vendorPartInst(ITEM_VENDOR_PART);
	addLeaf(vendorPartInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/vendor-rev
	// Description: Transceiver vendors revision number. 2-octet field that
	//              contains ASCII characters.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the vendor revision number
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafVendorRev vendorRevInst(ITEM_VENDOR_REV);
	addLeaf(vendorRevInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/serial-no
	// Description: Transceiver serial number encoded using ASCII characters,
	//              left-aligned with any padding on the right with ASCII spaces
	//              (20h), or ASCII nul (00h) removed, and ASCII less-than (3Ch)
	//              replaced with ASCII open-brace (7Bh) and ASCII more-than (3Eh)
	//              replaced with ASCII close-brace (7Dh).
	//
	//              Optional node included when the NETCONF Server has determined
	//              the serial number.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafSerialNo serialNoInst(ITEM_SERIAL_NO);
	addLeaf(serialNoInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/SFF8472-compliance-code
	// Description: Indication of which feature set(s) are
	//              implemented in the transceiver from Byte 94 of address A0h
	//              https://ta.snia.org/higherlogic/ws/public/download/294/SFF-8472.PDF
	//
	//              Optional node included when the NETCONF Server has determined
	//              the compliance code.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafSFF8472ComplianceCode SFF8472ComplianceCodeInst(ITEM_SFF8472_COMPLIANCE_CODE);
	addLeaf(SFF8472ComplianceCodeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/connector-type
	// Description: Connector-type indicates the external optical or electrical cable
	//              connector provided as the media interface as defined in the connector
	//              types derived from table 4-3 in SFF-8024.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the connector type.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafConnectorType connectorTypeInst(ITEM_CONNECTOR_TYPE);
	addLeaf(connectorTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/identifier
	// Description: Connector identifier as defined in the identifer
	//              types derived from table 4-1 in SFF-8024.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the identifier type.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafIdentifier identifierInst(ITEM_IDENTIFIER);
	addLeaf(identifierInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/nominal-bitrate
	// Description: Nominal bitrate in Mb/s (10^6 bits per second).
	//              If needed actual value is rounded to nearest integer.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the nominal bit rate.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafNominalBitrate nominalBitrateInst(ITEM_NOMINAL_BITRATE);
	addLeaf(nominalBitrateInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/low-bitrate-margin
	// Description: Minimum supported bitrate as percentage of nominal bitrate
	//              below nominal bitrate.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the low bit rate margin
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafLowBitrateMargin lowBitrateMarginInst(ITEM_LOW_BITRATE_MARGIN);
	addLeaf(lowBitrateMarginInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/high-bitrate-margin
	// Description: Maximum supported bitrate as percentage of nominal bitrate
	//              above nominal bitrate.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the high bitrate margin.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafHighBitrateMargin highBitrateMarginInst(ITEM_HIGH_BITRATE_MARGIN);
	addLeaf(highBitrateMarginInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/rx-power-type
	// Description: Receieved power measurement type
	//              oma = optical modulation amplitude
	//              avp = average power
	//
	//              Optional node included when the NETCONF Server has determined
	//              the rx power type.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafRxPowerType rxPowerTypeInst(ITEM_RX_POWER_TYPE);
	addLeaf(rxPowerTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/rx-power
	// Description: Measured RX input power in mW.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the measured RX power.
	//
	//              If operating with QSFP, this power corresponds to that of
	//              Lane/Channel 1.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafRxPower rxPowerInst(ITEM_RX_POWER);
	addLeaf(rxPowerInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/tx-power
	// Description: Measured coupled TX output power in mW.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the measured coupled TX power.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafTxPower txPowerInst(ITEM_TX_POWER);
	addLeaf(txPowerInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/tx-bias-current
	// Description: Measured transmitter laser bias current in mA.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the tx bias current.
	//
	//              If operating with QSFP, this bias current corresponds to that of
	//              Lane/Channel 1.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafTxBiasCurrent txBiasCurrentInst(ITEM_TX_BIAS_CURRENT);
	addLeaf(txBiasCurrentInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/voltage
	// Description: Internally measured supply voltage in mV.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the internally measured voltage.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafVoltage voltageInst(ITEM_VOLTAGE);
	addLeaf(voltageInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/temperature
	// Description: Internally measured module temperature in degrees Celcius.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the temperature.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafTemperature temperatureInst(ITEM_TEMPERATURE);
	addLeaf(temperatureInst);

	// -----------------------------------------------------------------------------
	// Reference:   /transceiver-group/port-transceiver-data/interface-name
	// Description: Name of interface
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
	// Units:
	// -----------------------------------------------------------------------------
	RefInterfaceName interfaceNameInst(ITEM_INTERFACE_NAME);
	addReference(interfaceNameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /transceiver-group/port-transceiver-data/port-number
	// Description: A number which identifies a port. In case of SFP/SFP+
	//              port, port number value is 0 to N-1 where N is number of ports
	//              in the device. Numbers 0 to N-1 are assigned to ports in order
	//              following order of labels on the device (labels for ports are
	//              not necessarily numbers starting from zero)
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:port-reference/o-ran-interfaces:port-number
	// Units:
	// -----------------------------------------------------------------------------
	RefPortNumber portNumberInst(ITEM_PORT_NUMBER);
	addReference(portNumberInst);

	// -----------------------------------------------------------------------------
	// List:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting
	// Description: Additional reporting according to SFF8436 which specifies real time
	//              channel monitoring for each transmit and receive channel and includes
	//              optical input power and Tx bias current.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAdditionalMultiLaneReporting additionalMultiLaneReportingInst(ITEM_ADDITIONAL_MULTI_LANE_REPORTING);
	additionalMultiLaneReportingInst.initialise();
	addList(additionalMultiLaneReportingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/name
// Description: A name that is unique across the O-RU that identifies a transceiver instance.
//              This name may be used in fault management to refer to a fault source
//              or affected object
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/present
// Description: Indicates if pluggable transceiver module is present.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafPresent::LeafPresent(uint32_t id)
	: YangLeaf("present", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafPresent::~LeafPresent()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/vendor-id
// Description: Name of the transciever vendor Full name of transceiver vendor,
//              that contains ASCII characters, left-aligned with
//              any padding on the right with ASCII spaces (20h), or ASCII nul
//              (00h) removed, and ASCII less-than (3Ch) replaced with ASCII
//              open-brace (7Bh) and ASCII more-than (3Eh) replaced with ASCII
//              close-brace (7Dh).
//
//              Optional node included when the NETCONF Server has determined
//              the vendor ID.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafVendorId::LeafVendorId(uint32_t id)
	: YangLeaf("vendor-id", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafVendorId::~LeafVendorId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/vendor-part
// Description: Transceiver vendors part number, that contains ASCII characters,
//              left-aligned with any padding on the right with ASCII spaces
//              (20h), or ASCII nul (00h) removed, and ASCII less-than (3Ch)
//              replaced with ASCII open-brace (7Bh) and ASCII more-than (3Eh)
//              replaced with ASCII close-brace (7Dh).
//
//              Optional node included when the NETCONF Server has determined
//              the vendor part number.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafVendorPart::LeafVendorPart(uint32_t id)
	: YangLeaf("vendor-part", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafVendorPart::~LeafVendorPart()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/vendor-rev
// Description: Transceiver vendors revision number. 2-octet field that
//              contains ASCII characters.
//
//              Optional node included when the NETCONF Server has determined
//              the vendor revision number
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafVendorRev::LeafVendorRev(uint32_t id)
	: YangLeaf("vendor-rev", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafVendorRev::~LeafVendorRev()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/serial-no
// Description: Transceiver serial number encoded using ASCII characters,
//              left-aligned with any padding on the right with ASCII spaces
//              (20h), or ASCII nul (00h) removed, and ASCII less-than (3Ch)
//              replaced with ASCII open-brace (7Bh) and ASCII more-than (3Eh)
//              replaced with ASCII close-brace (7Dh).
//
//              Optional node included when the NETCONF Server has determined
//              the serial number.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafSerialNo::LeafSerialNo(uint32_t id)
	: YangLeaf("serial-no", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafSerialNo::~LeafSerialNo()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/SFF8472-compliance-code
// Description: Indication of which feature set(s) are
//              implemented in the transceiver from Byte 94 of address A0h
//              https://ta.snia.org/higherlogic/ws/public/download/294/SFF-8472.PDF
//
//              Optional node included when the NETCONF Server has determined
//              the compliance code.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafSFF8472ComplianceCode::LeafSFF8472ComplianceCode(uint32_t id)
	: YangLeaf("SFF8472-compliance-code", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafSFF8472ComplianceCode::~LeafSFF8472ComplianceCode()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/connector-type
// Description: Connector-type indicates the external optical or electrical cable
//              connector provided as the media interface as defined in the connector
//              types derived from table 4-3 in SFF-8024.
//
//              Optional node included when the NETCONF Server has determined
//              the connector type.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafConnectorType::LeafConnectorType(uint32_t id)
	: YangLeaf("connector-type", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafConnectorType::~LeafConnectorType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/identifier
// Description: Connector identifier as defined in the identifer
//              types derived from table 4-1 in SFF-8024.
//
//              Optional node included when the NETCONF Server has determined
//              the identifier type.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafIdentifier::LeafIdentifier(uint32_t id)
	: YangLeaf("identifier", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafIdentifier::~LeafIdentifier()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/nominal-bitrate
// Description: Nominal bitrate in Mb/s (10^6 bits per second).
//              If needed actual value is rounded to nearest integer.
//
//              Optional node included when the NETCONF Server has determined
//              the nominal bit rate.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafNominalBitrate::LeafNominalBitrate(uint32_t id)
	: YangLeaf("nominal-bitrate", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafNominalBitrate::~LeafNominalBitrate()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/low-bitrate-margin
// Description: Minimum supported bitrate as percentage of nominal bitrate
//              below nominal bitrate.
//
//              Optional node included when the NETCONF Server has determined
//              the low bit rate margin
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafLowBitrateMargin::LeafLowBitrateMargin(uint32_t id)
	: YangLeaf("low-bitrate-margin", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafLowBitrateMargin::~LeafLowBitrateMargin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/high-bitrate-margin
// Description: Maximum supported bitrate as percentage of nominal bitrate
//              above nominal bitrate.
//
//              Optional node included when the NETCONF Server has determined
//              the high bitrate margin.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafHighBitrateMargin::LeafHighBitrateMargin(uint32_t id)
	: YangLeaf("high-bitrate-margin", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafHighBitrateMargin::~LeafHighBitrateMargin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/rx-power-type
// Description: Receieved power measurement type
//              oma = optical modulation amplitude
//              avp = average power
//
//              Optional node included when the NETCONF Server has determined
//              the rx power type.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafRxPowerType::LeafRxPowerType(uint32_t id)
	: YangLeaf("rx-power-type", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafRxPowerType::~LeafRxPowerType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/rx-power
// Description: Measured RX input power in mW.
//
//              Optional node included when the NETCONF Server has determined
//              the measured RX power.
//
//              If operating with QSFP, this power corresponds to that of
//              Lane/Channel 1.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafRxPower::LeafRxPower(uint32_t id)
	: YangLeaf("rx-power", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafRxPower::~LeafRxPower()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/tx-power
// Description: Measured coupled TX output power in mW.
//
//              Optional node included when the NETCONF Server has determined
//              the measured coupled TX power.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafTxPower::LeafTxPower(uint32_t id)
	: YangLeaf("tx-power", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafTxPower::~LeafTxPower()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/tx-bias-current
// Description: Measured transmitter laser bias current in mA.
//
//              Optional node included when the NETCONF Server has determined
//              the tx bias current.
//
//              If operating with QSFP, this bias current corresponds to that of
//              Lane/Channel 1.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafTxBiasCurrent::LeafTxBiasCurrent(uint32_t id)
	: YangLeaf("tx-bias-current", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafTxBiasCurrent::~LeafTxBiasCurrent()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/voltage
// Description: Internally measured supply voltage in mV.
//
//              Optional node included when the NETCONF Server has determined
//              the internally measured voltage.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafVoltage::LeafVoltage(uint32_t id)
	: YangLeaf("voltage", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafVoltage::~LeafVoltage()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/temperature
// Description: Internally measured module temperature in degrees Celcius.
//
//              Optional node included when the NETCONF Server has determined
//              the temperature.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LeafTemperature::LeafTemperature(uint32_t id)
	: YangLeaf("temperature", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LeafTemperature::~LeafTemperature()
{
}

// -----------------------------------------------------------------------------
// Reference:   /transceiver-group/port-transceiver-data/interface-name
// Description: Name of interface
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::RefInterfaceName::RefInterfaceName(uint32_t id)
	: YangReference("interface-name", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name")
{
}

GrpTransceiverGroup::LstPortTransceiverData::RefInterfaceName::~RefInterfaceName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /transceiver-group/port-transceiver-data/port-number
// Description: A number which identifies a port. In case of SFP/SFP+
//              port, port number value is 0 to N-1 where N is number of ports
//              in the device. Numbers 0 to N-1 are assigned to ports in order
//              following order of labels on the device (labels for ports are
//              not necessarily numbers starting from zero)
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::RefPortNumber::RefPortNumber(uint32_t id)
	: YangReference("port-number", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:port-reference/o-ran-interfaces:port-number")
{
}

GrpTransceiverGroup::LstPortTransceiverData::RefPortNumber::~RefPortNumber()
{
}

// -----------------------------------------------------------------------------
// List:        additional-multi-lane-reporting
// Description: Additional reporting according to SFF8436 which specifies real time
//              channel monitoring for each transmit and receive channel and includes
//              optical input power and Tx bias current.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LstAdditionalMultiLaneReporting(uint32_t id)
	: YangList("additional-multi-lane-reporting", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::~LstAdditionalMultiLaneReporting()
{
}

YangResult_E GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/lane
	// Description: the specific lane/channel associated with the report parameters
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafLane laneInst(ITEM_LANE);
	addLeaf(laneInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/rx-power
	// Description: Measured RX input power in mW.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the measured RX power for a particular lane/channel
	//              - see tabel 7-10 of SFF-8636.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafRxPower rxPowerInst(ITEM_RX_POWER);
	addLeaf(rxPowerInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-bias-current
	// Description: Measured transmitter laser bias current in mA.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the tx bias current for a particular lane/channel
	//              - see tabel 7-10 of SFF-8636.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafTxBiasCurrent txBiasCurrentInst(ITEM_TX_BIAS_CURRENT);
	addLeaf(txBiasCurrentInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-power
	// Description: Measured coupled TX output power in mW.
	//
	//              Optional node included when the NETCONF Server has determined
	//              the measured coupled TX power or a particular lane/channel
	//              - see tabel 7010 of SFF-8636.
	// Type:        dec64
	// Units:
	// -----------------------------------------------------------------------------
	LeafTxPower txPowerInst(ITEM_TX_POWER);
	addLeaf(txPowerInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/lane
// Description: the specific lane/channel associated with the report parameters
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafLane::LeafLane(uint32_t id)
	: YangLeaf("lane", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafLane::~LeafLane()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/rx-power
// Description: Measured RX input power in mW.
//
//              Optional node included when the NETCONF Server has determined
//              the measured RX power for a particular lane/channel
//              - see tabel 7-10 of SFF-8636.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafRxPower::LeafRxPower(uint32_t id)
	: YangLeaf("rx-power", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafRxPower::~LeafRxPower()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-bias-current
// Description: Measured transmitter laser bias current in mA.
//
//              Optional node included when the NETCONF Server has determined
//              the tx bias current for a particular lane/channel
//              - see tabel 7-10 of SFF-8636.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafTxBiasCurrent::LeafTxBiasCurrent(uint32_t id)
	: YangLeaf("tx-bias-current", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafTxBiasCurrent::~LeafTxBiasCurrent()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /transceiver-group/port-transceiver-data/additional-multi-lane-reporting/tx-power
// Description: Measured coupled TX output power in mW.
//
//              Optional node included when the NETCONF Server has determined
//              the measured coupled TX power or a particular lane/channel
//              - see tabel 7010 of SFF-8636.
// -----------------------------------------------------------------------------
GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafTxPower::LeafTxPower(uint32_t id)
	: YangLeaf("tx-power", id)
{
}

GrpTransceiverGroup::LstPortTransceiverData::LstAdditionalMultiLaneReporting::LeafTxPower::~LeafTxPower()
{
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
// Module:      o-ran-transceiver
// Description: This module defines the operational state data for SFP transceivers used in
//              an O-RAN Radio Unit.
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//              AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//              IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//              ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//              LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//              CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//              SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//              INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//              ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//              POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or without
//              modification, are permitted provided that the following conditions are met:
//
//              * Redistributions of source code must retain the above copyright notice,
//              this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above copyright notice,
//              this list of conditions and the above disclaimer in the documentation
//              and/or other materials provided with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived from
//              this software without specific prior written permission.
// -----------------------------------------------------------------------------
ModuleORanTransceiver::ModuleORanTransceiver(uint32_t id)
	: YangModule ("o-ran-transceiver",
	              "o-ran-transceiver.yang",
	              "o-ran-transceiver",
	              "urn:o-ran:transceiver:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /port-transceivers
	// Description: Container for Port transceiver information.
	//              Leaf nodes providing  parameters status and diagnostic
	//              information for pluggable transceiver module (like SFP,
	//              SFP+, SFP28)
	// -----------------------------------------------------------------------------
	CntPortTransceivers portTransceiversInst(ITEM_PORT_TRANSCEIVERS);
	portTransceiversInst.initialise();
	addContainer(portTransceiversInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanTransceiver::~ModuleORanTransceiver()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanTransceiver::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanTransceiver>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanTransceiver::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
