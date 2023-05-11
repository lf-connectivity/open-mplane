#ifndef _MODULE_IETF_DHCPV6_TYPES_H_
#define _MODULE_IETF_DHCPV6_TYPES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfDhcpv6Types.h
 * \brief     Module IetfDhcpv6Types interface
 *
 *
 * \details   This file defines the YANG module ietf-dhcpv6-types interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-dhcpv6-types"
 *            YANG Filename:    "ietf-dhcpv6-types.yang"
 *            Module Prefix:    "dhcpv6-types"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-dhcpv6-types"
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

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleIetfDhcpv6Types_NS {

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /vendor-infor
// Description: Vendor information.
// -----------------------------------------------------------------------------
class GrpVendorInfor : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_VENDOR_INFO,  // CntVendorInfo
	};

	GrpVendorInfor(uint32_t id);
	~GrpVendorInfor();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /vendor-infor/vendor-info
	// Description:
	// -----------------------------------------------------------------------------
	class CntVendorInfo : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_ENT_NUM,  // LeafEntNum
			ITEM_DATA,  // LstData
		};

		CntVendorInfo(uint32_t id);
		~CntVendorInfo();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /vendor-infor/vendor-info/ent-num
		// Description: enterprise number
		// -----------------------------------------------------------------------------
		class LeafEntNum : public YangLeaf
		{
		public:

			LeafEntNum(uint32_t id);
			~LeafEntNum();

		}; // LeafEntNum

		// -----------------------------------------------------------------------------
		// List:        /vendor-infor/vendor-info/data
		// Description: specific vendor info
		// -----------------------------------------------------------------------------
		class LstData : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstData(uint32_t id);
			~LstData();

			YangResult_E initialise(void);

		}; // LstData

	}; // CntVendorInfo

}; // GrpVendorInfor

