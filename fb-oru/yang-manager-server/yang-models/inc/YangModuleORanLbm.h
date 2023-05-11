#ifndef _MODULE_O_RAN_LBM_H_
#define _MODULE_O_RAN_LBM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanLbm.h
 * \brief     Module ORanLbm interface
 *
 *
 * \details   This file defines the YANG module o-ran-lbm interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-lbm"
 *            YANG Filename:    "o-ran-lbm.yang"
 *            Module Prefix:    "o-ran-lbm"
 *            Module namespace: "urn:o-ran:lbm:1.0"
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

// Module:   ietf-yang-types
// Revision: 2013-07-15
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   ietf-interfaces
// Revision:
// Notes:
#include "YangModuleIetfInterfaces.h"

// Module:   o-ran-interfaces
// Revision:
// Notes:
#include "YangModuleORanInterfaces.h"


namespace Mplane {

namespace ModuleORanLbm_NS {

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
// Container:   /md-data-definitions
// Description: Data definitions related to the maineance domains used for supporting
//              Ethernet loopback connectivity checks
// -----------------------------------------------------------------------------
class CntMdDataDefinitions : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MD_GROUP,  // Use GrpMdGroup
	};

	CntMdDataDefinitions(uint32_t id);
	~CntMdDataDefinitions();

