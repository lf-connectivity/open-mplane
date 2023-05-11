#ifndef _MODULE_O_RAN_MPLANE_INT_H_
#define _MODULE_O_RAN_MPLANE_INT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanMplaneInt.h
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

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"


namespace Mplane {

namespace ModuleORanMplaneInt_NS {

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
// Container:   /mplane-info
// Description: top level container for management plane information
// -----------------------------------------------------------------------------
class CntMplaneInfo : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MPLANE_GROUP,  // Use GrpMplaneGroup
	};

	CntMplaneInfo(uint32_t id);
	~CntMplaneInfo();

	YangResult_E initialise(void);

}; // CntMplaneInfo


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /mplane-group
// Description:
// -----------------------------------------------------------------------------
class GrpMplaneGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_SEARCHABLE_MPLANE_ACCESS_VLANS_INFO,  // CntSearchableMplaneAccessVlansInfo
		ITEM_M_PLANE_INTERFACES,  // CntMPlaneInterfaces
		ITEM_CONFIGURED_CLIENT_INFO,  // CntConfiguredClientInfo
	};

	GrpMplaneGroup(uint32_t id);
	~GrpMplaneGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/searchable-mplane-access-vlans-info
	// Description: These parameters shall be stored by the equipment in reset persistant memory
	//              to enable it to be re-used to optimize VALN discovery procerdures.
	// -----------------------------------------------------------------------------
	class CntSearchableMplaneAccessVlansInfo : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_VLAN_RANGE,  // CntVlanRange
			ITEM_SEARCHABLE_ACCESS_VLANS,  // LstSearchableAccessVlans
		};

		CntSearchableMplaneAccessVlansInfo(uint32_t id);
		~CntSearchableMplaneAccessVlansInfo();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Container:   /mplane-group/searchable-mplane-access-vlans-info/vlan-range
		// Description: the range of VLAN IDs that may be configured for M-Plane
		// -----------------------------------------------------------------------------
		class CntVlanRange : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_LOWEST_VLAN_ID,  // LeafLowestVlanId
				ITEM_HIGHEST_VLAN_ID,  // LeafHighestVlanId
			};

			CntVlanRange(uint32_t id);
			~CntVlanRange();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/lowest-vlan-id
			// Description: Value of this parameter informs equipment about lowest VID to be used
			//              in VLAN scan procedure
			// -----------------------------------------------------------------------------
			class LeafLowestVlanId : public YangLeaf
			{
			public:

				LeafLowestVlanId(uint32_t id);
				~LeafLowestVlanId();

			}; // LeafLowestVlanId

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/searchable-mplane-access-vlans-info/vlan-range/highest-vlan-id
			// Description: Value of this parameter informs about highest VID to be used
			//              in VLAN scan procedure
			// -----------------------------------------------------------------------------
			class LeafHighestVlanId : public YangLeaf
			{
			public:

				LeafHighestVlanId(uint32_t id);
				~LeafHighestVlanId();

			}; // LeafHighestVlanId

		}; // CntVlanRange

		// -----------------------------------------------------------------------------
		// List:        /mplane-group/searchable-mplane-access-vlans-info/searchable-access-vlans
		// Description: A list of access VLANs that may be operational on the transport
		//              network. Can be used by the equipment to optimize its VLAN searching - for
		//              M-plane operations.
		// -----------------------------------------------------------------------------
		class LstSearchableAccessVlans : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstSearchableAccessVlans(uint32_t id);
			~LstSearchableAccessVlans();

			YangResult_E initialise(void);

		}; // LstSearchableAccessVlans

	}; // CntSearchableMplaneAccessVlansInfo

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/m-plane-interfaces
	// Description: information concerning m-plane interfaces
	// -----------------------------------------------------------------------------
	class CntMPlaneInterfaces : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_M_PLANE_SSH_PORTS,  // CntMPlaneSshPorts
			ITEM_M_PLANE_SUB_INTERFACES,  // LstMPlaneSubInterfaces
		};

		CntMPlaneInterfaces(uint32_t id);
		~CntMPlaneInterfaces();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Container:   /mplane-group/m-plane-interfaces/m-plane-ssh-ports
		// Description: leafs for managing SSH ports
		// -----------------------------------------------------------------------------
		class CntMPlaneSshPorts : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_CALL_HOME_SSH_PORT,  // LeafCallHomeSshPort
				ITEM_SERVER_SSH_PORT,  // LeafServerSshPort
			};

			CntMPlaneSshPorts(uint32_t id);
			~CntMPlaneSshPorts();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/call-home-ssh-port
			// Description: The configured call home server port number
			// -----------------------------------------------------------------------------
			class LeafCallHomeSshPort : public YangLeaf
			{
			public:

				LeafCallHomeSshPort(uint32_t id);
				~LeafCallHomeSshPort();

			}; // LeafCallHomeSshPort

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/m-plane-interfaces/m-plane-ssh-ports/server-ssh-port
			// Description: The configured SSH server port number
			// -----------------------------------------------------------------------------
			class LeafServerSshPort : public YangLeaf
			{
			public:

				LeafServerSshPort(uint32_t id);
				~LeafServerSshPort();

			}; // LeafServerSshPort

		}; // CntMPlaneSshPorts

		// -----------------------------------------------------------------------------
		// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces
		// Description: list of m-plane information
		// -----------------------------------------------------------------------------
		class LstMPlaneSubInterfaces : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_INTERFACE_NAME,  // RefInterfaceName
				ITEM_SUB_INTERFACE,  // RefSubInterface
				ITEM_CLIENT_INFO,  // CntClientInfo
			};

			LstMPlaneSubInterfaces(uint32_t id);
			~LstMPlaneSubInterfaces();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/interface-name
			// Description: the name of the interface
			// -----------------------------------------------------------------------------
			class RefInterfaceName : public YangReference
			{
			public:

				RefInterfaceName(uint32_t id);
				~RefInterfaceName();

			}; // RefInterfaceName

			// -----------------------------------------------------------------------------
			// Reference:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/sub-interface
			// Description: vlans used to communicate with management plane servers.
			// -----------------------------------------------------------------------------
			class RefSubInterface : public YangReference
			{
			public:

				RefSubInterface(uint32_t id);
				~RefSubInterface();

			}; // RefSubInterface

			// -----------------------------------------------------------------------------
			// Container:   /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info
			// Description: the NETCONF client information, discovered by DHCP or manually
			//              configured during installation.
			// -----------------------------------------------------------------------------
			class CntClientInfo : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_MPLANE_FQDN,  // LstMplaneFqdn
					ITEM_MPLANE_IPV4_INFO,  // LstMplaneIpv4Info
					ITEM_MPLANE_IPV6_INFO,  // LstMplaneIpv6Info
				};

				CntClientInfo(uint32_t id);
				~CntClientInfo();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-fqdn
				// Description: The discovered FQDN(s) of M-Plane client(s).
				// -----------------------------------------------------------------------------
				class LstMplaneFqdn : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
					};

					LstMplaneFqdn(uint32_t id);
					~LstMplaneFqdn();

					YangResult_E initialise(void);

				}; // LstMplaneFqdn

				// -----------------------------------------------------------------------------
				// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info
				// Description: list of IPv4 NETCONF clients
				// -----------------------------------------------------------------------------
				class LstMplaneIpv4Info : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
						ITEM_MPLANE_IPV4,  // LeafMplaneIpv4
						ITEM_PORT,  // LeafPort
					};

					LstMplaneIpv4Info(uint32_t id);
					~LstMplaneIpv4Info();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/mplane-ipv4
					// Description: The IPv4 address of M-Plane client discovered by the O-RU
					//              or manually configured.
					// -----------------------------------------------------------------------------
					class LeafMplaneIpv4 : public YangLeaf
					{
					public:

						LeafMplaneIpv4(uint32_t id);
						~LeafMplaneIpv4();

					}; // LeafMplaneIpv4

					// -----------------------------------------------------------------------------
					// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv4-info/port
					// Description: The call home port number discovered or manually configured.
					// -----------------------------------------------------------------------------
					class LeafPort : public YangLeaf
					{
					public:

						LeafPort(uint32_t id);
						~LeafPort();

					}; // LeafPort

				}; // LstMplaneIpv4Info

				// -----------------------------------------------------------------------------
				// List:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info
				// Description: list of IPv6 NETCONF clients
				// -----------------------------------------------------------------------------
				class LstMplaneIpv6Info : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
						ITEM_MPLANE_IPV6,  // LeafMplaneIpv6
						ITEM_PORT,  // LeafPort
					};

					LstMplaneIpv6Info(uint32_t id);
					~LstMplaneIpv6Info();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/mplane-ipv6
					// Description: The IPv6 address of M-Plane client discovered by the O-RU
					//              or manually configured.
					// -----------------------------------------------------------------------------
					class LeafMplaneIpv6 : public YangLeaf
					{
					public:

						LeafMplaneIpv6(uint32_t id);
						~LeafMplaneIpv6();

					}; // LeafMplaneIpv6

					// -----------------------------------------------------------------------------
					// Leaf:        /mplane-group/m-plane-interfaces/m-plane-sub-interfaces/client-info/mplane-ipv6-info/port
					// Description: The call home port number discovered or manually configured.
					// -----------------------------------------------------------------------------
					class LeafPort : public YangLeaf
					{
					public:

						LeafPort(uint32_t id);
						~LeafPort();

					}; // LeafPort

				}; // LstMplaneIpv6Info

			}; // CntClientInfo

		}; // LstMPlaneSubInterfaces

	}; // CntMPlaneInterfaces

	// -----------------------------------------------------------------------------
	// Container:   /mplane-group/configured-client-info
	// Description: the NETCONF client information that may be configured by another
	//              NETCONF client. These clients are reported independently from clients
	//              manually configured or discovered using DHCP.
	// -----------------------------------------------------------------------------
	class CntConfiguredClientInfo : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_MPLANE_FQDN,  // LstMplaneFqdn
			ITEM_MPLANE_IPV4_INFO,  // LstMplaneIpv4Info
			ITEM_MPLANE_IPV6_INFO,  // LstMplaneIpv6Info
		};

		CntConfiguredClientInfo(uint32_t id);
		~CntConfiguredClientInfo();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /mplane-group/configured-client-info/mplane-fqdn
		// Description: The configured FQDN(s) of M-Plane client(s).
		// -----------------------------------------------------------------------------
		class LstMplaneFqdn : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstMplaneFqdn(uint32_t id);
			~LstMplaneFqdn();

			YangResult_E initialise(void);

		}; // LstMplaneFqdn

		// -----------------------------------------------------------------------------
		// List:        /mplane-group/configured-client-info/mplane-ipv4-info
		// Description: list of IPv4 NETCONF clients
		// -----------------------------------------------------------------------------
		class LstMplaneIpv4Info : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_MPLANE_IPV4,  // LeafMplaneIpv4
				ITEM_PORT,  // LeafPort
			};

			LstMplaneIpv4Info(uint32_t id);
			~LstMplaneIpv4Info();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/mplane-ipv4
			// Description: The IPv4 address of configured M-Plane client.
			// -----------------------------------------------------------------------------
			class LeafMplaneIpv4 : public YangLeaf
			{
			public:

				LeafMplaneIpv4(uint32_t id);
				~LeafMplaneIpv4();

			}; // LeafMplaneIpv4

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/configured-client-info/mplane-ipv4-info/port
			// Description: The configured call home port number.
			// -----------------------------------------------------------------------------
			class LeafPort : public YangLeaf
			{
			public:

				LeafPort(uint32_t id);
				~LeafPort();

			}; // LeafPort

		}; // LstMplaneIpv4Info

		// -----------------------------------------------------------------------------
		// List:        /mplane-group/configured-client-info/mplane-ipv6-info
		// Description: list of IPv6 NETCONF clients
		// -----------------------------------------------------------------------------
		class LstMplaneIpv6Info : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_MPLANE_IPV6,  // LeafMplaneIpv6
				ITEM_PORT,  // LeafPort
			};

			LstMplaneIpv6Info(uint32_t id);
			~LstMplaneIpv6Info();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/mplane-ipv6
			// Description: The IPv6 address of configured M-Plane client..
			// -----------------------------------------------------------------------------
			class LeafMplaneIpv6 : public YangLeaf
			{
			public:

				LeafMplaneIpv6(uint32_t id);
				~LeafMplaneIpv6();

			}; // LeafMplaneIpv6

			// -----------------------------------------------------------------------------
			// Leaf:        /mplane-group/configured-client-info/mplane-ipv6-info/port
			// Description: The configured call home port number.
			// -----------------------------------------------------------------------------
			class LeafPort : public YangLeaf
			{
			public:

				LeafPort(uint32_t id);
				~LeafPort();

			}; // LeafPort

		}; // LstMplaneIpv6Info

	}; // CntConfiguredClientInfo

}; // GrpMplaneGroup


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
class ModuleORanMplaneInt : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MPLANE_INFO,  // CntMplaneInfo
	};

	ModuleORanMplaneInt(uint32_t id);
	~ModuleORanMplaneInt();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanMplaneInt_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_MPLANE_INT_H_ */
