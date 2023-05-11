/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfYangLibrary.cpp
 * \brief     Module IetfYangLibrary interface
 *
 *
 * \details   This file defines the YANG module ietf-yang-library interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-yang-library"
 *            YANG Filename:    "ietf-yang-library.yang"
 *            Module Prefix:    "yanglib"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-yang-library"
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
#include "YangModuleIetfYangLibrary.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleIetfYangLibrary_NS;

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
// -----------------------------------------------------------------------------
// Container:   modules-state
// Description: Contains YANG module monitoring information.
// -----------------------------------------------------------------------------
CntModulesState::CntModulesState(uint32_t id)
    : YangContainer("modules-state", id) {}

CntModulesState::~CntModulesState() {}

YangResult_E
CntModulesState::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /modules-state/module-set-id
  // Description: Contains a server-specific identifier representing
  //              the current set of modules and submodules.  The
  //              server MUST change the value of this leaf if the
  //              information represented by the 'module' list instances
  //              has changed.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafModuleSetId moduleSetIdInst(ITEM_MODULE_SET_ID);
  addLeaf(moduleSetIdInst);

  // -----------------------------------------------------------------------------
  // Uses:        /modules-state/module-list
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList moduleListInst(ITEM_MODULE_LIST);
  moduleListInst.initialise();
  addGroup(moduleListInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /modules-state/module-set-id
// Description: Contains a server-specific identifier representing
//              the current set of modules and submodules.  The
//              server MUST change the value of this leaf if the
//              information represented by the 'module' list instances
//              has changed.
// -----------------------------------------------------------------------------
CntModulesState::LeafModuleSetId::LeafModuleSetId(uint32_t id)
    : YangLeaf("module-set-id", id) {}

CntModulesState::LeafModuleSetId::~LeafModuleSetId() {}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    module-list
// Description: The module data structure is represented as a grouping
//              so it can be reused in configuration or another monitoring
//              data structure.
// -----------------------------------------------------------------------------
GrpModuleList::GrpModuleList(uint32_t id) : YangGroup("module-list", id) {}

GrpModuleList::~GrpModuleList() {}

YangResult_E
GrpModuleList::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /module-list/module
  // Description: Each entry represents one revision of one module
  //              currently supported by the server.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstModule moduleInst(ITEM_MODULE);
  moduleInst.initialise();
  addList(moduleInst);

  // -----------------------------------------------------------------------------
  // Grouping:    /module-list/common-leafs
  // Description: Common parameters for YANG modules and submodules.
  // -----------------------------------------------------------------------------
  GrpCommonLeafs commonLeafsInst(ITEM_COMMON_LEAFS);
  commonLeafsInst.initialise();
  addGroup(commonLeafsInst);

  // -----------------------------------------------------------------------------
  // Grouping:    /module-list/schema-leaf
  // Description: Common schema leaf parameter for modules and submodules.
  // -----------------------------------------------------------------------------
  GrpSchemaLeaf schemaLeafInst(ITEM_SCHEMA_LEAF);
  schemaLeafInst.initialise();
  addGroup(schemaLeafInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        module
// Description: Each entry represents one revision of one module
//              currently supported by the server.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LstModule(uint32_t id) : YangList("module", id) {}

GrpModuleList::LstModule::~LstModule() {}

YangResult_E
GrpModuleList::LstModule::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /module-list/module/namespace
  // Description: The XML namespace identifier for this module.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafNamespace namespaceInst(ITEM_NAMESPACE);
  addLeaf(namespaceInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /module-list/module/conformance-type
  // Description: Indicates the type of conformance the server is claiming
  //              for the YANG module identified by this entry.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafConformanceType conformanceTypeInst(ITEM_CONFORMANCE_TYPE);
  addLeaf(conformanceTypeInst);

  // -----------------------------------------------------------------------------
  // List:        /module-list/module/feature
  // Description: List of YANG feature names from this module that are
  //              supported by the server, regardless of whether they are
  //              defined in the module or any included submodule.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstFeature featureInst(ITEM_FEATURE);
  featureInst.initialise();
  addList(featureInst);

  // -----------------------------------------------------------------------------
  // List:        /module-list/module/deviation
  // Description: List of YANG deviation module names and revisions
  //              used by this server to modify the conformance of
  //              the module associated with this entry.  Note that
  //              the same module can be used for deviations for
  //              multiple modules, so the same entry MAY appear
  //              within multiple 'module' entries.
  //              The deviation module MUST be present in the 'module'
  //              list, with the same name and revision values.
  //              The 'conformance-type' value will be 'implement' for
  //              the deviation module.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstDeviation deviationInst(ITEM_DEVIATION);
  deviationInst.initialise();
  addList(deviationInst);

  // -----------------------------------------------------------------------------
  // List:        /module-list/module/submodule
  // Description: Each entry represents one submodule within the
  //              parent module.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSubmodule submoduleInst(ITEM_SUBMODULE);
  submoduleInst.initialise();
  addList(submoduleInst);

  // -----------------------------------------------------------------------------
  // Uses:        /module-list/module/common-leafs
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList::GrpCommonLeafs commonLeafsInst(ITEM_COMMON_LEAFS);
  commonLeafsInst.initialise();
  addGroup(commonLeafsInst);

  // -----------------------------------------------------------------------------
  // Uses:        /module-list/module/schema-leaf
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList::GrpSchemaLeaf schemaLeafInst(ITEM_SCHEMA_LEAF);
  schemaLeafInst.initialise();
  addGroup(schemaLeafInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /module-list/module/namespace
// Description: The XML namespace identifier for this module.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LeafNamespace::LeafNamespace(uint32_t id)
    : YangLeaf("namespace", id) {}

GrpModuleList::LstModule::LeafNamespace::~LeafNamespace() {}

// -----------------------------------------------------------------------------
// Leaf:        /module-list/module/conformance-type
// Description: Indicates the type of conformance the server is claiming
//              for the YANG module identified by this entry.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LeafConformanceType::LeafConformanceType(uint32_t id)
    : YangLeaf("conformance-type", id) {}

GrpModuleList::LstModule::LeafConformanceType::~LeafConformanceType() {}

// -----------------------------------------------------------------------------
// List:        feature
// Description: List of YANG feature names from this module that are
//              supported by the server, regardless of whether they are
//              defined in the module or any included submodule.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LstFeature::LstFeature(uint32_t id)
    : YangList("feature", id) {}

GrpModuleList::LstModule::LstFeature::~LstFeature() {}

YangResult_E
GrpModuleList::LstModule::LstFeature::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        deviation
// Description: List of YANG deviation module names and revisions
//              used by this server to modify the conformance of
//              the module associated with this entry.  Note that
//              the same module can be used for deviations for
//              multiple modules, so the same entry MAY appear
//              within multiple 'module' entries.
//              The deviation module MUST be present in the 'module'
//              list, with the same name and revision values.
//              The 'conformance-type' value will be 'implement' for
//              the deviation module.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LstDeviation::LstDeviation(uint32_t id)
    : YangList("deviation", id) {}

GrpModuleList::LstModule::LstDeviation::~LstDeviation() {}

YangResult_E
GrpModuleList::LstModule::LstDeviation::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /module-list/module/deviation/common-leafs
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList::GrpCommonLeafs commonLeafsInst(ITEM_COMMON_LEAFS);
  commonLeafsInst.initialise();
  addGroup(commonLeafsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        submodule
// Description: Each entry represents one submodule within the
//              parent module.
// -----------------------------------------------------------------------------
GrpModuleList::LstModule::LstSubmodule::LstSubmodule(uint32_t id)
    : YangList("submodule", id) {}

GrpModuleList::LstModule::LstSubmodule::~LstSubmodule() {}

YangResult_E
GrpModuleList::LstModule::LstSubmodule::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /module-list/module/submodule/common-leafs
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList::GrpCommonLeafs commonLeafsInst(ITEM_COMMON_LEAFS);
  commonLeafsInst.initialise();
  addGroup(commonLeafsInst);

  // -----------------------------------------------------------------------------
  // Uses:        /module-list/module/submodule/schema-leaf
  // Description:
  // -----------------------------------------------------------------------------
  GrpModuleList::GrpSchemaLeaf schemaLeafInst(ITEM_SCHEMA_LEAF);
  schemaLeafInst.initialise();
  addGroup(schemaLeafInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    common-leafs
// Description: Common parameters for YANG modules and submodules.
// -----------------------------------------------------------------------------
GrpModuleList::GrpCommonLeafs::GrpCommonLeafs(uint32_t id)
    : YangGroup("common-leafs", id) {}

GrpModuleList::GrpCommonLeafs::~GrpCommonLeafs() {}

YangResult_E
GrpModuleList::GrpCommonLeafs::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /module-list/common-leafs/name
  // Description: The YANG module or submodule name.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /module-list/common-leafs/revision
  // Description: The YANG module or submodule revision date.
  //              A zero-length string is used if no revision statement
  //              is present in the YANG module or submodule.
  // Type:        ???UNION
  // Units:
  // -----------------------------------------------------------------------------
  LeafRevision revisionInst(ITEM_REVISION);
  addLeaf(revisionInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /module-list/common-leafs/name
// Description: The YANG module or submodule name.
// -----------------------------------------------------------------------------
GrpModuleList::GrpCommonLeafs::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpModuleList::GrpCommonLeafs::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /module-list/common-leafs/revision
// Description: The YANG module or submodule revision date.
//              A zero-length string is used if no revision statement
//              is present in the YANG module or submodule.
// -----------------------------------------------------------------------------
GrpModuleList::GrpCommonLeafs::LeafRevision::LeafRevision(uint32_t id)
    : YangLeaf("revision", id) {}

GrpModuleList::GrpCommonLeafs::LeafRevision::~LeafRevision() {}

// -----------------------------------------------------------------------------
// Grouping:    schema-leaf
// Description: Common schema leaf parameter for modules and submodules.
// -----------------------------------------------------------------------------
GrpModuleList::GrpSchemaLeaf::GrpSchemaLeaf(uint32_t id)
    : YangGroup("schema-leaf", id) {}

GrpModuleList::GrpSchemaLeaf::~GrpSchemaLeaf() {}

YangResult_E
GrpModuleList::GrpSchemaLeaf::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /module-list/schema-leaf/schema
  // Description: Contains a URL that represents the YANG schema
  //              resource for this module or submodule.
  //              This leaf will only be present if there is a URL
  //              available for retrieval of the schema for this entry.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafSchema schemaInst(ITEM_SCHEMA);
  addLeaf(schemaInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /module-list/schema-leaf/schema
// Description: Contains a URL that represents the YANG schema
//              resource for this module or submodule.
//              This leaf will only be present if there is a URL
//              available for retrieval of the schema for this entry.
// -----------------------------------------------------------------------------
GrpModuleList::GrpSchemaLeaf::LeafSchema::LeafSchema(uint32_t id)
    : YangLeaf("schema", id) {}

GrpModuleList::GrpSchemaLeaf::LeafSchema::~LeafSchema() {}

// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************
// -----------------------------------------------------------------------------
// Notification:yang-library-change
// Description: Generated when the set of modules and submodules supported
//              by the server has changed.
// -----------------------------------------------------------------------------
NotifYangLibraryChange::NotifYangLibraryChange(uint32_t id)
    : YangNotif("yang-library-change", id) {}

NotifYangLibraryChange::~NotifYangLibraryChange() {}

YangResult_E
NotifYangLibraryChange::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /yang-library-change/module-set-id
  // Description: Contains the module-set-id value representing the
  //              set of modules and submodules supported at the server at
  //              the time the notification is generated.
  // Ref: /ietf-yang-library:modules-state/ietf-yang-library:module-set-id
  // Units:
  // -----------------------------------------------------------------------------
  RefModuleSetId moduleSetIdInst(ITEM_MODULE_SET_ID);
  addReference(moduleSetIdInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /yang-library-change/module-set-id
// Description: Contains the module-set-id value representing the
//              set of modules and submodules supported at the server at
//              the time the notification is generated.
// -----------------------------------------------------------------------------
NotifYangLibraryChange::RefModuleSetId::RefModuleSetId(uint32_t id)
    : YangReference(
          "module-set-id",
          id,
          "/ietf-yang-library:modules-state/ietf-yang-library:module-set-id") {}

NotifYangLibraryChange::RefModuleSetId::~RefModuleSetId() {}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      ietf-yang-library
// Description: This module contains monitoring information about the YANG
//              modules and submodules that are used within a YANG-based
//              server.
//              Copyright (c) 2016 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 7895; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIetfYangLibrary::ModuleIetfYangLibrary(uint32_t id)
    : YangModule(
          "ietf-yang-library",
          "ietf-yang-library.yang",
          "yanglib",
          "urn:ietf:params:xml:ns:yang:ietf-yang-library",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /modules-state
  // Description: Contains YANG module monitoring information.
  // -----------------------------------------------------------------------------
  CntModulesState modulesStateInst(ITEM_MODULES_STATE);
  modulesStateInst.initialise();
  addContainer(modulesStateInst);

  // -----------------------------------------------------------------------------
  // Notification:/yang-library-change
  // Description: Generated when the set of modules and submodules supported
  //              by the server has changed.
  // -----------------------------------------------------------------------------
  NotifYangLibraryChange yangLibraryChangeInst(ITEM_YANG_LIBRARY_CHANGE);
  yangLibraryChangeInst.initialise();
  addNotification(yangLibraryChangeInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleIetfYangLibrary::~ModuleIetfYangLibrary() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleIetfYangLibrary::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleIetfYangLibrary>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleIetfYangLibrary::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
