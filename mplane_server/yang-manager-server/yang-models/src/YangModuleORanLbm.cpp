/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLbm.cpp
 * \brief     Module ORanLbm interface
 *
 *
 * \details   This file defines the YANG module o-ran-lbm interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-lbm"
 *            YANG Filename:    "o-ran-lbm.yang"
 *            Module Prefix:    "o-ran-lbm"
 *            Module namespace: "urn:o-ran:lbm:1.0"
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
#include "YangModuleORanLbm.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanLbm_NS;

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
// Container:   md-data-definitions
// Description: Data definitions related to the maineance domains used for
// supporting
//              Ethernet loopback connectivity checks
// -----------------------------------------------------------------------------
CntMdDataDefinitions::CntMdDataDefinitions(uint32_t id)
    : YangContainer("md-data-definitions", id) {}

CntMdDataDefinitions::~CntMdDataDefinitions() {}

YangResult_E
CntMdDataDefinitions::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /md-data-definitions/md-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpMdGroup mdGroupInst(ITEM_MD_GROUP);
  mdGroupInst.initialise();
  addGroup(mdGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    md-group
// Description:
// -----------------------------------------------------------------------------
GrpMdGroup::GrpMdGroup(uint32_t id) : YangGroup("md-group", id) {}

GrpMdGroup::~GrpMdGroup() {}

YangResult_E
GrpMdGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /md-group/maintenance-domain
  // Description: A Maintenance Domain managed object is required in order to
  // create an MA
  //              with a MAID that includes that Maintenance Domain's Name. From
  //              this Maintenance Domain managed object, all Maintenance
  //              Association managed objects associated with that Maintenance
  //              Domain managed object can be accessed, and thus controlled.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstMaintenanceDomain maintenanceDomainInst(ITEM_MAINTENANCE_DOMAIN);
  maintenanceDomainInst.initialise();
  addList(maintenanceDomainInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        maintenance-domain
// Description: A Maintenance Domain managed object is required in order to
// create an MA
//              with a MAID that includes that Maintenance Domain's Name. From
//              this Maintenance Domain managed object, all Maintenance
//              Association managed objects associated with that Maintenance
//              Domain managed object can be accessed, and thus controlled.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceDomain(uint32_t id)
    : YangList("maintenance-domain", id) {}

GrpMdGroup::LstMaintenanceDomain::~LstMaintenanceDomain() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /md-group/maintenance-domain/id
  // Description: A unique identifier of a Maintenance Domain
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafId idInst(ITEM_ID);
  addLeaf(idInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /md-group/maintenance-domain/name
  // Description: The value for the Maintenance Domain Name. Only the name-type
  //              'character-string' is supported
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /md-group/maintenance-domain/md-level
  // Description: Integer identifying the Maintenance Domain Level (MD Level).
  // Higher
  //              numbers correspond to higher Maintenance Domains, those with
  //              the greatest physical reach, with the highest values for
  //              customers' CFM PDUs.  Lower numbers correspond to lower
  //              Maintenance Domains, those with more limited physical reach,
  //              with the lowest values for CFM PDUs protecting single bridges
  //              or physical links.
  // Type:        int32
  // Units:
  // -----------------------------------------------------------------------------
  LeafMdLevel mdLevelInst(ITEM_MD_LEVEL);
  addLeaf(mdLevelInst);

  // -----------------------------------------------------------------------------
  // List:        /md-group/maintenance-domain/maintenance-association
  // Description: This list represents Maintenance Entity Groups (Y.1731) or
  //              Maintenance Associations (802.1ag). MEGs/MAs are sets of
  //              MEPs, each configured to the same service inside a common
  //              OAM domain.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstMaintenanceAssociation maintenanceAssociationInst(
      ITEM_MAINTENANCE_ASSOCIATION);
  maintenanceAssociationInst.initialise();
  addList(maintenanceAssociationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /md-group/maintenance-domain/id
// Description: A unique identifier of a Maintenance Domain
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LeafId::LeafId(uint32_t id)
    : YangLeaf("id", id) {}

GrpMdGroup::LstMaintenanceDomain::LeafId::~LeafId() {}

// -----------------------------------------------------------------------------
// Leaf:        /md-group/maintenance-domain/name
// Description: The value for the Maintenance Domain Name. Only the name-type
//              'character-string' is supported
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpMdGroup::LstMaintenanceDomain::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /md-group/maintenance-domain/md-level
// Description: Integer identifying the Maintenance Domain Level (MD Level).
// Higher
//              numbers correspond to higher Maintenance Domains, those with the
//              greatest physical reach, with the highest values for customers'
//              CFM PDUs.  Lower numbers correspond to lower Maintenance
//              Domains, those with more limited physical reach, with the lowest
//              values for CFM PDUs protecting single bridges or physical links.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LeafMdLevel::LeafMdLevel(uint32_t id)
    : YangLeaf("md-level", id) {}

GrpMdGroup::LstMaintenanceDomain::LeafMdLevel::~LeafMdLevel() {}

// -----------------------------------------------------------------------------
// List:        maintenance-association
// Description: This list represents Maintenance Entity Groups (Y.1731) or
//              Maintenance Associations (802.1ag). MEGs/MAs are sets of
//              MEPs, each configured to the same service inside a common
//              OAM domain.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::
    LstMaintenanceAssociation(uint32_t id)
    : YangList("maintenance-association", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::
    ~LstMaintenanceAssociation() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /md-group/maintenance-domain/maintenance-association/id
  // Description: A unique identifier of a Maintenance Association
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafId idInst(ITEM_ID);
  addLeaf(idInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /md-group/maintenance-domain/maintenance-association/name
  // Description: The value for the Maintenance Association Name. Only the
  // name-type
  //              'character-string' is supported
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // List: /md-group/maintenance-domain/maintenance-association/component-list
  // Description: A list of components each of which can be managed in a manner
  //              essentially equivalent to an 802.1Q bridge.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstComponentList componentListInst(ITEM_COMPONENT_LIST);
  componentListInst.initialise();
  addList(componentListInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /md-group/maintenance-domain/maintenance-association/id
// Description: A unique identifier of a Maintenance Association
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LeafId::LeafId(
    uint32_t id)
    : YangLeaf("id", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LeafId::~LeafId() {
}

// -----------------------------------------------------------------------------
// Leaf:        /md-group/maintenance-domain/maintenance-association/name
// Description: The value for the Maintenance Association Name. Only the
// name-type
//              'character-string' is supported
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LeafName::LeafName(
    uint32_t id)
    : YangLeaf("name", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LeafName::
    ~LeafName() {}

// -----------------------------------------------------------------------------
// List:        component-list
// Description: A list of components each of which can be managed in a manner
//              essentially equivalent to an 802.1Q bridge.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstComponentList(uint32_t id)
    : YangList("component-list", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    ~LstComponentList() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /md-group/maintenance-domain/maintenance-association/component-list/component-id
  // Description: The bridge component within the system to which the
  // information
  //              in this maintenance-association applies
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafComponentId componentIdInst(ITEM_COMPONENT_ID);
  addLeaf(componentIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /md-group/maintenance-domain/maintenance-association/component-list/name
  // Description: The value for the Maintenance Association Name. Only the
  // name-type
  //              'character-string' is supported
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // List:
  // /md-group/maintenance-domain/maintenance-association/component-list/vid
  // Description: The VID(s) monitored by this MA, or 0, if the MA is not
  // attached to any
  //              VID. The first VID returned is the MA's Primary VID
  // Array Key:
  // -----------------------------------------------------------------------------
  LstVid vidInst(ITEM_VID);
  vidInst.initialise();
  addList(vidInst);

  // -----------------------------------------------------------------------------
  // List:
  // /md-group/maintenance-domain/maintenance-association/component-list/remote-meps
  // Description: A list of the MEPIDs of the MEPs in the MA.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstRemoteMeps remoteMepsInst(ITEM_REMOTE_MEPS);
  remoteMepsInst.initialise();
  addList(remoteMepsInst);

  // -----------------------------------------------------------------------------
  // List:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point
  // Description: The list of Maintenance association End Points in a specific
  // Maintance
  //              Association.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstMaintenanceAssociationEndPoint maintenanceAssociationEndPointInst(
      ITEM_MAINTENANCE_ASSOCIATION_END_POINT);
  maintenanceAssociationEndPointInst.initialise();
  addList(maintenanceAssociationEndPointInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /md-group/maintenance-domain/maintenance-association/component-list/component-id
// Description: The bridge component within the system to which the information
//              in this maintenance-association applies
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LeafComponentId::LeafComponentId(uint32_t id)
    : YangLeaf("component-id", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LeafComponentId::~LeafComponentId() {}

// -----------------------------------------------------------------------------
// Leaf:
// /md-group/maintenance-domain/maintenance-association/component-list/name
// Description: The value for the Maintenance Association Name. Only the
// name-type
//              'character-string' is supported
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// List:        vid
// Description: The VID(s) monitored by this MA, or 0, if the MA is not attached
// to any
//              VID. The first VID returned is the MA's Primary VID
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstVid::LstVid(uint32_t id)
    : YangList("vid", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstVid::~LstVid() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstVid::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        remote-meps
// Description: A list of the MEPIDs of the MEPs in the MA.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstRemoteMeps::LstRemoteMeps(uint32_t id)
    : YangList("remote-meps", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstRemoteMeps::~LstRemoteMeps() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstRemoteMeps::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        maintenance-association-end-point
// Description: The list of Maintenance association End Points in a specific
// Maintance
//              Association.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::LstMaintenanceAssociationEndPoint(
        uint32_t id)
    : YangList("maintenance-association-end-point", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::~LstMaintenanceAssociationEndPoint() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mep-identifier
  // Description: Integer that is unique among all the MEPs in the same MA.
  // Other
  //              definition is: a small integer, unique over a given
  //              Maintenance Association, identifying a specific Maintenance
  //              association End Point.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafMepIdentifier mepIdentifierInst(ITEM_MEP_IDENTIFIER);
  addLeaf(mepIdentifierInst);

  // -----------------------------------------------------------------------------
  // Leaf:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/administrative-state
  // Description: The administrative state of the MEP
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafAdministrativeState administrativeStateInst(ITEM_ADMINISTRATIVE_STATE);
  addLeaf(administrativeStateInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/interface
  // Description: An interface, either a Bridge Port or an aggregated IEEE 802.3
  // port
  //              within a Bridge Port, to which the MEP is attached. Each
  //              interface in the system is uniquely identified by an
  //              interface-name. The structure and content of the name is
  //              outside the scope of this specification.
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/ietf-interfaces:name
  // Units:
  // -----------------------------------------------------------------------------
  RefInterface interfaceInst(ITEM_INTERFACE);
  addReference(interfaceInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/primary-vid
  // Description: The Primary VID of the MEP. The value 0 indicates that either
  // the
  //              Primary VID is that of the MEP's MA or that the MEP's MA is
  //              associated with no VID
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:vlan-id
  // Units:
  // -----------------------------------------------------------------------------
  RefPrimaryVid primaryVidInst(ITEM_PRIMARY_VID);
  addReference(primaryVidInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mac-address
  // Description: The MAC address of the MEP
  // Ref:
  // /ietf-interfaces:interfaces/ietf-interfaces:interface/o-ran-interfaces:mac-address
  // Units:
  // -----------------------------------------------------------------------------
  RefMacAddress macAddressInst(ITEM_MAC_ADDRESS);
  addReference(macAddressInst);

  // -----------------------------------------------------------------------------
  // Container:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/loopback
  // Description: Data definitions related to the Loopback function.
  // -----------------------------------------------------------------------------
  CntLoopback loopbackInst(ITEM_LOOPBACK);
  loopbackInst.initialise();
  addContainer(loopbackInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mep-identifier
// Description: Integer that is unique among all the MEPs in the same MA. Other
//              definition is: a small integer, unique over a given
//              Maintenance Association, identifying a specific Maintenance
//              association End Point.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::LeafMepIdentifier::LeafMepIdentifier(
        uint32_t id)
    : YangLeaf("mep-identifier", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::LeafMepIdentifier::~LeafMepIdentifier() {
}

// -----------------------------------------------------------------------------
// Leaf:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/administrative-state
// Description: The administrative state of the MEP
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::LeafAdministrativeState::
        LeafAdministrativeState(uint32_t id)
    : YangLeaf("administrative-state", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::LeafAdministrativeState::
        ~LeafAdministrativeState() {}

// -----------------------------------------------------------------------------
// Reference:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/interface
// Description: An interface, either a Bridge Port or an aggregated IEEE 802.3
// port
//              within a Bridge Port, to which the MEP is attached. Each
//              interface in the system is uniquely identified by an
//              interface-name. The structure and content of the name is outside
//              the scope of this specification.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefInterface::RefInterface(uint32_t id)
    : YangReference(
          "interface",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "ietf-interfaces:name") {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefInterface::~RefInterface() {}

// -----------------------------------------------------------------------------
// Reference:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/primary-vid
// Description: The Primary VID of the MEP. The value 0 indicates that either
// the
//              Primary VID is that of the MEP's MA or that the MEP's MA is
//              associated with no VID
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefPrimaryVid::RefPrimaryVid(uint32_t id)
    : YangReference(
          "primary-vid",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "o-ran-interfaces:vlan-id") {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefPrimaryVid::~RefPrimaryVid() {}

// -----------------------------------------------------------------------------
// Reference:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mac-address
// Description: The MAC address of the MEP
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefMacAddress::RefMacAddress(uint32_t id)
    : YangReference(
          "mac-address",
          id,
          "/ietf-interfaces:interfaces/ietf-interfaces:interface/"
          "o-ran-interfaces:mac-address") {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::RefMacAddress::~RefMacAddress() {}

// -----------------------------------------------------------------------------
// Container:   loopback
// Description: Data definitions related to the Loopback function.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::CntLoopback::CntLoopback(uint32_t id)
    : YangContainer("loopback", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::CntLoopback::~CntLoopback() {}

YangResult_E
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::CntLoopback::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/loopback/replies-transmitted
  // Description: The total number of LBRs transmitted.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafRepliesTransmitted repliesTransmittedInst(ITEM_REPLIES_TRANSMITTED);
  addLeaf(repliesTransmittedInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/loopback/replies-transmitted
// Description: The total number of LBRs transmitted.
// -----------------------------------------------------------------------------
GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::CntLoopback::LeafRepliesTransmitted::
        LeafRepliesTransmitted(uint32_t id)
    : YangLeaf("replies-transmitted", id) {}

GrpMdGroup::LstMaintenanceDomain::LstMaintenanceAssociation::LstComponentList::
    LstMaintenanceAssociationEndPoint::CntLoopback::LeafRepliesTransmitted::
        ~LeafRepliesTransmitted() {}

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
// Module:      o-ran-lbm
// Description: This module defines the module capabilities for
//              the O-RAN Radio loop-back protocol (IEEE 802.1ag).
//              It is derived from MEF-38 (Service OAM Fault Management YANG
//              Modules, April 2012)
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//              CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
//              INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//              MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//              DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//              CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
//              USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//              AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//              LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//              IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//              THE POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following
//              conditions are met:
//
//              * Redistributions of source code must retain the above copyright
//              notice, this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above
//              copyright notice, this list of conditions and the above
//              disclaimer in the documentation and/or other materials provided
//              with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived
//              from this software without specific prior written permission.
// -----------------------------------------------------------------------------
ModuleORanLbm::ModuleORanLbm(uint32_t id)
    : YangModule(
          "o-ran-lbm", "o-ran-lbm.yang", "o-ran-lbm", "urn:o-ran:lbm:1.0", id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /md-data-definitions
  // Description: Data definitions related to the maineance domains used for
  // supporting
  //              Ethernet loopback connectivity checks
  // -----------------------------------------------------------------------------
  CntMdDataDefinitions mdDataDefinitionsInst(ITEM_MD_DATA_DEFINITIONS);
  mdDataDefinitionsInst.initialise();
  addContainer(mdDataDefinitionsInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanLbm::~ModuleORanLbm() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanLbm::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanLbm>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanLbm::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
