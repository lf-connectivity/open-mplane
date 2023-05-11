/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTrace.cpp
 * \brief     Module ORanTrace interface
 *
 *
 * \details   This file defines the YANG module o-ran-trace interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-trace"
 *            YANG Filename:    "o-ran-trace.yang"
 *            Module Prefix:    "o-ran-trace"
 *            Module namespace: "urn:o-ran:trace:1.0"
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
#include "YangModuleORanTrace.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------

using namespace Mplane;
using namespace ModuleORanTrace_NS;

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
// Grouping:    trace-status-grouping
// Description: grouping used for trace RPCs
// -----------------------------------------------------------------------------
GrpTraceStatusGrouping::GrpTraceStatusGrouping(uint32_t id)
    : YangGroup("trace-status-grouping", id) {}

GrpTraceStatusGrouping::~GrpTraceStatusGrouping() {}

YangResult_E
GrpTraceStatusGrouping::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /trace-status-grouping/status
  // Description: result of rpc operation
  // Type:        enum
  // Units:
  // -----------------------------------------------------------------------------
  LeafStatus statusInst(ITEM_STATUS);
  addLeaf(statusInst);

  // -----------------------------------------------------------------------------
  // Leaf:        /trace-status-grouping/failure-reason
  // Description: free form text description why error occurred
  // Type:        string
  // Units:
  // -----------------------------------------------------------------------------
  LeafFailureReason failureReasonInst(ITEM_FAILURE_REASON);
  addLeaf(failureReasonInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /trace-status-grouping/status
// Description: result of rpc operation
// -----------------------------------------------------------------------------
GrpTraceStatusGrouping::LeafStatus::LeafStatus(uint32_t id)
    : YangLeaf("status", id) {}

GrpTraceStatusGrouping::LeafStatus::~LeafStatus() {}

// -----------------------------------------------------------------------------
// Leaf:        /trace-status-grouping/failure-reason
// Description: free form text description why error occurred
// -----------------------------------------------------------------------------
GrpTraceStatusGrouping::LeafFailureReason::LeafFailureReason(uint32_t id)
    : YangLeaf("failure-reason", id) {}

GrpTraceStatusGrouping::LeafFailureReason::~LeafFailureReason() {}

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
// Notification:trace-log-generated
// Description: When new log file generated, send this notification.
// -----------------------------------------------------------------------------
NotifTraceLogGenerated::NotifTraceLogGenerated(uint32_t id)
    : YangNotif("trace-log-generated", id) {}

NotifTraceLogGenerated::~NotifTraceLogGenerated() {}

YangResult_E
NotifTraceLogGenerated::initialise(void) {
  // -----------------------------------------------------------------------------
  // Leaf:        /trace-log-generated/is-notification-last
  // Description: Informs if notification is last - the one after receiving
  // stop-trace-logs rpc. Type:        UNKNOWN:3 Units:
  // -----------------------------------------------------------------------------
  LeafIsNotificationLast isNotificationLastInst(ITEM_IS_NOTIFICATION_LAST);
  addLeaf(isNotificationLastInst);

  // -----------------------------------------------------------------------------
  // List:        /trace-log-generated/log-file-name
  // Description: The list of trace log file names on the O-RU.
  // Array Key:
  // -----------------------------------------------------------------------------
  LstLogFileName logFileNameInst(ITEM_LOG_FILE_NAME);
  logFileNameInst.initialise();
  addList(logFileNameInst);

  return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /trace-log-generated/is-notification-last
// Description: Informs if notification is last - the one after receiving
// stop-trace-logs rpc.
// -----------------------------------------------------------------------------
NotifTraceLogGenerated::LeafIsNotificationLast::LeafIsNotificationLast(
    uint32_t id)
    : YangLeaf("is-notification-last", id) {}

NotifTraceLogGenerated::LeafIsNotificationLast::~LeafIsNotificationLast() {}

// -----------------------------------------------------------------------------
// List:        log-file-name
// Description: The list of trace log file names on the O-RU.
// -----------------------------------------------------------------------------
NotifTraceLogGenerated::LstLogFileName::LstLogFileName(uint32_t id)
    : YangList("log-file-name", id) {}

NotifTraceLogGenerated::LstLogFileName::~LstLogFileName() {}

YangResult_E
NotifTraceLogGenerated::LstLogFileName::initialise(void) {

  return YangResult_E::OK;
}

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-trace
// Description: This module defines the operations for the trace logs.
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
ModuleORanTrace::ModuleORanTrace(uint32_t id)
    : YangModule(
          "o-ran-trace",
          "o-ran-trace.yang",
          "o-ran-trace",
          "urn:o-ran:trace:1.0",
          id)
// Add user code here
// %%->

// <-%%
{
  // -----------------------------------------------------------------------------
  // Notification:/trace-log-generated
  // Description: When new log file generated, send this notification.
  // -----------------------------------------------------------------------------
  NotifTraceLogGenerated traceLogGeneratedInst(ITEM_TRACE_LOG_GENERATED);
  traceLogGeneratedInst.initialise();
  addNotification(traceLogGeneratedInst);

  // Add user code here
  // %%->

  // <-%%
}

ModuleORanTrace::~ModuleORanTrace() {
  // Add user code here
  // %%->

  // <-%%
}

std::shared_ptr<YangModule>
ModuleORanTrace::createModule(uint32_t id) {
  std::shared_ptr<YangModule> instance(std::make_shared<ModuleORanTrace>(id));
  // assert(instance->getId() != ITEM_NULL);
  return instance;
}

std::shared_ptr<YangModule>
ModuleORanTrace::singleton() {
  // call create() with dummy values
  return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