// -----------------------------------------------------------------------------
// Grouping:    /duid
// Description: Each server and client has only one DUID (DHCP Unique Identifier).
//              The DUID here identifies a unique DHCPv6 server for clients. DUID
//              consists of a two-octet type field and an arbitrary length (no more
//              than 128 bytes) content field. Currently there are four defined types
//              of DUIDs in RFC3315 and RFC6355 - DUID-LLT, DUID-EN, DUID-LL and
//              DUID-UUID. DUID-Uknown represents those unconventional DUIDs.
// -----------------------------------------------------------------------------
class GrpDuid : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_TYPE_CODE,  // LeafTypeCode
		ITEM_DUID_TYPE,  // ChoiceDuidType
	};

	GrpDuid(uint32_t id);
	~GrpDuid();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /duid/type-code
	// Description: Type code of this DUID
	// -----------------------------------------------------------------------------
	class LeafTypeCode : public YangLeaf
	{
	public:

		LeafTypeCode(uint32_t id);
		~LeafTypeCode();

	}; // LeafTypeCode

	// -----------------------------------------------------------------------------
	// Choice:      /duid/duid-type
	// Description: Selects the format for the DUID.
	// -----------------------------------------------------------------------------
	class ChoiceDuidType : public YangChoice
	{
	public:
		// Choice Option
		enum : uint32_t
		{
			ITEM_DUID_LLT,  // OptDuidLlt
			ITEM_DUID_EN,  // OptDuidEn
			ITEM_DUID_LL,  // OptDuidLl
			ITEM_DUID_UUID,  // OptDuidUuid
			ITEM_DUID_UNKNOWN,  // OptDuidUnknown
		};

		ChoiceDuidType(uint32_t id);
		~ChoiceDuidType();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Option: /duid/duid-type[duid-llt]
		// -----------------------------------------------------------------------------
		class OptDuidLlt : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DUID_LLT_HARDWARE_TYPE,  // LeafDuidLltHardwareType
				ITEM_DUID_LLT_TIME,  // LeafDuidLltTime
				ITEM_DUID_LLT_LINK_LAYER_ADDR,  // LeafDuidLltLinkLayerAddr
			};

			OptDuidLlt(uint32_t id);
			~OptDuidLlt();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-llt]/duid-llt-hardware-type
			// Description: Hardware type as assigned by IANA (RFC826).
			// -----------------------------------------------------------------------------
			class LeafDuidLltHardwareType : public YangLeaf
			{
			public:

				LeafDuidLltHardwareType(uint32_t id);
				~LeafDuidLltHardwareType();

			}; // LeafDuidLltHardwareType

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-llt]/duid-llt-time
			// Description: The time value is the time that the DUID is
			//               generated represented in seconds since midnight (UTC),
			//               January 1, 2000, modulo 2^32.
			// -----------------------------------------------------------------------------
			class LeafDuidLltTime : public YangLeaf
			{
			public:

				LeafDuidLltTime(uint32_t id);
				~LeafDuidLltTime();

			}; // LeafDuidLltTime

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-llt]/duid-llt-link-layer-addr
			// Description: Link-layer address as described in RFC2464
			// -----------------------------------------------------------------------------
			class LeafDuidLltLinkLayerAddr : public YangLeaf
			{
			public:

				LeafDuidLltLinkLayerAddr(uint32_t id);
				~LeafDuidLltLinkLayerAddr();

			}; // LeafDuidLltLinkLayerAddr

		}; // OptDuidLlt


		// -----------------------------------------------------------------------------
		// Option: /duid/duid-type[duid-en]
		// -----------------------------------------------------------------------------
		class OptDuidEn : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DUID_EN_ENTERPRISE_NUMBER,  // LeafDuidEnEnterpriseNumber
				ITEM_DUID_EN_IDENTIFIER,  // LeafDuidEnIdentifier
			};

			OptDuidEn(uint32_t id);
			~OptDuidEn();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-en]/duid-en-enterprise-number
			// Description: Vendor's registered Private Enterprise Number as
			//                  maintained by IANA
			// -----------------------------------------------------------------------------
			class LeafDuidEnEnterpriseNumber : public YangLeaf
			{
			public:

				LeafDuidEnEnterpriseNumber(uint32_t id);
				~LeafDuidEnEnterpriseNumber();

			}; // LeafDuidEnEnterpriseNumber

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-en]/duid-en-identifier
			// Description: Indentifier, unique to the device that is
			//               using it
			// -----------------------------------------------------------------------------
			class LeafDuidEnIdentifier : public YangLeaf
			{
			public:

				LeafDuidEnIdentifier(uint32_t id);
				~LeafDuidEnIdentifier();

			}; // LeafDuidEnIdentifier

		}; // OptDuidEn


		// -----------------------------------------------------------------------------
		// Option: /duid/duid-type[duid-ll]
		// -----------------------------------------------------------------------------
		class OptDuidLl : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DUID_LL_HARDWARE_TYPE,  // LeafDuidLlHardwareType
				ITEM_DUID_LL_LINK_LAYER_ADDR,  // LeafDuidLlLinkLayerAddr
			};

			OptDuidLl(uint32_t id);
			~OptDuidLl();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-ll]/duid-ll-hardware-type
			// Description: Hardware type as assigned by IANA (RFC826).
			// -----------------------------------------------------------------------------
			class LeafDuidLlHardwareType : public YangLeaf
			{
			public:

				LeafDuidLlHardwareType(uint32_t id);
				~LeafDuidLlHardwareType();

			}; // LeafDuidLlHardwareType

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-ll]/duid-ll-link-layer-addr
			// Description: Link-layer address as described in RFC2464
			// -----------------------------------------------------------------------------
			class LeafDuidLlLinkLayerAddr : public YangLeaf
			{
			public:

				LeafDuidLlLinkLayerAddr(uint32_t id);
				~LeafDuidLlLinkLayerAddr();

			}; // LeafDuidLlLinkLayerAddr

		}; // OptDuidLl


		// -----------------------------------------------------------------------------
		// Option: /duid/duid-type[duid-uuid]
		// -----------------------------------------------------------------------------
		class OptDuidUuid : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_UUID,  // LeafUuid
			};

			OptDuidUuid(uint32_t id);
			~OptDuidUuid();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-uuid]/uuid
			// Description: A Universally Unique IDentifier in the string
			//              		representation defined in RFC 4122. The canonical
			//              		representation uses lowercase characters
			// -----------------------------------------------------------------------------
			class LeafUuid : public YangLeaf
			{
			public:

				LeafUuid(uint32_t id);
				~LeafUuid();

			}; // LeafUuid

		}; // OptDuidUuid


		// -----------------------------------------------------------------------------
		// Option: /duid/duid-type[duid-unknown]
		// -----------------------------------------------------------------------------
		class OptDuidUnknown : public YangChoiceOption
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_DATA,  // LeafData
			};

			OptDuidUnknown(uint32_t id);
			~OptDuidUnknown();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /duid/duid-type[duid-unknown]/data
			// Description: The bits to be used as the identifier
			// -----------------------------------------------------------------------------
			class LeafData : public YangLeaf
			{
			public:

				LeafData(uint32_t id);
				~LeafData();

			}; // LeafData

		}; // OptDuidUnknown

	}; // ChoiceDuidType

}; // GrpDuid

// -----------------------------------------------------------------------------
// Grouping:    /portset-para
// Description: portset parameters
// -----------------------------------------------------------------------------
class GrpPortsetPara : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_PORT_PARAMETER,  // CntPortParameter
	};

	GrpPortsetPara(uint32_t id);
	~GrpPortsetPara();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Container:   /portset-para/port-parameter
	// Description: port parameter
	// -----------------------------------------------------------------------------
	class CntPortParameter : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_OFFSET,  // LeafOffset
			ITEM_PSID_LEN,  // LeafPsidLen
			ITEM_PSID,  // LeafPsid
		};

		CntPortParameter(uint32_t id);
		~CntPortParameter();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /portset-para/port-parameter/offset
		// Description: offset in a port set
		// -----------------------------------------------------------------------------
		class LeafOffset : public YangLeaf
		{
		public:

			LeafOffset(uint32_t id);
			~LeafOffset();

		}; // LeafOffset

		// -----------------------------------------------------------------------------
		// Leaf:        /portset-para/port-parameter/psid-len
		// Description: length of a psid
		// -----------------------------------------------------------------------------
		class LeafPsidLen : public YangLeaf
		{
		public:

			LeafPsidLen(uint32_t id);
			~LeafPsidLen();

		}; // LeafPsidLen

		// -----------------------------------------------------------------------------
		// Leaf:        /portset-para/port-parameter/psid
		// Description: psid value
		// -----------------------------------------------------------------------------
		class LeafPsid : public YangLeaf
		{
		public:

			LeafPsid(uint32_t id);
			~LeafPsid();

		}; // LeafPsid

	}; // CntPortParameter

}; // GrpPortsetPara

