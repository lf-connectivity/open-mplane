/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIanaIfType.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleIanaIfType.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleIanaIfType_NS;

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
ModuleIanaIfType::ModuleIanaIfType(uint32_t id)
    : YangModule(
          "iana-if-type",
          "iana-if-type.yang",
          "ianaift",
          "urn:ietf:params:xml:ns:yang:iana-if-type",
          id)
// Add user code here
// %%->

// <-%%
{

  // Add user code here
  // %%->

  // <-%%
}

ModuleIanaIfType::~ModuleIanaIfType() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleIanaIfType::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleIanaIfType>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleIanaIfType::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
