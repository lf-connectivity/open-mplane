/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISftpSession.h
 * \brief     Virtual API for an SFTP session
 *
 *
 * \details   Manage an SFTP session
 *
 */


#ifndef VCOMMONI_INC_ISFTPSESSION_H_
#define VCOMMONI_INC_ISFTPSESSION_H_

#include <fcntl.h>

#include <string>
#include <functional>
#include <memory>
#include <vector>

namespace Mplane {

/*!
 * \class  ISftpSession
 * \brief
 * \details
 *
 */
class ISftpSession {
public:
	ISftpSession() {}
	virtual ~ISftpSession() {}

	/**
	 * Debug. Set debug level
	 */
	virtual void setDebug(unsigned level) =0 ;

	/**
	 * Get the current SFTP user
	 */
	virtual std::string user() const =0 ;

	/**
	 * Get the current SFTP host machine
	 */
	virtual std::string host() const =0 ;

	/**
	 * The allowed SFTP transactions
	 */
	enum SftpTransaction {
		SFTP_UPLOAD_FILE,		//<! upload a file to the host
		SFTP_DOWNLOAD_FILE,		//<! download a file from the host
		SFTP_UPLOAD_DATA,		//<! upload a file to the host
		SFTP_DOWNLOAD_DATA,		//<! download a file from the host
	};

	/**
	 * SFTP file transfer complete notification callback
	 * remoteFile = remote file path
	 * localFile = local file path
	 * transaction = the transaction type
	 * error = contains error string on any error
	 */
	using SftpFileCallback = std::function<void(const std::string& remoteFile, const std::string& localFile,
			SftpTransaction transaction, const std::string& error, bool timedOut)> ;

	/**
	 * SFTP file transfer complete notification callback
	 * remoteFile = remote file path
	 * data = empty for upload; downloaded data for download
	 * transaction = the transaction type
	 * error = contains error string on any error
	 * timedOut = TRUE if transaction timed out
	 */
	using SftpDataCallback = std::function<void(const std::string& remoteFile, const std::string& data,
			SftpTransaction transaction, const std::string& error, bool timedOut)> ;

	/**
	 * Start a file upload. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool fileUpload(const std::string& remoteFile, const std::string& localFile, SftpFileCallback complete,
			unsigned timeoutSecs = 0) =0 ;

	/**
	 * Start a file download. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool fileDownload(const std::string& remoteFile, const std::string& localFile, SftpFileCallback complete,
			unsigned timeoutSecs = 0) =0 ;

	/**
	 * Start a file upload from a data string. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool dataUpload(const std::string& remoteFile, const std::string& data, SftpDataCallback complete,
			unsigned timeoutSecs = 0,
			int fileOptions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) =0 ;

	/**
	 * Start a file download to a data string (data will be provided in callback). Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool dataDownload(const std::string& remoteFile, SftpDataCallback complete,
			unsigned timeoutSecs = 0) =0 ;


	/**
	 * get any errors and clear them
	 */
	virtual std::string error() =0 ;

	/**
	 * Disconnect session (freeing up resources)
	 */
	virtual void disconnect() =0 ;


} ;

}

#endif /* VCOMMONI_INC_ISFTPSESSION_H_ */
