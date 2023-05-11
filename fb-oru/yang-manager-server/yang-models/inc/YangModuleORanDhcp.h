#ifndef _MODULE_O_RAN_DHCP_H_
#define _MODULE_O_RAN_DHCP_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanDhcp.h
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

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   ietf-dhcpv6-types
// Revision: 2018-01-30
// Notes:
#include "YangModuleIetfDhcpv6Types.h"


namespace Mplane {

namespace ModuleORanDhcp_NS {

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
// Container:   /dhcp
// Description: DHCP client configuration
// -----------------------------------------------------------------------------
class CntDhcp : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DHCP_GROUP,  // Use GrpDhcpGroup
	};

	CntDhcp(uint32_t id);
	~CntDhcp();

	YangResult_E initialise(void);

}; // CntDhcp


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /ca-ra-servers
// Description: The CA/RA servers discovered using DHCP, discovered using the 3GPP
//              defined options in 3GPP 32.509 in vendor specific option 43/17
// -----------------------------------------------------------------------------
class GrpCaRaServers : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_CA_RA_SERVERS,  // LstCaRaServers
	};

	GrpCaRaServers(uint32_t id);
	~GrpCaRaServers();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /ca-ra-servers/ca-ra-servers
	// Description: A list of IP addresses or URIs for CA/RA Servers
	// -----------------------------------------------------------------------------
	class LstCaRaServers : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SERVERS,  // LeafServers
			ITEM_PORT_NUMBER,  // LeafPortNumber
			ITEM_CA_RA_PATH,  // LeafCaRaPath
			ITEM_SUBJECT_NAME,  // LeafSubjectName
			ITEM_PROTOCOL,  // LeafProtocol
		};

		LstCaRaServers(uint32_t id);
		~LstCaRaServers();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /ca-ra-servers/ca-ra-servers/servers
		// Description: the server identifier
		// -----------------------------------------------------------------------------
		class LeafServers : public YangLeaf
		{
		public:

			LeafServers(uint32_t id);
			~LeafServers();

		}; // LeafServers

		// -----------------------------------------------------------------------------
		// Leaf:        /ca-ra-servers/ca-ra-servers/port-number
		// Description: an optional (non-default) port
		// -----------------------------------------------------------------------------
		class LeafPortNumber : public YangLeaf
		{
		public:

			LeafPortNumber(uint32_t id);
			~LeafPortNumber();

		}; // LeafPortNumber

		// -----------------------------------------------------------------------------
		// Leaf:        /ca-ra-servers/ca-ra-servers/ca-ra-path
		// Description: ASCII string representing the path to the CMP server directory.
		//              A CMP server may be located in an arbitrary path other than root.
		// -----------------------------------------------------------------------------
		class LeafCaRaPath : public YangLeaf
		{
		public:

			LeafCaRaPath(uint32_t id);
			~LeafCaRaPath();

		}; // LeafCaRaPath

		// -----------------------------------------------------------------------------
		// Leaf:        /ca-ra-servers/ca-ra-servers/subject-name
		// Description: ASCII string representing the subject name of the CA/RA.
		// -----------------------------------------------------------------------------
		class LeafSubjectName : public YangLeaf
		{
		public:

			LeafSubjectName(uint32_t id);
			~LeafSubjectName();

		}; // LeafSubjectName

		// -----------------------------------------------------------------------------
		// Leaf:        /ca-ra-servers/ca-ra-servers/protocol
		// Description:
		// -----------------------------------------------------------------------------
		class LeafProtocol : public YangLeaf
		{
		public:

			//
			enum class Protocol_E : uint32_t
			{
				HTTP,	//
				HTTPS,	//

				Num_Protocol_E
			};

			LeafProtocol(uint32_t id);
			~LeafProtocol();

		}; // LeafProtocol

	}; // LstCaRaServers

}; // GrpCaRaServers