// -----------------------------------------------------------------------------
// Grouping:    /iaid
// Description: IA is a construct through which a server and a
//              client can identify, group, and manage a set of related IPv6
//              addresses. The key of the list is a 4-byte number IAID defined
//              in [RFC3315].
// -----------------------------------------------------------------------------
class GrpIaid : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_IDENTITY_ASSOCIATION,  // LstIdentityAssociation
	};

	GrpIaid(uint32_t id);
	~GrpIaid();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /iaid/identity-association
	// Description: IA
	// -----------------------------------------------------------------------------
	class LstIdentityAssociation : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_IAID,  // LeafIaid
			ITEM_IA_TYPE,  // LeafIaType
			ITEM_T1_TIME,  // LeafT1Time
			ITEM_T2_TIME,  // LeafT2Time
			ITEM_PREFERRED_LIFETIME,  // LeafPreferredLifetime
			ITEM_VALID_LIFETIME,  // LeafValidLifetime
			ITEM_IPV6_ADDR,  // LstIpv6Addr
			ITEM_IPV6_PREFIX,  // LstIpv6Prefix
			ITEM_PREFIX_LENGTH,  // LstPrefixLength
		};

		LstIdentityAssociation(uint32_t id);
		~LstIdentityAssociation();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/iaid
		// Description: IAID
		// -----------------------------------------------------------------------------
		class LeafIaid : public YangLeaf
		{
		public:

			LeafIaid(uint32_t id);
			~LeafIaid();

		}; // LeafIaid

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/ia-type
		// Description: IA type
		// -----------------------------------------------------------------------------
		class LeafIaType : public YangLeaf
		{
		public:

			LeafIaType(uint32_t id);
			~LeafIaType();

		}; // LeafIaType

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/t1-time
		// Description: t1 time
		// -----------------------------------------------------------------------------
		class LeafT1Time : public YangLeaf
		{
		public:

			LeafT1Time(uint32_t id);
			~LeafT1Time();

		}; // LeafT1Time

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/t2-time
		// Description: t2 time
		// -----------------------------------------------------------------------------
		class LeafT2Time : public YangLeaf
		{
		public:

			LeafT2Time(uint32_t id);
			~LeafT2Time();

		}; // LeafT2Time

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/preferred-lifetime
		// Description: preferred lifetime
		// -----------------------------------------------------------------------------
		class LeafPreferredLifetime : public YangLeaf
		{
		public:

			LeafPreferredLifetime(uint32_t id);
			~LeafPreferredLifetime();

		}; // LeafPreferredLifetime

		// -----------------------------------------------------------------------------
		// Leaf:        /iaid/identity-association/valid-lifetime
		// Description: valid lifetime
		// -----------------------------------------------------------------------------
		class LeafValidLifetime : public YangLeaf
		{
		public:

			LeafValidLifetime(uint32_t id);
			~LeafValidLifetime();

		}; // LeafValidLifetime

		// -----------------------------------------------------------------------------
		// List:        /iaid/identity-association/ipv6-addr
		// Description: ipv6 address
		// -----------------------------------------------------------------------------
		class LstIpv6Addr : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstIpv6Addr(uint32_t id);
			~LstIpv6Addr();

			YangResult_E initialise(void);

		}; // LstIpv6Addr

		// -----------------------------------------------------------------------------
		// List:        /iaid/identity-association/ipv6-prefix
		// Description: ipv6 prefix
		// -----------------------------------------------------------------------------
		class LstIpv6Prefix : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstIpv6Prefix(uint32_t id);
			~LstIpv6Prefix();

			YangResult_E initialise(void);

		}; // LstIpv6Prefix

		// -----------------------------------------------------------------------------
		// List:        /iaid/identity-association/prefix-length
		// Description: ipv6 prefix length
		// -----------------------------------------------------------------------------
		class LstPrefixLength : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstPrefixLength(uint32_t id);
			~LstPrefixLength();

			YangResult_E initialise(void);

		}; // LstPrefixLength

	}; // LstIdentityAssociation

}; // GrpIaid


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
// Module:      ietf-dhcpv6-types
// Description: This model defines a YANG data model that can be
//              used to define some commonly used DHCPv6 types
// -----------------------------------------------------------------------------
class ModuleIetfDhcpv6Types : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleIetfDhcpv6Types(uint32_t id);
	~ModuleIetfDhcpv6Types();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfDhcpv6Types_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_DHCPV6_TYPES_H_ */
