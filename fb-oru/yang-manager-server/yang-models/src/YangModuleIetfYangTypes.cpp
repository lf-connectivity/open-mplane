/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfYangTypes.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIetfYangTypes.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfYangTypes_NS;

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
ModuleIetfYangTypes::ModuleIetfYangTypes(uint32_t id)
	: YangModule ("ietf-yang-types",
	              "ietf-yang-types.yang",
	              "yang",
	              "urn:ietf:params:xml:ns:yang:ietf-yang-types",
	              id)
// Add user code here
// %%->

// <-%%
{

	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfYangTypes::~ModuleIetfYangTypes()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfYangTypes::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfYangTypes>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfYangTypes::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
