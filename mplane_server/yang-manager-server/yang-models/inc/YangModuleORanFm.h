#ifndef _MODULE_O_RAN_FM_H_
#define _MODULE_O_RAN_FM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFm.h
 * \brief     Module ORanFm interface
 *
 *
 * \details   This file defines the YANG module o-ran-fm interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-fm"
 *            YANG Filename:    "o-ran-fm.yang"
 *            Module Prefix:    "o-ran-fm"
 *            Module namespace: "urn:o-ran:fm:1.0"
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
// Revision: 2013-07-15
// Notes:
#include "YangModuleIetfYangTypes.h"


namespace Mplane {

namespace ModuleORanFm_NS {

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
// -----------------------------------------------------------------------------
// Container:   /active-alarm-list
// Description: List of currently active alarms. An alarm is removed from this table when the state transitions to clear.
// -----------------------------------------------------------------------------
class CntActiveAlarmList : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ACTIVE_ALARMS, // LstActiveAlarms
 };

 CntActiveAlarmList(uint32_t id);
 ~CntActiveAlarmList();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /active-alarm-list/active-alarms
 // Description: List of currenty active alarms
 // -----------------------------------------------------------------------------
 class LstActiveAlarms : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_ALARM, // Use GrpAlarm
   };

   LstActiveAlarms(uint32_t id);
   ~LstActiveAlarms();

   YangResult_E initialise(void);

 }; // LstActiveAlarms

}; // CntActiveAlarmList


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /alarm
// Description: Gropuping which can uniquely identify alarm
// -----------------------------------------------------------------------------
class GrpAlarm : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_FAULT_ID, // LeafFaultId
   ITEM_FAULT_SOURCE, // LeafFaultSource
   ITEM_FAULT_SEVERITY, // LeafFaultSeverity
   ITEM_IS_CLEARED, // LeafIsCleared
   ITEM_FAULT_TEXT, // LeafFaultText
   ITEM_EVENT_TIME, // LeafEventTime
   ITEM_AFFECTED_OBJECTS, // LstAffectedObjects
 };

 GrpAlarm(uint32_t id);
 ~GrpAlarm();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/fault-id
 // Description: Fault specific Id that identifies the fault.
 // -----------------------------------------------------------------------------
 class LeafFaultId : public YangLeaf {
  public:
   LeafFaultId(uint32_t id);
   ~LeafFaultId();

 }; // LeafFaultId

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/fault-source
 // Description: Represents the Object or source that is suspected to be faulty.
 // -----------------------------------------------------------------------------
 class LeafFaultSource : public YangLeaf {
  public:
   LeafFaultSource(uint32_t id);
   ~LeafFaultSource();

 }; // LeafFaultSource

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/fault-severity
 // Description: Fault severity defines the severity level of the fault. A
 // notification, whose fault severity has the value 'warning',
 //              is a special type of an alarm notification. For these alarm
 //              notifications, the Master Agent does not expect to receive a
 //              clear alarm notification.
 // -----------------------------------------------------------------------------
 class LeafFaultSeverity : public YangLeaf {
  public:
   // Fault severity defines the severity level of the fault. A notification,
   // whose fault severity has the value 'warning', is a special type of an
   // alarm notification. For these alarm notifications, the Master Agent does
   // not expect to receive a clear alarm notification.
   enum class FaultSeverity_E : uint32_t {
     CRITICAL, // Critical alarm means that this device is not able to perform
               // any further service
     MAJOR, // Major alarm appeared on the device
     MINOR, // Minor alarm appeared on the device
     WARNING, // Warning is being reported by the device

     Num_FaultSeverity_E
   };

   LeafFaultSeverity(uint32_t id);
   ~LeafFaultSeverity();

 }; // LeafFaultSeverity

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/is-cleared
 // Description: Fault state determines the type of the event. Not used if
 // faultSeverity is WARNING.
 // -----------------------------------------------------------------------------
 class LeafIsCleared : public YangLeaf {
  public:
   LeafIsCleared(uint32_t id);
   ~LeafIsCleared();

 }; // LeafIsCleared

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/fault-text
 // Description: Textual description of the fault.
 // -----------------------------------------------------------------------------
 class LeafFaultText : public YangLeaf {
  public:
   LeafFaultText(uint32_t id);
   ~LeafFaultText();

 }; // LeafFaultText

 // -----------------------------------------------------------------------------
 // Leaf:        /alarm/event-time
 // Description: Timestamp to indicate the time when the fault is
 // detected/cleared.
 // -----------------------------------------------------------------------------
 class LeafEventTime : public YangLeaf {
  public:
   LeafEventTime(uint32_t id);
   ~LeafEventTime();

 }; // LeafEventTime

 // -----------------------------------------------------------------------------
 // List:        /alarm/affected-objects
 // Description: List of affected-objects
 // -----------------------------------------------------------------------------
 class LstAffectedObjects : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
   };

   LstAffectedObjects(uint32_t id);
   ~LstAffectedObjects();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /alarm/affected-objects/name
   // Description: Represents the Object or source that is suspected to be
   // affected by this fault
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

 }; // LstAffectedObjects

}; // GrpAlarm


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
// Notification:/alarm-notif
// Description: Notification sent on initial alarm creation, as well as any time the alarm changes state, including clear
// -----------------------------------------------------------------------------
class NotifAlarmNotif : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ALARM, // Use GrpAlarm
 };

 NotifAlarmNotif(uint32_t id);
 ~NotifAlarmNotif();

 YangResult_E initialise(void);

}; // NotifAlarmNotif


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-fm
// Description: This module defines alarm reporting mechanism.
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
class ModuleORanFm : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ACTIVE_ALARM_LIST, // CntActiveAlarmList
   ITEM_ALARM_NOTIF, // NotifAlarmNotif
 };

 ModuleORanFm(uint32_t id);
 ~ModuleORanFm();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanFm_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_FM_H_ */
