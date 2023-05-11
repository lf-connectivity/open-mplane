/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IImage.h
 * \brief     Interface class for individual tarball image manipulation
 *
 *
 * \details   Interface to class that provides the methods to download, verify, and install compressed image files
 *
 */


#ifndef IIMAGE_H_
#define IIMAGE_H_

#include <functional>
#include <iostream>

#include "IFileStatus.h"

namespace Mplane {

class IImage {
public:
	/**
	 * Download function used to download a single file
	 */
	using DownloadFunction = std::function< bool(
		const std::string& filename,
		const std::string& serverUrl,
		const std::string& saveDir,
		std::string& failReason) > ;

	IImage() {}
	virtual ~IImage() {}

	/**
	 * Returns the number of files that this IImage class needs to download. Used to determine total progress
	 */
	virtual unsigned numFiles() const =0 ;

	/**
	 * Get an (over) estimate of the total install time, in seconds, for this image
	 */
	virtual unsigned installTimeSecs() const =0 ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(std::string& failReason) =0 ;

	/**
	 * Clean out all old images from the install directory
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool clean(std::string& failReason) =0 ;

	/**
	 * Is a download currently running?
	 * @return true is running a download; false if complete or error
	 */
	virtual bool isRunning() const =0 ;

	/**
	 * Set the url of the remote directory in which the file will be served from
	 * @param url
     * @param failReason Set to failure reason if returns false
	 */
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) =0 ;

	/**
	 * Set the name of image to download and install
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setImageName(const std::string& name, std::string& failReason) =0 ;

	/**
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) =0 ;

	/**
	 * Get the install directory for this image
	 */
	virtual std::string installDir() const =0 ;

	/**
	 * Utility provided by the derived class that converts a version and build number into a full image name. Uses
	 * the current build settings for this application along with the type of the derived object (e.g. app, library, os etc)
	 * to create the name
	 *
	 * @param version
	 * @param buildNumber
	 */
	virtual std::string formatName(const std::string& version, const std::string& buildNumber) =0 ;

    /**
     * Has the required file already been downloaded and exist in the install directory, and passes check
     * @return true if exists and passes check
     */
    virtual bool isDownloaded(void) =0 ;

    /**
     * Has the required file already been downloaded and installed
     * @return true if installed
     */
    virtual bool isInstalled(void) =0  ;

    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /**
     * Utility that returns information on the current install image
     * @return string containing information, or empty string if none
     */
    virtual std::string info() const =0 ;

    /**
     * Set the "current" image to use the specified file on next reboot. Updates the "previous"
     * image
     * @return TRUE if successful
     */
    virtual bool setCurrent(const std::string& filename) =0 ;

    /**
     * Get the filename of the current running image
     * @return filename, or empty string if no current image
     */
    virtual std::string current() const =0 ;

    /**
     * Get the filename of the previous running image
     * @return filename, or empty string if no previous image
     */
    virtual std::string previous() const =0 ;

    /**
     * Roll install back to previous installation
     * @param failReason
     * @return true if rollback was successful
     */
    virtual bool usePrevious(std::string failReason) =0 ;

    /**
     * Set the status object
     */
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) =0 ;

    /**
     * Set the default status object
     */
    virtual void defaultStatusObject() =0 ;

    /**
     * Set a new download function
     */
    virtual void setDownloadFunction(DownloadFunction download) =0 ;

    /**
     * Restore default download function
     */
    virtual void defaultDownloadFunction() =0 ;

protected:
    /**
     * Returns the current download function
     */
    virtual DownloadFunction getDownloadFunction() const =0 ;

    /**
     * Returns the current setting for the status callback function
     * @return status function
     */
    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const =0 ;

} ;


}

#endif /* IIMAGE_H_ */
