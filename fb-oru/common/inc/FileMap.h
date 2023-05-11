/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileMap.h
 * \brief     Read a file and convert it's contents to a std::map
 *
 *
 * \details   Read a file and convert it's contents to a std::map. Base implementation expects file format to be
 * 				lines of variable=value pairs. For example:
 *
 * 				HOME=/home/root
 * 				TERM=vt102
 * 				USER=root
 * 				SHLVL=2
 * 				interface=eth0
 * 				HUSHLOGIN=FALSE
 * 				PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin
 * 				MAIL=/var/spool/mail/root
 * 				SHELL=/bin/sh
 *
 * 				If a variable is set multiple times, then the *last* value set (reading down the file) is used
 *
 */


#ifndef INC_FILEMAP_H_
#define INC_FILEMAP_H_

#include <string>
#include <map>

namespace Mplane {

/*!
 * \class  FileMap
 * \brief
 * \details
 *
 */
class FileMap {
public:
	FileMap(const std::string& filePath) ;
	FileMap() ;
	virtual ~FileMap() ;

	/**
	 * Set a new path. Automatically causes the file to be read. Any errors will be returned by the
	 * error() method.
	 *
	 * \return TRUE if file read ok; otherwise returns FALSE
	 */
	bool setPath(const std::string& filePath) ;

	/**
	 * Get the map of variable/values
	 */
	std::map<std::string, std::string> values() const ;

	/**
	 * get any errors and clear the error string
	 */
	std::string error() ;

	/**
	 * Check if a value exists in the map
	 */
	bool isValue(const std::string& name) const ;

	/**
	 * get the value; or empty string if it doesn't exist
	 */
	std::string value(const std::string& name) const ;

	/**
	 * Add the specified values to the map. Can be used for debug or for setting defaults before reading the file
	 */
	void setValues(const std::map<std::string, std::string>& values) ;

	/*
	 * Debug
	 */
	void show() const ;

protected:
	// set the error string and return FALSE
	bool setError(const std::string& error) ;

	// process the file
	bool processFile() ;

private:
	std::string mPath ;
	std::map<std::string, std::string> mValues ;
	std::string mError ;
} ;

}

#endif /* INC_FILEMAP_H_ */
