/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ZipImage.h
 * \brief     Manage install from a zip file
 *
 *
 * \details   Handle installing all files zipped up into a single zip file
 *
 */


#ifndef ZIPIMAGE_H_
#define ZIPIMAGE_H_

#include <memory>
#include "IImage.h"

#include "ImageFundamental.h"

namespace Mplane {

class IFileMgr ;

class ZipImage : public ImageFundamental {
public:
	explicit ZipImage(ImageTask& task) ;
	virtual ~ZipImage() ;

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
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed.
	 *
	 * Adds a callback function that is used to output status during the operation
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(std::string& failReason) override ;

	/**
	 * Clean out all old images from the install directory
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool clean(std::string& failReason) override ;

    /**
     * Has the required file already been downloaded and exist in the install directory, and passes check
     * @return true if exists and passes check
     */
    virtual bool isDownloaded(void) override ;

	/**
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override ;

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
	 * Get the FileMgrWriter instance for installing zip files. Used in preparation for installing a zip file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getZipFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
			std::string& failReason) ;

	/**
	 * Callback function used to do the zip file transfer via TCP. Returns true if file is transferred ok.
	 */
	using TcpZipTransfer = std::function<bool()> ;

	/**
	 * Switches getAndInstall() method from downloading a url, into transfer via TCP port. Uses the TCP transfer callback
	 * to get the data
	 */
	virtual void startTcpTransfer(TcpZipTransfer zipTransfer) ;

	/**
	 * Ends the TCP transfer
	 */
	virtual void endTcpTransfer() ;


private:
    // "psuedo" file download - just copies file from zip
    bool transferFile(const std::vector<std::string>& unzippedFiles, const std::string& filename, const std::string& saveDir,
    		std::string& failReason) ;

    // Get the zip file (either by download url or via TCP)
    bool getZipFile(std::string& filename, std::string& failReason) ;


private:
	std::shared_ptr<IFileMgr> mFileMgr ;
	TcpZipTransfer mTcpTransfer ;
} ;

}

#endif /* ZIPIMAGE_H_ */
