/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111ImageManagement.cpp
 * \brief     The implementation of the Image Management in the host application
 *
 *
 * \details   The implementation of the Image Management in the host application
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Zcu111OsImage.h"
#include "NullLibImage.h"
#include "Zcu111ImageManagement.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111ImageManagement::Zcu111ImageManagement()
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

	// Replace the default image objects with Zcu111-specific
	replaceImageObject(IImageTypes::IMAGE_ROS, std::make_shared<Zcu111OsImage>(*this)) ;
	replaceImageObject(IImageTypes::IMAGE_LIBRARY, std::make_shared<NullLibImage>(*this)) ;
}
