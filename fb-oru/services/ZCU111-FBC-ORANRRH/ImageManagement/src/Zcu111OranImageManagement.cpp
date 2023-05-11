/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranImageManagement.cpp
 * \brief     The implementation of the Image Management in the host application
 *
 *
 * \details   The implementation of the Image Management in the host application
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Zcu111OranOsImage.h"
#include "Zcu111OranAppImage.h"
#include "NullLibImage.h"
#include "Zcu111OranImageManagement.h"

using namespace Mplane;


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IImageManagement> IImageManagement::getInstance()
{
    static std::shared_ptr<ImageManagement> pImageManagement(new Zcu111OranImageManagement());
    return pImageManagement;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111OranImageManagement::Zcu111OranImageManagement() :
	ImageManagement()
{
	// Replace the default image objects with Zcu111-specific
	replaceImageObject(IImageTypes::IMAGE_APPLICATION, std::make_shared<Zcu111OranAppImage>(*this)) ;
	replaceImageObject(IImageTypes::IMAGE_ROS, std::make_shared<Zcu111OranOsImage>(*this)) ;
	replaceImageObject(IImageTypes::IMAGE_LIBRARY, std::make_shared<NullLibImage>(*this)) ;

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
