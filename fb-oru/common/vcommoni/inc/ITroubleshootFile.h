/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITroubleshootFile.h
 * \brief     Virtual interface to troubleshoot log file
 *
 *
 * \details   Virtual interface to troubleshoot log file
 *
 */


#ifndef VCOMMONI_INC_ITROUBLESHOOTFILE_H_
#define VCOMMONI_INC_ITROUBLESHOOTFILE_H_

#include <string>
#include <functional>
#include <memory>

namespace Mplane {

/*!
 * \class  ITroubleshootFile
 * \brief
 * \details
 *
 */
class ITroubleshootFile {
public:

	/**
	 * Factory for creating instances of these troubleshooting files
	 *
	 */
	static std::shared_ptr<ITroubleshootFile> factory(const std::string& filename) ;

	ITroubleshootFile() {}
	virtual ~ITroubleshootFile() {}

	/**
	 * Set the storage directory
	 */
	virtual void setDir(const std::string& dir) =0 ;

	/**
	 * Enable/disable file compression
	 */
	virtual void setCompress(bool enable) =0;

	/**
	 * Get the full file path
	 */
	virtual std::string path() const =0 ;

	/**
	 * Is the file empty (and/or not written)?
	 */
	virtual bool empty() const =0 ;

	/**
	 * Gather data and save the file
	 * \return TRUE if completed ok; FALSE otherwise
	 */
	virtual bool troubleshoot() =0 ;

	/**
	 * Optional callback used to gather the data for the log. Gathers the data into a single string
	 */
	using GatherDataFunc = std::function<std::string()> ;

	/**
	 * Set the data gathering function. This will be used when the troubleshoot() method is called
	 *
	 * \note The alternative to this is for a derived object to implement it's own data gather method
	 */
	virtual void registerDataGatherer(GatherDataFunc func) =0 ;

	/**
	 * get (and clear) any error
	 */
	virtual std::string error() =0 ;
} ;

}

#endif /* VCOMMONI_INC_ITROUBLESHOOTFILE_H_ */
