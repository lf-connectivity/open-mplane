#ifndef _MODULE_O_RAN_ECPRI_DELAY_H_
#define _MODULE_O_RAN_ECPRI_DELAY_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanEcpriDelay.h
 * \brief     Module ORanEcpriDelay interface
 *
 *
 * \details   This file defines the YANG module o-ran-ecpri-delay interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-ecpri-delay"
 *            YANG Filename:    "o-ran-ecpri-delay.yang"
 *            Module Prefix:    "o-ran-msg5"
 *            Module namespace: "urn:o-ran:message5:1.0"
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

// Module:   o-ran-processing-element
// Revision:
// Notes:
#include "YangModuleORanProcessingElement.h"


namespace Mplane {

namespace ModuleORanEcpriDelay_NS {

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
// Container:   /ecpri-delay-message
// Description: top level tree covering off O-DU to O-RU msg5 delay measurement
// -----------------------------------------------------------------------------
class CntEcpriDelayMessage : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MSG5_GROUP,  // Use GrpMsg5Group
	};

	CntEcpriDelayMessage(uint32_t id);
	~CntEcpriDelayMessage();

	YangResult_E initialise(void);

}; // CntEcpriDelayMessage


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /msg5-group
// Description:
// -----------------------------------------------------------------------------
class GrpMsg5Group : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ENABLE_MESSAGE5,  // LeafEnableMessage5
		ITEM_RU_COMPENSATION,  // CntRuCompensation
		ITEM_MESSAGE5_SESSIONS,  // CntMessage5Sessions
	};

	GrpMsg5Group(uint32_t id);
	~GrpMsg5Group();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /msg5-group/enable-message5
	// Description: whether O-RU's eCPRI message 5 handling is enabled.
	// -----------------------------------------------------------------------------
	class LeafEnableMessage5 : public YangLeaf
	{
	public:

		LeafEnableMessage5(uint32_t id);
		~LeafEnableMessage5();

	}; // LeafEnableMessage5

	// -----------------------------------------------------------------------------
	// Container:   /msg5-group/ru-compensation
	// Description: leafs for ru timing compensation based on message 5 handling
	// -----------------------------------------------------------------------------
	class CntRuCompensation : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_TCV2,  // LeafTcv2
			ITEM_TCV1,  // LeafTcv1
		};

		CntRuCompensation(uint32_t id);
		~CntRuCompensation();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /msg5-group/ru-compensation/tcv2
		// Description: a compensation value to account for expected delay from packet
		//              receipt at R2 to timestamping in the O-RU
		// -----------------------------------------------------------------------------
		class LeafTcv2 : public YangLeaf
		{
		public:

			LeafTcv2(uint32_t id);
			~LeafTcv2();

		}; // LeafTcv2

		// -----------------------------------------------------------------------------
		// Leaf:        /msg5-group/ru-compensation/tcv1
		// Description: a compensation value to account for expected processing time from
		//              timestamping in the O-RU until actual packet transmission at R3
		// -----------------------------------------------------------------------------
		class LeafTcv1 : public YangLeaf
		{
		public:

			LeafTcv1(uint32_t id);
			~LeafTcv1();

		}; // LeafTcv1

	}; // CntRuCompensation

	// -----------------------------------------------------------------------------
	// Container:   /msg5-group/message5-sessions
	// Description: session information for eCPRI message 5
	// -----------------------------------------------------------------------------
	class CntMessage5Sessions : public YangContainer
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SESSION_PARAMETERS,  // LstSessionParameters
		};

		CntMessage5Sessions(uint32_t id);
		~CntMessage5Sessions();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// List:        /msg5-group/message5-sessions/session-parameters
		// Description: list of MSG5 session information
		// -----------------------------------------------------------------------------
		class LstSessionParameters : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_SESSION_ID,  // LeafSessionId
				ITEM_PROCESSING_ELEMENT_NAME,  // RefProcessingElementName
				ITEM_FLOW_STATE,  // CntFlowState
			};

			LstSessionParameters(uint32_t id);
			~LstSessionParameters();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /msg5-group/message5-sessions/session-parameters/session-id
			// Description: Session ID for MSG5 responder
			// -----------------------------------------------------------------------------
			class LeafSessionId : public YangLeaf
			{
			public:

				LeafSessionId(uint32_t id);
				~LeafSessionId();

			}; // LeafSessionId

			// -----------------------------------------------------------------------------
			// Reference:   /msg5-group/message5-sessions/session-parameters/processing-element-name
			// Description: the name of the processing element used for MSG5
			// -----------------------------------------------------------------------------
			class RefProcessingElementName : public YangReference
			{
			public:

				RefProcessingElementName(uint32_t id);
				~RefProcessingElementName();

			}; // RefProcessingElementName

			// -----------------------------------------------------------------------------
			// Container:   /msg5-group/message5-sessions/session-parameters/flow-state
			// Description: MSG5 flow state
			// -----------------------------------------------------------------------------
			class CntFlowState : public YangContainer
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_RESPONSES_TRANSMITTED,  // LeafResponsesTransmitted
					ITEM_REQUESTS_TRANSMITTED,  // LeafRequestsTransmitted
					ITEM_FOLLOWUPS_TRANSMITTED,  // LeafFollowupsTransmitted
				};

				CntFlowState(uint32_t id);
				~CntFlowState();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /msg5-group/message5-sessions/session-parameters/flow-state/responses-transmitted
				// Description: The total number of eCPRI mesage 5 response messages transmitted by
				//              the O-RU.
				// -----------------------------------------------------------------------------
				class LeafResponsesTransmitted : public YangLeaf
				{
				public:

					LeafResponsesTransmitted(uint32_t id);
					~LeafResponsesTransmitted();

				}; // LeafResponsesTransmitted

				// -----------------------------------------------------------------------------
				// Leaf:        /msg5-group/message5-sessions/session-parameters/flow-state/requests-transmitted
				// Description: The total number of eCPRI mesage 5 request messages transmitted by
				//              the O-RU.
				// -----------------------------------------------------------------------------
				class LeafRequestsTransmitted : public YangLeaf
				{
				public:

					LeafRequestsTransmitted(uint32_t id);
					~LeafRequestsTransmitted();

				}; // LeafRequestsTransmitted

				// -----------------------------------------------------------------------------
				// Leaf:        /msg5-group/message5-sessions/session-parameters/flow-state/followups-transmitted
				// Description: The total number of eCPRI mesage 5 follow up messages transmitted by
				//              the O-RU.
				// -----------------------------------------------------------------------------
				class LeafFollowupsTransmitted : public YangLeaf
				{
				public:

					LeafFollowupsTransmitted(uint32_t id);
					~LeafFollowupsTransmitted();

				}; // LeafFollowupsTransmitted

			}; // CntFlowState

		}; // LstSessionParameters

	}; // CntMessage5Sessions

}; // GrpMsg5Group


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
// Module:      o-ran-ecpri-delay
// Description: This module is an optional module for supporting eCPRI message 5 handling
//              used for eCPRI based delay measurements.
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
class ModuleORanEcpriDelay : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_ECPRI_DELAY_MESSAGE,  // CntEcpriDelayMessage
	};

	ModuleORanEcpriDelay(uint32_t id);
	~ModuleORanEcpriDelay();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanEcpriDelay_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_ECPRI_DELAY_H_ */
