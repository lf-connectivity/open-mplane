#ifndef _MPLANE_ETNACARRIERSERVERFIXTURE_H_
#define _MPLANE_ETNACARRIERSERVERFIXTURE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      im_fixture.h
 * \brief     Image Management test fixture
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>
#include <string>
#include <memory>

#include "gtest/gtest.h"

#include "IImage.h"
#include "ImageBase.h"
#include "ImageTask.h"

namespace Mplane
{

//-------------------------------------------------------------------------------------------------------------
class WorkingDir {
public:
	static std::string wd ;
	static void getWd() ;
	static void chdirWd() ;
};

//-------------------------------------------------------------------------------------------------------------
// Task used for testing the IImage classes
class TestImageTask : public ImageTask {
public:
	TestImageTask() :
		ImageTask()
	{}

	virtual ~TestImageTask() {}

protected:
    virtual int run() {
    	return 0 ;
    }

};


//-------------------------------------------------------------------------------------------------------------
class ITestImage : public IImage {
public:
	virtual unsigned numFiles() const =0 ;
	virtual bool initialise(std::string& failReason) =0 ;
	virtual bool getAndInstall(std::string& failReason) =0 ;
	virtual bool clean(std::string& failReason) =0 ;
	virtual bool isRunning() const =0 ;
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) =0 ;
	virtual bool setImageName(const std::string& name, std::string& failReason) =0 ;
	virtual bool setInstallDir(const std::string& dir, std::string& failReason) =0 ;
	virtual std::string formatName(const std::string& version, const std::string& buildNumber) =0 ;
    virtual bool isDownloaded(void) =0 ;
    virtual bool isInstalled(void) =0  ;
    virtual void show(std::ostream& os = std::cout) const =0 ;
    virtual std::string info() const =0 ;
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status) =0 ;
    virtual void defaultStatusObject() =0 ;
    virtual void setDownloadFunction(IImage::DownloadFunction download) =0 ;
    virtual void defaultDownloadFunction() =0 ;

	// Allow access to protected methods
    virtual IImage::DownloadFunction getDownloadFunction() const =0 ;
    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const =0 ;
    virtual bool alreadyDownloaded() =0 ;
    virtual bool alreadyInstalled() =0 ;
    virtual bool download(std::string& failReason) =0 ;
    virtual bool check(std::string& failReason) =0 ;
    virtual bool install(std::string& failReason) =0 ;
    virtual bool testDownloadFile(const std::string& filename, const std::string& serverUrl, const std::string& saveDir,
    		std::string& failReason) =0 ;
    virtual bool testCheckFile(const std::string& saveDir,
    		const std::string& filename, const std::string& md5file, std::string& failReason) =0 ;
    virtual bool checkData(std::string& failReason) const =0 ;
    virtual bool isFreeFileSpace(const std::string& dir, unsigned requiredSize, std::string& failReason) const =0 ;
    virtual bool getVersionBuild(const std::string& imageName, std::string& baseName, float& version,
    		unsigned& buildNumber) const =0 ;

    // Test Interface
    virtual void setFreeSpace(bool free) =0 ;
};


//-------------------------------------------------------------------------------------------------------------
template <typename T>
class TestImage : public T, public ITestImage
{
public:
	using super = T ;

	TestImage(ImageTask& task, const std::string& name) :
		T(task, name),
		mFreeSpace(true)
	{}

	TestImage(ImageTask& task) :
		T(task),
		mFreeSpace(true)
	{}

	virtual ~TestImage() {}

	virtual unsigned numFiles() const
	{
		return 1 ;
	}

	virtual bool initialise(std::string& failReason)
	{
		return this->super::initialise(failReason) ;
	}
	virtual bool getAndInstall(std::string& failReason)
	{
		return this->super::getAndInstall(failReason) ;
	}
	virtual bool clean(std::string& failReason)
	{
		return this->super::clean(failReason) ;
	}
	virtual bool isRunning() const
	{
		return this->super::isRunning() ;
	}
	virtual bool setRemoteUrl(const std::string& url, std::string& failReason) override
	{
		return this->super::setRemoteUrl(url, failReason) ;
	}

	virtual bool setImageName(const std::string& name, std::string& failReason) override
	{
		return this->super::setImageName(name, failReason) ;
	}

