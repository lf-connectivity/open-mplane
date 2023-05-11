/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IORanLogFileMgr.h
 * \brief     API for manager of ORAN log files
 *
 *
 * \details   Interface for collecting the ORAN log files in an application and for generating those files
 *
 */

#ifndef VCOMMONI_INC_IORANLOGFILEMGR_H_
#define VCOMMONI_INC_IORANLOGFILEMGR_H_

#include <string>
#include <memory>
#include <vector>

#include "IORanLogFile.h"

namespace Mplane
{

/*!
 * \class  IORanLogFileMgr
 * \brief
 * \details
 *
 */
class IORanLogFileMgr
{
public:

	IORanLogFileMgr() {}
	virtual ~IORanLogFileMgr() {}

	/**
	 * Add an ORAN log file to be managed by this manager
	 */
	virtual void addFile(std::shared_ptr<IORanLogFile> file) = 0;

	/**
	 * Enable/disable file compression
	 */
	virtual void setFileCompression(bool enable) = 0;

	/**
	 * Set the storage directory for all the files
	 */
	virtual void setDir(const std::string& dir) = 0;

	/**
	 * get (and clear) any error
	 */
	virtual std::string error() = 0;

	/**
	 * For debug, clear the list of files and reset the manager
	 */
	virtual void clear() = 0;

	/**
	 * Generate the log files. Returns the list of paths to the files
	 */
	virtual std::vector<std::string> generateLogs() = 0;

	/**
	 * Start logging. Rather than doing all files like generateLogs(), this method
	 * does a single file then stops. Use with nextLog() and doneLog() to iterate over
	 * all files
	 */
	virtual bool startLog() = 0;

	/**
	 * have we iterated over all files?
	 */
	virtual bool doneLog() = 0;

	/**
	 * iterated over the next files
	 */
	virtual bool nextLog() = 0;

	/**
	 * Get the list of all file paths
	 */
	virtual std::vector<std::string> paths() = 0;


} ;

}

#endif /* VCOMMONI_INC_IORANLOGFILEMGR_H_ */
