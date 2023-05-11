#ifndef _MODULE_IETF_NETCONF_ACM_H_
#define _MODULE_IETF_NETCONF_ACM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfNetconfAcm.h
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

// Module:   ietf-yang-types
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleIetfNetconfAcm_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// Action taken by the server when a particular
// rule matches.
enum class ActionType_E : uint32_t {
  PERMIT, // Requested action is permitted.
  DENY, // Requested action is denied.

  Num_ActionType_E
};

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
// Container:   /nacm
// Description: Parameters for NETCONF access control model.
// -----------------------------------------------------------------------------
class CntNacm : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ENABLE_NACM, // LeafEnableNacm
   ITEM_READ_DEFAULT, // LeafReadDefault
   ITEM_WRITE_DEFAULT, // LeafWriteDefault
   ITEM_EXEC_DEFAULT, // LeafExecDefault
   ITEM_ENABLE_EXTERNAL_GROUPS, // LeafEnableExternalGroups
   ITEM_DENIED_OPERATIONS, // LeafDeniedOperations
   ITEM_DENIED_DATA_WRITES, // LeafDeniedDataWrites
   ITEM_DENIED_NOTIFICATIONS, // LeafDeniedNotifications
   ITEM_GROUPS, // CntGroups
   ITEM_RULE_LIST, // LstRuleList
 };

 CntNacm(uint32_t id);
 ~CntNacm();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/enable-nacm
 // Description: Enables or disables all NETCONF access control
 //              enforcement.  If 'true', then enforcement
 //              is enabled.  If 'false', then enforcement
 //              is disabled.
 // -----------------------------------------------------------------------------
 class LeafEnableNacm : public YangLeaf {
  public:
   LeafEnableNacm(uint32_t id);
   ~LeafEnableNacm();

 }; // LeafEnableNacm

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/read-default
 // Description: Controls whether read access is granted if
 //              no appropriate rule is found for a
 //              particular read request.
 // -----------------------------------------------------------------------------
 class LeafReadDefault : public YangLeaf {
  public:
   // Controls whether read access is granted if
   // no appropriate rule is found for a
   // particular read request.
   enum class ReadDefault_E : uint32_t {

     Num_ReadDefault_E
   };

   LeafReadDefault(uint32_t id);
   ~LeafReadDefault();

 }; // LeafReadDefault

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/write-default
 // Description: Controls whether create, update, or delete access
 //              is granted if no appropriate rule is found for a
 //              particular write request.
 // -----------------------------------------------------------------------------
 class LeafWriteDefault : public YangLeaf {
  public:
   // Controls whether create, update, or delete access
   // is granted if no appropriate rule is found for a
   // particular write request.
   enum class WriteDefault_E : uint32_t {

     Num_WriteDefault_E
   };

   LeafWriteDefault(uint32_t id);
   ~LeafWriteDefault();

 }; // LeafWriteDefault

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/exec-default
 // Description: Controls whether exec access is granted if no appropriate
 //              rule is found for a particular protocol operation request.
 // -----------------------------------------------------------------------------
 class LeafExecDefault : public YangLeaf {
  public:
   // Controls whether exec access is granted if no appropriate
   // rule is found for a particular protocol operation request.
   enum class ExecDefault_E : uint32_t {

     Num_ExecDefault_E
   };

   LeafExecDefault(uint32_t id);
   ~LeafExecDefault();

 }; // LeafExecDefault

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/enable-external-groups
 // Description: Controls whether the server uses the groups reported by the
 //              NETCONF transport layer when it assigns the user to a set of
 //              NACM groups.  If this leaf has the value 'false', any group
 //              names reported by the transport layer are ignored by the
 //              server.
 // -----------------------------------------------------------------------------
 class LeafEnableExternalGroups : public YangLeaf {
  public:
   LeafEnableExternalGroups(uint32_t id);
   ~LeafEnableExternalGroups();

 }; // LeafEnableExternalGroups

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/denied-operations
 // Description: Number of times since the server last restarted that a
 //              protocol operation request was denied.
 // -----------------------------------------------------------------------------
 class LeafDeniedOperations : public YangLeaf {
  public:
   LeafDeniedOperations(uint32_t id);
   ~LeafDeniedOperations();

 }; // LeafDeniedOperations

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/denied-data-writes
 // Description: Number of times since the server last restarted that a
 //              protocol operation request to alter
 //              a configuration datastore was denied.
 // -----------------------------------------------------------------------------
 class LeafDeniedDataWrites : public YangLeaf {
  public:
   LeafDeniedDataWrites(uint32_t id);
   ~LeafDeniedDataWrites();

 }; // LeafDeniedDataWrites

 // -----------------------------------------------------------------------------
 // Leaf:        /nacm/denied-notifications
 // Description: Number of times since the server last restarted that
 //              a notification was dropped for a subscription because
 //              access to the event type was denied.
 // -----------------------------------------------------------------------------
 class LeafDeniedNotifications : public YangLeaf {
  public:
   LeafDeniedNotifications(uint32_t id);
   ~LeafDeniedNotifications();

 }; // LeafDeniedNotifications

 // -----------------------------------------------------------------------------
 // Container:   /nacm/groups
 // Description: NETCONF access control groups.
 // -----------------------------------------------------------------------------
 class CntGroups : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_GROUP, // LstGroup
   };

   CntGroups(uint32_t id);
   ~CntGroups();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // List:        /nacm/groups/group
   // Description: One NACM group entry.  This list will only contain
   //              configured entries, not any entries learned from
   //              any transport protocols.
   // -----------------------------------------------------------------------------
   class LstGroup : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_NAME, // LeafName
       ITEM_USER_NAME, // LstUserName
     };

     LstGroup(uint32_t id);
     ~LstGroup();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/groups/group/name
     // Description: Group name associated with this entry.
     // -----------------------------------------------------------------------------
     class LeafName : public YangLeaf {
      public:
       LeafName(uint32_t id);
       ~LeafName();

     }; // LeafName

     // -----------------------------------------------------------------------------
     // List:        /nacm/groups/group/user-name
     // Description: Each entry identifies the username of
     //              a member of the group associated with
     //              this entry.
     // -----------------------------------------------------------------------------
     class LstUserName : public YangList {
      public:
       // Item IDs
       enum : uint32_t {};

       LstUserName(uint32_t id);
       ~LstUserName();

       YangResult_E initialise(void);

     }; // LstUserName

   }; // LstGroup

 }; // CntGroups

 // -----------------------------------------------------------------------------
 // List:        /nacm/rule-list
 // Description: An ordered collection of access control rules.
 // -----------------------------------------------------------------------------
 class LstRuleList : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_GROUP, // LstGroup
     ITEM_RULE, // LstRule
   };

   LstRuleList(uint32_t id);
   ~LstRuleList();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /nacm/rule-list/name
   // Description: Arbitrary name assigned to the rule-list.
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // List:        /nacm/rule-list/group
   // Description: List of administrative groups that will be
   //              assigned the associated access rights
   //              defined by the 'rule' list.
   //              The string '*' indicates that all groups apply to the
   //              entry.
   // -----------------------------------------------------------------------------
   class LstGroup : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstGroup(uint32_t id);
     ~LstGroup();

     YangResult_E initialise(void);

   }; // LstGroup

   // -----------------------------------------------------------------------------
   // List:        /nacm/rule-list/rule
   // Description: One access control rule.
   //              Rules are processed in user-defined order until a match is
   //              found.  A rule matches if 'module-name', 'rule-type', and
   //              'access-operations' match the request.  If a rule
   //              matches, the 'action' leaf determines whether or not
   //              access is granted.
   // -----------------------------------------------------------------------------
   class LstRule : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_NAME, // LeafName
       ITEM_MODULE_NAME, // LeafModuleName
       ITEM_ACCESS_OPERATIONS, // LeafAccessOperations
       ITEM_ACTION, // LeafAction
       ITEM_COMMENT, // LeafComment
       ITEM_RULE_TYPE, // ChoiceRuleType
     };

     LstRule(uint32_t id);
     ~LstRule();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/rule-list/rule/name
     // Description: Arbitrary name assigned to the rule.
     // -----------------------------------------------------------------------------
     class LeafName : public YangLeaf {
      public:
       LeafName(uint32_t id);
       ~LeafName();

     }; // LeafName

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/rule-list/rule/module-name
     // Description: Name of the module associated with this rule.
     //              This leaf matches if it has the value '*' or if the
     //              object being accessed is defined in the module with the
     //              specified module name.
     // -----------------------------------------------------------------------------
     class LeafModuleName : public YangLeaf {
      public:
       LeafModuleName(uint32_t id);
       ~LeafModuleName();

     }; // LeafModuleName

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/rule-list/rule/access-operations
     // Description: Access operations associated with this rule.
     //              This leaf matches if it has the value '*' or if the
     //              bit corresponding to the requested operation is set.
     // -----------------------------------------------------------------------------
     class LeafAccessOperations : public YangLeaf {
      public:
       LeafAccessOperations(uint32_t id);
       ~LeafAccessOperations();

     }; // LeafAccessOperations

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/rule-list/rule/action
     // Description: The access control action associated with the
     //              rule.  If a rule has been determined to match a
     //              particular request, then this object is used
     //              to determine whether to permit or deny the
     //              request.
     // -----------------------------------------------------------------------------
     class LeafAction : public YangLeaf {
      public:
       // The access control action associated with the
       // rule.  If a rule has been determined to match a
       // particular request, then this object is used
       // to determine whether to permit or deny the
       // request.
       enum class Action_E : uint32_t {

         Num_Action_E
       };

       LeafAction(uint32_t id);
       ~LeafAction();

     }; // LeafAction

     // -----------------------------------------------------------------------------
     // Leaf:        /nacm/rule-list/rule/comment
     // Description: A textual description of the access rule.
     // -----------------------------------------------------------------------------
     class LeafComment : public YangLeaf {
      public:
       LeafComment(uint32_t id);
       ~LeafComment();

     }; // LeafComment

     // -----------------------------------------------------------------------------
     // Choice:      /nacm/rule-list/rule/rule-type
     // Description: This choice matches if all leafs present in the rule
     //              match the request.  If no leafs are present, the
     //              choice matches all requests.
     // -----------------------------------------------------------------------------
     class ChoiceRuleType : public YangChoice {
      public:
       // Choice Option
       enum : uint32_t {
         ITEM_PROTOCOL_OPERATION, // OptProtocolOperation
         ITEM_NOTIFICATION, // OptNotification
         ITEM_DATA_NODE, // OptDataNode
       };

       ChoiceRuleType(uint32_t id);
       ~ChoiceRuleType();

       YangResult_E initialise(void);

       // -----------------------------------------------------------------------------
       // Option:
       // /nacm/rule-list/rule/rule-type[protocol-operation]
       // -----------------------------------------------------------------------------
       class OptProtocolOperation : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_RPC_NAME, // LeafRpcName
         };

         OptProtocolOperation(uint32_t id);
         ~OptProtocolOperation();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Leaf:
         // /nacm/rule-list/rule/rule-type[protocol-operation]/rpc-name
         // Description: This leaf matches if it has the value
         // '*' or if
         //              its value equals the requested
         //              protocol operation name.
         // -----------------------------------------------------------------------------
         class LeafRpcName : public YangLeaf {
          public:
           LeafRpcName(uint32_t id);
           ~LeafRpcName();

         }; // LeafRpcName

       }; // OptProtocolOperation

       // -----------------------------------------------------------------------------
       // Option: /nacm/rule-list/rule/rule-type[notification]
       // -----------------------------------------------------------------------------
       class OptNotification : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_NOTIFICATION_NAME, // LeafNotificationName
         };

         OptNotification(uint32_t id);
         ~OptNotification();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Leaf:
         // /nacm/rule-list/rule/rule-type[notification]/notification-name
         // Description: This leaf matches if it has the value
         // '*' or if its
         //              value equals the requested
         //              notification name.
         // -----------------------------------------------------------------------------
         class LeafNotificationName : public YangLeaf {
          public:
           LeafNotificationName(uint32_t id);
           ~LeafNotificationName();

         }; // LeafNotificationName

       }; // OptNotification

       // -----------------------------------------------------------------------------
       // Option: /nacm/rule-list/rule/rule-type[data-node]
       // -----------------------------------------------------------------------------
       class OptDataNode : public YangChoiceOption {
        public:
         // Item IDs
         enum : uint32_t {
           ITEM_PATH, // LeafPath
         };

         OptDataNode(uint32_t id);
         ~OptDataNode();

         YangResult_E initialise(void);

         // -----------------------------------------------------------------------------
         // Leaf:
         // /nacm/rule-list/rule/rule-type[data-node]/path
         // Description: Data node instance-identifier
         // associated with the
         //              data node, action, or notification
         //              controlled by this rule.
         //              Configuration data or state data
         //              instance-identifiers start with a
         //              top-level data node.  A complete
         //              instance-identifier is required for
         //              this type of path value. The special
         //              value '/' refers to all possible
         //              datastore contents.
         // -----------------------------------------------------------------------------
         class LeafPath : public YangLeaf {
          public:
           LeafPath(uint32_t id);
           ~LeafPath();

         }; // LeafPath

       }; // OptDataNode

     }; // ChoiceRuleType

   }; // LstRule

 }; // LstRuleList

}; // CntNacm


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
class ModuleIetfNetconfAcm : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NACM, // CntNacm
 };

 ModuleIetfNetconfAcm(uint32_t id);
 ~ModuleIetfNetconfAcm();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleIetfNetconfAcm_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_NETCONF_ACM_H_ */
