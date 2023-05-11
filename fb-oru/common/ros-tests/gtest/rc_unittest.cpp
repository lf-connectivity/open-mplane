/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      rc_unittest.cpp
 * \brief     ROS rc init script tests
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include <unistd.h>

#include "gtest/gtest.h"

#include "Socket.h"
#include "SocketHandler.h"
#include "SocketServer.h"
#include "Path.h"
#include "stringfunc.hpp"

using namespace Mplane ;

const std::string GTEST_DIR{"../../../ros-tests/gtest"} ;
const std::string TEST_FILES_DIR{GTEST_DIR + "/test-files"} ;

#ifdef ROS_TOP
const std::string ROS_TOPDIR(ROS_TOP) ;
#else
const std::string ROS_TOPDIR("") ;
#endif

const std::string ROS_ETCDIR(ROS_TOPDIR + "/board-files/common/rootfs/etc:") ;

//===================================================================================================================
class MockAppSocketHandler : public SocketHandler {
public:
	MockAppSocketHandler(bool stable) :
		SocketHandler(),
		mHandling(false),
		mStable(stable)
	{}
	virtual ~MockAppSocketHandler() {}

protected:
    virtual int handler()
    {
        mHandling = true;
		*this << "\n->" ;

        while (mHandling)
        {
            try
            {
            	std::string buff ;
            	*this >> buff ;
            	if (buff.empty())
            		continue ;

            	*this << buff ;

            	if (buff.find("quit") != std::string::npos)
            	{
                    this->close();
                    mHandling = false;
                    return 0 ;
            	}

            	if (buff.find(".system.getState") != std::string::npos)
            	{
            		if (mStable)
            			*this << "STATUS=OK appState=STABLE" ;
            		else
            			*this << "STATUS=OK appState=FAILED" ;
            	}

        		*this << "\n->" ;
            }
            catch (SocketException& e)
            {
                logDebugNormal("Client closed connection (exception: %s)", e.description().c_str()) ;
                this->close();
                mHandling = false;
            }
        }
    	return 0 ;
    }

    bool mHandling ;
    bool mStable ;
};



class MockApp : public SocketServer {
public:
	MockApp(bool stable) :
		SocketServer(49500, 1, 0),
		mHandler(std::make_shared<MockAppSocketHandler>(stable))
	{
		addSocketHandlers( mHandler ) ;
		int rc = start() ;
		std::cerr << "Started MockApp rc=" << rc << std::endl ;
	}

	virtual ~MockApp()
	{
	}

	std::shared_ptr<MockAppSocketHandler> mHandler ;
};

//===================================================================================================================
class RosTest : public ::testing::Test
{
public:
	static void SetUpTestCase()
	{
		// Set PATH to point to the gtest dir and here (for any mock executables built)
		std::string PATH(::getenv("PATH")) ;
		char buff[1024] ;
		std::string cwd(::getcwd(buff, sizeof(buff))) ;
		PATH = cwd + "/" + GTEST_DIR + ":" +
			   ROS_ETCDIR +
			   cwd + ":" +
			   PATH ;
		setenv("PATH", PATH.c_str(), 1);

		std::cerr << "PATH=" << PATH << std::endl ;
	}

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
    	const ::testing::TestInfo* const test_info =
    	  ::testing::UnitTest::GetInstance()->current_test_info();

    	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    	std::cout << test_info->name() << " - START" <<  std::endl;

    	setupTestFiles() ;

    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }


    virtual void setupTestFiles()
    {
		// Create a user-specific temp directory in which to run tests
		std::string user(::getenv("USER")) ;
		if (user.empty())
			user = "test" ;
		mTempDir = std::string("/tmp/ros-test/") + user ;
		Path::mkpath(mTempDir) ;

		// Create a clean set of test files
		createTestFiles("pkg-images", TEST_FILES_DIR, mTempDir) ;
		createTestFiles("lib-images", TEST_FILES_DIR, mTempDir) ;
		createTestFiles("app-images", TEST_FILES_DIR, mTempDir) ;
    }

    virtual void createTestFiles(const std::string& subdir, const std::string& srcdir, const std::string& dstdir)
    {
    	std::string srcpath(srcdir + "/" + subdir) ;
    	std::string dstpath(dstdir + "/" + subdir) ;
//		std::cerr << srcpath << " => " << dstpath << std::endl ;

    	Path::mkpath(dstpath) ;
    	Path::removeDirContents(dstpath, true) ;

    	std::vector<std::string> contents(Path::dirContents(srcpath)) ;
    	for (auto file : contents)
    	{
    		std::string base(Path::basename(file)) ;
//    		std::cerr << " * " << file << " = " << base << std::endl ;

    		if (base == "links.txt")
    		{
//    			std::cerr << "Process links files..." << std::endl ;
    			processLinks(file, srcpath, dstpath) ;
    			continue ;
    		}

    		// Copy
    		EXPECT_TRUE(Path::fileCopy(file, dstpath + "/" + base)) ;
    	}
    }

    virtual void processLinks(const std::string& linksFilename, const std::string& srcdir, const std::string& dstdir)
    {
    	std::ifstream infile;
		infile.open(linksFilename.c_str());
    	if (!infile.is_open())
    		return ;

    	std::string linebuff ;
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);

			// Skip comments (#) and look for lines of the form:
			// link > file

			std::string::size_type pos = linebuff.find("#") ;
			if (pos != std::string::npos)
				linebuff.erase(pos, std::string::npos) ;
			if (linebuff.length() == 0)
				continue ;

			pos = linebuff.find(">") ;
			if (pos == std::string::npos)
				continue ;

			std::string link(removeSpaces(linebuff.substr(0, pos))) ;
			std::string file(removeSpaces(linebuff.substr(pos+1))) ;

