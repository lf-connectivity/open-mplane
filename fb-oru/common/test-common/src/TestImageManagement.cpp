/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestImageManagement.cpp
 * \brief     The implementation of the Image Management in the TIF test application
 *
 *
 * \details   The implementation of the Image Management in the TIF test application
 *
 */

#include "IImageManagement.h"
#include "ImageManagement.h"
#include "TestImageManagement.h"

using namespace Mplane;

static const std::string TEMP_INSTALL_DIR("/tmp/nandflash") ;

// The TestImageManagement implementation.
TestImageManagement::TestImageManagement(const std::string& topdir) :
	ImageManagement()
{
	// Amend the install directory for each object
	std::string failReason ;
	getImage(IImageTypes::IMAGE_APPLICATION)->setInstallDir(topdir + "/app-images", failReason) ;
	getImage(IImageTypes::IMAGE_LIBRARY)->setInstallDir(topdir + "/lib-images", failReason) ;
	getImage(IImageTypes::IMAGE_ROS)->setInstallDir(topdir + "/os-images", failReason) ;
	getImage(IImageTypes::IMAGE_FPGA)->setInstallDir(topdir + "/fpga-images", failReason) ;
	getImage(IImageTypes::IMAGE_PACKAGE)->setInstallDir(topdir + "/pkg-images", failReason) ;
}

TestImageManagement::TestImageManagement() :
	TestImageManagement(TEMP_INSTALL_DIR)
{
}
