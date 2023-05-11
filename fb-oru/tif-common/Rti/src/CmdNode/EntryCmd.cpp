/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EntryCmd.cpp
 * \brief     Builtin command handler
 *
 *
 * \details   Creates a hidden directory containing all of the builtin commands
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "ILoggable.h"
#include "Task.h"
#include "Process.h"
#include "stringfunc.hpp"

#include "RtiKeyword.h"
#include "Nodes/RtiDirEntry.h"
#include "Nodes/DirClass.h"
#include "CmdNode/DirCmd.h"
#include "CmdNode/EntryCmd.h"




using namespace Mplane ;


//=============================================================================================================
// TYPES
//=============================================================================================================

// Sort RtiDirEntry* elements by name
struct ByDirName {
	bool operator()(RtiDirEntry* a, RtiDirEntry* b)
	{
		return a->getName() < b->getName() ;
	}
} byDirName ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string BUILTINS_DIR("builtins") ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
std::string EntryCmd::mBuiltinCommandHelp("") ;

//-------------------------------------------------------------------------------------------------------------
EntryCmd::EntryCmd(const std::string& pathname, const std::string& callFields,
		const std::string& returnFields, const std::string& comment,
		IRtiMsgParser& msgParser, IRtiSettings& settings) :
	EntryFunc(pathname, comment, callFields, returnFields, msgParser, settings),
	mPassword("        ")
{
	// Create password string (use random access so it's not available to 'strings' command!
	mPassword[4] = '$' ;
	mPassword[1] = 'v' ;
	mPassword[3] = 'n' ;
	mPassword[0] = 'E' ;
	mPassword[7] = 'r' ;
	mPassword[5] = 't' ;
	mPassword[6] = 'a' ;
	mPassword[2] = 'e' ;
}


