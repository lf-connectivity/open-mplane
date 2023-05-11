/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanLogFileMgr.h
 * \brief     Manager of ORAN log files
 *
 *
 * \details   Collects the ORAN log files in an application and for generating those files
 *
 */


#ifndef FILEORANLOG_INC_ORANLOGFILEMGR_H_
#define FILEORANLOG_INC_ORANLOGFILEMGR_H_

#include <memory>
#include <vector>
#include <string>

#include "IORanLogFileMgr.h"

namespace Mplane
{

/*!
 * \class  ORanLogFileMgr
 * \brief
 * \details
 *
 */
class ORanLogFileMgr : public virtual IORanLogFileMgr
{
public:
	ORanLogFileMgr();
	virtual ~ORanLogFileMgr();

	/**
	 * Add a log file to be managed by this manager
	 */
	virtual void addFile(std::shared_ptr<IORanLogFile> file) override;

	/**
	 * Enable/disable file compression
	 */
	virtual void setFileCompression(bool enable) override;

	/**
	 * Generate the log files. Returns the list of paths to the files
	 */
	virtual std::vector<std::string> generateLogs() override;

	/**
	 * Set the storage directory for all the files
	 */
	virtual void setDir(const std::string & dir) override;

	/**
	 * get (and clear) any error
	 */
	virtual std::string error() override;

	/**
	 * For debug, clear the list of files and reset the manager
	 */
	virtual void clear() override;

	/**
	 * Start logging. Rather than doing all files like generateLogs(), this method
	 * does a single file then stops. Use with nextLog() and doneLog() to iterate over
	 * all files
	 */
	virtual bool startLog() override;

	/**
	 * have we iterated over all files?
	 */
	virtual bool doneLog() override;

	/**
	 * iterated over the next files
	 */
	virtual bool nextLog() override;

	/**
	 * Get the list of all file paths
	 */
	virtual std::vector<std::string> paths() override;


private:
	/**
	 * Set the error string and return FALSE
	 */
	bool setError(const std::string& error);

private:
	std::string mDir;
	bool mCompress;
	std::vector<std::shared_ptr<IORanLogFile>> mFiles;
	std::string mError;
	unsigned mIndex; //<! file iteration index
};

}

#endif /* FILEORANLOG_INC_ORANLOGFILEMGR_H_ */
