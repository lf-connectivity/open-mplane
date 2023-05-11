/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SftpSession.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include "NullTimeoutTimer.h"
#include "Path.h"
#include "TimeoutTimer.h"

#include "SftpPath.h"
#include "SftpSession.h"
#include "SshSession.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
/**
 * NOTE: Whatever you do, do NOT allocate a buffer of this size on the stack.
 * Because the stack is running inside a thread (where the default stack size is
 * small) you'll end up with really weird behaviour and segfaults as the stack
 * overflows!
 *
 */
const unsigned BUFF_LEN = 165335;

// Uncomment to add debug
//#define DEBUG_SFTP

//=============================================================================================================
// Job
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class SftpSession::Job {
 public:
  enum JobType {
    JOB_TRANSACTION,
    JOB_MKDIR,
  };

  void
  show() const {
#ifdef DEBUG_SFTP
    std::cerr << "JOB ";
    if (mType == JOB_MKDIR) {
      std::cerr << "MKDIR " << mRemotePath << std::endl;
      return;
    }

    std::cerr << "TRANSACTION ";
    switch (mTransaction) {
      case SFTP_UPLOAD_FILE:
        std::cerr << "UPLOAD FILE remote=" << mRemotePath
                  << " local=" << mLocalPath;
        break;

      case SFTP_DOWNLOAD_FILE:
        std::cerr << "DOWNLOAD FILE remote=" << mRemotePath
                  << " local=" << mLocalPath;
        break;

      case SFTP_UPLOAD_DATA:
        std::cerr << "UPLOAD DATA remote=" << mRemotePath;
        break;

      case SFTP_DOWNLOAD_DATA:
        std::cerr << "DOWNLOAD DATA remote=" << mRemotePath;
        break;

      default:
        std::cerr << "UNKNOWN ";
        break;
    }

    std::cerr << std::endl;
#endif
  }

  void
  showStatus() const {
#ifdef DEBUG_SFTP
    std::cerr << "JOB ";
    if (mError.empty()) {
      std::cerr << "OK";
    } else {
      std::cerr << "ERROR:" << mError;
    }

    std::cerr << std::endl;
#endif
  }

  ISftpSession::SftpTransaction mTransaction;
  std::string mRemotePath;
  std::string mLocalPath;
  std::string mData;
  int mDataFileOptions;
  ISftpSession::SftpFileCallback mFileCallback;
  ISftpSession::SftpDataCallback mDataCallback;
  JobType mType;
  std::string mError;
  unsigned mTimeout;
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SftpSession::SftpSession(std::shared_ptr<ISshSession> ssh)
    : TaskEvent(Task::PRIORITY_MIN, Task::DEFAULT_STACK, "SFTP", "SFTP"),

      mMutex(),
      mSsh(ssh),
      mConnected(false),
      mSession(nullptr),
      mError(""),
      mJobs(),
      mDataBuffer((char*)calloc(BUFF_LEN, sizeof(char))) {
#ifdef DEBUG_SFTP
  std::cerr << "NEW SftpSession" << std::endl;
#endif

  if (!mSsh->isAuthenticated()) {
    setError("SSH not authenticated");
    return;
  }

  mSession = sftp_new(mSsh->session());
  if (mSession == nullptr) {
    setError(
        "Error allocating SFTP session: " +
        std::string(ssh_get_error(mSsh->session())));
    return;
  }

  int rc = sftp_init(mSession);
  if (rc != SSH_OK) {
    setError(
        "Error initialising SFTP session: " +
        std::string(ssh_get_error(mSsh->session())));
    return;
  }

  mConnected = true;
}

//-------------------------------------------------------------------------------------------------------------
SftpSession::~SftpSession() {
#ifdef DEBUG_SFTP
  std::cerr << "DEL SftpSession" << std::endl;
#endif
  disconnect();

  free(mDataBuffer);
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::disconnect() {
  if (mSession) {
#ifdef DEBUG_SFTP
    std::cerr << "DEL SftpSession : sftp_free" << std::endl;
#endif
    sftp_free(mSession);
  }
  mSession = nullptr;
  mSsh.reset();
  mConnected = false;
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::setDebug(unsigned level) {
  mSsh->setDebug(level);
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpSession::error() {
  std::string tmp;
  swap(mError, tmp);
  return tmp;
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::isConnected() const {
  return mConnected;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpSession::user() const {
  return mSsh->user();
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpSession::host() const {
  return mSsh->host();
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::fileUpload(
    const std::string& remoteFile,
    const std::string& localFile,
    ISftpSession::SftpFileCallback complete,
    unsigned timeoutSecs) {
  if (!mConnected) {
    setError("SFTP session not created");
    return false;
  }

  if (!Path::exists(localFile)) {
    setError("Unable to read local file");
    return false;
  }

  SftpPath sp(remoteFile);
  if (!sp.isValid()) {
    setError(sp.error());
    return false;
  }

  addMkdir(sp.path());

  std::shared_ptr<Job> job(std::make_shared<Job>());
  job->mTransaction = SFTP_UPLOAD_FILE;
  job->mRemotePath = sp.path();
  job->mLocalPath = localFile;
  job->mFileCallback = complete;
  job->mType = Job::JOB_TRANSACTION;
  job->mTimeout = timeoutSecs;

  {
    std::unique_lock<std::mutex> lock(mMutex);
    mJobs.push_back(job);
  }

  event();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::fileDownload(
    const std::string& remoteFile,
    const std::string& localFile,
    ISftpSession::SftpFileCallback complete,
    unsigned timeoutSecs) {
  if (!mConnected) {
    setError("SFTP session not created");
    return false;
  }

  SftpPath sp(remoteFile);
  if (!sp.isValid()) {
    setError(sp.error());
    return false;
  }

  std::shared_ptr<Job> job(std::make_shared<Job>());
  job->mTransaction = SFTP_DOWNLOAD_FILE;
  job->mRemotePath = sp.path();
  job->mLocalPath = localFile;
  job->mFileCallback = complete;
  job->mType = Job::JOB_TRANSACTION;
  job->mTimeout = timeoutSecs;

  {
    std::unique_lock<std::mutex> lock(mMutex);
    mJobs.push_back(job);
  }

  event();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::dataUpload(
    const std::string& remoteFile,
    const std::string& data,
    ISftpSession::SftpDataCallback complete,
    unsigned timeoutSecs,
    int fileOptions) {
  if (!mConnected) {
    setError("SFTP session not created");
    return false;
  }

  SftpPath sp(remoteFile);
  if (!sp.isValid()) {
    setError(sp.error());
    return false;
  }

  addMkdir(sp.path());

  std::shared_ptr<Job> job(std::make_shared<Job>());
  job->mTransaction = SFTP_UPLOAD_DATA;
  job->mRemotePath = sp.path();
  job->mDataCallback = complete;
  job->mData = data;
  job->mDataFileOptions = fileOptions;
  job->mType = Job::JOB_TRANSACTION;
  job->mTimeout = timeoutSecs;

  {
    std::unique_lock<std::mutex> lock(mMutex);
    mJobs.push_back(job);
  }

  event();
  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::dataDownload(
    const std::string& remoteFile,
    ISftpSession::SftpDataCallback complete,
    unsigned timeoutSecs) {
  if (!mConnected) {
    setError("SFTP session not created");
    return false;
  }

  SftpPath sp(remoteFile);
  if (!sp.isValid()) {
    setError(sp.error());
    return false;
  }

  std::shared_ptr<Job> job(std::make_shared<Job>());
  job->mTransaction = SFTP_DOWNLOAD_DATA;
  job->mRemotePath = sp.path();
  job->mDataCallback = complete;
  job->mData.clear();
  job->mType = Job::JOB_TRANSACTION;
  job->mTimeout = timeoutSecs;

  {
    std::unique_lock<std::mutex> lock(mMutex);
    mJobs.push_back(job);
  }

  event();
  return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::runEvent() {
#ifdef DEBUG_SFTP
  std::cerr << "SftpSession::runEvent()" << std::endl;
#endif

  bool done(true);
  do {
    // get next job
    std::shared_ptr<Job> job;
    {
      std::unique_lock<std::mutex> lock(mMutex);

#ifdef DEBUG_SFTP
      std::cerr << "-- JOBS --" << std::endl;
      for (auto j : mJobs) {
        j->show();
      }
      std::cerr << "----------" << std::endl;
#endif

      if (mJobs.empty())
        break;

      job = mJobs.front();
      mJobs.pop_front();

      // see if more to do
      if (!mJobs.empty())
        done = false;
    }

    // Process this job
    if (job->mType == Job::JOB_MKDIR) {
      handleMkdir(job);
      job->showStatus();
      continue;
    }

    if (job->mTransaction == SFTP_UPLOAD_FILE) {
      handleFileUpload(job);
      job->showStatus();
      continue;
    }
    if (job->mTransaction == SFTP_DOWNLOAD_FILE) {
      handleFileDownload(job);
      job->showStatus();
      continue;
    }
    if (job->mTransaction == SFTP_UPLOAD_DATA) {
      handleDataUpload(job);
      job->showStatus();
      continue;
    }
    if (job->mTransaction == SFTP_DOWNLOAD_DATA) {
      handleDataDownload(job);
      job->showStatus();
      continue;
    }

    // WTF?!
    std::cerr << "Unexpected job" << std::endl;

  } while (!done);

  return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::setError(const std::string& error) {
  if (!mError.empty())
    mError += "\n";
  mError += error;
}

//-------------------------------------------------------------------------------------------------------------
std::string
SftpSession::sshError(const std::string& msg) {
  return std::string(msg) + std::string(ssh_get_error(mSsh->session()));
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::addMkdir(const std::string remotePath) {
  std::string dir(remotePath);
  std::size_t pos(dir.find_last_of("/"));
  if (pos == std::string::npos)
    return;

  std::shared_ptr<Job> job(std::make_shared<Job>());
  job->mType = Job::JOB_MKDIR;
  job->mRemotePath = dir.substr(0, pos);

  std::unique_lock<std::mutex> lock(mMutex);
  mJobs.push_back(job);
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::handleMkdir(std::shared_ptr<Job> job) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << std::endl;
#endif

  int rc = sftp_mkdir(mSession, job->mRemotePath.c_str(), S_IRWXU);
  if (rc == SSH_OK)
    return;

  if (sftp_get_error(mSession) != SSH_FX_FILE_ALREADY_EXISTS) {
    job->mError = sshError("Can't create directory:");
  }

  //    job->mFileCallback(job->mRemotePath, "", SFTP_UPLOAD_FILE, job->mError,
  // false) ;
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::handleFileUpload(std::shared_ptr<Job> job) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << std::endl;
  job->show();
#endif

  int fd = open(job->mLocalPath.c_str(), O_RDONLY);
  if (fd < 0) {
    job->mError = "Unable to read local file";
    job->mFileCallback(
        job->mRemotePath,
        job->mLocalPath,
        SFTP_UPLOAD_FILE,
        job->mError,
        false);
    return;
  }

  struct stat statbuff;
  int protection(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fstat(fd, &statbuff) == 0)
    protection = statbuff.st_mode;

  auto getData = [this, fd](std::string& data, std::string& error) -> bool {
    data.clear();
    error.clear();

    int numRead = read(fd, mDataBuffer, BUFF_LEN);
    if (numRead == 0)
      return true;

    if (numRead < 0) {
      if (numRead == EAGAIN)
        return true;

      error = "Local file read error";
      return false;
    }

    data = std::string(mDataBuffer, mDataBuffer + numRead);
    return true;
  };

  std::shared_ptr<TimeoutTimer> timer;
  if (job->mTimeout > 0) {
    timer = std::make_shared<TimeoutTimer>(std::chrono::seconds(job->mTimeout));
  } else {
    timer = std::make_shared<NullTimeoutTimer>();
  }

  doUpload(job->mRemotePath, protection, getData, job->mError, timer);
  close(fd);

  job->mFileCallback(
      job->mRemotePath,
      job->mLocalPath,
      SFTP_UPLOAD_FILE,
      job->mError,
      timer->isTimedOut());
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::handleFileDownload(std::shared_ptr<Job> job) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << std::endl;
  job->show();
#endif

  sftp_file file = sftp_open(mSession, job->mRemotePath.c_str(), O_RDONLY, 0);
  if (file == nullptr) {
    job->mError = sshError("Can't open file for reading: ");
    job->mFileCallback(
        job->mRemotePath,
        job->mLocalPath,
        SFTP_DOWNLOAD_FILE,
        job->mError,
        false);
    return;
  }

  // copy file permissions
  sftp_attributes stats(sftp_fstat(file));
  if (stats == nullptr) {
    job->mError = sshError("Can't get file stats: ");
    job->mFileCallback(
        job->mRemotePath,
        job->mLocalPath,
        SFTP_DOWNLOAD_FILE,
        job->mError,
        false);
    return;
  }
  sftp_close(file);

  int fd = open(
      job->mLocalPath.c_str(),
      O_WRONLY | O_CREAT | O_TRUNC,
      stats->permissions);
  if (fd < 0) {
    std::string errorstr;
    mDataBuffer[0] = '\0';
    strerror_r(errno, mDataBuffer, BUFF_LEN);
    errorstr = std::string(mDataBuffer);

    job->mError = "Unable to write local file " + errorstr;
    job->mFileCallback(
        job->mRemotePath,
        job->mLocalPath,
        SFTP_DOWNLOAD_FILE,
        job->mError,
        false);
    return;
  }

  auto putData = [fd](const std::string& data, std::string& error) -> bool {
    if (data.empty())
      return true;

    int rc = write(fd, data.c_str(), data.size());
    if (rc < 0) {
      error = "Local file write error";
      return false;
    }

    return true;
  };

  std::shared_ptr<TimeoutTimer> timer;
  if (job->mTimeout > 0) {
    timer = std::make_shared<TimeoutTimer>(std::chrono::seconds(job->mTimeout));
  } else {
    timer = std::make_shared<NullTimeoutTimer>();
  }

  doDownload(job->mRemotePath, putData, job->mError, timer);
  close(fd);

  job->mFileCallback(
      job->mRemotePath,
      job->mLocalPath,
      SFTP_DOWNLOAD_FILE,
      job->mError,
      timer->isTimedOut());
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::handleDataUpload(std::shared_ptr<Job> job) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << std::endl;
  job->show();
#endif

  unsigned index(0);
  auto getData = [&index, job](std::string& data, std::string& error) -> bool {
    data.clear();
    error.clear();

    if (index >= job->mData.size())
      return true;

    unsigned datalen(BUFF_LEN);
    if (datalen > (job->mData.size() - index))
      datalen = job->mData.size() - index;

    data = std::string(job->mData.begin(), job->mData.begin() + datalen);
    index += datalen;
    return true;
  };

  std::shared_ptr<TimeoutTimer> timer;
  if (job->mTimeout > 0) {
    timer = std::make_shared<TimeoutTimer>(std::chrono::seconds(job->mTimeout));
  } else {
    timer = std::make_shared<NullTimeoutTimer>();
  }

  doUpload(
      job->mRemotePath, job->mDataFileOptions, getData, job->mError, timer);
  job->mDataCallback(
      job->mRemotePath, "", SFTP_UPLOAD_DATA, job->mError, timer->isTimedOut());
}

//-------------------------------------------------------------------------------------------------------------
void
SftpSession::handleDataDownload(std::shared_ptr<Job> job) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << std::endl;
  job->show();
#endif

  job->mData.clear();
  auto putData = [job](const std::string& data, std::string& error) -> bool {

#ifdef DEBUG_SFTP
    std::cerr << "handleDataDownload::::putData size=" << data.size()
              << std::endl;
#endif

    if (data.empty())
      return true;

    job->mData += data;
    return true;
  };

  std::shared_ptr<TimeoutTimer> timer;
  if (job->mTimeout > 0) {
    timer = std::make_shared<TimeoutTimer>(std::chrono::seconds(job->mTimeout));
  } else {
    timer = std::make_shared<NullTimeoutTimer>();
  }

  doDownload(job->mRemotePath, putData, job->mError, timer);
  job->mDataCallback(
      job->mRemotePath,
      job->mData,
      SFTP_DOWNLOAD_DATA,
      job->mError,
      timer->isTimedOut());
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::doUpload(
    const std::string& remotePath,
    int fileOptions,
    GetDataFunc getData,
    std::string& error,
    std::shared_ptr<TimeoutTimer> timer) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << " remote=" << remotePath << std::endl;
#endif

  sftp_file file = sftp_open(
      mSession, remotePath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, fileOptions);
  if (file == nullptr) {
    error = sshError("Can't open file for writing: ");
    return false;
  }

  int datalen(0);
  std::string data;
  do {
    if (!getData(data, error)) {
      sftp_close(file);
      return false;
    }

    if (timer->isTimedOut()) {
      error = "Transfer timed out";
      sftp_close(file);
      return false;
    }

    datalen = data.size();
    if (datalen == 0)
      continue;
    int nwritten = sftp_write(file, data.c_str(), datalen);
    if (nwritten != datalen) {
      error = sshError("Can't write data to file: ");
      sftp_close(file);
      return false;
    }

    if (timer->isTimedOut()) {
      error = "Transfer timed out";
      sftp_close(file);
      return false;
    }

  } while (datalen > 0);

  int rc = sftp_close(file);
  if (rc != SSH_OK) {
    error = sshError("Can't close the written file: ");
    return false;
  }

  return true;
}

//-------------------------------------------------------------------------------------------------------------
bool
SftpSession::doDownload(
    const std::string& remotePath,
    PuttDataFunc putData,
    std::string& error,
    std::shared_ptr<TimeoutTimer> timer) {
#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << " remote=" << remotePath << std::endl;
#endif

  sftp_file file = sftp_open(mSession, remotePath.c_str(), O_RDONLY, 0);
  if (file == nullptr) {
    error = sshError("Can't open file for reading: ");
    return false;
  }

  int nbytes(0);
  do {
    nbytes = sftp_read(file, mDataBuffer, BUFF_LEN);
    if (nbytes == 0) {
      break; // EOF
    }

    if (timer->isTimedOut()) {
      error = "Transfer timed out";
      sftp_close(file);
      return false;
    }

    if (nbytes < 0) {
      error = sshError("Error while reading file: ");
      sftp_close(file);
      return false;
    }

    if (!putData(std::string(mDataBuffer, mDataBuffer + nbytes), error)) {
      sftp_close(file);
      return false;
    }

    if (timer->isTimedOut()) {
      error = "Transfer timed out";
      sftp_close(file);
      return false;
    }

  } while (nbytes > 0);

  sftp_close(file);

#ifdef DEBUG_SFTP
  std::cerr << __FUNCTION__ << " DONE" << std::endl;
#endif

  return true;
}
