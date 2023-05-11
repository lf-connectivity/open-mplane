/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileStatus.h
 * \brief     Base class for managing file status
 *
 *
 * \details   This interface provides a common class for any objects performing
 * file operations (downloading, installing etc) where other classes may need
 * status and progress information on the file operation(s)
 *
 */

#ifndef FILESTATUS_H_
#define FILESTATUS_H_

#include "IFileStatus.h"

// Uncomment for testbench debug
//#define DEBUG_FILESTATUS

namespace Mplane {

class FileStatus : public virtual IFileStatus {
 public:
  FileStatus();
  virtual ~FileStatus();

  // Copy constructor
  explicit FileStatus(std::shared_ptr<IFileStatus> rhs);

  /**
   * Factory to create a simple status tracker. Performs no output, just tracks
   * the progress stats
   */
  static std::shared_ptr<IFileStatus> simpleTracker();

  /**
   * Factory to create a simple status tracker with an output function that
   * displays the file name, operation and percentage in a simple string
   */
  static std::shared_ptr<IFileStatus> simpleOutput(StatusOutputFunc func);

  /**
   * Copy the data from the specified IFileStatus pointer
   */
  virtual void copy(std::shared_ptr<IFileStatus>) override;

  /**
   * Set the output function to be use to report status
   */
  virtual void setOutputFunction(IFileStatus::StatusOutputFunc func) override;

  /**
   * Deletes the output function
   */
  virtual void clearOutputFunction() override;

  /**
   * Set the total number of files involved. Also used to reset the class
   */
  virtual void restart(unsigned num) override;

  /**
   * Sets the current file operation being performed
   */
  virtual void operation(const std::string& op) override;

  /**
   * Start operating on a new file
   */
  virtual void start(const std::string& filename) override;

  /**
   * Start operating on a new file
   */
  virtual void start(
      const std::string& op, const std::string& filename) override;

  /**
   * Set the percentage progress of this file
   */
  virtual void progress(unsigned progressPercent) override;

  /**
   * End of operation on this file
   */
  virtual void end() override;

  /**
   * Skip a file. Effectively does a start() & end() to skip a single file
   */
  virtual void skip() override;

  /**
   * Skip files. Effectively does a start() & end() to skip multiple files
   */
  virtual void skip(unsigned numFiles) override;

  /**
   * Report that the current file operation has failed
   */
  virtual void fail(const std::string& error) override;

  /**
   * Report that all file operations have been completed
   */
  virtual void success() override;

  // Accessor

  /**
   * Operations completed?
   */
  virtual bool isComplete() const override;

  /**
   * Get any error string
   */
  virtual std::string getError() const override;

  /**
   * Get the total number of files
   */
  virtual unsigned getNumFiles() const override;

  /**
   * Current file name
   */
  virtual std::string getFilename() const override;

  /**
   * Current file operation
   */
  virtual std::string getOperation() const override;

  /**
   * Current file progress
   */
  virtual unsigned getProgress() const override;

  /**
   * Current total progress
   */
  virtual unsigned getTotalProgress() const override;

 protected:
  // Overridable methods for creating the output string
  virtual std::string outputStart(
      const std::string& op, const std::string& filename) const;
  virtual std::string outputPercent(unsigned percent) const;
  virtual std::string outputEnd() const;

 private:
  // Updates the progress counts and returns true if the status has changed such
  // that a new output is required
  bool updateProgress(unsigned progress);

#ifdef DEBUG_FILESTATUS
  void debugShow();
#endif

 private:
  unsigned mNumFiles;
  unsigned mCurrentFile;
  std::string mOp;
  std::string mFile;
  unsigned mFileProgress;
  unsigned mTotalProgress;
  bool mDone;
  std::string mError;
  IFileStatus::StatusOutputFunc mOutputFunc;

  // Internal tracker - used to determine whether to output or not
  int mPrevProgress;
};

} // namespace Mplane

#endif /* FILESTATUS_H_ */