//			std::cerr << "LINK: " << dstdir + "/" + link << " -> " << dstdir + "/" + file << std::endl ;
			EXPECT_TRUE(Path::createLink(dstdir + "/" + link, dstdir + "/" + file)) ;

		}

		infile.close() ;
    }

    virtual std::string readFile(const std::string& filename)
    {
    	std::ifstream infile;
		infile.open(filename.c_str());
    	if (!infile.is_open())
    		return "" ;

    	std::string results ;

    	std::string linebuff ;
		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);

			results += linebuff + "\n" ;
		}

		infile.close() ;
		return results ;
    }

public:
    std::string mTempDir ;


};




//===================================================================================================================
/*
 * Unit tests
 *
 *  \verify{\req{061}}
 *  \verify{\req{062}}
 *  \verify{\req{063}}
 *  \verify{\req{064}}
 *  \verify{\req{065}}
 */

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, Current2Previous)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_TRUE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, Current2NoPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	// Remove previous links
	Path::remove(mTempDir + "/app-images/previous") ;
	Path::remove(mTempDir + "/lib-images/previous") ;


	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, Current2NoAppPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	// Remove previous links
	Path::remove(mTempDir + "/app-images/previous") ;
//	Path::remove(mTempDir + "/lib-images/previous") ;


	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, Current2NoLibPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	// Remove previous links
//	Path::remove(mTempDir + "/app-images/previous") ;
	Path::remove(mTempDir + "/lib-images/previous") ;


	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_TRUE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, NoCurrentNoPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	// Remove current links
	Path::remove(mTempDir + "/app-images/current") ;
	Path::remove(mTempDir + "/lib-images/current") ;

	// Remove previous links
	Path::remove(mTempDir + "/app-images/previous") ;
	Path::remove(mTempDir + "/lib-images/previous") ;


	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, NoCurrentPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	// Not really likely that we'd get this combination, but check it to be complete

	// Remove current links
	Path::remove(mTempDir + "/app-images/current") ;
	Path::remove(mTempDir + "/lib-images/current") ;

	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Pretend to retry - try 1
	std::string runRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " runRetry >" + scriptOut + " 2>&1") ;
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_TRUE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 2
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 3
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);

	// Pretend to retry - try 4
	system( runRetry.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "SCRIPT OUT: " << result << std::endl ;
	EXPECT_FALSE(result.find("current") != std::string::npos);
	EXPECT_FALSE(result.find("previous") != std::string::npos);


	std::cerr << "Done" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, AppStable)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	// Try to get the stable point with no app
	std::string appStable(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " appStable 5 >" + scriptOut + " 2>&1") ;

	std::cerr << "Test 5sec timeout" << std::endl ;
	system( appStable.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("TIMEOUT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);

	// Create a "working" app
	{
		MockApp app(true) ;

		std::cerr << "Test STABLE" << std::endl ;

		system( appStable.c_str() ) ;
		result = readFile(scriptOut) ;
		std::cerr << "RESULT: " << result << std::endl ;
		EXPECT_FALSE(result.find("TIMEOUT") != std::string::npos);
		EXPECT_TRUE(result.find("STABLE") != std::string::npos);
	}

	// Create a "failing" app
	{
		MockApp app(false) ;

		std::cerr << "Test FAILED" << std::endl ;

		system( appStable.c_str() ) ;
		result = readFile(scriptOut) ;
		std::cerr << "RESULT: " << result << std::endl ;
		EXPECT_TRUE(result.find("TIMEOUT") != std::string::npos);
		EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	}


}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, RollbackAll)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	std::string rebootFlag("./reboot-flag.txt") ;
	Path::remove(rebootFlag) ;

	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	unsigned timeout(5) ;
	std::string timeoutStr(std::to_string(timeout)) ;
	std::string stableOrReboot(
		GTEST_DIR + "/testfunc.sh " +
		mTempDir + " " +
		mTempDir +
		" stableOrReboot " + timeoutStr +
		" >" + scriptOut + " 2>&1"
	) ;

	// try 1 (current) - will fail
	std::cerr << "running current" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 2 (current) - will fail
	std::cerr << "running current - Retry 1" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 3 (previous) - will fail
	std::cerr << "running current - Retry 2" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 4 - will fail
	std::cerr << "running previous" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_FALSE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_TRUE(result.find("FAILED") != std::string::npos);
