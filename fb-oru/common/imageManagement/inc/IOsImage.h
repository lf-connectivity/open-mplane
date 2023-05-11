/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IOsImage.h
 * \brief     Virtual interface to OS image
 *
 *
 */


#ifndef IMAGEMANAGEMENT_INC_IOSIMAGE_H_
#define IMAGEMANAGEMENT_INC_IOSIMAGE_H_

#include <string>
#include "IImageTypes.h"

namespace Mplane {

/*!
 * \class  IOsImage
 * \brief
 * \details
 *
 */
class IOsImage {
public:
	IOsImage() {}
	virtual ~IOsImage() {}

	/**
	 * Get the currently active OS bank
	 */
	virtual IImageTypes::OsImageBank getOsBank(void) =0 ;

	/**
	 * Set whether next OS install will also install a new u-boot
	 * @param ubootInstall	if true will install u-boot
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setUbootInstall(bool ubootInstall, std::string& failReason) =0 ;

	/**
	 * Get current u-boot install value
	 */
	virtual bool getUbootInstall(void) =0 ;

} ;

}

#endif /* IMAGEMANAGEMENT_INC_IOSIMAGE_H_ */
