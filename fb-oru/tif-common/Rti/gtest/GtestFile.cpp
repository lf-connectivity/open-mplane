/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      gentool_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "gtest/gtest.h"

#include <regex.h>

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "GtestFile.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void GtestFile::deleteFile(const std::string& filename)
{
	remove(filename.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
bool GtestFile::checkFileExists(const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	bool ok = infile.good() ;
	EXPECT_TRUE( ok ) << filename ;
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool GtestFile::checkFileContents(const std::string& filename, const std::string& expected)
{
	regex_t re ;
//  if (regcomp(&re, expected.c_str(), REG_EXTENDED|REG_NOSUB) != 0)
	if (regcomp(&re, expected.c_str(), REG_NOSUB) != 0)
	{
		ADD_FAILURE() << "Error compiling regexp " << expected ;
		return false ;
	}

	bool found = false ;
	std::ifstream infile(filename.c_str());
	std::string linebuff ;
	if (infile.is_open())
	{
		while(infile.good() && !found)
		{
			// get the line text string
			std::getline(infile, linebuff);

			int status = regexec(&re, linebuff.c_str(), (size_t)0, NULL, 0) ;
			if (status == 0)
			{
				std::cout << "Found '" << linebuff << "' in file " << filename << std::endl ;
				found = true ;
			}
		}
		EXPECT_TRUE(found) << "Unable to find " << expected << " in " << filename ;
	}
	else
	{
		ADD_FAILURE() << "Unable to read file " << filename ;
	}

	regfree(&re) ;
	return found ;
}

//===================================================================================================================

