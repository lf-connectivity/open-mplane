/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanFm.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanFm.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanFm_NS;

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
// Container:   active-alarm-list
// Description: List of currently active alarms. An alarm is removed from this
// table when the state transitions to clear.
// -----------------------------------------------------------------------------
CntActiveAlarmList::CntActiveAlarmList(uint32_t id)
    : YangContainer("active-alarm-list", id) {}

CntActiveAlarmList::~CntActiveAlarmList() {}

YangResult_E
CntActiveAlarmList::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /active-alarm-list/active-alarms
  // Description: List of currenty active alarms
  // Array Key:
  // -----------------------------------------------------------------------------
  LstActiveAlarms activeAlarmsInst(ITEM_ACTIVE_ALARMS);
  activeAlarmsInst.initialise();
  addList(activeAlarmsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        active-alarms
// Description: List of currenty active alarms
// -----------------------------------------------------------------------------
CntActiveAlarmList::LstActiveAlarms::LstActiveAlarms(uint32_t id)
    : YangList("active-alarms", id) {}

CntActiveAlarmList::LstActiveAlarms::~LstActiveAlarms() {}

YangResult_E
CntActiveAlarmList::LstActiveAlarms::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /active-alarm-list/active-alarms/alarm
  // Description:
  // -----------------------------------------------------------------------------
  GrpAlarm alarmInst(ITEM_ALARM);
  alarmInst.initialise();
  addGroup(alarmInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    alarm
// Description: Gropuping which can uniquely identify alarm
// -----------------------------------------------------------------------------
GrpAlarm::GrpAlarm(uint32_t id) : YangGroup("alarm", id) {}

GrpAlarm::~GrpAlarm() {}

YangResult_E
GrpAlarm::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/fault-id
  // Description: Fault specific Id that identifies the fault.
  // Type:        uint16
  // Units:
  // -----------------------------------------------------------------------------
  LeafFaultId faultIdInst(ITEM_FAULT_ID);
  addLeaf(faultIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/fault-source
  // Description: Represents the Object or source that is suspected to be
  // faulty. Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafFaultSource faultSourceInst(ITEM_FAULT_SOURCE);
  addLeaf(faultSourceInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/fault-severity
  // Description: Fault severity defines the severity level of the fault. A
  // notification, whose fault severity has the value 'warning',
  //              is a special type of an alarm notification. For these alarm
  //              notifications, the Master Agent does not expect to receive a
  //              clear alarm notification.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafFaultSeverity faultSeverityInst(ITEM_FAULT_SEVERITY);
  addLeaf(faultSeverityInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/is-cleared
  // Description: Fault state determines the type of the event. Not used if
  // faultSeverity is WARNING. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafIsCleared isClearedInst(ITEM_IS_CLEARED);
  addLeaf(isClearedInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/fault-text
  // Description: Textual description of the fault.
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafFaultText faultTextInst(ITEM_FAULT_TEXT);
  addLeaf(faultTextInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/event-time
  // Description: Timestamp to indicate the time when the fault is
  // detected/cleared. Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafEventTime eventTimeInst(ITEM_EVENT_TIME);
  addLeaf(eventTimeInst);

  // -----------------------------------------------------------------------------
  // List:        /alarm/affected-objects
  // Description: List of affected-objects
  // Array Key:
  // -----------------------------------------------------------------------------
  LstAffectedObjects affectedObjectsInst(ITEM_AFFECTED_OBJECTS);
  affectedObjectsInst.initialise();
  addList(affectedObjectsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/fault-id
// Description: Fault specific Id that identifies the fault.
// -----------------------------------------------------------------------------
GrpAlarm::LeafFaultId::LeafFaultId(uint32_t id) : YangLeaf("fault-id", id) {}

GrpAlarm::LeafFaultId::~LeafFaultId() {}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/fault-source
// Description: Represents the Object or source that is suspected to be faulty.
// -----------------------------------------------------------------------------
GrpAlarm::LeafFaultSource::LeafFaultSource(uint32_t id)
    : YangLeaf("fault-source", id) {}

GrpAlarm::LeafFaultSource::~LeafFaultSource() {}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/fault-severity
// Description: Fault severity defines the severity level of the fault. A
// notification, whose fault severity has the value 'warning',
//              is a special type of an alarm notification. For these alarm
//              notifications, the Master Agent does not expect to receive a
//              clear alarm notification.
// -----------------------------------------------------------------------------
GrpAlarm::LeafFaultSeverity::LeafFaultSeverity(uint32_t id)
    : YangLeaf("fault-severity", id) {}

GrpAlarm::LeafFaultSeverity::~LeafFaultSeverity() {}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/is-cleared
// Description: Fault state determines the type of the event. Not used if
// faultSeverity is WARNING.
// -----------------------------------------------------------------------------
GrpAlarm::LeafIsCleared::LeafIsCleared(uint32_t id)
    : YangLeaf("is-cleared", id) {}

GrpAlarm::LeafIsCleared::~LeafIsCleared() {}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/fault-text
// Description: Textual description of the fault.
// -----------------------------------------------------------------------------
GrpAlarm::LeafFaultText::LeafFaultText(uint32_t id)
    : YangLeaf("fault-text", id) {}

GrpAlarm::LeafFaultText::~LeafFaultText() {}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/event-time
// Description: Timestamp to indicate the time when the fault is
// detected/cleared.
// -----------------------------------------------------------------------------
GrpAlarm::LeafEventTime::LeafEventTime(uint32_t id)
    : YangLeaf("event-time", id) {}

GrpAlarm::LeafEventTime::~LeafEventTime() {}

// -----------------------------------------------------------------------------
// List:        affected-objects
// Description: List of affected-objects
// -----------------------------------------------------------------------------
GrpAlarm::LstAffectedObjects::LstAffectedObjects(uint32_t id)
    : YangList("affected-objects", id) {}

GrpAlarm::LstAffectedObjects::~LstAffectedObjects() {}

YangResult_E
GrpAlarm::LstAffectedObjects::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /alarm/affected-objects/name
  // Description: Represents the Object or source that is suspected to be
  // affected by this fault Type:        string Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /alarm/affected-objects/name
// Description: Represents the Object or source that is suspected to be affected
// by this fault
// -----------------------------------------------------------------------------
GrpAlarm::LstAffectedObjects::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpAlarm::LstAffectedObjects::LeafName::~LeafName() {}

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
// Notification:alarm-notif
// Description: Notification sent on initial alarm creation, as well as any time
// the alarm changes state, including clear
// -----------------------------------------------------------------------------
NotifAlarmNotif::NotifAlarmNotif(uint32_t id) : YangNotif("alarm-notif", id) {}

NotifAlarmNotif::~NotifAlarmNotif() {}

YangResult_E
NotifAlarmNotif::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /alarm-notif/alarm
  // Description:
  // -----------------------------------------------------------------------------
  GrpAlarm alarmInst(ITEM_ALARM);
  alarmInst.initialise();
  addGroup(alarmInst);

  return YangResult_E::OK;
}

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
ModuleORanFm::ModuleORanFm(uint32_t id)
    : YangModule(
          "o-ran-fm", "o-ran-fm.yang", "o-ran-fm", "urn:o-ran:fm:1.0", id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /active-alarm-list
  // Description: List of currently active alarms. An alarm is removed from this
  // table when the state transitions to clear.
  // -----------------------------------------------------------------------------
  CntActiveAlarmList activeAlarmListInst(ITEM_ACTIVE_ALARM_LIST);
  activeAlarmListInst.initialise();
  addContainer(activeAlarmListInst);

  // -----------------------------------------------------------------------------
  // Notification:/alarm-notif
  // Description: Notification sent on initial alarm creation, as well as any
  // time the alarm changes state, including clear
  // -----------------------------------------------------------------------------
  NotifAlarmNotif alarmNotifInst(ITEM_ALARM_NOTIF);
  alarmNotifInst.initialise();
  addNotification(alarmNotifInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanFm::~ModuleORanFm() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanFm::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanFm>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanFm::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
