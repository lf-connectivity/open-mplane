/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileMap.cpp
 * \brief     Read a file and convert it's contents to a std::map
 *
 *
 * \details   Read a file and convert it's contents to a std::map. Base implementation expects file format to be
 * 				lines of variable=value pairs. For example:
 *
 * 				HOME=/home/root
 * 				TERM=vt102
 * 				USER=root
 * 				SHLVL=2
 * 				interface=eth0
 * 				HUSHLOGIN=FALSE
 * 				PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin
 * 				MAIL=/var/spool/mail/root
 * 				SHELL=/bin/sh
 *
 * 				If a variable is set multiple times, then the *last* value set (reading down the file) is used
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>
#include <sstream>
#include <iostream>

#include "stringfunc.hpp"

#include "FileMap.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::string WHITESPACE(" \t") ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileMap::FileMap(const std::string &filePath) :
	FileMap()
{
	setPath(filePath) ;
}

//-------------------------------------------------------------------------------------------------------------
FileMap::FileMap() :
	mPath(),
	mValues(),
	mError()
{
}

//-------------------------------------------------------------------------------------------------------------
FileMap::~FileMap()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FileMap::setPath(const std::string &filePath)
{
	(void)error();

	if (filePath.empty())
		return setError("Invalid empty file path") ;

	mPath = filePath ;
	return processFile() ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> FileMap::values() const
{
	return mValues ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileMap::error()
{
	std::string temp ;
	std::swap(temp, mError) ;
	return temp ;
}

//-------------------------------------------------------------------------------------------------------------
void FileMap::setValues(const std::map<std::string, std::string> &values)
{
	(void)error();

	for (auto entry : values)
		mValues[entry.first] = entry.second ;
}


//-------------------------------------------------------------------------------------------------------------
bool FileMap::isValue(const std::string &name) const
{
	return mValues.find(name) != mValues.end() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileMap::value(const std::string &name) const
{
	if (!isValue(name))
		return std::string() ;

	return mValues.at(name) ;
}

//-------------------------------------------------------------------------------------------------------------
void FileMap::show() const
{
	std::cout << "-- FileMap: " << mPath << " --" << std::endl ;
	for (auto entry : mValues)
	{
		std::cout << entry.first << " = " << entry.second << std::endl ;
	}
	std::cout << "--------" << std::endl ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FileMap::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileMap::processFile()
{
	mValues.clear() ;

	std::ifstream infile;
	infile.open(mPath);

	if (!infile.is_open())
		return false ;

	// Scan through file updating each interface so we end up with their latest state
	std::string linebuff ;
	while(infile.good())
	{
		// get the line text string
		std::getline(infile, linebuff);

		// Trim spaces from the start & and of line
		linebuff = trim(linebuff, WHITESPACE) ;

		// skip empty
		if (linebuff.empty())
			continue ;

		// Skip comments
		if (linebuff[0] == '#')
			continue ;

		// get any variables
		std::size_t pos(linebuff.find("=")) ;
		if (pos == std::string::npos)
			continue ;

		std::string var(trim(linebuff.substr(0, pos), WHITESPACE)) ;
		std::string value(trim(linebuff.substr(pos+1), WHITESPACE)) ;

		mValues[var] = value ;

	}
	infile.close() ;

	return true ;
}
