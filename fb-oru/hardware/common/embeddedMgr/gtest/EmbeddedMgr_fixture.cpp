/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EmbeddedMgr_fixture.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>

#include "Path.h"
#include "TestEmbeddedMgr.h"
#include "EmbeddedMgr_fixture.h"

using namespace Mplane ;

//===================================================================================================================
// TEST FIXTURE METHODS
//===================================================================================================================
namespace {
	void createFile(const std::string& path)
	{
		std::ofstream ofile(path) ;
		ofile.close() ;
	}
}
//-------------------------------------------------------------------------------------------------------------------
void EmbeddedMgrTestFixture::SetUp()
{
	std::string firmwareDir(TestEmbeddedMgr::testFirmwarePath()) ;
	Path::mkpath(firmwareDir) ;

	// Create some dummy files
	createFile(firmwareDir + "/r5-0-echo-test.bin") ;
	createFile(firmwareDir + "/r5-1-echo-test.bin") ;

	createFile(firmwareDir + "/r5-0-zzz.bin") ;
	createFile(firmwareDir + "/r5-1-zzz.bin") ;
}


//-------------------------------------------------------------------------------------------------------------------
void EmbeddedMgrTestFixture::TearDown()
{
	std::string firmwareDir(TestEmbeddedMgr::testFirmwarePath()) ;
	Path::removeDirContents(firmwareDir, true) ;
}



//-------------------------------------------------------------------------------------------------------------------
// Set up the test case (create shared resources)
void EmbeddedMgrTestFixture::SetUpTestCase()
{
}

//-------------------------------------------------------------------------------------------------------------------
// Shut down test case
void EmbeddedMgrTestFixture::TearDownTestCase()
{
}
