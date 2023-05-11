#ifndef _MODULE_IANA_IF_TYPE_H_
#define _MODULE_IANA_IF_TYPE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIanaIfType.h
 * \brief     Module IanaIfType interface
 *
 *
 * \details   This file defines the YANG module iana-if-type interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "iana-if-type"
 *            YANG Filename:    "iana-if-type.yang"
 *            Module Prefix:    "ianaift"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:iana-if-type"
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


namespace Mplane {

namespace ModuleIanaIfType_NS {

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
// Module:      iana-if-type
// Description: This YANG module defines YANG identities for IANA-registered
//              interface types.
//              This YANG module is maintained by IANA and reflects the
//              'ifType definitions' registry.
//              The latest revision of this YANG module can be obtained from
//              the IANA web site.
//              Requests for new values should be made to IANA via
//              email (iana&iana.org).
//              Copyright (c) 2014 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//              The initial version of this YANG module is part of RFC 7224;
//              see the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIanaIfType : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleIanaIfType(uint32_t id);
	~ModuleIanaIfType();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIanaIfType_NS */

} /* namespace Mplane */

#endif /* _MODULE_IANA_IF_TYPE_H_ */
