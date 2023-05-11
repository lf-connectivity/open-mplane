/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangPersist.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>

#include "Path.h"
#include "stringfunc.hpp"

#include "YangPersist.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

#ifdef OFF_TARGET
const std::string PERSISTENT_STORAGE("/tmp/yang-persistent") ;
#else
const std::string PERSISTENT_STORAGE("/nandflash/yang-persistent") ;
#endif

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangPersist> IYangPersist::factory(const std::string& yangModelName)
{
	return std::make_shared<YangPersist>(yangModelName) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangPersist::YangPersist(const std::string &yangModelName) :
	mYangModelName(yangModelName),
	mSaveFilename(PERSISTENT_STORAGE + "/" + mYangModelName + ".save"),
	mDirty(false),
	mValues(),
	mPersistPaths()
{
	// ensure path exists
	Path::mkpath(PERSISTENT_STORAGE) ;
}

//-------------------------------------------------------------------------------------------------------------
YangPersist::~YangPersist()
{
	// flush file
	write() ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> YangPersist::read()
{
//std::cerr << "YangPersist[" <<  mYangModelName << "] read" << std::endl ;

	mValues.clear() ;

	std::ifstream in;
	in.open(mSaveFilename.c_str());
	if (!in.is_open())
	{
		return mValues ;
	}

	std::string line ;
	while(in.good())
	{
		// get the line text string
		std::getline(in, line);

		// Skip comments (#)
		std::string::size_type pos = line.find("#") ;
		if (pos != std::string::npos)
			line.erase(pos, std::string::npos) ;

		line = trim(line) ;

		if (line.length() == 0)
			continue ;

		// Looking for lines of the form:
		// "/xpath"="value"
		pos = line.find("\"=\"") ;
		if (pos == std::string::npos)
			continue ;

		std::string xpath(line.substr(0, pos+1)) ;
		std::string value(line.substr(pos+2)) ;

		xpath = trim(xpath) ;
		value = trim(value) ;

		if (xpath.size() < 3)
			continue ;
		if (value.size() < 3)
			continue ;

		// remove any quotes
		if ((xpath[0] == '"') && (xpath[xpath.size()-1] == '"'))
			xpath = xpath.substr(1, xpath.size()-2) ;
		if ((value[0] == '"') && (value[value.size()-1] == '"'))
			value = value.substr(1, value.size()-2) ;

		mValues[xpath] = value ;

//std::cerr << "YangPersist[" <<  mYangModelName << "] '" << xpath << "' => '" << value << "'" << std::endl ;
	}
	in.close() ;


	return mValues ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> YangPersist::values() const
{
	return mValues ;
}

//-------------------------------------------------------------------------------------------------------------
void YangPersist::set(const std::map<std::string, std::string> &values)
{
	for (auto entry : values)
		set(entry.first, entry.second) ;

	// do an auto-write after a batch
	write() ;
}

//-------------------------------------------------------------------------------------------------------------
void YangPersist::set(const std::string &xpath, const std::string &value)
{
//	std::cerr << "YangPersist[" <<  mYangModelName << "]::set '" << xpath << "' = '" << value << "'" << std::endl ;

	// filter out if xpath is not a persistent path
	if (!xpathMatchesPersist(xpath))
	{
//		std::cerr << "YangPersist[" <<  mYangModelName << "]::set - NOT PERSISTENT" << std::endl ;
		return ;
	}

	auto entry(mValues.find(xpath)) ;
	if (entry == mValues.end())
	{
//		std::cerr << "YangPersist[" <<  mYangModelName << "]::set - PERSISTENT new" << std::endl ;
		mValues[xpath] = value ;
		mDirty = true ;
		return ;
	}

	if (entry->second == value)
		return ;

//	std::cerr << "YangPersist[" <<  mYangModelName << "]::set - PERSISTENT changed" << std::endl ;
	entry->second = value ;
	mDirty = true ;
}

//-------------------------------------------------------------------------------------------------------------
void YangPersist::setPersist(const std::set<std::string> &xpaths)
{
	mPersistPaths.insert(xpaths.begin(), xpaths.end()) ;
}

//-------------------------------------------------------------------------------------------------------------
void YangPersist::setPersist(const std::string &xpath)
{
	mPersistPaths.insert(xpath) ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangPersist::write()
{
	// skip if no changes
	if (!mDirty)
		return true ;

	std::ofstream out;
	out.open(mSaveFilename.c_str());
	if (!out.is_open())
	{
		return false ;
	}

	out << "# Persistent values for YANG model " << mYangModelName << std::endl ;
	for (auto entry : mValues)
	{
		out << "\"" << entry.first << "\"=\"" << entry.second << "\"" << std::endl ;
	}

	out.close() ;

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool YangPersist::xpathMatchesPersist(const std::string &xpath) const
{
	for (auto path : mPersistPaths)
	{
		// see if xpath starts with this path
		if (startsWith(xpath, path))
			return true ;
	}

	return false ;
}
