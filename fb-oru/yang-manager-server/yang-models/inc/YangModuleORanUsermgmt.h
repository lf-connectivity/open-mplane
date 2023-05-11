#ifndef _MODULE_O_RAN_USERMGMT_H_
#define _MODULE_O_RAN_USERMGMT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUsermgmt.h
 * \brief     Module ORanUsermgmt interface
 *
 *
 * \details   This file defines the YANG module o-ran-usermgmt interface.
 *
 *             ** Auto-generated file, do not edit **
 *
 *            Module Name:      "o-ran-usermgmt"
 *            YANG Filename:    "o-ran-usermgmt.yang"
 *            Module Prefix:    "o-ran-usermgmt"
 *            Module namespace: "urn:o-ran:user-mgmt:1.0"
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

// Module:   ietf-netconf-acm
// Revision:
// Notes:
#include "YangModuleIetfNetconfAcm.h"


namespace Mplane {

namespace ModuleORanUsermgmt_NS {

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
// Container:   /users
// Description: list of user accounts
// -----------------------------------------------------------------------------
class CntUsers : public YangContainer
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_USER_LIST,  // Use GrpUserList
	};

	CntUsers(uint32_t id);
	~CntUsers();

	YangResult_E initialise(void);

}; // CntUsers


// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    /user-list
// Description:
// -----------------------------------------------------------------------------
class GrpUserList : public YangGroup
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_USER,  // LstUser
	};

	GrpUserList(uint32_t id);
	~GrpUserList();

	YangResult_E initialise(void);

	// -----------------------------------------------------------------------------
	// List:        /user-list/user
	// Description: The list of local users configured on this device.
	// -----------------------------------------------------------------------------
	class LstUser : public YangList
	{
	public:
		// Item IDs
		enum : uint32_t
		{
			ITEM_NAME,  // LeafName
			ITEM_ACCOUNT_TYPE,  // LeafAccountType
			ITEM_PASSWORD,  // LeafPassword
			ITEM_ENABLED,  // LeafEnabled
		};

		LstUser(uint32_t id);
		~LstUser();

		YangResult_E initialise(void);

		// -----------------------------------------------------------------------------
		// Leaf:        /user-list/user/name
		// Description: The user name string identifying this entry.
		//
		//              NOTE: o-ran-usermgmt:user-profile/user/name is
		//              identical to nacm:nacm/groups/group/user-name
		//              but the current schema is preserved for backwards
		//              compatibility.
		// -----------------------------------------------------------------------------
		class LeafName : public YangLeaf
		{
		public:

			LeafName(uint32_t id);
			~LeafName();

		}; // LeafName

		// -----------------------------------------------------------------------------
		// Leaf:        /user-list/user/account-type
		// Description:
		// -----------------------------------------------------------------------------
		class LeafAccountType : public YangLeaf
		{
		public:

			//
			enum class AccountType_E : uint32_t
			{
				PASSWORD,	// the user-name is for password based authentication
				CERTIFICATE,	// the user-name is for certificate based authentciation

				Num_AccountType_E
			};

			LeafAccountType(uint32_t id);
			~LeafAccountType();

		}; // LeafAccountType

		// -----------------------------------------------------------------------------
		// Leaf:        /user-list/user/password
		// Description: The password for this entry.
		//
		//              This field is only valid when account-type is NOT set to CERTIFICATE,
		//              i.e., when account-type is NOT present or present and set to
		//              PASSWORD.
		// -----------------------------------------------------------------------------
		class LeafPassword : public YangLeaf
		{
		public:

			LeafPassword(uint32_t id);
			~LeafPassword();

		}; // LeafPassword

		// -----------------------------------------------------------------------------
		// Leaf:        /user-list/user/enabled
		// Description: Indicates whether an account is enabled or disabled.
		// -----------------------------------------------------------------------------
		class LeafEnabled : public YangLeaf
		{
		public:

			LeafEnabled(uint32_t id);
			~LeafEnabled();

		}; // LeafEnabled

	}; // LstUser

}; // GrpUserList


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
// Module:      o-ran-usermgmt
// Description: This module defines the user management model for the O-RAN Equipment.
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
class ModuleORanUsermgmt : public YangModule
{
public:
	// Item IDs
	enum : uint32_t
	{
		ITEM_USERS,  // CntUsers
	};

	ModuleORanUsermgmt(uint32_t id);
	~ModuleORanUsermgmt();

	/**
	 * Create singleton
	 */
	static std::shared_ptr<YangModule> createModule(uint32_t id);

	/**
	 * Access singleton
	 */
	static std::shared_ptr<YangModule> singleton();

};

} /* namespace ModuleORanUsermgmt_NS */

} /* namespace Mplane */

#endif /* _MODULE_O_RAN_USERMGMT_H_ */
