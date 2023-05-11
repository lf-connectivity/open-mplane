/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanExternalio.cpp
 * \brief     Module ORanExternalio interface
 *
 *
 * \details   This file defines the YANG module o-ran-externalio interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-externalio"
 *            YANG Filename:    "o-ran-externalio.yang"
 *            Module Prefix:    "o-ran-io"
 *            Module namespace: "urn:o-ran:external-io:1.0"
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
#include "YangModuleORanExternalio.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanExternalio_NS;

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
// Container:   external-io
// Description: External IO information.
// -----------------------------------------------------------------------------
CntExternalIo::CntExternalIo(uint32_t id) : YangContainer("external-io", id) {}

CntExternalIo::~CntExternalIo() {}

YangResult_E
CntExternalIo::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /external-io/external-io-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpExternalIoGroup externalIoGroupInst(ITEM_EXTERNAL_IO_GROUP);
  externalIoGroupInst.initialise();
  addGroup(externalIoGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    external-io-group
// Description:
// -----------------------------------------------------------------------------
GrpExternalIoGroup::GrpExternalIoGroup(uint32_t id)
    : YangGroup("external-io-group", id) {}

GrpExternalIoGroup::~GrpExternalIoGroup() {}

YangResult_E
GrpExternalIoGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /external-io-group/input
  // Description: Leaf nodes describing external line inputs
  // Array Key:
  // -----------------------------------------------------------------------------
  LstInput inputInst(ITEM_INPUT);
  inputInst.initialise();
  addList(inputInst);

  // -----------------------------------------------------------------------------
  // List:        /external-io-group/output
  // Description: Leaf nodes describing external line outputs
  // Array Key:
  // -----------------------------------------------------------------------------
  LstOutput outputInst(ITEM_OUTPUT);
  outputInst.initialise();
  addList(outputInst);

  // -----------------------------------------------------------------------------
  // List:        /external-io-group/output-setting
  // Description: List allowing to set output line state
  // Array Key:
  // -----------------------------------------------------------------------------
  LstOutputSetting outputSettingInst(ITEM_OUTPUT_SETTING);
  outputSettingInst.initialise();
  addList(outputSettingInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        input
// Description: Leaf nodes describing external line inputs
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstInput::LstInput(uint32_t id) : YangList("input", id) {}

GrpExternalIoGroup::LstInput::~LstInput() {}

YangResult_E
GrpExternalIoGroup::LstInput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/input/name
  // Description: A unique name that identifies an input port instance.
  //              This name may be used in fault management to refer to a fault
  //              source or affected object
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/input/port-in
  // Description: A number which identifies an external input port.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafPortIn portInInst(ITEM_PORT_IN);
  addLeaf(portInInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/input/line-in
  // Description: Value TRUE indicates that circuit is open.
  //              Value FALSE indicates that circuit is closed.
  //
  //              Usually when nothing is connected to the line the value is
  //              TRUE. The details of external line-in implementation are HW
  //              specific.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafLineIn lineInInst(ITEM_LINE_IN);
  addLeaf(lineInInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/input/name
// Description: A unique name that identifies an input port instance.
//              This name may be used in fault management to refer to a fault
//              source or affected object
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstInput::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpExternalIoGroup::LstInput::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/input/port-in
// Description: A number which identifies an external input port.
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstInput::LeafPortIn::LeafPortIn(uint32_t id)
    : YangLeaf("port-in", id) {}

GrpExternalIoGroup::LstInput::LeafPortIn::~LeafPortIn() {}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/input/line-in
// Description: Value TRUE indicates that circuit is open.
//              Value FALSE indicates that circuit is closed.
//
//              Usually when nothing is connected to the line the value is TRUE.
//              The details of external line-in implementation are HW specific.
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstInput::LeafLineIn::LeafLineIn(uint32_t id)
    : YangLeaf("line-in", id) {}

GrpExternalIoGroup::LstInput::LeafLineIn::~LeafLineIn() {}

// -----------------------------------------------------------------------------
// List:        output
// Description: Leaf nodes describing external line outputs
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutput::LstOutput(uint32_t id)
    : YangList("output", id) {}

GrpExternalIoGroup::LstOutput::~LstOutput() {}

YangResult_E
GrpExternalIoGroup::LstOutput::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/output/name
  // Description: A name that is unique that identifies an output port instance.
  //              This name may be used in fault management to refer to a fault
  //              source or affected object
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/output/port-out
  // Description: A number which identifies an external output port.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafPortOut portOutInst(ITEM_PORT_OUT);
  addLeaf(portOutInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/output/name
// Description: A name that is unique that identifies an output port instance.
//              This name may be used in fault management to refer to a fault
//              source or affected object
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutput::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpExternalIoGroup::LstOutput::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/output/port-out
// Description: A number which identifies an external output port.
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutput::LeafPortOut::LeafPortOut(uint32_t id)
    : YangLeaf("port-out", id) {}

GrpExternalIoGroup::LstOutput::LeafPortOut::~LeafPortOut() {}

// -----------------------------------------------------------------------------
// List:        output-setting
// Description: List allowing to set output line state
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutputSetting::LstOutputSetting(uint32_t id)
    : YangList("output-setting", id) {}

GrpExternalIoGroup::LstOutputSetting::~LstOutputSetting() {}

YangResult_E
GrpExternalIoGroup::LstOutputSetting::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /external-io-group/output-setting/line-out
  // Description: Value TRUE indicates that circuit is in its natural state.
  //              Value FALSE indicates that circuit is not in its natural
  //              state.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafLineOut lineOutInst(ITEM_LINE_OUT);
  addLeaf(lineOutInst);

  // -----------------------------------------------------------------------------
  // Reference:   /external-io-group/output-setting/name
  // Description: Name derived from unmodifiable list external-io
  // Ref:         /external-io/output/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /external-io-group/output-setting/line-out
// Description: Value TRUE indicates that circuit is in its natural state.
//              Value FALSE indicates that circuit is not in its natural state.
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutputSetting::LeafLineOut::LeafLineOut(uint32_t id)
    : YangLeaf("line-out", id) {}

GrpExternalIoGroup::LstOutputSetting::LeafLineOut::~LeafLineOut() {}

// -----------------------------------------------------------------------------
// Reference:   /external-io-group/output-setting/name
// Description: Name derived from unmodifiable list external-io
// -----------------------------------------------------------------------------
GrpExternalIoGroup::LstOutputSetting::RefName::RefName(uint32_t id)
    : YangReference("name", id, "/external-io/output/name") {}

GrpExternalIoGroup::LstOutputSetting::RefName::~RefName() {}

// -----------------------------------------------------------------------------
// Grouping:    notification-group
// Description:
// -----------------------------------------------------------------------------
GrpNotificationGroup::GrpNotificationGroup(uint32_t id)
    : YangGroup("notification-group", id) {}

GrpNotificationGroup::~GrpNotificationGroup() {}

YangResult_E
GrpNotificationGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /notification-group/current-input-notification
  // Description: a container for the state of the input ports
  // -----------------------------------------------------------------------------
  CntCurrentInputNotification currentInputNotificationInst(
      ITEM_CURRENT_INPUT_NOTIFICATION);
  currentInputNotificationInst.initialise();
  addContainer(currentInputNotificationInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   current-input-notification
// Description: a container for the state of the input ports
// -----------------------------------------------------------------------------
GrpNotificationGroup::CntCurrentInputNotification::CntCurrentInputNotification(
    uint32_t id)
    : YangContainer("current-input-notification", id) {}

GrpNotificationGroup::CntCurrentInputNotification::
    ~CntCurrentInputNotification() {}

YangResult_E
GrpNotificationGroup::CntCurrentInputNotification::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /notification-group/current-input-notification/external-input
  // Description: a list of the input ports and their state
  // Array Key:
  // -----------------------------------------------------------------------------
  LstExternalInput externalInputInst(ITEM_EXTERNAL_INPUT);
  externalInputInst.initialise();
  addList(externalInputInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        external-input
// Description: a list of the input ports and their state
// -----------------------------------------------------------------------------
GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::
    LstExternalInput(uint32_t id)
    : YangList("external-input", id) {}

GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::
    ~LstExternalInput() {}

YangResult_E
GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::initialise(
    void) {
  // -----------------------------------------------------------------------------
  // Reference:
  // /notification-group/current-input-notification/external-input/name
  // Description: the name of the ald-port
  // Ref:         /external-io/input/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /notification-group/current-input-notification/external-input/io-port
  // Description: the external input port
  // Ref:         /external-io/input/port-in
  // Units:
  // -----------------------------------------------------------------------------
  RefIoPort ioPortInst(ITEM_IO_PORT);
  addReference(ioPortInst);

  // -----------------------------------------------------------------------------
  // Reference:
  // /notification-group/current-input-notification/external-input/line-in
  // Description: the state of the external input port
  // Ref:         /external-io/input/line-in
  // Units:
  // -----------------------------------------------------------------------------
  RefLineIn lineInInst(ITEM_LINE_IN);
  addReference(lineInInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference: /notification-group/current-input-notification/external-input/name
// Description: the name of the ald-port
// -----------------------------------------------------------------------------
GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefName::
    RefName(uint32_t id)
    : YangReference("name", id, "/external-io/input/name") {}

GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefName::
    ~RefName() {}

// -----------------------------------------------------------------------------
// Reference:
// /notification-group/current-input-notification/external-input/io-port
// Description: the external input port
// -----------------------------------------------------------------------------
GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefIoPort::
    RefIoPort(uint32_t id)
    : YangReference("io-port", id, "/external-io/input/port-in") {}

GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefIoPort::
    ~RefIoPort() {}

// -----------------------------------------------------------------------------
// Reference:
// /notification-group/current-input-notification/external-input/line-in
// Description: the state of the external input port
// -----------------------------------------------------------------------------
GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefLineIn::
    RefLineIn(uint32_t id)
    : YangReference("line-in", id, "/external-io/input/line-in") {}

GrpNotificationGroup::CntCurrentInputNotification::LstExternalInput::RefLineIn::
    ~RefLineIn() {}

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
// Notification:external-input-change
// Description: Notification used to indicate that external line input has
// changed state
// -----------------------------------------------------------------------------
NotifExternalInputChange::NotifExternalInputChange(uint32_t id)
    : YangNotif("external-input-change", id) {}

NotifExternalInputChange::~NotifExternalInputChange() {}

YangResult_E
NotifExternalInputChange::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /external-input-change/notification-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpNotificationGroup notificationGroupInst(ITEM_NOTIFICATION_GROUP);
  notificationGroupInst.initialise();
  addGroup(notificationGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-externalio
// Description: This module defines the input state and output configuration for
//              external IO.
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
ModuleORanExternalio::ModuleORanExternalio(uint32_t id)
    : YangModule(
          "o-ran-externalio",
          "o-ran-externalio.yang",
          "o-ran-io",
          "urn:o-ran:external-io:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Container:   /external-io
  // Description: External IO information.
  // -----------------------------------------------------------------------------
  CntExternalIo externalIoInst(ITEM_EXTERNAL_IO);
  externalIoInst.initialise();
  addContainer(externalIoInst);

  // -----------------------------------------------------------------------------
  // Notification:/external-input-change
  // Description: Notification used to indicate that external line input has
  // changed state
  // -----------------------------------------------------------------------------
  NotifExternalInputChange externalInputChangeInst(ITEM_EXTERNAL_INPUT_CHANGE);
  externalInputChangeInst.initialise();
  addNotification(externalInputChangeInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanExternalio::~ModuleORanExternalio() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanExternalio::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanExternalio>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanExternalio::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
