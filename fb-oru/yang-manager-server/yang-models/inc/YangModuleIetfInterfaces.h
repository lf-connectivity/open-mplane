#ifndef _MODULE_IETF_INTERFACES_H_
#define _MODULE_IETF_INTERFACES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfInterfaces.h
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

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleIetfInterfaces_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************


// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device allows user-controlled
//              interfaces to be named arbitrarily.
// -----------------------------------------------------------------------------
class FeatureArbitraryNames : public YangFeature
{
public:
	FeatureArbitraryNames(uint32_t id);
	~FeatureArbitraryNames();

}; // FeatureArbitraryNames

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device supports
//              pre-provisioning of interface configuration, i.e., it is
//              possible to configure an interface whose physical interface
//              hardware is not present on the device.
// -----------------------------------------------------------------------------
class FeaturePreProvisioning : public YangFeature
{
public:
	FeaturePreProvisioning(uint32_t id);
	~FeaturePreProvisioning();

}; // FeaturePreProvisioning

// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the device implements
//              the IF-MIB.
// -----------------------------------------------------------------------------
class FeatureIfMib : public YangFeature
{
public:
	FeatureIfMib(uint32_t id);
	~FeatureIfMib();

}; // FeatureIfMib


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
// Container:   /interfaces
// Description: Interface parameters.
// -----------------------------------------------------------------------------
class CntInterfaces : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_INTERFACE,  // LstInterface
	};

	CntInterfaces(uint32_t id);
	~CntInterfaces();

	YangResult_E initialise(void);

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
	// -----------------------------------------------------------------------------
	class LstInterface : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_DESCRIPTION,  // LeafDescription
			ITEM_TYPE,  // LeafType
			ITEM_ENABLED,  // LeafEnabled
			ITEM_LINK_UP_DOWN_TRAP_ENABLE,  // LeafLinkUpDownTrapEnable
			ITEM_ADMIN_STATUS,  // LeafAdminStatus
			ITEM_OPER_STATUS,  // LeafOperStatus
			ITEM_LAST_CHANGE,  // LeafLastChange
			ITEM_IF_INDEX,  // LeafIfIndex
			ITEM_PHYS_ADDRESS,  // LeafPhysAddress
			ITEM_SPEED,  // LeafSpeed
			ITEM_L2_MTU,  // LeafL2Mtu
			ITEM_VLAN_TAGGING,  // LeafVlanTagging
			ITEM_VLAN_ID,  // LeafVlanId
			ITEM_LAST_CLEARED,  // LeafLastCleared
			ITEM_MAC_ADDRESS,  // LeafMacAddress
			ITEM_BASE_INTERFACE,  // RefBaseInterface
			ITEM_STATISTICS,  // CntStatistics
			ITEM_IPV4,  // CntIpv4
			ITEM_IPV6,  // CntIpv6
			ITEM_PORT_REFERENCE,  // CntPortReference
			ITEM_HIGHER_LAYER_IF,  // LstHigherLayerIf
			ITEM_LOWER_LAYER_IF,  // LstLowerLayerIf
			ITEM_ALIAS_MACS,  // LstAliasMacs
			ITEM_COS_MARKING,  // Use GrpCosMarking
		};

		LstInterface(uint32_t id);
		~LstInterface();

		YangResult_E initialise(void);

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
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

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
		class LeafDescription : public YangLeaf
		{
		public:

			LeafDescription(uint32_t id);
			~LeafDescription();

		}; // LeafDescription

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
		class LeafType : public YangLeaf
		{
		public:

			LeafType(uint32_t id);
			~LeafType();

		}; // LeafType

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
		class LeafEnabled : public YangLeaf
		{
		public:

			LeafEnabled(uint32_t id);
			~LeafEnabled();

		}; // LeafEnabled

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/link-up-down-trap-enable
		// Description: Controls whether linkUp/linkDown SNMP notifications
		//              should be generated for this interface.
		//              If this node is not configured, the value 'enabled' is
		//              operationally used by the server for interfaces that do
		//              not operate on top of any other interface (i.e., there are
		//              no 'lower-layer-if' entries), and 'disabled' otherwise.
		// -----------------------------------------------------------------------------
		class LeafLinkUpDownTrapEnable : public YangLeaf
		{
		public:

			// Controls whether linkUp/linkDown SNMP notifications
			// should be generated for this interface.
			// If this node is not configured, the value 'enabled' is
			// operationally used by the server for interfaces that do
			// not operate on top of any other interface (i.e., there are
			// no 'lower-layer-if' entries), and 'disabled' otherwise.
			enum class LinkUpDownTrapEnable_E : uint32_t
			{
				ENABLED,	// The device will generate linkUp/linkDown SNMP
						// notifications for this interface.
				DISABLED,	// The device will not generate linkUp/linkDown SNMP
						// notifications for this interface.

				Num_LinkUpDownTrapEnable_E
			};

			LeafLinkUpDownTrapEnable(uint32_t id);
			~LeafLinkUpDownTrapEnable();

		}; // LeafLinkUpDownTrapEnable

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/admin-status
		// Description: The desired state of the interface.
		//              This leaf has the same read semantics as ifAdminStatus.
		// -----------------------------------------------------------------------------
		class LeafAdminStatus : public YangLeaf
		{
		public:

			// The desired state of the interface.
			// This leaf has the same read semantics as ifAdminStatus.
			enum class AdminStatus_E : uint32_t
			{
				UP,	// Ready to pass packets.
				DOWN,	// Not ready to pass packets and not in some test mode.
				TESTING,	// In some test mode.

				Num_AdminStatus_E
			};

			LeafAdminStatus(uint32_t id);
			~LeafAdminStatus();

		}; // LeafAdminStatus

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/oper-status
		// Description: The current operational state of the interface.
		//              This leaf has the same semantics as ifOperStatus.
		// -----------------------------------------------------------------------------
		class LeafOperStatus : public YangLeaf
		{
		public:

			// The current operational state of the interface.
			// This leaf has the same semantics as ifOperStatus.
			enum class OperStatus_E : uint32_t
			{
				UP,	// Ready to pass packets.
				DOWN,	// The interface does not pass any packets.
				TESTING,	// In some test mode.  No operational packets can
						// be passed.
				UNKNOWN,	// Status cannot be determined for some reason.
				DORMANT,	// Waiting for some external event.
				NOT_PRESENT,	// Some component (typically hardware) is missing.
				LOWER_LAYER_DOWN,	// Down due to state of lower-layer interface(s).

				Num_OperStatus_E
			};

			LeafOperStatus(uint32_t id);
			~LeafOperStatus();

		}; // LeafOperStatus

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/last-change
		// Description: The time the interface entered its current operational
		//              state.  If the current state was entered prior to the
		//              last re-initialization of the local network management
		//              subsystem, then this node is not present.
		// -----------------------------------------------------------------------------
		class LeafLastChange : public YangLeaf
		{
		public:

			LeafLastChange(uint32_t id);
			~LeafLastChange();

		}; // LeafLastChange

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/if-index
		// Description: The ifIndex value for the ifEntry represented by this
		//              interface.
		// -----------------------------------------------------------------------------
		class LeafIfIndex : public YangLeaf
		{
		public:

			LeafIfIndex(uint32_t id);
			~LeafIfIndex();

		}; // LeafIfIndex

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
		class LeafPhysAddress : public YangLeaf
		{
		public:

			LeafPhysAddress(uint32_t id);
			~LeafPhysAddress();

		}; // LeafPhysAddress

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/speed
		// Description: An estimate of the interface's current bandwidth in bits
		//              per second.  For interfaces that do not vary in
		//              bandwidth or for those where no accurate estimation can
		//              be made, this node should contain the nominal bandwidth.
		//              For interfaces that have no concept of bandwidth, this
		//              node is not present.
		// -----------------------------------------------------------------------------
		class LeafSpeed : public YangLeaf
		{
		public:

			LeafSpeed(uint32_t id);
			~LeafSpeed();

		}; // LeafSpeed

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/l2-mtu
		// Description: The maximum size of layer 2 frames that may be transmitted
		//              or received on the interface (excluding any FCS overhead).
		//              For Ethernet interfaces it also excludes the
		//              4-8 byte overhead of any known (i.e. explicitly matched by
		//              a child sub-interface) 801.1Q VLAN tags.
		// -----------------------------------------------------------------------------
		class LeafL2Mtu : public YangLeaf
		{
		public:

			LeafL2Mtu(uint32_t id);
			~LeafL2Mtu();

		}; // LeafL2Mtu

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/vlan-tagging
		// Description: Indicates if VLAN tagging is used.
		//              Default true is used to enable equipment to auonomously discover that it is
		//              connected to a trunk port.
		// -----------------------------------------------------------------------------
		class LeafVlanTagging : public YangLeaf
		{
		public:

			LeafVlanTagging(uint32_t id);
			~LeafVlanTagging();

		}; // LeafVlanTagging

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/vlan-id
		// Description: The VLAN-ID.
		// -----------------------------------------------------------------------------
		class LeafVlanId : public YangLeaf
		{
		public:

			LeafVlanId(uint32_t id);
			~LeafVlanId();

		}; // LeafVlanId

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/last-cleared
		// Description: Timestamp of the last time the interface counters were
		//              cleared.
		// -----------------------------------------------------------------------------
		class LeafLastCleared : public YangLeaf
		{
		public:

			LeafLastCleared(uint32_t id);
			~LeafLastCleared();

		}; // LeafLastCleared

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces/interface/mac-address
		// Description: The MAC address of the interface.
		// -----------------------------------------------------------------------------
		class LeafMacAddress : public YangLeaf
		{
		public:

			LeafMacAddress(uint32_t id);
			~LeafMacAddress();

		}; // LeafMacAddress

		// -----------------------------------------------------------------------------
		// Reference:   /interfaces/interface/base-interface
		// Description: The base interface for the VLAN sub-interafce.
		// -----------------------------------------------------------------------------
		class RefBaseInterface : public YangReference
		{
		public:

			RefBaseInterface(uint32_t id);
			~RefBaseInterface();

		}; // RefBaseInterface

		// -----------------------------------------------------------------------------
		// Container:   /interfaces/interface/statistics
		// Description: A collection of interface-related statistics objects.
		// -----------------------------------------------------------------------------
		class CntStatistics : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DISCONTINUITY_TIME,  // LeafDiscontinuityTime
				ITEM_IN_OCTETS,  // LeafInOctets
				ITEM_IN_UNICAST_PKTS,  // LeafInUnicastPkts
				ITEM_IN_BROADCAST_PKTS,  // LeafInBroadcastPkts
				ITEM_IN_MULTICAST_PKTS,  // LeafInMulticastPkts
				ITEM_IN_DISCARDS,  // LeafInDiscards
				ITEM_IN_ERRORS,  // LeafInErrors
				ITEM_IN_UNKNOWN_PROTOS,  // LeafInUnknownProtos
				ITEM_OUT_OCTETS,  // LeafOutOctets
				ITEM_OUT_UNICAST_PKTS,  // LeafOutUnicastPkts
				ITEM_OUT_BROADCAST_PKTS,  // LeafOutBroadcastPkts
				ITEM_OUT_MULTICAST_PKTS,  // LeafOutMulticastPkts
				ITEM_OUT_DISCARDS,  // LeafOutDiscards
				ITEM_OUT_ERRORS,  // LeafOutErrors
			};

			CntStatistics(uint32_t id);
			~CntStatistics();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/statistics/discontinuity-time
			// Description: The time on the most recent occasion at which any one or
			//              more of this interface's counters suffered a
			//              discontinuity.  If no such discontinuities have occurred
			//              since the last re-initialization of the local management
			//              subsystem, then this node contains the time the local
			//              management subsystem re-initialized itself.
			// -----------------------------------------------------------------------------
			class LeafDiscontinuityTime : public YangLeaf
			{
			public:

				LeafDiscontinuityTime(uint32_t id);
				~LeafDiscontinuityTime();

			}; // LeafDiscontinuityTime

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/statistics/in-octets
			// Description: The total number of octets received on the interface,
			//              including framing characters.
			//              Discontinuities in the value of this counter can occur
			//              at re-initialization of the management system and at
			//              other times as indicated by the value of
			//              'discontinuity-time'.
			// -----------------------------------------------------------------------------
			class LeafInOctets : public YangLeaf
			{
			public:

				LeafInOctets(uint32_t id);
				~LeafInOctets();

			}; // LeafInOctets

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
			class LeafInUnicastPkts : public YangLeaf
			{
			public:

				LeafInUnicastPkts(uint32_t id);
				~LeafInUnicastPkts();

			}; // LeafInUnicastPkts

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
			class LeafInBroadcastPkts : public YangLeaf
			{
			public:

				LeafInBroadcastPkts(uint32_t id);
				~LeafInBroadcastPkts();

			}; // LeafInBroadcastPkts

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
			class LeafInMulticastPkts : public YangLeaf
			{
			public:

				LeafInMulticastPkts(uint32_t id);
				~LeafInMulticastPkts();

			}; // LeafInMulticastPkts

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
			class LeafInDiscards : public YangLeaf
			{
			public:

				LeafInDiscards(uint32_t id);
				~LeafInDiscards();

			}; // LeafInDiscards

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
			class LeafInErrors : public YangLeaf
			{
			public:

				LeafInErrors(uint32_t id);
				~LeafInErrors();

			}; // LeafInErrors

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
			class LeafInUnknownProtos : public YangLeaf
			{
			public:

				LeafInUnknownProtos(uint32_t id);
				~LeafInUnknownProtos();

			}; // LeafInUnknownProtos

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/statistics/out-octets
			// Description: The total number of octets transmitted out of the
			//              interface, including framing characters.
			//              Discontinuities in the value of this counter can occur
			//              at re-initialization of the management system and at
			//              other times as indicated by the value of
			//              'discontinuity-time'.
			// -----------------------------------------------------------------------------
			class LeafOutOctets : public YangLeaf
			{
			public:

				LeafOutOctets(uint32_t id);
				~LeafOutOctets();

			}; // LeafOutOctets

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
			class LeafOutUnicastPkts : public YangLeaf
			{
			public:

				LeafOutUnicastPkts(uint32_t id);
				~LeafOutUnicastPkts();

			}; // LeafOutUnicastPkts

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
			class LeafOutBroadcastPkts : public YangLeaf
			{
			public:

				LeafOutBroadcastPkts(uint32_t id);
				~LeafOutBroadcastPkts();

			}; // LeafOutBroadcastPkts

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
			class LeafOutMulticastPkts : public YangLeaf
			{
			public:

				LeafOutMulticastPkts(uint32_t id);
				~LeafOutMulticastPkts();

			}; // LeafOutMulticastPkts

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
			class LeafOutDiscards : public YangLeaf
			{
			public:

				LeafOutDiscards(uint32_t id);
				~LeafOutDiscards();

			}; // LeafOutDiscards

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
			class LeafOutErrors : public YangLeaf
			{
			public:

				LeafOutErrors(uint32_t id);
				~LeafOutErrors();

			}; // LeafOutErrors

		}; // CntStatistics

		// -----------------------------------------------------------------------------
		// Container:   /interfaces/interface/ipv4
		// Description: Parameters for the IPv4 address family.
		// -----------------------------------------------------------------------------
		class CntIpv4 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_ENABLED,  // LeafEnabled
				ITEM_FORWARDING,  // LeafForwarding
				ITEM_MTU,  // LeafMtu
				ITEM_M_PLANE_MARKING,  // LeafMPlaneMarking
				ITEM_ADDRESS,  // LstAddress
				ITEM_NEIGHBOR,  // LstNeighbor
				ITEM_DSCP_MARKING,  // Use GrpDscpMarking
			};

			CntIpv4(uint32_t id);
			~CntIpv4();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv4/enabled
			// Description: Controls whether IPv4 is enabled or disabled on this
			//              interface.  When IPv4 is enabled, this interface is
			//              connected to an IPv4 stack, and the interface can send
			//              and receive IPv4 packets.
			// -----------------------------------------------------------------------------
			class LeafEnabled : public YangLeaf
			{
			public:

				LeafEnabled(uint32_t id);
				~LeafEnabled();

			}; // LeafEnabled

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv4/forwarding
			// Description: Controls IPv4 packet forwarding of datagrams received by,
			//              but not addressed to, this interface.  IPv4 routers
			//              forward datagrams.  IPv4 hosts do not (except those
			//              source-routed via the host).
			// -----------------------------------------------------------------------------
			class LeafForwarding : public YangLeaf
			{
			public:

				LeafForwarding(uint32_t id);
				~LeafForwarding();

			}; // LeafForwarding

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv4/mtu
			// Description: The size, in octets, of the largest IPv4 packet that the
			//              interface will send and receive.
			//              The server may restrict the allowed values for this leaf,
			//              depending on the interface's type.
			//              If this leaf is not configured, the operationally used MTU
			//              depends on the interface's type.
			// -----------------------------------------------------------------------------
			class LeafMtu : public YangLeaf
			{
			public:

				LeafMtu(uint32_t id);
				~LeafMtu();

			}; // LeafMtu

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv4/m-plane-marking
			// Description: 18 represents AF21 or 'immediate traffic'
			// -----------------------------------------------------------------------------
			class LeafMPlaneMarking : public YangLeaf
			{
			public:

				LeafMPlaneMarking(uint32_t id);
				~LeafMPlaneMarking();

			}; // LeafMPlaneMarking

			// -----------------------------------------------------------------------------
			// List:        /interfaces/interface/ipv4/address
			// Description: The list of IPv4 addresses on the interface.
			// -----------------------------------------------------------------------------
			class LstAddress : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_SUBNET,  // ChoiceSubnet
				};

				LstAddress(uint32_t id);
				~LstAddress();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv4/address/ip
				// Description: The IPv4 address on the interface.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv4/address/origin
				// Description: The origin of this address.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this address.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Choice:      /interfaces/interface/ipv4/address/subnet
				// Description: The subnet can be specified as a prefix length or,
				//              if the server supports non-contiguous netmasks, as
				//              a netmask.
				// -----------------------------------------------------------------------------
				class ChoiceSubnet : public YangChoice
				{
				public:
					// Choice Option
					enum : uint32_t
					{
						ITEM_PREFIX_LENGTH,  // OptPrefixLength
						ITEM_NETMASK,  // OptNetmask
					};

					ChoiceSubnet(uint32_t id);
					~ChoiceSubnet();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Option: /interfaces/interface/ipv4/address/subnet[prefix-length]
					// -----------------------------------------------------------------------------
					class OptPrefixLength : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_PREFIX_LENGTH,  // LeafPrefixLength
						};

						OptPrefixLength(uint32_t id);
						~OptPrefixLength();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Leaf:        /interfaces/interface/ipv4/address/subnet[prefix-length]/prefix-length
						// Description: The length of the subnet prefix.
						// -----------------------------------------------------------------------------
						class LeafPrefixLength : public YangLeaf
						{
						public:

							LeafPrefixLength(uint32_t id);
							~LeafPrefixLength();

						}; // LeafPrefixLength

					}; // OptPrefixLength


					// -----------------------------------------------------------------------------
					// Option: /interfaces/interface/ipv4/address/subnet[netmask]
					// -----------------------------------------------------------------------------
					class OptNetmask : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_NETMASK,  // LeafNetmask
						};

						OptNetmask(uint32_t id);
						~OptNetmask();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Leaf:        /interfaces/interface/ipv4/address/subnet[netmask]/netmask
						// Description: The subnet specified as a netmask.
						// -----------------------------------------------------------------------------
						class LeafNetmask : public YangLeaf
						{
						public:

							LeafNetmask(uint32_t id);
							~LeafNetmask();

						}; // LeafNetmask

					}; // OptNetmask

				}; // ChoiceSubnet

			}; // LstAddress

			// -----------------------------------------------------------------------------
			// List:        /interfaces/interface/ipv4/neighbor
			// Description: A list of mappings from IPv4 addresses to
			//              link-layer addresses.
			//              Entries in this list in the intended configuration are
			//              used as static entries in the ARP Cache.
			//              In the operational state, this list represents the ARP
			//              Cache.
			// -----------------------------------------------------------------------------
			class LstNeighbor : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_LINK_LAYER_ADDRESS,  // LeafLinkLayerAddress
					ITEM_ORIGIN,  // LeafOrigin
				};

				LstNeighbor(uint32_t id);
				~LstNeighbor();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv4/neighbor/ip
				// Description: The IPv4 address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv4/neighbor/link-layer-address
				// Description: The link-layer address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafLinkLayerAddress : public YangLeaf
				{
				public:

					LeafLinkLayerAddress(uint32_t id);
					~LeafLinkLayerAddress();

				}; // LeafLinkLayerAddress

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv4/neighbor/origin
				// Description: The origin of this neighbor entry.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this neighbor entry.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

			}; // LstNeighbor

		}; // CntIpv4

		// -----------------------------------------------------------------------------
		// Container:   /interfaces/interface/ipv6
		// Description: Parameters for the IPv6 address family.
		// -----------------------------------------------------------------------------
		class CntIpv6 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_ENABLED,  // LeafEnabled
				ITEM_FORWARDING,  // LeafForwarding
				ITEM_MTU,  // LeafMtu
				ITEM_DUP_ADDR_DETECT_TRANSMITS,  // LeafDupAddrDetectTransmits
				ITEM_M_PLANE_MARKING,  // LeafMPlaneMarking
				ITEM_AUTOCONF,  // CntAutoconf
				ITEM_ADDRESS,  // LstAddress
				ITEM_NEIGHBOR,  // LstNeighbor
				ITEM_DSCP_MARKING,  // Use GrpDscpMarking
			};

			CntIpv6(uint32_t id);
			~CntIpv6();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv6/enabled
			// Description: Controls whether IPv6 is enabled or disabled on this
			//              interface.  When IPv6 is enabled, this interface is
			//              connected to an IPv6 stack, and the interface can send
			//              and receive IPv6 packets.
			// -----------------------------------------------------------------------------
			class LeafEnabled : public YangLeaf
			{
			public:

				LeafEnabled(uint32_t id);
				~LeafEnabled();

			}; // LeafEnabled

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv6/forwarding
			// Description: Controls IPv6 packet forwarding of datagrams received by,
			//              but not addressed to, this interface.  IPv6 routers
			//              forward datagrams.  IPv6 hosts do not (except those
			//              source-routed via the host).
			// -----------------------------------------------------------------------------
			class LeafForwarding : public YangLeaf
			{
			public:

				LeafForwarding(uint32_t id);
				~LeafForwarding();

			}; // LeafForwarding

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv6/mtu
			// Description: The size, in octets, of the largest IPv6 packet that the
			//              interface will send and receive.
			//              The server may restrict the allowed values for this leaf,
			//              depending on the interface's type.
			//              If this leaf is not configured, the operationally used MTU
			//              depends on the interface's type.
			// -----------------------------------------------------------------------------
			class LeafMtu : public YangLeaf
			{
			public:

				LeafMtu(uint32_t id);
				~LeafMtu();

			}; // LeafMtu

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv6/dup-addr-detect-transmits
			// Description: The number of consecutive Neighbor Solicitation messages
			//              sent while performing Duplicate Address Detection on a
			//              tentative address.  A value of zero indicates that
			//              Duplicate Address Detection is not performed on
			//              tentative addresses.  A value of one indicates a single
			//              transmission with no follow-up retransmissions.
			// -----------------------------------------------------------------------------
			class LeafDupAddrDetectTransmits : public YangLeaf
			{
			public:

				LeafDupAddrDetectTransmits(uint32_t id);
				~LeafDupAddrDetectTransmits();

			}; // LeafDupAddrDetectTransmits

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/ipv6/m-plane-marking
			// Description: 18 represents AF21 or 'immediate traffic'
			// -----------------------------------------------------------------------------
			class LeafMPlaneMarking : public YangLeaf
			{
			public:

				LeafMPlaneMarking(uint32_t id);
				~LeafMPlaneMarking();

			}; // LeafMPlaneMarking

			// -----------------------------------------------------------------------------
			// Container:   /interfaces/interface/ipv6/autoconf
			// Description: Parameters to control the autoconfiguration of IPv6
			//              addresses, as described in RFC 4862.
			// -----------------------------------------------------------------------------
			class CntAutoconf : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_CREATE_GLOBAL_ADDRESSES,  // LeafCreateGlobalAddresses
					ITEM_CREATE_TEMPORARY_ADDRESSES,  // LeafCreateTemporaryAddresses
					ITEM_TEMPORARY_VALID_LIFETIME,  // LeafTemporaryValidLifetime
					ITEM_TEMPORARY_PREFERRED_LIFETIME,  // LeafTemporaryPreferredLifetime
				};

				CntAutoconf(uint32_t id);
				~CntAutoconf();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/autoconf/create-global-addresses
				// Description: If enabled, the host creates global addresses as
				//              described in RFC 4862.
				// -----------------------------------------------------------------------------
				class LeafCreateGlobalAddresses : public YangLeaf
				{
				public:

					LeafCreateGlobalAddresses(uint32_t id);
					~LeafCreateGlobalAddresses();

				}; // LeafCreateGlobalAddresses

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/autoconf/create-temporary-addresses
				// Description: If enabled, the host creates temporary addresses as
				//              described in RFC 4941.
				// -----------------------------------------------------------------------------
				class LeafCreateTemporaryAddresses : public YangLeaf
				{
				public:

					LeafCreateTemporaryAddresses(uint32_t id);
					~LeafCreateTemporaryAddresses();

				}; // LeafCreateTemporaryAddresses

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-valid-lifetime
				// Description: The time period during which the temporary address
				//              is valid.
				// -----------------------------------------------------------------------------
				class LeafTemporaryValidLifetime : public YangLeaf
				{
				public:

					LeafTemporaryValidLifetime(uint32_t id);
					~LeafTemporaryValidLifetime();

				}; // LeafTemporaryValidLifetime

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/autoconf/temporary-preferred-lifetime
				// Description: The time period during which the temporary address is
				//              preferred.
				// -----------------------------------------------------------------------------
				class LeafTemporaryPreferredLifetime : public YangLeaf
				{
				public:

					LeafTemporaryPreferredLifetime(uint32_t id);
					~LeafTemporaryPreferredLifetime();

				}; // LeafTemporaryPreferredLifetime

			}; // CntAutoconf

			// -----------------------------------------------------------------------------
			// List:        /interfaces/interface/ipv6/address
			// Description: The list of IPv6 addresses on the interface.
			// -----------------------------------------------------------------------------
			class LstAddress : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_PREFIX_LENGTH,  // LeafPrefixLength
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_STATUS,  // LeafStatus
				};

				LstAddress(uint32_t id);
				~LstAddress();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/address/ip
				// Description: The IPv6 address on the interface.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/address/prefix-length
				// Description: The length of the subnet prefix.
				// -----------------------------------------------------------------------------
				class LeafPrefixLength : public YangLeaf
				{
				public:

					LeafPrefixLength(uint32_t id);
					~LeafPrefixLength();

				}; // LeafPrefixLength

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/address/origin
				// Description: The origin of this address.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this address.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/address/status
				// Description: The status of an address.  Most of the states correspond
				//              to states from the IPv6 Stateless Address
				//              Autoconfiguration protocol.
				// -----------------------------------------------------------------------------
				class LeafStatus : public YangLeaf
				{
				public:

					// The status of an address.  Most of the states correspond
					// to states from the IPv6 Stateless Address
					// Autoconfiguration protocol.
					enum class Status_E : uint32_t
					{
						PREFERRED,	// This is a valid address that can appear as the
								// destination or source address of a packet.
						DEPRECATED,	// This is a valid but deprecated address that should
								// no longer be used as a source address in new
								// communications, but packets addressed to such an
								// address are processed as expected.
						INVALID,	// This isn't a valid address, and it shouldn't appear
								// as the destination or source address of a packet.
						INACCESSIBLE,	// The address is not accessible because the interface
								// to which this address is assigned is not
								// operational.
						UNKNOWN,	// The status cannot be determined for some reason.
						TENTATIVE,	// The uniqueness of the address on the link is being
								// verified.  Addresses in this state should not be
								// used for general communication and should only be
								// used to determine the uniqueness of the address.
						DUPLICATE,	// The address has been determined to be non-unique on
								// the link and so must not be used.
						OPTIMISTIC,	// The address is available for use, subject to
								// restrictions, while its uniqueness on a link is
								// being verified.

						Num_Status_E
					};

					LeafStatus(uint32_t id);
					~LeafStatus();

				}; // LeafStatus

			}; // LstAddress

			// -----------------------------------------------------------------------------
			// List:        /interfaces/interface/ipv6/neighbor
			// Description: A list of mappings from IPv6 addresses to
			//              link-layer addresses.
			//              Entries in this list in the intended configuration are
			//              used as static entries in the Neighbor Cache.
			//              In the operational state, this list represents the
			//              Neighbor Cache.
			// -----------------------------------------------------------------------------
			class LstNeighbor : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_LINK_LAYER_ADDRESS,  // LeafLinkLayerAddress
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_IS_ROUTER,  // LeafIsRouter
					ITEM_STATE,  // LeafState
				};

				LstNeighbor(uint32_t id);
				~LstNeighbor();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/neighbor/ip
				// Description: The IPv6 address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/neighbor/link-layer-address
				// Description: The link-layer address of the neighbor node.
				//              In the operational state, if the neighbor's 'state' leaf
				//              is 'incomplete', this leaf is not instantiated.
				// -----------------------------------------------------------------------------
				class LeafLinkLayerAddress : public YangLeaf
				{
				public:

					LeafLinkLayerAddress(uint32_t id);
					~LeafLinkLayerAddress();

				}; // LeafLinkLayerAddress

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/neighbor/origin
				// Description: The origin of this neighbor entry.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this neighbor entry.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/neighbor/is-router
				// Description: Indicates that the neighbor node acts as a router.
				// -----------------------------------------------------------------------------
				class LeafIsRouter : public YangLeaf
				{
				public:

					LeafIsRouter(uint32_t id);
					~LeafIsRouter();

				}; // LeafIsRouter

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces/interface/ipv6/neighbor/state
				// Description: The Neighbor Unreachability Detection state of this
				//              entry.
				// -----------------------------------------------------------------------------
				class LeafState : public YangLeaf
				{
				public:

					// The Neighbor Unreachability Detection state of this
					// entry.
					enum class State_E : uint32_t
					{
						INCOMPLETE,	// Address resolution is in progress, and the
								// link-layer address of the neighbor has not yet been
								// determined.
						REACHABLE,	// Roughly speaking, the neighbor is known to have been
								// reachable recently (within tens of seconds ago).
						STALE,	// The neighbor is no longer known to be reachable, but
								// until traffic is sent to the neighbor no attempt
								// should be made to verify its reachability.
						DELAY,	// The neighbor is no longer known to be reachable, and
								// traffic has recently been sent to the neighbor.
								// Rather than probe the neighbor immediately, however,
								// delay sending probes for a short while in order to
								// give upper-layer protocols a chance to provide
								// reachability confirmation.
						PROBE,	// The neighbor is no longer known to be reachable, and
								// unicast Neighbor Solicitation probes are being sent
								// to verify reachability.

						Num_State_E
					};

					LeafState(uint32_t id);
					~LeafState();

				}; // LeafState

			}; // LstNeighbor

		}; // CntIpv6

		// -----------------------------------------------------------------------------
		// Container:   /interfaces/interface/port-reference
		// Description: a port reference used by other O-RAN modules
		// -----------------------------------------------------------------------------
		class CntPortReference : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_PORT_NUMBER,  // LeafPortNumber
				ITEM_PORT_NAME,  // RefPortName
			};

			CntPortReference(uint32_t id);
			~CntPortReference();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces/interface/port-reference/port-number
			// Description: A number allocated by the server which identifies a port.
			//              Port number value is 0 to N-1 where N is number of ports
			//              in the device.
			//
			//              This value is fixed for the lifetime of the equipment, i.e., cannot be
			//              changed during equipment reboots.
			// -----------------------------------------------------------------------------
			class LeafPortNumber : public YangLeaf
			{
			public:

				LeafPortNumber(uint32_t id);
				~LeafPortNumber();

			}; // LeafPortNumber

			// -----------------------------------------------------------------------------
			// Reference:   /interfaces/interface/port-reference/port-name
			// Description: O-RAN interfaces use a reference to a physical port component.
			//
			//              In this case, the component name referenced must be of class type
			//              port, i.e., when /hw:hardware/hw:component/hw:class is derived from
			//              ianahw:port
			// -----------------------------------------------------------------------------
			class RefPortName : public YangReference
			{
			public:

				RefPortName(uint32_t id);
				~RefPortName();

			}; // RefPortName

		}; // CntPortReference

		// -----------------------------------------------------------------------------
		// List:        /interfaces/interface/higher-layer-if
		// Description: A list of references to interfaces layered on top of this
		//              interface.
		// -----------------------------------------------------------------------------
		class LstHigherLayerIf : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstHigherLayerIf(uint32_t id);
			~LstHigherLayerIf();

			YangResult_E initialise(void);

		}; // LstHigherLayerIf

		// -----------------------------------------------------------------------------
		// List:        /interfaces/interface/lower-layer-if
		// Description: A list of references to interfaces layered underneath this
		//              interface.
		// -----------------------------------------------------------------------------
		class LstLowerLayerIf : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstLowerLayerIf(uint32_t id);
			~LstLowerLayerIf();

			YangResult_E initialise(void);

		}; // LstLowerLayerIf

		// -----------------------------------------------------------------------------
		// List:        /interfaces/interface/alias-macs
		// Description: Augments interfaces with range of alias MAC addresses.
		// -----------------------------------------------------------------------------
		class LstAliasMacs : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstAliasMacs(uint32_t id);
			~LstAliasMacs();

			YangResult_E initialise(void);

		}; // LstAliasMacs

	}; // LstInterface

}; // CntInterfaces

