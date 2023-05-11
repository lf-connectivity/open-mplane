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
#include "gtest/gtest.h"

#include <string>
#include <iostream>

#include "ITif.h"
#include "IRtiMsgParser.h"
#include "TestInterfaceBase.h"
#include "TestInterfaceFactory.h"
#include "Model/TestingTestInterface.h"
#include "Model/TestInjected.h"

using namespace Mplane ;


//===================================================================================================================
namespace Mplane {


class TestAti : public virtual ITifControl
{

public:
	TestAti(unsigned NumConnections = 3) :
		mTif()
	{
		for (unsigned idx=0; idx < NumConnections; ++idx)
		{
			std::shared_ptr<TestInterfaceBase> tif( std::make_shared<TestingTestInterface>() ) ;
			mTif.push_back( std::dynamic_pointer_cast<ITif>(tif) ) ;
		}
	}

	~TestAti() {}


	std::shared_ptr<ITif> getTif()
	{
		return mTif[0] ;
	}


	/**
	 * Singleton creation
	 */
	static std::shared_ptr<TestAti> createInstance(unsigned NumConnections = 3)
	{
		static std::shared_ptr<TestAti> instance(std::make_shared<TestAti>(NumConnections)) ;
		return instance ;
	}

	/**
	 * Singleton
	 */
	static std::shared_ptr<TestAti> getTestAti()
	{
		return createInstance();
	}
	static std::shared_ptr<ITifControl> getInstance()
	{
//		return std::dynamic_pointer_cast<ITifControl>(createInstance());
		std::shared_ptr<ITifControl> instance( std::dynamic_pointer_cast<ITifControl>(createInstance()) );
		return instance ;
	}

	/**
	 * Inject the directory(s) provided by this entity
	 * @return true if ok
	 */
	virtual bool doInject(std::shared_ptr<ITifEntry> entry) override
	{
		for (auto tif : mTif)
		{
			if (!tif->doInject(entry))
				return false ;
		}
		return true ;
	}

	/**
	 * Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doHideDir(const std::string& dir) override
	{
		for (auto tif : mTif)
		{
			if (!tif->doHideDir(dir))
				return false ;
		}
		return true ;
	}


	/**
	 * Un-Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doUnhideDir(const std::string& dir) override
	{
		for (auto tif : mTif)
		{
			if (!tif->doUnhideDir(dir))
				return false ;
		}
		return true ;
	}

	bool doRename(const std::string& dir, const std::string& newName)
	{
		for (auto tif : mTif)
		{
			if (!tif->doRename(dir, newName))
				return false ;
		}
		return true ;
	}

protected:
    std::vector< std::shared_ptr<ITif> > mTif ;
};

}


class ITifTests : public ::testing::Test
{
public:
	virtual ~ITifTests() {}

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
    virtual void TearDown() {}


    std::string runCmd(const std::string& cmd)
    {
    	std::shared_ptr<TestAti> ati(TestAti::getTestAti()) ;
    	std::shared_ptr<ITif> tif(ati->getTif()) ;
    	std::shared_ptr<IRtiMsgParser> handler(std::dynamic_pointer_cast<IRtiMsgParser>(tif)) ;

    	return handler->parse(cmd) ;
    }

    std::string runCmdOk(const std::string& cmd)
    {
    	std::string result = runCmd(cmd) ;
    	std::cout << "CMD: " << cmd << std::endl << "REPLY: '" << result << "'" << std::endl ;
    	EXPECT_TRUE( result.find("Error") == std::string::npos ) << "Unexpected command error" ;
    	EXPECT_TRUE( result.find("error") == std::string::npos ) << "Unexpected command error" ;
    	EXPECT_TRUE( result.find("Status=ERROR") == std::string::npos ) << "Unexpected command error" ;
    	EXPECT_TRUE( result.find("Status=OK") != std::string::npos ) << "Unexpected command error" ;

    	return result ;
    }

    std::string runCmdError(const std::string& cmd)
    {
    	std::string result = runCmd(cmd) ;
    	std::cout << "CMD: " << cmd << std::endl << "REPLY: " << result << std::endl ;
    //	EXPECT_TRUE( result.find("Error") != std::string::npos ) << "Expected command error but found none" ;
    	EXPECT_TRUE( result.find("Status=OK") == std::string::npos ) << "Expected command error but found none" ;
    	EXPECT_TRUE( result.find("Status=ERROR") != std::string::npos ) << "Expected command error but found none" ;

    	return result ;
    }

};


//=============================================================================================================
// ITifControl
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITifControl> ITifControl::getInstance()
{
//	return TestAti::getInstance() ;
	std::shared_ptr<ITifControl> instance( TestAti::getInstance() ) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::inject(std::shared_ptr<ITifEntry> entry)
{
//	return ITifControl::getInstance()->inject(entry) ;
	std::shared_ptr<ITifControl> instance( ITifControl::getInstance() ) ;
	return instance->doInject(entry) ;
}

//-------------------------------------------------------------------------------------------------------------
bool ITifControl::hideDir(const std::string& dir, bool hide)
{
	return ITifControl::getInstance()->doHideDir(dir) ;
}


//===================================================================================================================
/*
 * Unit tests
 */


//-------------------------------------------------------------------------------------------------------------------
TEST_F(ITifTests, Create)
{
	std::string result ;

	result = runCmdOk("ls /") ;
	EXPECT_TRUE(result.find("tif:scripts/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:settings/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:testing/") != std::string::npos) ;

	for (auto cmd : std::vector<std::string>{
		"ls /",
		"ls /tif:testing",
	})
	{
		result = runCmd(cmd) ;
		std::cerr << "->" << cmd << "\n" << result << std::endl ;
	}

	result = runCmdOk("ls /") ;
	EXPECT_FALSE(result.find("dpd/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:scripts/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:settings/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:testing/") != std::string::npos) ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST_F(ITifTests, Inject)
{
	std::string result ;

	result = runCmdOk("ls /") ;
	EXPECT_FALSE(result.find("dpd/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:scripts/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:settings/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:testing/") != std::string::npos) ;

	// Emulate a feature creating an injection object and injecting it
	std::shared_ptr<ITifEntry> newTif(std::make_shared<TestInjected>()) ;
	EXPECT_TRUE(ITifControl::inject(newTif)) ;

	// show results now

	for (auto cmd : std::vector<std::string>{
		"ls /",
		"ls /tif:testing",
		"ls /dpd",
	})
	{
		result = runCmd(cmd) ;
		std::cerr << "->" << cmd << "\n" << result << std::endl ;
	}

	result = runCmdOk("ls /") ;
	EXPECT_TRUE(result.find("dpd/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:scripts/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:settings/") != std::string::npos) ;
	EXPECT_TRUE(result.find("tif:testing/") != std::string::npos) ;

	result = runCmdOk("ls /dpd") ;
	EXPECT_TRUE(result.find("abort([INT tx])") != std::string::npos) ;
}


//===================================================================================================================
