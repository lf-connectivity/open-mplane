/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LibImage.h
 * \brief     Library image class
 *
 *
 * \details   Handles download and install of library images
 *
 */


#ifndef LIBIMAGE_H_
#define LIBIMAGE_H_

#include "ImageBase.h"

namespace Mplane {

class LibImage : public ImageBase
{
public:
	using super = ImageBase ;

    // Constructor
	explicit LibImage(ImageTask& task) ;

	// Destructor
	virtual ~LibImage() ;

	/**
	 * Returns the number of files that this IImage class needs to download. Used to determine total progress
	 */
	virtual unsigned numFiles() const override ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

	/**
	 * Set the name of image to download and install
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setImageName(const std::string& name, std::string& failReason) override ;

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

    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /**
     * Utility that returns information on the current install image
     * @return string containing information, or empty string if none
     */
    virtual std::string info() const override ;


protected:

    // Overridable ALGORITHM methods

    /**
     * Has the required file already been downloaded and exist in the install directory, and passes check.
     *
     * LibImage variant is slightly more complex than the default in order to attempt to only download new files
     * when necessary. If the actual filename isn't already downloaded (i.e. the default behaviour), then this version
     * goes on to download the remote md5list file and compares the contents with the currently downloaded file. If
     * the contents of the current library match with the new library then marks the current as being an equivalent of the new
     * library and does not download it.
     *
     * @param failReason Set to failure reason if returns false
     * @return true if exists and passes check
     */
    virtual bool alreadyDownloaded() override ;
} ;


}

#endif /* LIBIMAGE_H_ */
