/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFileMgr.h
 * \brief     Virtual interface to a file manager
 *
 *
 * \details   Manage file download/upload and local storage listing and deletion
 *
 */

#ifndef IFILEMGR_H_
#define IFILEMGR_H_

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "IFileStatus.h"

namespace Mplane {

/**
 * File save virtual class. This class is used to manage data transferred
 * primarily over TCP PORT IN ports, where the data is to be written to a file.
 * Each block of data added via this class will be appended to the end of the
 * file.
 */
class IFileMgrWriter {
 public:
  IFileMgrWriter() {}
  virtual ~IFileMgrWriter() {}

  /**
   * Append new data to the file
   * @return false on error
   */
  virtual bool addData(const std::vector<uint8_t>& data) = 0;

  /**
   * Change the status object used during the file write
   * @param status
   */
  virtual void setStatusObject(std::shared_ptr<IFileStatus> status) = 0;
};

/**
 * File manager virtual class
 */
class IFileMgr {
 public:
  IFileMgr() {}
  virtual ~IFileMgr() {}

  /**
   * Factory for creating new instances
   */
  static std::shared_ptr<IFileMgr> factory();
  static std::shared_ptr<IFileMgr> factory(const std::string& dir);

  /**
   * Callback function used to return download/upload status
   */
  using StatusFunction = std::function<void(const std::string&)>;

  /**
   * Set the directory path to where these files are stored locally.
   * Upload/download will use this directory
   * @param dir
   * @param mkdir    Optional parameter: if set then automatically creates
   * the path to this directory if it doesn't exist
   * @return true if able to switch to this directory (i.e. it exists etc)
   */
  virtual bool setDir(const std::string& dir, bool mkdir = false) = 0;

  /**
   * Set the temporary directory path to where these files are temporarily
   * downloaded to. Using this method overrides the default location
   * @param dir
   * @param mkdir    Optional parameter: if set then automatically creates
   * the path to this directory if it doesn't exist
   * @param clear    Optional parameter: if set then clears out any existing
   * files/directories found in the specified directory
   * @return true if able to switch to this directory (i.e. it exists etc)
   */
  virtual bool setTempDir(
      const std::string& dir, bool mkdir = true, bool clear = true) = 0;

  /**
   * Get the current directory setting
   */
  virtual std::string getDir() const = 0;

  /**
   * Get the current temporary directory setting
   */
  virtual std::string getTempDir() const = 0;

  /**
   * Returns any error string created by running these methods. Clears out the
   * stored error
   * @return error string or empty
   */
  virtual std::string getError() = 0;

  /**
   * List the files stored in the directory set via the 'setDir()' method. If an
   * extension has been set via setExtension then this will show only those
   * files that have the extension
   * @return list of files
   */
  virtual std::vector<std::string> listFiles() = 0;

  /**
   * Delete based on filename but also accepts * wildcard. If just '*' is
   * specified then deletes all files, otherwise expects the start of a filename
   * ending in '*' and will then delete all files starting with the specified
   * string
   * @param filename
   * @return true if deleted ok
   */
  virtual bool delfile(const std::string& filename) = 0;

  /**
   * Delete the specified file
   * @param filename
   * @return true if file deleted
   */
  virtual bool del(const std::string& filename) = 0;

  /**
   * Delete the specified file. Uses the index from the list of files (as
   * returned by listFiles() method)
   * @param fileIndex 0-based file index
   * @return true if file deleted
   */
  virtual bool del(unsigned fileIndex) = 0;

  /**
   * Download the file from the specified url
   * @param url Where to get file from
   * @param filename Local filename to store file as
   * @param status Optional status callback function
   * @return true if file downloaded
   */
  virtual bool download(
      const std::string& url, const std::string& filename) = 0;

  virtual bool download(
      const std::string& url,
      const std::string& filename,
      std::shared_ptr<IFileStatus> status) = 0;

  /**
   * Start transferring data via a TCP PORT IN port onto the unit to be saved in
   * the current directory using the specified filename If everything is set up
   * ok, returns a pointer to a newly created IFileMgrWriter object which will
   * manage the file writes
   * @return pointer to a newly created IFileMgrWrite object; null pointer on
   * error
   */
  virtual std::shared_ptr<IFileMgrWriter> portTransferStart(
      const std::string& filename, unsigned fileSize) = 0;

  /**
   * Start transferring data via a TCP PORT IN port onto the unit to be saved in
   * the current directory using the specified filename If everything is set up
   * ok, returns a pointer to a newly created IFileMgrWriter object which will
   * manage the file writes
   * @return pointer to a newly created IFileMgrWrite object; null pointer on
   * error
   */
  virtual std::shared_ptr<IFileMgrWriter> portTransferStart(
      const std::string& filename,
      unsigned fileSize,
      std::shared_ptr<IFileStatus> status) = 0;

  /**
   * Stop the port transfer. If transfer completed with no errors, runs the
   * final tidy up and any file moving required
   * @return true if everything completed without errors
   */
  virtual bool portTransferEnd(bool ok) = 0;

  /**
   * Get the amount (approximately) of free space available in the directory
   * specified by setDir() method
   */
  virtual unsigned long long dirFreeSpace() const = 0;
};

} // namespace Mplane

#endif /* IFILEMGR_H_ */