//	EXPECT_FALSE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, RollbackToPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	std::string rebootFlag("./reboot-flag.txt") ;
	Path::remove(rebootFlag) ;

	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	unsigned timeout(5) ;
	std::string timeoutStr(std::to_string(timeout)) ;
	std::string stableOrReboot(
		GTEST_DIR + "/testfunc.sh " +
		mTempDir + " " +
		mTempDir +
		" stableOrReboot " + timeoutStr +
		" >" + scriptOut + " 2>&1"
	) ;

	// try 1 (current) - will fail
	std::cerr << "running current" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 2 (current) - will fail
	std::cerr << "running current - Retry 1" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 3 (previous) - will fail
	std::cerr << "running current - Retry 2" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	{
	// Create a "working" app
	MockApp app(true) ;

	// try 4 - will pass
	std::cerr << "running previous" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_FALSE(result.find("REBOOT") != std::string::npos);
	EXPECT_TRUE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_FALSE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;
	}

	// Re-run checks to see that the retry counter has been cleared
	std::cerr << "** Start again **" << std::endl ;
	setupTestFiles() ;

	// try 1 (current) - will fail
	std::cerr << "running current" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 2 (current) - will fail
	std::cerr << "running current - Retry 1" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 3 (previous) - will fail
	std::cerr << "running current - Retry 2" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 4 - will fail
	std::cerr << "running previous" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_FALSE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_TRUE(result.find("FAILED") != std::string::npos);
//	EXPECT_FALSE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

}


//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, RollbackToPreviousRunPrevious)
{
	// skip if not testing with radio ros
	if (!Path::isDir(ROS_ETCDIR))
		return ;

	std::string rebootFlag("./reboot-flag.txt") ;
	Path::remove(rebootFlag) ;

	std::string clearRetry(GTEST_DIR + "/testfunc.sh " + mTempDir + " " + mTempDir + " clearRetry") ;
	system( clearRetry.c_str() ) ;

	std::string scriptOut(mTempDir + "/script.out") ;
	std::string result ;

	unsigned timeout(5) ;
	std::string timeoutStr(std::to_string(timeout)) ;
	std::string stableOrReboot(
		GTEST_DIR + "/testfunc.sh " +
		mTempDir + " " +
		mTempDir +
		" stableOrReboot " + timeoutStr +
		" >" + scriptOut + " 2>&1"
	) ;

	// try 1 (current) - will fail
	std::cerr << "running current" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 2 (current) - will fail
	std::cerr << "running current - Retry 1" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 3 (previous) - will fail
	std::cerr << "running current - Retry 2" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	{
	// Create a "working" app
	MockApp app(true) ;

	// try 4 - will pass
	std::cerr << "running previous" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_FALSE(result.find("REBOOT") != std::string::npos);
	EXPECT_TRUE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_FALSE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;
	}

	// If we don't restore the files then we now have:
	//   current=old previous
	//   previous=
	//
	// So we can do the retries, but will immediately fail when we get to try the previous
	//
	std::cerr << "** Re-run with failing current **" << std::endl ;

	// try 1 (current) - will fail
	std::cerr << "running current" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 2 (current) - will fail
	std::cerr << "running current - Retry 1" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_TRUE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_FALSE(result.find("FAILED") != std::string::npos);
//	EXPECT_TRUE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

	// try 3 (previous) - will fail
	std::cerr << "running current - Retry 2" << std::endl ;
	system( stableOrReboot.c_str() ) ;
	result = readFile(scriptOut) ;
	std::cerr << "RESULT: " << result << std::endl ;
	EXPECT_FALSE(result.find("REBOOT") != std::string::npos);
	EXPECT_FALSE(result.find("STABLE") != std::string::npos);
	EXPECT_TRUE(result.find("FAILED") != std::string::npos);
//	EXPECT_FALSE(Path::exists(rebootFlag)) ;
//	Path::remove(rebootFlag) ;

}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(RosTest, ros)
{
	std::cerr << "ROS_TOP=" << ROS_TOPDIR << std::endl ;
}



//===================================================================================================================
