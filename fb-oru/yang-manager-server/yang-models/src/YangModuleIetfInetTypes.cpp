/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfInetTypes.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIetfInetTypes.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfInetTypes_NS;

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
ModuleIetfInetTypes::ModuleIetfInetTypes(uint32_t id)
	: YangModule ("ietf-inet-types",
	              "ietf-inet-types.yang",
	              "inet",
	              "urn:ietf:params:xml:ns:yang:ietf-inet-types",
	              id)
// Add user code here
// %%->

// <-%%
{

	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfInetTypes::~ModuleIetfInetTypes()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfInetTypes::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfInetTypes>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfInetTypes::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
