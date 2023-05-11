/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangModuleORanUsermgmt.cpp
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
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "YangModuleORanUsermgmt.h"

// -----------------------------------------------------------------------------
// External Module Augmenters
// -----------------------------------------------------------------------------


using namespace Mplane;
using namespace ModuleORanUsermgmt_NS;

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
// -----------------------------------------------------------------------------
// Container:   users
// Description: list of user accounts
// -----------------------------------------------------------------------------
CntUsers::CntUsers(uint32_t id)
	: YangContainer("users", id)
{
}

CntUsers::~CntUsers()
{
}

YangResult_E CntUsers::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Uses:        /users/user-list
	// Description:
	// -----------------------------------------------------------------------------
	GrpUserList userListInst(ITEM_USER_LIST);
	userListInst.initialise();
	addGroup(userListInst);



	return YangResult_E::OK;
}





// *****************************************************************************
// Groupings
// *****************************************************************************

// -----------------------------------------------------------------------------
// Grouping:    user-list
// Description:
// -----------------------------------------------------------------------------
GrpUserList::GrpUserList(uint32_t id)
	: YangGroup("user-list", id)
{
}

GrpUserList::~GrpUserList()
{
}

YangResult_E GrpUserList::initialise(void)
{
	// -----------------------------------------------------------------------------
	// List:        /user-list/user
	// Description: The list of local users configured on this device.
	// Array Key:
	// -----------------------------------------------------------------------------
	LstUser userInst(ITEM_USER);
	userInst.initialise();
	addList(userInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// List:        user
// Description: The list of local users configured on this device.
// -----------------------------------------------------------------------------
GrpUserList::LstUser::LstUser(uint32_t id)
	: YangList("user", id)
{
}

GrpUserList::LstUser::~LstUser()
{
}

YangResult_E GrpUserList::LstUser::initialise(void)
{
	// -----------------------------------------------------------------------------
	// Leaf:        /user-list/user/name
	// Description: The user name string identifying this entry.
	//
	//              NOTE: o-ran-usermgmt:user-profile/user/name is
	//              identical to nacm:nacm/groups/group/user-name
	//              but the current schema is preserved for backwards
	//              compatibility.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafName nameInst(ITEM_NAME);
	addLeaf(nameInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /user-list/user/account-type
	// Description:
	// Type:        enum
	// Units:
	// -----------------------------------------------------------------------------
	LeafAccountType accountTypeInst(ITEM_ACCOUNT_TYPE);
	addLeaf(accountTypeInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /user-list/user/password
	// Description: The password for this entry.
	//
	//              This field is only valid when account-type is NOT set to CERTIFICATE,
	//              i.e., when account-type is NOT present or present and set to
	//              PASSWORD.
	// Type:        string
	// Units:
	// -----------------------------------------------------------------------------
	LeafPassword passwordInst(ITEM_PASSWORD);
	addLeaf(passwordInst);

	// -----------------------------------------------------------------------------
	// Leaf:        /user-list/user/enabled
	// Description: Indicates whether an account is enabled or disabled.
	// Type:        UNKNOWN:3
	// Units:
	// -----------------------------------------------------------------------------
	LeafEnabled enabledInst(ITEM_ENABLED);
	addLeaf(enabledInst);



	return YangResult_E::OK;
}

// -----------------------------------------------------------------------------
// Leaf:        /user-list/user/name
// Description: The user name string identifying this entry.
//
//              NOTE: o-ran-usermgmt:user-profile/user/name is
//              identical to nacm:nacm/groups/group/user-name
//              but the current schema is preserved for backwards
//              compatibility.
// -----------------------------------------------------------------------------
GrpUserList::LstUser::LeafName::LeafName(uint32_t id)
	: YangLeaf("name", id)
{
}

GrpUserList::LstUser::LeafName::~LeafName()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /user-list/user/account-type
// Description:
// -----------------------------------------------------------------------------
GrpUserList::LstUser::LeafAccountType::LeafAccountType(uint32_t id)
	: YangLeaf("account-type", id)
{
}

GrpUserList::LstUser::LeafAccountType::~LeafAccountType()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /user-list/user/password
// Description: The password for this entry.
//
//              This field is only valid when account-type is NOT set to CERTIFICATE,
//              i.e., when account-type is NOT present or present and set to
//              PASSWORD.
// -----------------------------------------------------------------------------
GrpUserList::LstUser::LeafPassword::LeafPassword(uint32_t id)
	: YangLeaf("password", id)
{
}

GrpUserList::LstUser::LeafPassword::~LeafPassword()
{
}

// -----------------------------------------------------------------------------
// Leaf:        /user-list/user/enabled
// Description: Indicates whether an account is enabled or disabled.
// -----------------------------------------------------------------------------
GrpUserList::LstUser::LeafEnabled::LeafEnabled(uint32_t id)
	: YangLeaf("enabled", id)
{
}

GrpUserList::LstUser::LeafEnabled::~LeafEnabled()
{
}






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
ModuleORanUsermgmt::ModuleORanUsermgmt(uint32_t id)
	: YangModule ("o-ran-usermgmt",
	              "o-ran-usermgmt.yang",
	              "o-ran-usermgmt",
	              "urn:o-ran:user-mgmt:1.0",
	              id)
// Add user code here
// %%->

// <-%%
{
	// -----------------------------------------------------------------------------
	// Container:   /users
	// Description: list of user accounts
	// -----------------------------------------------------------------------------
	CntUsers usersInst(ITEM_USERS);
	usersInst.initialise();
	addContainer(usersInst);


	// Add user code here
	// %%->

	// <-%%
}

ModuleORanUsermgmt::~ModuleORanUsermgmt()
{
	// Add user code here
	// %%->

	// <-%%
}

std::shared_ptr<YangModule> ModuleORanUsermgmt::createModule(uint32_t id)
{
	std::shared_ptr<YangModule> instance( std::make_shared<ModuleORanUsermgmt>(id) );
	// assert(instance->getId() != ITEM_NULL);
	return instance;
}

std::shared_ptr<YangModule> ModuleORanUsermgmt::singleton()
{
	// call create() with dummy values
	return createModule(ITEM_NULL);
}

// Add user code here
// %%->

// <-%%
