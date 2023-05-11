/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirCmd.cpp
 * \brief     Directory entry for RTI builtin commands
 *
 *
 * \details    Container for the builtin commands. This class just modifies the default help slightly
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CmdNode/DirCmd.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirCmd::DirCmd(const std::string& pathname, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	DirClass(pathname, comment, msgParser, settings)
{
	setType(RTIENTRY_CLASS) ;
}


//-------------------------------------------------------------------------------------------------------------
DirCmd::~DirCmd()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string DirCmd::help()
{
	std::string reply = "\n" ;

	// Organise into vars, classes, funcs
	std::vector< RtiDirEntry* > varList ;
	std::vector< RtiDirEntry* > classList ;
	std::vector< RtiDirEntry* > funcList ;
	sortContents(varList, classList, funcList) ;

	// Show functions
	reply += showSimpleHelp("Commands", funcList) ;

	return reply ;
}