// -----------------------------------------------------------------------------
// Grouping:    /security-gateways
// Description: The security gateways discovered using DHCP, discovered using the 3GPP
//              defined options in 3GPP 32.509 in vendor specific option 43/17
// -----------------------------------------------------------------------------
class GrpSecurityGateways : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SEGW,  // LstSegw
	};

	GrpSecurityGateways(uint32_t id);
	~GrpSecurityGateways();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /security-gateways/segw
	// Description: A list of IP addresses or URIs for SeGW
	// -----------------------------------------------------------------------------
	class LstSegw : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_GATEWAYS,  // LeafGateways
		};

		LstSegw(uint32_t id);
		~LstSegw();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /security-gateways/segw/gateways
		// Description: the SeGW identifier
		// -----------------------------------------------------------------------------
		class LeafGateways : public YangLeaf
		{
		public:

			LeafGateways(uint32_t id);
			~LeafGateways();

		}; // LeafGateways

	}; // LstSegw

}; // GrpSecurityGateways

// -----------------------------------------------------------------------------
// Grouping:    /netconf-clients
// Description: The netconf clients discovered using DHCP, discovered using the IANA
//              defined options or O-RAN defined syntax for encoding IP adresses or FQDNs
//              in vendor specific option 43/17
// -----------------------------------------------------------------------------
class GrpNetconfClients : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_NETCONF_CLIENTS,  // LstNetconfClients
	};

	GrpNetconfClients(uint32_t id);
	~GrpNetconfClients();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /netconf-clients/netconf-clients
	// Description: A list of IP addresses or URIs for NETCONF clients
	// -----------------------------------------------------------------------------
	class LstNetconfClients : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_CLIENT,  // LeafClient
			ITEM_OPTIONAL_PORT,  // LeafOptionalPort
		};

		LstNetconfClients(uint32_t id);
		~LstNetconfClients();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-clients/netconf-clients/client
		// Description: the client identifier
		// -----------------------------------------------------------------------------
		class LeafClient : public YangLeaf
		{
		public:

			LeafClient(uint32_t id);
			~LeafClient();

		}; // LeafClient

		// -----------------------------------------------------------------------------
		// Leaf:        /netconf-clients/netconf-clients/optional-port
		// Description: an optional (non-default) port
		// -----------------------------------------------------------------------------
		class LeafOptionalPort : public YangLeaf
		{
		public:

			LeafOptionalPort(uint32_t id);
			~LeafOptionalPort();

		}; // LeafOptionalPort

	}; // LstNetconfClients

}; // GrpNetconfClients

// -----------------------------------------------------------------------------
// Grouping:    /dhcpv4-option
// Description: DHCPv4 Configuration options
// -----------------------------------------------------------------------------
class GrpDhcpv4Option : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DHCP_SERVER_IDENTIFIER,  // LeafDhcpServerIdentifier
		ITEM_DOMAIN_NAME,  // LeafDomainName
		ITEM_INTERFACE_MTU,  // LeafInterfaceMtu
		ITEM_DOMAIN_NAME_SERVERS,  // LstDomainNameServers
		ITEM_DEFAULT_GATEWAYS,  // LstDefaultGateways
		ITEM_NETCONF_CLIENTS,  // Use GrpNetconfClients
		ITEM_CA_RA_SERVERS,  // Use GrpCaRaServers
		ITEM_SECURITY_GATEWAYS,  // Use GrpSecurityGateways
	};

	GrpDhcpv4Option(uint32_t id);
	~GrpDhcpv4Option();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/dhcp-server-identifier
	// Description: DHCP server identifier
	// -----------------------------------------------------------------------------
	class LeafDhcpServerIdentifier : public YangLeaf
	{
	public:

		LeafDhcpServerIdentifier(uint32_t id);
		~LeafDhcpServerIdentifier();

	}; // LeafDhcpServerIdentifier

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/domain-name
	// Description: Name of the domain
	// -----------------------------------------------------------------------------
	class LeafDomainName : public YangLeaf
	{
	public:

		LeafDomainName(uint32_t id);
		~LeafDomainName();

	}; // LeafDomainName

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv4-option/interface-mtu
	// Description: Minimum Transmission Unit (MTU) of the interface
	// -----------------------------------------------------------------------------
	class LeafInterfaceMtu : public YangLeaf
	{
	public:

		LeafInterfaceMtu(uint32_t id);
		~LeafInterfaceMtu();

	}; // LeafInterfaceMtu

	// -----------------------------------------------------------------------------
	// List:        /dhcpv4-option/domain-name-servers
	// Description: A list of DNS servers
	// -----------------------------------------------------------------------------
	class LstDomainNameServers : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstDomainNameServers(uint32_t id);
		~LstDomainNameServers();

		YangResult_E initialise(void);

	}; // LstDomainNameServers

	// -----------------------------------------------------------------------------
	// List:        /dhcpv4-option/default-gateways
	// Description: the list of default gateways on the O-RUs subnet
	// -----------------------------------------------------------------------------
	class LstDefaultGateways : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstDefaultGateways(uint32_t id);
		~LstDefaultGateways();

		YangResult_E initialise(void);

	}; // LstDefaultGateways

}; // GrpDhcpv4Option

