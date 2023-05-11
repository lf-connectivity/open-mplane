/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigParser_unittest.cpp
 * \brief     YANG configuration parser unit tests
 *
 *
 * \details   YANG configuration parser unit tests
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IConfigCoordinator.h"
#include "IYangConfigParser.h"
#include "YangConfigParser.h"
#include "YangConfigDownload.h"

using namespace Mplane;

class TestYangConfigParser : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
    	Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}
protected:

private:
};

TEST_F(TestYangConfigParser, InitialFileTest)
{
	std::shared_ptr<IConfigDownload> mYangConfigDownload( std::make_shared<YangConfigDownload>() );
	std::shared_ptr<YangConfigParser> mYangConfigParser(std::make_shared<YangConfigParser>());

    // Get the instance of configuration coordinator
    std::shared_ptr<IConfigCoordinator> configCoord = IConfigCoordinator::singleton();

    // Register the Yang config download and Yang config parser with the coordinator
    configCoord->registerConfig(mYangConfigDownload, mYangConfigParser);

    // Tell config download manager to change the root install directory.
    std::string failReason ;
    mYangConfigDownload->testInjectInstallDir("../../../ConfigParser/gtest/config", failReason) ;
    mYangConfigDownload->setInstallFileName("YangConfig.xml",failReason);

    // Load the configuration file
	ReturnType::State returnType = configCoord->load(mYangConfigDownload->getName());

	// Check the return type of the load to make sure it is successful
	if( returnType == ReturnType::RT_OK )
	{
		std::string yangVersion;
		mYangConfigParser->getYangVersion(yangVersion);
		ASSERT_TRUE("1.1" == yangVersion);

		std::string oranVersion;
		mYangConfigParser->getOranVersion(oranVersion);
		ASSERT_TRUE("2.0.0" == oranVersion);

		std::string product;
		mYangConfigParser->getProduct(product);
		ASSERT_TRUE("FBC-ORAN-Radio" == product);

		std::string varient;
		mYangConfigParser->getVarient(varient);
		ASSERT_TRUE("0.4" == varient);

		std::string formatVersion;
		mYangConfigParser->getFormatVersion(formatVersion);
		ASSERT_TRUE("1.0" == formatVersion);

		std::string company;
		mYangConfigParser->getCompany(company);
		ASSERT_TRUE("Mplane" == company);
	}
}
