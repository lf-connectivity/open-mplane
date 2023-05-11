#ifndef _MODULE_O_RAN_ALD_H_
#define _MODULE_O_RAN_ALD_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanAld.h
 * \brief     Module ORanAld interface
 *
 *
 * \details   This file defines the YANG module o-ran-ald interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-ald"
 *            YANG Filename:    "o-ran-ald.yang"
 *            Module Prefix:    "o-ran-ald"
 *            Module namespace: "urn:o-ran:ald:1.0"
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

// Module:   o-ran-ald-port
// Revision:
// Notes:
#include "YangModuleORanAldPort.h"


namespace Mplane {

namespace ModuleORanAld_NS {

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
// Grouping:    /ald-input
// Description:
// -----------------------------------------------------------------------------
class GrpAldInput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ALD_REQ_MSG,  // LeafAldReqMsg
		ITEM_PORT_ID,  // RefPortId
	};

	GrpAldInput(uint32_t id);
	~GrpAldInput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-input/ald-req-msg
	// Description: Response message to be forwarded to ALD in type of binary-string
	// -----------------------------------------------------------------------------
	class LeafAldReqMsg : public YangLeaf
	{
	public:

		LeafAldReqMsg(uint32_t id);
		~LeafAldReqMsg();

	}; // LeafAldReqMsg

	// -----------------------------------------------------------------------------
	// Reference:   /ald-input/port-id
	// Description: Unique ALD port identifier reported by radio
	// -----------------------------------------------------------------------------
	class RefPortId : public YangReference
	{
	public:

		RefPortId(uint32_t id);
		~RefPortId();

	}; // RefPortId

}; // GrpAldInput

// -----------------------------------------------------------------------------
// Grouping:    /ald-output
// Description:
// -----------------------------------------------------------------------------
class GrpAldOutput : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_STATUS,  // LeafStatus
		ITEM_ERROR_MESSAGE,  // LeafErrorMessage
		ITEM_ALD_RESP_MSG,  // LeafAldRespMsg
		ITEM_FRAMES_WITH_WRONG_CRC,  // LeafFramesWithWrongCrc
		ITEM_FRAMES_WITHOUT_STOP_FLAG,  // LeafFramesWithoutStopFlag
		ITEM_NUMBER_OF_RECEIVED_OCTETS,  // LeafNumberOfReceivedOctets
		ITEM_PORT_ID,  // RefPortId
	};

	GrpAldOutput(uint32_t id);
	~GrpAldOutput();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/status
	// Description: Status of RPC handling seen from equipment perspective
	// -----------------------------------------------------------------------------
	class LeafStatus : public YangLeaf
	{
	public:

		// Status of RPC handling seen from equipment perspective
		enum class Status_E : uint32_t
		{
			ACCEPTED,	// Operation was accepted, message was processed towards ALD and response is provided
			REJECTED,	// Operation was rejected by O-RU

			Num_Status_E
		};

		LeafStatus(uint32_t id);
		~LeafStatus();

	}; // LeafStatus

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/error-message
	// Description: Detailed error message when the status is rejected. E.g. wrong ALD port identifier was used in RPC received from Netconf Client
	// -----------------------------------------------------------------------------
	class LeafErrorMessage : public YangLeaf
	{
	public:

		LeafErrorMessage(uint32_t id);
		~LeafErrorMessage();

	}; // LeafErrorMessage

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/ald-resp-msg
	// Description: Response message forwarded from ALD in type of binary-string
	// -----------------------------------------------------------------------------
	class LeafAldRespMsg : public YangLeaf
	{
	public:

		LeafAldRespMsg(uint32_t id);
		~LeafAldRespMsg();

	}; // LeafAldRespMsg

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/frames-with-wrong-crc
	// Description: Number of frames with incorrect CRC (FCS) received from ALD - running counter
	// -----------------------------------------------------------------------------
	class LeafFramesWithWrongCrc : public YangLeaf
	{
	public:

		LeafFramesWithWrongCrc(uint32_t id);
		~LeafFramesWithWrongCrc();

	}; // LeafFramesWithWrongCrc

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/frames-without-stop-flag
	// Description: Number of frames without stop flag received from ALD - running counter
	// -----------------------------------------------------------------------------
	class LeafFramesWithoutStopFlag : public YangLeaf
	{
	public:

		LeafFramesWithoutStopFlag(uint32_t id);
		~LeafFramesWithoutStopFlag();

	}; // LeafFramesWithoutStopFlag

	// -----------------------------------------------------------------------------
	// Leaf:        /ald-output/number-of-received-octets
	// Description: Number of octets received from HDLC bus - running counter
	// -----------------------------------------------------------------------------
	class LeafNumberOfReceivedOctets : public YangLeaf
	{
	public:

		LeafNumberOfReceivedOctets(uint32_t id);
		~LeafNumberOfReceivedOctets();

	}; // LeafNumberOfReceivedOctets

	// -----------------------------------------------------------------------------
	// Reference:   /ald-output/port-id
	// Description: Unique ALD port identifier reported by radio
	// -----------------------------------------------------------------------------
	class RefPortId : public YangReference
	{
	public:

		RefPortId(uint32_t id);
		~RefPortId();

	}; // RefPortId

}; // GrpAldOutput


// *****************************************************************************
// Lists
// *****************************************************************************

// *****************************************************************************
// Choices
// *****************************************************************************

// *****************************************************************************
// Notifications
// *****************************************************************************

// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      o-ran-ald
// Description: This module defines the module for the ald communication.
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
class ModuleORanAld : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
	};

	ModuleORanAld(uint32_t id);
	~ModuleORanAld();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanAld_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_ALD_H_ */
