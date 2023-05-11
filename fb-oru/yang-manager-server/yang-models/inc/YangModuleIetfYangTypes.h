#ifndef _MODULE_IETF_YANG_TYPES_H_
#define _MODULE_IETF_YANG_TYPES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfYangTypes.h
 * \brief     Module IetfYangTypes interface
 *
 *
 * \details   This file defines the YANG module ietf-yang-types interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-yang-types"
 *            YANG Filename:    "ietf-yang-types.yang"
 *            Module Prefix:    "yang"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-yang-types"
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

namespace ModuleIetfYangTypes_NS {

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
// Module:      ietf-yang-types
// Description: This module contains a collection of generally useful derived
//              YANG data types.
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
class ModuleIetfYangTypes : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleIetfYangTypes(uint32_t id);
	~ModuleIetfYangTypes();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfYangTypes_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_YANG_TYPES_H_ */
