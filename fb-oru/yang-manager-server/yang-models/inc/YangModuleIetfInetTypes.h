#ifndef _MODULE_IETF_INET_TYPES_H_
#define _MODULE_IETF_INET_TYPES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfInetTypes.h
 * \brief     Module IetfInetTypes interface
 *
 *
 * \details   This file defines the YANG module ietf-inet-types interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-inet-types"
 *            YANG Filename:    "ietf-inet-types.yang"
 *            Module Prefix:    "inet"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-inet-types"
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


namespace Mplane {

namespace ModuleIetfInetTypes_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// This value represents the version of the IP protocol.
//
// In the value set and its semantics, this type is equivalent
// to the InetVersion textual convention of the SMIv2.
enum class IpVersion_E : uint32_t
{
	UNKNOWN,	// An unknown or unspecified version of the Internet
			// protocol.
	IPV4,	// The IPv4 protocol as defined in RFC 791.
	IPV6,	// The IPv6 protocol as defined in RFC 2460.

	Num_IpVersion_E
};


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
// Module:      ietf-inet-types
// Description: This module contains a collection of generally useful derived
//              YANG data types for Internet addresses and related things.
//
//              Copyright (c) 2013 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//
//              This version of this YANG module is part of RFC 6991; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIetfInetTypes : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleIetfInetTypes(uint32_t id);
	~ModuleIetfInetTypes();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfInetTypes_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_INET_TYPES_H_ */
