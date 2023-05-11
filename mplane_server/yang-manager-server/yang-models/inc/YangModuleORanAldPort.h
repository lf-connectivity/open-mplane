#ifndef _MODULE_O_RAN_ALD_PORT_H_
#define _MODULE_O_RAN_ALD_PORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAldPort.h
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


namespace Mplane {

namespace ModuleORanAldPort_NS {

// *****************************************************************************
// Type Definitions
// *****************************************************************************

// *****************************************************************************
// Features
// *****************************************************************************
// -----------------------------------------------------------------------------
// Feature
// Description: This feature indicates that the equipment supports the over-current notification
//              capability.
// -----------------------------------------------------------------------------
class FeatureOVERCURRENTSUPPORTED : public YangFeature
{
public:
 FeatureOVERCURRENTSUPPORTED(uint32_t id);
 ~FeatureOVERCURRENTSUPPORTED();

}; // FeatureOVERCURRENTSUPPORTED


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
// Container:   /ald-ports-io
// Description: ALD port information.
//              ALD port of the equipment that can be used to connect External Equipment (Antenna Line Devices).
//              Communication uses AISG over HDLC.
//              Physical connection depends on connector type offered by the port (RS-485 or antenna line)
//              Note: Single instance of ALD Port can point to more than one antenna line devices.
// -----------------------------------------------------------------------------
class CntAldPortsIo : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ALDPORT_GROUP, // Use GrpAldportGroup
 };

 CntAldPortsIo(uint32_t id);
 ~CntAldPortsIo();

 YangResult_E initialise(void);

}; // CntAldPortsIo


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /aldport-group
// Description:
// -----------------------------------------------------------------------------
class GrpAldportGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OVER_CURRENT_SUPPORTED, // LeafOverCurrentSupported
   ITEM_ALD_PORT, // LstAldPort
   ITEM_ALD_PORT_DC_CONTROL, // LstAldPortDcControl
 };

 GrpAldportGroup(uint32_t id);
 ~GrpAldportGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Leaf:        /aldport-group/over-current-supported
 // Description: Set to TRUE when the equipment supports over curent
 // notifications
 // -----------------------------------------------------------------------------
 class LeafOverCurrentSupported : public YangLeaf {
  public:
   LeafOverCurrentSupported(uint32_t id);
   ~LeafOverCurrentSupported();

 }; // LeafOverCurrentSupported

 // -----------------------------------------------------------------------------
 // List:        /aldport-group/ald-port
 // Description: Leaf nodes describing ALD Port
 // -----------------------------------------------------------------------------
 class LstAldPort : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PORT_ID, // LeafPortId
     ITEM_DC_CONTROL_SUPPORT, // LeafDcControlSupport
     ITEM_DC_ENABLED_STATUS, // LeafDcEnabledStatus
     ITEM_SUPPORTED_CONNECTOR, // LeafSupportedConnector
   };

   LstAldPort(uint32_t id);
   ~LstAldPort();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port/name
   // Description: A name that is unique that identifies a ald port instance.
   //              This name may be used in fault management to refer to a fault
   //              source or affected object
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port/port-id
   // Description: A number which identifies an ALD Port.
   //              The number of the Physical ALD port connector in the module.
   //              If the module supports 2 ALD Port connectors, use 0 and 1.
   // -----------------------------------------------------------------------------
   class LeafPortId : public YangLeaf {
    public:
     LeafPortId(uint32_t id);
     ~LeafPortId();

   }; // LeafPortId

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port/dc-control-support
   // Description: It is shown that on/off in the DC power supply is possible.
   //              In case of False, power supply is always on.
   // -----------------------------------------------------------------------------
   class LeafDcControlSupport : public YangLeaf {
    public:
     LeafDcControlSupport(uint32_t id);
     ~LeafDcControlSupport();

   }; // LeafDcControlSupport

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port/dc-enabled-status
   // Description: Status of DC voltage enabled on antenna line.
   //              Valid only in case dc-control-support is true.
   // -----------------------------------------------------------------------------
   class LeafDcEnabledStatus : public YangLeaf {
    public:
     LeafDcEnabledStatus(uint32_t id);
     ~LeafDcEnabledStatus();

   }; // LeafDcEnabledStatus

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port/supported-connector
   // Description: Informs about the connectors of Module which ALDs are
   // connected to.
   //              This value is depending on HW design.
   // -----------------------------------------------------------------------------
   class LeafSupportedConnector : public YangLeaf {
    public:
     // Informs about the connectors of Module which ALDs are connected to.
     // This value is depending on HW design.
     enum class SupportedConnector_E : uint32_t {
       ANTENNA_CONNECTOR, // This ald port is related to antenna connector
       RS485_PORT, // This ald port is related to RS485 port

       Num_SupportedConnector_E
     };

     LeafSupportedConnector(uint32_t id);
     ~LeafSupportedConnector();

   }; // LeafSupportedConnector

 }; // LstAldPort

 // -----------------------------------------------------------------------------
 // List:        /aldport-group/ald-port-dc-control
 // Description: Container needed to manage DC on ALD ports
 // -----------------------------------------------------------------------------
 class LstAldPortDcControl : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_DC_ENABLED, // LeafDcEnabled
     ITEM_NAME, // RefName
   };

   LstAldPortDcControl(uint32_t id);
   ~LstAldPortDcControl();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /aldport-group/ald-port-dc-control/dc-enabled
   // Description: If dc-control-support is true case, this leaf is effective.
   //              If dc-control-support is not true this leaf makes no action
   //              In case of true, the power supply shall be turned on.
   // -----------------------------------------------------------------------------
   class LeafDcEnabled : public YangLeaf {
    public:
     LeafDcEnabled(uint32_t id);
     ~LeafDcEnabled();

   }; // LeafDcEnabled

   // -----------------------------------------------------------------------------
   // Reference:   /aldport-group/ald-port-dc-control/name
   // Description: Name derived from unmodifiable list ald-port
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

 }; // LstAldPortDcControl

}; // GrpAldportGroup

