/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanProcessingElement.cpp
 * \brief     Module ORanProcessingElement interface
 *
 *
 * \details   This file defines the YANG module o-ran-processing-element
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-processing-element"
 *            YANG Filename:    "o-ran-processing-element.yang"
 *            Module Prefix:    "o-ran-elements"
 *            Module namespace: "urn:o-ran:processing-element:1.0"
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
#include "YangModuleORanProcessingElement.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanProcessingElement_NS;

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
// Container:   processing-elements
// Description: a model defining the mapping between transport flows and
// arbitrary
//              O-RAN processing elements. A processing element may be then
//              defined for handling connectivity or delay procedures, or
//              defined with a corresponding eaxcid for CU plane operations
// -----------------------------------------------------------------------------
CntProcessingElements::CntProcessingElements(uint32_t id)
    : YangContainer("processing-elements", id) {}

CntProcessingElements::~CntProcessingElements() {}

YangResult_E
CntProcessingElements::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /processing-elements/pe-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpPeGroup peGroupInst(ITEM_PE_GROUP);
  peGroupInst.initialise();
  addGroup(peGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    pe-group
// Description:
// -----------------------------------------------------------------------------
GrpPeGroup::GrpPeGroup(uint32_t id) : YangGroup("pe-group", id) {}

GrpPeGroup::~GrpPeGroup() {}

YangResult_E
GrpPeGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /pe-group/maximum-number-of-transport-flows
  // Description: The maximum number of transport flows that can be supported by
  // an O-RU Type:        uint16 Units:
  // -----------------------------------------------------------------------------
  LeafMaximumNumberOfTransportFlows maximumNumberOfTransportFlowsInst(
      ITEM_MAXIMUM_NUMBER_OF_TRANSPORT_FLOWS);
  addLeaf(maximumNumberOfTransportFlowsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /pe-group/transport-session-type
  // Description: the type of transport session used for identifying different
  // processing
  //              elements
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafTransportSessionType transportSessionTypeInst(
      ITEM_TRANSPORT_SESSION_TYPE);
  addLeaf(transportSessionTypeInst);

  // -----------------------------------------------------------------------------
  // List:        /pe-group/ru-elements
  // Description: the list of transport definitions for each processing element
  // Array Key:
  // -----------------------------------------------------------------------------
  LstRuElements ruElementsInst(ITEM_RU_ELEMENTS);
  ruElementsInst.initialise();
  addList(ruElementsInst);

  // -----------------------------------------------------------------------------
  // Container:   /pe-group/enhanced-uplane-mapping
  // Description: a mapping table for enhanced user plane marking
  // -----------------------------------------------------------------------------
  CntEnhancedUplaneMapping enhancedUplaneMappingInst(
      ITEM_ENHANCED_UPLANE_MAPPING);
  enhancedUplaneMappingInst.initialise();
  addContainer(enhancedUplaneMappingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/maximum-number-of-transport-flows
// Description: The maximum number of transport flows that can be supported by
// an O-RU
// -----------------------------------------------------------------------------
GrpPeGroup::LeafMaximumNumberOfTransportFlows::
    LeafMaximumNumberOfTransportFlows(uint32_t id)
    : YangLeaf("maximum-number-of-transport-flows", id) {}

GrpPeGroup::LeafMaximumNumberOfTransportFlows::
    ~LeafMaximumNumberOfTransportFlows() {}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/transport-session-type
// Description: the type of transport session used for identifying different
// processing
//              elements
// -----------------------------------------------------------------------------
GrpPeGroup::LeafTransportSessionType::LeafTransportSessionType(uint32_t id)
    : YangLeaf("transport-session-type", id) {}

GrpPeGroup::LeafTransportSessionType::~LeafTransportSessionType() {}

// -----------------------------------------------------------------------------
// List:        ru-elements
// Description: the list of transport definitions for each processing element
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::LstRuElements(uint32_t id)
    : YangList("ru-elements", id) {}

GrpPeGroup::LstRuElements::~LstRuElements() {}

YangResult_E
GrpPeGroup::LstRuElements::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /pe-group/ru-elements/name
  // Description: A name that is unique across the O-RU that identifies a
  // processing
  //              element instance.
  //
  //              This name may be used in fault management to refer to a fault
  //              source or affected object
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Container:   /pe-group/ru-elements/transport-flow
  // Description: container for the transport-flow used for CU plane
  // -----------------------------------------------------------------------------
  CntTransportFlow transportFlowInst(ITEM_TRANSPORT_FLOW);
  transportFlowInst.initialise();
  addContainer(transportFlowInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/ru-elements/name
// Description: A name that is unique across the O-RU that identifies a
// processing
//              element instance.
//
//              This name may be used in fault management to refer to a fault
//              source or affected object
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpPeGroup::LstRuElements::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Container:   transport-flow
// Description: container for the transport-flow used for CU plane
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntTransportFlow(uint32_t id)
    : YangContainer("transport-flow", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::~CntTransportFlow() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /pe-group/ru-elements/transport-flow/interface-name
  // Description: the interface name
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
  // Units:
  // -----------------------------------------------------------------------------
  RefInterfaceName interfaceNameInst(ITEM_INTERFACE_NAME);
  addReference(interfaceNameInst);

  // -----------------------------------------------------------------------------
  // Container:   /pe-group/ru-elements/transport-flow/aliasmac-flow
  // Description: leafs for virtual mac type data flows
  // -----------------------------------------------------------------------------
  CntAliasmacFlow aliasmacFlowInst(ITEM_ALIASMAC_FLOW);
  aliasmacFlowInst.initialise();
  addContainer(aliasmacFlowInst);

  // -----------------------------------------------------------------------------
  // Container:   /pe-group/ru-elements/transport-flow/eth-flow
  // Description: leafs for mac + vlan-id type data flows
  // -----------------------------------------------------------------------------
  CntEthFlow ethFlowInst(ITEM_ETH_FLOW);
  ethFlowInst.initialise();
  addContainer(ethFlowInst);

  // -----------------------------------------------------------------------------
  // Container:   /pe-group/ru-elements/transport-flow/udpip-flow
  // Description: leafs for UDP/IP type data flows
  // -----------------------------------------------------------------------------
  CntUdpipFlow udpipFlowInst(ITEM_UDPIP_FLOW);
  udpipFlowInst.initialise();
  addContainer(udpipFlowInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /pe-group/ru-elements/transport-flow/interface-name
// Description: the interface name
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::RefInterfaceName::RefInterfaceName(
    uint32_t id)
    : YangReference(
          "interface-name",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "ietf-interfaces:name") {}

GrpPeGroup::LstRuElements::CntTransportFlow::RefInterfaceName::
    ~RefInterfaceName() {}

// -----------------------------------------------------------------------------
// Container:   aliasmac-flow
// Description: leafs for virtual mac type data flows
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::CntAliasmacFlow(
    uint32_t id)
    : YangContainer("aliasmac-flow", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::
    ~CntAliasmacFlow() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /pe-group/ru-elements/transport-flow/aliasmac-flow/o-du-mac-address
  // Description: O-DU's MAC address used for alias MAC based flow
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafODuMacAddress oDuMacAddressInst(ITEM_O_DU_MAC_ADDRESS);
  addLeaf(oDuMacAddressInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/ru-elements/transport-flow/aliasmac-flow/ru-aliasmac-address
  // Description: O-RU's alias MAC address used for alias MAC based flow
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/o-ran-interfaces:alias-macs Units:
  // -----------------------------------------------------------------------------
  RefRuAliasmacAddress ruAliasmacAddressInst(ITEM_RU_ALIASMAC_ADDRESS);
  addReference(ruAliasmacAddressInst);

  // -----------------------------------------------------------------------------
  // Reference:   /pe-group/ru-elements/transport-flow/aliasmac-flow/vlan-id
  // Description: O-RU's VLAN-ID used for alias MAC based flow
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/o-ran-interfaces:vlan-id Units:
  // -----------------------------------------------------------------------------
  RefVlanId vlanIdInst(ITEM_VLAN_ID);
  addReference(vlanIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /pe-group/ru-elements/transport-flow/aliasmac-flow/o-du-mac-address
// Description: O-DU's MAC address used for alias MAC based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::
    LeafODuMacAddress::LeafODuMacAddress(uint32_t id)
    : YangLeaf("o-du-mac-address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::
    LeafODuMacAddress::~LeafODuMacAddress() {}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/ru-elements/transport-flow/aliasmac-flow/ru-aliasmac-address
// Description: O-RU's alias MAC address used for alias MAC based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::
    RefRuAliasmacAddress::RefRuAliasmacAddress(uint32_t id)
    : YangReference(
          "ru-aliasmac-address",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/o-ran-interfaces:alias-macs") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::
    RefRuAliasmacAddress::~RefRuAliasmacAddress() {}

// -----------------------------------------------------------------------------
// Reference:   /pe-group/ru-elements/transport-flow/aliasmac-flow/vlan-id
// Description: O-RU's VLAN-ID used for alias MAC based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::RefVlanId::
    RefVlanId(uint32_t id)
    : YangReference(
          "vlan-id",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/o-ran-interfaces:vlan-id") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntAliasmacFlow::RefVlanId::
    ~RefVlanId() {}

// -----------------------------------------------------------------------------
// Container:   eth-flow
// Description: leafs for mac + vlan-id type data flows
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::CntEthFlow(uint32_t id)
    : YangContainer("eth-flow", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::~CntEthFlow() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /pe-group/ru-elements/transport-flow/eth-flow/o-du-mac-address
  // Description: O-DU's MAC address used for Ethernet based flow
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafODuMacAddress oDuMacAddressInst(ITEM_O_DU_MAC_ADDRESS);
  addLeaf(oDuMacAddressInst);

  // -----------------------------------------------------------------------------
  // Reference:   /pe-group/ru-elements/transport-flow/eth-flow/ru-mac-address
  // Description: O-RU's MAC address used for Ethernet based flow
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/o-ran-interfaces:mac-address Units:
  // -----------------------------------------------------------------------------
  RefRuMacAddress ruMacAddressInst(ITEM_RU_MAC_ADDRESS);
  addReference(ruMacAddressInst);

  // -----------------------------------------------------------------------------
  // Reference:   /pe-group/ru-elements/transport-flow/eth-flow/vlan-id
  // Description: O-RU's VLAN-ID used for Ethernet based flow
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/o-ran-interfaces:vlan-id Units:
  // -----------------------------------------------------------------------------
  RefVlanId vlanIdInst(ITEM_VLAN_ID);
  addReference(vlanIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/ru-elements/transport-flow/eth-flow/o-du-mac-address
// Description: O-DU's MAC address used for Ethernet based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::LeafODuMacAddress::
    LeafODuMacAddress(uint32_t id)
    : YangLeaf("o-du-mac-address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::LeafODuMacAddress::
    ~LeafODuMacAddress() {}

// -----------------------------------------------------------------------------
// Reference:   /pe-group/ru-elements/transport-flow/eth-flow/ru-mac-address
// Description: O-RU's MAC address used for Ethernet based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::RefRuMacAddress::
    RefRuMacAddress(uint32_t id)
    : YangReference(
          "ru-mac-address",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/o-ran-interfaces:mac-address") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::RefRuMacAddress::
    ~RefRuMacAddress() {}

// -----------------------------------------------------------------------------
// Reference:   /pe-group/ru-elements/transport-flow/eth-flow/vlan-id
// Description: O-RU's VLAN-ID used for Ethernet based flow
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::RefVlanId::RefVlanId(
    uint32_t id)
    : YangReference(
          "vlan-id",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/o-ran-interfaces:vlan-id") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntEthFlow::RefVlanId::
    ~RefVlanId() {}

// -----------------------------------------------------------------------------
// Container:   udpip-flow
// Description: leafs for UDP/IP type data flows
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::CntUdpipFlow(
    uint32_t id)
    : YangContainer("udpip-flow", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::~CntUdpipFlow() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ip-address
  // Description: O-DU's IPv address
  // Type:        ???UNION
  // Units:
  // -----------------------------------------------------------------------------
  LeafODuIpAddress oDuIpAddressInst(ITEM_O_DU_IP_ADDRESS);
  addLeaf(oDuIpAddressInst);

  // -----------------------------------------------------------------------------
  // Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/ru-ephemeral-udp-port
  // Description: ephemeral port used by O-RU
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafRuEphemeralUdpPort ruEphemeralUdpPortInst(ITEM_RU_EPHEMERAL_UDP_PORT);
  addLeaf(ruEphemeralUdpPortInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ephemeral-udp-port
  // Description: ephemeral port used by O-DU
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafODuEphemeralUdpPort oDuEphemeralUdpPortInst(ITEM_O_DU_EPHEMERAL_UDP_PORT);
  addLeaf(oDuEphemeralUdpPortInst);

  // -----------------------------------------------------------------------------
  // Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/ecpri-destination-udp
  // Description: the well known UDP port number used by eCPRI
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafEcpriDestinationUdp ecpriDestinationUdpInst(ITEM_ECPRI_DESTINATION_UDP);
  addLeaf(ecpriDestinationUdpInst);

  // -----------------------------------------------------------------------------
  // Choice:      /pe-group/ru-elements/transport-flow/udpip-flow/address
  // Description: choice of O-RU IPv4 or IPv6 address
  // Type:        Address_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceAddress addressInst(ITEM_ADDRESS);
  addressInst.initialise();
  addChoice(addressInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ip-address
// Description: O-DU's IPv address
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::LeafODuIpAddress::
    LeafODuIpAddress(uint32_t id)
    : YangLeaf("o-du-ip-address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::LeafODuIpAddress::
    ~LeafODuIpAddress() {}

// -----------------------------------------------------------------------------
// Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/ru-ephemeral-udp-port
// Description: ephemeral port used by O-RU
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafRuEphemeralUdpPort::LeafRuEphemeralUdpPort(uint32_t id)
    : YangLeaf("ru-ephemeral-udp-port", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafRuEphemeralUdpPort::~LeafRuEphemeralUdpPort() {}

// -----------------------------------------------------------------------------
// Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/o-du-ephemeral-udp-port
// Description: ephemeral port used by O-DU
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafODuEphemeralUdpPort::LeafODuEphemeralUdpPort(uint32_t id)
    : YangLeaf("o-du-ephemeral-udp-port", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafODuEphemeralUdpPort::~LeafODuEphemeralUdpPort() {}

// -----------------------------------------------------------------------------
// Leaf: /pe-group/ru-elements/transport-flow/udpip-flow/ecpri-destination-udp
// Description: the well known UDP port number used by eCPRI
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafEcpriDestinationUdp::LeafEcpriDestinationUdp(uint32_t id)
    : YangLeaf("ecpri-destination-udp", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::
    LeafEcpriDestinationUdp::~LeafEcpriDestinationUdp() {}

// -----------------------------------------------------------------------------
// Choice:      address
// Description: choice of O-RU IPv4 or IPv6 address
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    ChoiceAddress(uint32_t id)
    : YangChoice("address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    ~ChoiceAddress() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptRuIpv4Address ruIpv4Address(ITEM_RU_IPV4_ADDRESS);
  ruIpv4Address.initialise();
  addOption(ruIpv4Address);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptRuIpv6Address ruIpv6Address(ITEM_RU_IPV6_ADDRESS);
  ruIpv6Address.initialise();
  addOption(ruIpv6Address);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:
// /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv4-address]
// -------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv4Address::OptRuIpv4Address(uint32_t id)
    : YangChoiceOption("ru-ipv4-address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv4Address::~OptRuIpv4Address() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv4Address::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv4-address]/ru-ipv4-address
  // Description: O-RU's IPv4 address
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/ietf-ip:ipv4/ietf-ip:address/ietf-ip:ip
  // Units:
  // -----------------------------------------------------------------------------
  RefRuIpv4Address ruIpv4AddressInst(ITEM_RU_IPV4_ADDRESS);
  addReference(ruIpv4AddressInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv4-address]/ru-ipv4-address
// Description: O-RU's IPv4 address
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv4Address::RefRuIpv4Address::RefRuIpv4Address(uint32_t id)
    : YangReference(
          "ru-ipv4-address",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/ietf-ip:ipv4/ietf-ip:address/"
          "ietf-ip:ip") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv4Address::RefRuIpv4Address::~RefRuIpv4Address() {}

// -------------------------------------------------------------------------
// Option:
// /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv6-address]
// -------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv6Address::OptRuIpv6Address(uint32_t id)
    : YangChoiceOption("ru-ipv6-address", id) {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv6Address::~OptRuIpv6Address() {}

YangResult_E
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv6Address::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv6-address]/ru-ipv6-address
  // Description: O-RU's IPv6 address
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name
  // = current()/../../interface-name]/ietf-ip:ipv6/ietf-ip:address/ietf-ip:ip
  // Units:
  // -----------------------------------------------------------------------------
  RefRuIpv6Address ruIpv6AddressInst(ITEM_RU_IPV6_ADDRESS);
  addReference(ruIpv6AddressInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/ru-elements/transport-flow/udpip-flow/address[ru-ipv6-address]/ru-ipv6-address
// Description: O-RU's IPv6 address
// -----------------------------------------------------------------------------
GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv6Address::RefRuIpv6Address::RefRuIpv6Address(uint32_t id)
    : YangReference(
          "ru-ipv6-address",
          id,
          "/ietf-interfaces:interfaces/"
          "ietf-interfaces:interface[ietf-interfaces:name = "
          "current()/../../interface-name]/ietf-ip:ipv6/ietf-ip:address/"
          "ietf-ip:ip") {}

GrpPeGroup::LstRuElements::CntTransportFlow::CntUdpipFlow::ChoiceAddress::
    OptRuIpv6Address::RefRuIpv6Address::~RefRuIpv6Address() {}

// -----------------------------------------------------------------------------
// Container:   enhanced-uplane-mapping
// Description: a mapping table for enhanced user plane marking
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::CntEnhancedUplaneMapping(uint32_t id)
    : YangContainer("enhanced-uplane-mapping", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::~CntEnhancedUplaneMapping() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /pe-group/enhanced-uplane-mapping/uplane-mapping
  // Description: a mapping between up-link name and
  // o-ran-interfaces:up-marking-name Array Key:
  // -----------------------------------------------------------------------------
  LstUplaneMapping uplaneMappingInst(ITEM_UPLANE_MAPPING);
  uplaneMappingInst.initialise();
  addList(uplaneMappingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        uplane-mapping
// Description: a mapping between up-link name and
// o-ran-interfaces:up-marking-name
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::LstUplaneMapping(
    uint32_t id)
    : YangList("uplane-mapping", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::~LstUplaneMapping() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf: /pe-group/enhanced-uplane-mapping/uplane-mapping/up-marking-name
  // Description: a unique up marking name that is used for enhanced up marking
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUpMarkingName upMarkingNameInst(ITEM_UP_MARKING_NAME);
  addLeaf(upMarkingNameInst);

  // -----------------------------------------------------------------------------
  // Choice:      /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings
  // Description: U-Plane markings
  // Type:        UpMarkings_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceUpMarkings upMarkingsInst(ITEM_UP_MARKINGS);
  upMarkingsInst.initialise();
  addChoice(upMarkingsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /pe-group/enhanced-uplane-mapping/uplane-mapping/up-marking-name
// Description: a unique up marking name that is used for enhanced up marking
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::LeafUpMarkingName::
    LeafUpMarkingName(uint32_t id)
    : YangLeaf("up-marking-name", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::LeafUpMarkingName::
    ~LeafUpMarkingName() {}

// -----------------------------------------------------------------------------
// Choice:      up-markings
// Description: U-Plane markings
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    ChoiceUpMarkings(uint32_t id)
    : YangChoice("up-markings", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    ~ChoiceUpMarkings() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptEthernet ethernet(ITEM_ETHERNET);
  ethernet.initialise();
  addOption(ethernet);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptIpv4 ipv4(ITEM_IPV4);
  ipv4.initialise();
  addOption(ipv4);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptIpv6 ipv6(ITEM_IPV6);
  ipv6.initialise();
  addOption(ipv6);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:
// /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ethernet]
// -------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptEthernet::OptEthernet(uint32_t id)
    : YangChoiceOption("ethernet", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptEthernet::~OptEthernet() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptEthernet::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ethernet]/up-cos-name
  // Description: the Ethernet U-plane transport marking as defined in
  // o-ran-interfaces Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:class-of-service/o-ran-interfaces:enhanced-uplane-markings/o-ran-interfaces:up-marking-name
  // Units:
  // -----------------------------------------------------------------------------
  RefUpCosName upCosNameInst(ITEM_UP_COS_NAME);
  addReference(upCosNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ethernet]/up-cos-name
// Description: the Ethernet U-plane transport marking as defined in
// o-ran-interfaces
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptEthernet::RefUpCosName::RefUpCosName(uint32_t id)
    : YangReference(
          "up-cos-name",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "o-ran-interfaces:class-of-service/"
          "o-ran-interfaces:enhanced-uplane-markings/"
          "o-ran-interfaces:up-marking-name") {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptEthernet::RefUpCosName::~RefUpCosName() {}

// -------------------------------------------------------------------------
// Option: /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv4]
// -------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv4::OptIpv4(uint32_t id)
    : YangChoiceOption("ipv4", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv4::~OptIpv4() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv4::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv4]/upv4-dscp-name
  // Description: the IPv4 U-plane transport marking as defined in
  // o-ran-interfaces Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-ip:ipv4/o-ran-interfaces:diffserv-markings/o-ran-interfaces:enhanced-uplane-markings/o-ran-interfaces:up-marking-name
  // Units:
  // -----------------------------------------------------------------------------
  RefUpv4DscpName upv4DscpNameInst(ITEM_UPV4_DSCP_NAME);
  addReference(upv4DscpNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv4]/upv4-dscp-name
// Description: the IPv4 U-plane transport marking as defined in
// o-ran-interfaces
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv4::RefUpv4DscpName::RefUpv4DscpName(uint32_t id)
    : YangReference(
          "upv4-dscp-name",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-ip:ipv4/"
          "o-ran-interfaces:diffserv-markings/"
          "o-ran-interfaces:enhanced-uplane-markings/"
          "o-ran-interfaces:up-marking-name") {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv4::RefUpv4DscpName::~RefUpv4DscpName() {}

// -------------------------------------------------------------------------
// Option: /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv6]
// -------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv6::OptIpv6(uint32_t id)
    : YangChoiceOption("ipv6", id) {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv6::~OptIpv6() {}

YangResult_E
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv6::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv6]/upv6-dscp-name
  // Description: the IPv6 U-plane transport marking as defined in
  // o-ran-interfaces Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-ip:ipv6/o-ran-interfaces:diffserv-markings/o-ran-interfaces:enhanced-uplane-markings/o-ran-interfaces:up-marking-name
  // Units:
  // -----------------------------------------------------------------------------
  RefUpv6DscpName upv6DscpNameInst(ITEM_UPV6_DSCP_NAME);
  addReference(upv6DscpNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:
// /pe-group/enhanced-uplane-mapping/uplane-mapping/up-markings[ipv6]/upv6-dscp-name
// Description: the IPv6 U-plane transport marking as defined in
// o-ran-interfaces
// -----------------------------------------------------------------------------
GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv6::RefUpv6DscpName::RefUpv6DscpName(uint32_t id)
    : YangReference(
          "upv6-dscp-name",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-ip:ipv6/"
          "o-ran-interfaces:diffserv-markings/"
          "o-ran-interfaces:enhanced-uplane-markings/"
          "o-ran-interfaces:up-marking-name") {}

GrpPeGroup::CntEnhancedUplaneMapping::LstUplaneMapping::ChoiceUpMarkings::
    OptIpv6::RefUpv6DscpName::~RefUpv6DscpName() {}

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
// Module:      o-ran-processing-element
// Description: This module defines the YANG definitions for mapping of
// transport flows to
//              processing elements. Three options are supported:
//              i) virtual MAC based mapping
//              ii) MAC addrress + VLAN-ID based mapping
//              iii) UDP/IP based mapping
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
ModuleORanProcessingElement::ModuleORanProcessingElement(uint32_t id)
    : YangModule(
          "o-ran-processing-element",
          "o-ran-processing-element.yang",
          "o-ran-elements",
          "urn:o-ran:processing-element:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /processing-elements
  // Description: a model defining the mapping between transport flows and
  // arbitrary
  //              O-RAN processing elements. A processing element may be then
  //              defined for handling connectivity or delay procedures, or
  //              defined with a corresponding eaxcid for CU plane operations
  // -----------------------------------------------------------------------------
  CntProcessingElements processingElementsInst(ITEM_PROCESSING_ELEMENTS);
  processingElementsInst.initialise();
  addContainer(processingElementsInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanProcessingElement::~ModuleORanProcessingElement() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanProcessingElement::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanProcessingElement>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanProcessingElement::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
