/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirNode.cpp
 * \brief     Directory node
 *
 *
 * \details   Node in a directory tree  that can be either a file or a directory containing further nodes
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include "stringfunc.hpp"

#include "DirNode.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
std::string DirNode::PATHSEP("/") ;
std::string DirNode::THISDIR(".") ;
std::string DirNode::PREVDIR("..") ;
std::string DirNode::HIDDEN(".") ;

//=============================================================================================================
// STATIC
//=============================================================================================================
bool DirNode::mShowHidden(false) ;

//=============================================================================================================
// PUBLIC - DirNode
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::DirNode::setShowHidden(bool showHidden)
{
	mShowHidden = showHidden ;
}

//-------------------------------------------------------------------------------------------------------------
DirNode::DirNode(const std::string& pathname, DirNodeType type) :
	mType(type),
	mHidden(hidden(pathname)),
	mPath(path(pathname)),
	mName(name(pathname)),
	mError("")
{
//	std::cerr << "NEW: DirNode Path=" << mPath << " Name=" << mName << " @ " << this << std::endl ;

	// for directories we need to set up the special directories '.' & '..'
	// Just point at ourself initially
	if (mType == DN_DIRECTORY)
	{
		std::string dirPath(mPath) ;
		if (!mName.empty())
			dirPath.append(mName+PATHSEP) ;
		mDirContents[THISDIR] = new DirEntry(dirPath, THISDIR, this) ;
		mDirContents[PREVDIR] = new DirEntry(dirPath, PREVDIR, this) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
DirNode::~DirNode()
{
//	std::cerr << "DEL: DirNode Path=" << mPath << " Name=" << mName << " @ " << this << std::endl ;
	for (auto entry : mDirContents)
	{
		delete entry.second ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool DirNode::add(DirNodePtr node)
{
	DirNodePtr dir = this ;

	if (node->mPath[0] != PATHSEP[0])
	{
		mError = "Path " ;
		mError += node->mPath ;
		mError += " is not absolute" ;
		return false ;
	}

	// Are we at the correct level?
	if (node->mPath != dir->mPath)
	{
		// Get directory
		dir = findDir(node->mPath) ;
		if (!dir)
		{
			if (mError.empty())
			{
				mError = "Unable to add path " ;
				mError += node->mPath ;
				mError += node->mName ;
			}
			return false ;
		}
	}

	// Must now be at the correct level, check for existing entry
	auto entry(dir->mDirContents.find(node->mName)) ;
	if (entry != dir->mDirContents.end())
	{
//std::cerr << "DirNode::add(" << node->getFullPath() << ") already exists, deleting previous..." << std::endl;
		delete entry->second ;
		dir->mDirContents.erase(entry) ;
	}

	// add node to contents
	dir->mDirContents[node->mName] = new DirEntry(node->mPath, node->mName, node) ;

	// if new node is a directory then set '..' to the new parent
	if (node->mType == DN_DIRECTORY)
	{
		node->mDirContents[PREVDIR]->setNode(dir) ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DirNode::deleteDirContents()
{
	if (!isDir())
	{
		mError = "Node " ;
		mError += mPath ;
		mError += mName ;
		mError += " is not a directory" ;
		return false ;
	}

	// Remove entries from contents
	for (DirContentsIterator iter(mDirContents.begin()); iter != mDirContents.end(); ++iter)
	{
		if ( isThisDir(iter->first) || isPrevDir(iter->first) )
		{
			// skip
			++iter ;
		}
		else
		{
			// delete
			bool ok = true ;
			if (iter->second->getNode()->isDir())
				ok = iter->second->getNode()->deleteDirContents() ;

			if (!ok)
				return false ;

			delete iter->second ;
			mDirContents.erase(iter++) ;
		}
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::string DirNode::getError()
{
	std::string error(mError) ;
	mError.clear() ;

	return error ;
}

//-------------------------------------------------------------------------------------------------------------
DirNodePtr DirNode::findNode(const std::string& path, FindType findOption)
{
	// start at this level
	DirNodePtr dir = this ;
	if (!dir->isDir())
	{
		return (DirNodePtr)0 ;
	}

	// check for absolute path
	if (path.at(0) == PATHSEP[0])
	{
		// Get to root
		dir = getRoot() ;
		if (!dir)
			return (DirNodePtr)0 ;
	}

	// Walk down path - stop with error if not present
	std::vector< std::string > dirNames( splitpath(path) ) ;

	for (auto name : dirNames)
	{
		DirContentsIterator dirIter(dirFind(dir, name, findOption)) ;
		if (dirIter == dir->mDirContents.end())
			return (DirNodePtr)0 ;

		dir = dirIter->second->getNode() ;
	}

	return dir ;
}

//-------------------------------------------------------------------------------------------------------------
DirNodePtr DirNode::findDir(const std::string& path, FindType findOption)
{
	DirNodePtr node = findNode(path, findOption) ;
	if (!node)
		return (DirNodePtr)0 ;

	if (node->mType != DN_DIRECTORY)
		return (DirNodePtr)0 ;

	return node ;
}

//-------------------------------------------------------------------------------------------------------------
DirNodePtr DirNode::findFile(const std::string& path, FindType findOption)
{
	DirNodePtr node = findNode(path, findOption) ;
	if (!node)
		return (DirNodePtr)0 ;

	if (node->mType != DN_FILE)
		return (DirNodePtr)0 ;

	return node ;
}


//-------------------------------------------------------------------------------------------------------------
void DirNode::setHidden(bool hidden)
{
	mHidden = hidden ;
}

//-------------------------------------------------------------------------------------------------------------
void DirNode::rename(const std::string& name)
{
	// Update parent contents - change map key
	DirNodePtr parent(mDirContents[PREVDIR]->getNode()) ;
	if (parent != this)
	{
		DirEntry* entry(nullptr) ;
		for (auto& dir : parent->mDirContents)
		{
			if (mName == dir.first)
			{
				entry = dir.second ;
				break ;
			}
		}
		if (entry)
		{
			parent->mDirContents.erase(mName) ;
			parent->mDirContents[name] = entry ;
		}
	}

	// Create the from/to path segments used for renaming
	std::string from("/" + mName + "/") ;
	std::string to("/" + name + "/") ;

	// Process directory contents - all the paths of these sub-nodes will need this dir renaming
	renamePaths(from, to) ;

	// Finally rename the node
	mName = name ;

}


//-------------------------------------------------------------------------------------------------------------
std::string DirNode::getFullPath() const
{
	std::string fullpath(mPath) ;
	if (!mName.empty())
		fullpath += mName ;
	return fullpath ;
}


//-------------------------------------------------------------------------------------------------------------
std::string DirNode::getPath() const
{
	return mPath ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirNode::getName() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
bool DirNode::isDir() const
{
	return mType == DN_DIRECTORY ;
}


//-------------------------------------------------------------------------------------------------------------
bool DirNode::isRootDir() const
{
	if (!isDir())
		return false ;

	if ((mPath == PATHSEP) && (mName == ""))
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DirNode::isHidden() const
{
	return mHidden ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< DirNodePtr > DirNode::getDir()
{
	std::vector< DirNodePtr > contents ;
	for (DirContentsIterator iter(mDirContents.begin()); iter != mDirContents.end(); ++iter)
	{
		if ( isThisDir(iter->first) || isPrevDir(iter->first) )
			continue ;

		// skip hidden entries
		DirNodePtr node(iter->second->getNode()) ;
		if ( !node->isHidden() || mShowHidden )
			contents.push_back( node ) ;
	}

	return contents ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector< DirNodePtr > DirNode::getDirAll()
{
	std::vector< DirNodePtr > contents ;
	for (DirContentsIterator iter(mDirContents.begin()); iter != mDirContents.end(); ++iter)
	{
		if ( isThisDir(iter->first) || isPrevDir(iter->first) )
			continue ;

		contents.push_back( iter->second->getNode() ) ;
	}

	return contents ;
}

//-------------------------------------------------------------------------------------------------------------
void DirNode::show() const
{
	std::cout << mPath ;
	if (!mName.empty())
	{
		std::cout << mName << (isDir() ? PATHSEP : "") ;
	}
	std::cout << std::endl ;
	if (isDir())
	{
		for (auto entry : mDirContents)
		{
			if ( isThisDir(entry.first) || isPrevDir(entry.first) )
				continue ;

			entry.second->getNode()->show() ;
		}
	}

}


//-------------------------------------------------------------------------------------------------------------
void DirNode::showDetails() const
{
	std::cout << std::endl ;
	std::cout << "NODE: " << mPath << " " ;
	if (!mName.empty())
	{
		std::cout << mName << (isDir() ? PATHSEP : "") ;
	}
	std::cout << " @ " << this  ;
	if (mHidden)
		std::cout << " [HIDDEN]" ;
	std::cout << std::endl ;
	if (isDir())
	{
		for (auto entry : mDirContents)
		{
			std::cout << "[" << entry.first << "] " ;
			if ( isThisDir(entry.first) || isPrevDir(entry.first) )
			{
				std::cout << "ENTRY: " << entry.second->getPath() << " " ;
				if (!entry.second->getName().empty())
				{
					std::cout << entry.second->getName() << (isDir() ? PATHSEP : "") ;
				}
				std::cout << " @ " << entry.second <<
						" NODE @ " << entry.second->getNode() <<
						std::endl ;
				continue ;
			}
			entry.second->getNode()->showDetails() ;
		}
	}
}



//=============================================================================================================
// PRIVATE - DirNode
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirNodePtr DirNode::getRoot()
{
	// Are we already there
	if (isRootDir())
		return this ;

	// Get to root
	DirNodePtr dir = this ;
	DirNodePtr prevDir = 0 ;
	while (!dir->isRootDir())
	{
		dir = dir->mDirContents[PREVDIR]->getNode() ;
		if (dir == prevDir)
		{
			mError = "Internal error: directory " ;
			mError += dir->mPath ;
			mError += dir->mName ;
			mError += " does not have parent directory set" ;
			return (DirNodePtr)0 ;
		}
	}

	return dir ;
}


//-------------------------------------------------------------------------------------------------------------
DirNode::DirContentsIterator DirNode::dirFind(DirNodePtr dir, const std::string& name, FindType findOption)
{
	// for case sensitive match we can just use the STL
	if (findOption == FIND_CASE_SENSITIVE)
		return dir->mDirContents.find(name) ;

	// otherwise we have to iterate
	std::string lower(toLower(name)) ;
	DirContentsIterator iter ;
	for (iter = dir->mDirContents.begin(); iter != dir->mDirContents.end(); ++iter)
	{
		if (lower == toLower(iter->first))
		{
			return iter ;
		}
	}
	return iter ;
}


//=============================================================================================================
// STATIC - DirNode
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string DirNode::path(const std::string& fullpath)
{
	if (fullpath.empty())
		return "" ;

	// strip out any hidden element markers
	std::string path( replaceStrs(fullpath, PATHSEP+HIDDEN, PATHSEP) ) ;

	// remove trailing '/' if path is not "/"
	if (path.size() > 1)
	{
		if (path.at(path.size()-1) == PATHSEP[0])
			path.erase(path.size()-1) ;
	}
	if (path.empty())
		return "" ;

	// got to last '/' and return from start of string to /
	std::size_t pos = path.find_last_of(PATHSEP) ;
	if (pos == std::string::npos)
		return "" ;

	return path.substr(0, pos+1) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirNode::name(const std::string& fullpath)
{
	if (fullpath.empty())
		return "" ;

	// strip out any hidden element markers
	std::string name( replaceStrs(fullpath, PATHSEP+HIDDEN, PATHSEP) ) ;

	// remove trailing '/' if full string is not just "/"
	if (name.size() > 1)
	{
		if (name.at(name.size()-1) == PATHSEP[0])
			name.erase(name.size()-1) ;
	}
	if (name.empty())
		return "" ;

	// find '/' - if not present then return full string
	std::size_t pos = name.find_last_of(PATHSEP) ;
	if (pos == std::string::npos)
		return name ;

	// remove everything after last '/'
	return name.substr(pos+1, std::string::npos) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> DirNode::splitpath(const std::string& path)
{
	std::vector< std::string > names ;
	std::size_t start = 0 ;
	std::size_t end = path.find_first_of(PATHSEP) ;
	while (start != std::string::npos)
	{
		std::size_t len = end-start ;
		if (end == std::string::npos)
			len = std::string::npos ;
		std::string name = path.substr(start, len) ;
		if (!name.empty())
			names.push_back( name ) ;

		if (end == std::string::npos)
			break ;

		start = end+1 ;
		if (start+1 >= path.size())
			break ;

		end = path.find_first_of(PATHSEP, start) ;
	}

	return names ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DirNode::hidden(const std::string& fullpath)
{
	return fullpath.find(HIDDEN) != std::string::npos ;
}


//-------------------------------------------------------------------------------------------------------------
bool Mplane::DirNode::isThisDir(const std::string& path)
{
	if (path == THISDIR)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DirNode::isPrevDir(const std::string& path)
{
	if (path == PREVDIR)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void DirNode::renamePaths(const std::string& from, const std::string& to)
{
	mPath = replaceStrs(mPath, from, to) ;

	// Process directory contents - all the paths of these sub-nodes will need this dir renaming
	for (auto& dir : mDirContents)
	{
		// rename path of this entry
		dir.second->renamePath(from, to) ;

		if ( isThisDir(dir.first) || isPrevDir(dir.first) )
			continue ;

		// recursively modify the node
		dir.second->getNode()->renamePaths(from, to) ;
	}
}

//=============================================================================================================
// PUBLIC - DirEntry
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DirEntry::DirEntry(const std::string& path, const std::string& name, DirNodePtr node) :
	mNode(node),
	mPath(path),
	mName(name)
{
//	std::cerr << "NEW: DirEntry Path=" << mPath << " Name=" << mName << " @ " << this << " (node @ " << node << ")" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
DirEntry::~DirEntry()
{
//	std::cerr << "DEL: DirEntry Path=" << mPath << " Name=" << mName << " @ " << this << std::endl ;

	// don't delete node if name is '.' or '..'
	if ( (mName == DirNode::THISDIR) || (mName == DirNode::PREVDIR) )
		return ;

//	std::cerr << "DEL: + delete node " << mNode << std::endl ;
	delete mNode ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirEntry::getFullPath() const
{
	std::string fullpath(mPath) ;
	if (!mName.empty())
		fullpath += mName ;
	return fullpath ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirEntry::getPath() const
{
	return mPath ;
}

//-------------------------------------------------------------------------------------------------------------
std::string DirEntry::getName() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
DirNodePtr DirEntry::getNode() const
{
	return mNode ;
}

//-------------------------------------------------------------------------------------------------------------
void DirEntry::setNode(DirNodePtr node)
{
	mNode = node ;
}

//-------------------------------------------------------------------------------------------------------------
void DirEntry::renamePath(const std::string& from, const std::string& to)
{
	mPath = replaceStrs(mPath, from, to) ;
}
