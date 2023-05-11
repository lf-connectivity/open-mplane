/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalDownload.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxCalDownload.h"
#include "cm_fixture.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::TxCalDownload::TxCalDownload() :
	CalDownload("TxCalDownload")
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxCalDownload::~TxCalDownload()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::TxCalDownload::initialise(std::string& failReason)
{
std::cerr << "TxCalDownload::initialise()" << std::endl ;

	this->super::initialise(failReason) ;
	failReason = "" ;

    std::string nandDir( CmTestFixture::getNandDir() );
    setInstallDir(nandDir + "/cal", failReason) ;

	std::cerr << "TxCalDownload::initialise() - set install file to : txcal.xml" << std::endl ;
	return setInstallFileName("txcal.xml", failReason) ;
}
