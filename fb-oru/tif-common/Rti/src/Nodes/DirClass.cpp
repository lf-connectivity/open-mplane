/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirClass.cpp
 * \brief     Directory entry that manages class items
 *
 *
 * \details   Basically this is just another directory that can contain test functions or variables
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include "Nodes/DirClass.h"

using namespace Mplane ;

//=============================================================================================================
// TYPES
//=============================================================================================================

// Sort RtiDirEntry* elements by name
struct ByName {
	bool operator()(RtiDirEntry* a, RtiDirEntry* b)
	{
		return a->getName() < b->getName() ;
	}
} byName ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirClass::DirClass(const std::string& pathname, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	RtiDirEntry(pathname, comment, DirNode::DN_DIRECTORY, msgParser, settings),
	mVarTitle("Variables"),
	mClassTitle("Available Test Interfaces"),
	mFuncTitle("Available Test Functions")
{
	setType(RTIENTRY_CLASS) ;
}


//-------------------------------------------------------------------------------------------------------------
DirClass::~DirClass()
{

}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::processFunc(const std::string& args)
{
	std::string reply = "Error: Cannot execute class " ;
	reply += getName() ;
	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::help()
{
	std::string reply = "\n" ;

	// Organise into vars, classes, funcs
	std::vector< RtiDirEntry* > varList ;
	std::vector< RtiDirEntry* > classList ;
	std::vector< RtiDirEntry* > funcList ;
	sortContents(varList, classList, funcList) ;

	// Show vars
	reply += showSelfHelp(mVarTitle, varList) ;

	// Show class
	reply += showSimpleHelp(mClassTitle, classList) ;

	// Show functions
	reply += showSelfHelp(mFuncTitle, funcList) ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::ls()
{
	std::string reply = "\n" ;

	// Organise into vars, classes, funcs
	std::vector< RtiDirEntry* > varList ;
	std::vector< RtiDirEntry* > classList ;
	std::vector< RtiDirEntry* > funcList ;
	sortContents(varList, classList, funcList) ;

	// Show vars
	reply += showSelfLs(varList) ;

	// Show class
	if (!classList.empty())
	{
		for (std::vector< RtiDirEntry* >::iterator entry(classList.begin()); entry != classList.end(); ++entry)
		{
			// show this directory name
			reply += lsFormat((*entry)->getName() + DirNode::PATHSEP, (*entry)->getComment()) ;
		}
	}

	// Show functions
	reply += showSelfLs(funcList) ;

	return reply ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DirClass::sortContents(
		std::vector< RtiDirEntry* >& varList,
		std::vector< RtiDirEntry* >& classList,
		std::vector< RtiDirEntry* >& funcList
		)
{
	// Organise into vars, classes, funcs
	std::vector< DirNodePtr > contents( getDir() ) ;
	for (std::vector< DirNodePtr >::iterator iter(contents.begin()); iter != contents.end(); ++iter)
	{
		RtiDirEntry* entry = dynamic_cast<RtiDirEntry*>(*iter) ;
		switch (entry->getType())
		{
		case RTIENTRY_CLASS:
			classList.push_back(entry) ;
			break ;
		case RTIENTRY_VAR:
			varList.push_back(entry) ;
			break ;
		case RTIENTRY_FUNC:
			funcList.push_back(entry) ;
			break ;
		case RTIENTRY_BASE:
		default:
			break ;
		}
	}

	// Now sort contents
	std::sort(varList.begin(), varList.end(), byName) ;
	std::sort(classList.begin(), classList.end(), byName) ;
	std::sort(funcList.begin(), funcList.end(), byName) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::showSimpleHelp(const std::string& title, const std::vector< RtiDirEntry* >& entryList)
{
	std::string reply ;
	if (!entryList.empty())
	{
		reply += helpTitleFormat(title) ;

		for (std::vector< RtiDirEntry* >::const_iterator entry(entryList.begin()); entry != entryList.end(); ++entry)
		{
			reply += helpFormat((*entry)->getName(), (*entry)->getComment()) ;
		}
	}
	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::showSelfHelp(const std::string& title, const std::vector< RtiDirEntry* >& entryList)
{
	std::string reply ;
	if (!entryList.empty())
	{
		reply += helpTitleFormat(title) ;

		for (std::vector< RtiDirEntry* >::const_iterator entry(entryList.begin()); entry != entryList.end(); ++entry)
		{
			reply += (*entry)->help() ;
		}
	}
	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirClass::showSelfLs(const std::vector< RtiDirEntry* >& entryList)
{
	std::string reply ;
	if (!entryList.empty())
	{
		for (std::vector< RtiDirEntry* >::const_iterator entry(entryList.begin()); entry != entryList.end(); ++entry)
		{
			reply += (*entry)->ls() ;
		}
	}
	return reply ;
}
