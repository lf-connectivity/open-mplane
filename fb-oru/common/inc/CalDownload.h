/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDownload.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef CALDOWNLOAD_H_
#define CALDOWNLOAD_H_

#include <memory>
#include <string>
#include <map>

#include "Mutex.h"
#include "Loggable.h"

#include "ICalDownload.h"


namespace Mplane {

class SystemTask ;


/**
 * This base class implementation is intended to be used by objects that read calibration data files
 * that can be maintained by the calibration data download manager.
 *
 * The final implementation register with the calibration data download manager so that it knows
 * with files types it should support. This makes the download manager functionality independent of
 * the calibration data implementation from one product to the next.
 */

class CalDownload : public ICalDownload, public Loggable
{
public:
	CalDownload(const std::string& name) ;

	virtual ~CalDownload() ;

	/**
	 * NOTE: Normally the ICalDownload objects have name of the form "<name>CalDownload". Since we use this types list
	 * in tif as an enumerated list, we don't need the extra "CalDownload" string, so that gets silently removed.
	 */
	static std::string CAL_TYPE_SUFFIX ;

    /**
     * Get the name associated with this calibration data down load type. This name is used to derive the
     * hash value.
     */
    virtual std::string getName() const override;

	/**
	 * Get the type name associated with this calibration data down load type. If the name is of the form
	 * <Type>CalDownload, then the string returned by this method will be <Type>
	 */
	virtual std::string getTypeName() const override;


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
	 * @param remoteFilename Filename of remote file to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& remoteFilename, std::string& failReason) override ;

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
	virtual bool getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason) override ;

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

    /*! @brief  Display information about this image type
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /*! @brief  Display Temperature information about cal file management
     *
     */
    virtual void showTemperatures(std::ostream& os = std::cout) const override;

	/**
	 * Get the full path of install file
	 * @return file path
	 */
	virtual std::string getInstallFilePath() const override ;

	/**
	 * Get the filename of install file
	 * @return filename
	 */
	virtual std::string getInstallFileName() const override ;

	/**
	 * Set the name of file to install (in the install dir). This may well be different from the remote filename that is downloaded
	 * @param name
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallFileName(const std::string& name, std::string& failReason) override ;

    /**
     * Set the status object
     */
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) override ;

    /**
     * Adds a path and it's calibration date - used to display the list of cal dates for each path
     */
    virtual void addPath(unsigned path, const std::string& calDate) override ;


    /**
     * Adds a path and it's initial calibration temperature - used to display the list of cal dates for each path
     */
    virtual void addTemperature(unsigned path, const float& calInitialTemp) override ;


	/**
	 * Get the FileMgrWriter instance for installing cal files. Used in preparation for installing a cal file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getCalFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
			std::string& failReason) override ;

	/**
	 * Switches getAndInstall() method from downloading a url, into transfer via TCP port. Uses the TCP transfer callback
	 * to get the data
	 */
	virtual void startTcpTransfer(TcpCalTransfer calTransfer) override ;

	/**
	 * Ends the TCP transfer
	 */
	virtual void endTcpTransfer() override ;


protected:
	/**
	 * Set the directory path in which the file will be installed into
	 * @param dir
     * @param failReason Set to failure reason if returns false
	 * @return status. Will be true if ok, false otherwise
	 */
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override ;

    /**
     * Returns the current setting for the status callback function
     * @return status function
     */
    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const override ;

    /**
     * Change the install directory for test purposes
     * @param path
     * @param failReason
     * @return true if directory changed ok
     */
    virtual bool testInjectInstallDir(const std::string& path, std::string& failReason) override ;

protected:

	// Download status
	enum CalDownloadStatus {
		CALDOWNLOAD_IDLE,
		CALDOWNLOAD_RUNNING,
	};

    // Utility methods used by derived objects

    /**
     * Get the current status
     */
	CalDownloadStatus getStatus() const ;

    /**
     * Set the status
     */
    void setStatus(const CalDownloadStatus& status) ;

    /**
     * Utility to download a single file using the file's url into the specified save directory. Does a download to a temporary
     * directory and temporary filename
     *
     * @param failReason Set to failure reason if returns false
     * @return true if file downloaded ok
     */
    bool downloadFile(std::string& failReason) ;

    /**
     * Checks that the data structure has all of it's fields set appropriately. Overridable so that derived objects can determine
     * their own criteria for data being complete.
     *
     * @param failReason Set to failure reason if returns false
     * @return true if data ok
     */
    virtual bool checkData(const std::string& remoteFilename, std::string& failReason) const ;

    // Private data access
	const std::string& getInstallDir() const {
		return mInstallDir;
	}

	const std::string& getServerUrl() const {
		return mServerUrl;
	}

	const std::string& getRemoteFileName() const {
		return mRemoteFileName;
	}

private:
    /**
     * Mutex to protect status
     */
    mutable Mutex mMutex ;

    // Cache the type name string
    mutable std::string mTypeName ;

    // Current status
    CalDownloadStatus mStatus ;

    // Server url
    std::string mServerUrl ;

    // name for download
    std::string mRemoteFileName ;

    // install directory
    std::string mInstallDir ;

    // install filename
    std::string mInstallFileName ;

    // unique name associated with this cal data type
    std::string mCalDataName;

    // Function to use to report back status during download
    std::shared_ptr<IFileStatus> mStatusObject ;

	std::shared_ptr<IFileMgr> mFileMgr ;
	TcpCalTransfer mTcpTransfer ;

	// Paths and cal dates
	std::map<unsigned, std::string> mPathDates ;

	// Paths and initial cal temperatures
	std::map<unsigned, float> mPathInitialTemps ;

} ;

}

#endif /* CALDOWNLOAD_H_ */
