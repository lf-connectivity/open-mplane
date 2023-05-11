/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppOptions_unittest.cpp
 * \brief     Google Test of AppOptions
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the AppOptions class.
 *
 */

#include <gtest/gtest.h>

#include <cstdlib>
#include <string>
#include <iostream>

#include <memory>
#include "IAppOptions.h"
#include "IBootEnv.h"
#include "AppOptions.h"

using namespace Mplane;

using namespace std;

class TestAppOptions : public AppOptions
{
public:
	TestAppOptions(int argc, const char** argv,
			const std::string& applicationDescription,
			const std::vector< std::shared_ptr<IAppOptionSpec> >& optionsSpecification) :
		AppOptions(argc, argv, applicationDescription, optionsSpecification)
	{}

	virtual ~TestAppOptions() {}

};



//-------------------------------------------------------------------------------------------------------------
TEST(AppOptions, Env)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


	::setenv("SVAL",  "Env sval", 1) ;
//	::setenv("SVAL2", "Env sval2", 1) ;
	::setenv("SVAL3", "Env sval3", 1) ;
	::setenv("SVAL5", "Env sval5", 1) ;
	::setenv("IVAL",  "1111", 1) ;
//	::setenv("IVAL2", "2222", 1) ;
	::setenv("IVAL3", "3333", 1) ;
	::setenv("FVAL",  "1111.1", 1) ;
