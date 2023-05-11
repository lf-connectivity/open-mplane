/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServicesTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "IRadio.h"

#include "IServicesCtl.h"

#include "TxService.h"
#include "RxService.h"
#include "FaultService.h"
#include "DigitalPowerService.h"

#include "RrhServicesTestCase.h"

#include "OranRrhServices.h"
#include "IAppSettings.h"
#include "IAppSettingsFactory.h"
#include "IAppOptions.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */

using namespace std;


void RrhServicesTestCases::SetUp()
{
}

void RrhServicesTestCases::TearDown()
{
}

void RrhServicesTestCases::unittest()
{
	cout << "RrhServices unit test" << endl;


	// create application options as they are needed by the ART radio implementation
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
	std::cerr << "Starting AxisRrhProcess application for " << appSettings->getBoardString() << " hardware" << std::endl;

	int argc = 0;
	char noarg[] = "";
	const char** argv = (const char**)&noarg;

	// Define expected options and process the command line
	std::shared_ptr<IAppOptions> opts(IAppOptions::createInstance(argc, argv,
		"Advanced Radio Tester",
		std::vector<std::shared_ptr<IAppOptionSpec> >{
			IAppOptionSpec::factory("ethbb",  DataVariantType::String, "Ethernet interface name (over baseband)", "eth_bb", "ETHBB"),
			IAppOptionSpec::factory("ethcdi", DataVariantType::String, "Ethernet interface name (control and debug)", "eth_cdi", "ETHCDI"),
			IAppOptionSpec::factory("ethssdp", DataVariantType::String, "Ethernet interface name (discovery)", "vlanbr", "ETHSSDP"),
		}
	)) ;

	std::shared_ptr<IRadio> radio = IRadioFactory::getInterface();

	radio->initialise();

	std::shared_ptr<IServicesCtl> testCtl( IServicesFactory::create() );

	std::shared_ptr<OranRrhServices> cs = std::dynamic_pointer_cast<OranRrhServices> (testCtl);
(void)cs;

#if 0
	// Find fibre control service
	std::shared_ptr<FibreControlService> fibreControlService ;
	for (auto service : cs->mServices)
	{
		fibreControlService = std::dynamic_pointer_cast<FibreControlService>(service) ;
		if (fibreControlService)
			break ;
	}

	ASSERT_TRUE(fibreControlService.get() != nullptr) ;

	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceCreated );

	testCtl->start();

	usleep( 1300 * 1000 );

	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceRunning );

	testCtl->suspend();

	usleep( 1300 * 1000 );

	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceSuspended );

	testCtl->resume();

	usleep( 250 * 1000 ); // give 'em a little time to resume

    // don't test for resumed, won't see it.
	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceRunning );

	testCtl->reset();

    // don't test for reset state, won't see it.
	usleep( 200 * 1000 );

	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceRunning );

	usleep( 200 * 1000 );

	testCtl->shutdown();

	usleep( 200 * 1000 );

	ASSERT_TRUE( fibreControlService->getState() == Service::ServiceShutdown );

	ASSERT_TRUE( fibreControlService->wasCancelled() == false );
	ASSERT_TRUE( fibreControlService->getExitValue() == 0 );
#endif
}


/*
 * Unit test
 */
TEST_F(RrhServicesTestCases, unittest)
{
    unittest();
}
