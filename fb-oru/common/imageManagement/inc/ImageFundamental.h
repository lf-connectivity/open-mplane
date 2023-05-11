/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageFundamental.h
 * \brief     Lowest common base class for IIamge classes
 *
 *
 * \details   Originally the class ImageBase was the base class, but when ZipImage was added it became obvious
 * 			that I needed a more fundamental base class which did all the really common bits so this class was born.
 * 			ImageBase now derives from this and adds all of the common tarball behaviour, while this class provides
 * 			the behaviours common to all
 *
 */


#ifndef IMAGEFUNDAMENTAL_H_
#define IMAGEFUNDAMENTAL_H_

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "IImage.h"
#include "Mutex.h"
#include "Loggable.h"

#include "ImageTask.h"

namespace Mplane {

class ImageFundamental : public IImage, public Loggable
{
public:
	ImageFundamental(ImageTask& task, const std::string& name) ;
	virtual ~ImageFundamental() ;

	/**
	 * Returns the number of files that this IImage class needs to download. Used to determine total progress
	 */
	virtual unsigned numFiles() const override ;

	/**
	 * Get an (over) estimate of the total install time, in seconds, for this image
	 */
	virtual unsigned installTimeSecs() const override ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(std::string& failReason) override ;

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
	 * Is a download currently running?
	 * @return true is running a download; false if complete or error
	 */
	virtual bool isRunning() const override ;

	/**
	 * Set the url of the remote directory in which the file will be served from
	 * @param url
     * @param failReason Set to failure reason if returns false
	 */
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) override ;

	/**
	 * Set the name of image to download and install
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setImageName(const std::string& name, std::string& failReason) override ;

	/**
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override ;

	/**
	 * Get the install directory for this image
	 */
	virtual std::string installDir() const override ;


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
     * Has the required file already been downloaded and exist in the install directory, and passes check
     * @return true if exists and passes check
     */
    virtual bool isDownloaded(void) override ;

    /**
     * Has the required file already been downloaded and installed
     * @return true if installed
     */
    virtual bool isInstalled(void) override  ;


    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /**
     * Utility that returns information on the current install image
     * @return string containing information, or empty string if none
     */
    virtual std::string info() const override ;

    /**
     * Set the "current" image to use the specified file on next reboot. Updates the "previous"
     * image
     * @return TRUE if successful
     */
    virtual bool setCurrent(const std::string& filename) override ;

    /**
     * Get the filename of the current running image
     * @return filename, or empty string if no current image
     */
    virtual std::string current() const override ;

    /**
     * Get the filename of the previous running image
     * @return filename, or empty string if no previous image
     */
    virtual std::string previous() const override ;


    /**
     * Roll install back to previous installation
     * @param failReason
     * @return true if rollback was successful
     */
    virtual bool usePrevious(std::string failReason) override ;

    /**
     * Set the status object
     */
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) override ;

    /**
     * Set the default status object
     */
    virtual void defaultStatusObject() override ;

    /**
     * Set a new download function
     */
    virtual void setDownloadFunction(DownloadFunction download) override ;

    /**
     * Restore default download function
     */
    virtual void defaultDownloadFunction() override ;

protected:
    /**
     * Returns the current download function
     */
    virtual IImage::DownloadFunction getDownloadFunction() const override ;

    /**
     * Returns the current setting for the status callback function
     * @return status function
     */
    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const override ;


protected:
	// Download status
	enum ImageStatus {
		IMAGE_IDLE,
		IMAGE_RUNNING,
	};


    // Utility methods used by derived objects

    /**
     * Get the current status
     */
    ImageStatus getStatus() const ;

    /**
     * Set the status
     */
    void setStatus(const ImageStatus& status) ;

    /**
     * Checks that the data structure has all of it's fields set appropriately. Overridable so that derived objects can determine
     * their own criteria for data being complete.
     *
     * @param failReason Set to failure reason if returns false
     * @return true if data ok
     */
    virtual bool checkData(std::string& failReason) const ;

    /**
     * Keep the parent task running
     */
    void keepAlive(void) ;

    // Format a value and title with fixed padding (used for show())
    void showPadValue(std::ostream& os, const std::string& title, const std::string& value) const ;


    // Private data access
	const std::string& getImageName() const {
		return mImageName;
	}

	const std::string& getInstallDir() const {
		return mInstallDir;
	}

	const std::string& getServerUrl() const {
		return mServerUrl;
	}

private:
    // task under which these image classes are running
    ImageTask& mTask ;

    /**
     * Mutex to protect status
     */
    mutable Mutex mMutex ;

    // Current status
    ImageStatus	mStatus ;

    // Server url
    std::string mServerUrl ;

    // install directory
    std::string mInstallDir ;

    // Image name for download
    std::string mImageName ;

    // Function to use to report back status during download
    std::shared_ptr<IFileStatus> mStatusObject ;

    // Function to use to download a file
    DownloadFunction mDownloadFunc ;
} ;

}

#endif /* IMAGEFUNDAMENTAL_H_ */
