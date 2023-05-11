#ifndef _MODULE_IETF_YANG_LIBRARY_H_
#define _MODULE_IETF_YANG_LIBRARY_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleIetfYangLibrary.h
 * \brief     Module IetfYangLibrary interface
 *
 *
 * \details   This file defines the YANG module ietf-yang-library interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "ietf-yang-library"
 *            YANG Filename:    "ietf-yang-library.yang"
 *            Module Prefix:    "yanglib"
 *            Module namespace: "urn:ietf:params:xml:ns:yang:ietf-yang-library"
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
// Revision:
// Notes:
#include "YangModuleIetfYangTypes.h"

// Module:   ietf-inet-types
// Revision:
// Notes:
#include "YangModuleIetfInetTypes.h"


namespace Mplane {

namespace ModuleIetfYangLibrary_NS {

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
// Container:   /modules-state
// Description: Contains YANG module monitoring information.
// -----------------------------------------------------------------------------
class CntModulesState : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MODULE_SET_ID,  // LeafModuleSetId
		ITEM_MODULE_LIST,  // Use GrpModuleList
	};

	CntModulesState(uint32_t id);
	~CntModulesState();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Leaf:        /modules-state/module-set-id
	// Description: Contains a server-specific identifier representing
	//              the current set of modules and submodules.  The
	//              server MUST change the value of this leaf if the
	//              information represented by the 'module' list instances
	//              has changed.
	// -----------------------------------------------------------------------------
	class LeafModuleSetId : public YangLeaf
	{
	public:

