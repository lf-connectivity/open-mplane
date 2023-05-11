/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageBase.h
 * \brief     Base class that implements the IImage interface
 *
 *
 * \details   Base class that implements the IImage class with overridable protected methods
 *
 * Class is designed such that only one instance of this class (or a derived class) can be downloading at a time. This
 * is to ensure that the file system is managed properly (i.e. we don't try downloading multiple files at the same time
 * each instance thinking there's just enough file space left for it's downloads and not being aware that the space
 * is also being used up by another instance).
 *
 * With this restriction applied it means that all ImageBase instances will run consecutively so there is no need for
 * excessive multi-thread protection. In this case we just lock the internal state and don't allow any outside variable
 * changes or download initiation until the state shows it's currently idle (i.e. not downloading). This protects us
 * from multiple TIF instances/threads trying to change things during a download.
 *
 * File-system protection is by design in that the instances of ImageData *must* all be run in the same thread and
 * therefore can only be run consecutively.
 *
 */


#ifndef IMAGEBASE_H_
#define IMAGEBASE_H_

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "IImage.h"
#include "Mutex.h"
#include "Loggable.h"

#include "ImageTask.h"
#include "SystemTask.h"

#include "ImageFundamental.h"

namespace Mplane {

class ImageBase : public ImageFundamental
{
public:
	using super = ImageFundamental ;

    // Constructor
	explicit ImageBase(ImageTask& task, const std::string& name) ;

	// Destructor
	virtual ~ImageBase() ;


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
	 * Set the name of image to download and install
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setImageName(const std::string& name, std::string& failReason) override ;

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
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override ;

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
     * Restore default download function
     */
    virtual void defaultDownloadFunction() override ;

protected:

    // Overridable ALGORITHM methods

    /**
     * Has the required file already been downloaded and exist in the install directory, and passes check
     * @param failReason Set to failure reason if returns false
     * @return true if exists and passes check
     */
    virtual bool alreadyDownloaded()  ;

    /**
     * Has the required file already been downloaded and installed
     * @param failReason Set to failure reason if returns false
     * @return true if installed
     */
    virtual bool alreadyInstalled()  ;

    /**
     * Download the file(s) ready for checking
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool download(std::string& failReason) ;

    /**
     * Check the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool check(std::string& failReason) ;

    /**
     * Install the file(s)
     * @param failReason Set to failure reason if returns false
	 * @return true if completed ok; false on failure, in which case the status will be set
     */
    virtual bool install(std::string& failReason) ;

protected:

    // Utility methods used by derived objects

    /**
     * Utility to download a single file using the file's url into the specified save directory. Downloads to a temporary
     * directory before checking amount of required space for file and seeing if destination directory has sufficient space.
     * In there is insufficient space will run clean() to try to free space
     *
     * @param filename	Base filename to download
     * @param serverUrl Server url
     * @param saveDir Directory in which to save file
     * @param failReason Set to failure reason if returns false
     * @return true if file downloaded ok
     */
    bool downloadFileSpaceCheck(const std::string& filename, const std::string& serverUrl, const std::string& saveDir, std::string& failReason) ;

    /**
     * Utility to download a single file using the file's url into the specified save directory. Does a download direct to
     * the save directory.
     *
     * @param filename	Base filename to download
     * @param serverUrl Server url
     * @param saveDir Directory in which to save file
     * @param failReason Set to failure reason if returns false
     * @return true if file downloaded ok
     */
    bool downloadFile(const std::string& filename, const std::string& serverUrl, const std::string& saveDir, std::string& failReason) ;

    /**
     * Utility to check a single file using it's MD5 sum check file
     * @param fileUrl
     * @param savePath
     * @param failReason Set to failure reason if returns false
     * @return true if file checks ok
     */
    bool checkFile(const std::string& saveDir, const std::string& filename, const std::string& md5file, std::string& failReason) ;

    /**
     * Checks that the data structure has all of it's fields set appropriately. Overridable so that derived objects can determine
     * their own criteria for data being complete.
     *
     * @param failReason Set to failure reason if returns false
     * @return true if data ok
     */
    virtual bool checkData(std::string& failReason) const ;

    /**
     * Is there enough free file system storage to add the specified size file? Uses the directory path to determine
     * the file system to check.
     *
     * NOTE: This method has been made virtual only so that a test class can be derived which overrides this utility to test
     * out the other methods properly
     *
     * @param dir	Directory in which file would be saveds
     * @param requiredSize	Size of file to save
     * @param failReason	Failure reason if returns false
     * @return true if enough file space
     */
    virtual bool isFreeFileSpace(const std::string& dir, unsigned requiredSize, std::string& failReason) const ;

    /**
     * Convert an image name into an MD5 filename
     * @param imageName
     * @return
     */
    virtual std::string md5Filename(const std::string& imageName) const ;

    /**
     * Convert an image name into an MD5 list filename
     * @param imageName
     * @return
     */
    virtual std::string md5ListFilename(const std::string& imageName) const ;

    /**
     * Given an image name of the format NNNN-VV.VV-BB-TTT.tgz gets the base name part (NNN), the version number VV.VV
     * and the build number (BB)
     * @param imageName Image name
     * @param baseName	Base name of image
     * @param version	version float
     * @param buildNumber	Build number
     * @return false if unable to extract values
     */
    virtual bool getVersionBuild(const std::string& imageName, std::string& baseName, float& version, unsigned& buildNumber) const ;

    /**
     * Checks to see if (a) link exists, and (b) link points to the specified file. If both of these are true then
     * the link is current
     *
     * @param linkPath	Path to link to check
     * @param filePath	Path to file that link should point at
     * @return true if link current
     */
    bool linkCurrent(const std::string& linkPath, std::string& filePath) const ;

	const std::string& getMd5ListName() const {
		return mMd5ListName;
	}
	void setMd5ListName(const std::string& md5ListName) {
		mMd5ListName = md5ListName;
	}

	const std::string& getMd5Name() const {
		return mMd5Name;
	}

	const std::string& getCurrentLink() const ;
	const std::string& getPreviousLink() const ;

private:
	// skip files (for file status)
	void skipFiles() ;

private:
    // Name of MD5 checksum file
    std::string mMd5Name ;

    // Name of MD5 checksum list file
    std::string mMd5ListName ;
} ;


}

#endif /* IMAGEBASE_H_ */
