/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpPath.h
 * \brief     Object representing SFTP remote file path
 *
 *
 * \details   Created by a string of the form:
 *
 * 		sftp://<username>@<host>[:port]/path
 *
 * 		Methods of theclass can then access the various parts of the path
 *
 */


#ifndef INC_SFTPPATH_H_
#define INC_SFTPPATH_H_

#include <string>

namespace Mplane {

/*!
 * \class  SftpPath
 * \brief
 * \details
 *
 */
class SftpPath {
public:
	SftpPath(const std::string& remotePath) ;
	virtual ~SftpPath() ;

	/**
	 * Is this a valid remote path
	 */
	bool isValid() const ;

	/*
	 * If path is invalid then get the error string
	 */
	std::string error() const ;

	/**
	 * Get the user name
	 */
	std::string user() const ;

	/**
	 * Get the remote host name
	 */
	std::string host() const ;

	/**
	 * Get the remote path
	 */
	std::string path() const ;

	/**
	 * Get the optional port. Returns 0 if not specified
	 */
	unsigned port() const ;

private:
	bool mValid ;
	std::string mUser ;
	std::string mHost ;
	std::string mPath ;
	unsigned mPort ;
	std::string mError ;
} ;

}

#endif /* INC_SFTPPATH_H_ */
