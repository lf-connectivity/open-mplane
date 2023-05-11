/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaImage.h
 * \brief     Fpga image class
 *
 *
 * \details   Handles download and install of fpga images
 *
 */


#ifndef FPGAIMAGE_H_
#define FPGAIMAGE_H_

#include "ImageBase.h"

namespace Mplane {

class FpgaImage : public ImageBase
{
public:
	using super = ImageBase ;

    // Constructor
	explicit FpgaImage(ImageTask& task) ;

	// Destructor
	virtual ~FpgaImage() ;

	/**
	 * Clean out old images from the install directory. Removes all files that are not currently linked to
	 * (e.g. by 'current', or 'previous' links etc). Also cleans out any bad links that link to non-existent files.
	 *
	 * When determining whether a file is linked to, it keeps the linked to file and any related files. For example,
	 * if there is a link for file XXX.tgz, then that file will be kept along with files like XXX.tgx.md5, XXX.tgx.mdlist
	 * etc
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool clean(std::string& failReason) override ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

	/**
	 * Utility provided by the derived class that converts a version and build number into a full image name. Uses
	 * the current build settings for this application along with the type of the derived object (e.g. app, library, os etc)
	 * to create the name
	 *
	 * @param version
	 * @param buildNumber
	 */
	virtual std::string formatName(const std::string& version, const std::string& buildNumber) override ;


    /**
     * Utility that returns information on the current install image
     * @return string containing information, or empty string if none
     */
    virtual std::string info() const override ;

    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

protected:

    // Overridable ALGORITHM methods

    /**
     * Has the required file already been downloaded and installed
     * @param failReason Set to failure reason if returns false
     * @return true if installed
     */
    virtual bool alreadyInstalled() override ;

    /**
     * Install the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool install(std::string& failReason) override ;


} ;


}

#endif /* FPGAIMAGE_H_ */
