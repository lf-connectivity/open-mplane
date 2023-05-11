/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInterfaceBase.cpp
 * \brief     Base class for the radio test interface
 *
 *
 * \details   Provides common base "devices" such as 'tif:settings', 'tif:scripts' etc.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TestInterfaceBase.h"
#include "CmdNode/EntryCmd.h"
#include "ScriptsNode/DirScripts.h"
#include "SettingsNode/EntrySettings.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestInterfaceBase::TestInterfaceBase()
{
	// Add the builtin commands
	EntryCmd::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	// Add scripts support
	DirScripts::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;

	// Add settings support
	EntrySettings::registerMethods(/* IRtiMsgParser */ *this, /* IRtiSettings */ *this) ;
}

//-------------------------------------------------------------------------------------------------------------
TestInterfaceBase::~TestInterfaceBase()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool TestInterfaceBase::doInject(std::shared_ptr<ITifEntry> entry)
{
	return entry->registerEntry(this) ;
}

//-------------------------------------------------------------------------------------------------------------
bool TestInterfaceBase::doHideDir(const std::string& dir)
{
	std::string path(dir) ;
	if (path.back() != '/')
		path += "/" ;
	DirNodePtr node(mTreeRoot->findDir(path)) ;
	if (!node)
		return false ;

	node->setHidden(true) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TestInterfaceBase::doUnhideDir(const std::string& dir)
{
	std::string path(dir) ;
	if (path.back() != '/')
		path += "/" ;
	DirNodePtr node(mTreeRoot->findDir(path)) ;
	if (!node)
		return false ;

	node->setHidden(true) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TestInterfaceBase::doRename(const std::string& dir, const std::string& newName)
{
	std::string path(dir) ;
	if (path.back() != '/')
		path += "/" ;
	DirNodePtr node(mTreeRoot->findDir(path)) ;
	if (!node)
		return false ;

	node->rename(newName) ;
	return true ;
}
