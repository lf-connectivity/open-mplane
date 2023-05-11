/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAldPort.cpp
 * \brief     Module ORanAldPort interface
 *
 *
 * \details   This file defines the YANG module o-ran-ald-port interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-ald-port"
 *            YANG Filename:    "o-ran-ald-port.yang"
 *            Module Prefix:    "o-ran-ald-port"
 *            Module namespace: "urn:o-ran:ald-port:1.0"
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
#include "YangModuleORanAldPort.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanAldPort_NS;

// Add user code here
// %%->

// <-%%

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports the
// over-current notification
//              capability.
// -----------------------------------------------------------------------------
FeatureOVERCURRENTSUPPORTED::FeatureOVERCURRENTSUPPORTED(uint32_t id)
    : YangFeature("OVERCURRENT-SUPPORTED", id) {}

FeatureOVERCURRENTSUPPORTED::~FeatureOVERCURRENTSUPPORTED() {}

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
// Container:   ald-ports-io
// Description: ALD port information.
//              ALD port of the equipment that can be used to connect External
//              Equipment (Antenna Line Devices). Communication uses AISG over
//              HDLC. Physical connection depends on connector type offered by
//              the port (RS-485 or antenna line) Note: Single instance of ALD
//              Port can point to more than one antenna line devices.
// -----------------------------------------------------------------------------
CntAldPortsIo::CntAldPortsIo(uint32_t id) : YangContainer("ald-ports-io", id) {}

CntAldPortsIo::~CntAldPortsIo() {}

