/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonImageManagement.cpp
 * \brief     The implementation of the Image Management in the host application
 *
 *
 * \details   The implementation of the Image Management in the host application
 *
 */
// Includes go here, before the namespace

#include "CommonImageManagement.h"

using namespace Mplane;


// The EtnaRadioImageManagement implementation.
Mplane::CommonImageManagement::CommonImageManagement()
{
    // blank constructor, is the same as ImageManagement

#ifdef OFF_TARGET
	static const std::string TEMP_INSTALL_DIR("/tmp/nandflash") ;

	// Amend the install directory for each object
	std::string failReason ;
	getImage(IImageTypes::IMAGE_APPLICATION)->setInstallDir(TEMP_INSTALL_DIR + "/app-images", failReason) ;
	getImage(IImageTypes::IMAGE_LIBRARY)->setInstallDir(TEMP_INSTALL_DIR + "/lib-images", failReason) ;
	getImage(IImageTypes::IMAGE_ROS)->setInstallDir(TEMP_INSTALL_DIR + "/os-images", failReason) ;
	getImage(IImageTypes::IMAGE_FPGA)->setInstallDir(TEMP_INSTALL_DIR + "/fpga-images", failReason) ;
#endif
}

//// The interface to the singleton
//std::shared_ptr<IImageManagement> IImageManagement::getInstance()
//{
//    static std::shared_ptr<ImageManagement> pImageManagement(new CommonImageManagement());
//
//    return pImageManagement;
//}
