#ifndef _MODULE_O_RAN_EXTERNALIO_H_
#define _MODULE_O_RAN_EXTERNALIO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanExternalio.h
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

namespace ModuleORanExternalio_NS {

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
// Container:   /external-io
// Description: External IO information.
// -----------------------------------------------------------------------------
class CntExternalIo : public YangContainer
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_EXTERNAL_IO_GROUP, // Use GrpExternalIoGroup
 };

 CntExternalIo(uint32_t id);
 ~CntExternalIo();

 YangResult_E initialise(void);

}; // CntExternalIo


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /external-io-group
// Description:
// -----------------------------------------------------------------------------
class GrpExternalIoGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_INPUT, // LstInput
   ITEM_OUTPUT, // LstOutput
   ITEM_OUTPUT_SETTING, // LstOutputSetting
 };

 GrpExternalIoGroup(uint32_t id);
 ~GrpExternalIoGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // List:        /external-io-group/input
 // Description: Leaf nodes describing external line inputs
 // -----------------------------------------------------------------------------
 class LstInput : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PORT_IN, // LeafPortIn
     ITEM_LINE_IN, // LeafLineIn
   };

   LstInput(uint32_t id);
   ~LstInput();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/input/name
   // Description: A unique name that identifies an input port instance.
   //              This name may be used in fault management to refer to a fault
   //              source or affected object
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/input/port-in
   // Description: A number which identifies an external input port.
   // -----------------------------------------------------------------------------
   class LeafPortIn : public YangLeaf {
    public:
     LeafPortIn(uint32_t id);
     ~LeafPortIn();

   }; // LeafPortIn

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/input/line-in
   // Description: Value TRUE indicates that circuit is open.
   //              Value FALSE indicates that circuit is closed.
   //
   //              Usually when nothing is connected to the line
   //              the value is TRUE. The details of external
   //              line-in implementation are HW specific.
   // -----------------------------------------------------------------------------
   class LeafLineIn : public YangLeaf {
    public:
     LeafLineIn(uint32_t id);
     ~LeafLineIn();

   }; // LeafLineIn

 }; // LstInput

 // -----------------------------------------------------------------------------
 // List:        /external-io-group/output
 // Description: Leaf nodes describing external line outputs
 // -----------------------------------------------------------------------------
 class LstOutput : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_NAME, // LeafName
     ITEM_PORT_OUT, // LeafPortOut
   };

   LstOutput(uint32_t id);
   ~LstOutput();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/output/name
   // Description: A name that is unique that identifies an output port
   // instance.
   //              This name may be used in fault management to refer to
   //              a fault source or affected object
   // -----------------------------------------------------------------------------
   class LeafName : public YangLeaf {
    public:
     LeafName(uint32_t id);
     ~LeafName();

   }; // LeafName

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/output/port-out
   // Description: A number which identifies an external output port.
   // -----------------------------------------------------------------------------
   class LeafPortOut : public YangLeaf {
    public:
     LeafPortOut(uint32_t id);
     ~LeafPortOut();

   }; // LeafPortOut

 }; // LstOutput

 // -----------------------------------------------------------------------------
 // List:        /external-io-group/output-setting
 // Description: List allowing to set output line state
 // -----------------------------------------------------------------------------
 class LstOutputSetting : public YangList {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_LINE_OUT, // LeafLineOut
     ITEM_NAME, // RefName
   };

   LstOutputSetting(uint32_t id);
   ~LstOutputSetting();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // Leaf:        /external-io-group/output-setting/line-out
   // Description: Value TRUE indicates that circuit is in its natural
   // state.
   //              Value FALSE indicates that circuit is not in its
   //              natural state.
   // -----------------------------------------------------------------------------
   class LeafLineOut : public YangLeaf {
    public:
     LeafLineOut(uint32_t id);
     ~LeafLineOut();

   }; // LeafLineOut

   // -----------------------------------------------------------------------------
   // Reference:   /external-io-group/output-setting/name
   // Description: Name derived from unmodifiable list external-io
   // -----------------------------------------------------------------------------
   class RefName : public YangReference {
    public:
     RefName(uint32_t id);
     ~RefName();

   }; // RefName

 }; // LstOutputSetting

}; // GrpExternalIoGroup

