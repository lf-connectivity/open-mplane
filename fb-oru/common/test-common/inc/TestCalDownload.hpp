/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestCalDownload.hpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef TEST_COMMON_INC_TESTCALDOWNLOAD_HPP_
#define TEST_COMMON_INC_TESTCALDOWNLOAD_HPP_

#include <vector>
#include <string>
#include <memory>

#include "ICalDownload.h"


namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
class ITestCalDownload : public ICalDownload {
public:

	// ICalDownload
	virtual bool initialise(std::string& failReason) =0 ;
	virtual bool getAndInstall(const std::string& remoteFilename, std::string& failReason) =0 ;
	virtual bool getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason) =0 ;
	virtual bool isRunning() const =0 ;
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) =0 ;
    virtual void show(std::ostream& os = std::cout) const =0 ;
	virtual std::string getInstallFilePath() const =0 ;
	virtual std::string getInstallFileName() const =0 ;

	// Allow access to protected methods
	virtual bool setInstallFileName(const std::string& name, std::string& failReason) =0 ;
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) =0 ;

	virtual bool testInjectInstallDir(const std::string& path, std::string& failReason) =0 ;

    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const =0 ;

	virtual std::string getName() const =0 ;
	virtual std::string getTypeName() const =0 ;

    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) =0 ;
	virtual std::shared_ptr<IFileMgrWriter> getCalFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
			std::string& failReason) =0 ;
	virtual void startTcpTransfer(TcpCalTransfer calTransfer) =0 ;
	virtual void endTcpTransfer() =0 ;

	// Test Interface
    virtual void setFreeSpace(bool free) =0 ;
    virtual void setNandDir(const std::string& dir) =0 ;

};

/*!
 * \class  TestCalDownload
 * \brief
 * \details
 *
 */
//-------------------------------------------------------------------------------------------------------------
template <typename T>
class TestCalDownload : public T, public ITestCalDownload
{
public:
	using super = T ;

	static std::string mNandDir ;

	TestCalDownload(const std::string& name) :
		T(name),
		mFreeSpace(true)
	{}

	TestCalDownload() :
		T(),
		mFreeSpace(true)
	{}

	virtual ~TestCalDownload() {}

//    virtual std::size_t getHash() {
//        return this->super::getHash();
//    }

    virtual std::string getName() const {
        return this->super::getName();
    }

    virtual std::string getTypeName() const {
        return this->super::getTypeName();
    }

	virtual bool getAndInstall(const std::string& remoteFilename, std::string& failReason) override {
		return this->super::getAndInstall(remoteFilename, failReason) ;
	}

	virtual bool getAndInstall(const std::string& remoteFilename, std::shared_ptr<IFileStatus> status, std::string& failReason) override {
		return this->super::getAndInstall(remoteFilename, status, failReason) ;
	}


	virtual bool initialise(std::string& failReason) override {
		return this->super::initialise(failReason) ;
	}
	virtual bool isRunning() const override {
		return this->super::isRunning() ;
	}
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) override {
		return this->super::setRemoteUrl(url, failReason) ;
	}
    virtual void show(std::ostream& os = std::cout) const override {
		this->super::show(os) ;
    }
	virtual std::string getInstallFilePath() const override {
		return this->super::getInstallFilePath() ;
	}
	virtual std::string getInstallFileName() const override {
		return this->super::getInstallFileName() ;
	}

	// Allow access to protected methods
	virtual bool setInstallFileName(const std::string& name, std::string& failReason) override {
		return this->super::setInstallFileName(name, failReason) ;
	}
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override {

		std::string installDir(dir) ;

		// hijack any attempts to write to root /nandflash dir
		if (dir.find("/nandflash") == 0)
		{
			// Create a user-specific temp directory in which to run tests - needs to match up with test fixture
			installDir = mNandDir + "/cal" ;
		}

	    return this->super::setInstallDir(installDir, failReason) ;
	}

	virtual bool testInjectInstallDir(const std::string& path, std::string& failReason)
	{
		return this->super::testInjectInstallDir(path, failReason) ;
	}

	std::shared_ptr<IFileStatus> getStatusObject(void) const
	{
		return this->super::getStatusObject() ;
	}

    void setStatusObject(std::shared_ptr<IFileStatus> status)
    {
		this->super::setStatusObject(status) ;
    }
    virtual void addPath(unsigned path, const std::string& calDate) override
    {
    	this->super::addPath(path, calDate) ;
    }

    virtual void showTemperatures(std::ostream& os = std::cout) const override
    {
    }
    virtual void addTemperature(unsigned path, const float& calInitialTemp) override
    {
    }

	std::shared_ptr<IFileMgrWriter> getCalFileWriter(std::shared_ptr<IFileStatus> statusObj, unsigned fileSize,
			std::string& failReason)
	{
		return this->super::getCalFileWriter(statusObj, fileSize, failReason) ;
	}
	void startTcpTransfer(TcpCalTransfer calTransfer)
	{
		this->super::startTcpTransfer(calTransfer) ;
	}
	void endTcpTransfer()
	{
		this->super::endTcpTransfer() ;
	}

	// Test interface
    virtual void setFreeSpace(bool free)
	{
    	mFreeSpace = free ;
	}

    virtual void setNandDir(const std::string& dir)
    {
    	mNandDir = dir ;
    }

public:
    bool mFreeSpace ;
};

template <typename T>
std::string TestCalDownload<T>::mNandDir = "/tmp/nandflash" ;


}

#endif /* TEST_COMMON_INC_TESTCALDOWNLOAD_HPP_ */
