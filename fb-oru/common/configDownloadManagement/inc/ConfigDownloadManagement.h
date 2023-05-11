/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigDownloadManagement.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef CONFIG_DOWNLOAD_MANAGEMENT_H_
#define CONFIG_DOWNLOAD_MANAGEMENT_H_

#include <map>
#include <memory>

#include "IConfigDownloadManagement.h"
#include "Conditional.h"
#include "Task.h"

namespace Mplane {

class ConfigDownloadManagement : public IConfigDownloadManagement, public Task
{
public:
	virtual ~ConfigDownloadManagement() ;

    /**
     * Shut the task down
     */
    virtual void shutdown(void) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of config file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of config file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of config file to download
	 * @param fileName CalDownload name to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of config file to download
	 * @param fileName CalDownload name to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName, const std::string& fileName,
			std::string& failReason) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of config file to download
	 * @param failReason string containing failure reason if fails
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason,
			std::shared_ptr<Conditional> endSignal) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns immediately. Caller uses endSignal conditional
	 * to be notified of end of download.
	 *
	 * @param type Type of config file to download
	 * @param failReason string containing failure reason if fails
	 * @param endSignal If set then this Conditional will be used to signal the end of the download to the caller
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::string& failReason, std::shared_ptr<Conditional> endSignal) override ;


	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of config file to download
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::shared_ptr<IFileStatus> status,
			std::string& failReason) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param type Type of config file to download
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if downloaded ok, false if failed
	 */
	virtual bool getAndInstall(const std::string& typeName,
			std::string& failReason) override ;




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

    /*! @brief  Display detailed information about config file management
     *
     */
    virtual void showDetail(std::ostream& os = std::cout) const override ;

    /*! @brief  Display information about config file management
     *
     */
    virtual void show(std::ostream& os = std::cout) const override ;

    /*! @brief  Display information about a particular config file type
     *
     */
    virtual void show(const std::string& typeName, std::ostream& os = std::cout) const override ;

	/**
	 * Get the name of installed file
	 * @param type Type of config file
	 * @return filename
	 */
	virtual std::string getInstallFileName(const std::string& typeName) const override ;

	/**
	 * Get the full file path for the installed file
	 * @param type Type of config file
	 * @return file path
	 */
	virtual std::string getInstallFilePath(const std::string& typeName) const override ;

	/**
	 * Change the install directory for test purposes
	 * @param path
	 * @param failReason
	 * @return true if directory changed ok
	 */
	virtual bool testInjectInstallDir(const std::string& path, std::string& failReason) override ;

	/**
	 * Method used to add different calibration download types to the calibration data download
	 * manager.
	 *
	 * @param calDownLoad
	 * @return true is added OK, otherwise false.
	 */
	virtual bool addConfigDownloadType( std::shared_ptr<IConfigDownload> calDownLoad ) override;


    /**
     * Return a list of calibration down load types registered with the calibration download manager.
     * @return
     */
    virtual std::vector< std::shared_ptr<IConfigDownload> > getConfigDowloadObjects() override;

	/**
	 * Get the list of IConfigDownload names currently installed in the manager.
	 *
	 * NOTE: Normally the IConfigDownload objects have name of the form "<name>Download". Since we use this types list
	 * in tif as an enumerated list, we don't need the extra "Download" string, so that gets silently removed.
	 *
	 * Similarly, the type name string specified in the other commands can be with or without the trailing "Download"
	 */
	virtual std::set<std::string> getTypes() const override ;

	/**
	 * Get the FileMgrWriter instance for installing config files. Used in preparation for installing a config file
	 * via TCP port
	 */
	virtual std::shared_ptr<IFileMgrWriter> getConfigFileWriter(
			const std::string& typeName,
			std::shared_ptr<IFileStatus> statusObj,
			unsigned fileSize, std::string& failReason) override ;

	/**
	 * Performs the file download (in a background task) handling and error checking and verification and then
	 * installs the file into the required destination. Returns when all operations have completed
	 *
	 * @param statusFunc Status callback. Used to display status information during download
	 * @param configWriteFunc Write function used to write the file data
	 * @param configCompleteFunc Complete function used to tidy up
	 * @param failReason string containing failure reason if fails
	 * @return Will be true if downloaded ok, false if failed
	 */
	virtual bool configInstall(
		const std::string& typeName,
		std::shared_ptr<IFileStatus> status,
		ImageConfigWrite configWriteFunc,
		ImageConfigComplete configCompleteFunc,
		std::string& failReason) override ;


protected:

    /**
     * Constructor protected so task can only be created by the singleton
     * implementation of getInterface.
     */
	ConfigDownloadManagement();

    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override;


protected:
    // Get the current state and type of downloading image
    bool getState(std::string& typeName) const ;

    // Set the state
    void setState(bool downloading, const std::string& typeName) ;

    // Get the config download object (mainly for test purposes)
    std::shared_ptr<IConfigDownload> getConfigDownload(const std::string& typeName) const ;

    // Set the status object for all image objects
    void setStatusObject(std::shared_ptr<IFileStatus> status) ;

	// Set the url without any mutex locking
	virtual bool setRemoteUrlNoMutex(const std::string& url, std::string& failReason) ;


private:
    // Task loop control
    bool mTaskRunning ;

    // Server
    std::string mServerUrl ;

    // Injected install dir (set when we want to debug and override the default path)
    std::string mInjectedInstallDir ;

    // Protect state
    mutable Mutex mMutex ;

    // Running state
    bool mIsDownloading ;
    std::string mTypeDownloading ;
    std::string mFileName ;
    std::shared_ptr<Conditional> mCondEnd ;
    std::shared_ptr<IConfigDownload> mDownload ;
    bool mDownloadOk ;
    std::string mDownloadFailReason ;
    std::shared_ptr<IFileStatus> mStatusObject ;
    std::function<void(void)> mDownloadDoneCallback ;

    // Conditional used to start download
    Conditional mCondStart ;

    typedef std::map< std::string, std::shared_ptr<IConfigDownload>> MapConfigDownload;

    // Keep a map of the Config objects used to manage each config type
    MapConfigDownload mConfigDownloadMap ;

} ;

}

#endif /* CONFIG_DOWNLOAD_MANAGEMENT_H_ */
