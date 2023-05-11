/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IORanLogFile.h
 * \brief     Virtual interface to an ORAN log file
 *
 *
 * \details   Virtual interface to ORAN log file
 *
 */


#ifndef VCOMMONI_INC_IORANLOGFILE_H_
#define VCOMMONI_INC_IORANLOGFILE_H_

#include <string>
#include <functional>
#include <memory>

namespace Mplane
{

/*!
 * \class  IORanLogFile
 * \brief
 * \details
 *
 */
class IORanLogFile
{
public:

	/**
	 * Factory for creating instances of these ORAN log files
	 *
	 */
	static std::shared_ptr<IORanLogFile> factory(const std::string& filename);

	IORanLogFile() {}
	virtual ~IORanLogFile() {}

	/**
	 * Set the storage directory
	 */
	virtual void setDir(const std::string& dir) = 0;

	/**
	 * Enable/disable file compression
	 */
	virtual void setCompress(bool enable) = 0;

	/**
	 * Get the full file path
	 */
	virtual std::string path() const = 0;

	/**
	 * Is the file empty (and/or not written)?
	 */
	virtual bool empty() const = 0;

	/**
	 * Gather data and save the file
	 * \return TRUE if completed ok; FALSE otherwise
	 */
	virtual bool generateLog() = 0;

	/**
	 * Optional callback used to gather the data for the log. Gathers the data into a single string
	 */
	using GatherDataFunc = std::function<std::string()>;

	/**
	 * Set the data gathering function. This will be used when the generateLog() method is called
	 *
	 * \note The alternative to this is for a derived object to implement it's own data gather method
	 */
	virtual void registerDataGatherer(GatherDataFunc func) = 0;

	/**
	 * get (and clear) any error
	 */
	virtual std::string error() = 0;

} ;

}

#endif /* VCOMMONI_INC_IORANLOGFILE_H_ */
