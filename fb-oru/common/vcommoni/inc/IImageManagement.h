#ifndef _COMM_IIMAGEMANAGEMENT_H_
#define _COMM_IIMAGEMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IImageManagement.h
 * \brief     Interface to Image Management
 *
 *
 * \details   Interface for Image Management
 *
 */
#include <memory>

#include "IFileMgr.h"
#include "IImageTypes.h"
#include "IImage.h"

#include "Conditional.h"
#include "ImageTask.h"

namespace Mplane
{
/*! \brief The common ImageManagement class
 *
 * The ImageManagement class provides a singleton interface to the radio application's
 * image management task that is responsible for ensuring the application manages its
 * images within the application.
 *
 */
class IImageManagement: public ImageTask
{

public:
	using ImageType = IImageTypes::Type ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IImageManagement> getInstance() ;

    IImageManagement() {}
    virtual ~IImageManagement() {}

    /**
     * Shut the task down
     */
    virtual void shutdown(void) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::string& failReason) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::string& failReason) =0 ;


	/**
	 * Clean out all but the latest files from the install directory of the specified image type
	 *
	 * @param type Image type to clean
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool cleanImages(ImageType type, std::string& failReason) =0 ;

	/**
	 * Clean out all but the latest files from the install directory of all images
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool cleanImages(std::string& failReason) =0 ;

	/**
	 * Is a download currently running?
	 * @return true if running a download; false if complete or error
	 */
	virtual bool isDownloading(void) const =0 ;

	/**
	 * Returns the download status once complete. On failure, failReason string will contain an error message
	 * @param failReason	Error message if failed
	 * @return true if downloaded ok; fale on failure
	 */
	virtual bool isDownloadOk(std::string& failReason) const =0 ;


	/**
	 * Set the url of the remote directory in which the file will be served from
	 * @param url
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) =0 ;

	/**
	 * Get the current remote url setting
	 * @return remote url
	 */
	virtual std::string getRemoteUrl() =0 ;

	/**
	 * Get the current OS bank setting
	 */
	virtual IImageTypes::OsImageBank getOsBank(void) =0 ;

	/**
	 * Set whether next OS install will also install a new u-boot
	 * @param ubootInstall	if true will install u-boot
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setUbootInstall(bool ubootInstall, std::string& failReason) =0;

	/**
	 * Get current u-boot install value
	 */
	virtual bool getUbootInstall(void) =0;

	/**
	 * Set the threshold number of stored packages, above which an auto-clean will be caused.
	 * @param threshold	threshold
	 * @return true if ok
	 */
	virtual bool setAutocleanThreshold(unsigned threshold, std::string& failReason) =0;

	/**
	 * Get current auto-clean threshold value
	 */
	virtual unsigned getAutocleanThreshold(void) =0;

    /*! @brief  Display detailed information about image management
     *
     */
    virtual void showDetail(std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display information about image management
     *
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display information about a particular image type
     *
     */
    virtual void show(ImageType type, std::ostream& os = std::cout) const =0 ;

    /**
     * Get the Image object that handles this type
     * @param type	Image type
     * @return shared pointer to Image object
     */
    virtual std::shared_ptr<IImage> getImage(const ImageType& type) =0 ;

    /**
     * Set a new download function for all image types
     */
    virtual void setDownloadFunction(IImage::DownloadFunction download) =0 ;

    /**
     * Restore default download function for all image types
     */
    virtual void defaultDownloadFunction() =0 ;


	/**
	 * Get the FileMgrWriter instance for installing zip files. Used in preparation for installing a zip file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getZipFileWriter(std::shared_ptr<IFileStatus> statusObj,
			unsigned fileSize, std::string& failReason) =0 ;


	// Callback functions used for zip file install

	/**
	 * Zip file write callback. Used to write the file data
	 */
	using ImageZipWrite = std::function<bool(void)> ;

	/**
	 * Tidy up function at the end of zip file download
	 */
	using ImageZipComplete = std::function<void(void)> ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param zipWriteFunc Write function used to write the file data
	 * @param zipCompleteFunc Complete function used to tidy up
	 * @param failReason string containing failure reason if fails
	 * @return Will be true if downloaded ok, false if failed
	 */
	virtual bool zipInstall(
			std::shared_ptr<IFileStatus> status,
			ImageZipWrite zipWriteFunc,
			ImageZipComplete zipCompleteFunc,
			std::string& failReason) =0 ;


protected:
	/**
	 * Allow derived objects to modify the image objects
	 */
	virtual bool replaceImageObject(IImageTypes::Type type, std::shared_ptr<IImage> image) =0 ;

};


}  // end namespace Mplane

#endif /* _COMM_IIMAGEMANAGEMENT_H_ */
