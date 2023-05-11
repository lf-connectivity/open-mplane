/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfNetconfMonitoring.cpp
 * \brief     Module IetfNetconfMonitoring interface
 *
 *
 * \details   This file defines the YANG module ietf-netconf-monitoring
 interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-netconf-monitoring"
 *            YANG Filename:    "ietf-netconf-monitoring.yang"
 *            Module Prefix:    "ncm"
 *            Module namespace:
 "urn:ietf:params:xml:ns:yang:ietf-netconf-monitoring"
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
#include "YangModuleIetfNetconfMonitoring.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleIetfNetconfMonitoring_NS;

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
// Container:   netconf-state
// Description: The netconf-state container is the root of the monitoring
//              data model.
// -----------------------------------------------------------------------------
CntNetconfState::CntNetconfState(uint32_t id)
    : YangContainer("netconf-state", id) {}

CntNetconfState::~CntNetconfState() {}

YangResult_E
CntNetconfState::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/capabilities
  // Description: Contains the list of NETCONF capabilities supported by the
  //              server.
  // -----------------------------------------------------------------------------
  CntCapabilities capabilitiesInst(ITEM_CAPABILITIES);
  capabilitiesInst.initialise();
  addContainer(capabilitiesInst);

  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/datastores
  // Description: Contains the list of NETCONF configuration datastores.
  // -----------------------------------------------------------------------------
  CntDatastores datastoresInst(ITEM_DATASTORES);
  datastoresInst.initialise();
  addContainer(datastoresInst);

  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/schemas
  // Description: Contains the list of data model schemas supported by the
  //              server.
  // -----------------------------------------------------------------------------
  CntSchemas schemasInst(ITEM_SCHEMAS);
  schemasInst.initialise();
  addContainer(schemasInst);

  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/sessions
  // Description: The sessions container includes session-specific data for
  //              NETCONF management sessions.  The session list MUST include
  //              all currently active NETCONF sessions.
  // -----------------------------------------------------------------------------
  CntSessions sessionsInst(ITEM_SESSIONS);
  sessionsInst.initialise();
  addContainer(sessionsInst);

  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/statistics
  // Description: Statistical data pertaining to the NETCONF server.
  // -----------------------------------------------------------------------------
  CntStatistics statisticsInst(ITEM_STATISTICS);
  statisticsInst.initialise();
  addContainer(statisticsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   capabilities
// Description: Contains the list of NETCONF capabilities supported by the
//              server.
// -----------------------------------------------------------------------------
CntNetconfState::CntCapabilities::CntCapabilities(uint32_t id)
    : YangContainer("capabilities", id) {}

CntNetconfState::CntCapabilities::~CntCapabilities() {}

YangResult_E
CntNetconfState::CntCapabilities::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /netconf-state/capabilities/capability
  // Description: List of NETCONF capabilities supported by the server.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstCapability capabilityInst(ITEM_CAPABILITY);
  capabilityInst.initialise();
  addList(capabilityInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        capability
// Description: List of NETCONF capabilities supported by the server.
// -----------------------------------------------------------------------------
CntNetconfState::CntCapabilities::LstCapability::LstCapability(uint32_t id)
    : YangList("capability", id) {}

CntNetconfState::CntCapabilities::LstCapability::~LstCapability() {}

YangResult_E
CntNetconfState::CntCapabilities::LstCapability::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   datastores
// Description: Contains the list of NETCONF configuration datastores.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::CntDatastores(uint32_t id)
    : YangContainer("datastores", id) {}

CntNetconfState::CntDatastores::~CntDatastores() {}

YangResult_E
CntNetconfState::CntDatastores::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /netconf-state/datastores/datastore
  // Description: List of NETCONF configuration datastores supported by
  //              the NETCONF server and related information.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstDatastore datastoreInst(ITEM_DATASTORE);
  datastoreInst.initialise();
  addList(datastoreInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        datastore
// Description: List of NETCONF configuration datastores supported by
//              the NETCONF server and related information.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::LstDatastore(uint32_t id)
    : YangList("datastore", id) {}

CntNetconfState::CntDatastores::LstDatastore::~LstDatastore() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/datastores/datastore/name
  // Description: Name of the datastore associated with this list entry.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Container:   /netconf-state/datastores/datastore/locks
  // Description: The NETCONF <lock> and <partial-lock> operations allow
  //              a client to lock specific resources in a datastore.  The
  //              NETCONF server will prevent changes to the locked
  //              resources by all sessions except the one that acquired
  //              the lock(s).
  //              Monitoring information is provided for each datastore
  //              entry including details such as the session that acquired
  //              the lock, the type of lock (global or partial) and the
  //              list of locked resources.  Multiple locks per datastore
  //              are supported.
  // -----------------------------------------------------------------------------
  CntLocks locksInst(ITEM_LOCKS);
  locksInst.initialise();
  addContainer(locksInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/datastores/datastore/name
// Description: Name of the datastore associated with this list entry.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

CntNetconfState::CntDatastores::LstDatastore::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Container:   locks
// Description: The NETCONF <lock> and <partial-lock> operations allow
//              a client to lock specific resources in a datastore.  The
//              NETCONF server will prevent changes to the locked
//              resources by all sessions except the one that acquired
//              the lock(s).
//              Monitoring information is provided for each datastore
//              entry including details such as the session that acquired
//              the lock, the type of lock (global or partial) and the
//              list of locked resources.  Multiple locks per datastore
//              are supported.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::CntLocks(uint32_t id)
    : YangContainer("locks", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::~CntLocks() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::initialise(void) {
  // -----------------------------------------------------------------------------
  // Choice:      /netconf-state/datastores/datastore/locks/lock-type
  // Description: Indicates if a global lock or a set of partial locks
  //              are set.
  // Type:        LockType_E
  // Units:       -
  // -----------------------------------------------------------------------------
  ChoiceLockType lockTypeInst(ITEM_LOCK_TYPE);
  lockTypeInst.initialise();
  addChoice(lockTypeInst);

  // -----------------------------------------------------------------------------
  // Grouping:    /netconf-state/datastores/datastore/locks/lock-info
  // Description: Lock related parameters, common to both global and
  //              partial locks.
  // -----------------------------------------------------------------------------
  GrpLockInfo lockInfoInst(ITEM_LOCK_INFO);
  lockInfoInst.initialise();
  addGroup(lockInfoInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Choice:      lock-type
// Description: Indicates if a global lock or a set of partial locks
//              are set.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    ChoiceLockType(uint32_t id)
    : YangChoice("lock-type", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    ~ChoiceLockType() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    initialise(void) {

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptGlobalLock globalLock(ITEM_GLOBAL_LOCK);
  globalLock.initialise();
  addOption(globalLock);

  // -------------------------------------------------------------------------
  // Option:       array-choice/antenna-type[tx]
  // Description:  Leafref to tx array if such is chosen
  // -------------------------------------------------------------------------
  OptPartialLock partialLock(ITEM_PARTIAL_LOCK);
  partialLock.initialise();
  addOption(partialLock);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option:      /netconf-state/datastores/datastore/locks/lock-type[global-lock]
// -------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::OptGlobalLock(uint32_t id)
    : YangChoiceOption("global-lock", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::~OptGlobalLock() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:
  // /netconf-state/datastores/datastore/locks/lock-type[global-lock]/global-lock
  // Description: Present if the global lock is set.
  // -----------------------------------------------------------------------------
  CntGlobalLock globalLockInst(ITEM_GLOBAL_LOCK);
  globalLockInst.initialise();
  addContainer(globalLockInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   global-lock
// Description: Present if the global lock is set.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::CntGlobalLock::CntGlobalLock(uint32_t id)
    : YangContainer("global-lock", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::CntGlobalLock::~CntGlobalLock() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptGlobalLock::CntGlobalLock::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:
  // /netconf-state/datastores/datastore/locks/lock-type[global-lock]/global-lock/lock-info
  // Description:
  // -----------------------------------------------------------------------------
  CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo
      lockInfoInst(ITEM_LOCK_INFO);
  lockInfoInst.initialise();
  addGroup(lockInfoInst);

  return YangResult_E::OK;
}

// -------------------------------------------------------------------------
// Option: /netconf-state/datastores/datastore/locks/lock-type[partial-lock]
// -------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::OptPartialLock(uint32_t id)
    : YangChoiceOption("partial-lock", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::~OptPartialLock() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:
  // /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock
  // Description: List of partial locks.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstPartialLock partialLockInst(ITEM_PARTIAL_LOCK);
  partialLockInst.initialise();
  addList(partialLockInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        partial-lock
// Description: List of partial locks.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstPartialLock(uint32_t id)
    : YangList("partial-lock", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::~LstPartialLock() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:
  // /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/lock-id
  // Description: This is the lock id returned in the <partial-lock>
  //              response.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafLockId lockIdInst(ITEM_LOCK_ID);
  addLeaf(lockIdInst);

  // -----------------------------------------------------------------------------
  // List:
  // /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/select
  // Description: The xpath expression that was used to request
  //              the lock.  The select expression indicates the
  //              original intended scope of the lock.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSelect selectInst(ITEM_SELECT);
  selectInst.initialise();
  addList(selectInst);

  // -----------------------------------------------------------------------------
  // List:
  // /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/locked-node
  // Description: The list of instance-identifiers (i.e., the
  //              locked nodes).
  //              The scope of the partial lock is defined by the list
  //              of locked nodes.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstLockedNode lockedNodeInst(ITEM_LOCKED_NODE);
  lockedNodeInst.initialise();
  addList(lockedNodeInst);

  // -----------------------------------------------------------------------------
  // Uses:
  // /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/lock-info
  // Description:
  // -----------------------------------------------------------------------------
  CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo
      lockInfoInst(ITEM_LOCK_INFO);
  lockInfoInst.initialise();
  addGroup(lockInfoInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:
// /netconf-state/datastores/datastore/locks/lock-type[partial-lock]/partial-lock/lock-id
// Description: This is the lock id returned in the <partial-lock>
//              response.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LeafLockId::LeafLockId(uint32_t id)
    : YangLeaf("lock-id", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LeafLockId::~LeafLockId() {}

// -----------------------------------------------------------------------------
// List:        select
// Description: The xpath expression that was used to request
//              the lock.  The select expression indicates the
//              original intended scope of the lock.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstSelect::LstSelect(uint32_t id)
    : YangList("select", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstSelect::~LstSelect() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstSelect::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        locked-node
// Description: The list of instance-identifiers (i.e., the
//              locked nodes).
//              The scope of the partial lock is defined by the list
//              of locked nodes.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstLockedNode::LstLockedNode(uint32_t id)
    : YangList("locked-node", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstLockedNode::~LstLockedNode() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::ChoiceLockType::
    OptPartialLock::LstPartialLock::LstLockedNode::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    lock-info
// Description: Lock related parameters, common to both global and
//              partial locks.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    GrpLockInfo(uint32_t id)
    : YangGroup("lock-info", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    ~GrpLockInfo() {}

YangResult_E
CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Leaf: /netconf-state/datastores/datastore/locks/lock-info/locked-by-session
  // Description: The session ID of the session that has locked
  //              this resource.  Both a global lock and a partial
  //              lock MUST contain the NETCONF session-id.
  //              If the lock is held by a session that is not managed
  //              by the NETCONF server (e.g., a CLI session), a session
  //              id of 0 (zero) is reported.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafLockedBySession lockedBySessionInst(ITEM_LOCKED_BY_SESSION);
  addLeaf(lockedBySessionInst);

  // -----------------------------------------------------------------------------
  // Leaf: /netconf-state/datastores/datastore/locks/lock-info/locked-time
  // Description: The date and time of when the resource was
  //              locked.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLockedTime lockedTimeInst(ITEM_LOCKED_TIME);
  addLeaf(lockedTimeInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf: /netconf-state/datastores/datastore/locks/lock-info/locked-by-session
// Description: The session ID of the session that has locked
//              this resource.  Both a global lock and a partial
//              lock MUST contain the NETCONF session-id.
//              If the lock is held by a session that is not managed
//              by the NETCONF server (e.g., a CLI session), a session
//              id of 0 (zero) is reported.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    LeafLockedBySession::LeafLockedBySession(uint32_t id)
    : YangLeaf("locked-by-session", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    LeafLockedBySession::~LeafLockedBySession() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/datastores/datastore/locks/lock-info/locked-time
// Description: The date and time of when the resource was
//              locked.
// -----------------------------------------------------------------------------
CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    LeafLockedTime::LeafLockedTime(uint32_t id)
    : YangLeaf("locked-time", id) {}

CntNetconfState::CntDatastores::LstDatastore::CntLocks::GrpLockInfo::
    LeafLockedTime::~LeafLockedTime() {}

// -----------------------------------------------------------------------------
// Container:   schemas
// Description: Contains the list of data model schemas supported by the
//              server.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::CntSchemas(uint32_t id)
    : YangContainer("schemas", id) {}

CntNetconfState::CntSchemas::~CntSchemas() {}

YangResult_E
CntNetconfState::CntSchemas::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /netconf-state/schemas/schema
  // Description: List of data model schemas supported by the server.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSchema schemaInst(ITEM_SCHEMA);
  schemaInst.initialise();
  addList(schemaInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        schema
// Description: List of data model schemas supported by the server.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LstSchema(uint32_t id)
    : YangList("schema", id) {}

CntNetconfState::CntSchemas::LstSchema::~LstSchema() {}

YangResult_E
CntNetconfState::CntSchemas::LstSchema::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/schemas/schema/identifier
  // Description: Identifier to uniquely reference the schema.  The
  //              identifier is used in the <get-schema> operation and may
  //              be used for other purposes such as file retrieval.
  //              For modeling languages that support or require a data
  //              model name (e.g., YANG module name) the identifier MUST
  //              match that name.  For YANG data models, the identifier is
  //              the name of the module or submodule.  In other cases, an
  //              identifier such as a filename MAY be used instead.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafIdentifier identifierInst(ITEM_IDENTIFIER);
  addLeaf(identifierInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/schemas/schema/version
  // Description: Version of the schema supported.  Multiple versions MAY be
  //              supported simultaneously by a NETCONF server.  Each
  //              version MUST be reported individually in the schema list,
  //              i.e., with same identifier, possibly different location,
  //              but different version.
  //              For YANG data models, version is the value of the most
  //              recent YANG 'revision' statement in the module or
  //              submodule, or the empty string if no 'revision' statement
  //              is present.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafVersion versionInst(ITEM_VERSION);
  addLeaf(versionInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/schemas/schema/format
  // Description: The data modeling language the schema is written
  //              in (currently xsd, yang, yin, rng, or rnc).
  //              For YANG data models, 'yang' format MUST be supported and
  //              'yin' format MAY also be provided.
  // Type:        ???IDENT
  // Units:
  // -----------------------------------------------------------------------------
  LeafFormat formatInst(ITEM_FORMAT);
  addLeaf(formatInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/schemas/schema/namespace
  // Description: The XML namespace defined by the data model.
  //              For YANG data models, this is the module's namespace.
  //              If the list entry describes a submodule, this field
  //              contains the namespace of the module to which the
  //              submodule belongs.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafNamespace namespaceInst(ITEM_NAMESPACE);
  addLeaf(namespaceInst);

  // -----------------------------------------------------------------------------
  // List:        /netconf-state/schemas/schema/location
  // Description: One or more locations from which the schema can be
  //              retrieved.  This list SHOULD contain at least one
  //              entry per schema.
  //              A schema entry may be located on a remote file system
  //              (e.g., reference to file system for ftp retrieval) or
  //              retrieved directly from a server supporting the
  //              <get-schema> operation (denoted by the value 'NETCONF').
  // Array Key:
  // -----------------------------------------------------------------------------
  LstLocation locationInst(ITEM_LOCATION);
  locationInst.initialise();
  addList(locationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/schemas/schema/identifier
// Description: Identifier to uniquely reference the schema.  The
//              identifier is used in the <get-schema> operation and may
//              be used for other purposes such as file retrieval.
//              For modeling languages that support or require a data
//              model name (e.g., YANG module name) the identifier MUST
//              match that name.  For YANG data models, the identifier is
//              the name of the module or submodule.  In other cases, an
//              identifier such as a filename MAY be used instead.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LeafIdentifier::LeafIdentifier(
    uint32_t id)
    : YangLeaf("identifier", id) {}

CntNetconfState::CntSchemas::LstSchema::LeafIdentifier::~LeafIdentifier() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/schemas/schema/version
// Description: Version of the schema supported.  Multiple versions MAY be
//              supported simultaneously by a NETCONF server.  Each
//              version MUST be reported individually in the schema list,
//              i.e., with same identifier, possibly different location,
//              but different version.
//              For YANG data models, version is the value of the most
//              recent YANG 'revision' statement in the module or
//              submodule, or the empty string if no 'revision' statement
//              is present.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LeafVersion::LeafVersion(uint32_t id)
    : YangLeaf("version", id) {}

CntNetconfState::CntSchemas::LstSchema::LeafVersion::~LeafVersion() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/schemas/schema/format
// Description: The data modeling language the schema is written
//              in (currently xsd, yang, yin, rng, or rnc).
//              For YANG data models, 'yang' format MUST be supported and
//              'yin' format MAY also be provided.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LeafFormat::LeafFormat(uint32_t id)
    : YangLeaf("format", id) {}

CntNetconfState::CntSchemas::LstSchema::LeafFormat::~LeafFormat() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/schemas/schema/namespace
// Description: The XML namespace defined by the data model.
//              For YANG data models, this is the module's namespace.
//              If the list entry describes a submodule, this field
//              contains the namespace of the module to which the
//              submodule belongs.
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LeafNamespace::LeafNamespace(
    uint32_t id)
    : YangLeaf("namespace", id) {}

CntNetconfState::CntSchemas::LstSchema::LeafNamespace::~LeafNamespace() {}

// -----------------------------------------------------------------------------
// List:        location
// Description: One or more locations from which the schema can be
//              retrieved.  This list SHOULD contain at least one
//              entry per schema.
//              A schema entry may be located on a remote file system
//              (e.g., reference to file system for ftp retrieval) or
//              retrieved directly from a server supporting the
//              <get-schema> operation (denoted by the value 'NETCONF').
// -----------------------------------------------------------------------------
CntNetconfState::CntSchemas::LstSchema::LstLocation::LstLocation(uint32_t id)
    : YangList("location", id) {}

CntNetconfState::CntSchemas::LstSchema::LstLocation::~LstLocation() {}

YangResult_E
CntNetconfState::CntSchemas::LstSchema::LstLocation::initialise(void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   sessions
// Description: The sessions container includes session-specific data for
//              NETCONF management sessions.  The session list MUST include
//              all currently active NETCONF sessions.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::CntSessions(uint32_t id)
    : YangContainer("sessions", id) {}

CntNetconfState::CntSessions::~CntSessions() {}

YangResult_E
CntNetconfState::CntSessions::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /netconf-state/sessions/session
  // Description: All NETCONF sessions managed by the NETCONF server
  //              MUST be reported in this list.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstSession sessionInst(ITEM_SESSION);
  sessionInst.initialise();
  addList(sessionInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        session
// Description: All NETCONF sessions managed by the NETCONF server
//              MUST be reported in this list.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LstSession(uint32_t id)
    : YangList("session", id) {}

CntNetconfState::CntSessions::LstSession::~LstSession() {}

YangResult_E
CntNetconfState::CntSessions::LstSession::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/sessions/session/session-id
  // Description: Unique identifier for the session.  This value is the
  //              NETCONF session identifier, as defined in RFC 4741.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafSessionId sessionIdInst(ITEM_SESSION_ID);
  addLeaf(sessionIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/sessions/session/transport
  // Description: Identifies the transport for each session, e.g.,
  //              'netconf-ssh', 'netconf-soap', etc.
  // Type:        ???IDENT
  // Units:
  // -----------------------------------------------------------------------------
  LeafTransport transportInst(ITEM_TRANSPORT);
  addLeaf(transportInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/sessions/session/username
  // Description: The username is the client identity that was authenticated
  //              by the NETCONF transport protocol.  The algorithm used to
  //              derive the username is NETCONF transport protocol specific
  //              and in addition specific to the authentication mechanism
  //              used by the NETCONF transport protocol.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafUsername usernameInst(ITEM_USERNAME);
  addLeaf(usernameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/sessions/session/source-host
  // Description: Host identifier of the NETCONF client.  The value
  //              returned is implementation specific (e.g., hostname,
  //              IPv4 address, IPv6 address)
  // Type:        ???UNION
  // Units:
  // -----------------------------------------------------------------------------
  LeafSourceHost sourceHostInst(ITEM_SOURCE_HOST);
  addLeaf(sourceHostInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/sessions/session/login-time
  // Description: Time at the server at which the session was established.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafLoginTime loginTimeInst(ITEM_LOGIN_TIME);
  addLeaf(loginTimeInst);

  // -----------------------------------------------------------------------------
  // Uses:        /netconf-state/sessions/session/common-counters
  // Description: Per-session counters.  Zero based with following reset
  //              behaviour:
  //                - at start of a session
  //                - when max value is reached
  // -----------------------------------------------------------------------------
  GrpCommonCounters commonCountersInst(ITEM_COMMON_COUNTERS);
  commonCountersInst.initialise();
  addGroup(commonCountersInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/sessions/session/session-id
// Description: Unique identifier for the session.  This value is the
//              NETCONF session identifier, as defined in RFC 4741.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LeafSessionId::LeafSessionId(
    uint32_t id)
    : YangLeaf("session-id", id) {}

CntNetconfState::CntSessions::LstSession::LeafSessionId::~LeafSessionId() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/sessions/session/transport
// Description: Identifies the transport for each session, e.g.,
//              'netconf-ssh', 'netconf-soap', etc.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LeafTransport::LeafTransport(
    uint32_t id)
    : YangLeaf("transport", id) {}

CntNetconfState::CntSessions::LstSession::LeafTransport::~LeafTransport() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/sessions/session/username
// Description: The username is the client identity that was authenticated
//              by the NETCONF transport protocol.  The algorithm used to
//              derive the username is NETCONF transport protocol specific
//              and in addition specific to the authentication mechanism
//              used by the NETCONF transport protocol.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LeafUsername::LeafUsername(
    uint32_t id)
    : YangLeaf("username", id) {}

CntNetconfState::CntSessions::LstSession::LeafUsername::~LeafUsername() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/sessions/session/source-host
// Description: Host identifier of the NETCONF client.  The value
//              returned is implementation specific (e.g., hostname,
//              IPv4 address, IPv6 address)
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LeafSourceHost::LeafSourceHost(
    uint32_t id)
    : YangLeaf("source-host", id) {}

CntNetconfState::CntSessions::LstSession::LeafSourceHost::~LeafSourceHost() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/sessions/session/login-time
// Description: Time at the server at which the session was established.
// -----------------------------------------------------------------------------
CntNetconfState::CntSessions::LstSession::LeafLoginTime::LeafLoginTime(
    uint32_t id)
    : YangLeaf("login-time", id) {}

CntNetconfState::CntSessions::LstSession::LeafLoginTime::~LeafLoginTime() {}

// -----------------------------------------------------------------------------
// Container:   statistics
// Description: Statistical data pertaining to the NETCONF server.
// -----------------------------------------------------------------------------
CntNetconfState::CntStatistics::CntStatistics(uint32_t id)
    : YangContainer("statistics", id) {}

CntNetconfState::CntStatistics::~CntStatistics() {}

YangResult_E
CntNetconfState::CntStatistics::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/statistics/netconf-start-time
  // Description: Date and time at which the management subsystem was
  //              started.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafNetconfStartTime netconfStartTimeInst(ITEM_NETCONF_START_TIME);
  addLeaf(netconfStartTimeInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/statistics/in-bad-hellos
  // Description: Number of sessions silently dropped because an
  //              invalid <hello> message was received.  This includes <hello>
  //              messages with a 'session-id' attribute, bad namespace, and
  //              bad capability declarations.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafInBadHellos inBadHellosInst(ITEM_IN_BAD_HELLOS);
  addLeaf(inBadHellosInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/statistics/in-sessions
  // Description: Number of sessions started.  This counter is incremented
  //              when a <hello> message with a <session-id> is sent.
  //              'in-sessions' - 'in-bad-hellos' =
  //                 'number of correctly started netconf sessions'
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafInSessions inSessionsInst(ITEM_IN_SESSIONS);
  addLeaf(inSessionsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /netconf-state/statistics/dropped-sessions
  // Description: Number of sessions that were abnormally terminated, e.g.,
  //              due to idle timeout or transport close.  This counter is not
  //              incremented when a session is properly closed by a
  //              <close-session> operation, or killed by a <kill-session>
  //              operation.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafDroppedSessions droppedSessionsInst(ITEM_DROPPED_SESSIONS);
  addLeaf(droppedSessionsInst);

  // -----------------------------------------------------------------------------
  // Uses:        /netconf-state/statistics/common-counters
  // Description: Global counters, accumulated from all sessions.
  //              Zero based with following reset behaviour:
  //                - re-initialization of NETCONF server
  //                - when max value is reached
  // -----------------------------------------------------------------------------
  GrpCommonCounters commonCountersInst(ITEM_COMMON_COUNTERS);
  commonCountersInst.initialise();
  addGroup(commonCountersInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/statistics/netconf-start-time
// Description: Date and time at which the management subsystem was
//              started.
// -----------------------------------------------------------------------------
CntNetconfState::CntStatistics::LeafNetconfStartTime::LeafNetconfStartTime(
    uint32_t id)
    : YangLeaf("netconf-start-time", id) {}

CntNetconfState::CntStatistics::LeafNetconfStartTime::~LeafNetconfStartTime() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/statistics/in-bad-hellos
// Description: Number of sessions silently dropped because an
//              invalid <hello> message was received.  This includes <hello>
//              messages with a 'session-id' attribute, bad namespace, and
//              bad capability declarations.
// -----------------------------------------------------------------------------
CntNetconfState::CntStatistics::LeafInBadHellos::LeafInBadHellos(uint32_t id)
    : YangLeaf("in-bad-hellos", id) {}

CntNetconfState::CntStatistics::LeafInBadHellos::~LeafInBadHellos() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/statistics/in-sessions
// Description: Number of sessions started.  This counter is incremented
//              when a <hello> message with a <session-id> is sent.
//              'in-sessions' - 'in-bad-hellos' =
//                 'number of correctly started netconf sessions'
// -----------------------------------------------------------------------------
CntNetconfState::CntStatistics::LeafInSessions::LeafInSessions(uint32_t id)
    : YangLeaf("in-sessions", id) {}

CntNetconfState::CntStatistics::LeafInSessions::~LeafInSessions() {}

// -----------------------------------------------------------------------------
// Leaf:        /netconf-state/statistics/dropped-sessions
// Description: Number of sessions that were abnormally terminated, e.g.,
//              due to idle timeout or transport close.  This counter is not
//              incremented when a session is properly closed by a
//              <close-session> operation, or killed by a <kill-session>
//              operation.
// -----------------------------------------------------------------------------
CntNetconfState::CntStatistics::LeafDroppedSessions::LeafDroppedSessions(
    uint32_t id)
    : YangLeaf("dropped-sessions", id) {}

CntNetconfState::CntStatistics::LeafDroppedSessions::~LeafDroppedSessions() {}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    common-counters
// Description: Counters that exist both per session, and also globally,
//              accumulated from all sessions.
// -----------------------------------------------------------------------------
GrpCommonCounters::GrpCommonCounters(uint32_t id)
    : YangGroup("common-counters", id) {}

GrpCommonCounters::~GrpCommonCounters() {}

YangResult_E
GrpCommonCounters::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /common-counters/in-rpcs
  // Description: Number of correct <rpc> messages received.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafInRpcs inRpcsInst(ITEM_IN_RPCS);
  addLeaf(inRpcsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /common-counters/in-bad-rpcs
  // Description: Number of messages received when an <rpc> message was
  // expected,
  //              that were not correct <rpc> messages.  This includes XML parse
  //              errors and errors on the rpc layer.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafInBadRpcs inBadRpcsInst(ITEM_IN_BAD_RPCS);
  addLeaf(inBadRpcsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /common-counters/out-rpc-errors
  // Description: Number of <rpc-reply> messages sent that contained an
  //              <rpc-error> element.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafOutRpcErrors outRpcErrorsInst(ITEM_OUT_RPC_ERRORS);
  addLeaf(outRpcErrorsInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /common-counters/out-notifications
  // Description: Number of <notification> messages sent.
  // Type:        uint32
  // Units:
  // -----------------------------------------------------------------------------
  LeafOutNotifications outNotificationsInst(ITEM_OUT_NOTIFICATIONS);
  addLeaf(outNotificationsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /common-counters/in-rpcs
// Description: Number of correct <rpc> messages received.
// -----------------------------------------------------------------------------
GrpCommonCounters::LeafInRpcs::LeafInRpcs(uint32_t id)
    : YangLeaf("in-rpcs", id) {}

GrpCommonCounters::LeafInRpcs::~LeafInRpcs() {}

// -----------------------------------------------------------------------------
// Leaf:        /common-counters/in-bad-rpcs
// Description: Number of messages received when an <rpc> message was expected,
//              that were not correct <rpc> messages.  This includes XML parse
//              errors and errors on the rpc layer.
// -----------------------------------------------------------------------------
GrpCommonCounters::LeafInBadRpcs::LeafInBadRpcs(uint32_t id)
    : YangLeaf("in-bad-rpcs", id) {}

GrpCommonCounters::LeafInBadRpcs::~LeafInBadRpcs() {}

// -----------------------------------------------------------------------------
// Leaf:        /common-counters/out-rpc-errors
// Description: Number of <rpc-reply> messages sent that contained an
//              <rpc-error> element.
// -----------------------------------------------------------------------------
GrpCommonCounters::LeafOutRpcErrors::LeafOutRpcErrors(uint32_t id)
    : YangLeaf("out-rpc-errors", id) {}

GrpCommonCounters::LeafOutRpcErrors::~LeafOutRpcErrors() {}

// -----------------------------------------------------------------------------
// Leaf:        /common-counters/out-notifications
// Description: Number of <notification> messages sent.
// -----------------------------------------------------------------------------
GrpCommonCounters::LeafOutNotifications::LeafOutNotifications(uint32_t id)
    : YangLeaf("out-notifications", id) {}

GrpCommonCounters::LeafOutNotifications::~LeafOutNotifications() {}

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
// Module:      ietf-netconf-monitoring
// Description: NETCONF Monitoring Module.
//              All elements in this module are read-only.
//              Copyright (c) 2010 IETF Trust and the persons identified as
//              authors of the code. All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD
//              License set forth in Section 4.c of the IETF Trust's
//              Legal Provisions Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 6022; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIetfNetconfMonitoring::ModuleIetfNetconfMonitoring(uint32_t id)
    : YangModule(
          "ietf-netconf-monitoring",
          "ietf-netconf-monitoring.yang",
          "ncm",
          "urn:ietf:params:xml:ns:yang:ietf-netconf-monitoring",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /netconf-state
  // Description: The netconf-state container is the root of the monitoring
  //              data model.
  // -----------------------------------------------------------------------------
  CntNetconfState netconfStateInst(ITEM_NETCONF_STATE);
  netconfStateInst.initialise();
  addContainer(netconfStateInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleIetfNetconfMonitoring::~ModuleIetfNetconfMonitoring() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleIetfNetconfMonitoring::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleIetfNetconfMonitoring>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleIetfNetconfMonitoring::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