	virtual bool setInstallDir(const std::string& dir, std::string& failReason) override
	{
		return this->super::setInstallDir(dir, failReason) ;
	}
	virtual std::string formatName(const std::string& version, const std::string& buildNumber)
	{
		return this->super::formatName(version, buildNumber) ;
	}
    virtual bool isDownloaded(void)
    {
		return this->super::isDownloaded() ;
    }
    virtual bool isInstalled(void)
    {
		return this->super::isInstalled() ;
    }
    virtual void show(std::ostream& os = std::cout) const
    {
		this->super::show(os) ;
    }
    virtual std::string info() const
    {
		return this->super::info() ;
    }

    virtual std::shared_ptr<IFileStatus> getStatusObject(void) const
    {
    	return this->super::getStatusObject() ;
    }
    virtual void setStatusObject(std::shared_ptr<IFileStatus> status)
    {
    	this->super::setStatusObject(status) ;
    }
    virtual void defaultStatusObject()
    {
    	this->super::defaultStatusObject() ;
    }

    virtual IImage::DownloadFunction getDownloadFunction(void) const
    {
    	return this->super::getDownloadFunction() ;
    }
    virtual void setDownloadFunction(DownloadFunction download)
    {
    	this->super::setDownloadFunction(download) ;
    }
    virtual void defaultDownloadFunction()
    {
    	this->super::defaultDownloadFunction() ;
    }


    virtual bool usePrevious(std::string failReason) override
	{
    	return this->super::usePrevious(failReason) ;
	}


	// Allow access to protected methods

    virtual bool alreadyDownloaded()
    {
    	return this->super::alreadyDownloaded() ;
    }

    virtual bool alreadyInstalled()
    {
    	return this->super::alreadyInstalled() ;
    }

    virtual bool download(std::string& failReason)
    {
    	return this->super::download(failReason) ;
    }

    virtual bool check(std::string& failReason)
    {
    	return this->super::check(failReason) ;
    }

    virtual bool install(std::string& failReason)
    {
    	return this->super::install(failReason) ;
    }

    virtual bool testDownloadFile(const std::string& filename, const std::string& serverUrl, const std::string& saveDir,
    		std::string& failReason)
    {
    	return this->downloadFile(filename, serverUrl, saveDir, failReason) ;
    }

    virtual bool testCheckFile(const std::string& saveDir,
    		const std::string& filename, const std::string& md5file, std::string& failReason)
	{
    	return this->checkFile(saveDir, filename, md5file, failReason) ;
	}

    virtual bool checkData(std::string& failReason) const
    {
    	return this->super::checkData(failReason) ;
    }

    virtual bool isFreeFileSpace(const std::string& dir, unsigned requiredSize, std::string& failReason) const
    {
    	return mFreeSpace ;
    }

    virtual bool getVersionBuild(const std::string& imageName, std::string& baseName, float& version, unsigned& buildNumber) const
    {
    	return this->super::getVersionBuild(imageName, baseName, version, buildNumber) ;
    }


	// Test interface
    virtual void setFreeSpace(bool free)
	{
    	mFreeSpace = free ;
	}

public:
    bool mFreeSpace ;
};


//-------------------------------------------------------------------------------------------------------------
/*! @brief Test fixture for Image Management
 *
 *  This class uses the Google test facilities to perform unit testing
 */
class ImTestFixture : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp();

    /*! @brief Tear down the test
     */
    virtual void TearDown();

    // Image class test methods
    virtual void MethodsSimple(std::shared_ptr<IImage> ib) ;
    virtual void InstallChecks(std::shared_ptr<IImage> ib);
    virtual void Download(std::shared_ptr<IImage> ib, const std::string& fname, const std::string& currentLink = "current");
    virtual void DownloadBad(std::shared_ptr<IImage> ib, const std::string& fname);
    virtual void Methods(std::shared_ptr<ITestImage> ib, const std::string& fname,
    		const std::string& currentLink = "current",
    		const std::string& previousLink = "previous");
    virtual void Clean(std::shared_ptr<IImage> ib,
    		const std::string& currentLink = "current",
    		const std::string& previousLink = "previous");

    void clearStatus(void) ;
    std::string getStatus(void) ;
    void writeStatus(const std::string& status) ;


    static std::string getTempDir(void) ;
    static std::string getDownloadDir(void) ;
    static std::string getNorDir(void) ;
    static std::string getNandDir(void) ;

protected:
    std::string mImageType ;
    TestImageTask mImageTask ;

private:
    // directories
    static std::string mTempDir ;
    static std::string mDownloadDir ;
    static std::string mNorDir ;
    static std::string mNandDir ;

    std::string mStatus ;
};



} /* namespace Mplane */

#endif
