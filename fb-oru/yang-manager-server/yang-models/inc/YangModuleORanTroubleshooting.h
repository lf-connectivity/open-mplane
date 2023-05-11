#ifndef _MODULE_O_RAN_TROUBLESHOOTING_H_
#define _MODULE_O_RAN_TROUBLESHOOTING_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanTroubleshooting.h
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

namespace ModuleORanTroubleshooting_NS {

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
// Grouping:    /troubleshooting-status-grouping
// Description: grouping used for troubleshooting RPCs
// -----------------------------------------------------------------------------
class GrpTroubleshootingStatusGrouping : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_STATUS,  // LeafStatus
		ITEM_FAILURE_REASON,  // LeafFailureReason
	};

	GrpTroubleshootingStatusGrouping(uint32_t id);
	~GrpTroubleshootingStatusGrouping();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /troubleshooting-status-grouping/status
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
	// Leaf:        /troubleshooting-status-grouping/failure-reason
	// Description: free form text description why error occurred
	// -----------------------------------------------------------------------------
	class LeafFailureReason : public YangLeaf
	{
	public:

		LeafFailureReason(uint32_t id);
		~LeafFailureReason();

	}; // LeafFailureReason

}; // GrpTroubleshootingStatusGrouping


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
// Notification:/troubleshooting-log-generated
// Description: When new log file generated, send this notification.
// -----------------------------------------------------------------------------
class NotifTroubleshootingLogGenerated : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_LOG_FILE_NAME,  // LstLogFileName
	};

	NotifTroubleshootingLogGenerated(uint32_t id);
	~NotifTroubleshootingLogGenerated();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /troubleshooting-log-generated/log-file-name
	// Description: The list of troubleshooting log file names on the O-RU.
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

}; // NotifTroubleshootingLogGenerated


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-troubleshooting
// Description: This module defines the operations for the troubleshooting logs.
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
class ModuleORanTroubleshooting : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_TROUBLESHOOTING_LOG_GENERATED,  // NotifTroubleshootingLogGenerated
	};

	ModuleORanTroubleshooting(uint32_t id);
	~ModuleORanTroubleshooting();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanTroubleshooting_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_TROUBLESHOOTING_H_ */
