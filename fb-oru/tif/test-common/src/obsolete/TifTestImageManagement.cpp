/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TifTestImageManagement.cpp
 * \brief     The implementation of the Image Management in the TIF test application
 *
 *
 * \details   The implementation of the Image Management in the TIF test application
 *
 */

#include "IImageManagement.h"
#include "ImageManagement.h"
#include "TifTestImageManagement.h"

using namespace Mplane;

static const std::string TEMP_INSTALL_DIR("/tmp/nandflash") ;

// The TifTestImageManagement implementation.
Mplane::TifTestImageManagement::TifTestImageManagement() :
	ImageManagement()
{
	// Amend the install directory for each object
	std::string failReason ;
	getImage(IImageTypes::IMAGE_APPLICATION)->setInstallDir(TEMP_INSTALL_DIR + "/app-images", failReason) ;
	getImage(IImageTypes::IMAGE_LIBRARY)->setInstallDir(TEMP_INSTALL_DIR + "/lib-images", failReason) ;
	getImage(IImageTypes::IMAGE_ROS)->setInstallDir(TEMP_INSTALL_DIR + "/os-images", failReason) ;
	getImage(IImageTypes::IMAGE_FPGA)->setInstallDir(TEMP_INSTALL_DIR + "/fpga-images", failReason) ;
	getImage(IImageTypes::IMAGE_PACKAGE)->setInstallDir(TEMP_INSTALL_DIR + "/pkg-images", failReason) ;
}

// The interface to the singleton
std::shared_ptr<IImageManagement> Mplane::IImageManagement::getInstance()
{
    static std::shared_ptr<IImageManagement> pImageManagement(new TifTestImageManagement());

    // auto start
    static int start = pImageManagement->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

    return pImageManagement;
}