// -----------------------------------------------------------------------------
// Container:   /interfaces-state
// Description: Data nodes for the operational state of interfaces.
// -----------------------------------------------------------------------------
class CntInterfacesState : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_INTERFACE,  // LstInterface
	};

	CntInterfacesState(uint32_t id);
	~CntInterfacesState();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /interfaces-state/interface
	// Description: The list of interfaces on the device.
	//              System-controlled interfaces created by the system are
	//              always present in this list, whether or not they are
	//              configured.
	// -----------------------------------------------------------------------------
	class LstInterface : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_TYPE,  // LeafType
			ITEM_ADMIN_STATUS,  // LeafAdminStatus
			ITEM_OPER_STATUS,  // LeafOperStatus
			ITEM_LAST_CHANGE,  // LeafLastChange
			ITEM_IF_INDEX,  // LeafIfIndex
			ITEM_PHYS_ADDRESS,  // LeafPhysAddress
			ITEM_SPEED,  // LeafSpeed
			ITEM_STATISTICS,  // CntStatistics
			ITEM_IPV4,  // CntIpv4
			ITEM_IPV6,  // CntIpv6
			ITEM_HIGHER_LAYER_IF,  // LstHigherLayerIf
			ITEM_LOWER_LAYER_IF,  // LstLowerLayerIf
		};

		LstInterface(uint32_t id);
		~LstInterface();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/name
		// Description: The name of the interface.
		//              A server implementation MAY map this leaf to the ifName
		//              MIB object.  Such an implementation needs to use some
		//              mechanism to handle the differences in size and characters
		//              allowed between this leaf and ifName.  The definition of
		//              such a mechanism is outside the scope of this document.
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/type
		// Description: The type of the interface.
		// -----------------------------------------------------------------------------
		class LeafType : public YangLeaf
		{
		public:

			LeafType(uint32_t id);
			~LeafType();

		}; // LeafType

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/admin-status
		// Description: The desired state of the interface.
		//              This leaf has the same read semantics as ifAdminStatus.
		// -----------------------------------------------------------------------------
		class LeafAdminStatus : public YangLeaf
		{
		public:

			// The desired state of the interface.
			// This leaf has the same read semantics as ifAdminStatus.
			enum class AdminStatus_E : uint32_t
			{
				UP,	// Ready to pass packets.
				DOWN,	// Not ready to pass packets and not in some test mode.
				TESTING,	// In some test mode.

				Num_AdminStatus_E
			};

			LeafAdminStatus(uint32_t id);
			~LeafAdminStatus();

		}; // LeafAdminStatus

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/oper-status
		// Description: The current operational state of the interface.
		//              This leaf has the same semantics as ifOperStatus.
		// -----------------------------------------------------------------------------
		class LeafOperStatus : public YangLeaf
		{
		public:

			// The current operational state of the interface.
			// This leaf has the same semantics as ifOperStatus.
			enum class OperStatus_E : uint32_t
			{
				UP,	// Ready to pass packets.
				DOWN,	// The interface does not pass any packets.
				TESTING,	// In some test mode.  No operational packets can
						// be passed.
				UNKNOWN,	// Status cannot be determined for some reason.
				DORMANT,	// Waiting for some external event.
				NOT_PRESENT,	// Some component (typically hardware) is missing.
				LOWER_LAYER_DOWN,	// Down due to state of lower-layer interface(s).

				Num_OperStatus_E
			};

			LeafOperStatus(uint32_t id);
			~LeafOperStatus();

		}; // LeafOperStatus

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/last-change
		// Description: The time the interface entered its current operational
		//              state.  If the current state was entered prior to the
		//              last re-initialization of the local network management
		//              subsystem, then this node is not present.
		// -----------------------------------------------------------------------------
		class LeafLastChange : public YangLeaf
		{
		public:

			LeafLastChange(uint32_t id);
			~LeafLastChange();

		}; // LeafLastChange

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/if-index
		// Description: The ifIndex value for the ifEntry represented by this
		//              interface.
		// -----------------------------------------------------------------------------
		class LeafIfIndex : public YangLeaf
		{
		public:

			LeafIfIndex(uint32_t id);
			~LeafIfIndex();

		}; // LeafIfIndex

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
		class LeafPhysAddress : public YangLeaf
		{
		public:

			LeafPhysAddress(uint32_t id);
			~LeafPhysAddress();

		}; // LeafPhysAddress

		// -----------------------------------------------------------------------------
		// Leaf:        /interfaces-state/interface/speed
		// Description: An estimate of the interface's current bandwidth in bits
		//              per second.  For interfaces that do not vary in
		//              bandwidth or for those where no accurate estimation can
		//              be made, this node should contain the nominal bandwidth.
		//              For interfaces that have no concept of bandwidth, this
		//              node is not present.
		// -----------------------------------------------------------------------------
		class LeafSpeed : public YangLeaf
		{
		public:

			LeafSpeed(uint32_t id);
			~LeafSpeed();

		}; // LeafSpeed

		// -----------------------------------------------------------------------------
		// Container:   /interfaces-state/interface/statistics
		// Description: A collection of interface-related statistics objects.
		// -----------------------------------------------------------------------------
		class CntStatistics : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DISCONTINUITY_TIME,  // LeafDiscontinuityTime
				ITEM_IN_OCTETS,  // LeafInOctets
				ITEM_IN_UNICAST_PKTS,  // LeafInUnicastPkts
				ITEM_IN_BROADCAST_PKTS,  // LeafInBroadcastPkts
				ITEM_IN_MULTICAST_PKTS,  // LeafInMulticastPkts
				ITEM_IN_DISCARDS,  // LeafInDiscards
				ITEM_IN_ERRORS,  // LeafInErrors
				ITEM_IN_UNKNOWN_PROTOS,  // LeafInUnknownProtos
				ITEM_OUT_OCTETS,  // LeafOutOctets
				ITEM_OUT_UNICAST_PKTS,  // LeafOutUnicastPkts
				ITEM_OUT_BROADCAST_PKTS,  // LeafOutBroadcastPkts
				ITEM_OUT_MULTICAST_PKTS,  // LeafOutMulticastPkts
				ITEM_OUT_DISCARDS,  // LeafOutDiscards
				ITEM_OUT_ERRORS,  // LeafOutErrors
			};

			CntStatistics(uint32_t id);
			~CntStatistics();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/statistics/discontinuity-time
			// Description: The time on the most recent occasion at which any one or
			//              more of this interface's counters suffered a
			//              discontinuity.  If no such discontinuities have occurred
			//              since the last re-initialization of the local management
			//              subsystem, then this node contains the time the local
			//              management subsystem re-initialized itself.
			// -----------------------------------------------------------------------------
			class LeafDiscontinuityTime : public YangLeaf
			{
			public:

				LeafDiscontinuityTime(uint32_t id);
				~LeafDiscontinuityTime();

			}; // LeafDiscontinuityTime

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/statistics/in-octets
			// Description: The total number of octets received on the interface,
			//              including framing characters.
			//              Discontinuities in the value of this counter can occur
			//              at re-initialization of the management system and at
			//              other times as indicated by the value of
			//              'discontinuity-time'.
			// -----------------------------------------------------------------------------
			class LeafInOctets : public YangLeaf
			{
			public:

				LeafInOctets(uint32_t id);
				~LeafInOctets();

			}; // LeafInOctets

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
			class LeafInUnicastPkts : public YangLeaf
			{
			public:

				LeafInUnicastPkts(uint32_t id);
				~LeafInUnicastPkts();

			}; // LeafInUnicastPkts

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
			class LeafInBroadcastPkts : public YangLeaf
			{
			public:

				LeafInBroadcastPkts(uint32_t id);
				~LeafInBroadcastPkts();

			}; // LeafInBroadcastPkts

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
			class LeafInMulticastPkts : public YangLeaf
			{
			public:

				LeafInMulticastPkts(uint32_t id);
				~LeafInMulticastPkts();

			}; // LeafInMulticastPkts

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
			class LeafInDiscards : public YangLeaf
			{
			public:

				LeafInDiscards(uint32_t id);
				~LeafInDiscards();

			}; // LeafInDiscards

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
			class LeafInErrors : public YangLeaf
			{
			public:

				LeafInErrors(uint32_t id);
				~LeafInErrors();

			}; // LeafInErrors

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
			class LeafInUnknownProtos : public YangLeaf
			{
			public:

				LeafInUnknownProtos(uint32_t id);
				~LeafInUnknownProtos();

			}; // LeafInUnknownProtos

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/statistics/out-octets
			// Description: The total number of octets transmitted out of the
			//              interface, including framing characters.
			//              Discontinuities in the value of this counter can occur
			//              at re-initialization of the management system and at
			//              other times as indicated by the value of
			//              'discontinuity-time'.
			// -----------------------------------------------------------------------------
			class LeafOutOctets : public YangLeaf
			{
			public:

				LeafOutOctets(uint32_t id);
				~LeafOutOctets();

			}; // LeafOutOctets

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
			class LeafOutUnicastPkts : public YangLeaf
			{
			public:

				LeafOutUnicastPkts(uint32_t id);
				~LeafOutUnicastPkts();

			}; // LeafOutUnicastPkts

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
			class LeafOutBroadcastPkts : public YangLeaf
			{
			public:

				LeafOutBroadcastPkts(uint32_t id);
				~LeafOutBroadcastPkts();

			}; // LeafOutBroadcastPkts

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
			class LeafOutMulticastPkts : public YangLeaf
			{
			public:

				LeafOutMulticastPkts(uint32_t id);
				~LeafOutMulticastPkts();

			}; // LeafOutMulticastPkts

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
			class LeafOutDiscards : public YangLeaf
			{
			public:

				LeafOutDiscards(uint32_t id);
				~LeafOutDiscards();

			}; // LeafOutDiscards

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
			class LeafOutErrors : public YangLeaf
			{
			public:

				LeafOutErrors(uint32_t id);
				~LeafOutErrors();

			}; // LeafOutErrors

		}; // CntStatistics

		// -----------------------------------------------------------------------------
		// Container:   /interfaces-state/interface/ipv4
		// Description: Interface-specific parameters for the IPv4 address family.
		// -----------------------------------------------------------------------------
		class CntIpv4 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_FORWARDING,  // LeafForwarding
				ITEM_MTU,  // LeafMtu
				ITEM_ADDRESS,  // LstAddress
				ITEM_NEIGHBOR,  // LstNeighbor
			};

			CntIpv4(uint32_t id);
			~CntIpv4();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/ipv4/forwarding
			// Description: Indicates whether IPv4 packet forwarding is enabled or
			//              disabled on this interface.
			// -----------------------------------------------------------------------------
			class LeafForwarding : public YangLeaf
			{
			public:

				LeafForwarding(uint32_t id);
				~LeafForwarding();

			}; // LeafForwarding

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/ipv4/mtu
			// Description: The size, in octets, of the largest IPv4 packet that the
			//              interface will send and receive.
			// -----------------------------------------------------------------------------
			class LeafMtu : public YangLeaf
			{
			public:

				LeafMtu(uint32_t id);
				~LeafMtu();

			}; // LeafMtu

			// -----------------------------------------------------------------------------
			// List:        /interfaces-state/interface/ipv4/address
			// Description: The list of IPv4 addresses on the interface.
			// -----------------------------------------------------------------------------
			class LstAddress : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_SUBNET,  // ChoiceSubnet
				};

				LstAddress(uint32_t id);
				~LstAddress();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv4/address/ip
				// Description: The IPv4 address on the interface.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv4/address/origin
				// Description: The origin of this address.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this address.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Choice:      /interfaces-state/interface/ipv4/address/subnet
				// Description: The subnet can be specified as a prefix length or,
				//              if the server supports non-contiguous netmasks, as
				//              a netmask.
				// -----------------------------------------------------------------------------
				class ChoiceSubnet : public YangChoice
				{
				public:
					// Choice Option
					enum : uint32_t
					{
						ITEM_PREFIX_LENGTH,  // OptPrefixLength
						ITEM_NETMASK,  // OptNetmask
					};

					ChoiceSubnet(uint32_t id);
					~ChoiceSubnet();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Option: /interfaces-state/interface/ipv4/address/subnet[prefix-length]
					// -----------------------------------------------------------------------------
					class OptPrefixLength : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_PREFIX_LENGTH,  // LeafPrefixLength
						};

						OptPrefixLength(uint32_t id);
						~OptPrefixLength();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Leaf:        /interfaces-state/interface/ipv4/address/subnet[prefix-length]/prefix-length
						// Description: The length of the subnet prefix.
						// -----------------------------------------------------------------------------
						class LeafPrefixLength : public YangLeaf
						{
						public:

							LeafPrefixLength(uint32_t id);
							~LeafPrefixLength();

						}; // LeafPrefixLength

					}; // OptPrefixLength


					// -----------------------------------------------------------------------------
					// Option: /interfaces-state/interface/ipv4/address/subnet[netmask]
					// -----------------------------------------------------------------------------
					class OptNetmask : public YangChoiceOption
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_NETMASK,  // LeafNetmask
						};

						OptNetmask(uint32_t id);
						~OptNetmask();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Leaf:        /interfaces-state/interface/ipv4/address/subnet[netmask]/netmask
						// Description: The subnet specified as a netmask.
						// -----------------------------------------------------------------------------
						class LeafNetmask : public YangLeaf
						{
						public:

							LeafNetmask(uint32_t id);
							~LeafNetmask();

						}; // LeafNetmask

					}; // OptNetmask

				}; // ChoiceSubnet

			}; // LstAddress

			// -----------------------------------------------------------------------------
			// List:        /interfaces-state/interface/ipv4/neighbor
			// Description: A list of mappings from IPv4 addresses to
			//              link-layer addresses.
			//              This list represents the ARP Cache.
			// -----------------------------------------------------------------------------
			class LstNeighbor : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_LINK_LAYER_ADDRESS,  // LeafLinkLayerAddress
					ITEM_ORIGIN,  // LeafOrigin
				};

				LstNeighbor(uint32_t id);
				~LstNeighbor();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv4/neighbor/ip
				// Description: The IPv4 address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv4/neighbor/link-layer-address
				// Description: The link-layer address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafLinkLayerAddress : public YangLeaf
				{
				public:

					LeafLinkLayerAddress(uint32_t id);
					~LeafLinkLayerAddress();

				}; // LeafLinkLayerAddress

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv4/neighbor/origin
				// Description: The origin of this neighbor entry.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this neighbor entry.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

			}; // LstNeighbor

		}; // CntIpv4

		// -----------------------------------------------------------------------------
		// Container:   /interfaces-state/interface/ipv6
		// Description: Parameters for the IPv6 address family.
		// -----------------------------------------------------------------------------
		class CntIpv6 : public YangContainer
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_FORWARDING,  // LeafForwarding
				ITEM_MTU,  // LeafMtu
				ITEM_ADDRESS,  // LstAddress
				ITEM_NEIGHBOR,  // LstNeighbor
			};

			CntIpv6(uint32_t id);
			~CntIpv6();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/ipv6/forwarding
			// Description: Indicates whether IPv6 packet forwarding is enabled or
			//              disabled on this interface.
			// -----------------------------------------------------------------------------
			class LeafForwarding : public YangLeaf
			{
			public:

				LeafForwarding(uint32_t id);
				~LeafForwarding();

			}; // LeafForwarding

			// -----------------------------------------------------------------------------
			// Leaf:        /interfaces-state/interface/ipv6/mtu
			// Description: The size, in octets, of the largest IPv6 packet that the
			//              interface will send and receive.
			// -----------------------------------------------------------------------------
			class LeafMtu : public YangLeaf
			{
			public:

				LeafMtu(uint32_t id);
				~LeafMtu();

			}; // LeafMtu

			// -----------------------------------------------------------------------------
			// List:        /interfaces-state/interface/ipv6/address
			// Description: The list of IPv6 addresses on the interface.
			// -----------------------------------------------------------------------------
			class LstAddress : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_PREFIX_LENGTH,  // LeafPrefixLength
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_STATUS,  // LeafStatus
				};

				LstAddress(uint32_t id);
				~LstAddress();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/address/ip
				// Description: The IPv6 address on the interface.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/address/prefix-length
				// Description: The length of the subnet prefix.
				// -----------------------------------------------------------------------------
				class LeafPrefixLength : public YangLeaf
				{
				public:

					LeafPrefixLength(uint32_t id);
					~LeafPrefixLength();

				}; // LeafPrefixLength

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/address/origin
				// Description: The origin of this address.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this address.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/address/status
				// Description: The status of an address.  Most of the states correspond
				//              to states from the IPv6 Stateless Address
				//              Autoconfiguration protocol.
				// -----------------------------------------------------------------------------
				class LeafStatus : public YangLeaf
				{
				public:

					// The status of an address.  Most of the states correspond
					// to states from the IPv6 Stateless Address
					// Autoconfiguration protocol.
					enum class Status_E : uint32_t
					{
						PREFERRED,	// This is a valid address that can appear as the
								// destination or source address of a packet.
						DEPRECATED,	// This is a valid but deprecated address that should
								// no longer be used as a source address in new
								// communications, but packets addressed to such an
								// address are processed as expected.
						INVALID,	// This isn't a valid address, and it shouldn't appear
								// as the destination or source address of a packet.
						INACCESSIBLE,	// The address is not accessible because the interface
								// to which this address is assigned is not
								// operational.
						UNKNOWN,	// The status cannot be determined for some reason.
						TENTATIVE,	// The uniqueness of the address on the link is being
								// verified.  Addresses in this state should not be
								// used for general communication and should only be
								// used to determine the uniqueness of the address.
						DUPLICATE,	// The address has been determined to be non-unique on
								// the link and so must not be used.
						OPTIMISTIC,	// The address is available for use, subject to
								// restrictions, while its uniqueness on a link is
								// being verified.

						Num_Status_E
					};

					LeafStatus(uint32_t id);
					~LeafStatus();

				}; // LeafStatus

			}; // LstAddress

			// -----------------------------------------------------------------------------
			// List:        /interfaces-state/interface/ipv6/neighbor
			// Description: A list of mappings from IPv6 addresses to
			//              link-layer addresses.
			//              This list represents the Neighbor Cache.
			// -----------------------------------------------------------------------------
			class LstNeighbor : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_IP,  // LeafIp
					ITEM_LINK_LAYER_ADDRESS,  // LeafLinkLayerAddress
					ITEM_ORIGIN,  // LeafOrigin
					ITEM_IS_ROUTER,  // LeafIsRouter
					ITEM_STATE,  // LeafState
				};

				LstNeighbor(uint32_t id);
				~LstNeighbor();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/neighbor/ip
				// Description: The IPv6 address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafIp : public YangLeaf
				{
				public:

					LeafIp(uint32_t id);
					~LeafIp();

				}; // LeafIp

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/neighbor/link-layer-address
				// Description: The link-layer address of the neighbor node.
				// -----------------------------------------------------------------------------
				class LeafLinkLayerAddress : public YangLeaf
				{
				public:

					LeafLinkLayerAddress(uint32_t id);
					~LeafLinkLayerAddress();

				}; // LeafLinkLayerAddress

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/neighbor/origin
				// Description: The origin of this neighbor entry.
				// -----------------------------------------------------------------------------
				class LeafOrigin : public YangLeaf
				{
				public:

					// The origin of this neighbor entry.
					enum class Origin_E : uint32_t
					{

						Num_Origin_E
					};

					LeafOrigin(uint32_t id);
					~LeafOrigin();

				}; // LeafOrigin

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/neighbor/is-router
				// Description: Indicates that the neighbor node acts as a router.
				// -----------------------------------------------------------------------------
				class LeafIsRouter : public YangLeaf
				{
				public:

					LeafIsRouter(uint32_t id);
					~LeafIsRouter();

				}; // LeafIsRouter

				// -----------------------------------------------------------------------------
				// Leaf:        /interfaces-state/interface/ipv6/neighbor/state
				// Description: The Neighbor Unreachability Detection state of this
				//              entry.
				// -----------------------------------------------------------------------------
				class LeafState : public YangLeaf
				{
				public:

					// The Neighbor Unreachability Detection state of this
					// entry.
					enum class State_E : uint32_t
					{
						INCOMPLETE,	// Address resolution is in progress, and the
								// link-layer address of the neighbor has not yet been
								// determined.
						REACHABLE,	// Roughly speaking, the neighbor is known to have been
								// reachable recently (within tens of seconds ago).
						STALE,	// The neighbor is no longer known to be reachable, but
								// until traffic is sent to the neighbor no attempt
								// should be made to verify its reachability.
						DELAY,	// The neighbor is no longer known to be reachable, and
								// traffic has recently been sent to the neighbor.
								// Rather than probe the neighbor immediately, however,
								// delay sending probes for a short while in order to
								// give upper-layer protocols a chance to provide
								// reachability confirmation.
						PROBE,	// The neighbor is no longer known to be reachable, and
								// unicast Neighbor Solicitation probes are being sent
								// to verify reachability.

						Num_State_E
					};

					LeafState(uint32_t id);
					~LeafState();

				}; // LeafState

			}; // LstNeighbor

		}; // CntIpv6

		// -----------------------------------------------------------------------------
		// List:        /interfaces-state/interface/higher-layer-if
		// Description: A list of references to interfaces layered on top of this
		//              interface.
		// -----------------------------------------------------------------------------
		class LstHigherLayerIf : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstHigherLayerIf(uint32_t id);
			~LstHigherLayerIf();

			YangResult_E initialise(void);

		}; // LstHigherLayerIf

		// -----------------------------------------------------------------------------
		// List:        /interfaces-state/interface/lower-layer-if
		// Description: A list of references to interfaces layered underneath this
		//              interface.
		// -----------------------------------------------------------------------------
		class LstLowerLayerIf : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstLowerLayerIf(uint32_t id);
			~LstLowerLayerIf();

			YangResult_E initialise(void);

		}; // LstLowerLayerIf

	}; // LstInterface

}; // CntInterfacesState


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
class ModuleIetfInterfaces : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ARBITRARY_NAMES,  // Feature
		ITEM_PRE_PROVISIONING,  // Feature
		ITEM_IF_MIB,  // Feature
		ITEM_INTERFACES,  // CntInterfaces
		ITEM_INTERFACES_STATE,  // CntInterfacesState
	};

	ModuleIetfInterfaces(uint32_t id);
	~ModuleIetfInterfaces();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfInterfaces_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_INTERFACES_H_ */
