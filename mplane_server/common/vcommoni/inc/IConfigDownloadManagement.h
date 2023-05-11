#ifndef _COMM_ICONFIGDOWNLOADMANAGEMENT_H_
#define _COMM_ICONFIGDOWNLOADMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IConfigDownloadManagement.h
 * \brief     Interface to ConfigDownload Management
 *
 *
 * \details   Interface for ConfigDownload Management
 *
 */
#include <memory>
#include <set>
#include <vector>

#include "Conditional.h"

#include "IConfigDownload.h"
#include "IFileStatus.h"

namespace Mplane {
/*! \brief The common ConfigDownloadManagement class
 *
 * The ConfigDownloadManagement class provides a singleton interface to the
 * radio application's config file download management task that is responsible
 * for ensuring the application manages its config file downloads within the
 * application.
 *
 */
class IConfigDownloadManagement {

 public:
  using ConfigDownloadType = std::size_t;

  /**
   * Singleton
   */
  static std::shared_ptr<IConfigDownloadManagement> getInstance();

  IConfigDownloadManagement() {}
  virtual ~IConfigDownloadManagement() {}

  /**
   * Shut the task down
   */
  virtual void shutdown(void) = 0;

  /**
   * Method used to add different configuration download types to the
   * configuration data download manager.
   *
   * @param ConfigDownload
   * @return true is added OK, otherwise false.
   */
  virtual bool addConfigDownloadType(
      std::shared_ptr<IConfigDownload> ConfigDownload) = 0;