	YangResult_E initialise(void);

}; // CntMdDataDefinitions


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /md-group
// Description:
// -----------------------------------------------------------------------------
class GrpMdGroup : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MAINTENANCE_DOMAIN,  // LstMaintenanceDomain
	};

	GrpMdGroup(uint32_t id);
	~GrpMdGroup();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /md-group/maintenance-domain
	// Description: A Maintenance Domain managed object is required in order to create an MA
	//              with a MAID that includes that Maintenance Domain's Name. From
	//              this Maintenance Domain managed object, all Maintenance
	//              Association managed objects associated with that Maintenance
	//              Domain managed object can be accessed, and thus controlled.
	// -----------------------------------------------------------------------------
	class LstMaintenanceDomain : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_ID,  // LeafId
			ITEM_NAME,  // LeafName
			ITEM_MD_LEVEL,  // LeafMdLevel
			ITEM_MAINTENANCE_ASSOCIATION,  // LstMaintenanceAssociation
		};

		LstMaintenanceDomain(uint32_t id);
		~LstMaintenanceDomain();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /md-group/maintenance-domain/id
		// Description: A unique identifier of a Maintenance Domain
		// -----------------------------------------------------------------------------
		class LeafId : public YangLeaf
		{
		public:

			LeafId(uint32_t id);
			~LeafId();

		}; // LeafId

		// -----------------------------------------------------------------------------
		// Leaf:        /md-group/maintenance-domain/name
		// Description: The value for the Maintenance Domain Name. Only the name-type
		//              'character-string' is supported
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /md-group/maintenance-domain/md-level
		// Description: Integer identifying the Maintenance Domain Level (MD Level).  Higher
		//              numbers correspond to higher Maintenance Domains, those with the
		//              greatest physical reach, with the highest values for customers'
		//              CFM PDUs.  Lower numbers correspond to lower Maintenance
		//              Domains, those with more limited physical reach, with the lowest
		//              values for CFM PDUs protecting single bridges or physical links.
		// -----------------------------------------------------------------------------
		class LeafMdLevel : public YangLeaf
		{
		public:

			LeafMdLevel(uint32_t id);
			~LeafMdLevel();

		}; // LeafMdLevel

		// -----------------------------------------------------------------------------
		// List:        /md-group/maintenance-domain/maintenance-association
		// Description: This list represents Maintenance Entity Groups (Y.1731) or
		//              Maintenance Associations (802.1ag). MEGs/MAs are sets of
		//              MEPs, each configured to the same service inside a common
		//              OAM domain.
		// -----------------------------------------------------------------------------
		class LstMaintenanceAssociation : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_ID,  // LeafId
				ITEM_NAME,  // LeafName
				ITEM_COMPONENT_LIST,  // LstComponentList
			};

			LstMaintenanceAssociation(uint32_t id);
			~LstMaintenanceAssociation();

			YangResult_E initialise(void);

			// -----------------------------------------------------------------------------
			// Leaf:        /md-group/maintenance-domain/maintenance-association/id
			// Description: A unique identifier of a Maintenance Association
			// -----------------------------------------------------------------------------
			class LeafId : public YangLeaf
			{
			public:

				LeafId(uint32_t id);
				~LeafId();

			}; // LeafId

			// -----------------------------------------------------------------------------
			// Leaf:        /md-group/maintenance-domain/maintenance-association/name
			// Description: The value for the Maintenance Association Name. Only the name-type
			//              'character-string' is supported
			// -----------------------------------------------------------------------------
			class LeafName : public YangLeaf
			{
			public:

				LeafName(uint32_t id);
				~LeafName();

			}; // LeafName

			// -----------------------------------------------------------------------------
			// List:        /md-group/maintenance-domain/maintenance-association/component-list
			// Description: A list of components each of which can be managed in a manner
			//              essentially equivalent to an 802.1Q bridge.
			// -----------------------------------------------------------------------------
			class LstComponentList : public YangList
			{
			public:
				// Item IDs
				enum : uint32_t
				{
					ITEM_COMPONENT_ID,  // LeafComponentId
					ITEM_NAME,  // LeafName
					ITEM_VID,  // LstVid
					ITEM_REMOTE_MEPS,  // LstRemoteMeps
					ITEM_MAINTENANCE_ASSOCIATION_END_POINT,  // LstMaintenanceAssociationEndPoint
				};

				LstComponentList(uint32_t id);
				~LstComponentList();

				YangResult_E initialise(void);

				// -----------------------------------------------------------------------------
				// Leaf:        /md-group/maintenance-domain/maintenance-association/component-list/component-id
				// Description: The bridge component within the system to which the information
				//              in this maintenance-association applies
				// -----------------------------------------------------------------------------
				class LeafComponentId : public YangLeaf
				{
				public:

					LeafComponentId(uint32_t id);
					~LeafComponentId();

				}; // LeafComponentId

				// -----------------------------------------------------------------------------
				// Leaf:        /md-group/maintenance-domain/maintenance-association/component-list/name
				// Description: The value for the Maintenance Association Name. Only the name-type
				//              'character-string' is supported
				// -----------------------------------------------------------------------------
				class LeafName : public YangLeaf
				{
				public:

					LeafName(uint32_t id);
					~LeafName();

				}; // LeafName

				// -----------------------------------------------------------------------------
				// List:        /md-group/maintenance-domain/maintenance-association/component-list/vid
				// Description: The VID(s) monitored by this MA, or 0, if the MA is not attached to any
				//              VID. The first VID returned is the MA's Primary VID
				// -----------------------------------------------------------------------------
				class LstVid : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
					};

					LstVid(uint32_t id);
					~LstVid();

					YangResult_E initialise(void);

				}; // LstVid

				// -----------------------------------------------------------------------------
				// List:        /md-group/maintenance-domain/maintenance-association/component-list/remote-meps
				// Description: A list of the MEPIDs of the MEPs in the MA.
				// -----------------------------------------------------------------------------
				class LstRemoteMeps : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
					};

					LstRemoteMeps(uint32_t id);
					~LstRemoteMeps();

					YangResult_E initialise(void);

				}; // LstRemoteMeps

				// -----------------------------------------------------------------------------
				// List:        /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point
				// Description: The list of Maintenance association End Points in a specific Maintance
				//              Association.
				// -----------------------------------------------------------------------------
				class LstMaintenanceAssociationEndPoint : public YangList
				{
				public:
					// Item IDs
					enum : uint32_t
					{
						ITEM_MEP_IDENTIFIER,  // LeafMepIdentifier
						ITEM_ADMINISTRATIVE_STATE,  // LeafAdministrativeState
						ITEM_INTERFACE,  // RefInterface
						ITEM_PRIMARY_VID,  // RefPrimaryVid
						ITEM_MAC_ADDRESS,  // RefMacAddress
						ITEM_LOOPBACK,  // CntLoopback
					};

					LstMaintenanceAssociationEndPoint(uint32_t id);
					~LstMaintenanceAssociationEndPoint();

					YangResult_E initialise(void);

					// -----------------------------------------------------------------------------
					// Leaf:        /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mep-identifier
					// Description: Integer that is unique among all the MEPs in the same MA. Other
					//              definition is: a small integer, unique over a given
					//              Maintenance Association, identifying a specific Maintenance
					//              association End Point.
					// -----------------------------------------------------------------------------
					class LeafMepIdentifier : public YangLeaf
					{
					public:

						LeafMepIdentifier(uint32_t id);
						~LeafMepIdentifier();

					}; // LeafMepIdentifier

					// -----------------------------------------------------------------------------
					// Leaf:        /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/administrative-state
					// Description: The administrative state of the MEP
					// -----------------------------------------------------------------------------
					class LeafAdministrativeState : public YangLeaf
					{
					public:

						LeafAdministrativeState(uint32_t id);
						~LeafAdministrativeState();

					}; // LeafAdministrativeState

					// -----------------------------------------------------------------------------
					// Reference:   /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/interface
					// Description: An interface, either a Bridge Port or an aggregated IEEE 802.3 port
					//              within a Bridge Port, to which the MEP is attached. Each interface in
					//              the system is uniquely identified by an interface-name. The structure
					//              and content of the name is outside the scope of this specification.
					// -----------------------------------------------------------------------------
					class RefInterface : public YangReference
					{
					public:

						RefInterface(uint32_t id);
						~RefInterface();

					}; // RefInterface

					// -----------------------------------------------------------------------------
					// Reference:   /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/primary-vid
					// Description: The Primary VID of the MEP. The value 0 indicates that either the
					//              Primary VID is that of the MEP's MA or that the MEP's MA is
					//              associated with no VID
					// -----------------------------------------------------------------------------
					class RefPrimaryVid : public YangReference
					{
					public:

						RefPrimaryVid(uint32_t id);
						~RefPrimaryVid();

					}; // RefPrimaryVid

					// -----------------------------------------------------------------------------
					// Reference:   /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/mac-address
					// Description: The MAC address of the MEP
					// -----------------------------------------------------------------------------
					class RefMacAddress : public YangReference
					{
					public:

						RefMacAddress(uint32_t id);
						~RefMacAddress();

					}; // RefMacAddress

					// -----------------------------------------------------------------------------
					// Container:   /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/loopback
					// Description: Data definitions related to the Loopback function.
					// -----------------------------------------------------------------------------
					class CntLoopback : public YangContainer
					{
					public:
						// Item IDs
						enum : uint32_t
						{
							ITEM_REPLIES_TRANSMITTED,  // LeafRepliesTransmitted
						};

						CntLoopback(uint32_t id);
						~CntLoopback();

						YangResult_E initialise(void);

						// -----------------------------------------------------------------------------
						// Leaf:        /md-group/maintenance-domain/maintenance-association/component-list/maintenance-association-end-point/loopback/replies-transmitted
						// Description: The total number of LBRs transmitted.
						// -----------------------------------------------------------------------------
						class LeafRepliesTransmitted : public YangLeaf
						{
						public:

							LeafRepliesTransmitted(uint32_t id);
							~LeafRepliesTransmitted();

						}; // LeafRepliesTransmitted

					}; // CntLoopback

				}; // LstMaintenanceAssociationEndPoint

			}; // LstComponentList

		}; // LstMaintenanceAssociation

	}; // LstMaintenanceDomain

}; // GrpMdGroup


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
// Module:      o-ran-lbm
// Description: This module defines the module capabilities for
//              the O-RAN Radio loop-back protocol (IEEE 802.1ag).
//              It is derived from MEF-38 (Service OAM Fault Management YANG Modules, April 2012)
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
class ModuleORanLbm : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MD_DATA_DEFINITIONS,  // CntMdDataDefinitions
	};

	ModuleORanLbm(uint32_t id);
	~ModuleORanLbm();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanLbm_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_LBM_H_ */