//	::setenv("FVAL2", "2222.2", 1) ;
	::setenv("FVAL3", "3333.3", 1) ;

	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	bootEnv->reset() ;
	bootEnv->setVar("SVAL4", "U-BOOT Env sval4");
	bootEnv->setVar("SVAL5", "U-BOOT Env sval5");


	const char *argv[] = { (char*)"prog",
			(char*)"--bval",
			(char*)"--sval",  (char*)"anarg",
			(char*)"--ival",  (char*)"8",
			(char*)"--fval",  (char*)"88.9"
	} ;
	std::shared_ptr<IAppOptions> opts1(IAppOptions::createInstance(sizeof(argv) / sizeof(char*), argv, "A simple program",
		std::vector<std::shared_ptr<IAppOptionSpec> >{
			// default & env - command line set
			IAppOptionSpec::factory("bval", DataVariantType::Bool, "An example bool option"),
			IAppOptionSpec::factory("sval", DataVariantType::String, "An example string option", "default string", "SVAL"),
			IAppOptionSpec::factory("ival", DataVariantType::Int, "An example int option", "123", "IVAL"),
			IAppOptionSpec::factory("fval", DataVariantType::Float, "An example float option", "56.78", "FVAL"),

			// default & env - default set
			IAppOptionSpec::factory("bval2", DataVariantType::Bool, "Another example bool option", "true"),
			IAppOptionSpec::factory("sval2", DataVariantType::String, "Another example string option", "some string", "SVAL2"),
			IAppOptionSpec::factory("ival2", DataVariantType::Int, "Another example int option", "890", "IVAL2"),
			IAppOptionSpec::factory("fval2", DataVariantType::Float, "Another example float option", "44.44", "FVAL2"),

			// default & env - env set
			IAppOptionSpec::factory("bval3", DataVariantType::Bool, "Another example bool option"),
			IAppOptionSpec::factory("sval3", DataVariantType::String, "Another example string option", "some string 3", "SVAL3"),
			IAppOptionSpec::factory("ival3", DataVariantType::Int, "Another example int option", "", "IVAL3"),
			IAppOptionSpec::factory("fval3", DataVariantType::Float, "Another example float option", "", "FVAL3"),

			// default & env - u-boot env set
			IAppOptionSpec::factory("sval4", DataVariantType::String, "Another example string option 4", "some string 4", "SVAL4"),
			IAppOptionSpec::factory("sval5", DataVariantType::String, "Another example string option 5", "some string 5", "SVAL5"),
		}
	)) ;

	EXPECT_TRUE(opts1->getOption("bval").isSet()) ;
	EXPECT_TRUE(opts1->getOption("bval").toBool()) ;
	EXPECT_TRUE(opts1->getOption("bval2").isSet()) ;
	EXPECT_TRUE(opts1->getOption("bval2").toBool()) ;
	EXPECT_TRUE(opts1->getOption("bval3").isSet()) ;
	EXPECT_FALSE(opts1->getOption("bval3").toBool()) ;

	std::shared_ptr<IAppOptions> opts2(IAppOptions::getInstance()) ;

	EXPECT_TRUE(opts2->getOption("bval").isSet()) ;
	EXPECT_TRUE(opts2->getOption("bval").toBool()) ;
	EXPECT_TRUE(opts2->getOption("bval2").isSet()) ;
	EXPECT_TRUE(opts2->getOption("bval2").toBool()) ;
	EXPECT_TRUE(opts2->getOption("bval3").isSet()) ;
	EXPECT_FALSE(opts2->getOption("bval3").toBool()) ;

	EXPECT_TRUE(opts2->getOption("sval").isSet()) ;
	EXPECT_EQ("anarg", opts2->getOption("sval").toString()) ;
	EXPECT_TRUE(opts2->getOption("sval2").isSet()) ;
	EXPECT_EQ("some string", opts2->getOption("sval2").toString()) ;
	EXPECT_TRUE(opts2->getOption("sval3").isSet()) ;
	EXPECT_EQ("Env sval3", opts2->getOption("sval3").toString()) ;
	EXPECT_TRUE(opts2->getOption("sval4").isSet()) ;
	EXPECT_EQ("U-BOOT Env sval4", opts2->getOption("sval4").toString()) ;
	EXPECT_TRUE(opts2->getOption("sval5").isSet()) ;
	EXPECT_EQ("U-BOOT Env sval5", opts2->getOption("sval5").toString()) ;

	EXPECT_TRUE(opts2->getOption("ival").isSet()) ;
	EXPECT_EQ(8, opts2->getOption("ival").toInt()) ;
	EXPECT_TRUE(opts2->getOption("ival2").isSet()) ;
	EXPECT_EQ(890, opts2->getOption("ival2").toInt()) ;
	EXPECT_TRUE(opts2->getOption("ival3").isSet()) ;
	EXPECT_EQ(3333, opts2->getOption("ival3").toInt()) ;

	EXPECT_TRUE(opts2->getOption("fval").isSet()) ;
	EXPECT_NEAR(88.9, opts2->getOption("fval").toFloat(), 0.05) ;
	EXPECT_TRUE(opts2->getOption("fval2").isSet()) ;
	EXPECT_NEAR(44.4, opts2->getOption("fval2").toFloat(), 0.05) ;
	EXPECT_TRUE(opts2->getOption("fval3").isSet()) ;
	EXPECT_NEAR(3333.3, opts2->getOption("fval3").toFloat(), 0.05) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(AppOptions, Help)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	const char *argv[] = { (char*)"prog",
			(char*)"--bval",
			(char*)"--sval",  (char*)"anarg",
			(char*)"--ival",  (char*)"8",
			(char*)"--fval",  (char*)"88.9",
			(char*)"-help"
	} ;
	std::shared_ptr<IAppOptions> opts1(new TestAppOptions(sizeof(argv) / sizeof(char*), argv, "A simple program",
		std::vector<std::shared_ptr<IAppOptionSpec> >{
			// default & env - command line set
			IAppOptionSpec::factory("bval", DataVariantType::Bool, "An example bool option"),
			IAppOptionSpec::factory("sval", DataVariantType::String, "An example string option", "default string", "SVAL"),
			IAppOptionSpec::factory("ival", DataVariantType::Int, "An example int option", "123", "IVAL"),
			IAppOptionSpec::factory("fval", DataVariantType::Float, "An example float option", "56.78", "FVAL"),

			// default & env - default set
			IAppOptionSpec::factory("bval2", DataVariantType::Bool, "Another example bool option", "true"),
			IAppOptionSpec::factory("sval2", DataVariantType::String, "Another example string option", "some string", "SVAL2"),
			IAppOptionSpec::factory("ival2", DataVariantType::Int, "Another example int option", "890", "IVAL2"),
			IAppOptionSpec::factory("fval2", DataVariantType::Float, "Another example float option", "44.44", "FVAL2"),

			// default & env - env set
			IAppOptionSpec::factory("bval3", DataVariantType::Bool, "Another example bool option"),
			IAppOptionSpec::factory("sval3", DataVariantType::String, "Another example string option", "some string 3", "SVAL3"),
			IAppOptionSpec::factory("ival3", DataVariantType::Int, "Another example int option", "", "IVAL3"),
			IAppOptionSpec::factory("fval3", DataVariantType::Float, "Another example float option", "", "FVAL3"),
		}
	)) ;

}
