/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfInterfaces.cpp
 * \brief     Module IetfInterfaces interface
 *
 *
 * \details   This file defines the YANG module ietf-interfaces interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-interfaces"
 *            YANG Filename:    "ietf-interfaces.yang"
 *            Module Prefix:    "if"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-interfaces"
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
#include "YangModuleIetfInterfaces.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

// Module:   ietf-ip
#include "YangModuleIetfIp.h"

// Module:   o-ran-interfaces
#include "YangModuleORanInterfaces.h"


using namespace Mplane;
using namespace ModuleIetfInterfaces_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device allows user-controlled
//              interfaces to be named arbitrarily.
// -----------------------------------------------------------------------------
FeatureArbitraryNames::FeatureArbitraryNames(uint32_t id)
	: YangFeature("arbitrary-names", id)
{
}

FeatureArbitraryNames::~FeatureArbitraryNames()
{
}

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device supports
//              pre-provisioning of interface configuration, i.e., it is
//              possible to configure an interface whose physical interface
//              hardware is not present on the device.
// -----------------------------------------------------------------------------
FeaturePreProvisioning::FeaturePreProvisioning(uint32_t id)
	: YangFeature("pre-provisioning", id)
{
}

FeaturePreProvisioning::~FeaturePreProvisioning()
{
}

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device implements
//              the IF-MIB.
// -----------------------------------------------------------------------------
FeatureIfMib::FeatureIfMib(uint32_t id)
	: YangFeature("if-mib", id)
{
}

FeatureIfMib::~FeatureIfMib()
{
}


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
// Container:   interfaces
// Description: Interface parameters.
// -----------------------------------------------------------------------------
CntInterfaces::CntInterfaces(uint32_t id)
	: YangContainer("interfaces", id)
{
}

CntInterfaces::~CntInterfaces()
{
}