  /**
   * Return a list of configuration down load types registered with the
   * configuration download manager.
   * @return
   */
  virtual std::vector<std::shared_ptr<IConfigDownload>>
  getConfigDowloadObjects() = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns immediately. Caller uses endSignal conditional to be
   * notified of end of download.
   *
   * @param type Type of config file to download
   * @param fileName ConfigDownload name to download
   * @param failReason string containing failure reason if fails
   * @param statusFunc Status callback. Used to display status information
   * during download
   * @param endSignal If set then this Conditional will be used to signal the
   * end of the download to the caller
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      const std::string& fileName,
      std::shared_ptr<IFileStatus> status,
      std::string& failReason,
      std::shared_ptr<Conditional> endSignal) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns immediately. Caller uses endSignal conditional to be
   * notified of end of download.
   *
   * @param type Type of config file to download
   * @param fileName ConfigDownload name to download
   * @param failReason string containing failure reason if fails
   * @param endSignal If set then this Conditional will be used to signal the
   * end of the download to the caller
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      const std::string& fileName,
      std::string& failReason,
      std::shared_ptr<Conditional> endSignal) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param type Type of config file to download
   * @param fileName ConfigDownload name to download
   * @param statusFunc Status callback. Used to display status information
   * during download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      const std::string& fileName,
      std::shared_ptr<IFileStatus> status,
      std::string& failReason) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param type Type of config file to download
   * @param fileName ConfigDownload name to download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      const std::string& fileName,
      std::string& failReason) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns immediately. Caller uses endSignal conditional to be
   * notified of end of download.
   *
   * @param type Type of config file to download
   * @param failReason string containing failure reason if fails
   * @param statusFunc Status callback. Used to display status information
   * during download
   * @param endSignal If set then this Conditional will be used to signal the
   * end of the download to the caller
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      std::shared_ptr<IFileStatus> status,
      std::string& failReason,
      std::shared_ptr<Conditional> endSignal) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns immediately. Caller uses endSignal conditional to be
   * notified of end of download.
   *
   * @param type Type of config file to download
   * @param failReason string containing failure reason if fails
   * @param endSignal If set then this Conditional will be used to signal the
   * end of the download to the caller
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      std::string& failReason,
      std::shared_ptr<Conditional> endSignal) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param type Type of config file to download
   * @param statusFunc Status callback. Used to display status information
   * during download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName,
      std::shared_ptr<IFileStatus> status,
      std::string& failReason) = 0;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param type Type of config file to download
   * @param failReason string containing failure reason if fails
   * @return status. Will be true if downloaded ok, false if failed
   */
  virtual bool getAndInstall(
      const std::string& typeName, std::string& failReason) = 0;

  /**
   * Is a download currently running?
   * @return true if running a download; false if complete or error
   */
  virtual bool isDownloading(void) const = 0;

  /**
   * Returns the download status once complete. On failure, failReason string
   * will contain an error message
   * @param failReason    Error message if failed
   * @return true if downloaded ok; fale on failure
   */
  virtual bool isDownloadOk(std::string& failReaso252n) const = 0;

  /**
   * Set the url of the remote directory in which the file will be served from
   * @param url
   * @param failReason Set to failure reason if returns false
   * @return true if ok
   */
  virtual bool setRemoteUrl(
      const std::string& url, std::string& failReason) = 0;

  /**
   * Get the current remote url setting
   * @return remote url
   */
  virtual std::string getRemoteUrl() = 0;

  /*! @brief  Display detailed information about config file management
   *
   */
  virtual void showDetail(std::ostream& os = std::cout) const = 0;

  /*! @brief  Display information about config file management
   *
   */
  virtual void show(std::ostream& os = std::cout) const = 0;

  /*! @brief  Display information about a particular config file type
   *
   */
  virtual void show(
      const std::string& typeName, std::ostream& os = std::cout) const = 0;

  /**
   * Get the name of installed file
   * @param type Type of config file
   * @return filename
   */
  virtual std::string getInstallFileName(const std::string& typeName) const = 0;

  /**
   * Get the full file path for the installed file
   * @param type Type of config file
   * @return file path
   */
  virtual std::string getInstallFilePath(const std::string& typeName) const = 0;

  /**
   * Change the install directory for test purposes
   * @param path
   * @param failReason
   * @return true if directory changed ok
   */
  virtual bool testInjectInstallDir(
      const std::string& path, std::string& failReason) = 0;

  /**
   * Get the list of IConfigDownload names currently installed in the manager.
   *
   * NOTE: Normally the IConfigDownload objects have name of the form
   * "<name>Download". Since we use this types list in tif as an enumerated
   * list, we don't need the extra "Download" string, so that gets silently
   * removed.
   *
   * Similarly, the type name string specified in the other commands can be with
   * or without the trailing "Download"
   */
  virtual std::set<std::string> getTypes() const = 0;

  /**
   * Get the FileMgrWriter instance for installing config files. Used in
   * preparation for installing a config file via TCP port
   */
  virtual std::shared_ptr<IFileMgrWriter> getConfigFileWriter(
      const std::string& typeName,
      std::shared_ptr<IFileStatus> statusObj,
      unsigned fileSize,
      std::string& failReason) = 0;

  // Callback functions used for config file install

  /**
   * config file write callback. Used to write the file data
   */
  using ImageConfigWrite = std::function<bool(void)>;

  /**
   * Tidy up function at the end of config file download
   */
  using ImageConfigComplete = std::function<void(void)>;

  /**
   * Performs the file download (in a background task) handling and error
   * checking and verification and then installs the file into the required
   * destination. Returns when all operations have completed
   *
   * @param statusFunc Status callback. Used to display status information
   * during download
   * @param calWriteFunc Write function used to write the file data
   * @param calCompleteFunc Complete function used to tidy up
   * @param failReason string containing failure reason if fails
   * @return Will be true if downloaded ok, false if failed
   */
  virtual bool configInstall(
      const std::string& typeName,
      std::shared_ptr<IFileStatus> status,
      ImageConfigWrite calWriteFunc,
      ImageConfigComplete calCompleteFunc,
      std::string& failReason) = 0;
};

} // end namespace Mplane

#endif /* _COMM_ICONFIGDOWNLOADMANAGEMENT_H_ */
