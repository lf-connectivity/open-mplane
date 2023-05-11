/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFileStatus.h
 * \brief     Virtual interface for file status
 *
 *
 * \details   This interface provides a common class for any objects performing file operations (downloading, installing etc)
 * 			where other classes may need status and progress information on the file operation(s)
 *
 */


#ifndef IFILESTATUS_H_
#define IFILESTATUS_H_

#include <string>
#include <memory>
#include <functional>

namespace Mplane {

class IFileStatus {
public:
	IFileStatus() {}
	virtual ~IFileStatus() {}

	/**
	 * Output function for reporting the status
	 */
	using StatusOutputFunc = std::function<void(const std::string& msg)> ;


	/**
	 * Factory to create a simple status tracker. Performs no output, just tracks the progress stats
	 */
	static std::shared_ptr<IFileStatus> simpleTracker() ;

	/**
	 * Factory to create a simple status tracker with an output function that displays the file name, operation and percentage
	 * in a simple string
	 */
	static std::shared_ptr<IFileStatus> simpleOutput(StatusOutputFunc func) ;


	/**
	 * Factory to create a "null" object which provides the methods but does nothing
	 */
	static std::shared_ptr<IFileStatus> nullObject() ;


	/**
	 * Copy the data from the specified IFileStatus pointer
	 */
	virtual void copy(std::shared_ptr<IFileStatus>) =0 ;


	/**
	 * Set the output function to be use to report status
	 */
	virtual void setOutputFunction(StatusOutputFunc func) =0 ;

	/**
	 * Deletes the output function
	 */
	virtual void clearOutputFunction() =0 ;

	/**
	 * Restart the class settings, and set the total number of files involved.
	 */
	virtual void restart(unsigned num) =0 ;

	/**
	 * Sets the current file operation being performed
	 */
	virtual void operation(const std::string& op) =0 ;

	/**
	 * Start operating on a new file
	 */
	virtual void start(const std::string& filename) =0 ;

	/**
	 * Start operating on a new file
	 */
	virtual void start(const std::string& op, const std::string& filename) =0 ;

	/**
	 * Set the percentage progress of this file
	 */
	virtual void progress(unsigned progressPercent) =0 ;

	/**
	 * End of operation on this file
	 */
	virtual void end() =0 ;

	/**
	 * Skip a file. Effectively does a start() & end() to skip a single file
	 */
	virtual void skip() =0 ;

	/**
	 * Skip files. Effectively does a start() & end() to skip multiple files
	 */
	virtual void skip(unsigned numFiles) =0 ;

	/**
	 * Report that the current file operation has failed
	 */
	virtual void fail(const std::string& error) =0 ;

	/**
	 * Report that all file operations have been completed
	 */
	virtual void success() =0 ;

	// Accessor

	/**
	 * Operations completed?
	 */
	virtual bool isComplete() const =0 ;

	/**
	 * Get any error string
	 */
	virtual std::string getError() const =0 ;

	/**
	 * Get the total number of files
	 */
	virtual unsigned getNumFiles() const =0 ;

	/**
	 * Current file name
	 */
	virtual std::string getFilename() const =0 ;

	/**
	 * Current file operation
	 */
	virtual std::string getOperation() const =0 ;

	/**
	 * Current file progress
	 */
	virtual unsigned getProgress() const =0 ;

	/**
	 * Current total progress
	 */
	virtual unsigned getTotalProgress() const =0 ;
} ;

}

#endif /* IFILESTATUS_H_ */
