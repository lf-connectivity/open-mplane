/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntrySettings.cpp
 * \brief     Function handler for 'tif:scripts'
 *
 *
 * \details   Function handler for the special device 'tif:scripts' which supports the execution of script files
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <sstream>

#include "Nodes/RtiDirEntry.h"
#include "Nodes/DirClass.h"
#include "Nodes/EntryVar.h"
#include "SettingsNode/EntrySettings.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

static const std::string ValueStr = "Value" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
EntrySettings::EntrySettings(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings)
{
}


//-------------------------------------------------------------------------------------------------------------
EntrySettings::~EntrySettings()
{
}


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void EntrySettings::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	std::string settingsDir("/tif:settings") ;

	// Create a directory to store the data in
	msgParser.add( static_cast<RtiDirEntry *>(new DirClass(settingsDir, "Test settings", msgParser, settings)) ) ;

	// Create a command for each setting variable
	for (std::vector< std::shared_ptr<DataVariant> >::const_iterator iter(settings.begin()); iter != settings.end(); ++iter)
	{
		std::string comment( settings.getComment((*iter)->getName()) ) ;

		// Add a Var entry which uses the Setting's data value
		msgParser.add( static_cast<RtiDirEntry *>(
			new EntryVar(settingsDir + DirNode::PATHSEP + (*iter)->getName(), *iter, comment, msgParser, settings)
		) ) ;
	}

}
