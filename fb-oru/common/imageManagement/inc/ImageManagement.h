#ifndef _COMM_IMAGEMANAGEMENT_H_
#define _COMM_IMAGEMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageManagement.h
 * \brief     The class definition for Image Management
 *
 *
 * \details   The class definition for Image Management
 *
 */
#include <memory>
#include <map>

#include "GlobalTypeDefs.h"
#include "Mutex.h"

#include "IImage.h"
#include "IImageManagement.h"

namespace Mplane
{
/*! \brief The common ImageManagement class
 *
 * The ImageManagement class provides a singleton interface to the radio application's
 * image management task that is responsible for ensuring the application manages its
 * images within the application.
 *
 */
class ImageManagement: public IImageManagement
{

public:

    /**
     * destructor
     */
    ~ImageManagement();

    /**
     * Shut the task down
     */
    virtual void shutdown(void) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param failReason string containing failure reason if fails
	 * @param status Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) override ;

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
			std::string& failReason, std::shared_ptr<Conditional> endSignal) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param failReason string containing failure reason if fails
	 * @param status Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) override ;

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
			std::string& failReason, std::shared_ptr<Conditional> endSignal) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param imageName Image name to download
	 * @param status Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& imageName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) override ;

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
			std::string& failReason) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of image to download
	 * @param version Image version to download
	 * @param build Image build number to download
	 * @param status Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(ImageType type, const std::string& version, const std::string& build,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) override ;

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
			std::string& failReason) override ;



	/**
	 * Clean out all but the latest files from the install directory of the specified image type
	 *
	 * @param type Image type to clean
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool cleanImages(ImageType type, std::string& failReason) override ;

	/**
	 * Clean out all but the latest files from the install directory of all images
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if cleaned ok, false if failed
	 */
	virtual bool cleanImages(std::string& failReason) override ;

	/**
	 * Is a download currently running?
	 * @return true if running a download; false if complete or error
	 */
	virtual bool isDownloading(void) const override ;

	/**
	 * Returns the download status once complete. On failure, failReason string will contain an error message
	 * @param failReason	Error message if failed
	 * @return true if downloaded ok; fale on failure
	 */
	virtual bool isDownloadOk(std::string& failReason) const override ;



	/**
	 * Set the url of the remote directory in which the file will be served from
	 * @param url
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) override ;

	/**
	 * Get the current remote url setting
	 * @return remote url
	 */
	virtual std::string getRemoteUrl() override ;

	/**
	 * Set the threshold number of stored packages, above which an auto-clean will be caused.
	 * @param threshold	threshold
	 * @return true if ok
	 */
	virtual bool setAutocleanThreshold(unsigned threshold, std::string& failReason) override;

	/**
	 * Get current auto-clean threshold value
	 */
	virtual unsigned getAutocleanThreshold(void) override ;


	// Specific options for OS

	/**
	 * Get the current OS bank setting
	 */
	virtual IImageTypes::OsImageBank getOsBank(void) override ;

	/**
	 * Set whether next OS install will also install a new u-boot
	 * @param ubootInstall	if true will install u-boot
     * @param failReason Set to failure reason if returns false
	 * @return true if ok
	 */
	virtual bool setUbootInstall(bool ubootInstall, std::string& failReason) override ;

	/**
	 * Get current u-boot install value
	 */
	virtual bool getUbootInstall(void) override;

    /*! @brief  Display detailed information about image management
     *
     */
    virtual void showDetail(std::ostream& os = std::cout) const override ;

    /*! @brief  Display information about image management
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /*! @brief  Display information about a particular image type
     *
     */
    virtual void show(ImageType type, std::ostream& os = std::cout) const override ;

    /**
     * Get the Image object that handles this type
     * @param type	Image type
     * @return shared pointer to Image object
     */
    virtual std::shared_ptr<IImage> getImage(const ImageType& type) override ;

    /**
     * Set a new download function for all image types
     */
    virtual void setDownloadFunction(IImage::DownloadFunction download) override ;

    /**
     * Restore default download function for all image types
     */
    virtual void defaultDownloadFunction() override ;

	/**
	 * Get the FileMgrWriter instance for installing zip files. Used in preparation for installing a zip file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getZipFileWriter(std::shared_ptr<IFileStatus> statusObj,
			unsigned fileSize, std::string& failReason) override ;

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
			std::string& failReason) override ;


protected:
	/**
	 * Allow derived objects to modify the image objects
	 */
	virtual bool replaceImageObject(IImageTypes::Type type, std::shared_ptr<IImage> image) override ;


protected:

    /**
     * Constructor protected so task can only be created by the singleton
     * implementation of getInterface.
     */
    explicit ImageManagement();

    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override;


protected:
    // Get the current state and type of downloading image
    bool getState(ImageType& type) const ;

    // Set the state
    void setState(bool downloading, const ImageType& type) ;


    // Set the status object for all image objects
    void setStatusObject(std::shared_ptr<IFileStatus> status) ;

    // Set the default status object for all image objects
    void defaultStatusObject() ;

    // set the url without mutex lock
	bool setRemoteUrlNoMutex(const std::string& url, std::string& failReason) ;

	// check auto-clean threshold - initiate clean if over threshold
	bool checkAutoClean(unsigned threshold, std::string& failReason) ;

	// low-level (non mutex protected) clean
	bool doCleanImages(std::string& failReason) ;


private:
    // Task loop control
    bool mTaskRunning ;

    // Server
    std::string mServerUrl ;

    // Protect state
    mutable Mutex mMutex ;

    // Running state
    bool mIsDownloading ;
    ImageType mTypeDownloading ;
    std::string mImageName ;
    std::shared_ptr<Conditional> mCondEnd ;
    std::shared_ptr<IImage> mDownloadImage ;
    bool mDownloadOk ;
    std::string mDownloadFailReason ;
    std::shared_ptr<IFileStatus> mStatusObject ;
    std::function<void(void)> mDownloadDoneCallback ;
    unsigned mAutocleanThreshold ;

    // Conditional used to start download
    Conditional mCondStart ;

    // Keep a map of the Image objects used to manage each image type
    std::map<ImageType, std::shared_ptr<IImage>> mImageMap ;

};


}  // end namespace Mplane

#endif /* _COMM_IMAGEMANAGEMENT_H_ */
