/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfDhcpv6Types.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIetfDhcpv6Types.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfDhcpv6Types_NS;

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    vendor-infor
// Description: Vendor information.
// -----------------------------------------------------------------------------
GrpVendorInfor::GrpVendorInfor(uint32_t id)
	: YangGroup("vendor-infor", id)
{
}

GrpVendorInfor::~GrpVendorInfor()
{
}

YangResult_E GrpVendorInfor::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /vendor-infor/vendor-info
	// Description:
	// -----------------------------------------------------------------------------
	CntVendorInfo vendorInfoInst(ITEM_VENDOR_INFO);
	vendorInfoInst.initialise();
	addContainer(vendorInfoInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   vendor-info
// Description:
// -----------------------------------------------------------------------------
GrpVendorInfor::CntVendorInfo::CntVendorInfo(uint32_t id)
	: YangContainer("vendor-info", id)
{
}

GrpVendorInfor::CntVendorInfo::~CntVendorInfo()
{
}

YangResult_E GrpVendorInfor::CntVendorInfo::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /vendor-infor/vendor-info/ent-num
	// Description: enterprise number
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafEntNum entNumInst(ITEM_ENT_NUM);
	addLeaf(entNumInst);

	// -----------------------------------------------------------------------------
	// List:        /vendor-infor/vendor-info/data
	// Description: specific vendor info
	// Array Key:
	// -----------------------------------------------------------------------------
	LstData dataInst(ITEM_DATA);
	dataInst.initialise();
	addList(dataInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /vendor-infor/vendor-info/ent-num
// Description: enterprise number
// -----------------------------------------------------------------------------
GrpVendorInfor::CntVendorInfo::LeafEntNum::LeafEntNum(uint32_t id)
	: YangLeaf("ent-num", id)
{
}

GrpVendorInfor::CntVendorInfo::LeafEntNum::~LeafEntNum()
{
}

// -----------------------------------------------------------------------------
// List:        data
// Description: specific vendor info
// -----------------------------------------------------------------------------
GrpVendorInfor::CntVendorInfo::LstData::LstData(uint32_t id)
	: YangList("data", id)
{
}

GrpVendorInfor::CntVendorInfo::LstData::~LstData()
{
}

YangResult_E GrpVendorInfor::CntVendorInfo::LstData::initialise(void)
{


	return YangResult_E::OK;
}








// -----------------------------------------------------------------------------
// Grouping:    duid
// Description: Each server and client has only one DUID (DHCP Unique Identifier).
//              The DUID here identifies a unique DHCPv6 server for clients. DUID
//              consists of a two-octet type field and an arbitrary length (no more
//              than 128 bytes) content field. Currently there are four defined types
//              of DUIDs in RFC3315 and RFC6355 - DUID-LLT, DUID-EN, DUID-LL and
//              DUID-UUID. DUID-Uknown represents those unconventional DUIDs.
// -----------------------------------------------------------------------------
GrpDuid::GrpDuid(uint32_t id)
	: YangGroup("duid", id)
{
}

GrpDuid::~GrpDuid()
{
}

YangResult_E GrpDuid::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/type-code
	// Description: Type code of this DUID
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafTypeCode typeCodeInst(ITEM_TYPE_CODE);
	addLeaf(typeCodeInst);

	// -----------------------------------------------------------------------------
	// Choice:      /duid/duid-type
	// Description: Selects the format for the DUID.
	// Type:        DuidType_E
	// Units:       -
	// -----------------------------------------------------------------------------
	ChoiceDuidType duidTypeInst(ITEM_DUID_TYPE);
	duidTypeInst.initialise();
	addChoice(duidTypeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/type-code
// Description: Type code of this DUID
// -----------------------------------------------------------------------------
GrpDuid::LeafTypeCode::LeafTypeCode(uint32_t id)
	: YangLeaf("type-code", id)
{
}

GrpDuid::LeafTypeCode::~LeafTypeCode()
{
}

// -----------------------------------------------------------------------------
// Choice:      duid-type
// Description: Selects the format for the DUID.
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::ChoiceDuidType(uint32_t id)
	: YangChoice("duid-type", id)
{
}

GrpDuid::ChoiceDuidType::~ChoiceDuidType()
{
}

YangResult_E GrpDuid::ChoiceDuidType::initialise(void)
{

	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDuidLlt duidLlt(ITEM_DUID_LLT);
	duidLlt.initialise();
	addOption(duidLlt);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDuidEn duidEn(ITEM_DUID_EN);
	duidEn.initialise();
	addOption(duidEn);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDuidLl duidLl(ITEM_DUID_LL);
	duidLl.initialise();
	addOption(duidLl);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDuidUuid duidUuid(ITEM_DUID_UUID);
	duidUuid.initialise();
	addOption(duidUuid);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDuidUnknown duidUnknown(ITEM_DUID_UNKNOWN);
	duidUnknown.initialise();
	addOption(duidUnknown);



	return YangResult_E::OK;
}


// -------------------------------------------------------------------------
// Option:      /duid/duid-type[duid-llt]
// -------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLlt::OptDuidLlt(uint32_t id)
	: YangChoiceOption("duid-llt", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLlt::~OptDuidLlt()
{
}

YangResult_E GrpDuid::ChoiceDuidType::OptDuidLlt::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-llt]/duid-llt-hardware-type
	// Description: Hardware type as assigned by IANA (RFC826).
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidLltHardwareType duidLltHardwareTypeInst(ITEM_DUID_LLT_HARDWARE_TYPE);
	addLeaf(duidLltHardwareTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-llt]/duid-llt-time
	// Description: The time value is the time that the DUID is
	//               generated represented in seconds since midnight (UTC),
	//               January 1, 2000, modulo 2^32.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidLltTime duidLltTimeInst(ITEM_DUID_LLT_TIME);
	addLeaf(duidLltTimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-llt]/duid-llt-link-layer-addr
	// Description: Link-layer address as described in RFC2464
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidLltLinkLayerAddr duidLltLinkLayerAddrInst(ITEM_DUID_LLT_LINK_LAYER_ADDR);
	addLeaf(duidLltLinkLayerAddrInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-llt]/duid-llt-hardware-type
// Description: Hardware type as assigned by IANA (RFC826).
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltHardwareType::LeafDuidLltHardwareType(uint32_t id)
	: YangLeaf("duid-llt-hardware-type", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltHardwareType::~LeafDuidLltHardwareType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-llt]/duid-llt-time
// Description: The time value is the time that the DUID is
//               generated represented in seconds since midnight (UTC),
//               January 1, 2000, modulo 2^32.
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltTime::LeafDuidLltTime(uint32_t id)
	: YangLeaf("duid-llt-time", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltTime::~LeafDuidLltTime()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-llt]/duid-llt-link-layer-addr
// Description: Link-layer address as described in RFC2464
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltLinkLayerAddr::LeafDuidLltLinkLayerAddr(uint32_t id)
	: YangLeaf("duid-llt-link-layer-addr", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLlt::LeafDuidLltLinkLayerAddr::~LeafDuidLltLinkLayerAddr()
{
}



// -------------------------------------------------------------------------
// Option:      /duid/duid-type[duid-en]
// -------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidEn::OptDuidEn(uint32_t id)
	: YangChoiceOption("duid-en", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidEn::~OptDuidEn()
{
}

YangResult_E GrpDuid::ChoiceDuidType::OptDuidEn::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-en]/duid-en-enterprise-number
	// Description: Vendor's registered Private Enterprise Number as
	//                  maintained by IANA
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidEnEnterpriseNumber duidEnEnterpriseNumberInst(ITEM_DUID_EN_ENTERPRISE_NUMBER);
	addLeaf(duidEnEnterpriseNumberInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-en]/duid-en-identifier
	// Description: Indentifier, unique to the device that is
	//               using it
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidEnIdentifier duidEnIdentifierInst(ITEM_DUID_EN_IDENTIFIER);
	addLeaf(duidEnIdentifierInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-en]/duid-en-enterprise-number
// Description: Vendor's registered Private Enterprise Number as
//                  maintained by IANA
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidEn::LeafDuidEnEnterpriseNumber::LeafDuidEnEnterpriseNumber(uint32_t id)
	: YangLeaf("duid-en-enterprise-number", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidEn::LeafDuidEnEnterpriseNumber::~LeafDuidEnEnterpriseNumber()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-en]/duid-en-identifier
// Description: Indentifier, unique to the device that is
//               using it
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidEn::LeafDuidEnIdentifier::LeafDuidEnIdentifier(uint32_t id)
	: YangLeaf("duid-en-identifier", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidEn::LeafDuidEnIdentifier::~LeafDuidEnIdentifier()
{
}



// -------------------------------------------------------------------------
// Option:      /duid/duid-type[duid-ll]
// -------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLl::OptDuidLl(uint32_t id)
	: YangChoiceOption("duid-ll", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLl::~OptDuidLl()
{
}

YangResult_E GrpDuid::ChoiceDuidType::OptDuidLl::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-ll]/duid-ll-hardware-type
	// Description: Hardware type as assigned by IANA (RFC826).
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidLlHardwareType duidLlHardwareTypeInst(ITEM_DUID_LL_HARDWARE_TYPE);
	addLeaf(duidLlHardwareTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-ll]/duid-ll-link-layer-addr
	// Description: Link-layer address as described in RFC2464
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafDuidLlLinkLayerAddr duidLlLinkLayerAddrInst(ITEM_DUID_LL_LINK_LAYER_ADDR);
	addLeaf(duidLlLinkLayerAddrInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-ll]/duid-ll-hardware-type
// Description: Hardware type as assigned by IANA (RFC826).
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLl::LeafDuidLlHardwareType::LeafDuidLlHardwareType(uint32_t id)
	: YangLeaf("duid-ll-hardware-type", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLl::LeafDuidLlHardwareType::~LeafDuidLlHardwareType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-ll]/duid-ll-link-layer-addr
// Description: Link-layer address as described in RFC2464
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidLl::LeafDuidLlLinkLayerAddr::LeafDuidLlLinkLayerAddr(uint32_t id)
	: YangLeaf("duid-ll-link-layer-addr", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidLl::LeafDuidLlLinkLayerAddr::~LeafDuidLlLinkLayerAddr()
{
}



// -------------------------------------------------------------------------
// Option:      /duid/duid-type[duid-uuid]
// -------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidUuid::OptDuidUuid(uint32_t id)
	: YangChoiceOption("duid-uuid", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidUuid::~OptDuidUuid()
{
}

YangResult_E GrpDuid::ChoiceDuidType::OptDuidUuid::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-uuid]/uuid
	// Description: A Universally Unique IDentifier in the string
	//              		representation defined in RFC 4122. The canonical
	//              		representation uses lowercase characters
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafUuid uuidInst(ITEM_UUID);
	addLeaf(uuidInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-uuid]/uuid
// Description: A Universally Unique IDentifier in the string
//              		representation defined in RFC 4122. The canonical
//              		representation uses lowercase characters
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidUuid::LeafUuid::LeafUuid(uint32_t id)
	: YangLeaf("uuid", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidUuid::LeafUuid::~LeafUuid()
{
}



// -------------------------------------------------------------------------
// Option:      /duid/duid-type[duid-unknown]
// -------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidUnknown::OptDuidUnknown(uint32_t id)
	: YangChoiceOption("duid-unknown", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidUnknown::~OptDuidUnknown()
{
}

YangResult_E GrpDuid::ChoiceDuidType::OptDuidUnknown::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /duid/duid-type[duid-unknown]/data
	// Description: The bits to be used as the identifier
	// Type:        ???BINARY
	// Units:
	// -----------------------------------------------------------------------------
	LeafData dataInst(ITEM_DATA);
	addLeaf(dataInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /duid/duid-type[duid-unknown]/data
// Description: The bits to be used as the identifier
// -----------------------------------------------------------------------------
GrpDuid::ChoiceDuidType::OptDuidUnknown::LeafData::LeafData(uint32_t id)
	: YangLeaf("data", id)
{
}

GrpDuid::ChoiceDuidType::OptDuidUnknown::LeafData::~LeafData()
{
}








// -----------------------------------------------------------------------------
// Grouping:    portset-para
// Description: portset parameters
// -----------------------------------------------------------------------------
GrpPortsetPara::GrpPortsetPara(uint32_t id)
	: YangGroup("portset-para", id)
{
}

GrpPortsetPara::~GrpPortsetPara()
{
}

YangResult_E GrpPortsetPara::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Container:   /portset-para/port-parameter
	// Description: port parameter
	// -----------------------------------------------------------------------------
	CntPortParameter portParameterInst(ITEM_PORT_PARAMETER);
	portParameterInst.initialise();
	addContainer(portParameterInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   port-parameter
// Description: port parameter
// -----------------------------------------------------------------------------
GrpPortsetPara::CntPortParameter::CntPortParameter(uint32_t id)
	: YangContainer("port-parameter", id)
{
}

GrpPortsetPara::CntPortParameter::~CntPortParameter()
{
}

YangResult_E GrpPortsetPara::CntPortParameter::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /portset-para/port-parameter/offset
	// Description: offset in a port set
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafOffset offsetInst(ITEM_OFFSET);
	addLeaf(offsetInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /portset-para/port-parameter/psid-len
	// Description: length of a psid
	// Type:        uint8
	// Units:
	// -----------------------------------------------------------------------------
	LeafPsidLen psidLenInst(ITEM_PSID_LEN);
	addLeaf(psidLenInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /portset-para/port-parameter/psid
	// Description: psid value
	// Type:        uint16
	// Units:
	// -----------------------------------------------------------------------------
	LeafPsid psidInst(ITEM_PSID);
	addLeaf(psidInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /portset-para/port-parameter/offset
// Description: offset in a port set
// -----------------------------------------------------------------------------
GrpPortsetPara::CntPortParameter::LeafOffset::LeafOffset(uint32_t id)
	: YangLeaf("offset", id)
{
}

GrpPortsetPara::CntPortParameter::LeafOffset::~LeafOffset()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /portset-para/port-parameter/psid-len
// Description: length of a psid
// -----------------------------------------------------------------------------
GrpPortsetPara::CntPortParameter::LeafPsidLen::LeafPsidLen(uint32_t id)
	: YangLeaf("psid-len", id)
{
}

GrpPortsetPara::CntPortParameter::LeafPsidLen::~LeafPsidLen()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /portset-para/port-parameter/psid
// Description: psid value
// -----------------------------------------------------------------------------
GrpPortsetPara::CntPortParameter::LeafPsid::LeafPsid(uint32_t id)
	: YangLeaf("psid", id)
{
}

GrpPortsetPara::CntPortParameter::LeafPsid::~LeafPsid()
{
}






// -----------------------------------------------------------------------------
// Grouping:    iaid
// Description: IA is a construct through which a server and a
//              client can identify, group, and manage a set of related IPv6
//              addresses. The key of the list is a 4-byte number IAID defined
//              in [RFC3315].
// -----------------------------------------------------------------------------
GrpIaid::GrpIaid(uint32_t id)
	: YangGroup("iaid", id)
{
}

GrpIaid::~GrpIaid()
{
}

YangResult_E GrpIaid::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /iaid/identity-association
	// Description: IA
	// Array Key:
	// -----------------------------------------------------------------------------
	LstIdentityAssociation identityAssociationInst(ITEM_IDENTITY_ASSOCIATION);
	identityAssociationInst.initialise();
	addList(identityAssociationInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        identity-association
// Description: IA
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LstIdentityAssociation(uint32_t id)
	: YangList("identity-association", id)
{
}

GrpIaid::LstIdentityAssociation::~LstIdentityAssociation()
{
}

YangResult_E GrpIaid::LstIdentityAssociation::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/iaid
	// Description: IAID
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafIaid iaidInst(ITEM_IAID);
	addLeaf(iaidInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/ia-type
	// Description: IA type
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafIaType iaTypeInst(ITEM_IA_TYPE);
	addLeaf(iaTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/t1-time
	// Description: t1 time
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafT1Time t1TimeInst(ITEM_T1_TIME);
	addLeaf(t1TimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/t2-time
	// Description: t2 time
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafT2Time t2TimeInst(ITEM_T2_TIME);
	addLeaf(t2TimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/preferred-lifetime
	// Description: preferred lifetime
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafPreferredLifetime preferredLifetimeInst(ITEM_PREFERRED_LIFETIME);
	addLeaf(preferredLifetimeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /iaid/identity-association/valid-lifetime
	// Description: valid lifetime
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafValidLifetime validLifetimeInst(ITEM_VALID_LIFETIME);
	addLeaf(validLifetimeInst);

	// -----------------------------------------------------------------------------
	// List:        /iaid/identity-association/ipv6-addr
	// Description: ipv6 address
	// Array Key:
	// -----------------------------------------------------------------------------
	LstIpv6Addr ipv6AddrInst(ITEM_IPV6_ADDR);
	ipv6AddrInst.initialise();
	addList(ipv6AddrInst);

	// -----------------------------------------------------------------------------
	// List:        /iaid/identity-association/ipv6-prefix
	// Description: ipv6 prefix
	// Array Key:
	// -----------------------------------------------------------------------------
	LstIpv6Prefix ipv6PrefixInst(ITEM_IPV6_PREFIX);
	ipv6PrefixInst.initialise();
	addList(ipv6PrefixInst);

	// -----------------------------------------------------------------------------
	// List:        /iaid/identity-association/prefix-length
	// Description: ipv6 prefix length
	// Array Key:
	// -----------------------------------------------------------------------------
	LstPrefixLength prefixLengthInst(ITEM_PREFIX_LENGTH);
	prefixLengthInst.initialise();
	addList(prefixLengthInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/iaid
// Description: IAID
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafIaid::LeafIaid(uint32_t id)
	: YangLeaf("iaid", id)
{
}

GrpIaid::LstIdentityAssociation::LeafIaid::~LeafIaid()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/ia-type
// Description: IA type
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafIaType::LeafIaType(uint32_t id)
	: YangLeaf("ia-type", id)
{
}

GrpIaid::LstIdentityAssociation::LeafIaType::~LeafIaType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/t1-time
// Description: t1 time
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafT1Time::LeafT1Time(uint32_t id)
	: YangLeaf("t1-time", id)
{
}

GrpIaid::LstIdentityAssociation::LeafT1Time::~LeafT1Time()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/t2-time
// Description: t2 time
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafT2Time::LeafT2Time(uint32_t id)
	: YangLeaf("t2-time", id)
{
}

GrpIaid::LstIdentityAssociation::LeafT2Time::~LeafT2Time()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/preferred-lifetime
// Description: preferred lifetime
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafPreferredLifetime::LeafPreferredLifetime(uint32_t id)
	: YangLeaf("preferred-lifetime", id)
{
}

GrpIaid::LstIdentityAssociation::LeafPreferredLifetime::~LeafPreferredLifetime()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /iaid/identity-association/valid-lifetime
// Description: valid lifetime
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LeafValidLifetime::LeafValidLifetime(uint32_t id)
	: YangLeaf("valid-lifetime", id)
{
}

GrpIaid::LstIdentityAssociation::LeafValidLifetime::~LeafValidLifetime()
{
}

// -----------------------------------------------------------------------------
// List:        ipv6-addr
// Description: ipv6 address
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LstIpv6Addr::LstIpv6Addr(uint32_t id)
	: YangList("ipv6-addr", id)
{
}

GrpIaid::LstIdentityAssociation::LstIpv6Addr::~LstIpv6Addr()
{
}

YangResult_E GrpIaid::LstIdentityAssociation::LstIpv6Addr::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        ipv6-prefix
// Description: ipv6 prefix
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LstIpv6Prefix::LstIpv6Prefix(uint32_t id)
	: YangList("ipv6-prefix", id)
{
}

GrpIaid::LstIdentityAssociation::LstIpv6Prefix::~LstIpv6Prefix()
{
}

YangResult_E GrpIaid::LstIdentityAssociation::LstIpv6Prefix::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        prefix-length
// Description: ipv6 prefix length
// -----------------------------------------------------------------------------
GrpIaid::LstIdentityAssociation::LstPrefixLength::LstPrefixLength(uint32_t id)
	: YangList("prefix-length", id)
{
}

GrpIaid::LstIdentityAssociation::LstPrefixLength::~LstPrefixLength()
{
}

YangResult_E GrpIaid::LstIdentityAssociation::LstPrefixLength::initialise(void)
{


	return YangResult_E::OK;
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
// Module:      ietf-dhcpv6-types
// Description: This model defines a YANG data model that can be
//              used to define some commonly used DHCPv6 types
// -----------------------------------------------------------------------------
ModuleIetfDhcpv6Types::ModuleIetfDhcpv6Types(uint32_t id)
	: YangModule ("ietf-dhcpv6-types",
	              "ietf-dhcpv6-types.yang",
	              "dhcpv6-types",
	              "urn:ietf:params:xml:ns:yang:ietf-dhcpv6-types",
	              id)
// Add user code here
// %%->

// <-%%
{

	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfDhcpv6Types::~ModuleIetfDhcpv6Types()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfDhcpv6Types::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfDhcpv6Types>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfDhcpv6Types::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
