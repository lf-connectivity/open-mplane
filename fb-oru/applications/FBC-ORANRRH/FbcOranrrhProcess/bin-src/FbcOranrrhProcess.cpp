/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FbcOranrrhProcess.cpp
 * \brief     Facebook Consortium ORAN radio application
 *
 *
 * \details   Facebook Consortium ORAN  radio application
 *
 */
#ifdef OFF_TARGET
#include "IFpgaKernel.h"
#endif

#include "RadioApp.h"

using namespace Mplane;

/*!
 * \brief The first start point for the program
 */
int main(int argc, const char** argv)
{
#ifdef OFF_TARGET
	  // change the off-target fpga configuration settings
	  ::setenv("OFFTARGET_CFG_DIR", "../../../../../hardware/ZCU111_ORANRRH/fpga/cfg", 1) ;

	// Get kernel to ensure FPGA emulator is created with correct data size
	auto kernel(IFpgaKernel::getInstance()) ;
	(void)kernel;
#endif

	// Create application
	std::shared_ptr<IApplication> app( std::make_shared<RadioApp>() ) ;

	// Run the app
	return app->run("FBC ORAN RRH", argc, argv) ;
}
