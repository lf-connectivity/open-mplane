/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpSession.h
 * \brief     Simple libssh wrapper for sftp
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SSH_INC_SFTPSESSION_H_
#define SSH_INC_SFTPSESSION_H_

#include <libssh/sftp.h>

#include <string>
#include <memory>
#include <mutex>
#include <list>

#include "TaskEvent.h"
#include "TimeoutTimer.h"
#include "ISftpSession.h"
#include "ISshSession.h"

namespace Mplane {

/*!
 * \class  SftpSession
 * \brief
 * \details
 *
 */
class SftpSession : public virtual ISftpSession, public TaskEvent {
public:
	SftpSession(std::shared_ptr<SshSession> ssh) ;
	virtual ~SftpSession() ;

	/**
	 * Is the session currently connected?
	 */
	bool isConnected() const ;

	/**
	 * Debug. Set debug level
	 */
	virtual void setDebug(unsigned level) override ;

	/**
	 * Get the current SFTP user
	 */
	virtual std::string user() const override ;

	/**
	 * Get the current SFTP host machine
	 */
	virtual std::string host() const override ;

	/**
	 * Start a file upload. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool fileUpload(const std::string& remoteFile, const std::string& localFile, ISftpSession::SftpFileCallback complete,
			unsigned timeoutSecs = 0) override ;

	/**
	 * Start a file download. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool fileDownload(const std::string& remoteFile, const std::string& localFile, ISftpSession::SftpFileCallback complete,
			unsigned timeoutSecs = 0) override ;

	/**
	 * Start a file upload from a data string. Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool dataUpload(const std::string& remoteFile, const std::string& data, ISftpSession::SftpDataCallback complete,
			unsigned timeoutSecs = 0,
			int fileOptions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) override ;

	/**
	 * Start a file download to a data string (data will be provided in callback). Transfer will complete in the background and the "complete" function called when done
	 * @return TRUE if file transfer scheduled ok; false otherwise
	 */
	virtual bool dataDownload(const std::string& remoteFile, ISftpSession::SftpDataCallback complete,
			unsigned timeoutSecs = 0) override ;


	/**
	 * get any errors and clear them
	 */
	virtual std::string error() override ;

	/**
	 * Disconnect session (freeing up resources)
	 */
	virtual void disconnect() override ;


protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	void setError(const std::string& error) ;
	void addMkdir(const std::string remotePath) ;
	std::string sshError(const std::string& msg) ;

	class Job ;
	void handleMkdir(std::shared_ptr<Job> job) ;
	void handleFileUpload(std::shared_ptr<Job> job) ;
	void handleFileDownload(std::shared_ptr<Job> job) ;
	void handleDataUpload(std::shared_ptr<Job> job) ;
	void handleDataDownload(std::shared_ptr<Job> job) ;


	using GetDataFunc = std::function<bool(std::string& data, std::string& error)> ;
	using PuttDataFunc = std::function<bool(const std::string& data, std::string& error)> ;
	bool doUpload(const std::string& remotePath, int fileOptions, GetDataFunc getData, std::string& error,
			std::shared_ptr<TimeoutTimer> timer) ;
	bool doDownload(const std::string& remotePath, PuttDataFunc puttData, std::string& error,
			std::shared_ptr<TimeoutTimer> timer) ;

private:
	std::mutex mMutex ;
	std::shared_ptr<ISshSession> mSsh ;
	bool mConnected ;
	sftp_session mSession ;
	std::string mError ;

	std::list< std::shared_ptr<Job> > mJobs ;
	char* mDataBuffer ;
} ;

}

#endif /* SSH_INC_SFTPSESSION_H_ */