// -----------------------------------------------------------------------------
// Grouping:    /overcurrent-group
// Description:
// -----------------------------------------------------------------------------
class GrpOvercurrentGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OVERLOAD_CONDITION, // CntOverloadCondition
 };

 GrpOvercurrentGroup(uint32_t id);
 ~GrpOvercurrentGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /overcurrent-group/overload-condition
 // Description: Container used in notification
 // -----------------------------------------------------------------------------
 class CntOverloadCondition : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_OVERLOADED_PORTS, // LstOverloadedPorts
   };

   CntOverloadCondition(uint32_t id);
   ~CntOverloadCondition();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // List:        /overcurrent-group/overload-condition/overloaded-ports
   // Description: List of overloaded ports
   // -----------------------------------------------------------------------------
   class LstOverloadedPorts : public YangList {
    public:
     // Item IDs
     enum : uint32_t {};

     LstOverloadedPorts(uint32_t id);
     ~LstOverloadedPorts();

     YangResult_E initialise(void);

   }; // LstOverloadedPorts

 }; // CntOverloadCondition

}; // GrpOvercurrentGroup

// -----------------------------------------------------------------------------
// Grouping:    /dc-enabled-group
// Description:
// -----------------------------------------------------------------------------
class GrpDcEnabledGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_ALD_PORT, // LstAldPort
 };

 GrpDcEnabledGroup(uint32_t id);
 ~GrpDcEnabledGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /dc-enabled-group/ald-port
 // Description: list of ald-ports that has its dc-enabled-status changed
 // -----------------------------------------------------------------------------
 class LstAldPort : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // RefName
     ITEM_DC_ENABLED_STATUS, // RefDcEnabledStatus
   };

   LstAldPort(uint32_t id);
   ~LstAldPort();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Reference:   /dc-enabled-group/ald-port/name
   // Description: Name of port which has changed
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

   // -----------------------------------------------------------------------------
   // Reference:   /dc-enabled-group/ald-port/dc-enabled-status
   // Description: New staus of dc-enabled-status
   // -----------------------------------------------------------------------------
   class RefDcEnabledStatus : public YangReference {
    public:
     RefDcEnabledStatus(uint32_t id);
     ~RefDcEnabledStatus();

   }; // RefDcEnabledStatus

 }; // LstAldPort

}; // GrpDcEnabledGroup


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
// Notification:/overcurrent-report
// Description: The equipment is able to report overcurrent condition about Port.
//              This function is depending on HW design.
//              The notification depend on power consumption which connected ALD devices and module.
// -----------------------------------------------------------------------------
class NotifOvercurrentReport : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OVERCURRENT_GROUP, // Use GrpOvercurrentGroup
 };

 NotifOvercurrentReport(uint32_t id);
 ~NotifOvercurrentReport();

 YangResult_E initialise(void);

}; // NotifOvercurrentReport

// -----------------------------------------------------------------------------
// Notification:/dc-enabled-status-change
// Description: The equipment is able to report the change of 'dc-enabled-status' of the ald-port.
//              This is applicable when the leaf 'dc-control-support' of the ald-pot is 'TRUE'.
// -----------------------------------------------------------------------------
class NotifDcEnabledStatusChange : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_DC_ENABLED_GROUP, // Use GrpDcEnabledGroup
 };

 NotifDcEnabledStatusChange(uint32_t id);
 ~NotifDcEnabledStatusChange();

 YangResult_E initialise(void);

}; // NotifDcEnabledStatusChange


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
class ModuleORanAldPort : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_OVERCURRENT_SUPPORTED, // Feature
   ITEM_ALD_PORTS_IO, // CntAldPortsIo
   ITEM_OVERCURRENT_REPORT, // NotifOvercurrentReport
   ITEM_DC_ENABLED_STATUS_CHANGE, // NotifDcEnabledStatusChange
 };

 ModuleORanAldPort(uint32_t id);
 ~ModuleORanAldPort();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanAldPort_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_ALD_PORT_H_ */
