/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootMgr_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Path.h"
#include "TroubleshootFile.h"
#include "TroubleshootMgr.h"

using namespace Mplane ;

const std::string DIR("./logs") ;

//===================================================================================================================
class TroubleshootMgrTest : public ::testing::Test
{
public:

	/*! @brief Setup the test
	 */
	virtual void SetUp()
	{
		const ::testing::TestInfo* const test_info =
		  ::testing::UnitTest::GetInstance()->current_test_info();

		std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
		std::cout << test_info->name() << " - START" <<  std::endl;

	}

	/*! @brief Tear down the test
	 */
	virtual void TearDown()
	{
	}


	std::string fileSlurp(const std::string& path)
	{
		if (!Path::exists(path))
			return "!!FILE DOES NOT EXIST!!" ;

		std::ifstream inFile(path);
		std::stringstream ss;
		ss << inFile.rdbuf();
		return ss.str() ;
	}

};




//===================================================================================================================
/*
 * Unit tests
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(TroubleshootMgrTest, create)
{
	TroubleshootMgr mgr ;
	EXPECT_EQ("", mgr.error()) ;

	std::vector<std::string> paths(mgr.generateLogs()) ;
	EXPECT_TRUE(paths.empty()) ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(TroubleshootMgrTest, files)
{
	std::shared_ptr<IORanLogFileMgr> mgr(ITroubleshootMgr::singleton()) ;
	mgr->clear() ;

	Path::removeDirContents(DIR) ;

	mgr->setDir(DIR) ;
	mgr->setFileCompression(false) ;

	// add some files
	const unsigned NUMFILES(3) ;
	for (unsigned i=1; i <= NUMFILES; ++i)
	{
		std::shared_ptr<IORanLogFile> file(IORanLogFile::factory("file" + std::to_string(i) + ".log")) ;
		file->registerDataGatherer([i]()->std::string {
			return "Log line for file " + std::to_string(i) ;
		}) ;
		mgr->addFile(file) ;
	}

	std::vector<std::string> contents ;

	contents = Path::dirContents(DIR) ;
	EXPECT_TRUE(contents.empty()) ;

	std::vector<std::string> paths(mgr->generateLogs()) ;
	EXPECT_EQ(NUMFILES, paths.size()) ;
	contents = Path::dirContents(DIR) ;
	EXPECT_EQ(NUMFILES, contents.size()) ;

	for (unsigned i=1; i <= NUMFILES; ++i)
	{
		std::string path(DIR + "/file" + std::to_string(i) + ".log") ;

		// check path
		auto it(std::find(paths.begin(), paths.end(), path)) ;
		EXPECT_TRUE(it != paths.end()) ;

		// check file contents
		std::string contents(fileSlurp(path)) ;
		std::string expected("Log line for file " + std::to_string(i)) ;
		EXPECT_EQ(expected, contents) ;
	}

}



//===================================================================================================================