// -----------------------------------------------------------------------------
// Grouping:    /notification-group
// Description:
// -----------------------------------------------------------------------------
class GrpNotificationGroup : public YangGroup
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_CURRENT_INPUT_NOTIFICATION, // CntCurrentInputNotification
 };

 GrpNotificationGroup(uint32_t id);
 ~GrpNotificationGroup();

 YangResult_E initialise(void);

 // -----------------------------------------------------------------------------
 // Container:   /notification-group/current-input-notification
 // Description: a container for the state of the input ports
 // -----------------------------------------------------------------------------
 class CntCurrentInputNotification : public YangContainer {
  public:
   // Item IDs
   enum : uint32_t {
     ITEM_EXTERNAL_INPUT, // LstExternalInput
   };

   CntCurrentInputNotification(uint32_t id);
   ~CntCurrentInputNotification();

   YangResult_E initialise(void);

   // -----------------------------------------------------------------------------
   // List:        /notification-group/current-input-notification/external-input
   // Description: a list of the input ports and their state
   // -----------------------------------------------------------------------------
   class LstExternalInput : public YangList {
    public:
     // Item IDs
     enum : uint32_t {
       ITEM_NAME, // RefName
       ITEM_IO_PORT, // RefIoPort
       ITEM_LINE_IN, // RefLineIn
     };

     LstExternalInput(uint32_t id);
     ~LstExternalInput();

     YangResult_E initialise(void);

     // -----------------------------------------------------------------------------
     // Reference:
     // /notification-group/current-input-notification/external-input/name
     // Description: the name of the ald-port
     // -----------------------------------------------------------------------------
     class RefName : public YangReference {
      public:
       RefName(uint32_t id);
       ~RefName();

     }; // RefName

     // -----------------------------------------------------------------------------
     // Reference:
     // /notification-group/current-input-notification/external-input/io-port
     // Description: the external input port
     // -----------------------------------------------------------------------------
     class RefIoPort : public YangReference {
      public:
       RefIoPort(uint32_t id);
       ~RefIoPort();

     }; // RefIoPort

     // -----------------------------------------------------------------------------
     // Reference:
     // /notification-group/current-input-notification/external-input/line-in
     // Description: the state of the external input port
     // -----------------------------------------------------------------------------
     class RefLineIn : public YangReference {
      public:
       RefLineIn(uint32_t id);
       ~RefLineIn();

     }; // RefLineIn

   }; // LstExternalInput

 }; // CntCurrentInputNotification

}; // GrpNotificationGroup


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
// Notification:/external-input-change
// Description: Notification used to indicate that external line input has changed state
// -----------------------------------------------------------------------------
class NotifExternalInputChange : public YangNotif
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_NOTIFICATION_GROUP, // Use GrpNotificationGroup
 };

 NotifExternalInputChange(uint32_t id);
 ~NotifExternalInputChange();

 YangResult_E initialise(void);

}; // NotifExternalInputChange


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
class ModuleORanExternalio : public YangModule
{
public:
 // Item IDs
 enum : uint32_t {
   ITEM_EXTERNAL_IO, // CntExternalIo
   ITEM_EXTERNAL_INPUT_CHANGE, // NotifExternalInputChange
 };

 ModuleORanExternalio(uint32_t id);
 ~ModuleORanExternalio();

 /**
  * Create singleton
  */
 static std::shared_ptr<YangModule> createModule(uint32_t id);

 /**
  * Access singleton
  */
 static std::shared_ptr<YangModule> singleton();
};

} /* namespace ModuleORanExternalio_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_EXTERNALIO_H_ */