// -----------------------------------------------------------------------------
// Grouping:    /dhcpv6-option
// Description: DHCPv6 Configuration options
// -----------------------------------------------------------------------------
class GrpDhcpv6Option : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DOMAIN_NAME,  // LeafDomainName
		ITEM_DHCP_SERVER_IDENTIFIER,  // CntDhcpServerIdentifier
		ITEM_DOMAIN_NAME_SERVERS,  // LstDomainNameServers
		ITEM_NETCONF_CLIENTS,  // Use GrpNetconfClients
		ITEM_CA_RA_SERVERS,  // Use GrpCaRaServers
		ITEM_SECURITY_GATEWAYS,  // Use GrpSecurityGateways
	};

	GrpDhcpv6Option(uint32_t id);
	~GrpDhcpv6Option();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /dhcpv6-option/domain-name
	// Description: Name of the domain
	// -----------------------------------------------------------------------------
	class LeafDomainName : public YangLeaf
	{
	public:

		LeafDomainName(uint32_t id);
		~LeafDomainName();

	}; // LeafDomainName

	// -----------------------------------------------------------------------------
	// Container:   /dhcpv6-option/dhcp-server-identifier
	// Description: dhcpv6 server identifief
	// -----------------------------------------------------------------------------
	class CntDhcpServerIdentifier : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_DHCPV6_TYPE_DUID,  // Use GrpDhcpv6TypeDuid
		};

		CntDhcpServerIdentifier(uint32_t id);
		~CntDhcpServerIdentifier();

		YangResult_E initialise(void);

	}; // CntDhcpServerIdentifier

	// -----------------------------------------------------------------------------
	// List:        /dhcpv6-option/domain-name-servers
	// Description: A list of DNS servers
	// -----------------------------------------------------------------------------
	class LstDomainNameServers : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstDomainNameServers(uint32_t id);
		~LstDomainNameServers();

		YangResult_E initialise(void);

	}; // LstDomainNameServers

}; // GrpDhcpv6Option