YangResult_E
CntAldPortsIo::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /ald-ports-io/aldport-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpAldportGroup aldportGroupInst(ITEM_ALDPORT_GROUP);
  aldportGroupInst.initialise();
  addGroup(aldportGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    aldport-group
// Description:
// -----------------------------------------------------------------------------
GrpAldportGroup::GrpAldportGroup(uint32_t id)
    : YangGroup("aldport-group", id) {}

GrpAldportGroup::~GrpAldportGroup() {}

YangResult_E
GrpAldportGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/over-current-supported
  // Description: Set to TRUE when the equipment supports over curent
  // notifications Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafOverCurrentSupported overCurrentSupportedInst(
      ITEM_OVER_CURRENT_SUPPORTED);
  addLeaf(overCurrentSupportedInst);

  // -----------------------------------------------------------------------------
  // List:        /aldport-group/ald-port
  // Description: Leaf nodes describing ALD Port
  // Array Key:
  // -----------------------------------------------------------------------------
  LstAldPort aldPortInst(ITEM_ALD_PORT);
  aldPortInst.initialise();
  addList(aldPortInst);

  // -----------------------------------------------------------------------------
  // List:        /aldport-group/ald-port-dc-control
  // Description: Container needed to manage DC on ALD ports
  // Array Key:
  // -----------------------------------------------------------------------------
  LstAldPortDcControl aldPortDcControlInst(ITEM_ALD_PORT_DC_CONTROL);
  aldPortDcControlInst.initialise();
  addList(aldPortDcControlInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/over-current-supported
// Description: Set to TRUE when the equipment supports over curent
// notifications
// -----------------------------------------------------------------------------
GrpAldportGroup::LeafOverCurrentSupported::LeafOverCurrentSupported(uint32_t id)
    : YangLeaf("over-current-supported", id) {}

GrpAldportGroup::LeafOverCurrentSupported::~LeafOverCurrentSupported() {}

// -----------------------------------------------------------------------------
// List:        ald-port
// Description: Leaf nodes describing ALD Port
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LstAldPort(uint32_t id)
    : YangList("ald-port", id) {}

GrpAldportGroup::LstAldPort::~LstAldPort() {}

YangResult_E
GrpAldportGroup::LstAldPort::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port/name
  // Description: A name that is unique that identifies a ald port instance.
  //              This name may be used in fault management to refer to a fault
  //              source or affected object
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafName nameInst(ITEM_NAME);
  addLeaf(nameInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port/port-id
  // Description: A number which identifies an ALD Port.
  //              The number of the Physical ALD port connector in the module.
  //              If the module supports 2 ALD Port connectors, use 0 and 1.
  // Type:        uint8
  // Units:
  // -----------------------------------------------------------------------------
  LeafPortId portIdInst(ITEM_PORT_ID);
  addLeaf(portIdInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port/dc-control-support
  // Description: It is shown that on/off in the DC power supply is possible.
  //              In case of False, power supply is always on.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafDcControlSupport dcControlSupportInst(ITEM_DC_CONTROL_SUPPORT);
  addLeaf(dcControlSupportInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port/dc-enabled-status
  // Description: Status of DC voltage enabled on antenna line.
  //              Valid only in case dc-control-support is true.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafDcEnabledStatus dcEnabledStatusInst(ITEM_DC_ENABLED_STATUS);
  addLeaf(dcEnabledStatusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port/supported-connector
  // Description: Informs about the connectors of Module which ALDs are
  // connected to.
  //              This value is depending on HW design.
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafSupportedConnector supportedConnectorInst(ITEM_SUPPORTED_CONNECTOR);
  addLeaf(supportedConnectorInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port/name
// Description: A name that is unique that identifies a ald port instance.
//              This name may be used in fault management to refer to a fault
//              source or affected object
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LeafName::LeafName(uint32_t id)
    : YangLeaf("name", id) {}

GrpAldportGroup::LstAldPort::LeafName::~LeafName() {}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port/port-id
// Description: A number which identifies an ALD Port.
//              The number of the Physical ALD port connector in the module.
//              If the module supports 2 ALD Port connectors, use 0 and 1.
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LeafPortId::LeafPortId(uint32_t id)
    : YangLeaf("port-id", id) {}

GrpAldportGroup::LstAldPort::LeafPortId::~LeafPortId() {}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port/dc-control-support
// Description: It is shown that on/off in the DC power supply is possible.
//              In case of False, power supply is always on.
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LeafDcControlSupport::LeafDcControlSupport(
    uint32_t id)
    : YangLeaf("dc-control-support", id) {}

GrpAldportGroup::LstAldPort::LeafDcControlSupport::~LeafDcControlSupport() {}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port/dc-enabled-status
// Description: Status of DC voltage enabled on antenna line.
//              Valid only in case dc-control-support is true.
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LeafDcEnabledStatus::LeafDcEnabledStatus(
    uint32_t id)
    : YangLeaf("dc-enabled-status", id) {}

GrpAldportGroup::LstAldPort::LeafDcEnabledStatus::~LeafDcEnabledStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port/supported-connector
// Description: Informs about the connectors of Module which ALDs are connected
// to.
//              This value is depending on HW design.
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPort::LeafSupportedConnector::LeafSupportedConnector(
    uint32_t id)
    : YangLeaf("supported-connector", id) {}

GrpAldportGroup::LstAldPort::LeafSupportedConnector::~LeafSupportedConnector() {
}

// -----------------------------------------------------------------------------
// List:        ald-port-dc-control
// Description: Container needed to manage DC on ALD ports
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPortDcControl::LstAldPortDcControl(uint32_t id)
    : YangList("ald-port-dc-control", id) {}

GrpAldportGroup::LstAldPortDcControl::~LstAldPortDcControl() {}

YangResult_E
GrpAldportGroup::LstAldPortDcControl::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /aldport-group/ald-port-dc-control/dc-enabled
  // Description: If dc-control-support is true case, this leaf is effective.
  //              If dc-control-support is not true this leaf makes no action
  //              In case of true, the power supply shall be turned on.
  // Type:        UNKNOWN:3
  // Units:
  // -----------------------------------------------------------------------------
  LeafDcEnabled dcEnabledInst(ITEM_DC_ENABLED);
  addLeaf(dcEnabledInst);

  // -----------------------------------------------------------------------------
  // Reference:   /aldport-group/ald-port-dc-control/name
  // Description: Name derived from unmodifiable list ald-port
  // Ref:         /ald-ports-io/ald-port/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /aldport-group/ald-port-dc-control/dc-enabled
// Description: If dc-control-support is true case, this leaf is effective.
//              If dc-control-support is not true this leaf makes no action
//              In case of true, the power supply shall be turned on.
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPortDcControl::LeafDcEnabled::LeafDcEnabled(uint32_t id)
    : YangLeaf("dc-enabled", id) {}

GrpAldportGroup::LstAldPortDcControl::LeafDcEnabled::~LeafDcEnabled() {}

// -----------------------------------------------------------------------------
// Reference:   /aldport-group/ald-port-dc-control/name
// Description: Name derived from unmodifiable list ald-port
// -----------------------------------------------------------------------------
GrpAldportGroup::LstAldPortDcControl::RefName::RefName(uint32_t id)
    : YangReference("name", id, "/ald-ports-io/ald-port/name") {}

GrpAldportGroup::LstAldPortDcControl::RefName::~RefName() {}

// -----------------------------------------------------------------------------
// Grouping:    overcurrent-group
// Description:
// -----------------------------------------------------------------------------
GrpOvercurrentGroup::GrpOvercurrentGroup(uint32_t id)
    : YangGroup("overcurrent-group", id) {}

GrpOvercurrentGroup::~GrpOvercurrentGroup() {}

YangResult_E
GrpOvercurrentGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // Container:   /overcurrent-group/overload-condition
  // Description: Container used in notification
  // -----------------------------------------------------------------------------
  CntOverloadCondition overloadConditionInst(ITEM_OVERLOAD_CONDITION);
  overloadConditionInst.initialise();
  addContainer(overloadConditionInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Container:   overload-condition
// Description: Container used in notification
// -----------------------------------------------------------------------------
GrpOvercurrentGroup::CntOverloadCondition::CntOverloadCondition(uint32_t id)
    : YangContainer("overload-condition", id) {}

GrpOvercurrentGroup::CntOverloadCondition::~CntOverloadCondition() {}

YangResult_E
GrpOvercurrentGroup::CntOverloadCondition::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /overcurrent-group/overload-condition/overloaded-ports
  // Description: List of overloaded ports
  // Array Key:
  // -----------------------------------------------------------------------------
  LstOverloadedPorts overloadedPortsInst(ITEM_OVERLOADED_PORTS);
  overloadedPortsInst.initialise();
  addList(overloadedPortsInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        overloaded-ports
// Description: List of overloaded ports
// -----------------------------------------------------------------------------
GrpOvercurrentGroup::CntOverloadCondition::LstOverloadedPorts::
    LstOverloadedPorts(uint32_t id)
    : YangList("overloaded-ports", id) {}

GrpOvercurrentGroup::CntOverloadCondition::LstOverloadedPorts::
    ~LstOverloadedPorts() {}

YangResult_E
GrpOvercurrentGroup::CntOverloadCondition::LstOverloadedPorts::initialise(
    void) {

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Grouping:    dc-enabled-group
// Description:
// -----------------------------------------------------------------------------
GrpDcEnabledGroup::GrpDcEnabledGroup(uint32_t id)
    : YangGroup("dc-enabled-group", id) {}

GrpDcEnabledGroup::~GrpDcEnabledGroup() {}

YangResult_E
GrpDcEnabledGroup::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /dc-enabled-group/ald-port
  // Description: list of ald-ports that has its dc-enabled-status changed
  // Array Key:
  // -----------------------------------------------------------------------------
  LstAldPort aldPortInst(ITEM_ALD_PORT);
  aldPortInst.initialise();
  addList(aldPortInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        ald-port
// Description: list of ald-ports that has its dc-enabled-status changed
// -----------------------------------------------------------------------------
GrpDcEnabledGroup::LstAldPort::LstAldPort(uint32_t id)
    : YangList("ald-port", id) {}

GrpDcEnabledGroup::LstAldPort::~LstAldPort() {}

YangResult_E
GrpDcEnabledGroup::LstAldPort::initialise(void) {
  // -----------------------------------------------------------------------------
  // Reference:   /dc-enabled-group/ald-port/name
  // Description: Name of port which has changed
  // Ref:         /ald-ports-io/ald-port/name
  // Units:
  // -----------------------------------------------------------------------------
  RefName nameInst(ITEM_NAME);
  addReference(nameInst);

  // -----------------------------------------------------------------------------
  // Reference:   /dc-enabled-group/ald-port/dc-enabled-status
  // Description: New staus of dc-enabled-status
  // Ref:         /ald-ports-io/ald-port/dc-enabled-status
  // Units:
  // -----------------------------------------------------------------------------
  RefDcEnabledStatus dcEnabledStatusInst(ITEM_DC_ENABLED_STATUS);
  addReference(dcEnabledStatusInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Reference:   /dc-enabled-group/ald-port/name
// Description: Name of port which has changed
// -----------------------------------------------------------------------------
GrpDcEnabledGroup::LstAldPort::RefName::RefName(uint32_t id)
    : YangReference("name", id, "/ald-ports-io/ald-port/name") {}

GrpDcEnabledGroup::LstAldPort::RefName::~RefName() {}

// -----------------------------------------------------------------------------
// Reference:   /dc-enabled-group/ald-port/dc-enabled-status
// Description: New staus of dc-enabled-status
// -----------------------------------------------------------------------------
GrpDcEnabledGroup::LstAldPort::RefDcEnabledStatus::RefDcEnabledStatus(
    uint32_t id)
    : YangReference(
          "dc-enabled-status", id, "/ald-ports-io/ald-port/dc-enabled-status") {
}

GrpDcEnabledGroup::LstAldPort::RefDcEnabledStatus::~RefDcEnabledStatus() {}

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
// Notification:overcurrent-report
// Description: The equipment is able to report overcurrent condition about
// Port.
//              This function is depending on HW design.
//              The notification depend on power consumption which connected ALD
//              devices and module.
// -----------------------------------------------------------------------------
NotifOvercurrentReport::NotifOvercurrentReport(uint32_t id)
    : YangNotif("overcurrent-report", id) {}

NotifOvercurrentReport::~NotifOvercurrentReport() {}

YangResult_E
NotifOvercurrentReport::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /overcurrent-report/overcurrent-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpOvercurrentGroup overcurrentGroupInst(ITEM_OVERCURRENT_GROUP);
  overcurrentGroupInst.initialise();
  addGroup(overcurrentGroupInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Notification:dc-enabled-status-change
// Description: The equipment is able to report the change of
// 'dc-enabled-status' of the ald-port.
//              This is applicable when the leaf 'dc-control-support' of the
//              ald-pot is 'TRUE'.
// -----------------------------------------------------------------------------
NotifDcEnabledStatusChange::NotifDcEnabledStatusChange(uint32_t id)
    : YangNotif("dc-enabled-status-change", id) {}

NotifDcEnabledStatusChange::~NotifDcEnabledStatusChange() {}

YangResult_E
NotifDcEnabledStatusChange::initialise(void) {
  // -----------------------------------------------------------------------------
  // Uses:        /dc-enabled-status-change/dc-enabled-group
  // Description:
  // -----------------------------------------------------------------------------
  GrpDcEnabledGroup dcEnabledGroupInst(ITEM_DC_ENABLED_GROUP);
  dcEnabledGroupInst.initialise();
  addGroup(dcEnabledGroupInst);

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-ald-port
// Description: This module defines the input state and output configuration for
//              the Antenna Line Device capability.
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
ModuleORanAldPort::ModuleORanAldPort(uint32_t id)
    : YangModule(
          "o-ran-ald-port",
          "o-ran-ald-port.yang",
          "o-ran-ald-port",
          "urn:o-ran:ald-port:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Feature
  // Description: This feature indicates that the equipment supports the
  // over-current notification
  //              capability.
  // -----------------------------------------------------------------------------
  FeatureOVERCURRENTSUPPORTED OVERCURRENTSUPPORTEDInst(
      ITEM_OVERCURRENT_SUPPORTED);
  addFeature(OVERCURRENTSUPPORTEDInst);

  // -----------------------------------------------------------------------------
  // Container:   /ald-ports-io
  // Description: ALD port information.
  //              ALD port of the equipment that can be used to connect External
  //              Equipment (Antenna Line Devices). Communication uses AISG over
  //              HDLC. Physical connection depends on connector type offered by
  //              the port (RS-485 or antenna line) Note: Single instance of ALD
  //              Port can point to more than one antenna line devices.
  // -----------------------------------------------------------------------------
  CntAldPortsIo aldPortsIoInst(ITEM_ALD_PORTS_IO);
  aldPortsIoInst.initialise();
  addContainer(aldPortsIoInst);

  // -----------------------------------------------------------------------------
  // Notification:/overcurrent-report
  // Description: The equipment is able to report overcurrent condition about
  // Port.
  //              This function is depending on HW design.
  //              The notification depend on power consumption which connected
  //              ALD devices and module.
  // -----------------------------------------------------------------------------
  NotifOvercurrentReport overcurrentReportInst(ITEM_OVERCURRENT_REPORT);
  overcurrentReportInst.initialise();
  addNotification(overcurrentReportInst);

  // -----------------------------------------------------------------------------
  // Notification:/dc-enabled-status-change
  // Description: The equipment is able to report the change of
  // 'dc-enabled-status' of the ald-port.
  //              This is applicable when the leaf 'dc-control-support' of the
  //              ald-pot is 'TRUE'.
  // -----------------------------------------------------------------------------
  NotifDcEnabledStatusChange dcEnabledStatusChangeInst(
      ITEM_DC_ENABLED_STATUS_CHANGE);
  dcEnabledStatusChangeInst.initialise();
  addNotification(dcEnabledStatusChangeInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanAldPort::~ModuleORanAldPort() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanAldPort::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanAldPort>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanAldPort::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
