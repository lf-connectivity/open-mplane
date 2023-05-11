/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      NullFileStatus.h
 * \brief     An IFileStatus that does nothing
 *
 *
 * \details
 *
 */


#ifndef NULLFILESTATUS_H_
#define NULLFILESTATUS_H_

#include "IFileStatus.h"

namespace Mplane {

class NullFileStatus : public virtual IFileStatus {
public:
	NullFileStatus() ;
	virtual ~NullFileStatus() ;

	/**
	 * Factory to create a "null" object which provides the methods but does nothing
	 */
	static std::shared_ptr<IFileStatus> nullObject() ;

	/**
	 * Copy the data from the specified IFileStatus pointer
	 */
	virtual void copy(std::shared_ptr<IFileStatus>) override ;


	/**
	 * Set the output function to be use to report status
	 */
	virtual void setOutputFunction(IFileStatus::StatusOutputFunc func) override ;

	/**
	 * Deletes the output function
	 */
	virtual void clearOutputFunction() override ;

	/**
	 * Set the total number of files involved. Also used to reset the class
	 */
	virtual void restart(unsigned num) override ;

	/**
	 * Sets the current file operation being performed
	 */
	virtual void operation(const std::string& op) override ;

	/**
	 * Start operating on a new file
	 */
	virtual void start(const std::string& filename) override ;

	/**
	 * Start operating on a new file
	 */
	virtual void start(const std::string& op, const std::string& filename) override ;

	/**
	 * Set the percentage progress of this file
	 */
	virtual void progress(unsigned progressPercent) override ;

	/**
	 * End of operation on this file
	 */
	virtual void end() override ;

	/**
	 * Skip a file. Effectively does a start() & end() to skip a single file
	 */
	virtual void skip() override ;

	/**
	 * Skip files. Effectively does a start() & end() to skip multiple files
	 */
	virtual void skip(unsigned numFiles) override ;

	/**
	 * Report that the current file operation has failed
	 */
	virtual void fail(const std::string& error) override ;

	/**
	 * Report that all file operations have been completed
	 */
	virtual void success() override ;

	// Accessor

	/**
	 * Operations completed?
	 */
	virtual bool isComplete() const override ;

	/**
	 * Get any error string
	 */
	virtual std::string getError() const override ;

	/**
	 * Get the total number of files
	 */
	virtual unsigned getNumFiles() const override ;

	/**
	 * Current file name
	 */
	virtual std::string getFilename() const override ;

	/**
	 * Current file operation
	 */
	virtual std::string getOperation() const override ;

	/**
	 * Current file progress
	 */
	virtual unsigned getProgress() const override ;

	/**
	 * Current total progress
	 */
	virtual unsigned getTotalProgress() const override ;

} ;

}

#endif /* NULLFILESTATUS_H_ */
