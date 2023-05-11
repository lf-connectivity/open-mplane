/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirScripts.cpp
 * \brief     Directory entry for RTI scripts
 *
 *
 * \details    Container for the scripts.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
// C lib
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

// C++
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "stringfunc.hpp"
#include "Tokeniser.h"

#include "ScriptsNode/DirScripts.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const std::string SCRIPTS_DIR_SETTING("scriptsDir") ;
static const std::string SCRIPTS_DIRNODE_NAME("/tif:scripts") ;
static const std::string SCRIPTS_EXTENSION(".tsf") ;

static bool debug = false ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirScripts::DirScripts(IRtiMsgParser& msgParser, IRtiSettings& settings) :
	DirScriptsBase(SCRIPTS_DIRNODE_NAME, "Test scripts", msgParser, settings)
{
	setType(RTIENTRY_CLASS) ;

	if (debug)
		std::cerr << "SCRIPTS: DirScripts create" << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------
DirScripts::~DirScripts()
{
	if (debug)
		std::cerr << "SCRIPTS: DirScripts destroy" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirScripts::help()
{
	// Refresh contents
	updateScripts() ;

	return this->super::help() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirScripts::ls()
{
	// Refresh contents
	updateScripts() ;

	return this->super::ls() ;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DirScripts::registerMethods(IRtiMsgParser& msgParser, IRtiSettings& settings)
{
	RtiDirEntry* cwd( msgParser.getWorkingDir() ) ;

	// Create a directory to store the data in
	RtiDirEntry* dirNode( dynamic_cast<RtiDirEntry *>(cwd->findDir(SCRIPTS_DIRNODE_NAME)) ) ;
	if (!dirNode)
	{
		if (debug)
			std::cerr << "SCRIPTS: Add tif:scripts" << std::endl ;
		dirNode = static_cast<RtiDirEntry *>(new DirScripts(msgParser, settings) ) ;
		msgParser.add( dirNode ) ;
	}

	if (!dirNode)
		return ;

	// Now that scripts node has been added to the tree we can safely populate it's contents
	DirScripts* scriptsNode = dynamic_cast<DirScripts*>(dirNode) ;
	scriptsNode->updateScripts() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DirScripts::updateScripts()
{
	if (mScripts.empty())
	{
//std::cerr << "Reading scripts from " << mSettings.get(SCRIPTS_DIR_SETTING)->toString() << std::endl ;
		mScripts = getScripts(mSettings.get(SCRIPTS_DIR_SETTING)->toString()) ;
	}
	else
	{
		if ( !scriptsChanged(mSettings.get(SCRIPTS_DIR_SETTING)->toString()) )
			return ;

		// unregister methods
		this->deleteDirContents() ;
	}

	// Update the map
	mScriptsMap.clear() ;

	// Add scripts
	for (std::vector< ScriptInfo >::const_iterator iter(mScripts.begin()); iter != mScripts.end(); ++iter)
	{
		// Check for any need to create a sub-directory in the tree
		std::string dirStr(iter->dir) ;
		if (!dirStr.empty())
		{
			if (!makePath(dirStr))
				continue ;
		}

		// Add the entry
		bool ok = mMsgParser.add(
			static_cast<RtiDirEntry *>(new EntryScripts(
				SCRIPTS_DIRNODE_NAME + DirNode::PATHSEP + dirStr + iter->name,
				"",
				"",
				iter->comment,
				mMsgParser, mSettings,
				mScriptsMap))
		);
		if (!ok)
			continue ;

		// add to map
		mScriptsMap[toLower(iter->name)] = &(*iter) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
std::vector< DirScripts::ScriptInfo > DirScripts::getScripts(const std::string& directory)
{
	std::vector< ScriptInfo > scripts ;
	if (directory.empty())
		return scripts ;

	// append a trailing '/'
	std::string dirPath(directory) ;
	if (dirPath[dirPath.size()-1] != DirNode::PATHSEP[0])
		dirPath += DirNode::PATHSEP ;

	// Find all the files
	std::vector< std::string > files( findFiles(dirPath, SCRIPTS_EXTENSION) ) ;

	// Scan through the files to build the scripts list
	for (std::vector< std::string >::const_iterator iter(files.begin()); iter != files.end(); ++iter)
	{
		std::string comment( readComment(*iter) ) ;
		std::pair<std::string, std::string> dir_name( scriptPathToName(dirPath, *iter) ) ;

		scripts.push_back( ScriptInfo(*iter, dir_name.first, dir_name.second, comment) ) ;
	}

	// sort
	ByPath byPath ;
	std::sort(scripts.begin(), scripts.end(), byPath) ;

	return scripts ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< std::string > DirScripts::findFiles(const std::string& directory, const std::string& extension)
{
	std::vector<std::string> dirs ;
	std::vector< std::string > files ;

	{
	std::unique_lock<std::mutex> lock(mReaddirMutex) ;

	// open directory
	DIR *dirp = opendir(directory.c_str()) ;
	if (!dirp)
		return files ;

	// Allocate a suitably sized buffer
	long name_max = pathconf(directory.c_str(), _PC_NAME_MAX);
	if (name_max == -1)         /* Limit not defined, or error */
		name_max = 255;         /* Take a guess */

	// can't use the gcc recommended method of calculating the size of the buffer to allocate (gcc4.8.1 g++ doesn't
	// provide offsetof) but allocating the whole size of the structure + a buffer for the maximum name size
	// should provide ample space (though there's some controversy: http://womble.decadent.org.uk/readdir_r-advisory.html
	// who would have thought reading a directory would be such a pain!)
	//
//	size_t len = offsetof(struct dirent, d_name) + name_max + 1;
	size_t len = sizeof(struct dirent) + name_max + 1;
	struct dirent *dbuffp = (struct dirent *)malloc(len);

	// read the directory
	while(true)
	{
		struct dirent *dp ;
		/**
		 * The latest standards deprecate the use of readdir_r because it doesn't allow
		 * the specification of the length of the buffer. It is preferred to use readdir
		 * and add your own locks if necessary.
		 */
		dp = readdir(dirp) ;
		if (dp == NULL)
			break ;

		std::string name(dp->d_name) ;
		if ((name == ".") || (name == ".."))
			continue ;

		std::string path(directory + name) ;

		// check that it's a file
		struct stat s;
		if( stat(path.c_str(), &s) != 0 )
			continue ;

		if( s.st_mode & S_IFDIR )
		{
//	    	std::vector< std::string > contents( findFiles(path + "/", extension) ) ;
//	    	files.insert(files.end(), contents.begin(), contents.end()) ;
			dirs.push_back(path) ;
			continue ;
		}

		if( !(s.st_mode & S_IFREG) )
			continue ;

		// check extension if required
		if ( !extension.empty() && (path.find(extension) == std::string::npos) )
			continue ;

		// add to list
		files.push_back(path) ;
	}

	// close
	closedir(dirp) ;

	free(dbuffp) ;

	}

	// process any sub directories
	for (auto dir : dirs)
	{
		std::vector< std::string > contents( findFiles(dir + "/", extension) ) ;
		files.insert(files.end(), contents.begin(), contents.end()) ;
	}

	return files ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirScripts::readComment(const std::string& filePath)
{
	std::string comment ;

	std::string linebuff ;
	std::ifstream infile;
	infile.open(filePath.c_str());

	if (infile.is_open())
	{
		while(infile.good() && comment.empty())
		{
			// get the line text string
			std::getline(infile, linebuff);

			// skip blank lines
			std::string trimmed( trim_left(linebuff)) ;
			trimmed = trim_right(trimmed) ;
			if (trimmed.empty())
				continue ;

			// find comment
			if (trimmed[0] == '#')
			{
				comment = trimmed.substr(1) ;
				comment = trim_left(comment) ;
			}
		}
	}
	infile.close() ;

	return comment ;
}

//-------------------------------------------------------------------------------------------------------------
std::pair<std::string, std::string> DirScripts::scriptPathToName(const std::string& directory, const std::string& path)
{
	std::string name(path) ;

	// remove directory
	std::size_t pos( name.find(directory) ) ;
	if (pos != std::string::npos)
	{
		// remove from start of string to end of directory
		name.erase(0, pos+directory.size()) ;
	}

	// remove extension
	pos = name.find(SCRIPTS_EXTENSION) ;
	if (pos != std::string::npos)
	{
		// remove extension
		name.erase(pos) ;
	}

	// Check for sub-directory
	std::string dir("") ;
	pos = name.find_last_of("/") ;
	if (pos != std::string::npos)
	{
		// include final '/' in directory
		dir = name.substr(0, pos+1) ;
		name = name.substr(pos+1) ;
	}

	return std::make_pair(dir, name) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DirScripts::scriptsChanged(const std::string& directory)
{
	std::vector< ScriptInfo > scripts = getScripts(directory) ;


	if (scripts.size() != mScripts.size())
	{
		mScripts = scripts ;
		return true ;
	}


	std::vector< ScriptInfo >::const_iterator iter1(mScripts.begin()) ;
	std::vector< ScriptInfo >::const_iterator iter2(mScripts.begin()) ;
	while(iter1 != mScripts.end())
	{
		if (iter1->osPath != iter2->osPath)
		{
			mScripts = scripts ;
			return true ;
		}

		++iter1 ;
		++iter2 ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool DirScripts::makePath(const std::string& path)
{
	Tokeniser token(path, "/") ;

	std::string pathSoFar("") ;
	while( token.nextToken() )
	{
		std::string dir = token.getToken() ;
		if (!pathSoFar.empty())
			pathSoFar += DirNode::PATHSEP ;
		pathSoFar += dir ;

		// see if dir is already present
		DirNode* node = this->findNode(pathSoFar) ;
		if (!node)
		{
			// create a new entry
			if (!mMsgParser.add( static_cast<RtiDirEntry *>(new DirScriptsBase(
					SCRIPTS_DIRNODE_NAME + DirNode::PATHSEP + pathSoFar, "", mMsgParser, mSettings)
			)))
				return false ;
		}
		else
		{
			if (!node->isDir())
				return false ;
		}
	}
	return true ;
}
