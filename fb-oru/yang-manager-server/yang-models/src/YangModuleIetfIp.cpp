/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfIp.cpp
 * \brief     Module IetfIp interface
 *
 *
 * \details   This file defines the YANG module ietf-ip interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-ip"
 *            YANG Filename:    "ietf-ip.yang"
 *            Module Prefix:    "ip"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-ip"
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
#include "YangModuleIetfIp.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfIp_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: Indicates support for configuring non-contiguous
//              subnet masks.
// -----------------------------------------------------------------------------
FeatureIpv4NonContiguousNetmasks::FeatureIpv4NonContiguousNetmasks(uint32_t id)
	: YangFeature("ipv4-non-contiguous-netmasks", id)
{
}

FeatureIpv4NonContiguousNetmasks::~FeatureIpv4NonContiguousNetmasks()
{
}

// -----------------------------------------------------------------------------
// Feature
// Description: Indicates support for privacy extensions for stateless address
//              autoconfiguration in IPv6.
// -----------------------------------------------------------------------------
FeatureIpv6PrivacyAutoconf::FeatureIpv6PrivacyAutoconf(uint32_t id)
	: YangFeature("ipv6-privacy-autoconf", id)
{
}

FeatureIpv6PrivacyAutoconf::~FeatureIpv6PrivacyAutoconf()
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
// Module:      ietf-ip
// Description: This module contains a collection of YANG definitions for
//              managing IP implementations.
//              Copyright (c) 2018 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 8344; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIetfIp::ModuleIetfIp(uint32_t id)
	: YangModule ("ietf-ip",
	              "ietf-ip.yang",
	              "ip",
	              "urn:ietf:params:xml:ns:yang:ietf-ip",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Feature
	// Description: Indicates support for configuring non-contiguous
	//              subnet masks.
	// -----------------------------------------------------------------------------
	FeatureIpv4NonContiguousNetmasks ipv4NonContiguousNetmasksInst(ITEM_IPV4_NON_CONTIGUOUS_NETMASKS);
	addFeature(ipv4NonContiguousNetmasksInst);

	// -----------------------------------------------------------------------------
	// Feature
	// Description: Indicates support for privacy extensions for stateless address
	//              autoconfiguration in IPv6.
	// -----------------------------------------------------------------------------
	FeatureIpv6PrivacyAutoconf ipv6PrivacyAutoconfInst(ITEM_IPV6_PRIVACY_AUTOCONF);
	addFeature(ipv6PrivacyAutoconfInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfIp::~ModuleIetfIp()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfIp::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfIp>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfIp::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
