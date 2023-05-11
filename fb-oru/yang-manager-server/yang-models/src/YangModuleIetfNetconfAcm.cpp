/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfNetconfAcm.cpp
 * \brief     Module IetfNetconfAcm interface
 *
 *
 * \details   This file defines the YANG module ietf-netconf-acm interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-netconf-acm"
 *            YANG Filename:    "ietf-netconf-acm.yang"
 *            Module Prefix:    "nacm"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-netconf-acm"
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
#include "YangModuleIetfNetconfAcm.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleIetfNetconfAcm_NS;

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
// Container:   nacm
// Description: Parameters for NETCONF access control model.
// -----------------------------------------------------------------------------
CntNacm::CntNacm(uint32_t id)
	: YangContainer("nacm", id)
{
}

CntNacm::~CntNacm()
{
}

YangResult_E CntNacm::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/enable-nacm
	// Description: Enables or disables all NETCONF access control
	//              enforcement.  If 'true', then enforcement
	//              is enabled.  If 'false', then enforcement
	//              is disabled.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnableNacm enableNacmInst(ITEM_ENABLE_NACM);
	addLeaf(enableNacmInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/read-default
	// Description: Controls whether read access is granted if
	//              no appropriate rule is found for a
	//              particular read request.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafReadDefault readDefaultInst(ITEM_READ_DEFAULT);
	addLeaf(readDefaultInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/write-default
	// Description: Controls whether create, update, or delete access
	//              is granted if no appropriate rule is found for a
	//              particular write request.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafWriteDefault writeDefaultInst(ITEM_WRITE_DEFAULT);
	addLeaf(writeDefaultInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/exec-default
	// Description: Controls whether exec access is granted if no appropriate
	//              rule is found for a particular protocol operation request.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafExecDefault execDefaultInst(ITEM_EXEC_DEFAULT);
	addLeaf(execDefaultInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/enable-external-groups
	// Description: Controls whether the server uses the groups reported by the
	//              NETCONF transport layer when it assigns the user to a set of
	//              NACM groups.  If this leaf has the value 'false', any group
	//              names reported by the transport layer are ignored by the
	//              server.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnableExternalGroups enableExternalGroupsInst(ITEM_ENABLE_EXTERNAL_GROUPS);
	addLeaf(enableExternalGroupsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/denied-operations
	// Description: Number of times since the server last restarted that a
	//              protocol operation request was denied.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDeniedOperations deniedOperationsInst(ITEM_DENIED_OPERATIONS);
	addLeaf(deniedOperationsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/denied-data-writes
	// Description: Number of times since the server last restarted that a
	//              protocol operation request to alter
	//              a configuration datastore was denied.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDeniedDataWrites deniedDataWritesInst(ITEM_DENIED_DATA_WRITES);
	addLeaf(deniedDataWritesInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/denied-notifications
	// Description: Number of times since the server last restarted that
	//              a notification was dropped for a subscription because
	//              access to the event type was denied.
	// Type:        uint32
	// Units:
	// -----------------------------------------------------------------------------
	LeafDeniedNotifications deniedNotificationsInst(ITEM_DENIED_NOTIFICATIONS);
	addLeaf(deniedNotificationsInst);

	// -----------------------------------------------------------------------------
	// List:        /nacm/rule-list
	// Description: An ordered collection of access control rules.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRuleList ruleListInst(ITEM_RULE_LIST);
	ruleListInst.initialise();
	addList(ruleListInst);

	// -----------------------------------------------------------------------------
	// Container:   /nacm/groups
	// Description: NETCONF access control groups.
	// -----------------------------------------------------------------------------
	CntGroups groupsInst(ITEM_GROUPS);
	groupsInst.initialise();
	addContainer(groupsInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/enable-nacm
// Description: Enables or disables all NETCONF access control
//              enforcement.  If 'true', then enforcement
//              is enabled.  If 'false', then enforcement
//              is disabled.
// -----------------------------------------------------------------------------
CntNacm::LeafEnableNacm::LeafEnableNacm(uint32_t id)
	: YangLeaf("enable-nacm", id)
{
}

CntNacm::LeafEnableNacm::~LeafEnableNacm()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/read-default
// Description: Controls whether read access is granted if
//              no appropriate rule is found for a
//              particular read request.
// -----------------------------------------------------------------------------
CntNacm::LeafReadDefault::LeafReadDefault(uint32_t id)
	: YangLeaf("read-default", id)
{
}

CntNacm::LeafReadDefault::~LeafReadDefault()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/write-default
// Description: Controls whether create, update, or delete access
//              is granted if no appropriate rule is found for a
//              particular write request.
// -----------------------------------------------------------------------------
CntNacm::LeafWriteDefault::LeafWriteDefault(uint32_t id)
	: YangLeaf("write-default", id)
{
}

CntNacm::LeafWriteDefault::~LeafWriteDefault()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/exec-default
// Description: Controls whether exec access is granted if no appropriate
//              rule is found for a particular protocol operation request.
// -----------------------------------------------------------------------------
CntNacm::LeafExecDefault::LeafExecDefault(uint32_t id)
	: YangLeaf("exec-default", id)
{
}

CntNacm::LeafExecDefault::~LeafExecDefault()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/enable-external-groups
// Description: Controls whether the server uses the groups reported by the
//              NETCONF transport layer when it assigns the user to a set of
//              NACM groups.  If this leaf has the value 'false', any group
//              names reported by the transport layer are ignored by the
//              server.
// -----------------------------------------------------------------------------
CntNacm::LeafEnableExternalGroups::LeafEnableExternalGroups(uint32_t id)
	: YangLeaf("enable-external-groups", id)
{
}

CntNacm::LeafEnableExternalGroups::~LeafEnableExternalGroups()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/denied-operations
// Description: Number of times since the server last restarted that a
//              protocol operation request was denied.
// -----------------------------------------------------------------------------
CntNacm::LeafDeniedOperations::LeafDeniedOperations(uint32_t id)
	: YangLeaf("denied-operations", id)
{
}

CntNacm::LeafDeniedOperations::~LeafDeniedOperations()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/denied-data-writes
// Description: Number of times since the server last restarted that a
//              protocol operation request to alter
//              a configuration datastore was denied.
// -----------------------------------------------------------------------------
CntNacm::LeafDeniedDataWrites::LeafDeniedDataWrites(uint32_t id)
	: YangLeaf("denied-data-writes", id)
{
}

CntNacm::LeafDeniedDataWrites::~LeafDeniedDataWrites()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/denied-notifications
// Description: Number of times since the server last restarted that
//              a notification was dropped for a subscription because
//              access to the event type was denied.
// -----------------------------------------------------------------------------
CntNacm::LeafDeniedNotifications::LeafDeniedNotifications(uint32_t id)
	: YangLeaf("denied-notifications", id)
{
}

CntNacm::LeafDeniedNotifications::~LeafDeniedNotifications()
{
}

// -----------------------------------------------------------------------------
// List:        rule-list
// Description: An ordered collection of access control rules.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRuleList(uint32_t id)
	: YangList("rule-list", id)
{
}

CntNacm::LstRuleList::~LstRuleList()
{
}

YangResult_E CntNacm::LstRuleList::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/name
	// Description: Arbitrary name assigned to the rule-list.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// List:        /nacm/rule-list/group
	// Description: List of administrative groups that will be
	//              assigned the associated access rights
	//              defined by the 'rule' list.
	//              The string '*' indicates that all groups apply to the
	//              entry.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstGroup groupInst(ITEM_GROUP);
	groupInst.initialise();
	addList(groupInst);

	// -----------------------------------------------------------------------------
	// List:        /nacm/rule-list/rule
	// Description: One access control rule.
	//              Rules are processed in user-defined order until a match is
	//              found.  A rule matches if 'module-name', 'rule-type', and
	//              'access-operations' match the request.  If a rule
	//              matches, the 'action' leaf determines whether or not
	//              access is granted.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstRule ruleInst(ITEM_RULE);
	ruleInst.initialise();
	addList(ruleInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/name
// Description: Arbitrary name assigned to the rule-list.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

CntNacm::LstRuleList::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// List:        group
// Description: List of administrative groups that will be
//              assigned the associated access rights
//              defined by the 'rule' list.
//              The string '*' indicates that all groups apply to the
//              entry.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstGroup::LstGroup(uint32_t id)
	: YangList("group", id)
{
}

CntNacm::LstRuleList::LstGroup::~LstGroup()
{
}

YangResult_E CntNacm::LstRuleList::LstGroup::initialise(void)
{


	return YangResult_E::OK;
}



// -----------------------------------------------------------------------------
// List:        rule
// Description: One access control rule.
//              Rules are processed in user-defined order until a match is
//              found.  A rule matches if 'module-name', 'rule-type', and
//              'access-operations' match the request.  If a rule
//              matches, the 'action' leaf determines whether or not
//              access is granted.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LstRule(uint32_t id)
	: YangList("rule", id)
{
}

CntNacm::LstRuleList::LstRule::~LstRule()
{
}

YangResult_E CntNacm::LstRuleList::LstRule::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/name
	// Description: Arbitrary name assigned to the rule.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/module-name
	// Description: Name of the module associated with this rule.
	//              This leaf matches if it has the value '*' or if the
	//              object being accessed is defined in the module with the
	//              specified module name.
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafModuleName moduleNameInst(ITEM_MODULE_NAME);
	addLeaf(moduleNameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/access-operations
	// Description: Access operations associated with this rule.
	//              This leaf matches if it has the value '*' or if the
	//              bit corresponding to the requested operation is set.
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafAccessOperations accessOperationsInst(ITEM_ACCESS_OPERATIONS);
	addLeaf(accessOperationsInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/action
	// Description: The access control action associated with the
	//              rule.  If a rule has been determined to match a
	//              particular request, then this object is used
	//              to determine whether to permit or deny the
	//              request.
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafAction actionInst(ITEM_ACTION);
	addLeaf(actionInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/comment
	// Description: A textual description of the access rule.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafComment commentInst(ITEM_COMMENT);
	addLeaf(commentInst);

	// -----------------------------------------------------------------------------
	// Choice:      /nacm/rule-list/rule/rule-type
	// Description: This choice matches if all leafs present in the rule
	//              match the request.  If no leafs are present, the
	//              choice matches all requests.
	// Type:        RuleType_E
	// Units:       -
	// -----------------------------------------------------------------------------
	ChoiceRuleType ruleTypeInst(ITEM_RULE_TYPE);
	ruleTypeInst.initialise();
	addChoice(ruleTypeInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/name
// Description: Arbitrary name assigned to the rule.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

CntNacm::LstRuleList::LstRule::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/module-name
// Description: Name of the module associated with this rule.
//              This leaf matches if it has the value '*' or if the
//              object being accessed is defined in the module with the
//              specified module name.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LeafModuleName::LeafModuleName(uint32_t id)
	: YangLeaf("module-name", id)
{
}

CntNacm::LstRuleList::LstRule::LeafModuleName::~LeafModuleName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/access-operations
// Description: Access operations associated with this rule.
//              This leaf matches if it has the value '*' or if the
//              bit corresponding to the requested operation is set.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LeafAccessOperations::LeafAccessOperations(uint32_t id)
	: YangLeaf("access-operations", id)
{
}

CntNacm::LstRuleList::LstRule::LeafAccessOperations::~LeafAccessOperations()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/action
// Description: The access control action associated with the
//              rule.  If a rule has been determined to match a
//              particular request, then this object is used
//              to determine whether to permit or deny the
//              request.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LeafAction::LeafAction(uint32_t id)
	: YangLeaf("action", id)
{
}

CntNacm::LstRuleList::LstRule::LeafAction::~LeafAction()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/comment
// Description: A textual description of the access rule.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::LeafComment::LeafComment(uint32_t id)
	: YangLeaf("comment", id)
{
}

CntNacm::LstRuleList::LstRule::LeafComment::~LeafComment()
{
}

// -----------------------------------------------------------------------------
// Choice:      rule-type
// Description: This choice matches if all leafs present in the rule
//              match the request.  If no leafs are present, the
//              choice matches all requests.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::ChoiceRuleType(uint32_t id)
	: YangChoice("rule-type", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::~ChoiceRuleType()
{
}

YangResult_E CntNacm::LstRuleList::LstRule::ChoiceRuleType::initialise(void)
{

	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptProtocolOperation protocolOperation(ITEM_PROTOCOL_OPERATION);
	protocolOperation.initialise();
	addOption(protocolOperation);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptNotification notification(ITEM_NOTIFICATION);
	notification.initialise();
	addOption(notification);


	// -------------------------------------------------------------------------
	// Option:       array-choice/antenna-type[tx]
	// Description:  Leafref to tx array if such is choosen
	// -------------------------------------------------------------------------
	OptDataNode dataNode(ITEM_DATA_NODE);
	dataNode.initialise();
	addOption(dataNode);



	return YangResult_E::OK;
}


// -------------------------------------------------------------------------
// Option:      /nacm/rule-list/rule/rule-type[protocol-operation]
// -------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptProtocolOperation::OptProtocolOperation(uint32_t id)
	: YangChoiceOption("protocol-operation", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptProtocolOperation::~OptProtocolOperation()
{
}

YangResult_E CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptProtocolOperation::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/rule-type[protocol-operation]/rpc-name
	// Description: This leaf matches if it has the value '*' or if
	//              its value equals the requested protocol operation
	//              name.
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafRpcName rpcNameInst(ITEM_RPC_NAME);
	addLeaf(rpcNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/rule-type[protocol-operation]/rpc-name
// Description: This leaf matches if it has the value '*' or if
//              its value equals the requested protocol operation
//              name.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptProtocolOperation::LeafRpcName::LeafRpcName(uint32_t id)
	: YangLeaf("rpc-name", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptProtocolOperation::LeafRpcName::~LeafRpcName()
{
}



// -------------------------------------------------------------------------
// Option:      /nacm/rule-list/rule/rule-type[notification]
// -------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptNotification::OptNotification(uint32_t id)
	: YangChoiceOption("notification", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptNotification::~OptNotification()
{
}

YangResult_E CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptNotification::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/rule-type[notification]/notification-name
	// Description: This leaf matches if it has the value '*' or if its
	//              value equals the requested notification name.
	// Type:        ???UNION
	// Units:
	// -----------------------------------------------------------------------------
	LeafNotificationName notificationNameInst(ITEM_NOTIFICATION_NAME);
	addLeaf(notificationNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/rule-type[notification]/notification-name
// Description: This leaf matches if it has the value '*' or if its
//              value equals the requested notification name.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptNotification::LeafNotificationName::LeafNotificationName(uint32_t id)
	: YangLeaf("notification-name", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptNotification::LeafNotificationName::~LeafNotificationName()
{
}



// -------------------------------------------------------------------------
// Option:      /nacm/rule-list/rule/rule-type[data-node]
// -------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptDataNode::OptDataNode(uint32_t id)
	: YangChoiceOption("data-node", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptDataNode::~OptDataNode()
{
}

YangResult_E CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptDataNode::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/rule-list/rule/rule-type[data-node]/path
	// Description: Data node instance-identifier associated with the
	//              data node, action, or notification controlled by
	//              this rule.
	//              Configuration data or state data
	//              instance-identifiers start with a top-level
	//              data node.  A complete instance-identifier is
	//              required for this type of path value.
	//              The special value '/' refers to all possible
	//              datastore contents.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafPath pathInst(ITEM_PATH);
	addLeaf(pathInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/rule-list/rule/rule-type[data-node]/path
// Description: Data node instance-identifier associated with the
//              data node, action, or notification controlled by
//              this rule.
//              Configuration data or state data
//              instance-identifiers start with a top-level
//              data node.  A complete instance-identifier is
//              required for this type of path value.
//              The special value '/' refers to all possible
//              datastore contents.
// -----------------------------------------------------------------------------
CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptDataNode::LeafPath::LeafPath(uint32_t id)
	: YangLeaf("path", id)
{
}

CntNacm::LstRuleList::LstRule::ChoiceRuleType::OptDataNode::LeafPath::~LeafPath()
{
}










// -----------------------------------------------------------------------------
// Container:   groups
// Description: NETCONF access control groups.
// -----------------------------------------------------------------------------
CntNacm::CntGroups::CntGroups(uint32_t id)
	: YangContainer("groups", id)
{
}

CntNacm::CntGroups::~CntGroups()
{
}

YangResult_E CntNacm::CntGroups::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /nacm/groups/group
	// Description: One NACM group entry.  This list will only contain
	//              configured entries, not any entries learned from
	//              any transport protocols.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstGroup groupInst(ITEM_GROUP);
	groupInst.initialise();
	addList(groupInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        group
// Description: One NACM group entry.  This list will only contain
//              configured entries, not any entries learned from
//              any transport protocols.
// -----------------------------------------------------------------------------
CntNacm::CntGroups::LstGroup::LstGroup(uint32_t id)
	: YangList("group", id)
{
}

CntNacm::CntGroups::LstGroup::~LstGroup()
{
}

YangResult_E CntNacm::CntGroups::LstGroup::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /nacm/groups/group/name
	// Description: Group name associated with this entry.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// List:        /nacm/groups/group/user-name
	// Description: Each entry identifies the username of
	//              a member of the group associated with
	//              this entry.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstUserName userNameInst(ITEM_USER_NAME);
	userNameInst.initialise();
	addList(userNameInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /nacm/groups/group/name
// Description: Group name associated with this entry.
// -----------------------------------------------------------------------------
CntNacm::CntGroups::LstGroup::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

CntNacm::CntGroups::LstGroup::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// List:        user-name
// Description: Each entry identifies the username of
//              a member of the group associated with
//              this entry.
// -----------------------------------------------------------------------------
CntNacm::CntGroups::LstGroup::LstUserName::LstUserName(uint32_t id)
	: YangList("user-name", id)
{
}

CntNacm::CntGroups::LstGroup::LstUserName::~LstUserName()
{
}

YangResult_E CntNacm::CntGroups::LstGroup::LstUserName::initialise(void)
{


	return YangResult_E::OK;
}












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
// Module:      ietf-netconf-acm
// Description: Network Configuration Access Control Model.
//              Copyright (c) 2012 - 2018 IETF Trust and the persons
//              identified as authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD
//              License set forth in Section 4.c of the IETF Trust's
//              Legal Provisions Relating to IETF Documents
//              (https://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 8341; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
ModuleIetfNetconfAcm::ModuleIetfNetconfAcm(uint32_t id)
	: YangModule ("ietf-netconf-acm",
	              "ietf-netconf-acm.yang",
	              "nacm",
	              "urn:ietf:params:xml:ns:yang:ietf-netconf-acm",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /nacm
	// Description: Parameters for NETCONF access control model.
	// -----------------------------------------------------------------------------
	CntNacm nacmInst(ITEM_NACM);
	nacmInst.initialise();
	addContainer(nacmInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleIetfNetconfAcm::~ModuleIetfNetconfAcm()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleIetfNetconfAcm::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleIetfNetconfAcm>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleIetfNetconfAcm::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
