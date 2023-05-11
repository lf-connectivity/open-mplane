/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Md5List.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>

#include "Tokeniser.h"
#include "stringfunc.hpp"
#include "Md5List.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Md5List::Md5List(const std::string& filePath)
{
	std::string linebuff ;
	std::ifstream infile;
	infile.open(filePath.c_str());
	if (!infile.is_open())
		return ;

	// File format:
	//	cf248b2e4b24131e502da502708e007a  lib/libgcc_s.so.1
	//	f9ea43b6b43d0d51ed0621165fe8a909  lib/libpthread-2.17.so
	//	e90f13d2c5b8c878ee56fb1bf00004be  lib/libgcc_s.so
	while(infile.good())
	{
		// get the line text string
		std::getline(infile, linebuff);

		// skip blank lines
		std::string trimmed( trim_left(linebuff)) ;
		trimmed = trim_right(trimmed) ;
		if (trimmed.empty())
			continue ;

		Tokeniser token(trimmed);
		std::vector<std::string> tokens(token.getTokens()) ;
		if (tokens.size() == 2)
		{
			mData[tokens[1]] = tokens[0] ;
		}

	}
}

//-------------------------------------------------------------------------------------------------------------
Md5List::~Md5List()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Md5List::operator ==(const Md5List& rhs) const
{
	// if either has no data then stop
	if (mData.empty())
		return false ;
	if (rhs.mData.empty())
		return false ;

	// easiest check is to see if sizes are the same
	if (mData.size() != rhs.mData.size())
		return false ;

	// work through the list checking that they both have the same entries and the entries have the same MD5 sum
	for (auto lhEntry : mData)
	{
		auto rhEntry(rhs.mData.find(lhEntry.first)) ;
		if (rhEntry == rhs.mData.end())
			return false ;

		// compare MD5 sum
		if (lhEntry.second != rhEntry->second)
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Md5List::operator !=(const Md5List& rhs) const
{
	return ! operator==(rhs) ;
}
