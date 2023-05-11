/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntryScripts.cpp
 * \brief     Function handler for 'tif:scripts'
 *
 *
 * \details   Function handler for the special device 'tif:scripts' which supports the execution of script files
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>
#include <sstream>

#include "stringfunc.hpp"

#include "RtiKeyword.h"
#include "ScriptsNode/EntryScripts.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
EntryScripts::EntryScripts(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings,
		const std::map<std::string, const ScriptInfo*>& scriptsMap) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mScriptsMap(scriptsMap)
{
}


//-------------------------------------------------------------------------------------------------------------
EntryScripts::~EntryScripts()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string EntryScripts::operator()(const std::string& functionName)
{
	std::string name(toLower(functionName)) ;

	std::map<std::string, const EntryScripts::ScriptInfo*>::const_iterator iter(mScriptsMap.find(name)) ;
	if (iter == mScriptsMap.end())
	{
		returnVarList->find(RtiKeyword::STATUS_VAR)->set("ERROR") ;
		returnVarList->find(RtiKeyword::MESSAGE_VAR)->set("Cannot find script " + functionName) ;
	}
	else
	{
		// get the list of commands
		std::vector< std::pair<std::string, unsigned> > cmdList(readCommands( iter->second->osPath )) ;

		// create a prompt for the duration of the script run
		std::string prompt = mMsgParser.getPrompt() ;

		// run the commands
		for (std::vector< std::pair<std::string, unsigned> >::const_iterator it(cmdList.begin()); it != cmdList.end(); ++it)
		{

			// run command
			std::stringstream ss ;
			ss << "[" << functionName << ":" << it->second << "]" << prompt << it->first << std::endl ;
			mMsgParser.sendOutput(ss.str());
			std::string reply = mMsgParser.parse(it->first) ;

			// show output
			mMsgParser.sendOutput(reply + "\n");

			// check for error
			if (reply.find("Status=ERROR") != std::string::npos)
			{
				returnVarList->find(RtiKeyword::STATUS_VAR)->set("ERROR") ;
				returnVarList->find(RtiKeyword::MESSAGE_VAR)->set("Script " + functionName + " failed at command '" + it->first + "'") ;
				return "" ;
			}
		}
	}

	// just use the return values to feed information back
	return "" ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector< std::pair<std::string, unsigned> > EntryScripts::readCommands(const std::string& filePath)
{
	std::vector< std::pair<std::string, unsigned> > commands ;

	std::string linebuff ;
	std::ifstream infile;
	infile.open(filePath.c_str());

	if (infile.is_open())
	{
		unsigned lineNum = 0 ;
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);
			++lineNum ;

			// skip comments and blank lines
			std::string trimmed( trim_left(linebuff)) ;
			trimmed = trim_right(trimmed) ;
			if (trimmed.empty())
				continue ;

			if (trimmed[0] == '#')
				continue ;

			commands.push_back( make_pair(trimmed, lineNum) ) ;
		}
	}
	infile.close() ;

	return commands ;
}
