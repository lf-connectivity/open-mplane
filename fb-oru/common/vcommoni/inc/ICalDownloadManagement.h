#ifndef _COMM_ICALDOWNLOADMANAGEMENT_H_
#define _COMM_ICALDOWNLOADMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICalDownloadManagement.h
 * \brief     Interface to CalDownload Management
 *
 *
 * \details   Interface for CalDownload Management
 *
 */
#include <memory>
#include <vector>
#include <set>

#include "Conditional.h"

#include "ICalDownload.h"
#include "IFileStatus.h"

namespace Mplane
{
/*! \brief The common CalDownloadManagement class
 *
 * The CalDownloadManagement class provides a singleton interface to the radio application's
 * cal file download management task that is responsible for ensuring the application manages its
 * cal file downloads within the application.
 *
 */
class ICalDownloadManagement
{

public:
	using CalDownloadType = std::size_t ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<ICalDownloadManagement> getInstance() ;

    ICalDownloadManagement() {}
    virtual ~ICalDownloadManagement() {}

    /**
     * Shut the task down
     */
    virtual void shutdown(void) =0 ;

    /**
     * Method used to add different calibration download types to the calibration data download
     * manager.
     *
     * @param calDownLoad
     * @return true is added OK, otherwise false.
     */
    virtual bool addCalDownloadType( std::shared_ptr<ICalDownload> calDownLoad ) = 0;


    /**
     * Return a list of calibration down load types registered with the calibration download manager.
     * @return
     */
    virtual std::vector< std::shared_ptr<ICalDownload> > getCalDowloadObjects() = 0;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of cal file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of cal file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of cal file to download
	 * @param fileName CalDownload name to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of cal file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::string& failReason) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of cal file to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of cal file to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) =0 ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of cal file to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of cal file to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::string& failReason) =0 ;



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
	virtual bool isDownloadOk(std::string& failReaso252n) const =0 ;


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

    /*! @brief  Display detailed information about cal file management
     *
     */
    virtual void showDetail(std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display information about cal file management
     *
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display information about a particular cal file type
     *
     */
    virtual void show(const std::string& typeName, std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display Temperature information about cal file management
     *
     */
    virtual void showTemperatures(std::ostream& os = std::cout) const =0 ;

	/**
	 * Get the name of installed file
	 * @param type Type of cal file
	 * @return filename
	 */
	virtual std::string getInstallFileName(const std::string& typeName) const =0 ;

	/**
	 * Get the full file path for the installed file
	 * @param type Type of cal file
	 * @return file path
	 */
	virtual std::string getInstallFilePath(const std::string& typeName) const =0 ;

	/**
	 * Change the install directory for test purposes
	 * @param path
	 * @param failReason
	 * @return true if directory changed ok
	 */
	virtual bool testInjectInstallDir(const std::string& path, std::string& failReason) =0 ;

	/**
	 * Get the list of ICalDownload names currently installed in the manager.
	 *
	 * NOTE: Normally the ICalDownload objects have name of the form "<name>Download". Since we use this types list
	 * in tif as an enumerated list, we don't need the extra "Download" string, so that gets silently removed.
	 *
	 * Similarly, the type name string specified in the other commands can be with or without the trailing "Download"
	 */
	virtual std::set<std::string> getTypes() const =0 ;


	/**
	 * Get the FileMgrWriter instance for installing cal files. Used in preparation for installing a cal file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getCalFileWriter(
			const std::string& typeName,
			std::shared_ptr<IFileStatus> statusObj,
			unsigned fileSize, std::string& failReason) =0 ;


	// Callback functions used for cal file install

	/**
	 * Cal file write callback. Used to write the file data
	 */
	using ImageCalWrite = std::function<bool(void)> ;

	/**
	 * Tidy up function at the end of cal file download
	 */
	using ImageCalComplete = std::function<void(void)> ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param calWriteFunc Write function used to write the file data
	 * @param calCompleteFunc Complete function used to tidy up
	 * @param failReason string containing failure reason if fails
	 * @return Will be true if downloaded ok, false if failed
	 */
	virtual bool calInstall(
		const std::string& typeName,
		std::shared_ptr<IFileStatus> status,
		ImageCalWrite calWriteFunc,
		ImageCalComplete calCompleteFunc,
		std::string& failReason) =0 ;

};


}  // end namespace Mplane

#endif /* _COMM_ICALDOWNLOADMANAGEMENT_H_ */
