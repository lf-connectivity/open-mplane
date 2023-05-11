/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirScriptsBase.cpp
 * \brief     Base class for a directory entry for RTI scripts
 *
 *
 * \details   Provides simple help/ls support for scripts directories
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ScriptsNode/DirScriptsBase.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirScriptsBase::DirScriptsBase(const std::string& pathname, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	DirClass(pathname, comment, msgParser, settings)
{
}


//-------------------------------------------------------------------------------------------------------------
DirScriptsBase::~DirScriptsBase()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string DirScriptsBase::help()
{
	std::string reply = "\n" ;

	// Organise into vars, classes, funcs
	std::vector< RtiDirEntry* > varList ;
	std::vector< RtiDirEntry* > classList ;
	std::vector< RtiDirEntry* > funcList ;
	sortContents(varList, classList, funcList) ;

	// Show functions
	reply += showSimpleHelp("Scripts", funcList) ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirScriptsBase::ls()
{
	return this->super::ls() ;
}