//-------------------------------------------------------------------------------------------------------------
EntryCmd::~EntryCmd()
{
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::operator()(const std::string& functionName)
{
	if (functionName == "help")
	{
		return cmdHelp() ;
	}
	else if (functionName == "ls")
	{
		return cmdLs() ;
	}
	else if (functionName == "cd")
	{
		return cmdCd() ;
	}
	else if (functionName == "su")
	{
		return cmdSu() ;
	}
	else if (functionName == "memory")
	{
		return cmdMemory() ;
	}
	else if (functionName == "quit")
	{
		return cmdQuit() ;
	}
	else if (functionName == "sleepMs")
	{
		return cmdSleep() ;
	}
	return "" ;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void EntryCmd::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	// Create a directory to store the data in
	msgParser.add( static_cast<RtiDirEntry *>(new DirCmd(getBuiltinDir(), "Builtin commands", msgParser, settings)) ) ;

	// Add the commands
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "help",
			"[STRING item]",
			"",
			"Show general help or help on a specific item",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "ls",
			"[STRING dir]",
			"",
			"Display contents of current or specified directory",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "cd",
			"[STRING dir]",
			"",
			"Change directory to specified directory or to top level",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "su",
			"[STRING password]",
			"",
			"Enter super user mode (shows current mode if no password specified). Exits super user mode if password is 'exit'.",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "memory",
			"",
			"",
			"Show current application memory usage",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "quit",
			"",
			"",
			"Shut down application",
			msgParser, settings))
	);
	msgParser.add(
		static_cast<RtiDirEntry *>(new EntryCmd(getBuiltinDir() + DirNode::PATHSEP + "sleepMs",
			"INT sleep (ms)",
			"",
			"Sleep for the specified number of ms",
			msgParser, settings))
	);


	// Build command help for builtins
	std::vector< RtiDirEntry* > funcList ;
	RtiDirEntry* cwd = msgParser.getWorkingDir() ;
	DirClass* builtin = dynamic_cast<DirClass*>( cwd->findDir( DirNode::PATHSEP + BUILTINS_DIR ) ) ;
	std::vector< DirNodePtr > contents( builtin->getDirAll() ) ;
	for (std::vector< DirNodePtr >::iterator iter(contents.begin()); iter != contents.end(); ++iter)
	{
		RtiDirEntry* entry = dynamic_cast<RtiDirEntry*>(*iter) ;
		switch (entry->getType())
		{
		case RTIENTRY_FUNC:
			funcList.push_back(entry) ;
			break ;
		case RTIENTRY_CLASS:
		case RTIENTRY_VAR:
		case RTIENTRY_BASE:
		default:
			break ;
		}
	}
	std::sort(funcList.begin(), funcList.end(), byDirName) ;
	mBuiltinCommandHelp = builtin->showSimpleHelp("Commands", funcList) ;

}

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::getBuiltinDir()
{
	return DirNode::PATHSEP + DirNode::HIDDEN + BUILTINS_DIR ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::EntryCmd::getBuiltinCommand(const std::string& cmd)
{
	return DirNode::PATHSEP + BUILTINS_DIR + DirNode::PATHSEP + cmd ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdCd()
{
	std::string dir("") ;
	if (callVarList->find("dir")->isSet())
		dir = callVarList->find("dir")->toString() ;

	if (!mMsgParser.setWorkingDir(dir))
	{
		returnVarList->find(RtiKeyword::STATUS_VAR)->set(RtiKeyword::StatusERROR) ;
		return "Error: Cannot change to directory " + dir ;
	}

	return "Current directory: " + mMsgParser.getWorkingDir()->getFullPath() ;
}


//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdLs()
{
	RtiDirEntry* entry = mMsgParser.getWorkingDir() ;

	if (callVarList->find("dir")->isSet())
	{
		std::string path = callVarList->find("dir")->toString();
		path = trim_left( path );
		if( !path.empty() )
		{
			entry = dynamic_cast<RtiDirEntry*>( entry->findNode(path, DirNode::FIND_CASE_INSENSITIVE) ) ;
			if (!entry)
			{
				returnVarList->find(RtiKeyword::STATUS_VAR)->set(RtiKeyword::StatusERROR) ;
				return "Error: Cannot run ls on " + path ;
			}
		}
	}

	return entry->ls() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdHelp()
{
	RtiDirEntry* cwd = mMsgParser.getWorkingDir() ;
	RtiDirEntry* entry = cwd ;

	bool showCommandHelp = true ;
	if (callVarList->find("item")->isSet())
	{
		std::string item = callVarList->find("item")->toString();
		item = trim_left( item );
		if( !item.empty() )
		{
			showCommandHelp = false ;
			entry = dynamic_cast<RtiDirEntry*>( cwd->findNode(item, DirNode::FIND_CASE_INSENSITIVE) ) ;
			if (!entry)
			{
				returnVarList->find(RtiKeyword::STATUS_VAR)->set(RtiKeyword::StatusERROR) ;
				return "Error: Cannot run help on " + item ;
			}
		}
	}

	std::string reply ;

	// do we need to start by showing the command help?
	if (showCommandHelp)
	{
		reply += mBuiltinCommandHelp ;
	}
	reply += entry->help() ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdSu()
{
	// if no password specified just show current mode
	if (!callVarList->find("password")->isSet())
	{
		return (mMsgParser.isSuperUser() ? "Super user mode" : "Normal user mode") ;
	}

	std::string password(callVarList->find("password")->toString()) ;

	// check for special case of "password" being 'exit'
	if (password == "exit")
	{
		// exit super user mode
		mMsgParser.setSuperUser(false) ;
		return "Exited super user mode" ;
	}

	// password specified but already in su mode
	if (mMsgParser.isSuperUser())
		return "In super user mode" ;

	// check password to switch to su mode
	if (password != mPassword)
	{
		returnVarList->find(RtiKeyword::STATUS_VAR)->set(RtiKeyword::StatusERROR) ;
		return "Invalid password. Attempted access has been logged" ;
	}

	mMsgParser.setSuperUser(true) ;
	return "Entered super user mode" ;
}


//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdMemory()
{
	long int rss(Process::getResidentSetSize()) ;
	unsigned long total, free, used, shared, buffer ;
	Process::getSystemMemory(total, free, used, shared, buffer) ;

	std::string reply(
		"process=" + std::to_string(rss) + "kB " +
		"total=" + std::to_string(total) + "bytes " +
		"free=" + std::to_string(free) + "bytes " +
		"used=" + std::to_string(used) + "bytes " +
		"shared=" + std::to_string(shared) + "bytes " +
		"buffer=" + std::to_string(buffer) + "bytes"
	) ;

	return reply ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdQuit()
{
	if (!mMsgParser.isSuperUser())
		return "Need to be super user to exit application" ;

	// Throw exception - may be able to (someday!) catch this in main()
	ILoggable::logEventInfo("QUIT command") ;
	throw std::runtime_error("Application 'quit' tif command") ;

	// will never get here
	return "EXIT" ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EntryCmd::cmdSleep()
{
	if (!callVarList->find("sleep")->isSet())
	{
		return "Must specify sleep duration" ;
	}

	unsigned duration(callVarList->find("sleep")->toUint()) ;
	Task::msSleep(duration) ;
	return "" ;
}
