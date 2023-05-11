/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranAppImage.h
 * \brief     Override the clean() method
 *
 *
 * \details   Provides a "slot friendly" clean() method that cleans out only files that are not allocated or read-only
 *
 */


#ifndef ZCU111_FBC_ORANRRH_IMAGEMANAGEMENT_INC_ZCU111ORANAPPIMAGE_H_
#define ZCU111_FBC_ORANRRH_IMAGEMANAGEMENT_INC_ZCU111ORANAPPIMAGE_H_

#include "AppImage.h"

namespace Mplane {

/*!
 * \class  Zcu111OranAppImage
 * \brief
 * \details
 *
 */
class Zcu111OranAppImage : public AppImage {
public:
	Zcu111OranAppImage(ImageTask& task) ;
	virtual ~Zcu111OranAppImage() ;

	/**
	 * Clean out old images from the install directory.
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool clean(std::string& failReason) override ;


} ;

}

#endif /* ZCU111_FBC_ORANRRH_IMAGEMANAGEMENT_INC_ZCU111ORANAPPIMAGE_H_ */
