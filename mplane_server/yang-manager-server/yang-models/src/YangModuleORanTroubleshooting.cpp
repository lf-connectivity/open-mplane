/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTroubleshooting.cpp
 * \brief     Module ORanTroubleshooting interface
 *
 *
 * \details   This file defines the YANG module o-ran-troubleshooting interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-troubleshooting"
 *            YANG Filename:    "o-ran-troubleshooting.yang"
 *            Module Prefix:    "o-ran-trblsht"
 *            Module namespace: "urn:o-ran:troubleshooting:1.0"
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
#include "YangModuleORanTroubleshooting.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanTroubleshooting_NS;

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    troubleshooting-status-grouping
// Description: grouping used for troubleshooting RPCs
// -----------------------------------------------------------------------------
GrpTroubleshootingStatusGrouping::GrpTroubleshootingStatusGrouping(uint32_t id)
    : YangGroup("troubleshooting-status-grouping", id) {}

GrpTroubleshootingStatusGrouping::~GrpTroubleshootingStatusGrouping() {}

YangResult_E
GrpTroubleshootingStatusGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /troubleshooting-status-grouping/status
  // Description: result of rpc operation
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /troubleshooting-status-grouping/failure-reason
  // Description: free form text description why error occurred
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafFailureReason failureReasonInst(ITEM_FAILURE_REASON);
  addLeaf(failureReasonInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /troubleshooting-status-grouping/status
// Description: result of rpc operation
// -----------------------------------------------------------------------------
GrpTroubleshootingStatusGrouping::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpTroubleshootingStatusGrouping::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /troubleshooting-status-grouping/failure-reason
// Description: free form text description why error occurred
// -----------------------------------------------------------------------------
GrpTroubleshootingStatusGrouping::LeafFailureReason::LeafFailureReason(
    uint32_t id)
    : YangLeaf("failure-reason", id) {}

GrpTroubleshootingStatusGrouping::LeafFailureReason::~LeafFailureReason() {}

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
// Notification:troubleshooting-log-generated
// Description: When new log file generated, send this notification.
// -----------------------------------------------------------------------------
NotifTroubleshootingLogGenerated::NotifTroubleshootingLogGenerated(uint32_t id)
    : YangNotif("troubleshooting-log-generated", id) {}

NotifTroubleshootingLogGenerated::~NotifTroubleshootingLogGenerated() {}

YangResult_E
NotifTroubleshootingLogGenerated::initialise(void) {
  // -----------------------------------------------------------------------------
  // List:        /troubleshooting-log-generated/log-file-name
  // Description: The list of troubleshooting log file names on the O-RU.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstLogFileName logFileNameInst(ITEM_LOG_FILE_NAME);
  logFileNameInst.initialise();
  addList(logFileNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        log-file-name
// Description: The list of troubleshooting log file names on the O-RU.
// -----------------------------------------------------------------------------
NotifTroubleshootingLogGenerated::LstLogFileName::LstLogFileName(uint32_t id)
    : YangList("log-file-name", id) {}

NotifTroubleshootingLogGenerated::LstLogFileName::~LstLogFileName() {}

YangResult_E
NotifTroubleshootingLogGenerated::LstLogFileName::initialise(void) {

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-troubleshooting
// Description: This module defines the operations for the troubleshooting logs.
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
ModuleORanTroubleshooting::ModuleORanTroubleshooting(uint32_t id)
    : YangModule(
          "o-ran-troubleshooting",
          "o-ran-troubleshooting.yang",
          "o-ran-trblsht",
          "urn:o-ran:troubleshooting:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Notification:/troubleshooting-log-generated
  // Description: When new log file generated, send this notification.
  // -----------------------------------------------------------------------------
  NotifTroubleshootingLogGenerated troubleshootingLogGeneratedInst(
      ITEM_TROUBLESHOOTING_LOG_GENERATED);
  troubleshootingLogGeneratedInst.initialise();
  addNotification(troubleshootingLogGeneratedInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanTroubleshooting::~ModuleORanTroubleshooting() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanTroubleshooting::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(
      std::make_shared<ModuleORanTroubleshooting>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanTroubleshooting::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
