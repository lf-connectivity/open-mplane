/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IImageTypes.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef IIMAGETYPES_H_
#define IIMAGETYPES_H_

#include <string>
#include <vector>

namespace Mplane {

class IImageTypes {
public:
	IImageTypes() {}
	virtual ~IImageTypes() {}

	// Image types
    enum Type
    {
        IMAGE_ZIP	 		= 0,//!< ZIP file containing all the other files
        IMAGE_PACKAGE 		= 1,//!< PACKAGE
        IMAGE_APPLICATION	= 2,//!< APPLICATION
        IMAGE_LIBRARY		= 3,//!< LIBRARY
        IMAGE_ROS			= 4,//!< ROS
        IMAGE_FPGA			= 5,//!< FPGA
    } ;

	// Specific options for OS
	enum OsImageBank {
		OS_BANK1,
		OS_BANK2,
	};


    /**
     * Convert image type into a string
     * @param type
     * @return string representing type
     */
    static std::string typeToStr(Type type) ;

    /**
     * Convert string into image type if possible
     * @param type	Set to type if string is valid
     * @return true if converted string; false otherwise
     */
    static bool strToType(const std::string& str, Type& type) ;

    /**
     * Returns the list of supported types
     */
    static std::vector<IImageTypes::Type> typesList(void) ;

} ;

}

#endif /* IIMAGETYPES_H_ */
