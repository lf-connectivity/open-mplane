#ifndef _MODULE_O_RAN_TRACE_H_
#define _MODULE_O_RAN_TRACE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTrace.h
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

namespace ModuleORanTrace_NS {

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

// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /trace-status-grouping
// Description: grouping used for trace RPCs
// -----------------------------------------------------------------------------
class GrpTraceStatusGrouping : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_STATUS,  // LeafStatus
		ITEM_FAILURE_REASON,  // LeafFailureReason
	};

	GrpTraceStatusGrouping(uint32_t id);
	~GrpTraceStatusGrouping();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /trace-status-grouping/status
	// Description: result of rpc operation
	// -----------------------------------------------------------------------------
	class LeafStatus : public YangLeaf
	{
	public:

		// result of rpc operation
		enum class Status_E : uint32_t
		{
			SUCCESS,	// rpc completed correctly
			FAILURE,	// rpc failed

			Num_Status_E
		};

		LeafStatus(uint32_t id);
		~LeafStatus();

	}; // LeafStatus

	// -----------------------------------------------------------------------------
	// Leaf:        /trace-status-grouping/failure-reason
	// Description: free form text description why error occurred
	// -----------------------------------------------------------------------------
	class LeafFailureReason : public YangLeaf
	{
	public:

		LeafFailureReason(uint32_t id);
		~LeafFailureReason();

	}; // LeafFailureReason

}; // GrpTraceStatusGrouping


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
// Notification:/trace-log-generated
// Description: When new log file generated, send this notification.
// -----------------------------------------------------------------------------
class NotifTraceLogGenerated : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_IS_NOTIFICATION_LAST,  // LeafIsNotificationLast
		ITEM_LOG_FILE_NAME,  // LstLogFileName
	};

	NotifTraceLogGenerated(uint32_t id);
	~NotifTraceLogGenerated();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /trace-log-generated/is-notification-last
	// Description: Informs if notification is last - the one after receiving stop-trace-logs rpc.
	// -----------------------------------------------------------------------------
	class LeafIsNotificationLast : public YangLeaf
	{
	public:

		LeafIsNotificationLast(uint32_t id);
		~LeafIsNotificationLast();

	}; // LeafIsNotificationLast

	// -----------------------------------------------------------------------------
	// List:        /trace-log-generated/log-file-name
	// Description: The list of trace log file names on the O-RU.
	// -----------------------------------------------------------------------------
	class LstLogFileName : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
		};

		LstLogFileName(uint32_t id);
		~LstLogFileName();

		YangResult_E initialise(void);

	}; // LstLogFileName

}; // NotifTraceLogGenerated


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-trace
// Description: This module defines the operations for the trace logs.
//
//              Copyright 2019 the O-RAN Alliance.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
//              AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//              IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//              ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//              LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//              CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//              SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//              INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//              ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//              POSSIBILITY OF SUCH DAMAGE.
//
//              Redistribution and use in source and binary forms, with or without
//              modification, are permitted provided that the following conditions are met:
//
//              * Redistributions of source code must retain the above copyright notice,
//              this list of conditions and the above disclaimer.
//              * Redistributions in binary form must reproduce the above copyright notice,
//              this list of conditions and the above disclaimer in the documentation
//              and/or other materials provided with the distribution.
//              * Neither the Members of the O-RAN Alliance nor the names of its
//              contributors may be used to endorse or promote products derived from
//              this software without specific prior written permission.
// -----------------------------------------------------------------------------
class ModuleORanTrace : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_TRACE_LOG_GENERATED,  // NotifTraceLogGenerated
	};

	ModuleORanTrace(uint32_t id);
	~ModuleORanTrace();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanTrace_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_TRACE_H_ */
