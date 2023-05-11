/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxCalDownload.h"
#include "cm_fixture.h"


using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RxCalDownload::RxCalDownload() :
	CalDownload("RxCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RxCalDownload::~RxCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::RxCalDownload::initialise(std::string& failReason)
{
	this->super::initialise(failReason) ;
	failReason = "" ;

    // Create a user-specific temp directory in which to run tests - needs to match up with test fixture
    std::string nandDir( CmTestFixture::getNandDir() );
    setInstallDir(nandDir + "/cal", failReason) ;
	return setInstallFileName("rxcal.xml", failReason) ;
}
