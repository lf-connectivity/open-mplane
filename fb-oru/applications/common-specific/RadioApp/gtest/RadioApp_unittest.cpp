/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Application_unittest.cpp
 * \brief     Google Test of Application
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the Application class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "RadioApp.h"

using namespace Mplane;

using namespace std;


#if 0
//-------------------------------------------------------------------------------------------------------------
class AppPlugin : public virtual IApplicationPlugin {
public:
	AppPlugin() {}
	virtual ~AppPlugin() {}

	// Hooks provided at various stages in the application run process

	virtual int appStart() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

	virtual int appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options) override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}
	virtual int appOptions(int argc, const char** argv,
			const std::string& title,
			std::vector<std::shared_ptr<IAppOptionSpec> >& options) override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

	virtual int appPreWait() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}
	virtual int appWait() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

	virtual int appPreInit() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}
	virtual int appInit() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}
	virtual int appPostInit() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

	virtual int appPreRun() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}
	virtual int appRun() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

	virtual int appEnd() override {
		++mCallCount ;
		mLastCall = __FUNCTION__ ;
		return 0 ;
	}

public:
	unsigned mCallCount{0} ;
	std::string mLastCall{""} ;
};

class Plugin1 : public AppPlugin {
public:
	Plugin1() : AppPlugin() {}
	virtual ~Plugin1() {}
};
class Plugin2 : public AppPlugin {
public:
	Plugin2() : AppPlugin() {}
	virtual ~Plugin2() {}
};

//-------------------------------------------------------------------------------------------------------------
TEST(Application, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IApplication> app(std::make_shared<Application>()) ;
	std::shared_ptr<IApplicationPlugin> p1(std::make_shared<Plugin1>()) ;
	std::shared_ptr<IApplicationPlugin> p2(std::make_shared<Plugin2>()) ;

	app->addPlugin(p1) ;
	app->addPlugin(p2) ;

	int argc(1) ;
	const char* args[] = {"test"} ;
	const char** argv{args} ;

	EXPECT_EQ(0, app->run("A Test", argc, argv)) ;

	EXPECT_EQ(11u, std::dynamic_pointer_cast<AppPlugin>(p1)->mCallCount) ;
	EXPECT_EQ(11u, std::dynamic_pointer_cast<AppPlugin>(p2)->mCallCount) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(Application, Common)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IApplication> app(std::make_shared<Application>()) ;
	std::shared_ptr<IApplicationPlugin> p1(std::make_shared<Plugin1>()) ;
	std::shared_ptr<IApplicationPlugin> p2(std::make_shared<Plugin2>()) ;

	app->addPlugin(p1) ;
	app->addPlugin(p2) ;

}

#endif
