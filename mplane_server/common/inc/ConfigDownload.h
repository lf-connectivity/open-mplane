/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ConfigDownload.h
 * \brief
 *
 *
 * \details
 *
 */

#ifndef CONFIGDOWNLOAD_H_
#define CONFIGDOWNLOAD_H_

#include <map>
#include <memory>
#include <string>

#include "Loggable.h"
#include "Mutex.h"

#include "IConfigDownload.h"

namespace Mplane {

class SystemTask;

/**
 * This base class implementation is intended to be used by objects that read
 * configuration data files that can be maintained by the configuration data
 * download manager.
 *
 * The final implementation register with the configuration data download
 * manager so that it knows with files types it should support. This makes the
 * download manager functionality independent of the configuration data
 * implementation from one product to the next.
 */

class ConfigDownload : public IConfigDownload, public Loggable {
 public:
  ConfigDownload(const std::string& name);

  virtual ~ConfigDownload();

  /**
   * NOTE: Normally the IConfigDownload objects have name of the form
   * "<name>ConfigDownload". Since we use this types list in tif as an
   * enumerated list, we don't need the extra "ConfigDownload" string, so that
   * gets silently removed.
   */
  static std::string CONFIG_TYPE_SUFFIX;

  /**
   * Get the name associated with this configuration data down load type. This
   * name is used to derive the hash value.
   */
  virtual std::string getName() const override;

  /**
   * Get the type name associated with this configuration data down load type.
   * If the name is of the form <Type>ConfigDownload, then the string returned
   * by this method will be <Type>
   */
  virtual std::string getTypeName() const override;

  /**
   * Called after object creation in order to perform any other initialisation
   * tasks that can't be done during initialisation (i.e. ensures all virtual
   * methods get called correctly)
   *
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if initialised ok, false otherwise
   */
  virtual bool initialise(std::string& failReason) override;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param remoteFilename Filename of remote file to download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& remoteFilename, std::string& failReason) override;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed.
   *
   * Adds a callback function that is used to output status during the operation
   *
   * @param remoteFilename Filename of remote file to download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& remoteFilename,
      std::shared_ptr<IFileStatus> status,
      std::string& failReason) override;

  /**
   * Is a download currently running?
   * @return true is running a download; false if complete or error
   */
  virtual bool isRunning() const override;

  /**
   * Set the url of the remote directory in which the file will be served from
   * @param url
   * @param failReason Set to failure reason if returns false
   */
  virtual bool setRemoteUrl(
      const std::string& url, std::string& failReason) override;

  /*! @brief  Display information about this image type
   *
   */
  virtual void show(std::ostream& os = std::cout) const override;

  /**
   * Get the full path of install file
   * @return file path
   */
  virtual std::string getInstallFilePath() const override;

  /**
   * Get the filename of install file
   * @return filename
   */
  virtual std::string getInstallFileName() const override;

  /**
   * Set the name of file to install (in the install dir). This may well be
   * different from the remote filename that is downloaded
   * @param name
   * @param failReason Set to failure reason if returns false
   * @return status. Will be true if ok, false otherwise
   */
  virtual bool setInstallFileName(
      const std::string& name, std::string& failReason) override;

  /**
   * Set the status object
   */
  virtual void setStatusObject(std::shared_ptr<IFileStatus> status) override;

  /**
   * Adds a path and it's configuration date - used to display the list of
   * config dates for each path
   */
  virtual void addPath(unsigned path, const std::string& calDate) override;

  /**
   * Get the FileMgrWriter instance for installing config files. Used in
   * preparation for installing a config file via TCP port
   */
  virtual std::shared_ptr<IFileMgrWriter> getConfigFileWriter(
      std::shared_ptr<IFileStatus> statusObj,
      unsigned fileSize,
      std::string& failReason) override;

  /**
   * Switches getAndInstall() method from downloading a url, into transfer via
   * TCP port. Uses the TCP transfer callback to get the data
   */
  virtual void startTcpTransfer(TcpConfigTransfer configTransfer) override;

  /**
   * Ends the TCP transfer
   */
  virtual void endTcpTransfer() override;

  // protected:
  /**
   * Set the directory path in which the file will be installed into
   * @param dir
   * @param failReason Set to failure reason if returns false
   * @return status. Will be true if ok, false otherwise
   */
  virtual bool setInstallDir(
      const std::string& dir, std::string& failReason) override;

  /**
   * Returns the current setting for the status callback function
   * @return status function
   */
  virtual std::shared_ptr<IFileStatus> getStatusObject(void) const override;

  /**
   * Change the install directory for test purposes
   * @param path
   * @param failReason
   * @return true if directory changed ok
   */
  virtual bool testInjectInstallDir(
      const std::string& path, std::string& failReason) override;

 protected:
  // Download status
  enum ConfigDownloadStatus {
    CONFIGDOWNLOAD_IDLE,
    CONFIGDOWNLOAD_RUNNING,
  };

  // Utility methods used by derived objects

  /**
   * Get the current status
   */
  ConfigDownloadStatus getStatus() const;

  /**
   * Set the status
   */
  void setStatus(const ConfigDownloadStatus& status);

  /**
   * Utility to download a single file using the file's url into the specified
   * save directory. Does a download to a temporary directory and temporary
   * filename
   *
   * @param failReason Set to failure reason if returns false
   * @return true if file downloaded ok
   */
  bool downloadFile(std::string& failReason);

  /**
   * Checks that the data structure has all of it's fields set appropriately.
   * Overridable so that derived objects can determine their own criteria for
   * data being complete.
   *
   * @param failReason Set to failure reason if returns false
   * @return true if data ok
   */
  virtual bool checkData(
      const std::string& remoteFilename, std::string& failReason) const;

  // Private data access
  const std::string&
  getInstallDir() const {
    return mInstallDir;
  }

  const std::string&
  getServerUrl() const {
    return mServerUrl;
  }

  const std::string&
  getRemoteFileName() const {
    return mRemoteFileName;
  }

 private:
  /**
   * Mutex to protect status
   */
  mutable Mutex mMutex;

  // Cache the type name string
  mutable std::string mTypeName;

  // Current status
  ConfigDownloadStatus mStatus;

  // Server url
  std::string mServerUrl;

  // name for download
  std::string mRemoteFileName;

  // install directory
  std::string mInstallDir;

  // install filename
  std::string mInstallFileName;

  // unique name associated with this config data type
  std::string mConfigDataName;

  // Function to use to report back status during download
  std::shared_ptr<IFileStatus> mStatusObject;

  std::shared_ptr<IFileMgr> mFileMgr;
  TcpConfigTransfer mTcpTransfer;

  // Paths and config dates
  std::map<unsigned, std::string> mPathDates;
};

} // namespace Mplane

#endif /* CONFIGDOWNLOAD_H_ */
