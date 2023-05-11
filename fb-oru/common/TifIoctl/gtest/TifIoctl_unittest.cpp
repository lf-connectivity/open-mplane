/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TifIoctl_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include <memory>
#include "TifIoctl.hpp"

namespace Mplane {

class TifIoctlChild : public TifIoctl<TifIoctlChild> {
public:
	TifIoctlChild() :
		TifIoctl<TifIoctlChild>(*this)
	{
		registerCommand("simpleCmd", "", "", &TifIoctlChild::simpleCmd) ;
		registerCommand("simpleFailCmd", "", "", &TifIoctlChild::simpleFailCmd) ;
		registerCommand("oneArgCmd", "INT arg", "INT ret", &TifIoctlChild::oneArgCmd) ;
	}

	~TifIoctlChild() {}

	bool simpleCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;
		return true ;
	}

	bool simpleFailCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;
		return false ;
	}

	bool oneArgCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;

		int ival = callerArgs->find("arg")->toInt() ;
		returnArgs->find("ret")->set(ival * 2) ;

		return true ;
	}

};



class TifIoctlTest : public TifIoctl<TifIoctlTest> {
public:
	TifIoctlTest() :
		TifIoctl<TifIoctlTest>(*this),
		mChild(new TifIoctlChild)
	{
		registerCommand("simpleCmd", "", "", &TifIoctlTest::simpleCmd) ;
		registerCommand("simpleFailCmd", "", "", &TifIoctlTest::simpleFailCmd) ;
		registerCommand("oneArgCmd", "INT arg", "INT ret", &TifIoctlTest::oneArgCmd) ;

		registerObject("child", std::dynamic_pointer_cast<ITifIoctl>(mChild) ) ;
	}

	~TifIoctlTest() {}

	bool simpleCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;
		return true ;
	}

	bool simpleFailCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;
		return false ;
	}

	bool oneArgCmd(DataVariantList* callerArgs, DataVariantList* returnArgs)
	{
		std::cout << __FUNCTION__ << std::endl ;

		int ival = callerArgs->find("arg")->toInt() ;
		returnArgs->find("ret")->set(ival * 2) ;

		return true ;
	}

	std::shared_ptr<TifIoctlChild>	mChild ;

};

}


using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, Basic)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;
}

//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, NoCmd)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;
    DataVariantList* callerDv = new DataVariantList() ;
    DataVariantList* returnDv = new DataVariantList() ;

    // should throw an exception
    bool except = false ;
    try {
        EXPECT_FALSE( test.executeCommand("noCommand", callerDv, returnDv) ) ;
    }
    catch(...)
    {
    	except = true ;
    }

    EXPECT_TRUE( except ) ;

    delete callerDv ;
    delete returnDv ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, NoObject)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;

    // should throw an exception
    bool except = false ;
    try {
    	std::shared_ptr<ITifIoctl> obj = test.getObject("noObject") ;
    }
    catch(...)
    {
    	except = true ;
    }

    EXPECT_TRUE( except ) ;

}



//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, SimpleExec)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;

    // standard call
    DataVariantList* callerDv = new DataVariantList() ;
    DataVariantList* returnDv = new DataVariantList() ;

    EXPECT_TRUE( test.executeCommand("simpleCmd", callerDv, returnDv) ) ;
    EXPECT_FALSE( test.executeCommand("simpleFailCmd", callerDv, returnDv) ) ;


    // Call with args mismatch
    DataVariantList* callerDv2 = new DataVariantList("INT arg") ;
    DataVariantList* returnDv2 = new DataVariantList("INT ret") ;

    // should NOT throw an exception - providing more call args than needed
    bool except = false ;
    try {
    	test.executeCommand("simpleCmd", callerDv2, returnDv) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_FALSE( except ) ;

    // should throw - command cannot set all the expected return args
    except = false ;
    try {
    	test.executeCommand("simpleCmd", callerDv, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;

    // should throw - command cannot set all the expected return args
    except = false ;
    try {
    	test.executeCommand("simpleCmd", callerDv2, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;


    delete callerDv ;
    delete returnDv ;

    delete callerDv2 ;
    delete returnDv2 ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, OneArgExec)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;

    DataVariantList* callerDv = new DataVariantList("INT arg") ;
    DataVariantList* returnDv = new DataVariantList("INT ret") ;

    DataVariantList* callerDv2 = new DataVariantList() ;
    DataVariantList* returnDv2 = new DataVariantList() ;

    callerDv->find("arg")->set(22) ;
    EXPECT_TRUE( test.executeCommand("oneArgCmd", callerDv, returnDv) ) ;

    EXPECT_EQ(44, returnDv->find("ret")->toInt()) ;

    // should throw an exception - call args
    bool except = false ;
    try {
    	test.executeCommand("oneArgCmd", callerDv2, returnDv) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;

    // should not - return args will be amended
    except = false ;
    try {
    	test.executeCommand("oneArgCmd", callerDv, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_FALSE( except ) ;

    // should throw an exception - call args
    except = false ;
    try {
    	test.executeCommand("oneArgCmd", callerDv2, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;


    delete callerDv ;
    delete returnDv ;

    delete callerDv2 ;
    delete returnDv2 ;
}


//-------------------------------------------------------------------------------------------------------------------
TEST(TifIoctl, Object)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;


    TifIoctlTest test ;
    std::shared_ptr<ITifIoctl> child = test.getObject("child") ;

    DataVariantList* callerDv = new DataVariantList("INT arg") ;
    DataVariantList* returnDv = new DataVariantList("INT ret") ;

    DataVariantList* callerDv2 = new DataVariantList() ;
    DataVariantList* returnDv2 = new DataVariantList() ;

    callerDv->find("arg")->set(22) ;
    EXPECT_TRUE( child->executeCommand("oneArgCmd", callerDv, returnDv) ) ;

    EXPECT_EQ(44, returnDv->find("ret")->toInt()) ;

    // should throw an exception - call args
    bool except = false ;
    try {
    	child->executeCommand("oneArgCmd", callerDv2, returnDv) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;

    // should not - return args will be amended
    except = false ;
    try {
    	child->executeCommand("oneArgCmd", callerDv, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_FALSE( except ) ;

    // should throw an exception - call args
    except = false ;
    try {
    	child->executeCommand("oneArgCmd", callerDv2, returnDv2) ;
    }
    catch(...)
    {
    	except = true ;
    }
    EXPECT_TRUE( except ) ;


    delete callerDv ;
    delete returnDv ;

    delete callerDv2 ;
    delete returnDv2 ;
}



//===================================================================================================================
