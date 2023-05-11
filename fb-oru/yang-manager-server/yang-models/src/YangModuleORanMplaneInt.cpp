/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanMplaneInt.cpp
 * \brief     Module ORanMplaneInt interface
 *
 *
 * \details   This file defines the YANG module o-ran-mplane-int interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-mplane-int"
 *            YANG Filename:    "o-ran-mplane-int.yang"
 *            Module Prefix:    "o-ran-mplane-int"
 *            Module namespace: "urn:o-ran:mplane-interfaces:1.0"
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
#include "YangModuleORanMplaneInt.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanMplaneInt_NS;

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
// Container:   mplane-info
// Description: top level container for management plane information
// -----------------------------------------------------------------------------
CntMplaneInfo::CntMplaneInfo(uint32_t id)
	: YangContainer("mplane-info", id)
{
}

CntMplaneInfo::~CntMplaneInfo()
{
}

YangResult_E CntMplaneInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /mplane-info/mplane-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpMplaneGroup mplaneGroupInst(ITEM_MPLANE_GROUP);
	mplaneGroupInst.initialise();
	addGroup(mplaneGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    mplane-group
// Description:
// -----------------------------------------------------------------------------
GrpMplaneGroup::GrpMplaneGroup(uint32_t id)
	: YangGroup("mplane-group", id)
{
}

GrpMplaneGroup::~GrpMplaneGroup()
{
}

YangResult_E GrpMplaneGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/searchable-mplane-access-vlans-info
	// Description: These parameters shall be stored by the equipment in reset persistant memory
	//              to enable it to be re-used to optimize VALN discovery procerdures.
	// -----------------------------------------------------------------------------
	CntSearchableMplaneAccessVlansInfo searchableMplaneAccessVlansInfoInst(ITEM_SEARCHABLE_MPLANE_ACCESS_VLANS_INFO);
	searchableMplaneAccessVlansInfoInst.initialise();
	addContainer(searchableMplaneAccessVlansInfoInst);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/m-plane-interfaces
	// Description: information concerning m-plane interfaces
	// -----------------------------------------------------------------------------
	CntMPlaneInterfaces mPlaneInterfacesInst(ITEM_M_PLANE_INTERFACES);
	mPlaneInterfacesInst.initialise();
	addContainer(mPlaneInterfacesInst);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/configured-client-info
	// Description: the NETCONF client information that may be configured by another
	//              NETCONF client. These clients are reported independently from clients
	//              manually configured or discovered using DHCP.
	// -----------------------------------------------------------------------------
	CntConfiguredClientInfo configuredClientInfoInst(ITEM_CONFIGURED_CLIENT_INFO);
	configuredClientInfoInst.initialise();
	addContainer(configuredClientInfoInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   searchable-mplane-access-vlans-info
// Description: These parameters shall be stored by the equipment in reset persistant memory
//              to enable it to be re-used to optimize VALN discovery procerdures.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntSearchableMplaneAccessVlansInfo(uint32_t id)
	: YangContainer("searchable-mplane-access-vlans-info", id)
{
}

GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::~CntSearchableMplaneAccessVlansInfo()
{
}

YangResult_E GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /mplane-group/searchable-mplane-access-vlans-info/searchable-access-vlans
	// Description: A list of access VLANs that may be operational on the transport
	//              network. Can be used by the equipment to optimize its VLAN searching - for
	//              M-plane operations.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSearchableAccessVlans searchableAccessVlansInst(ITEM_SEARCHABLE_ACCESS_VLANS);
	searchableAccessVlansInst.initialise();
	addList(searchableAccessVlansInst);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/searchable-mplane-access-vlans-info/vlan-range
	// Description: the range of VLAN IDs that may be configured for M-Plane
	// -----------------------------------------------------------------------------
	CntVlanRange vlanRangeInst(ITEM_VLAN_RANGE);
	vlanRangeInst.initialise();
	addContainer(vlanRangeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        searchable-access-vlans
// Description: A list of access VLANs that may be operational on the transport
//              network. Can be used by the equipment to optimize its VLAN searching - for
//              M-plane operations.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::LstSearchableAccessVlans::LstSearchableAccessVlans(uint32_t id)
	: YangList("searchable-access-vlans", id)
{
}

GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::LstSearchableAccessVlans::~LstSearchableAccessVlans()
{
}

YangResult_E GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::LstSearchableAccessVlans::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Container:   vlan-range
// Description: the range of VLAN IDs that may be configured for M-Plane
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::CntVlanRange(uint32_t id)
	: YangContainer("vlan-range", id)
{
}

GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::~CntVlanRange()
{
}

YangResult_E GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/lowest-vlan-id
	// Description: Value of this parameter informs equipment about lowest VID to be used
	//              in VLAN scan procedure
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafLowestVlanId lowestVlanIdInst(ITEM_LOWEST_VLAN_ID);
	addLeaf(lowestVlanIdInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/highest-vlan-id
	// Description: Value of this parameter informs about highest VID to be used
	//              in VLAN scan procedure
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafHighestVlanId highestVlanIdInst(ITEM_HIGHEST_VLAN_ID);
	addLeaf(highestVlanIdInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/lowest-vlan-id
// Description: Value of this parameter informs equipment about lowest VID to be used
//              in VLAN scan procedure
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::LeafLowestVlanId::LeafLowestVlanId(uint32_t id)
	: YangLeaf("lowest-vlan-id", id)
{
}

GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::LeafLowestVlanId::~LeafLowestVlanId()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/highest-vlan-id
// Description: Value of this parameter informs about highest VID to be used
//              in VLAN scan procedure
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::LeafHighestVlanId::LeafHighestVlanId(uint32_t id)
	: YangLeaf("highest-vlan-id", id)
{
}

GrpMplaneGroup::CntSearchableMplaneAccessVlansInfo::CntVlanRange::LeafHighestVlanId::~LeafHighestVlanId()
{
}







// -----------------------------------------------------------------------------
// Container:   m-plane-interfaces
// Description: information concerning m-plane interfaces
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneInterfaces(uint32_t id)
	: YangContainer("m-plane-interfaces", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::~CntMPlaneInterfaces()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces
	// Description: list of m-plane information
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMPlaneSubInterfaces mPlaneSubInterfacesInst(ITEM_M_PLANE_SUB_INTERFACES);
	mPlaneSubInterfacesInst.initialise();
	addList(mPlaneSubInterfacesInst);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/m-plane-interfaces/m-plane-ssh-ports
	// Description: leafs for managing SSH ports
	// -----------------------------------------------------------------------------
	CntMPlaneSshPorts mPlaneSshPortsInst(ITEM_M_PLANE_SSH_PORTS);
	mPlaneSshPortsInst.initialise();
	addContainer(mPlaneSshPortsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        m-plane-sub-interfaces
// Description: list of m-plane information
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::LstMPlaneSubInterfaces(uint32_t id)
	: YangList("m-plane-sub-interfaces", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::~LstMPlaneSubInterfaces()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/interface-name
	// Description: the name of the interface
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
	// Units:
	// -----------------------------------------------------------------------------
	RefInterfaceName interfaceNameInst(ITEM_INTERFACE_NAME);
	addReference(interfaceNameInst);

	// -----------------------------------------------------------------------------
	// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/sub-interface
	// Description: vlans used to communicate with management plane servers.
	// Ref:         /ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:vlan-id
	// Units:
	// -----------------------------------------------------------------------------
	RefSubInterface subInterfaceInst(ITEM_SUB_INTERFACE);
	addReference(subInterfaceInst);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info
	// Description: the NETCONF client information, discovered by DHCP or manually
	//              configured during installation.
	// -----------------------------------------------------------------------------
	CntClientInfo clientInfoInst(ITEM_CLIENT_INFO);
	clientInfoInst.initialise();
	addContainer(clientInfoInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/interface-name
// Description: the name of the interface
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::RefInterfaceName::RefInterfaceName(uint32_t id)
	: YangReference("interface-name", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name")
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::RefInterfaceName::~RefInterfaceName()
{
}

// -----------------------------------------------------------------------------
// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/sub-interface
// Description: vlans used to communicate with management plane servers.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::RefSubInterface::RefSubInterface(uint32_t id)
	: YangReference("sub-interface", id, "/ietf-interfaces:interfaces/ietf-interfaces:interface[ietf-interfaces:name = current()/../interface-name]/o-ran-interfaces:vlan-id")
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::RefSubInterface::~RefSubInterface()
{
}

// -----------------------------------------------------------------------------
// Container:   client-info
// Description: the NETCONF client information, discovered by DHCP or manually
//              configured during installation.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::CntClientInfo(uint32_t id)
	: YangContainer("client-info", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::~CntClientInfo()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-fqdn
	// Description: The discovered FQDN(s) of M-Plane client(s).
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneFqdn mplaneFqdnInst(ITEM_MPLANE_FQDN);
	mplaneFqdnInst.initialise();
	addList(mplaneFqdnInst);

	// -----------------------------------------------------------------------------
	// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info
	// Description: list of IPv4 NETCONF clients
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneIpv4Info mplaneIpv4InfoInst(ITEM_MPLANE_IPV4_INFO);
	mplaneIpv4InfoInst.initialise();
	addList(mplaneIpv4InfoInst);

	// -----------------------------------------------------------------------------
	// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info
	// Description: list of IPv6 NETCONF clients
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneIpv6Info mplaneIpv6InfoInst(ITEM_MPLANE_IPV6_INFO);
	mplaneIpv6InfoInst.initialise();
	addList(mplaneIpv6InfoInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        mplane-fqdn
// Description: The discovered FQDN(s) of M-Plane client(s).
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneFqdn::LstMplaneFqdn(uint32_t id)
	: YangList("mplane-fqdn", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneFqdn::~LstMplaneFqdn()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneFqdn::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        mplane-ipv4-info
// Description: list of IPv4 NETCONF clients
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::LstMplaneIpv4Info(uint32_t id)
	: YangList("mplane-ipv4-info", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::~LstMplaneIpv4Info()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/mplane-ipv4
	// Description: The IPv4 address of M-Plane client discovered by the O-RU
	//              or manually configured.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafMplaneIpv4 mplaneIpv4Inst(ITEM_MPLANE_IPV4);
	addLeaf(mplaneIpv4Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/port
	// Description: The call home port number discovered or manually configured.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPort portInst(ITEM_PORT);
	addLeaf(portInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/mplane-ipv4
// Description: The IPv4 address of M-Plane client discovered by the O-RU
//              or manually configured.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::LeafMplaneIpv4::LeafMplaneIpv4(uint32_t id)
	: YangLeaf("mplane-ipv4", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::LeafMplaneIpv4::~LeafMplaneIpv4()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/port
// Description: The call home port number discovered or manually configured.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::LeafPort::LeafPort(uint32_t id)
	: YangLeaf("port", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv4Info::LeafPort::~LeafPort()
{
}



// -----------------------------------------------------------------------------
// List:        mplane-ipv6-info
// Description: list of IPv6 NETCONF clients
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::LstMplaneIpv6Info(uint32_t id)
	: YangList("mplane-ipv6-info", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::~LstMplaneIpv6Info()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/mplane-ipv6
	// Description: The IPv6 address of M-Plane client discovered by the O-RU
	//              or manually configured.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafMplaneIpv6 mplaneIpv6Inst(ITEM_MPLANE_IPV6);
	addLeaf(mplaneIpv6Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/port
	// Description: The call home port number discovered or manually configured.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPort portInst(ITEM_PORT);
	addLeaf(portInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/mplane-ipv6
// Description: The IPv6 address of M-Plane client discovered by the O-RU
//              or manually configured.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::LeafMplaneIpv6::LeafMplaneIpv6(uint32_t id)
	: YangLeaf("mplane-ipv6", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::LeafMplaneIpv6::~LeafMplaneIpv6()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/port
// Description: The call home port number discovered or manually configured.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::LeafPort::LeafPort(uint32_t id)
	: YangLeaf("port", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::LstMPlaneSubInterfaces::CntClientInfo::LstMplaneIpv6Info::LeafPort::~LeafPort()
{
}








// -----------------------------------------------------------------------------
// Container:   m-plane-ssh-ports
// Description: leafs for managing SSH ports
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::CntMPlaneSshPorts(uint32_t id)
	: YangContainer("m-plane-ssh-ports", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::~CntMPlaneSshPorts()
{
}

YangResult_E GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/call-home-ssh-port
	// Description: The configured call home server port number
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafCallHomeSshPort callHomeSshPortInst(ITEM_CALL_HOME_SSH_PORT);
	addLeaf(callHomeSshPortInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/server-ssh-port
	// Description: The configured SSH server port number
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafServerSshPort serverSshPortInst(ITEM_SERVER_SSH_PORT);
	addLeaf(serverSshPortInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/call-home-ssh-port
// Description: The configured call home server port number
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::LeafCallHomeSshPort::LeafCallHomeSshPort(uint32_t id)
	: YangLeaf("call-home-ssh-port", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::LeafCallHomeSshPort::~LeafCallHomeSshPort()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/server-ssh-port
// Description: The configured SSH server port number
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::LeafServerSshPort::LeafServerSshPort(uint32_t id)
	: YangLeaf("server-ssh-port", id)
{
}

GrpMplaneGroup::CntMPlaneInterfaces::CntMPlaneSshPorts::LeafServerSshPort::~LeafServerSshPort()
{
}







// -----------------------------------------------------------------------------
// Container:   configured-client-info
// Description: the NETCONF client information that may be configured by another
//              NETCONF client. These clients are reported independently from clients
//              manually configured or discovered using DHCP.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::CntConfiguredClientInfo(uint32_t id)
	: YangContainer("configured-client-info", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::~CntConfiguredClientInfo()
{
}

YangResult_E GrpMplaneGroup::CntConfiguredClientInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /mplane-group/configured-client-info/mplane-fqdn
	// Description: The configured FQDN(s) of M-Plane client(s).
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneFqdn mplaneFqdnInst(ITEM_MPLANE_FQDN);
	mplaneFqdnInst.initialise();
	addList(mplaneFqdnInst);

	// -----------------------------------------------------------------------------
	// List:        /mplane-group/configured-client-info/mplane-ipv4-info
	// Description: list of IPv4 NETCONF clients
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneIpv4Info mplaneIpv4InfoInst(ITEM_MPLANE_IPV4_INFO);
	mplaneIpv4InfoInst.initialise();
	addList(mplaneIpv4InfoInst);

	// -----------------------------------------------------------------------------
	// List:        /mplane-group/configured-client-info/mplane-ipv6-info
	// Description: list of IPv6 NETCONF clients
	// Array Key:
	// -----------------------------------------------------------------------------
	LstMplaneIpv6Info mplaneIpv6InfoInst(ITEM_MPLANE_IPV6_INFO);
	mplaneIpv6InfoInst.initialise();
	addList(mplaneIpv6InfoInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        mplane-fqdn
// Description: The configured FQDN(s) of M-Plane client(s).
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneFqdn::LstMplaneFqdn(uint32_t id)
	: YangList("mplane-fqdn", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneFqdn::~LstMplaneFqdn()
{
}

YangResult_E GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneFqdn::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        mplane-ipv4-info
// Description: list of IPv4 NETCONF clients
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::LstMplaneIpv4Info(uint32_t id)
	: YangList("mplane-ipv4-info", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::~LstMplaneIpv4Info()
{
}

YangResult_E GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/mplane-ipv4
	// Description: The IPv4 address of configured M-Plane client.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafMplaneIpv4 mplaneIpv4Inst(ITEM_MPLANE_IPV4);
	addLeaf(mplaneIpv4Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/port
	// Description: The configured call home port number.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPort portInst(ITEM_PORT);
	addLeaf(portInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/mplane-ipv4
// Description: The IPv4 address of configured M-Plane client.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::LeafMplaneIpv4::LeafMplaneIpv4(uint32_t id)
	: YangLeaf("mplane-ipv4", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::LeafMplaneIpv4::~LeafMplaneIpv4()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/port
// Description: The configured call home port number.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::LeafPort::LeafPort(uint32_t id)
	: YangLeaf("port", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv4Info::LeafPort::~LeafPort()
{
}



// -----------------------------------------------------------------------------
// List:        mplane-ipv6-info
// Description: list of IPv6 NETCONF clients
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::LstMplaneIpv6Info(uint32_t id)
	: YangList("mplane-ipv6-info", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::~LstMplaneIpv6Info()
{
}

YangResult_E GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/mplane-ipv6
	// Description: The IPv6 address of configured M-Plane client..
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafMplaneIpv6 mplaneIpv6Inst(ITEM_MPLANE_IPV6);
	addLeaf(mplaneIpv6Inst);

	// -----------------------------------------------------------------------------
	// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/port
	// Description: The configured call home port number.
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPort portInst(ITEM_PORT);
	addLeaf(portInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/mplane-ipv6
// Description: The IPv6 address of configured M-Plane client..
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::LeafMplaneIpv6::LeafMplaneIpv6(uint32_t id)
	: YangLeaf("mplane-ipv6", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::LeafMplaneIpv6::~LeafMplaneIpv6()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/port
// Description: The configured call home port number.
// -----------------------------------------------------------------------------
GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::LeafPort::LeafPort(uint32_t id)
	: YangLeaf("port", id)
{
}

GrpMplaneGroup::CntConfiguredClientInfo::LstMplaneIpv6Info::LeafPort::~LeafPort()
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
// Module:      o-ran-mplane-int
// Description: This module defines the YANG definitions for managng the O-RAN Radio Unit
//              management plane interface.
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
ModuleORanMplaneInt::ModuleORanMplaneInt(uint32_t id)
	: YangModule ("o-ran-mplane-int",
	              "o-ran-mplane-int.yang",
	              "o-ran-mplane-int",
	              "urn:o-ran:mplane-interfaces:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /mplane-info
	// Description: top level container for management plane information
	// -----------------------------------------------------------------------------
	CntMplaneInfo mplaneInfoInst(ITEM_MPLANE_INFO);
	mplaneInfoInst.initialise();
	addContainer(mplaneInfoInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanMplaneInt::~ModuleORanMplaneInt()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanMplaneInt::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanMplaneInt>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanMplaneInt::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