		LeafModuleSetId(uint32_t id);
		~LeafModuleSetId();

	}; // LeafModuleSetId

}; // CntModulesState


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /module-list
// Description: The module data structure is represented as a grouping
//              so it can be reused in configuration or another monitoring
//              data structure.
// -----------------------------------------------------------------------------
class GrpModuleList : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_COMMON_LEAFS,  // GrpCommonLeafs
		ITEM_SCHEMA_LEAF,  // GrpSchemaLeaf
		ITEM_MODULE,  // LstModule
	};

	GrpModuleList(uint32_t id);
	~GrpModuleList();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Grouping:    /module-list/common-leafs
	// Description: Common parameters for YANG modules and submodules.
	// -----------------------------------------------------------------------------
	class GrpCommonLeafs : public YangGroup
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_REVISION,  // LeafRevision
		};

		GrpCommonLeafs(uint32_t id);
		~GrpCommonLeafs();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /module-list/common-leafs/name
		// Description: The YANG module or submodule name.
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /module-list/common-leafs/revision
		// Description: The YANG module or submodule revision date.
		//              A zero-length string is used if no revision statement
		//              is present in the YANG module or submodule.
		// -----------------------------------------------------------------------------
		class LeafRevision : public YangLeaf
		{
		public:

			LeafRevision(uint32_t id);
			~LeafRevision();

		}; // LeafRevision

	}; // GrpCommonLeafs

	// -----------------------------------------------------------------------------
	// Grouping:    /module-list/schema-leaf
	// Description: Common schema leaf parameter for modules and submodules.
	// -----------------------------------------------------------------------------
	class GrpSchemaLeaf : public YangGroup
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_SCHEMA,  // LeafSchema
		};

		GrpSchemaLeaf(uint32_t id);
		~GrpSchemaLeaf();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /module-list/schema-leaf/schema
		// Description: Contains a URL that represents the YANG schema
		//              resource for this module or submodule.
		//              This leaf will only be present if there is a URL
		//              available for retrieval of the schema for this entry.
		// -----------------------------------------------------------------------------
		class LeafSchema : public YangLeaf
		{
		public:

			LeafSchema(uint32_t id);
			~LeafSchema();

		}; // LeafSchema

	}; // GrpSchemaLeaf

	// -----------------------------------------------------------------------------
	// List:        /module-list/module
	// Description: Each entry represents one revision of one module
	//              currently supported by the server.
	// -----------------------------------------------------------------------------
	class LstModule : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAMESPACE,  // LeafNamespace
			ITEM_CONFORMANCE_TYPE,  // LeafConformanceType
			ITEM_FEATURE,  // LstFeature
			ITEM_DEVIATION,  // LstDeviation
			ITEM_SUBMODULE,  // LstSubmodule
			ITEM_COMMON_LEAFS,  // Use GrpCommonLeafs
			ITEM_SCHEMA_LEAF,  // Use GrpSchemaLeaf
		};

		LstModule(uint32_t id);
		~LstModule();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /module-list/module/namespace
		// Description: The XML namespace identifier for this module.
		// -----------------------------------------------------------------------------
		class LeafNamespace : public YangLeaf
		{
		public:

			LeafNamespace(uint32_t id);
			~LeafNamespace();

		}; // LeafNamespace

		// -----------------------------------------------------------------------------
		// Leaf:        /module-list/module/conformance-type
		// Description: Indicates the type of conformance the server is claiming
		//              for the YANG module identified by this entry.
		// -----------------------------------------------------------------------------
		class LeafConformanceType : public YangLeaf
		{
		public:

			// Indicates the type of conformance the server is claiming
			// for the YANG module identified by this entry.
			enum class ConformanceType_E : uint32_t
			{
				IMPLEMENT,	// Indicates that the server implements one or more
						// protocol-accessible objects defined in the YANG module
						// identified in this entry.  This includes deviation
						// statements defined in the module.
						// For YANG version 1.1 modules, there is at most one
						// module entry with conformance type 'implement' for a
						// particular module name, since YANG 1.1 requires that,
						// at most, one revision of a module is implemented.
						// For YANG version 1 modules, there SHOULD NOT be more
						// than one module entry for a particular module name.
				IMPORT,	// Indicates that the server imports reusable definitions
						// from the specified revision of the module but does
						// not implement any protocol-accessible objects from
						// this revision.
						// Multiple module entries for the same module name MAY
						// exist.  This can occur if multiple modules import the
						// same module but specify different revision dates in
						// the import statements.

				Num_ConformanceType_E
			};

			LeafConformanceType(uint32_t id);
			~LeafConformanceType();

		}; // LeafConformanceType

		// -----------------------------------------------------------------------------
		// List:        /module-list/module/feature
		// Description: List of YANG feature names from this module that are
		//              supported by the server, regardless of whether they are
		//              defined in the module or any included submodule.
		// -----------------------------------------------------------------------------
		class LstFeature : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
			};

			LstFeature(uint32_t id);
			~LstFeature();

			YangResult_E initialise(void);

		}; // LstFeature

		// -----------------------------------------------------------------------------
		// List:        /module-list/module/deviation
		// Description: List of YANG deviation module names and revisions
		//              used by this server to modify the conformance of
		//              the module associated with this entry.  Note that
		//              the same module can be used for deviations for
		//              multiple modules, so the same entry MAY appear
		//              within multiple 'module' entries.
		//              The deviation module MUST be present in the 'module'
		//              list, with the same name and revision values.
		//              The 'conformance-type' value will be 'implement' for
		//              the deviation module.
		// -----------------------------------------------------------------------------
		class LstDeviation : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_COMMON_LEAFS,  // Use GrpCommonLeafs
			};

			LstDeviation(uint32_t id);
			~LstDeviation();

			YangResult_E initialise(void);

		}; // LstDeviation

		// -----------------------------------------------------------------------------
		// List:        /module-list/module/submodule
		// Description: Each entry represents one submodule within the
		//              parent module.
		// -----------------------------------------------------------------------------
		class LstSubmodule : public YangList
		{
		public:
			// Item IDs
			enum : uint32_t
			{
				ITEM_COMMON_LEAFS,  // Use GrpCommonLeafs
				ITEM_SCHEMA_LEAF,  // Use GrpSchemaLeaf
			};

			LstSubmodule(uint32_t id);
			~LstSubmodule();

			YangResult_E initialise(void);

		}; // LstSubmodule

	}; // LstModule

}; // GrpModuleList


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
// Notification:/yang-library-change
// Description: Generated when the set of modules and submodules supported
//              by the server has changed.
// -----------------------------------------------------------------------------
class NotifYangLibraryChange : public YangNotif
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MODULE_SET_ID,  // RefModuleSetId
	};

	NotifYangLibraryChange(uint32_t id);
	~NotifYangLibraryChange();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// Reference:   /yang-library-change/module-set-id
	// Description: Contains the module-set-id value representing the
	//              set of modules and submodules supported at the server at
	//              the time the notification is generated.
	// -----------------------------------------------------------------------------
	class RefModuleSetId : public YangReference
	{
	public:

		RefModuleSetId(uint32_t id);
		~RefModuleSetId();

	}; // RefModuleSetId

}; // NotifYangLibraryChange


// *****************************************************************************
// Module
// *****************************************************************************

// -----------------------------------------------------------------------------
// Module:      ietf-yang-library
// Description: This module contains monitoring information about the YANG
//              modules and submodules that are used within a YANG-based
//              server.
//              Copyright (c) 2016 IETF Trust and the persons identified as
//              authors of the code.  All rights reserved.
//              Redistribution and use in source and binary forms, with or
//              without modification, is permitted pursuant to, and subject
//              to the license terms contained in, the Simplified BSD License
//              set forth in Section 4.c of the IETF Trust's Legal Provisions
//              Relating to IETF Documents
//              (http://trustee.ietf.org/license-info).
//              This version of this YANG module is part of RFC 7895; see
//              the RFC itself for full legal notices.
// -----------------------------------------------------------------------------
class ModuleIetfYangLibrary : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_MODULES_STATE,  // CntModulesState
		ITEM_YANG_LIBRARY_CHANGE,  // NotifYangLibraryChange
	};

	ModuleIetfYangLibrary(uint32_t id);
	~ModuleIetfYangLibrary();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleIetfYangLibrary_NS */

} /* namespace Mplane */

#endif /* _MODULE_IETF_YANG_LIBRARY_H_ */
