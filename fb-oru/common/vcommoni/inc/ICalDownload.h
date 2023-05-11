/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICalDownload.h
 * \brief     Interface class for individual cal file download
 *
 *
 * \details   Interface to class that provides the methods to download cal files
 *
 */


#ifndef ICALDOWNLOAD_H_
#define ICALDOWNLOAD_H_

#include <functional>
#include <iostream>

#include "IFileStatus.h"
#include "IFileMgr.h"

namespace Mplane {

class ICalDownload {
public:
	ICalDownload() {}
	virtual ~ICalDownload() {}

	/**
	 * Get the name associated with this calibration data down load type. This name is used to derive the
	 * hash value.
	 */
	virtual std::string getName() const =0;

	/**
	 * Get the type name associated with this calibration data down load type. If the name is of the form
	 * <Type>CalDownload, then the string returned by this method will be <Type>
	 */
	virtual std::string getTypeName() const =0;

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
	 * @param remoteFilename Filename of remote file to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& remoteFilename, std::string& failReason) =0 ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed.
	 *
	 * Adds a callback function that is used to output status during the operation
	 *
	 * @param remoteFilename Filename of remote file to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason) =0 ;

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

    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const =0 ;

    /*! @brief  Display Temperature information about cal file management
     *
     */
    virtual void showTemperatures(std::ostream& os = std::cout) const =0;

	/**
	 * Get the full path of install file
	 * @return file path
	 */
	virtual std::string getInstallFilePath() const =0 ;

	/**
	 * Get the filename of install file
	 * @return filename
	 */
	virtual std::string getInstallFileName() const =0 ;

	/**
	 * Set the name of file to install (in the install dir). This may well be different from the remote filename that is downloaded
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallFileName(const std::string& name, std::string& failReason) =0 ;

    /**
     * Change the install directory for test purposes
     * @param path
     * @param failReason
     * @return true if directory changed ok
     */
    virtual bool testInjectInstallDir(const std::string& path, std::string& failReason) =0 ;

    /**
     * Set the status object
     */
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) =0 ;

    /**
     * Adds a path and it's calibration date - used to display the list of cal dates for each path
     */
    virtual void addPath(unsigned path, const std::string& calDate) =0 ;

    /**
     * Adds a path and it's initial calibration temperature - used to display the list of temperatures for each path
     */
    virtual void addTemperature(unsigned path, const float& calInitialTemp) =0 ;

	/**
	 * Get the FileMgrWriter instance for installing cal files. Used in preparation for installing a cal file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getCalFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
			std::string& failReason) =0 ;

	/**
	 * Callback function used to do the cal file transfer via TCP. Returns true if file is transferred ok.
	 */
	using TcpCalTransfer = std::function<bool()> ;

	/**
	 * Switches getAndInstall() method from downloading a url, into transfer via TCP port. Uses the TCP transfer callback
	 * to get the data
	 */
	virtual void startTcpTransfer(TcpCalTransfer calTransfer) =0 ;

	/**
	 * Ends the TCP transfer
	 */
	virtual void endTcpTransfer() =0 ;


protected:
	/**
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) =0 ;

    /**
     * Returns the current setting for the status callback function
     * @return status function
     */
    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const =0 ;

} ;


}

#endif /* ICALDOWNLOAD_H_ */
