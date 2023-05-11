/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestImageManagement.cpp
 * \brief     The implementation of the Image Management
 *
 *
 * \details   The implementation of the Image Management
 *
 */

#include "TestImageManagement.h"

#include "IImageManagement.h"
#include "ImageManagement.h"

using namespace Mplane;

static const std::string TEMP_INSTALL_DIR("/tmp/nandflash") ;

// The TestImageManagement implementation.
Mplane::TestImageManagement::TestImageManagement() :
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
std::shared_ptr<IImageManagement> IImageManagement::getInstance()
{
    static std::shared_ptr<IImageManagement> pImageManagement(new TestImageManagement());

    // auto start
    static int start = pImageManagement->start() ;

	// avoid compiler warning
	int rc = start ; start = rc ;

    return pImageManagement;
}
