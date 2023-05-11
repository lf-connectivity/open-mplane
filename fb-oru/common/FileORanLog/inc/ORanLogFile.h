/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ORanLogFile.h
 * \brief     Base class implementing an ORAN log file
 *
 *
 * \details   Base class implementing an ORAN log file. This base class needs a data gather function to be defined. Otherwise
 *            derived classes can override the dataGather() method
 *
 */


#ifndef FILEORANLOG_INC_ORANLOGFILE_H_
#define FILEORANLOG_INCFILEORANLOG_INC_ORANLOGFILE_H_

#include "IORanLogFile.h"

namespace Mplane
{

/*!
 * \class  ORanLogFile
 * \brief
 * \details
 *
 */
class ORanLogFile : public virtual IORanLogFile
{
public:
	/**
	 * Factory for creating instances of these ORAN log files
	 *
	 */
	static std::shared_ptr<IORanLogFile> factory(const std::string & filename);

	ORanLogFile(const std::string & filename);
	virtual ~ORanLogFile();

	/**
	 * Set the storage directory
	 */
	virtual void setDir(const std::string & dir) override;

	/**
	 * Enable/disable file compression
	 */
	virtual void setCompress(bool enable) override;

	/**
	 * Get the full file path
	 */
	virtual std::string path() const override;

	/**
	 * Is the file empty (and/or not written)?
	 */
	virtual bool empty() const override;

	/**
	 * Gather data and save the file
	 * \return TRUE if completed ok; FALSE otherwise
	 */
	virtual bool generateLog() override;

	/**
	 * Set the data gathering function. This will be used when the generateLog() method is called
	 *
	 * \note The alternative to this is for a derived object to implement it's own data gather method
	 */
	virtual void registerDataGatherer(IORanLogFile::GatherDataFunc func) override;

	/**
	 * get (and clear) any error
	 */
	virtual std::string error() override;


protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather function has been registered
	 */
	virtual std::string dataGather();

	/**
	 * Set the error string and return FALSE
	 */
	bool setError(const std::string & error);

private:
	std::string mFilename;
	std::string mDir;
	bool mCompress;
	IORanLogFile::GatherDataFunc mGatherDataFunc;
	bool mEmpty;
	std::string mError;
};

}

#endif /* FILEORANLOG_INC_ORANLOGFILE_H_ */
