/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtiMsgHandler.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <time.h>

#include <algorithm>
#include <iostream>
#include <sstream>

#include <cstdio>
#include <cstdarg>

#include "Process.h"
#include "Tokeniser.h"
#include "stringfunc.hpp"
#include "Task.h"

#include "Nodes/RtiDirEntry.h"
#include "Nodes/DirClass.h"
#include "CmdNode/EntryCmd.h"

#include "TcpPortMgr.h"

#include "RtiKeyword.h"
#include "RtiMsgHandler.h"

using namespace Mplane ;

//=============================================================================================================
// CONST
//=============================================================================================================
const std::string PROMPT{"->"} ;
const std::string MULTICMD_SEP{";"} ;
const std::string MULTIREPLY_SEP{"%~%\n"} ;

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================
static std::string formatTimeDiff(const timespec& start, const timespec& end) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RtiMsgHandler::RtiMsgHandler( ) :
	SocketHandler("RtiMsgHandler", "TIF", Task::PRIORITY_HIGH),
	RtiSettings(),

	mTreeRoot(new DirClass(DirNode::PATHSEP, "Top level directory", *this, *this)),
	mCwd(mTreeRoot),
	mRtiConnected(false),
	mThereWasAnException(0),
	mSuperUser(false)
{
}

//-------------------------------------------------------------------------------------------------------------
RtiMsgHandler::~RtiMsgHandler()
{
	// delete directory tree and all it's contents
	delete mTreeRoot ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::add(RtiDirEntry* entry)
{
	return mTreeRoot->add(entry) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::addDir(DirClass* entry)
{
	// If directory already exists then just use that one
	if (mTreeRoot->findNode(entry->getFullPath()))
	{
		// free up entry
		delete entry ;

		return true ;
	}


	// Need to create directory
	Tokeniser token(entry->getFullPath(), "/") ;

	std::string pathSoFar("") ;
	while( token.nextToken() )
	{
		std::string dir = token.getToken() ;

		// is this the node we want?
		if ( !token.nextToken() )
			break ;

		pathSoFar += DirNode::PATHSEP + dir ;

		// see if dir is already present
		DirNode* node = mTreeRoot->findNode(pathSoFar) ;
		if (!node)
		{
			// create a new entry
			if (!mTreeRoot->add( static_cast<RtiDirEntry *>(new DirClass(
					pathSoFar, "", *this, *this)
			)))
				return false ;
		}
		else
		{
			if (!node->isDir())
				return false ;
		}
	}

	return mTreeRoot->add( static_cast<RtiDirEntry *>(entry) ) ;
}


//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::parseMulti(const std::string& msg)
{
	// if this is NOT a multi command string then process normally
	if (msg.find(MULTICMD_SEP) == std::string::npos)
		return parse(msg) ;

	// Multiple commands are joined in a single line with a separator between each command
	// Split into single commands and process each, joining all the replies with a special
	// multiple reply separator
	Tokeniser tokenise(msg, MULTICMD_SEP);
	std::vector<std::string> cmds(tokenise.getTokens()) ;
	std::string multireply ;
	for (auto cmd : cmds)
	{
		if (startsWith(cmd, "exit"))
			return multireply ;

		std::string reply = parse(cmd) ;

		if (!multireply.empty())
			multireply += MULTIREPLY_SEP ;

		multireply += reply ;
	}

	return multireply ;
}



//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::parse(const std::string& msg)
{
	Tokeniser tokenise(msg);

	// are we processing an inbuilt command, rather than  an interface
	std::string returnStr  = procCommand( msg );

	// if the string returned from procCommand is not empty we've performed a built in
	// command, so return immediately with the result
	if( !returnStr.empty() )
	{
		returnStr += "\n" ;
		return returnStr;
	}

	// get the first token of the radio test interface message
	std::string classFuncName("") ;
	if( tokenise.nextToken())
	{
		classFuncName = tokenise.getToken();
	}
	else
	{
		return RtiDirEntry::createErrorStatus("Syntax error: " + msg + " - no valid token data") + "\n" ;
	}

	// Get rest of command args
	std::string args = follows( msg, classFuncName );


	// Treat '.' as a path separator - so command can also look like class member access:
	//
	//   carrier.write
	//
	// is the same as
	//
	//   carrier/write
	//
	std::string name = replaceChars(classFuncName, ".", '/') ;

	// Find directory entry to handle the command
	RtiDirEntry* entry = dynamic_cast<RtiDirEntry*>( mCwd->findNode(name, DirNode::FIND_CASE_INSENSITIVE) ) ;

	if( entry == 0 || isPathHidden(entry))
		return RtiDirEntry::createErrorStatus("Syntax error: No handler for " + classFuncName) + "\n" ;

	returnStr = entry->processFunc( args );
	returnStr += "\n" ;
	return returnStr;
}


//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::setCallArgs(const std::string& callArgs) const
{
	return callArgs ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::setReturnArgs(const std::string& returnArgs) const
{
	// Need to add special return variables to all returns:
	//	"ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info]"
	return RtiKeyword::addKeywordArgs(returnArgs) ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgHandler::setSuperUser(bool superUser)
{
	mSuperUser = superUser ;
	DirNode::setShowHidden(mSuperUser) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::isSuperUser() const
{
	return mSuperUser ;
}



//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::tcpPortOpen(ITcpPortIoTypes::TcpPortType type,
		unsigned port, unsigned maxConnections, std::string& failReason)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	return tcpPortMgr->portOpen(type, port, maxConnections, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::tcpPortClose(unsigned port, std::string& failReason)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	return tcpPortMgr->portClose(port, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgHandler::tcpPortShow(std::ostream& os)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	tcpPortMgr->show(os) ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgHandler::tcpPortSend(unsigned port, const std::string& msg)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	tcpPortMgr->portSend(port, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void RtiMsgHandler::tcpPortSend(unsigned port, const std::vector<uint8_t>& msg)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	tcpPortMgr->portSend(port, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::tcpPortReceive(unsigned port,
		std::vector<uint8_t>& data, unsigned expectedSize,
		unsigned timeoutSecs)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	return tcpPortMgr->portReceive(port, data, expectedSize, timeoutSecs) ;
}

bool RtiMsgHandler::tcpPortReceive(unsigned port,
		ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize,
		unsigned timeoutSecs)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	return tcpPortMgr->portReceive(port, callback, expectedSize, timeoutSecs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::tcpIsPortOpen(unsigned port)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	return tcpPortMgr->isPortOpen(port) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RtiMsgHandler::tcpPortSetBinary(unsigned port, bool binary)
{
	std::shared_ptr<TcpPortMgr> tcpPortMgr(TcpPortMgr::getInstance()) ;
	tcpPortMgr->setBinary(port, binary) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::procCommand(const std::string& command)
{

	Tokeniser tokenise(command) ;

	// get the first token of the radio test interface message
	if( !tokenise.nextToken())
		return RtiDirEntry::createErrorStatus("Syntax error: " + command + " - no valid token data") ;


	// Get rest of command args
	std::string cmd(tokenise.getToken()) ;
	std::string args = follows( command, cmd );

	// Prefix with hidden builtin directory path
	std::string builtinCmd(EntryCmd::getBuiltinCommand(cmd)) ;

	// Find directory entry to handle the command
	RtiDirEntry* entry = dynamic_cast<RtiDirEntry*>( mCwd->findNode(builtinCmd, DirNode::FIND_CASE_INSENSITIVE) ) ;

	if ( entry == 0 )
		return "" ;

	return entry->processFunc( args );
}


//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::setWorkingDir(const std::string& path)
{
	RtiDirEntry* dir = mTreeRoot ;
	if( !path.empty() )
	{
		std::string trimmedPath = trim_left( path );
		dir = dynamic_cast<RtiDirEntry*>( mCwd->findDir(trimmedPath, DirNode::FIND_CASE_INSENSITIVE) ) ;
	}

	if (!dir)
		return false ;

	if (isPathHidden(dir))
		return false ;

	mCwd = dir ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
RtiDirEntry* RtiMsgHandler::getWorkingDir() const
{
	return mCwd ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RtiMsgHandler::getPrompt() const
{
	return (isSuperUser() ? (std::string("#")+PROMPT) : PROMPT) ;
}



//-------------------------------------------------------------------------------------------------------------
int RtiMsgHandler::handler()
{
	mRtiConnected = true;
	mThereWasAnException = false;

	logDebugNormal("New connection on socket: %d", this->mSock) ;

	// Keep a list of all the possible paths
	std::vector<std::string> absPaths(getDirPaths(mTreeRoot)) ;

	// now get the list relative to the current working directory
	std::string cwd(mCwd->getFullPath()) ;
	std::vector<std::string> relPaths(getRelPaths(absPaths, cwd)) ;
	std::vector<std::string> allPaths(relPaths) ;
	allPaths.insert(allPaths.end(), absPaths.begin(), absPaths.end()) ;
	std::vector<std::string> dotPaths(getDotPaths(allPaths)) ;
	allPaths.insert(allPaths.end(), dotPaths.begin(), dotPaths.end()) ;

	// Make this a non-block socket - allows us to service the task watchdog while waiting for user input
	setNonBlocking(true);

	// ensure socket is in binary mode
	setBinary(true) ;

	// Create telnet handler
	RtiTelnet telnetHandler(this) ;

	// Create editor to handle keys
	std::string pathSeperators( DirNode::PATHSEP + "." ) ;
	RtiMsgEditor msgEdit(this, pathSeperators) ;

	// If enabled, time execution of commands
	std::string executionTime("") ;

	// If enabled, show memory usage
	std::string memoryUsage("") ;

	// copy the socket
	int mySocket = mSock;

	// reply from command
	std::string reply ;

	bool exit(false) ;
	while (mRtiConnected && isConnected())
	{
		try
		{
			// get memory usage if required
			bool showMemoryUsed(get("memory")->toBool()) ;
			if (showMemoryUsed)
			{
				memoryUsage = "[" + std::to_string(Process::getResidentSetSize()) + " kB] " ;
			}
			else
			{
				if (!memoryUsage.empty())
					memoryUsage.clear() ;
			}

			std::string data;
			std::string prompt( reply + executionTime + memoryUsage + mCwd->getFullPath() + getPrompt() ) ;
			reply.clear() ;

			// output reply and prompt
			send(prompt);

			if(exit)
			{
				this->close();
				mRtiConnected = false;
				logDebugNormal("Exit command") ;
			}


			int watchdogCount = 0;

			// get user data - wait until we get a CR
			while(data.find_first_of("\r") == std::string::npos)
			{
				// get the "no echo" setting
				bool noEcho( get("noecho")->toBool() ) ;

				std::string readBuff ;
				bool gotChars( telnetHandler.handle(readBuff) ) ;

				// handle user entry
//				if (telnetHandler.noEchoMode())
				if (noEcho || telnetHandler.noEchoMode())
				{
					// NOTE: NO-ECHO mode does NOT support multiline input
					if (gotChars)
						data += readBuff ;
				}
				else
				{
					gotChars = msgEdit.handle(readBuff, data, allPaths, getPrompt()) ;
				}

				// don't kick the watchdog on every loop iteration
				watchdogCount++;
				if(watchdogCount == 100)
				{
					kickSoftwareWatchdog();
					// reset the counter
					watchdogCount = 0;
				}

				// if the read buffer is empty then wait a while
				if (!gotChars)
				{
					// sleep for 100ms to wait until a char is ready - increasing this
					// delay reduces the CPU load but increases the lag time in reading
					// from the socket
					Task::msSleep(100);

				}
			}

			// strip out any comment
			std::size_t pos(data.find('#')) ;
			if (pos != std::string::npos)
			{
				data = data.substr(0, pos) + "\r" ;
			}

			// handle empty command
			if (data == "\r")
				continue ;

			// Track TIF commands
			logDebugNormal("TIF-CMD[%d] %s", mSock, data.c_str()) ;

			// process the command
			if( startsWith( data, "exit"))
			{
				exit = true ;
			}
//#ifdef OFF_TARGET
//            else if( startsWith( data, "quit"))
//            {
//                this->close();
//                mRtiConnected = false;
//                logDebugNormal("QUIT command") ;
//                ::exit(0) ;
//            }
//#endif
			else
			{
				// time command if required
				executionTime.clear() ;
				timespec tStart, tStop ;
				bool timeExecution(get("timestamp")->toBool()) ;

				if (timeExecution)
					clock_gettime(CLOCK_REALTIME, &tStart) ;

				// Process the command
				reply = parseMulti(data) ;

				// Track TIF commands
				logDebugNormal("TIF-REPLY[%d] %s", mSock, reply.c_str()) ;

				// show time
				if (timeExecution)
				{
					clock_gettime(CLOCK_REALTIME, &tStop) ;
					executionTime = formatTimeDiff(tStart, tStop) ;
				}

				// Check for a change in working directory
				std::string newCwd(mCwd->getFullPath()) ;
				if (newCwd != cwd)
				{
					cwd = newCwd ;
					relPaths = getRelPaths(absPaths, cwd) ;
					allPaths = relPaths ;
					allPaths.insert(allPaths.end(), absPaths.begin(), absPaths.end()) ;
				}

			}
		}
		catch (SocketException& e)
		{
			logDebugNormal("Client connection error, exiting (exception: %s)", e.description().c_str()) ;
			// leave close to system level when we return from the handler
			// this->close();
			mThereWasAnException = true;
			mRtiConnected = false;
		}
	}

	logDebugNormal("Connection on socket: %d closed", mySocket) ;

	if( mThereWasAnException )
		return ERROR;

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
int RtiMsgHandler::sendOutput(const std::string& data)
{
	if (mRtiConnected)
	{
		try
		{
			send(data) ;

		} catch (SocketException& e)
		{
			std::cout << "Client send failed" << std::endl;
			// leave close to system level when we return from the handler
			// this->close();
			mThereWasAnException = true;
			mRtiConnected = false;
		}
	}

	if( mThereWasAnException )
		return ERROR;
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool RtiMsgHandler::send(const std::string& msg)
{
	// replace any NL with CR NL
	std::string msgCopy(msg) ;

	std::size_t pos(msgCopy.find('\n')) ;
	while (pos != std::string::npos)
	{
		msgCopy.insert(pos, "\r") ;
		pos = msgCopy.find('\n', pos+2) ;
	}

	*this << msgCopy ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
int RtiMsgHandler::recv(std::string& msg)
{
	*this >> msg ;
	return msg.size() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiMsgHandler::getDirPaths(const DirNodePtr& dirNode)
{
	std::vector<std::string> paths ;

	std::vector< DirNodePtr > dirContents( dirNode->getDir() ) ;
	for (std::vector< DirNodePtr >::const_iterator iter(dirContents.begin()); iter != dirContents.end(); ++iter)
	{
		paths.push_back((*iter)->getFullPath()) ;
	}
	for (std::vector< DirNodePtr >::const_iterator iter(dirContents.begin()); iter != dirContents.end(); ++iter)
	{
		if ((*iter)->isDir())
		{
			std::vector<std::string> subPaths(getDirPaths(*iter)) ;
			paths.insert(paths.end(), subPaths.begin(), subPaths.end()) ;
		}
	}

	return paths ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiMsgHandler::getRelPaths(const std::vector<std::string>& absPaths, const std::string& path)
{
	// ensure there is a trailing path separator
	std::string pathPrefix(path) ;
	if (pathPrefix.size() && pathPrefix[pathPrefix.size()-1] != DirNode::PATHSEP[0])
		pathPrefix += DirNode::PATHSEP ;

	std::vector<std::string> paths ;
	for (std::vector<std::string>::const_iterator iter(absPaths.begin()); iter != absPaths.end(); ++iter)
	{
		// if absolute path doesn't start with the specified path, then it can't be under that path so ignore
		if (iter->find(pathPrefix) != 0)
			continue ;

		// add this path after removing the prefix
		paths.push_back(iter->substr(pathPrefix.size())) ;
	}

	return paths ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> RtiMsgHandler::getDotPaths(const std::vector<std::string>& paths)
{
	// For those paths containing a path separator, convert the separator to '.'
	std::vector<std::string> newPaths ;
	for (std::vector<std::string>::const_iterator iter(paths.begin()); iter != paths.end(); ++iter)
	{
		// See if path contains a separator
		if (iter->find(DirNode::PATHSEP) != 0)
			continue ;

		// Replace separator
		std::string toDot(*iter) ;
		std::replace(toDot.begin(), toDot.end(), DirNode::PATHSEP[0], '.') ;
		newPaths.push_back(toDot) ;
	}

	return newPaths ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RtiMsgHandler::isPathHidden(DirNodePtr node) const
{
	// super-user can see all
	if (mSuperUser)
		return false ;

	return node->isHidden() ;
}

//=============================================================================================================
// LOCAL STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static std::string formatTimeDiff(const timespec& tStart, const timespec& tEnd)
{
	// get diff
	timespec tDiff ;
	tDiff.tv_nsec = tEnd.tv_nsec - tStart.tv_nsec ;
	tDiff.tv_sec  = tEnd.tv_sec  - tStart.tv_sec ;
	if (tDiff.tv_nsec < 0L)
	{
		tDiff.tv_sec--;
		tDiff.tv_nsec += 1000000000L ;
	}

	// Convert to string
	char timer_buff[128];
	unsigned us = (unsigned)(tDiff.tv_nsec / 1000L) ;
	snprintf(timer_buff, sizeof(timer_buff), "[+%d.%06u] ", (int)tDiff.tv_sec, us) ;

	return std::string(timer_buff) ;
}