YangResult_E CntInterfaces::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface
	// Description: The list of interfaces on the device.
	//              The status of an interface is available in this list in the
	//              operational state.  If the configuration of a
	//              system-controlled interface cannot be used by the system
	//              (e.g., the interface hardware present does not match the
	//              interface type), then the configuration is not applied to
	//              the system-controlled interface shown in the operational
	//              state.  If the configuration of a user-controlled interface
	//              cannot be used by the system, the configured interface is
	//              not instantiated in the operational state.
	//              System-controlled interfaces created by the system are
	//              always present in this list in the operational state,
	//              whether or not they are configured.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstInterface interfaceInst(ITEM_INTERFACE);
	interfaceInst.initialise();
	addList(interfaceInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        interface
// Description: The list of interfaces on the device.
//              The status of an interface is available in this list in the
//              operational state.  If the configuration of a
//              system-controlled interface cannot be used by the system
//              (e.g., the interface hardware present does not match the
//              interface type), then the configuration is not applied to
//              the system-controlled interface shown in the operational
//              state.  If the configuration of a user-controlled interface
//              cannot be used by the system, the configured interface is
//              not instantiated in the operational state.
//              System-controlled interfaces created by the system are
//              always present in this list in the operational state,
//              whether or not they are configured.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LstInterface(uint32_t id)
	: YangList("interface", id)
{
}

CntInterfaces::LstInterface::~LstInterface()
{
}

YangResult_E CntInterfaces::LstInterface::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/name
	// Description: The name of the interface.
	//              A device MAY restrict the allowed values for this leaf,
	//              possibly depending on the type of the interface.
	//              For system-controlled interfaces, this leaf is the
	//              device-specific name of the interface.
	//              If a client tries to create configuration for a
	//              system-controlled interface that is not present in the
	//              operational state, the server MAY reject the request if
	//              the implementation does not support pre-provisioning of
	//              interfaces or if the name refers to an interface that can
	//              never exist in the system.  A Network Configuration
	//              Protocol (NETCONF) server MUST reply with an rpc-error
	//              with the error-tag 'invalid-value' in this case.
	//              If the device supports pre-provisioning of interface
	//              configuration, the 'pre-provisioning' feature is
	//              advertised.
	//              If the device allows arbitrarily named user-controlled
	//              interfaces, the 'arbitrary-names' feature is advertised.
	//              When a configured user-controlled interface is created by
	//              the system, it is instantiated with the same name in the
	//              operational state.
	//              A server implementation MAY map this leaf to the ifName
	//              MIB object.  Such an implementation needs to use some
	//              mechanism to handle the differences in size and characters
	//              allowed between this leaf and ifName.  The definition of
	//              such a mechanism is outside the scope of this document.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/description
	// Description: A textual description of the interface.
	//              A server implementation MAY map this leaf to the ifAlias
	//              MIB object.  Such an implementation needs to use some
	//              mechanism to handle the differences in size and characters
	//              allowed between this leaf and ifAlias.  The definition of
	//              such a mechanism is outside the scope of this document.
	//              Since ifAlias is defined to be stored in non-volatile
	//              storage, the MIB implementation MUST map ifAlias to the
	//              value of 'description' in the persistently stored
	//              configuration.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDescription descriptionInst(ITEM_DESCRIPTION);
	addLeaf(descriptionInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/type
	// Description: The type of the interface.
	//              When an interface entry is created, a server MAY
	//              initialize the type leaf with a valid value, e.g., if it
	//              is possible to derive the type from the name of the
	//              interface.
	//              If a client tries to set the type of an interface to a
	//              value that can never be used by the system, e.g., if the
	//              type is not supported or if the type does not match the
	//              name of the interface, the server MUST reject the request.
	//              A NETCONF server MUST reply with an rpc-error with the
	//              error-tag 'invalid-value' in this case.
	// Type:        ???IDENT
	// Units:
	// -----------------------------------------------------------------------------
	LeafType typeInst(ITEM_TYPE);
	addLeaf(typeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/enabled
	// Description: This leaf contains the configured, desired state of the
	//              interface.
	//              Systems that implement the IF-MIB use the value of this
	//              leaf in the intended configuration to set
	//              IF-MIB.ifAdminStatus to 'up' or 'down' after an ifEntry
	//              has been initialized, as described in RFC 2863.
	//              Changes in this leaf in the intended configuration are
	//              reflected in ifAdminStatus.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnabled enabledInst(ITEM_ENABLED);
	addLeaf(enabledInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/link-up-down-trap-enable
	// Description: Controls whether linkUp/linkDown SNMP notifications
	//              should be generated for this interface.
	//              If this node is not configured, the value 'enabled' is
	//              operationally used by the server for interfaces that do
	//              not operate on top of any other interface (i.e., there are
	//              no 'lower-layer-if' entries), and 'disabled' otherwise.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafLinkUpDownTrapEnable linkUpDownTrapEnableInst(ITEM_LINK_UP_DOWN_TRAP_ENABLE);
	addLeaf(linkUpDownTrapEnableInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/admin-status
	// Description: The desired state of the interface.
	//              This leaf has the same read semantics as ifAdminStatus.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafAdminStatus adminStatusInst(ITEM_ADMIN_STATUS);
	addLeaf(adminStatusInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/oper-status
	// Description: The current operational state of the interface.
	//              This leaf has the same semantics as ifOperStatus.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOperStatus operStatusInst(ITEM_OPER_STATUS);
	addLeaf(operStatusInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/last-change
	// Description: The time the interface entered its current operational
	//              state.  If the current state was entered prior to the
	//              last re-initialization of the local network management
	//              subsystem, then this node is not present.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLastChange lastChangeInst(ITEM_LAST_CHANGE);
	addLeaf(lastChangeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/if-index
	// Description: The ifIndex value for the ifEntry represented by this
	//              interface.
	// Type:        int32
	// Units:
	// -----------------------------------------------------------------------------
	LeafIfIndex ifIndexInst(ITEM_IF_INDEX);
	addLeaf(ifIndexInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/phys-address
	// Description: The interface's address at its protocol sub-layer.  For
	//              example, for an 802.x interface, this object normally
	//              contains a Media Access Control (MAC) address.  The
	//              interface's media-specific modules must define the bit
	//              and byte ordering and the format of the value of this
	//              object.  For interfaces that do not have such an address
	//              (e.g., a serial line), this node is not present.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafPhysAddress physAddressInst(ITEM_PHYS_ADDRESS);
	addLeaf(physAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/speed
	// Description: An estimate of the interface's current bandwidth in bits
	//              per second.  For interfaces that do not vary in
	//              bandwidth or for those where no accurate estimation can
	//              be made, this node should contain the nominal bandwidth.
	//              For interfaces that have no concept of bandwidth, this
	//              node is not present.
	// Type:        uint64
	// Units:       bits/second
	// -----------------------------------------------------------------------------
	LeafSpeed speedInst(ITEM_SPEED);
	addLeaf(speedInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/l2-mtu
	// Description: The maximum size of layer 2 frames that may be transmitted
	//              or received on the interface (excluding any FCS overhead).
	//              For Ethernet interfaces it also excludes the
	//              4-8 byte overhead of any known (i.e. explicitly matched by
	//              a child sub-interface) 801.1Q VLAN tags.
	// Type:        uint16
	// Units:       bytes
	// -----------------------------------------------------------------------------
	LeafL2Mtu l2MtuInst(ITEM_L2_MTU);
	addLeaf(l2MtuInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/vlan-tagging
	// Description: Indicates if VLAN tagging is used.
	//              Default true is used to enable equipment to auonomously discover that it is
	//              connected to a trunk port.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafVlanTagging vlanTaggingInst(ITEM_VLAN_TAGGING);
	addLeaf(vlanTaggingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/vlan-id
	// Description: The VLAN-ID.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafVlanId vlanIdInst(ITEM_VLAN_ID);
	addLeaf(vlanIdInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/last-cleared
	// Description: Timestamp of the last time the interface counters were
	//              cleared.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLastCleared lastClearedInst(ITEM_LAST_CLEARED);
	addLeaf(lastClearedInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/mac-address
	// Description: The MAC address of the interface.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafMacAddress macAddressInst(ITEM_MAC_ADDRESS);
	addLeaf(macAddressInst);

	// -----------------------------------------------------------------------------
	// Reference:   /interfaces/interface/base-interface
	// Description: The base interface for the VLAN sub-interafce.
	// Ref:         [reference]
	// Units:
	// -----------------------------------------------------------------------------
	RefBaseInterface baseInterfaceInst(ITEM_BASE_INTERFACE);
	addReference(baseInterfaceInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/higher-layer-if
	// Description: A list of references to interfaces layered on top of this
	//              interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstHigherLayerIf higherLayerIfInst(ITEM_HIGHER_LAYER_IF);
	higherLayerIfInst.initialise();
	addList(higherLayerIfInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/lower-layer-if
	// Description: A list of references to interfaces layered underneath this
	//              interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowerLayerIf lowerLayerIfInst(ITEM_LOWER_LAYER_IF);
	lowerLayerIfInst.initialise();
	addList(lowerLayerIfInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/alias-macs
	// Description: Augments interfaces with range of alias MAC addresses.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAliasMacs aliasMacsInst(ITEM_ALIAS_MACS);
	aliasMacsInst.initialise();
	addList(aliasMacsInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces/interface/statistics
	// Description: A collection of interface-related statistics objects.
	// -----------------------------------------------------------------------------
	CntStatistics statisticsInst(ITEM_STATISTICS);
	statisticsInst.initialise();
	addContainer(statisticsInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces/interface/ipv4
	// Description: Parameters for the IPv4 address family.
	// -----------------------------------------------------------------------------
	CntIpv4 ipv4Inst(ITEM_IPV4);
	ipv4Inst.initialise();
	addContainer(ipv4Inst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces/interface/ipv6
	// Description: Parameters for the IPv6 address family.
	// -----------------------------------------------------------------------------
	CntIpv6 ipv6Inst(ITEM_IPV6);
	ipv6Inst.initialise();
	addContainer(ipv6Inst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces/interface/port-reference
	// Description: a port reference used by other O-RAN modules
	// -----------------------------------------------------------------------------
	CntPortReference portReferenceInst(ITEM_PORT_REFERENCE);
	portReferenceInst.initialise();
	addContainer(portReferenceInst);

	// -----------------------------------------------------------------------------
	// Uses:        /interfaces/interface/cos-marking
	// Module: o-ran-interfaces
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanInterfaces_NS::GrpCosMarking cosMarkingInst(ITEM_COS_MARKING);
	cosMarkingInst.initialise();
	addGroup(cosMarkingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/name
// Description: The name of the interface.
//              A device MAY restrict the allowed values for this leaf,
//              possibly depending on the type of the interface.
//              For system-controlled interfaces, this leaf is the
//              device-specific name of the interface.
//              If a client tries to create configuration for a
//              system-controlled interface that is not present in the
//              operational state, the server MAY reject the request if
//              the implementation does not support pre-provisioning of
//              interfaces or if the name refers to an interface that can
//              never exist in the system.  A Network Configuration
//              Protocol (NETCONF) server MUST reply with an rpc-error
//              with the error-tag 'invalid-value' in this case.
//              If the device supports pre-provisioning of interface
//              configuration, the 'pre-provisioning' feature is
//              advertised.
//              If the device allows arbitrarily named user-controlled
//              interfaces, the 'arbitrary-names' feature is advertised.
//              When a configured user-controlled interface is created by
//              the system, it is instantiated with the same name in the
//              operational state.
//              A server implementation MAY map this leaf to the ifName
//              MIB object.  Such an implementation needs to use some
//              mechanism to handle the differences in size and characters
//              allowed between this leaf and ifName.  The definition of
//              such a mechanism is outside the scope of this document.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

CntInterfaces::LstInterface::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/description
// Description: A textual description of the interface.
//              A server implementation MAY map this leaf to the ifAlias
//              MIB object.  Such an implementation needs to use some
//              mechanism to handle the differences in size and characters
//              allowed between this leaf and ifAlias.  The definition of
//              such a mechanism is outside the scope of this document.
//              Since ifAlias is defined to be stored in non-volatile
//              storage, the MIB implementation MUST map ifAlias to the
//              value of 'description' in the persistently stored
//              configuration.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafDescription::LeafDescription(uint32_t id)
	: YangLeaf("description", id)
{
}

CntInterfaces::LstInterface::LeafDescription::~LeafDescription()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/type
// Description: The type of the interface.
//              When an interface entry is created, a server MAY
//              initialize the type leaf with a valid value, e.g., if it
//              is possible to derive the type from the name of the
//              interface.
//              If a client tries to set the type of an interface to a
//              value that can never be used by the system, e.g., if the
//              type is not supported or if the type does not match the
//              name of the interface, the server MUST reject the request.
//              A NETCONF server MUST reply with an rpc-error with the
//              error-tag 'invalid-value' in this case.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafType::LeafType(uint32_t id)
	: YangLeaf("type", id)
{
}

CntInterfaces::LstInterface::LeafType::~LeafType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/enabled
// Description: This leaf contains the configured, desired state of the
//              interface.
//              Systems that implement the IF-MIB use the value of this
//              leaf in the intended configuration to set
//              IF-MIB.ifAdminStatus to 'up' or 'down' after an ifEntry
//              has been initialized, as described in RFC 2863.
//              Changes in this leaf in the intended configuration are
//              reflected in ifAdminStatus.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafEnabled::LeafEnabled(uint32_t id)
	: YangLeaf("enabled", id)
{
}

CntInterfaces::LstInterface::LeafEnabled::~LeafEnabled()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/link-up-down-trap-enable
// Description: Controls whether linkUp/linkDown SNMP notifications
//              should be generated for this interface.
//              If this node is not configured, the value 'enabled' is
//              operationally used by the server for interfaces that do
//              not operate on top of any other interface (i.e., there are
//              no 'lower-layer-if' entries), and 'disabled' otherwise.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafLinkUpDownTrapEnable::LeafLinkUpDownTrapEnable(uint32_t id)
	: YangLeaf("link-up-down-trap-enable", id)
{
}

CntInterfaces::LstInterface::LeafLinkUpDownTrapEnable::~LeafLinkUpDownTrapEnable()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/admin-status
// Description: The desired state of the interface.
//              This leaf has the same read semantics as ifAdminStatus.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafAdminStatus::LeafAdminStatus(uint32_t id)
	: YangLeaf("admin-status", id)
{
}

CntInterfaces::LstInterface::LeafAdminStatus::~LeafAdminStatus()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/oper-status
// Description: The current operational state of the interface.
//              This leaf has the same semantics as ifOperStatus.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafOperStatus::LeafOperStatus(uint32_t id)
	: YangLeaf("oper-status", id)
{
}

CntInterfaces::LstInterface::LeafOperStatus::~LeafOperStatus()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/last-change
// Description: The time the interface entered its current operational
//              state.  If the current state was entered prior to the
//              last re-initialization of the local network management
//              subsystem, then this node is not present.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafLastChange::LeafLastChange(uint32_t id)
	: YangLeaf("last-change", id)
{
}

CntInterfaces::LstInterface::LeafLastChange::~LeafLastChange()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/if-index
// Description: The ifIndex value for the ifEntry represented by this
//              interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafIfIndex::LeafIfIndex(uint32_t id)
	: YangLeaf("if-index", id)
{
}

CntInterfaces::LstInterface::LeafIfIndex::~LeafIfIndex()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/phys-address
// Description: The interface's address at its protocol sub-layer.  For
//              example, for an 802.x interface, this object normally
//              contains a Media Access Control (MAC) address.  The
//              interface's media-specific modules must define the bit
//              and byte ordering and the format of the value of this
//              object.  For interfaces that do not have such an address
//              (e.g., a serial line), this node is not present.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafPhysAddress::LeafPhysAddress(uint32_t id)
	: YangLeaf("phys-address", id)
{
}

CntInterfaces::LstInterface::LeafPhysAddress::~LeafPhysAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/speed
// Description: An estimate of the interface's current bandwidth in bits
//              per second.  For interfaces that do not vary in
//              bandwidth or for those where no accurate estimation can
//              be made, this node should contain the nominal bandwidth.
//              For interfaces that have no concept of bandwidth, this
//              node is not present.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafSpeed::LeafSpeed(uint32_t id)
	: YangLeaf("speed", id)
{
}

CntInterfaces::LstInterface::LeafSpeed::~LeafSpeed()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/l2-mtu
// Description: The maximum size of layer 2 frames that may be transmitted
//              or received on the interface (excluding any FCS overhead).
//              For Ethernet interfaces it also excludes the
//              4-8 byte overhead of any known (i.e. explicitly matched by
//              a child sub-interface) 801.1Q VLAN tags.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafL2Mtu::LeafL2Mtu(uint32_t id)
	: YangLeaf("l2-mtu", id)
{
}

CntInterfaces::LstInterface::LeafL2Mtu::~LeafL2Mtu()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/vlan-tagging
// Description: Indicates if VLAN tagging is used.
//              Default true is used to enable equipment to auonomously discover that it is
//              connected to a trunk port.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafVlanTagging::LeafVlanTagging(uint32_t id)
	: YangLeaf("vlan-tagging", id)
{
}

CntInterfaces::LstInterface::LeafVlanTagging::~LeafVlanTagging()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/vlan-id
// Description: The VLAN-ID.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafVlanId::LeafVlanId(uint32_t id)
	: YangLeaf("vlan-id", id)
{
}

CntInterfaces::LstInterface::LeafVlanId::~LeafVlanId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/last-cleared
// Description: Timestamp of the last time the interface counters were
//              cleared.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafLastCleared::LeafLastCleared(uint32_t id)
	: YangLeaf("last-cleared", id)
{
}

CntInterfaces::LstInterface::LeafLastCleared::~LeafLastCleared()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/mac-address
// Description: The MAC address of the interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LeafMacAddress::LeafMacAddress(uint32_t id)
	: YangLeaf("mac-address", id)
{
}

CntInterfaces::LstInterface::LeafMacAddress::~LeafMacAddress()
{
}

// -----------------------------------------------------------------------------
// Reference:   /interfaces/interface/base-interface
// Description: The base interface for the VLAN sub-interafce.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::RefBaseInterface::RefBaseInterface(uint32_t id)
	: YangReference("base-interface", id, "[reference]")
{
}

CntInterfaces::LstInterface::RefBaseInterface::~RefBaseInterface()
{
}

// -----------------------------------------------------------------------------
// List:        higher-layer-if
// Description: A list of references to interfaces layered on top of this
//              interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LstHigherLayerIf::LstHigherLayerIf(uint32_t id)
	: YangList("higher-layer-if", id)
{
}

CntInterfaces::LstInterface::LstHigherLayerIf::~LstHigherLayerIf()
{
}

YangResult_E CntInterfaces::LstInterface::LstHigherLayerIf::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        lower-layer-if
// Description: A list of references to interfaces layered underneath this
//              interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LstLowerLayerIf::LstLowerLayerIf(uint32_t id)
	: YangList("lower-layer-if", id)
{
}

CntInterfaces::LstInterface::LstLowerLayerIf::~LstLowerLayerIf()
{
}

YangResult_E CntInterfaces::LstInterface::LstLowerLayerIf::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        alias-macs
// Description: Augments interfaces with range of alias MAC addresses.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::LstAliasMacs::LstAliasMacs(uint32_t id)
	: YangList("alias-macs", id)
{
}

CntInterfaces::LstInterface::LstAliasMacs::~LstAliasMacs()
{
}

YangResult_E CntInterfaces::LstInterface::LstAliasMacs::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Container:   statistics
// Description: A collection of interface-related statistics objects.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::CntStatistics(uint32_t id)
	: YangContainer("statistics", id)
{
}

CntInterfaces::LstInterface::CntStatistics::~CntStatistics()
{
}

YangResult_E CntInterfaces::LstInterface::CntStatistics::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/discontinuity-time
	// Description: The time on the most recent occasion at which any one or
	//              more of this interface's counters suffered a
	//              discontinuity.  If no such discontinuities have occurred
	//              since the last re-initialization of the local management
	//              subsystem, then this node contains the time the local
	//              management subsystem re-initialized itself.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDiscontinuityTime discontinuityTimeInst(ITEM_DISCONTINUITY_TIME);
	addLeaf(discontinuityTimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-octets
	// Description: The total number of octets received on the interface,
	//              including framing characters.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInOctets inOctetsInst(ITEM_IN_OCTETS);
	addLeaf(inOctetsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-unicast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were not addressed to a
	//              multicast or broadcast address at this sub-layer.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInUnicastPkts inUnicastPktsInst(ITEM_IN_UNICAST_PKTS);
	addLeaf(inUnicastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-broadcast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were addressed to a broadcast
	//              address at this sub-layer.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInBroadcastPkts inBroadcastPktsInst(ITEM_IN_BROADCAST_PKTS);
	addLeaf(inBroadcastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-multicast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were addressed to a multicast
	//              address at this sub-layer.  For a MAC-layer protocol,
	//              this includes both Group and Functional addresses.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInMulticastPkts inMulticastPktsInst(ITEM_IN_MULTICAST_PKTS);
	addLeaf(inMulticastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-discards
	// Description: The number of inbound packets that were chosen to be
	//              discarded even though no errors had been detected to
	//              prevent their being deliverable to a higher-layer
	//              protocol.  One possible reason for discarding such a
	//              packet could be to free up buffer space.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInDiscards inDiscardsInst(ITEM_IN_DISCARDS);
	addLeaf(inDiscardsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-errors
	// Description: For packet-oriented interfaces, the number of inbound
	//              packets that contained errors preventing them from being
	//              deliverable to a higher-layer protocol.  For character-
	//              oriented or fixed-length interfaces, the number of
	//              inbound transmission units that contained errors
	//              preventing them from being deliverable to a higher-layer
	//              protocol.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInErrors inErrorsInst(ITEM_IN_ERRORS);
	addLeaf(inErrorsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/in-unknown-protos
	// Description: For packet-oriented interfaces, the number of packets
	//              received via the interface that were discarded because
	//              of an unknown or unsupported protocol.  For
	//              character-oriented or fixed-length interfaces that
	//              support protocol multiplexing, the number of
	//              transmission units received via the interface that were
	//              discarded because of an unknown or unsupported protocol.
	//              For any interface that does not support protocol
	//              multiplexing, this counter is not present.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInUnknownProtos inUnknownProtosInst(ITEM_IN_UNKNOWN_PROTOS);
	addLeaf(inUnknownProtosInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-octets
	// Description: The total number of octets transmitted out of the
	//              interface, including framing characters.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutOctets outOctetsInst(ITEM_OUT_OCTETS);
	addLeaf(outOctetsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-unicast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were not addressed
	//              to a multicast or broadcast address at this sub-layer,
	//              including those that were discarded or not sent.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutUnicastPkts outUnicastPktsInst(ITEM_OUT_UNICAST_PKTS);
	addLeaf(outUnicastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-broadcast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were addressed to a
	//              broadcast address at this sub-layer, including those
	//              that were discarded or not sent.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutBroadcastPkts outBroadcastPktsInst(ITEM_OUT_BROADCAST_PKTS);
	addLeaf(outBroadcastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-multicast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were addressed to a
	//              multicast address at this sub-layer, including those
	//              that were discarded or not sent.  For a MAC-layer
	//              protocol, this includes both Group and Functional
	//              addresses.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutMulticastPkts outMulticastPktsInst(ITEM_OUT_MULTICAST_PKTS);
	addLeaf(outMulticastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-discards
	// Description: The number of outbound packets that were chosen to be
	//              discarded even though no errors had been detected to
	//              prevent their being transmitted.  One possible reason
	//              for discarding such a packet could be to free up buffer
	//              space.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutDiscards outDiscardsInst(ITEM_OUT_DISCARDS);
	addLeaf(outDiscardsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/statistics/out-errors
	// Description: For packet-oriented interfaces, the number of outbound
	//              packets that could not be transmitted because of errors.
	//              For character-oriented or fixed-length interfaces, the
	//              number of outbound transmission units that could not be
	//              transmitted because of errors.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutErrors outErrorsInst(ITEM_OUT_ERRORS);
	addLeaf(outErrorsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/discontinuity-time
// Description: The time on the most recent occasion at which any one or
//              more of this interface's counters suffered a
//              discontinuity.  If no such discontinuities have occurred
//              since the last re-initialization of the local management
//              subsystem, then this node contains the time the local
//              management subsystem re-initialized itself.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafDiscontinuityTime::LeafDiscontinuityTime(uint32_t id)
	: YangLeaf("discontinuity-time", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafDiscontinuityTime::~LeafDiscontinuityTime()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-octets
// Description: The total number of octets received on the interface,
//              including framing characters.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInOctets::LeafInOctets(uint32_t id)
	: YangLeaf("in-octets", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInOctets::~LeafInOctets()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-unicast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were not addressed to a
//              multicast or broadcast address at this sub-layer.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInUnicastPkts::LeafInUnicastPkts(uint32_t id)
	: YangLeaf("in-unicast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInUnicastPkts::~LeafInUnicastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-broadcast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were addressed to a broadcast
//              address at this sub-layer.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInBroadcastPkts::LeafInBroadcastPkts(uint32_t id)
	: YangLeaf("in-broadcast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInBroadcastPkts::~LeafInBroadcastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-multicast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were addressed to a multicast
//              address at this sub-layer.  For a MAC-layer protocol,
//              this includes both Group and Functional addresses.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInMulticastPkts::LeafInMulticastPkts(uint32_t id)
	: YangLeaf("in-multicast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInMulticastPkts::~LeafInMulticastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-discards
// Description: The number of inbound packets that were chosen to be
//              discarded even though no errors had been detected to
//              prevent their being deliverable to a higher-layer
//              protocol.  One possible reason for discarding such a
//              packet could be to free up buffer space.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInDiscards::LeafInDiscards(uint32_t id)
	: YangLeaf("in-discards", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInDiscards::~LeafInDiscards()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-errors
// Description: For packet-oriented interfaces, the number of inbound
//              packets that contained errors preventing them from being
//              deliverable to a higher-layer protocol.  For character-
//              oriented or fixed-length interfaces, the number of
//              inbound transmission units that contained errors
//              preventing them from being deliverable to a higher-layer
//              protocol.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInErrors::LeafInErrors(uint32_t id)
	: YangLeaf("in-errors", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInErrors::~LeafInErrors()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/in-unknown-protos
// Description: For packet-oriented interfaces, the number of packets
//              received via the interface that were discarded because
//              of an unknown or unsupported protocol.  For
//              character-oriented or fixed-length interfaces that
//              support protocol multiplexing, the number of
//              transmission units received via the interface that were
//              discarded because of an unknown or unsupported protocol.
//              For any interface that does not support protocol
//              multiplexing, this counter is not present.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafInUnknownProtos::LeafInUnknownProtos(uint32_t id)
	: YangLeaf("in-unknown-protos", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafInUnknownProtos::~LeafInUnknownProtos()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-octets
// Description: The total number of octets transmitted out of the
//              interface, including framing characters.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutOctets::LeafOutOctets(uint32_t id)
	: YangLeaf("out-octets", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutOctets::~LeafOutOctets()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-unicast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were not addressed
//              to a multicast or broadcast address at this sub-layer,
//              including those that were discarded or not sent.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutUnicastPkts::LeafOutUnicastPkts(uint32_t id)
	: YangLeaf("out-unicast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutUnicastPkts::~LeafOutUnicastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-broadcast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were addressed to a
//              broadcast address at this sub-layer, including those
//              that were discarded or not sent.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutBroadcastPkts::LeafOutBroadcastPkts(uint32_t id)
	: YangLeaf("out-broadcast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutBroadcastPkts::~LeafOutBroadcastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-multicast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were addressed to a
//              multicast address at this sub-layer, including those
//              that were discarded or not sent.  For a MAC-layer
//              protocol, this includes both Group and Functional
//              addresses.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutMulticastPkts::LeafOutMulticastPkts(uint32_t id)
	: YangLeaf("out-multicast-pkts", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutMulticastPkts::~LeafOutMulticastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-discards
// Description: The number of outbound packets that were chosen to be
//              discarded even though no errors had been detected to
//              prevent their being transmitted.  One possible reason
//              for discarding such a packet could be to free up buffer
//              space.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutDiscards::LeafOutDiscards(uint32_t id)
	: YangLeaf("out-discards", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutDiscards::~LeafOutDiscards()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/statistics/out-errors
// Description: For packet-oriented interfaces, the number of outbound
//              packets that could not be transmitted because of errors.
//              For character-oriented or fixed-length interfaces, the
//              number of outbound transmission units that could not be
//              transmitted because of errors.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntStatistics::LeafOutErrors::LeafOutErrors(uint32_t id)
	: YangLeaf("out-errors", id)
{
}

CntInterfaces::LstInterface::CntStatistics::LeafOutErrors::~LeafOutErrors()
{
}




// -----------------------------------------------------------------------------
// Container:   ipv4
// Description: Parameters for the IPv4 address family.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::CntIpv4(uint32_t id)
	: YangContainer("ipv4", id)
{
}

CntInterfaces::LstInterface::CntIpv4::~CntIpv4()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/enabled
	// Description: Controls whether IPv4 is enabled or disabled on this
	//              interface.  When IPv4 is enabled, this interface is
	//              connected to an IPv4 stack, and the interface can send
	//              and receive IPv4 packets.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnabled enabledInst(ITEM_ENABLED);
	addLeaf(enabledInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/forwarding
	// Description: Controls IPv4 packet forwarding of datagrams received by,
	//              but not addressed to, this interface.  IPv4 routers
	//              forward datagrams.  IPv4 hosts do not (except those
	//              source-routed via the host).
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafForwarding forwardingInst(ITEM_FORWARDING);
	addLeaf(forwardingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/mtu
	// Description: The size, in octets, of the largest IPv4 packet that the
	//              interface will send and receive.
	//              The server may restrict the allowed values for this leaf,
	//              depending on the interface's type.
	//              If this leaf is not configured, the operationally used MTU
	//              depends on the interface's type.
	// Type:        uint16
	// Units:       octets
	// -----------------------------------------------------------------------------
	LeafMtu mtuInst(ITEM_MTU);
	addLeaf(mtuInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/m-plane-marking
	// Description: 18 represents AF21 or 'immediate traffic'
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafMPlaneMarking mPlaneMarkingInst(ITEM_M_PLANE_MARKING);
	addLeaf(mPlaneMarkingInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/ipv4/address
	// Description: The list of IPv4 addresses on the interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAddress addressInst(ITEM_ADDRESS);
	addressInst.initialise();
	addList(addressInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/ipv4/neighbor
	// Description: A list of mappings from IPv4 addresses to
	//              link-layer addresses.
	//              Entries in this list in the intended configuration are
	//              used as static entries in the ARP Cache.
	//              In the operational state, this list represents the ARP
	//              Cache.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNeighbor neighborInst(ITEM_NEIGHBOR);
	neighborInst.initialise();
	addList(neighborInst);

	// -----------------------------------------------------------------------------
	// Uses:        /interfaces/interface/ipv4/dscp-marking
	// Module: o-ran-interfaces
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanInterfaces_NS::GrpDscpMarking dscpMarkingInst(ITEM_DSCP_MARKING);
	dscpMarkingInst.initialise();
	addGroup(dscpMarkingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/enabled
// Description: Controls whether IPv4 is enabled or disabled on this
//              interface.  When IPv4 is enabled, this interface is
//              connected to an IPv4 stack, and the interface can send
//              and receive IPv4 packets.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LeafEnabled::LeafEnabled(uint32_t id)
	: YangLeaf("enabled", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LeafEnabled::~LeafEnabled()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/forwarding
// Description: Controls IPv4 packet forwarding of datagrams received by,
//              but not addressed to, this interface.  IPv4 routers
//              forward datagrams.  IPv4 hosts do not (except those
//              source-routed via the host).
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LeafForwarding::LeafForwarding(uint32_t id)
	: YangLeaf("forwarding", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LeafForwarding::~LeafForwarding()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/mtu
// Description: The size, in octets, of the largest IPv4 packet that the
//              interface will send and receive.
//              The server may restrict the allowed values for this leaf,
//              depending on the interface's type.
//              If this leaf is not configured, the operationally used MTU
//              depends on the interface's type.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LeafMtu::LeafMtu(uint32_t id)
	: YangLeaf("mtu", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LeafMtu::~LeafMtu()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/m-plane-marking
// Description: 18 represents AF21 or 'immediate traffic'
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LeafMPlaneMarking::LeafMPlaneMarking(uint32_t id)
	: YangLeaf("m-plane-marking", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LeafMPlaneMarking::~LeafMPlaneMarking()
{
}

// -----------------------------------------------------------------------------
// List:        address
// Description: The list of IPv4 addresses on the interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::LstAddress(uint32_t id)
	: YangList("address", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::~LstAddress()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::LstAddress::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/address/ip
	// Description: The IPv4 address on the interface.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/address/origin
	// Description: The origin of this address.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Choice:      /interfaces/interface/ipv4/address/subnet
	// Description: The subnet can be specified as a prefix length or,
	//              if the server supports non-contiguous netmasks, as
	//              a netmask.
	// Type:        Subnet_E
	// Units:       -
	// -----------------------------------------------------------------------------
	ChoiceSubnet subnetInst(ITEM_SUBNET);
	subnetInst.initialise();
	addChoice(subnetInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/address/ip
// Description: The IPv4 address on the interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/address/origin
// Description: The origin of this address.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Choice:      subnet
// Description: The subnet can be specified as a prefix length or,
//              if the server supports non-contiguous netmasks, as
//              a netmask.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::ChoiceSubnet(uint32_t id)
	: YangChoice("subnet", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::~ChoiceSubnet()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::initialise(void)
{

	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptPrefixLength prefixLength(ITEM_PREFIX_LENGTH);
	prefixLength.initialise();
	addOption(prefixLength);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptNetmask netmask(ITEM_NETMASK);
	netmask.initialise();
	addOption(netmask);



	return YangResult_E::OK;
}


// -------------------------------------------------------------------------
// Option:      /interfaces/interface/ipv4/address/subnet[prefix-length]
// -------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::OptPrefixLength(uint32_t id)
	: YangChoiceOption("prefix-length", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::~OptPrefixLength()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/address/subnet[prefix-length]/prefix-length
	// Description: The length of the subnet prefix.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrefixLength prefixLengthInst(ITEM_PREFIX_LENGTH);
	addLeaf(prefixLengthInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/address/subnet[prefix-length]/prefix-length
// Description: The length of the subnet prefix.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::LeafPrefixLength::LeafPrefixLength(uint32_t id)
	: YangLeaf("prefix-length", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::LeafPrefixLength::~LeafPrefixLength()
{
}



// -------------------------------------------------------------------------
// Option:      /interfaces/interface/ipv4/address/subnet[netmask]
// -------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::OptNetmask(uint32_t id)
	: YangChoiceOption("netmask", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::~OptNetmask()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/address/subnet[netmask]/netmask
	// Description: The subnet specified as a netmask.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafNetmask netmaskInst(ITEM_NETMASK);
	addLeaf(netmaskInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/address/subnet[netmask]/netmask
// Description: The subnet specified as a netmask.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::LeafNetmask::LeafNetmask(uint32_t id)
	: YangLeaf("netmask", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::LeafNetmask::~LeafNetmask()
{
}








// -----------------------------------------------------------------------------
// List:        neighbor
// Description: A list of mappings from IPv4 addresses to
//              link-layer addresses.
//              Entries in this list in the intended configuration are
//              used as static entries in the ARP Cache.
//              In the operational state, this list represents the ARP
//              Cache.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LstNeighbor(uint32_t id)
	: YangList("neighbor", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstNeighbor::~LstNeighbor()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv4::LstNeighbor::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/neighbor/ip
	// Description: The IPv4 address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/neighbor/link-layer-address
	// Description: The link-layer address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLinkLayerAddress linkLayerAddressInst(ITEM_LINK_LAYER_ADDRESS);
	addLeaf(linkLayerAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv4/neighbor/origin
	// Description: The origin of this neighbor entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/neighbor/ip
// Description: The IPv4 address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/neighbor/link-layer-address
// Description: The link-layer address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafLinkLayerAddress::LeafLinkLayerAddress(uint32_t id)
	: YangLeaf("link-layer-address", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafLinkLayerAddress::~LeafLinkLayerAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv4/neighbor/origin
// Description: The origin of this neighbor entry.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfaces::LstInterface::CntIpv4::LstNeighbor::LeafOrigin::~LeafOrigin()
{
}






// -----------------------------------------------------------------------------
// Container:   ipv6
// Description: Parameters for the IPv6 address family.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntIpv6(uint32_t id)
	: YangContainer("ipv6", id)
{
}

CntInterfaces::LstInterface::CntIpv6::~CntIpv6()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv6::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/enabled
	// Description: Controls whether IPv6 is enabled or disabled on this
	//              interface.  When IPv6 is enabled, this interface is
	//              connected to an IPv6 stack, and the interface can send
	//              and receive IPv6 packets.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnabled enabledInst(ITEM_ENABLED);
	addLeaf(enabledInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/forwarding
	// Description: Controls IPv6 packet forwarding of datagrams received by,
	//              but not addressed to, this interface.  IPv6 routers
	//              forward datagrams.  IPv6 hosts do not (except those
	//              source-routed via the host).
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafForwarding forwardingInst(ITEM_FORWARDING);
	addLeaf(forwardingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/mtu
	// Description: The size, in octets, of the largest IPv6 packet that the
	//              interface will send and receive.
	//              The server may restrict the allowed values for this leaf,
	//              depending on the interface's type.
	//              If this leaf is not configured, the operationally used MTU
	//              depends on the interface's type.
	// Type:        uint32
	// Units:       octets
	// -----------------------------------------------------------------------------
	LeafMtu mtuInst(ITEM_MTU);
	addLeaf(mtuInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/dup-addr-detect-transmits
	// Description: The number of consecutive Neighbor Solicitation messages
	//              sent while performing Duplicate Address Detection on a
	//              tentative address.  A value of zero indicates that
	//              Duplicate Address Detection is not performed on
	//              tentative addresses.  A value of one indicates a single
	//              transmission with no follow-up retransmissions.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDupAddrDetectTransmits dupAddrDetectTransmitsInst(ITEM_DUP_ADDR_DETECT_TRANSMITS);
	addLeaf(dupAddrDetectTransmitsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/m-plane-marking
	// Description: 18 represents AF21 or 'immediate traffic'
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafMPlaneMarking mPlaneMarkingInst(ITEM_M_PLANE_MARKING);
	addLeaf(mPlaneMarkingInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/ipv6/address
	// Description: The list of IPv6 addresses on the interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAddress addressInst(ITEM_ADDRESS);
	addressInst.initialise();
	addList(addressInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces/interface/ipv6/neighbor
	// Description: A list of mappings from IPv6 addresses to
	//              link-layer addresses.
	//              Entries in this list in the intended configuration are
	//              used as static entries in the Neighbor Cache.
	//              In the operational state, this list represents the
	//              Neighbor Cache.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNeighbor neighborInst(ITEM_NEIGHBOR);
	neighborInst.initialise();
	addList(neighborInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces/interface/ipv6/autoconf
	// Description: Parameters to control the autoconfiguration of IPv6
	//              addresses, as described in RFC 4862.
	// -----------------------------------------------------------------------------
	CntAutoconf autoconfInst(ITEM_AUTOCONF);
	autoconfInst.initialise();
	addContainer(autoconfInst);

	// -----------------------------------------------------------------------------
	// Uses:        /interfaces/interface/ipv6/dscp-marking
	// Module: o-ran-interfaces
	// Description:
	// -----------------------------------------------------------------------------
	ModuleORanInterfaces_NS::GrpDscpMarking dscpMarkingInst(ITEM_DSCP_MARKING);
	dscpMarkingInst.initialise();
	addGroup(dscpMarkingInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/enabled
// Description: Controls whether IPv6 is enabled or disabled on this
//              interface.  When IPv6 is enabled, this interface is
//              connected to an IPv6 stack, and the interface can send
//              and receive IPv6 packets.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LeafEnabled::LeafEnabled(uint32_t id)
	: YangLeaf("enabled", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LeafEnabled::~LeafEnabled()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/forwarding
// Description: Controls IPv6 packet forwarding of datagrams received by,
//              but not addressed to, this interface.  IPv6 routers
//              forward datagrams.  IPv6 hosts do not (except those
//              source-routed via the host).
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LeafForwarding::LeafForwarding(uint32_t id)
	: YangLeaf("forwarding", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LeafForwarding::~LeafForwarding()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/mtu
// Description: The size, in octets, of the largest IPv6 packet that the
//              interface will send and receive.
//              The server may restrict the allowed values for this leaf,
//              depending on the interface's type.
//              If this leaf is not configured, the operationally used MTU
//              depends on the interface's type.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LeafMtu::LeafMtu(uint32_t id)
	: YangLeaf("mtu", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LeafMtu::~LeafMtu()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/dup-addr-detect-transmits
// Description: The number of consecutive Neighbor Solicitation messages
//              sent while performing Duplicate Address Detection on a
//              tentative address.  A value of zero indicates that
//              Duplicate Address Detection is not performed on
//              tentative addresses.  A value of one indicates a single
//              transmission with no follow-up retransmissions.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LeafDupAddrDetectTransmits::LeafDupAddrDetectTransmits(uint32_t id)
	: YangLeaf("dup-addr-detect-transmits", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LeafDupAddrDetectTransmits::~LeafDupAddrDetectTransmits()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/m-plane-marking
// Description: 18 represents AF21 or 'immediate traffic'
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LeafMPlaneMarking::LeafMPlaneMarking(uint32_t id)
	: YangLeaf("m-plane-marking", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LeafMPlaneMarking::~LeafMPlaneMarking()
{
}

// -----------------------------------------------------------------------------
// List:        address
// Description: The list of IPv6 addresses on the interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstAddress::LstAddress(uint32_t id)
	: YangList("address", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstAddress::~LstAddress()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv6::LstAddress::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/address/ip
	// Description: The IPv6 address on the interface.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/address/prefix-length
	// Description: The length of the subnet prefix.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrefixLength prefixLengthInst(ITEM_PREFIX_LENGTH);
	addLeaf(prefixLengthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/address/origin
	// Description: The origin of this address.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/address/status
	// Description: The status of an address.  Most of the states correspond
	//              to states from the IPv6 Stateless Address
	//              Autoconfiguration protocol.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafStatus statusInst(ITEM_STATUS);
	addLeaf(statusInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/address/ip
// Description: The IPv6 address on the interface.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/address/prefix-length
// Description: The length of the subnet prefix.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafPrefixLength::LeafPrefixLength(uint32_t id)
	: YangLeaf("prefix-length", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafPrefixLength::~LeafPrefixLength()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/address/origin
// Description: The origin of this address.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/address/status
// Description: The status of an address.  Most of the states correspond
//              to states from the IPv6 Stateless Address
//              Autoconfiguration protocol.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafStatus::LeafStatus(uint32_t id)
	: YangLeaf("status", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstAddress::LeafStatus::~LeafStatus()
{
}



// -----------------------------------------------------------------------------
// List:        neighbor
// Description: A list of mappings from IPv6 addresses to
//              link-layer addresses.
//              Entries in this list in the intended configuration are
//              used as static entries in the Neighbor Cache.
//              In the operational state, this list represents the
//              Neighbor Cache.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LstNeighbor(uint32_t id)
	: YangList("neighbor", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::~LstNeighbor()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv6::LstNeighbor::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/neighbor/ip
	// Description: The IPv6 address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/neighbor/link-layer-address
	// Description: The link-layer address of the neighbor node.
	//              In the operational state, if the neighbor's 'state' leaf
	//              is 'incomplete', this leaf is not instantiated.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLinkLayerAddress linkLayerAddressInst(ITEM_LINK_LAYER_ADDRESS);
	addLeaf(linkLayerAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/neighbor/origin
	// Description: The origin of this neighbor entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/neighbor/is-router
	// Description: Indicates that the neighbor node acts as a router.
	// Type:        UNKNOWN:5
	// Units:
	// -----------------------------------------------------------------------------
	LeafIsRouter isRouterInst(ITEM_IS_ROUTER);
	addLeaf(isRouterInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/neighbor/state
	// Description: The Neighbor Unreachability Detection state of this
	//              entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/neighbor/ip
// Description: The IPv6 address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/neighbor/link-layer-address
// Description: The link-layer address of the neighbor node.
//              In the operational state, if the neighbor's 'state' leaf
//              is 'incomplete', this leaf is not instantiated.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafLinkLayerAddress::LeafLinkLayerAddress(uint32_t id)
	: YangLeaf("link-layer-address", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafLinkLayerAddress::~LeafLinkLayerAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/neighbor/origin
// Description: The origin of this neighbor entry.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/neighbor/is-router
// Description: Indicates that the neighbor node acts as a router.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafIsRouter::LeafIsRouter(uint32_t id)
	: YangLeaf("is-router", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafIsRouter::~LeafIsRouter()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/neighbor/state
// Description: The Neighbor Unreachability Detection state of this
//              entry.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

CntInterfaces::LstInterface::CntIpv6::LstNeighbor::LeafState::~LeafState()
{
}



// -----------------------------------------------------------------------------
// Container:   autoconf
// Description: Parameters to control the autoconfiguration of IPv6
//              addresses, as described in RFC 4862.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntAutoconf::CntAutoconf(uint32_t id)
	: YangContainer("autoconf", id)
{
}

CntInterfaces::LstInterface::CntIpv6::CntAutoconf::~CntAutoconf()
{
}

YangResult_E CntInterfaces::LstInterface::CntIpv6::CntAutoconf::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/autoconf/create-global-addresses
	// Description: If enabled, the host creates global addresses as
	//              described in RFC 4862.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafCreateGlobalAddresses createGlobalAddressesInst(ITEM_CREATE_GLOBAL_ADDRESSES);
	addLeaf(createGlobalAddressesInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/autoconf/create-temporary-addresses
	// Description: If enabled, the host creates temporary addresses as
	//              described in RFC 4941.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafCreateTemporaryAddresses createTemporaryAddressesInst(ITEM_CREATE_TEMPORARY_ADDRESSES);
	addLeaf(createTemporaryAddressesInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-valid-lifetime
	// Description: The time period during which the temporary address
	//              is valid.
	// Type:        uint32
	// Units:       seconds
	// -----------------------------------------------------------------------------
	LeafTemporaryValidLifetime temporaryValidLifetimeInst(ITEM_TEMPORARY_VALID_LIFETIME);
	addLeaf(temporaryValidLifetimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-preferred-lifetime
	// Description: The time period during which the temporary address is
	//              preferred.
	// Type:        uint32
	// Units:       seconds
	// -----------------------------------------------------------------------------
	LeafTemporaryPreferredLifetime temporaryPreferredLifetimeInst(ITEM_TEMPORARY_PREFERRED_LIFETIME);
	addLeaf(temporaryPreferredLifetimeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/autoconf/create-global-addresses
// Description: If enabled, the host creates global addresses as
//              described in RFC 4862.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafCreateGlobalAddresses::LeafCreateGlobalAddresses(uint32_t id)
	: YangLeaf("create-global-addresses", id)
{
}

CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafCreateGlobalAddresses::~LeafCreateGlobalAddresses()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/autoconf/create-temporary-addresses
// Description: If enabled, the host creates temporary addresses as
//              described in RFC 4941.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafCreateTemporaryAddresses::LeafCreateTemporaryAddresses(uint32_t id)
	: YangLeaf("create-temporary-addresses", id)
{
}

CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafCreateTemporaryAddresses::~LeafCreateTemporaryAddresses()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-valid-lifetime
// Description: The time period during which the temporary address
//              is valid.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafTemporaryValidLifetime::LeafTemporaryValidLifetime(uint32_t id)
	: YangLeaf("temporary-valid-lifetime", id)
{
}

CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafTemporaryValidLifetime::~LeafTemporaryValidLifetime()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-preferred-lifetime
// Description: The time period during which the temporary address is
//              preferred.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafTemporaryPreferredLifetime::LeafTemporaryPreferredLifetime(uint32_t id)
	: YangLeaf("temporary-preferred-lifetime", id)
{
}

CntInterfaces::LstInterface::CntIpv6::CntAutoconf::LeafTemporaryPreferredLifetime::~LeafTemporaryPreferredLifetime()
{
}







// -----------------------------------------------------------------------------
// Container:   port-reference
// Description: a port reference used by other O-RAN modules
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntPortReference::CntPortReference(uint32_t id)
	: YangContainer("port-reference", id)
{
}

CntInterfaces::LstInterface::CntPortReference::~CntPortReference()
{
}

YangResult_E CntInterfaces::LstInterface::CntPortReference::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces/interface/port-reference/port-number
	// Description: A number allocated by the server which identifies a port.
	//              Port number value is 0 to N-1 where N is number of ports
	//              in the device.
	//
	//              This value is fixed for the lifetime of the equipment, i.e., cannot be
	//              changed during equipment reboots.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPortNumber portNumberInst(ITEM_PORT_NUMBER);
	addLeaf(portNumberInst);

	// -----------------------------------------------------------------------------
	// Reference:   /interfaces/interface/port-reference/port-name
	// Description: O-RAN interfaces use a reference to a physical port component.
	//
	//              In this case, the component name referenced must be of class type
	//              port, i.e., when /hw:hardware/hw:component/hw:class is derived from
	//              ianahw:port
	// Ref:         /ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:name
	// Units:
	// -----------------------------------------------------------------------------
	RefPortName portNameInst(ITEM_PORT_NAME);
	addReference(portNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces/interface/port-reference/port-number
// Description: A number allocated by the server which identifies a port.
//              Port number value is 0 to N-1 where N is number of ports
//              in the device.
//
//              This value is fixed for the lifetime of the equipment, i.e., cannot be
//              changed during equipment reboots.
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntPortReference::LeafPortNumber::LeafPortNumber(uint32_t id)
	: YangLeaf("port-number", id)
{
}

CntInterfaces::LstInterface::CntPortReference::LeafPortNumber::~LeafPortNumber()
{
}

// -----------------------------------------------------------------------------
// Reference:   /interfaces/interface/port-reference/port-name
// Description: O-RAN interfaces use a reference to a physical port component.
//
//              In this case, the component name referenced must be of class type
//              port, i.e., when /hw:hardware/hw:component/hw:class is derived from
//              ianahw:port
// -----------------------------------------------------------------------------
CntInterfaces::LstInterface::CntPortReference::RefPortName::RefPortName(uint32_t id)
	: YangReference("port-name", id, "/ietf-hardware:hardware/ietf-hardware:component/ietf-hardware:name")
{
}

CntInterfaces::LstInterface::CntPortReference::RefPortName::~RefPortName()
{
}









// -----------------------------------------------------------------------------
// Container:   interfaces-state
// Description: Data nodes for the operational state of interfaces.
// -----------------------------------------------------------------------------
CntInterfacesState::CntInterfacesState(uint32_t id)
	: YangContainer("interfaces-state", id)
{
}

CntInterfacesState::~CntInterfacesState()
{
}

YangResult_E CntInterfacesState::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface
	// Description: The list of interfaces on the device.
	//              System-controlled interfaces created by the system are
	//              always present in this list, whether or not they are
	//              configured.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstInterface interfaceInst(ITEM_INTERFACE);
	interfaceInst.initialise();
	addList(interfaceInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        interface
// Description: The list of interfaces on the device.
//              System-controlled interfaces created by the system are
//              always present in this list, whether or not they are
//              configured.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LstInterface(uint32_t id)
	: YangList("interface", id)
{
}

CntInterfacesState::LstInterface::~LstInterface()
{
}

YangResult_E CntInterfacesState::LstInterface::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/name
	// Description: The name of the interface.
	//              A server implementation MAY map this leaf to the ifName
	//              MIB object.  Such an implementation needs to use some
	//              mechanism to handle the differences in size and characters
	//              allowed between this leaf and ifName.  The definition of
	//              such a mechanism is outside the scope of this document.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/type
	// Description: The type of the interface.
	// Type:        ???IDENT
	// Units:
	// -----------------------------------------------------------------------------
	LeafType typeInst(ITEM_TYPE);
	addLeaf(typeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/admin-status
	// Description: The desired state of the interface.
	//              This leaf has the same read semantics as ifAdminStatus.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafAdminStatus adminStatusInst(ITEM_ADMIN_STATUS);
	addLeaf(adminStatusInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/oper-status
	// Description: The current operational state of the interface.
	//              This leaf has the same semantics as ifOperStatus.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOperStatus operStatusInst(ITEM_OPER_STATUS);
	addLeaf(operStatusInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/last-change
	// Description: The time the interface entered its current operational
	//              state.  If the current state was entered prior to the
	//              last re-initialization of the local network management
	//              subsystem, then this node is not present.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLastChange lastChangeInst(ITEM_LAST_CHANGE);
	addLeaf(lastChangeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/if-index
	// Description: The ifIndex value for the ifEntry represented by this
	//              interface.
	// Type:        int32
	// Units:
	// -----------------------------------------------------------------------------
	LeafIfIndex ifIndexInst(ITEM_IF_INDEX);
	addLeaf(ifIndexInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/phys-address
	// Description: The interface's address at its protocol sub-layer.  For
	//              example, for an 802.x interface, this object normally
	//              contains a Media Access Control (MAC) address.  The
	//              interface's media-specific modules must define the bit
	//              and byte ordering and the format of the value of this
	//              object.  For interfaces that do not have such an address
	//              (e.g., a serial line), this node is not present.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafPhysAddress physAddressInst(ITEM_PHYS_ADDRESS);
	addLeaf(physAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/speed
	// Description: An estimate of the interface's current bandwidth in bits
	//              per second.  For interfaces that do not vary in
	//              bandwidth or for those where no accurate estimation can
	//              be made, this node should contain the nominal bandwidth.
	//              For interfaces that have no concept of bandwidth, this
	//              node is not present.
	// Type:        uint64
	// Units:       bits/second
	// -----------------------------------------------------------------------------
	LeafSpeed speedInst(ITEM_SPEED);
	addLeaf(speedInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/higher-layer-if
	// Description: A list of references to interfaces layered on top of this
	//              interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstHigherLayerIf higherLayerIfInst(ITEM_HIGHER_LAYER_IF);
	higherLayerIfInst.initialise();
	addList(higherLayerIfInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/lower-layer-if
	// Description: A list of references to interfaces layered underneath this
	//              interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstLowerLayerIf lowerLayerIfInst(ITEM_LOWER_LAYER_IF);
	lowerLayerIfInst.initialise();
	addList(lowerLayerIfInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces-state/interface/statistics
	// Description: A collection of interface-related statistics objects.
	// -----------------------------------------------------------------------------
	CntStatistics statisticsInst(ITEM_STATISTICS);
	statisticsInst.initialise();
	addContainer(statisticsInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces-state/interface/ipv4
	// Description: Interface-specific parameters for the IPv4 address family.
	// -----------------------------------------------------------------------------
	CntIpv4 ipv4Inst(ITEM_IPV4);
	ipv4Inst.initialise();
	addContainer(ipv4Inst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces-state/interface/ipv6
	// Description: Parameters for the IPv6 address family.
	// -----------------------------------------------------------------------------
	CntIpv6 ipv6Inst(ITEM_IPV6);
	ipv6Inst.initialise();
	addContainer(ipv6Inst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/name
// Description: The name of the interface.
//              A server implementation MAY map this leaf to the ifName
//              MIB object.  Such an implementation needs to use some
//              mechanism to handle the differences in size and characters
//              allowed between this leaf and ifName.  The definition of
//              such a mechanism is outside the scope of this document.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

CntInterfacesState::LstInterface::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/type
// Description: The type of the interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafType::LeafType(uint32_t id)
	: YangLeaf("type", id)
{
}

CntInterfacesState::LstInterface::LeafType::~LeafType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/admin-status
// Description: The desired state of the interface.
//              This leaf has the same read semantics as ifAdminStatus.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafAdminStatus::LeafAdminStatus(uint32_t id)
	: YangLeaf("admin-status", id)
{
}

CntInterfacesState::LstInterface::LeafAdminStatus::~LeafAdminStatus()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/oper-status
// Description: The current operational state of the interface.
//              This leaf has the same semantics as ifOperStatus.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafOperStatus::LeafOperStatus(uint32_t id)
	: YangLeaf("oper-status", id)
{
}

CntInterfacesState::LstInterface::LeafOperStatus::~LeafOperStatus()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/last-change
// Description: The time the interface entered its current operational
//              state.  If the current state was entered prior to the
//              last re-initialization of the local network management
//              subsystem, then this node is not present.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafLastChange::LeafLastChange(uint32_t id)
	: YangLeaf("last-change", id)
{
}

CntInterfacesState::LstInterface::LeafLastChange::~LeafLastChange()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/if-index
// Description: The ifIndex value for the ifEntry represented by this
//              interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafIfIndex::LeafIfIndex(uint32_t id)
	: YangLeaf("if-index", id)
{
}

CntInterfacesState::LstInterface::LeafIfIndex::~LeafIfIndex()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/phys-address
// Description: The interface's address at its protocol sub-layer.  For
//              example, for an 802.x interface, this object normally
//              contains a Media Access Control (MAC) address.  The
//              interface's media-specific modules must define the bit
//              and byte ordering and the format of the value of this
//              object.  For interfaces that do not have such an address
//              (e.g., a serial line), this node is not present.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafPhysAddress::LeafPhysAddress(uint32_t id)
	: YangLeaf("phys-address", id)
{
}

CntInterfacesState::LstInterface::LeafPhysAddress::~LeafPhysAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/speed
// Description: An estimate of the interface's current bandwidth in bits
//              per second.  For interfaces that do not vary in
//              bandwidth or for those where no accurate estimation can
//              be made, this node should contain the nominal bandwidth.
//              For interfaces that have no concept of bandwidth, this
//              node is not present.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LeafSpeed::LeafSpeed(uint32_t id)
	: YangLeaf("speed", id)
{
}

CntInterfacesState::LstInterface::LeafSpeed::~LeafSpeed()
{
}

// -----------------------------------------------------------------------------
// List:        higher-layer-if
// Description: A list of references to interfaces layered on top of this
//              interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LstHigherLayerIf::LstHigherLayerIf(uint32_t id)
	: YangList("higher-layer-if", id)
{
}

CntInterfacesState::LstInterface::LstHigherLayerIf::~LstHigherLayerIf()
{
}

YangResult_E CntInterfacesState::LstInterface::LstHigherLayerIf::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        lower-layer-if
// Description: A list of references to interfaces layered underneath this
//              interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::LstLowerLayerIf::LstLowerLayerIf(uint32_t id)
	: YangList("lower-layer-if", id)
{
}

CntInterfacesState::LstInterface::LstLowerLayerIf::~LstLowerLayerIf()
{
}

YangResult_E CntInterfacesState::LstInterface::LstLowerLayerIf::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Container:   statistics
// Description: A collection of interface-related statistics objects.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::CntStatistics(uint32_t id)
	: YangContainer("statistics", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::~CntStatistics()
{
}

YangResult_E CntInterfacesState::LstInterface::CntStatistics::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/discontinuity-time
	// Description: The time on the most recent occasion at which any one or
	//              more of this interface's counters suffered a
	//              discontinuity.  If no such discontinuities have occurred
	//              since the last re-initialization of the local management
	//              subsystem, then this node contains the time the local
	//              management subsystem re-initialized itself.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDiscontinuityTime discontinuityTimeInst(ITEM_DISCONTINUITY_TIME);
	addLeaf(discontinuityTimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-octets
	// Description: The total number of octets received on the interface,
	//              including framing characters.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInOctets inOctetsInst(ITEM_IN_OCTETS);
	addLeaf(inOctetsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-unicast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were not addressed to a
	//              multicast or broadcast address at this sub-layer.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInUnicastPkts inUnicastPktsInst(ITEM_IN_UNICAST_PKTS);
	addLeaf(inUnicastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-broadcast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were addressed to a broadcast
	//              address at this sub-layer.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInBroadcastPkts inBroadcastPktsInst(ITEM_IN_BROADCAST_PKTS);
	addLeaf(inBroadcastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-multicast-pkts
	// Description: The number of packets, delivered by this sub-layer to a
	//              higher (sub-)layer, that were addressed to a multicast
	//              address at this sub-layer.  For a MAC-layer protocol,
	//              this includes both Group and Functional addresses.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafInMulticastPkts inMulticastPktsInst(ITEM_IN_MULTICAST_PKTS);
	addLeaf(inMulticastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-discards
	// Description: The number of inbound packets that were chosen to be
	//              discarded even though no errors had been detected to
	//              prevent their being deliverable to a higher-layer
	//              protocol.  One possible reason for discarding such a
	//              packet could be to free up buffer space.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInDiscards inDiscardsInst(ITEM_IN_DISCARDS);
	addLeaf(inDiscardsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-errors
	// Description: For packet-oriented interfaces, the number of inbound
	//              packets that contained errors preventing them from being
	//              deliverable to a higher-layer protocol.  For character-
	//              oriented or fixed-length interfaces, the number of
	//              inbound transmission units that contained errors
	//              preventing them from being deliverable to a higher-layer
	//              protocol.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInErrors inErrorsInst(ITEM_IN_ERRORS);
	addLeaf(inErrorsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/in-unknown-protos
	// Description: For packet-oriented interfaces, the number of packets
	//              received via the interface that were discarded because
	//              of an unknown or unsupported protocol.  For
	//              character-oriented or fixed-length interfaces that
	//              support protocol multiplexing, the number of
	//              transmission units received via the interface that were
	//              discarded because of an unknown or unsupported protocol.
	//              For any interface that does not support protocol
	//              multiplexing, this counter is not present.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInUnknownProtos inUnknownProtosInst(ITEM_IN_UNKNOWN_PROTOS);
	addLeaf(inUnknownProtosInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-octets
	// Description: The total number of octets transmitted out of the
	//              interface, including framing characters.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutOctets outOctetsInst(ITEM_OUT_OCTETS);
	addLeaf(outOctetsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-unicast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were not addressed
	//              to a multicast or broadcast address at this sub-layer,
	//              including those that were discarded or not sent.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutUnicastPkts outUnicastPktsInst(ITEM_OUT_UNICAST_PKTS);
	addLeaf(outUnicastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-broadcast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were addressed to a
	//              broadcast address at this sub-layer, including those
	//              that were discarded or not sent.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutBroadcastPkts outBroadcastPktsInst(ITEM_OUT_BROADCAST_PKTS);
	addLeaf(outBroadcastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-multicast-pkts
	// Description: The total number of packets that higher-level protocols
	//              requested be transmitted and that were addressed to a
	//              multicast address at this sub-layer, including those
	//              that were discarded or not sent.  For a MAC-layer
	//              protocol, this includes both Group and Functional
	//              addresses.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint64
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutMulticastPkts outMulticastPktsInst(ITEM_OUT_MULTICAST_PKTS);
	addLeaf(outMulticastPktsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-discards
	// Description: The number of outbound packets that were chosen to be
	//              discarded even though no errors had been detected to
	//              prevent their being transmitted.  One possible reason
	//              for discarding such a packet could be to free up buffer
	//              space.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutDiscards outDiscardsInst(ITEM_OUT_DISCARDS);
	addLeaf(outDiscardsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/statistics/out-errors
	// Description: For packet-oriented interfaces, the number of outbound
	//              packets that could not be transmitted because of errors.
	//              For character-oriented or fixed-length interfaces, the
	//              number of outbound transmission units that could not be
	//              transmitted because of errors.
	//              Discontinuities in the value of this counter can occur
	//              at re-initialization of the management system and at
	//              other times as indicated by the value of
	//              'discontinuity-time'.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafOutErrors outErrorsInst(ITEM_OUT_ERRORS);
	addLeaf(outErrorsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/discontinuity-time
// Description: The time on the most recent occasion at which any one or
//              more of this interface's counters suffered a
//              discontinuity.  If no such discontinuities have occurred
//              since the last re-initialization of the local management
//              subsystem, then this node contains the time the local
//              management subsystem re-initialized itself.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafDiscontinuityTime::LeafDiscontinuityTime(uint32_t id)
	: YangLeaf("discontinuity-time", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafDiscontinuityTime::~LeafDiscontinuityTime()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-octets
// Description: The total number of octets received on the interface,
//              including framing characters.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInOctets::LeafInOctets(uint32_t id)
	: YangLeaf("in-octets", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInOctets::~LeafInOctets()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-unicast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were not addressed to a
//              multicast or broadcast address at this sub-layer.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInUnicastPkts::LeafInUnicastPkts(uint32_t id)
	: YangLeaf("in-unicast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInUnicastPkts::~LeafInUnicastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-broadcast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were addressed to a broadcast
//              address at this sub-layer.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInBroadcastPkts::LeafInBroadcastPkts(uint32_t id)
	: YangLeaf("in-broadcast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInBroadcastPkts::~LeafInBroadcastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-multicast-pkts
// Description: The number of packets, delivered by this sub-layer to a
//              higher (sub-)layer, that were addressed to a multicast
//              address at this sub-layer.  For a MAC-layer protocol,
//              this includes both Group and Functional addresses.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInMulticastPkts::LeafInMulticastPkts(uint32_t id)
	: YangLeaf("in-multicast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInMulticastPkts::~LeafInMulticastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-discards
// Description: The number of inbound packets that were chosen to be
//              discarded even though no errors had been detected to
//              prevent their being deliverable to a higher-layer
//              protocol.  One possible reason for discarding such a
//              packet could be to free up buffer space.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInDiscards::LeafInDiscards(uint32_t id)
	: YangLeaf("in-discards", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInDiscards::~LeafInDiscards()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-errors
// Description: For packet-oriented interfaces, the number of inbound
//              packets that contained errors preventing them from being
//              deliverable to a higher-layer protocol.  For character-
//              oriented or fixed-length interfaces, the number of
//              inbound transmission units that contained errors
//              preventing them from being deliverable to a higher-layer
//              protocol.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInErrors::LeafInErrors(uint32_t id)
	: YangLeaf("in-errors", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInErrors::~LeafInErrors()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/in-unknown-protos
// Description: For packet-oriented interfaces, the number of packets
//              received via the interface that were discarded because
//              of an unknown or unsupported protocol.  For
//              character-oriented or fixed-length interfaces that
//              support protocol multiplexing, the number of
//              transmission units received via the interface that were
//              discarded because of an unknown or unsupported protocol.
//              For any interface that does not support protocol
//              multiplexing, this counter is not present.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafInUnknownProtos::LeafInUnknownProtos(uint32_t id)
	: YangLeaf("in-unknown-protos", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafInUnknownProtos::~LeafInUnknownProtos()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-octets
// Description: The total number of octets transmitted out of the
//              interface, including framing characters.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutOctets::LeafOutOctets(uint32_t id)
	: YangLeaf("out-octets", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutOctets::~LeafOutOctets()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-unicast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were not addressed
//              to a multicast or broadcast address at this sub-layer,
//              including those that were discarded or not sent.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutUnicastPkts::LeafOutUnicastPkts(uint32_t id)
	: YangLeaf("out-unicast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutUnicastPkts::~LeafOutUnicastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-broadcast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were addressed to a
//              broadcast address at this sub-layer, including those
//              that were discarded or not sent.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutBroadcastPkts::LeafOutBroadcastPkts(uint32_t id)
	: YangLeaf("out-broadcast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutBroadcastPkts::~LeafOutBroadcastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-multicast-pkts
// Description: The total number of packets that higher-level protocols
//              requested be transmitted and that were addressed to a
//              multicast address at this sub-layer, including those
//              that were discarded or not sent.  For a MAC-layer
//              protocol, this includes both Group and Functional
//              addresses.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutMulticastPkts::LeafOutMulticastPkts(uint32_t id)
	: YangLeaf("out-multicast-pkts", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutMulticastPkts::~LeafOutMulticastPkts()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-discards
// Description: The number of outbound packets that were chosen to be
//              discarded even though no errors had been detected to
//              prevent their being transmitted.  One possible reason
//              for discarding such a packet could be to free up buffer
//              space.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutDiscards::LeafOutDiscards(uint32_t id)
	: YangLeaf("out-discards", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutDiscards::~LeafOutDiscards()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/statistics/out-errors
// Description: For packet-oriented interfaces, the number of outbound
//              packets that could not be transmitted because of errors.
//              For character-oriented or fixed-length interfaces, the
//              number of outbound transmission units that could not be
//              transmitted because of errors.
//              Discontinuities in the value of this counter can occur
//              at re-initialization of the management system and at
//              other times as indicated by the value of
//              'discontinuity-time'.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntStatistics::LeafOutErrors::LeafOutErrors(uint32_t id)
	: YangLeaf("out-errors", id)
{
}

CntInterfacesState::LstInterface::CntStatistics::LeafOutErrors::~LeafOutErrors()
{
}




// -----------------------------------------------------------------------------
// Container:   ipv4
// Description: Interface-specific parameters for the IPv4 address family.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::CntIpv4(uint32_t id)
	: YangContainer("ipv4", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::~CntIpv4()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/forwarding
	// Description: Indicates whether IPv4 packet forwarding is enabled or
	//              disabled on this interface.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafForwarding forwardingInst(ITEM_FORWARDING);
	addLeaf(forwardingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/mtu
	// Description: The size, in octets, of the largest IPv4 packet that the
	//              interface will send and receive.
	// Type:        uint16
	// Units:       octets
	// -----------------------------------------------------------------------------
	LeafMtu mtuInst(ITEM_MTU);
	addLeaf(mtuInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/ipv4/address
	// Description: The list of IPv4 addresses on the interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAddress addressInst(ITEM_ADDRESS);
	addressInst.initialise();
	addList(addressInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/ipv4/neighbor
	// Description: A list of mappings from IPv4 addresses to
	//              link-layer addresses.
	//              This list represents the ARP Cache.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNeighbor neighborInst(ITEM_NEIGHBOR);
	neighborInst.initialise();
	addList(neighborInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/forwarding
// Description: Indicates whether IPv4 packet forwarding is enabled or
//              disabled on this interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LeafForwarding::LeafForwarding(uint32_t id)
	: YangLeaf("forwarding", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LeafForwarding::~LeafForwarding()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/mtu
// Description: The size, in octets, of the largest IPv4 packet that the
//              interface will send and receive.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LeafMtu::LeafMtu(uint32_t id)
	: YangLeaf("mtu", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LeafMtu::~LeafMtu()
{
}

// -----------------------------------------------------------------------------
// List:        address
// Description: The list of IPv4 addresses on the interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::LstAddress(uint32_t id)
	: YangList("address", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::~LstAddress()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::LstAddress::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/address/ip
	// Description: The IPv4 address on the interface.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/address/origin
	// Description: The origin of this address.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Choice:      /interfaces-state/interface/ipv4/address/subnet
	// Description: The subnet can be specified as a prefix length or,
	//              if the server supports non-contiguous netmasks, as
	//              a netmask.
	// Type:        Subnet_E
	// Units:       -
	// -----------------------------------------------------------------------------
	ChoiceSubnet subnetInst(ITEM_SUBNET);
	subnetInst.initialise();
	addChoice(subnetInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/address/ip
// Description: The IPv4 address on the interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/address/origin
// Description: The origin of this address.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Choice:      subnet
// Description: The subnet can be specified as a prefix length or,
//              if the server supports non-contiguous netmasks, as
//              a netmask.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::ChoiceSubnet(uint32_t id)
	: YangChoice("subnet", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::~ChoiceSubnet()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::initialise(void)
{

	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptPrefixLength prefixLength(ITEM_PREFIX_LENGTH);
	prefixLength.initialise();
	addOption(prefixLength);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptNetmask netmask(ITEM_NETMASK);
	netmask.initialise();
	addOption(netmask);



	return YangResult_E::OK;
}


// -------------------------------------------------------------------------
// Option:      /interfaces-state/interface/ipv4/address/subnet[prefix-length]
// -------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::OptPrefixLength(uint32_t id)
	: YangChoiceOption("prefix-length", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::~OptPrefixLength()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/address/subnet[prefix-length]/prefix-length
	// Description: The length of the subnet prefix.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrefixLength prefixLengthInst(ITEM_PREFIX_LENGTH);
	addLeaf(prefixLengthInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/address/subnet[prefix-length]/prefix-length
// Description: The length of the subnet prefix.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::LeafPrefixLength::LeafPrefixLength(uint32_t id)
	: YangLeaf("prefix-length", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptPrefixLength::LeafPrefixLength::~LeafPrefixLength()
{
}



// -------------------------------------------------------------------------
// Option:      /interfaces-state/interface/ipv4/address/subnet[netmask]
// -------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::OptNetmask(uint32_t id)
	: YangChoiceOption("netmask", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::~OptNetmask()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/address/subnet[netmask]/netmask
	// Description: The subnet specified as a netmask.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafNetmask netmaskInst(ITEM_NETMASK);
	addLeaf(netmaskInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/address/subnet[netmask]/netmask
// Description: The subnet specified as a netmask.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::LeafNetmask::LeafNetmask(uint32_t id)
	: YangLeaf("netmask", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstAddress::ChoiceSubnet::OptNetmask::LeafNetmask::~LeafNetmask()
{
}








// -----------------------------------------------------------------------------
// List:        neighbor
// Description: A list of mappings from IPv4 addresses to
//              link-layer addresses.
//              This list represents the ARP Cache.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LstNeighbor(uint32_t id)
	: YangList("neighbor", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::~LstNeighbor()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/neighbor/ip
	// Description: The IPv4 address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/neighbor/link-layer-address
	// Description: The link-layer address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLinkLayerAddress linkLayerAddressInst(ITEM_LINK_LAYER_ADDRESS);
	addLeaf(linkLayerAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv4/neighbor/origin
	// Description: The origin of this neighbor entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/neighbor/ip
// Description: The IPv4 address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/neighbor/link-layer-address
// Description: The link-layer address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafLinkLayerAddress::LeafLinkLayerAddress(uint32_t id)
	: YangLeaf("link-layer-address", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafLinkLayerAddress::~LeafLinkLayerAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv4/neighbor/origin
// Description: The origin of this neighbor entry.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfacesState::LstInterface::CntIpv4::LstNeighbor::LeafOrigin::~LeafOrigin()
{
}






// -----------------------------------------------------------------------------
// Container:   ipv6
// Description: Parameters for the IPv6 address family.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::CntIpv6(uint32_t id)
	: YangContainer("ipv6", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::~CntIpv6()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv6::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/forwarding
	// Description: Indicates whether IPv6 packet forwarding is enabled or
	//              disabled on this interface.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafForwarding forwardingInst(ITEM_FORWARDING);
	addLeaf(forwardingInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/mtu
	// Description: The size, in octets, of the largest IPv6 packet that the
	//              interface will send and receive.
	// Type:        uint32
	// Units:       octets
	// -----------------------------------------------------------------------------
	LeafMtu mtuInst(ITEM_MTU);
	addLeaf(mtuInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/ipv6/address
	// Description: The list of IPv6 addresses on the interface.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstAddress addressInst(ITEM_ADDRESS);
	addressInst.initialise();
	addList(addressInst);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface/ipv6/neighbor
	// Description: A list of mappings from IPv6 addresses to
	//              link-layer addresses.
	//              This list represents the Neighbor Cache.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNeighbor neighborInst(ITEM_NEIGHBOR);
	neighborInst.initialise();
	addList(neighborInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/forwarding
// Description: Indicates whether IPv6 packet forwarding is enabled or
//              disabled on this interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LeafForwarding::LeafForwarding(uint32_t id)
	: YangLeaf("forwarding", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LeafForwarding::~LeafForwarding()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/mtu
// Description: The size, in octets, of the largest IPv6 packet that the
//              interface will send and receive.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LeafMtu::LeafMtu(uint32_t id)
	: YangLeaf("mtu", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LeafMtu::~LeafMtu()
{
}

// -----------------------------------------------------------------------------
// List:        address
// Description: The list of IPv6 addresses on the interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstAddress::LstAddress(uint32_t id)
	: YangList("address", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstAddress::~LstAddress()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv6::LstAddress::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/address/ip
	// Description: The IPv6 address on the interface.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/address/prefix-length
	// Description: The length of the subnet prefix.
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrefixLength prefixLengthInst(ITEM_PREFIX_LENGTH);
	addLeaf(prefixLengthInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/address/origin
	// Description: The origin of this address.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/address/status
	// Description: The status of an address.  Most of the states correspond
	//              to states from the IPv6 Stateless Address
	//              Autoconfiguration protocol.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafStatus statusInst(ITEM_STATUS);
	addLeaf(statusInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/address/ip
// Description: The IPv6 address on the interface.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/address/prefix-length
// Description: The length of the subnet prefix.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafPrefixLength::LeafPrefixLength(uint32_t id)
	: YangLeaf("prefix-length", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafPrefixLength::~LeafPrefixLength()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/address/origin
// Description: The origin of this address.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/address/status
// Description: The status of an address.  Most of the states correspond
//              to states from the IPv6 Stateless Address
//              Autoconfiguration protocol.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafStatus::LeafStatus(uint32_t id)
	: YangLeaf("status", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstAddress::LeafStatus::~LeafStatus()
{
}



// -----------------------------------------------------------------------------
// List:        neighbor
// Description: A list of mappings from IPv6 addresses to
//              link-layer addresses.
//              This list represents the Neighbor Cache.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LstNeighbor(uint32_t id)
	: YangList("neighbor", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::~LstNeighbor()
{
}

YangResult_E CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/neighbor/ip
	// Description: The IPv6 address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIp ipInst(ITEM_IP);
	addLeaf(ipInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/neighbor/link-layer-address
	// Description: The link-layer address of the neighbor node.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafLinkLayerAddress linkLayerAddressInst(ITEM_LINK_LAYER_ADDRESS);
	addLeaf(linkLayerAddressInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/neighbor/origin
	// Description: The origin of this neighbor entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafOrigin originInst(ITEM_ORIGIN);
	addLeaf(originInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/neighbor/is-router
	// Description: Indicates that the neighbor node acts as a router.
	// Type:        UNKNOWN:5
	// Units:
	// -----------------------------------------------------------------------------
	LeafIsRouter isRouterInst(ITEM_IS_ROUTER);
	addLeaf(isRouterInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /interfaces-state/interface/ipv6/neighbor/state
	// Description: The Neighbor Unreachability Detection state of this
	//              entry.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafState stateInst(ITEM_STATE);
	addLeaf(stateInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/neighbor/ip
// Description: The IPv6 address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafIp::LeafIp(uint32_t id)
	: YangLeaf("ip", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafIp::~LeafIp()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/neighbor/link-layer-address
// Description: The link-layer address of the neighbor node.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafLinkLayerAddress::LeafLinkLayerAddress(uint32_t id)
	: YangLeaf("link-layer-address", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafLinkLayerAddress::~LeafLinkLayerAddress()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/neighbor/origin
// Description: The origin of this neighbor entry.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafOrigin::LeafOrigin(uint32_t id)
	: YangLeaf("origin", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafOrigin::~LeafOrigin()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/neighbor/is-router
// Description: Indicates that the neighbor node acts as a router.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafIsRouter::LeafIsRouter(uint32_t id)
	: YangLeaf("is-router", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafIsRouter::~LeafIsRouter()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /interfaces-state/interface/ipv6/neighbor/state
// Description: The Neighbor Unreachability Detection state of this
//              entry.
// -----------------------------------------------------------------------------
CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafState::LeafState(uint32_t id)
	: YangLeaf("state", id)
{
}

CntInterfacesState::LstInterface::CntIpv6::LstNeighbor::LeafState::~LeafState()
{
}












// *****************************************************************************
// Groupings
// *****************************************************************************


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
// Module:      ietf-interfaces
// Description: This module contains a collection of YANG definitions for
//              managing network interfaces.
//              Copyright (c) 2018 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 8343; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIetfInterfaces::ModuleIetfInterfaces(uint32_t id)
	: YangModule ("ietf-interfaces",
	              "ietf-interfaces.yang",
	              "if",
	              "urn:ietf:params:xml:ns:yang:ietf-interfaces",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Feature
	// Description: This feature indicates that the device allows user-controlled
	//              interfaces to be named arbitrarily.
	// -----------------------------------------------------------------------------
	FeatureArbitraryNames arbitraryNamesInst(ITEM_ARBITRARY_NAMES);
	addFeature(arbitraryNamesInst);

	// -----------------------------------------------------------------------------
	// Feature
	// Description: This feature indicates that the device supports
	//              pre-provisioning of interface configuration, i.e., it is
	//              possible to configure an interface whose physical interface
	//              hardware is not present on the device.
	// -----------------------------------------------------------------------------
	FeaturePreProvisioning preProvisioningInst(ITEM_PRE_PROVISIONING);
	addFeature(preProvisioningInst);

	// -----------------------------------------------------------------------------
	// Feature
	// Description: This feature indicates that the device implements
	//              the IF-MIB.
	// -----------------------------------------------------------------------------
	FeatureIfMib ifMibInst(ITEM_IF_MIB);
	addFeature(ifMibInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces
	// Description: Interface parameters.
	// -----------------------------------------------------------------------------
	CntInterfaces interfacesInst(ITEM_INTERFACES);
	interfacesInst.initialise();
	addContainer(interfacesInst);

	// -----------------------------------------------------------------------------
	// Container:   /interfaces-state
	// Description: Data nodes for the operational state of interfaces.
	// -----------------------------------------------------------------------------
	CntInterfacesState interfacesStateInst(ITEM_INTERFACES_STATE);
	interfacesStateInst.initialise();
	addContainer(interfacesStateInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfInterfaces::~ModuleIetfInterfaces()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfInterfaces::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfInterfaces>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfInterfaces::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