// -----------------------------------------------------------------------------
// Grouping:    /dhcp-group
// Description:
// -----------------------------------------------------------------------------
class GrpDhcpGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_M_PLANE_DHCP,  // CntMPlaneDhcp
		ITEM_INTERFACES,  // LstInterfaces
	};

	GrpDhcpGroup(uint32_t id);
	~GrpDhcpGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /dhcp-group/m-plane-dhcp
	// Description: leafs covering off DHCP aspects of m-plane operations
	// -----------------------------------------------------------------------------
	class CntMPlaneDhcp : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_PRIVATE_ENTERPRISE_NUMBER,  // LeafPrivateEnterpriseNumber
			ITEM_PRIVATE_ENTERPRISE_NUM,  // LeafPrivateEnterpriseNum
			ITEM_VENDOR_CLASS_DATA,  // LeafVendorClassData
		};

		CntMPlaneDhcp(uint32_t id);
		~CntMPlaneDhcp();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-number
		// Description: the private enteprise number allocated to O-RAN Alliance
		// -----------------------------------------------------------------------------
		class LeafPrivateEnterpriseNumber : public YangLeaf
		{
		public:

			LeafPrivateEnterpriseNumber(uint32_t id);
			~LeafPrivateEnterpriseNumber();

		}; // LeafPrivateEnterpriseNumber

		// -----------------------------------------------------------------------------
		// Leaf:        /dhcp-group/m-plane-dhcp/private-enterprise-num
		// Description: the private enterprise number allocated to O-RAN Alliance
		// -----------------------------------------------------------------------------
		class LeafPrivateEnterpriseNum : public YangLeaf
		{
		public:

			LeafPrivateEnterpriseNum(uint32_t id);
			~LeafPrivateEnterpriseNum();

		}; // LeafPrivateEnterpriseNum

		// -----------------------------------------------------------------------------
		// Leaf:        /dhcp-group/m-plane-dhcp/vendor-class-data
		// Description: The string used in DHCPv4 option 60 or DHCPv4 option 124 and
		//              DHCPv6 option 16
		// -----------------------------------------------------------------------------
		class LeafVendorClassData : public YangLeaf
		{
		public:

			LeafVendorClassData(uint32_t id);
			~LeafVendorClassData();

		}; // LeafVendorClassData

	}; // CntMPlaneDhcp

	// -----------------------------------------------------------------------------
	// List:        /dhcp-group/interfaces
	// Description: Interface configuration
	// -----------------------------------------------------------------------------
	class LstInterfaces : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_INTERFACE,  // RefInterface
			ITEM_DHCPV4,  // CntDhcpv4
			ITEM_DHCPV6,  // CntDhcpv6
		};

		LstInterfaces(uint32_t id);
		~LstInterfaces();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Reference:   /dhcp-group/interfaces/interface
		// Description: Name of the interface
		// -----------------------------------------------------------------------------
		class RefInterface : public YangReference
		{
		public:

			RefInterface(uint32_t id);
			~RefInterface();

		}; // RefInterface

		// -----------------------------------------------------------------------------
		// Container:   /dhcp-group/interfaces/dhcpv4
		// Description: DHCPv4 information
		// -----------------------------------------------------------------------------
		class CntDhcpv4 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_CLIENT_ID,  // LeafClientId
				ITEM_DHCPV4_OPTION,  // Use GrpDhcpv4Option
			};

			CntDhcpv4(uint32_t id);
			~CntDhcpv4();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /dhcp-group/interfaces/dhcpv4/client-id
			// Description: DHCP client identifier
			// -----------------------------------------------------------------------------
			class LeafClientId : public YangLeaf
			{
			public:

				LeafClientId(uint32_t id);
				~LeafClientId();

			}; // LeafClientId

		}; // CntDhcpv4

		// -----------------------------------------------------------------------------
		// Container:   /dhcp-group/interfaces/dhcpv6
		// Description: DHCPv6 information
		// -----------------------------------------------------------------------------
		class CntDhcpv6 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DHCP_CLIENT_IDENTIFIER,  // CntDhcpClientIdentifier
				ITEM_DHCPV6_OPTION,  // Use GrpDhcpv6Option
			};

			CntDhcpv6(uint32_t id);
			~CntDhcpv6();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Container:   /dhcp-group/interfaces/dhcpv6/dhcp-client-identifier
			// Description: dhcpv6 client identifief
			// -----------------------------------------------------------------------------
			class CntDhcpClientIdentifier : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_DHCPV6_TYPE_DUID,  // Use GrpDhcpv6TypeDuid
				};

				CntDhcpClientIdentifier(uint32_t id);
				~CntDhcpClientIdentifier();

				YangResult_E initialise(void);

			}; // CntDhcpClientIdentifier

		}; // CntDhcpv6

	}; // LstInterfaces

}; // GrpDhcpGroup


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
class ModuleORanDhcp : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_DHCP,  // CntDhcp
	};

	ModuleORanDhcp(uint32_t id);
	~ModuleORanDhcp();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanDhcp_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_DHCP_H_ */
