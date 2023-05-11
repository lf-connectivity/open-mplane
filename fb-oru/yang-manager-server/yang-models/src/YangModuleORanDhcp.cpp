/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanDhcp.cpp
 * \brief     Module ORanDhcp interface
 *
 *
 * \details   This file defines the YANG module o-ran-dhcp interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-dhcp"
 *            YANG Filename:    "o-ran-dhcp.yang"
 *            Module Prefix:    "o-ran-dhcp"
 *            Module namespace: "urn:o-ran:dhcp:1.0"
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
#include "YangModuleORanDhcp.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanDhcp_NS;

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
// Container:   dhcp
// Description: DHCP client configuration
// -----------------------------------------------------------------------------
CntDhcp::CntDhcp(uint32_t id)
	: YangContainer("dhcp", id)
{
}

CntDhcp::~CntDhcp()
{
}

YangResult_E CntDhcp::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /dhcp/dhcp-group
	// Description:
	// -----------------------------------------------------------------------------
	GrpDhcpGroup dhcpGroupInst(ITEM_DHCP_GROUP);
	dhcpGroupInst.initialise();
	addGroup(dhcpGroupInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    ca-ra-servers
// Description: The CA/RA servers discovered using DHCP, discovered using the 3GPP
//              defined options in 3GPP 32.509 in vendor specific option 43/17
// -----------------------------------------------------------------------------
GrpCaRaServers::GrpCaRaServers(uint32_t id)
	: YangGroup("ca-ra-servers", id)
{
}

GrpCaRaServers::~GrpCaRaServers()
{
}

YangResult_E GrpCaRaServers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /ca-ra-servers/ca-ra-servers
	// Description: A list of IP addresses or URIs for CA/RA Servers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstCaRaServers caRaServersInst(ITEM_CA_RA_SERVERS);
	caRaServersInst.initialise();
	addList(caRaServersInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        ca-ra-servers
// Description: A list of IP addresses or URIs for CA/RA Servers
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LstCaRaServers(uint32_t id)
	: YangList("ca-ra-servers", id)
{
}

GrpCaRaServers::LstCaRaServers::~LstCaRaServers()
{
}

YangResult_E GrpCaRaServers::LstCaRaServers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /ca-ra-servers/ca-ra-servers/servers
	// Description: the server identifier
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafServers serversInst(ITEM_SERVERS);
	addLeaf(serversInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /ca-ra-servers/ca-ra-servers/port-number
	// Description: an optional (non-default) port
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPortNumber portNumberInst(ITEM_PORT_NUMBER);
	addLeaf(portNumberInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /ca-ra-servers/ca-ra-servers/ca-ra-path
	// Description: ASCII string representing the path to the CMP server directory.
	//              A CMP server may be located in an arbitrary path other than root.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafCaRaPath caRaPathInst(ITEM_CA_RA_PATH);
	addLeaf(caRaPathInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /ca-ra-servers/ca-ra-servers/subject-name
	// Description: ASCII string representing the subject name of the CA/RA.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafSubjectName subjectNameInst(ITEM_SUBJECT_NAME);
	addLeaf(subjectNameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /ca-ra-servers/ca-ra-servers/protocol
	// Description:
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafProtocol protocolInst(ITEM_PROTOCOL);
	addLeaf(protocolInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /ca-ra-servers/ca-ra-servers/servers
// Description: the server identifier
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LeafServers::LeafServers(uint32_t id)
	: YangLeaf("servers", id)
{
}

GrpCaRaServers::LstCaRaServers::LeafServers::~LeafServers()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /ca-ra-servers/ca-ra-servers/port-number
// Description: an optional (non-default) port
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LeafPortNumber::LeafPortNumber(uint32_t id)
	: YangLeaf("port-number", id)
{
}

GrpCaRaServers::LstCaRaServers::LeafPortNumber::~LeafPortNumber()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /ca-ra-servers/ca-ra-servers/ca-ra-path
// Description: ASCII string representing the path to the CMP server directory.
//              A CMP server may be located in an arbitrary path other than root.
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LeafCaRaPath::LeafCaRaPath(uint32_t id)
	: YangLeaf("ca-ra-path", id)
{
}

GrpCaRaServers::LstCaRaServers::LeafCaRaPath::~LeafCaRaPath()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /ca-ra-servers/ca-ra-servers/subject-name
// Description: ASCII string representing the subject name of the CA/RA.
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LeafSubjectName::LeafSubjectName(uint32_t id)
	: YangLeaf("subject-name", id)
{
}

GrpCaRaServers::LstCaRaServers::LeafSubjectName::~LeafSubjectName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /ca-ra-servers/ca-ra-servers/protocol
// Description:
// -----------------------------------------------------------------------------
GrpCaRaServers::LstCaRaServers::LeafProtocol::LeafProtocol(uint32_t id)
	: YangLeaf("protocol", id)
{
}

GrpCaRaServers::LstCaRaServers::LeafProtocol::~LeafProtocol()
{
}





// -----------------------------------------------------------------------------
// Grouping:    security-gateways
// Description: The security gateways discovered using DHCP, discovered using the 3GPP
//              defined options in 3GPP 32.509 in vendor specific option 43/17
// -----------------------------------------------------------------------------
GrpSecurityGateways::GrpSecurityGateways(uint32_t id)
	: YangGroup("security-gateways", id)
{
}

GrpSecurityGateways::~GrpSecurityGateways()
{
}

YangResult_E GrpSecurityGateways::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /security-gateways/segw
	// Description: A list of IP addresses or URIs for SeGW
	// Array Key:
	// -----------------------------------------------------------------------------
	LstSegw segwInst(ITEM_SEGW);
	segwInst.initialise();
	addList(segwInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        segw
// Description: A list of IP addresses or URIs for SeGW
// -----------------------------------------------------------------------------
GrpSecurityGateways::LstSegw::LstSegw(uint32_t id)
	: YangList("segw", id)
{
}

GrpSecurityGateways::LstSegw::~LstSegw()
{
}

YangResult_E GrpSecurityGateways::LstSegw::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /security-gateways/segw/gateways
	// Description: the SeGW identifier
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafGateways gatewaysInst(ITEM_GATEWAYS);
	addLeaf(gatewaysInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /security-gateways/segw/gateways
// Description: the SeGW identifier
// -----------------------------------------------------------------------------
GrpSecurityGateways::LstSegw::LeafGateways::LeafGateways(uint32_t id)
	: YangLeaf("gateways", id)
{
}

GrpSecurityGateways::LstSegw::LeafGateways::~LeafGateways()
{
}





// -----------------------------------------------------------------------------
// Grouping:    netconf-clients
// Description: The netconf clients discovered using DHCP, discovered using the IANA
//              defined options or O-RAN defined syntax for encoding IP adresses or FQDNs
//              in vendor specific option 43/17
// -----------------------------------------------------------------------------
GrpNetconfClients::GrpNetconfClients(uint32_t id)
	: YangGroup("netconf-clients", id)
{
}

GrpNetconfClients::~GrpNetconfClients()
{
}

YangResult_E GrpNetconfClients::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /netconf-clients/netconf-clients
	// Description: A list of IP addresses or URIs for NETCONF clients
	// Array Key:
	// -----------------------------------------------------------------------------
	LstNetconfClients netconfClientsInst(ITEM_NETCONF_CLIENTS);
	netconfClientsInst.initialise();
	addList(netconfClientsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        netconf-clients
// Description: A list of IP addresses or URIs for NETCONF clients
// -----------------------------------------------------------------------------
GrpNetconfClients::LstNetconfClients::LstNetconfClients(uint32_t id)
	: YangList("netconf-clients", id)
{
}

GrpNetconfClients::LstNetconfClients::~LstNetconfClients()
{
}

YangResult_E GrpNetconfClients::LstNetconfClients::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /netconf-clients/netconf-clients/client
	// Description: the client identifier
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafClient clientInst(ITEM_CLIENT);
	addLeaf(clientInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /netconf-clients/netconf-clients/optional-port
	// Description: an optional (non-default) port
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafOptionalPort optionalPortInst(ITEM_OPTIONAL_PORT);
	addLeaf(optionalPortInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-clients/netconf-clients/client
// Description: the client identifier
// -----------------------------------------------------------------------------
GrpNetconfClients::LstNetconfClients::LeafClient::LeafClient(uint32_t id)
	: YangLeaf("client", id)
{
}

GrpNetconfClients::LstNetconfClients::LeafClient::~LeafClient()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-clients/netconf-clients/optional-port
// Description: an optional (non-default) port
// -----------------------------------------------------------------------------
GrpNetconfClients::LstNetconfClients::LeafOptionalPort::LeafOptionalPort(uint32_t id)
	: YangLeaf("optional-port", id)
{
}

GrpNetconfClients::LstNetconfClients::LeafOptionalPort::~LeafOptionalPort()
{
}





// -----------------------------------------------------------------------------
// Grouping:    dhcpv4-option
// Description: DHCPv4 Configuration options
// -----------------------------------------------------------------------------
GrpDhcpv4Option::GrpDhcpv4Option(uint32_t id)
	: YangGroup("dhcpv4-option", id)
{
}

GrpDhcpv4Option::~GrpDhcpv4Option()
{
}

YangResult_E GrpDhcpv4Option::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/dhcp-server-identifier
	// Description: DHCP server identifier
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafDhcpServerIdentifier dhcpServerIdentifierInst(ITEM_DHCP_SERVER_IDENTIFIER);
	addLeaf(dhcpServerIdentifierInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/domain-name
	// Description: Name of the domain
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDomainName domainNameInst(ITEM_DOMAIN_NAME);
	addLeaf(domainNameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/interface-mtu
	// Description: Minimum Transmission Unit (MTU) of the interface
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafInterfaceMtu interfaceMtuInst(ITEM_INTERFACE_MTU);
	addLeaf(interfaceMtuInst);

	// -----------------------------------------------------------------------------
	// List:        /dhcpv4-option/domain-name-servers
	// Description: A list of DNS servers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstDomainNameServers domainNameServersInst(ITEM_DOMAIN_NAME_SERVERS);
	domainNameServersInst.initialise();
	addList(domainNameServersInst);

	// -----------------------------------------------------------------------------
	// List:        /dhcpv4-option/default-gateways
	// Description: the list of default gateways on the O-RUs subnet
	// Array Key:
	// -----------------------------------------------------------------------------
	LstDefaultGateways defaultGatewaysInst(ITEM_DEFAULT_GATEWAYS);
	defaultGatewaysInst.initialise();
	addList(defaultGatewaysInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv4-option/netconf-clients
	// Description:
	// -----------------------------------------------------------------------------
	GrpNetconfClients netconfClientsInst(ITEM_NETCONF_CLIENTS);
	netconfClientsInst.initialise();
	addGroup(netconfClientsInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv4-option/ca-ra-servers
	// Description:
	// -----------------------------------------------------------------------------
	GrpCaRaServers caRaServersInst(ITEM_CA_RA_SERVERS);
	caRaServersInst.initialise();
	addGroup(caRaServersInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv4-option/security-gateways
	// Description:
	// -----------------------------------------------------------------------------
	GrpSecurityGateways securityGatewaysInst(ITEM_SECURITY_GATEWAYS);
	securityGatewaysInst.initialise();
	addGroup(securityGatewaysInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcpv4-option/dhcp-server-identifier
// Description: DHCP server identifier
// -----------------------------------------------------------------------------
GrpDhcpv4Option::LeafDhcpServerIdentifier::LeafDhcpServerIdentifier(uint32_t id)
	: YangLeaf("dhcp-server-identifier", id)
{
}

GrpDhcpv4Option::LeafDhcpServerIdentifier::~LeafDhcpServerIdentifier()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcpv4-option/domain-name
// Description: Name of the domain
// -----------------------------------------------------------------------------
GrpDhcpv4Option::LeafDomainName::LeafDomainName(uint32_t id)
	: YangLeaf("domain-name", id)
{
}

GrpDhcpv4Option::LeafDomainName::~LeafDomainName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcpv4-option/interface-mtu
// Description: Minimum Transmission Unit (MTU) of the interface
// -----------------------------------------------------------------------------
GrpDhcpv4Option::LeafInterfaceMtu::LeafInterfaceMtu(uint32_t id)
	: YangLeaf("interface-mtu", id)
{
}

GrpDhcpv4Option::LeafInterfaceMtu::~LeafInterfaceMtu()
{
}

// -----------------------------------------------------------------------------
// List:        domain-name-servers
// Description: A list of DNS servers
// -----------------------------------------------------------------------------
GrpDhcpv4Option::LstDomainNameServers::LstDomainNameServers(uint32_t id)
	: YangList("domain-name-servers", id)
{
}

GrpDhcpv4Option::LstDomainNameServers::~LstDomainNameServers()
{
}

YangResult_E GrpDhcpv4Option::LstDomainNameServers::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        default-gateways
// Description: the list of default gateways on the O-RUs subnet
// -----------------------------------------------------------------------------
GrpDhcpv4Option::LstDefaultGateways::LstDefaultGateways(uint32_t id)
	: YangList("default-gateways", id)
{
}

GrpDhcpv4Option::LstDefaultGateways::~LstDefaultGateways()
{
}

YangResult_E GrpDhcpv4Option::LstDefaultGateways::initialise(void)
{


	return YangResult_E::OK;
}





// -----------------------------------------------------------------------------
// Grouping:    dhcpv6-option
// Description: DHCPv6 Configuration options
// -----------------------------------------------------------------------------
GrpDhcpv6Option::GrpDhcpv6Option(uint32_t id)
	: YangGroup("dhcpv6-option", id)
{
}

GrpDhcpv6Option::~GrpDhcpv6Option()
{
}

YangResult_E GrpDhcpv6Option::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv6-option/domain-name
	// Description: Name of the domain
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDomainName domainNameInst(ITEM_DOMAIN_NAME);
	addLeaf(domainNameInst);

	// -----------------------------------------------------------------------------
	// List:        /dhcpv6-option/domain-name-servers
	// Description: A list of DNS servers
	// Array Key:
	// -----------------------------------------------------------------------------
	LstDomainNameServers domainNameServersInst(ITEM_DOMAIN_NAME_SERVERS);
	domainNameServersInst.initialise();
	addList(domainNameServersInst);

	// -----------------------------------------------------------------------------
	// Container:   /dhcpv6-option/dhcp-server-identifier
	// Description: dhcpv6 server identifief
	// -----------------------------------------------------------------------------
	CntDhcpServerIdentifier dhcpServerIdentifierInst(ITEM_DHCP_SERVER_IDENTIFIER);
	dhcpServerIdentifierInst.initialise();
	addContainer(dhcpServerIdentifierInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv6-option/netconf-clients
	// Description:
	// -----------------------------------------------------------------------------
	GrpNetconfClients netconfClientsInst(ITEM_NETCONF_CLIENTS);
	netconfClientsInst.initialise();
	addGroup(netconfClientsInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv6-option/ca-ra-servers
	// Description:
	// -----------------------------------------------------------------------------
	GrpCaRaServers caRaServersInst(ITEM_CA_RA_SERVERS);
	caRaServersInst.initialise();
	addGroup(caRaServersInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv6-option/security-gateways
	// Description:
	// -----------------------------------------------------------------------------
	GrpSecurityGateways securityGatewaysInst(ITEM_SECURITY_GATEWAYS);
	securityGatewaysInst.initialise();
	addGroup(securityGatewaysInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcpv6-option/domain-name
// Description: Name of the domain
// -----------------------------------------------------------------------------
GrpDhcpv6Option::LeafDomainName::LeafDomainName(uint32_t id)
	: YangLeaf("domain-name", id)
{
}

GrpDhcpv6Option::LeafDomainName::~LeafDomainName()
{
}

// -----------------------------------------------------------------------------
// List:        domain-name-servers
// Description: A list of DNS servers
// -----------------------------------------------------------------------------
GrpDhcpv6Option::LstDomainNameServers::LstDomainNameServers(uint32_t id)
	: YangList("domain-name-servers", id)
{
}

GrpDhcpv6Option::LstDomainNameServers::~LstDomainNameServers()
{
}

YangResult_E GrpDhcpv6Option::LstDomainNameServers::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// Container:   dhcp-server-identifier
// Description: dhcpv6 server identifief
// -----------------------------------------------------------------------------
GrpDhcpv6Option::CntDhcpServerIdentifier::CntDhcpServerIdentifier(uint32_t id)
	: YangContainer("dhcp-server-identifier", id)
{
}

GrpDhcpv6Option::CntDhcpServerIdentifier::~CntDhcpServerIdentifier()
{
}

YangResult_E GrpDhcpv6Option::CntDhcpServerIdentifier::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /dhcpv6-option/dhcp-server-identifier/dhcpv6-type:duid
	// Module: ietf-dhcpv6-types
	// Description:
	// -----------------------------------------------------------------------------
	ModuleIetfDhcpv6Types_NS::GrpDuid dhcpv6TypeDuidInst(ITEM_DHCPV6_TYPE_DUID);
	dhcpv6TypeDuidInst.initialise();
	addGroup(dhcpv6TypeDuidInst);



	return YangResult_E::OK;
}






// -----------------------------------------------------------------------------
// Grouping:    dhcp-group
// Description:
// -----------------------------------------------------------------------------
GrpDhcpGroup::GrpDhcpGroup(uint32_t id)
	: YangGroup("dhcp-group", id)
{
}

GrpDhcpGroup::~GrpDhcpGroup()
{
}

YangResult_E GrpDhcpGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /dhcp-group/interfaces
	// Description: Interface configuration
	// Array Key:
	// -----------------------------------------------------------------------------
	LstInterfaces interfacesInst(ITEM_INTERFACES);
	interfacesInst.initialise();
	addList(interfacesInst);

	// -----------------------------------------------------------------------------
	// Container:   /dhcp-group/m-plane-dhcp
	// Description: leafs covering off DHCP aspects of m-plane operations
	// -----------------------------------------------------------------------------
	CntMPlaneDhcp mPlaneDhcpInst(ITEM_M_PLANE_DHCP);
	mPlaneDhcpInst.initialise();
	addContainer(mPlaneDhcpInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        interfaces
// Description: Interface configuration
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::LstInterfaces(uint32_t id)
	: YangList("interfaces", id)
{
}

GrpDhcpGroup::LstInterfaces::~LstInterfaces()
{
}

YangResult_E GrpDhcpGroup::LstInterfaces::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Reference:   /dhcp-group/interfaces/interface
	// Description: Name of the interface
	// Ref:         [reference]
	// Units:
	// -----------------------------------------------------------------------------
	RefInterface interfaceInst(ITEM_INTERFACE);
	addReference(interfaceInst);

	// -----------------------------------------------------------------------------
	// Container:   /dhcp-group/interfaces/dhcpv4
	// Description: DHCPv4 information
	// -----------------------------------------------------------------------------
	CntDhcpv4 dhcpv4Inst(ITEM_DHCPV4);
	dhcpv4Inst.initialise();
	addContainer(dhcpv4Inst);

	// -----------------------------------------------------------------------------
	// Container:   /dhcp-group/interfaces/dhcpv6
	// Description: DHCPv6 information
	// -----------------------------------------------------------------------------
	CntDhcpv6 dhcpv6Inst(ITEM_DHCPV6);
	dhcpv6Inst.initialise();
	addContainer(dhcpv6Inst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /dhcp-group/interfaces/interface
// Description: Name of the interface
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::RefInterface::RefInterface(uint32_t id)
	: YangReference("interface", id, "[reference]")
{
}

GrpDhcpGroup::LstInterfaces::RefInterface::~RefInterface()
{
}

// -----------------------------------------------------------------------------
// Container:   dhcpv4
// Description: DHCPv4 information
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::CntDhcpv4::CntDhcpv4(uint32_t id)
	: YangContainer("dhcpv4", id)
{
}

GrpDhcpGroup::LstInterfaces::CntDhcpv4::~CntDhcpv4()
{
}

YangResult_E GrpDhcpGroup::LstInterfaces::CntDhcpv4::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /dhcp-group/interfaces/dhcpv4/client-id
	// Description: DHCP client identifier
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafClientId clientIdInst(ITEM_CLIENT_ID);
	addLeaf(clientIdInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcp-group/interfaces/dhcpv4/dhcpv4-option
	// Description:
	// -----------------------------------------------------------------------------
	GrpDhcpv4Option dhcpv4OptionInst(ITEM_DHCPV4_OPTION);
	dhcpv4OptionInst.initialise();
	addGroup(dhcpv4OptionInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcp-group/interfaces/dhcpv4/client-id
// Description: DHCP client identifier
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::CntDhcpv4::LeafClientId::LeafClientId(uint32_t id)
	: YangLeaf("client-id", id)
{
}

GrpDhcpGroup::LstInterfaces::CntDhcpv4::LeafClientId::~LeafClientId()
{
}




// -----------------------------------------------------------------------------
// Container:   dhcpv6
// Description: DHCPv6 information
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::CntDhcpv6::CntDhcpv6(uint32_t id)
	: YangContainer("dhcpv6", id)
{
}

GrpDhcpGroup::LstInterfaces::CntDhcpv6::~CntDhcpv6()
{
}

YangResult_E GrpDhcpGroup::LstInterfaces::CntDhcpv6::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /dhcp-group/interfaces/dhcpv6/dhcp-client-identifier
	// Description: dhcpv6 client identifief
	// -----------------------------------------------------------------------------
	CntDhcpClientIdentifier dhcpClientIdentifierInst(ITEM_DHCP_CLIENT_IDENTIFIER);
	dhcpClientIdentifierInst.initialise();
	addContainer(dhcpClientIdentifierInst);

	// -----------------------------------------------------------------------------
	// Uses:        /dhcp-group/interfaces/dhcpv6/dhcpv6-option
	// Description:
	// -----------------------------------------------------------------------------
	GrpDhcpv6Option dhcpv6OptionInst(ITEM_DHCPV6_OPTION);
	dhcpv6OptionInst.initialise();
	addGroup(dhcpv6OptionInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   dhcp-client-identifier
// Description: dhcpv6 client identifief
// -----------------------------------------------------------------------------
GrpDhcpGroup::LstInterfaces::CntDhcpv6::CntDhcpClientIdentifier::CntDhcpClientIdentifier(uint32_t id)
	: YangContainer("dhcp-client-identifier", id)
{
}

GrpDhcpGroup::LstInterfaces::CntDhcpv6::CntDhcpClientIdentifier::~CntDhcpClientIdentifier()
{
}

YangResult_E GrpDhcpGroup::LstInterfaces::CntDhcpv6::CntDhcpClientIdentifier::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /dhcp-group/interfaces/dhcpv6/dhcp-client-identifier/dhcpv6-type:duid
	// Module: ietf-dhcpv6-types
	// Description:
	// -----------------------------------------------------------------------------
	ModuleIetfDhcpv6Types_NS::GrpDuid dhcpv6TypeDuidInst(ITEM_DHCPV6_TYPE_DUID);
	dhcpv6TypeDuidInst.initialise();
	addGroup(dhcpv6TypeDuidInst);



	return YangResult_E::OK;
}









// -----------------------------------------------------------------------------
// Container:   m-plane-dhcp
// Description: leafs covering off DHCP aspects of m-plane operations
// -----------------------------------------------------------------------------
GrpDhcpGroup::CntMPlaneDhcp::CntMPlaneDhcp(uint32_t id)
	: YangContainer("m-plane-dhcp", id)
{
}

GrpDhcpGroup::CntMPlaneDhcp::~CntMPlaneDhcp()
{
}

YangResult_E GrpDhcpGroup::CntMPlaneDhcp::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-number
	// Description: the private enteprise number allocated to O-RAN Alliance
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrivateEnterpriseNumber privateEnterpriseNumberInst(ITEM_PRIVATE_ENTERPRISE_NUMBER);
	addLeaf(privateEnterpriseNumberInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-num
	// Description: the private enterprise number allocated to O-RAN Alliance
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafPrivateEnterpriseNum privateEnterpriseNumInst(ITEM_PRIVATE_ENTERPRISE_NUM);
	addLeaf(privateEnterpriseNumInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcp-group/m-plane-dhcp/vendor-class-data
	// Description: The string used in DHCPv4 option 60 or DHCPv4 option 124 and
	//              DHCPv6 option 16
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafVendorClassData vendorClassDataInst(ITEM_VENDOR_CLASS_DATA);
	addLeaf(vendorClassDataInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-number
// Description: the private enteprise number allocated to O-RAN Alliance
// -----------------------------------------------------------------------------
GrpDhcpGroup::CntMPlaneDhcp::LeafPrivateEnterpriseNumber::LeafPrivateEnterpriseNumber(uint32_t id)
	: YangLeaf("private-enterprise-number", id)
{
}

GrpDhcpGroup::CntMPlaneDhcp::LeafPrivateEnterpriseNumber::~LeafPrivateEnterpriseNumber()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-num
// Description: the private enterprise number allocated to O-RAN Alliance
// -----------------------------------------------------------------------------
GrpDhcpGroup::CntMPlaneDhcp::LeafPrivateEnterpriseNum::LeafPrivateEnterpriseNum(uint32_t id)
	: YangLeaf("private-enterprise-num", id)
{
}

GrpDhcpGroup::CntMPlaneDhcp::LeafPrivateEnterpriseNum::~LeafPrivateEnterpriseNum()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /dhcp-group/m-plane-dhcp/vendor-class-data
// Description: The string used in DHCPv4 option 60 or DHCPv4 option 124 and
//              DHCPv6 option 16
// -----------------------------------------------------------------------------
GrpDhcpGroup::CntMPlaneDhcp::LeafVendorClassData::LeafVendorClassData(uint32_t id)
	: YangLeaf("vendor-class-data", id)
{
}

GrpDhcpGroup::CntMPlaneDhcp::LeafVendorClassData::~LeafVendorClassData()
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
// Module:      o-ran-dhcp
// Description: This module defines the YANG definitions for managng the DHCP client.
//
//              Copyright 2019 the O-RAN alliance.
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
ModuleORanDhcp::ModuleORanDhcp(uint32_t id)
	: YangModule ("o-ran-dhcp",
	              "o-ran-dhcp.yang",
	              "o-ran-dhcp",
	              "urn:o-ran:dhcp:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /dhcp
	// Description: DHCP client configuration
	// -----------------------------------------------------------------------------
	CntDhcp dhcpInst(ITEM_DHCP);
	dhcpInst.initialise();
	addContainer(dhcpInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanDhcp::~ModuleORanDhcp()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanDhcp::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanDhcp>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanDhcp::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
