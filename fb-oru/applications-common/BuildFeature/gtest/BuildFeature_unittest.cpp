/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BuildFeature_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <gtest/gtest.h>

#include "IApplication.h"
#include "IBuildFeature.h"
#include "BuildFeatureList.h"
#include "BuildFeatureUtils.hpp"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class DummyApp : public virtual IApplication {
public:

	/**
	 * Run the application. When running this class will call a number of hooks to allow
	 * derived objects to add additional behaviour, or override default behaviour
	 * @param argc
	 * @param argv
	 * @param extraOptions - Optionally supply additional options
	 * @return exit code
	 */
	virtual int run(
		const std::string& name,
		int argc, const char** argv,
		const std::vector< std::shared_ptr<IAppOptionSpec> >& extraOptions = {}) override
	{
		return 0 ;
	}

};

//-------------------------------------------------------------------------------------------------------------
class _BuildFeature : public virtual IBuildFeature {
public:
	_BuildFeature() : mInit(false) {}

	virtual ~_BuildFeature() {}

	virtual bool init(IApplication* app) override
	{
		mInit = true ;
		return true ;
	}


	virtual bool appStart() override  {return true;}
	virtual bool appPreOptions(std::vector<std::shared_ptr<IAppOptionSpec> >& options) override  {return true;}
	virtual bool appPreWait() override  {return true;}
	virtual bool appPreInit() override  {return true;}
	virtual bool appPostInit() override {return true;}
	virtual bool appPreRun() override {return true;}
	virtual bool appEnd() override {return true;}

	bool mInit ;
};

//-------------------------------------------------------------------------------------------------------------
class BuildFeatureA : public _BuildFeature {
public:
	BuildFeatureA() : _BuildFeature() {}
	virtual ~BuildFeatureA() {}

//	static std::shared_ptr<IBuildFeature> getInstance() ;
	static std::shared_ptr<IBuildFeature> getInstance()
	{
		static std::shared_ptr<IBuildFeature> instance(std::make_shared<BuildFeatureA>()) ;
		return instance ;
	}

	static int handle ;
};

int BuildFeatureA::handle = BuildFeatureList::getInstance()->registerBuildFeature(
	[]()->std::shared_ptr<IBuildFeature> {
		return BuildFeatureA::getInstance() ;
	}
) ;

//std::shared_ptr<IBuildFeature> BuildFeatureA::getInstance()
//{
//	static std::shared_ptr<IBuildFeature> instance(std::make_shared<BuildFeatureA>()) ;
//	return instance ;
//}



//-------------------------------------------------------------------------------------------------------------
class BuildFeatureB : public _BuildFeature {
public:
	BuildFeatureB() : _BuildFeature() {}
	virtual ~BuildFeatureB() {}

	static std::shared_ptr<IBuildFeature> getInstance()
	{
		return BuildFeatureUtils<BuildFeatureB>::getInstance() ;
	}

	static int handle ;
};

int BuildFeatureB::handle = BuildFeatureUtils<BuildFeatureB>::registerBuildFeature() ;



//-------------------------------------------------------------------------------------------------------------
TEST(BuildFeatures, Init)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	static std::shared_ptr<BuildFeatureList> flist(BuildFeatureList::getInstance()) ;

	EXPECT_EQ(2u, flist->numBuildFeatures()) ;

	std::shared_ptr<BuildFeatureA> featA(std::dynamic_pointer_cast<BuildFeatureA>(BuildFeatureA::getInstance())) ;
	EXPECT_FALSE(featA->mInit) ;
	std::shared_ptr<BuildFeatureB> featB(std::dynamic_pointer_cast<BuildFeatureB>(BuildFeatureB::getInstance())) ;
	EXPECT_FALSE(featB->mInit) ;

	std::shared_ptr<IApplication> app(std::make_shared<DummyApp>()) ;
	flist->initBuildFeatures(app.get()) ;
	EXPECT_TRUE(featA->mInit) ;
	EXPECT_TRUE(featB->mInit) ;

}
