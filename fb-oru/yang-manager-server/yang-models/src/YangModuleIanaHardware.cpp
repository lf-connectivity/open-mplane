/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIanaHardware.cpp
 * \brief     Module IanaHardware interface
 *
 *
 * \details   This file defines the YANG module iana-hardware interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "iana-hardware"
 *            YANG Filename:    "iana-hardware.yang"
 *            Module Prefix:    "ianahw"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:iana-hardware"
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
#include "YangModuleIanaHardware.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIanaHardware_NS;

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
// Module:      iana-hardware
// Description: IANA-defined identities for hardware class.
//              The latest revision of this YANG module can be obtained from
//              the IANA website.
//              Requests for new values should be made to IANA via
//              email (iana@iana.org).
//              Copyright (c) 2018 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              The initial version of this YANG module is part of RFC 8348;
//              see the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIanaHardware::ModuleIanaHardware(uint32_t id)
	: YangModule ("iana-hardware",
	              "iana-hardware.yang",
	              "ianahw",
	              "urn:ietf:params:xml:ns:yang:iana-hardware",
	              id)
// Add user code here
// %%->

// <-%%
{

	// Add user code here
	// %%->

	// <-%%
}

ModuleIanaHardware::~ModuleIanaHardware()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIanaHardware::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIanaHardware>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIanaHardware::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
