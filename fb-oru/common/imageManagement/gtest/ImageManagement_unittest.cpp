/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ImageManagement_unittest.cpp
 * \brief     Google Test of ImageManagement
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the ImageManagement class.
 *
 */

#include <gtest/gtest.h>

#include <stdlib.h>

#include <string>
#include <iostream>
#include <memory>

#include "Path.h"
#include "IBootEnv.h"

#include "im_fixture.h"
#include "ImageManagement.h"

using namespace Mplane;

using namespace std;


//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class ImageMgrTest : public ImTestFixture
{
public:
	using super = ImTestFixture ;

    virtual void SetUp()
    {
    	this->super::SetUp() ;

    	// tell test fixture that we're testing manager
    	mImageType = "mgr" ;
    }


    bool checkInstallApp(const std::string& app)
    {
        std::string link ;
        if (!Path::exists(getNandDir() + "/app-images/current"))
        	return false ;
        if (!Path::isLink(getNandDir() + "/app-images/current"))
        	return false ;

        Path::readLink(getNandDir() + "/app-images/current", link) ;
        if (std::string(getNandDir() + "/app-images/" + app) != link)
        	return false ;
        if (!Path::exists(getNandDir() + "/app-images/" + app))
        	return false ;
        if (!Path::isFile(getNandDir() + "/app-images/" + app))
        	return false ;
        if (!Path::exists(getNandDir() + "/app-images/" + app + ".md5"))
        	return false ;
        if (!Path::isFile(getNandDir() + "/app-images/" + app + ".md5"))
        	return false ;

        return true ;
    }

    bool checkInstallLib(const std::string& lib)
    {
        std::string link ;
        if (!Path::exists(getNandDir() + "/lib-images/current"))
        	return false ;
        if (!Path::isLink(getNandDir() + "/lib-images/current"))
        	return false ;

        Path::readLink(getNandDir() + "/lib-images/current", link) ;
        if (std::string(getNandDir() + "/lib-images/" + lib) != link)
        	return false ;
        if (!Path::exists(getNandDir() + "/lib-images/" + lib))
        	return false ;
//        if (!Path::isFile(getNandDir() + "/lib-images/" + lib))
//        	return false ;
        if (!Path::exists(getNandDir() + "/lib-images/" + lib + ".md5"))
        	return false ;
//        if (!Path::isFile(getNandDir() + "/lib-images/" + lib + ".md5"))
//        	return false ;

        return true ;
    }

    bool checkInstallPkg(const std::string& pkg)
    {
        std::string link ;
        if (!Path::exists(getNandDir() + "/pkg-images/current"))
        	return false ;
        if (!Path::isLink(getNandDir() + "/pkg-images/current"))
        	return false ;

        Path::readLink(getNandDir() + "/pkg-images/current", link) ;
        if (std::string(getNandDir() + "/pkg-images/" + pkg) != link)
        	return false ;
        if (!Path::exists(getNandDir() + "/pkg-images/" + pkg))
        	return false ;
        if (!Path::isFile(getNandDir() + "/pkg-images/" + pkg))
        	return false ;
        if (!Path::exists(getNandDir() + "/pkg-images/" + pkg + ".md5"))
        	return false ;
        if (!Path::isFile(getNandDir() + "/pkg-images/" + pkg + ".md5"))
        	return false ;

        return true ;
    }

    bool checkInstallOs(const std::string& os, unsigned bank)
    {
        std::string link ;

        if (!Path::exists(getNandDir() + "/os-images/" + os + ".md5"))
        	return false ;
        if (!Path::isFile(getNandDir() + "/os-images/" + os + ".md5"))
        	return false ;
        if (!Path::exists(getNandDir() + "/os-images/pImage" + std::to_string(bank)))
        	return false ;
        if (!Path::isLink(getNandDir() + "/os-images/pImage" + std::to_string(bank)))
        	return false ;

        Path::readLink(getNandDir() + "/os-images/pImage" + std::to_string(bank), link) ;
        if (std::string(getNandDir() + "/os-images/" + os + ".md5") != link)
        	return false ;
        if (!Path::exists(getNandDir() + "/os-images/dtb" + std::to_string(bank)))
        	return false ;
        if (!Path::isLink(getNandDir() + "/os-images/dtb" + std::to_string(bank)))
        	return false ;

        Path::readLink(getNandDir() + "/os-images/dtb" + std::to_string(bank), link) ;
        if (std::string(getNandDir() + "/os-images/" + os + ".md5") != link)
        	return false ;

        return true ;
    }


    void installPkgCheckFiles(const std::string& pkgnum)
    {
    	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

        std::string failReason ;

        std::cerr << "== INSTALL " << pkgnum << " ==" << std::endl ;

        // Install with status updates
        clearStatus() ;
        EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-"+pkgnum+".pkg",
           	IFileStatus::simpleOutput([this](const std::string& status){ writeStatus(status); }),
    		failReason)
        ) ;
        if (!failReason.empty())
        	std::cerr << "FAIL: " << failReason << std::endl ;
        failReason.clear() ;


        std::string status(getStatus()) ;
        std::cerr << "STATUS: " << status << std::endl ;

        // Expect no error
        EXPECT_TRUE(im->isDownloadOk(failReason)) ;
        if (!failReason.empty())
        	std::cerr << "FAIL: " << failReason << std::endl ;
        failReason.clear() ;

        // show installed
        im->show() ;


        // Should now have installed app/lib/os
        std::string link ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/current")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/app-images/current")) ;
        Path::readLink(getNandDir() + "/app-images/current", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-APP.tgz"), link) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-APP.tgz")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-APP.tgz")) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-APP.tgz.md5")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-APP.tgz.md5")) ;

        EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
        Path::readLink(getNandDir() + "/lib-images/current", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz"), link) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz")) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5")) ;

        EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/os.150-sprice.tgz.md5")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/os-images/os.150-sprice.tgz.md5")) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/pImage1")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/pImage1")) ;
        Path::readLink(getNandDir() + "/os-images/pImage1", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/os-images/os.150-sprice.tgz.md5"), link) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/dtb1")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/dtb1")) ;
        Path::readLink(getNandDir() + "/os-images/dtb1", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/os-images/os.150-sprice.tgz.md5"), link) ;

        EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/current")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
        Path::readLink(getNandDir() + "/pkg-images/current", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/pkg-images/FTU-sprice-"+pkgnum+".pkg"), link) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-sprice-"+pkgnum+".pkg")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-"+pkgnum+".pkg")) ;
        EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-sprice-"+pkgnum+".pkg.md5")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-"+pkgnum+".pkg.md5")) ;
    }


    void libIsLinked(const std::string& pkgnum, const std::string& libBaseNum)
    {
        std::string link ;

        EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz.md5")) ;
        EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz.md5list")) ;

        EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5")) ;
        EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5list")) ;
        Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz"), link) ;
        Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz.md5"), link) ;
        Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5list", link) ;
        EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+libBaseNum+"-LIB.tgz.md5list"), link) ;
    }


    void libRemoved(const std::string& pkgnum)
    {
        EXPECT_FALSE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz")) ;
        EXPECT_FALSE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5")) ;
        EXPECT_FALSE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-"+pkgnum+"-LIB.tgz.md5list")) ;
    }

};


//-------------------------------------------------------------------------------------------------------------
class TestImageManagement : public ImageManagement {
public:
	TestImageManagement() :
		ImageManagement()
	{
	    // Create a user-specific temp directory in which to run tests - needs to match up with test fixture
		std::string nandDir( ImTestFixture::getNandDir() );

	    // Amend the install directory for each object
		std::string failReason ;
		getImage(IImageTypes::IMAGE_APPLICATION)->setInstallDir(nandDir + "/app-images", failReason) ;
		getImage(IImageTypes::IMAGE_LIBRARY)->setInstallDir(nandDir + "/lib-images", failReason) ;
		getImage(IImageTypes::IMAGE_ROS)->setInstallDir(nandDir + "/os-images", failReason) ;
		getImage(IImageTypes::IMAGE_FPGA)->setInstallDir(nandDir + "/fpga-images", failReason) ;
		getImage(IImageTypes::IMAGE_PACKAGE)->setInstallDir(nandDir + "/pkg-images", failReason) ;
	}

	virtual ~TestImageManagement() {}
};

std::shared_ptr<IImageManagement> IImageManagement::getInstance()
{
	static std::shared_ptr<IImageManagement> instance(new TestImageManagement()) ;
	return instance ;
}

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, MethodsSimple)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<ImageManagement> im(new TestImageManagement) ;

    std::string failReason ;

    im->show() ;
    im->setUbootInstall(true, failReason) ;
    im->setRemoteUrl("http://server-of-great-repute", failReason) ;
    im->isDownloading() ;
    im->isDownloadOk(failReason) ;

    im->cleanImages(IImageTypes::IMAGE_LIBRARY, failReason);


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, ArgChecks)
{
	std::shared_ptr<ImageManagement> im(new TestImageManagement) ;
	im->start() ;

    std::string failReason ;

    im->show() ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    // fail because server url not set
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_LIBRARY, "ETNA-AXIS-FTU-TDD-CPRI-0.1-3-LIB.tgz", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // fail because file not found - will start ok
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_LIBRARY, "ETNA-AXIS-FTU-TDD-CPRI-1.1-2-LIB.tgz", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // wait for complete
    endSignal->wait() ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;



    // should work
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_LIBRARY, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // should be running for a few secs
    EXPECT_TRUE(im->isDownloading()) ;

    // wait for complete
    endSignal->wait() ;

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    im->show() ;

    // Should now have installed lib
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;


    // Run again - should skip download
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_LIBRARY, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // wait a sec
    sleep(1) ;

    // should be complete
    EXPECT_FALSE(im->isDownloading()) ;

    // wait for complete
    endSignal->wait() ;

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    im->show() ;

    // Should now have installed lib
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;


    // stop
	std::cerr << "Stopping task..." << std::endl ;
	im->shutdown() ;
}


#if 0
//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, Singleton)
{
	// Check multiple instances only start once
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;
	std::shared_ptr<IImageManagement> im2(IImageManagement::getInstance()) ;
	std::shared_ptr<IImageManagement> im3(IImageManagement::getInstance()) ;

    std::string failReason ;

    im->show() ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    // should work
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_LIBRARY, "ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz", failReason, endSignal) ) ;

    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // should be running for a few secs
    EXPECT_TRUE(im->isDownloading()) ;

    // wait for complete
    endSignal->wait() ;

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    im->show() ;

    // Should now have installed lib
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;

}
#endif



//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, Package)
{

	// Check multiple instances only start once
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;
	std::shared_ptr<IImageManagement> im2(IImageManagement::getInstance()) ;
	std::shared_ptr<IImageManagement> im3(IImageManagement::getInstance()) ;

	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;

    // Active BANK should be BANK1
    EXPECT_EQ(IImageTypes::OS_BANK1, im->getOsBank()) ;

    // bootenv should be BANK1
    EXPECT_EQ("1", bootEnv->getVar("activeos")) ;
    EXPECT_EQ("run boot1", bootEnv->getVar("bootcmd")) ;


    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;
    Path::removeDirContents(getNorDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;


    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;

    // Install with status updates
    clearStatus() ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-249.pkg",
    	IFileStatus::simpleOutput([this](const std::string& status){ writeStatus(status); }),
		failReason)
    ) ;
    std::string status(getStatus()) ;
    std::cerr << "STATUS: " << status << std::endl ;

    std::vector<std::string> expectedStatus{
		"Download: FTU-sprice-249.pkg",
		"Download: FTU-sprice-249.pkg.md5",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz.md5",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list",
		"Download: os.150-sprice.tgz",
		"Download: os.150-sprice.tgz.md5",
		"Flash: pImage.150-sprice [boot1]",
		"Flash: axis-dtb.150-sprice [dtb1]",
    } ;

    status = getStatus() ;
    for (auto expect : expectedStatus)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) != std::string::npos) ;
    }

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // show installed
    im->show() ;

    // Create a null os file in the download area
    Path::mkpath("/tmp/os-temp") ;
    system("touch /tmp/os-temp/os.150-sprice.tgz") ;

    // create some null files
    system("touch /tmp/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ;
    system("touch /tmp/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ;


    // Should now have installed app/lib/os
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 2) ) ;

    // Check NOR has been "flashed"
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot1/pImage.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb1/axis-dtb.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.150-sprice")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/u-boot/uboot.150-sprice")) ;

    // Active BANK should still be BANK1
    EXPECT_EQ(IImageTypes::OS_BANK1, im->getOsBank()) ;

    // But the bootenv should have switched to BANK2
    EXPECT_EQ("2", bootEnv->getVar("activeos")) ;
    EXPECT_EQ("run boot2", bootEnv->getVar("bootcmd")) ;


    //-----------------------------------------------------------------------
    // Now install new package with different OS -> BANK2 again
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // check install
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-0.0-35.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
	EXPECT_TRUE( checkInstallOs("os.30-ROS_FTU.tgz", 2) ) ;

    // Check NOR has been "flashed"
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot1/pImage.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb1/axis-dtb.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;

    // Should be the same
    EXPECT_EQ(IImageTypes::OS_BANK1, im->getOsBank()) ;
    EXPECT_EQ("2", bootEnv->getVar("activeos")) ;
    EXPECT_EQ("run boot2", bootEnv->getVar("bootcmd")) ;


    // Now try rdownloading FTU-sprice-252.pkg (os.150) - should just switch OS back to BANK1
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-252.pkg", failReason) ) ;

    // check install
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-sprice-252.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
	EXPECT_TRUE( checkInstallOs("os.30-ROS_FTU.tgz", 2) ) ;

    // Check NOR has been "flashed"
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot1/pImage.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb1/axis-dtb.150-sprice")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/boot2/pImage.30-ROS_FTU")) ;
    EXPECT_TRUE(Path::exists(getNorDir() + "/dtb2/axis-dtb.30-ROS_FTU")) ;
    EXPECT_FALSE(Path::exists(getNorDir() + "/u-boot/uboot.30-ROS_FTU")) ;

    // Should have switched active back to BANK1 to use os.150
    EXPECT_EQ(IImageTypes::OS_BANK1, im->getOsBank()) ;
    EXPECT_EQ("1", bootEnv->getVar("activeos")) ;
    EXPECT_EQ("run boot1", bootEnv->getVar("bootcmd")) ;







    std::cerr << "NAND: " << getNandDir() << std::endl ;
}




//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, PackageFail)
{
	std::shared_ptr<ImageManagement> im(new TestImageManagement) ;
    std::shared_ptr<Conditional> endSignal(new Conditional) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;

    std::cerr << "== Expect Fail (bad package) ==" << std::endl ;
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ) ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-666.pkg", failReason) ) ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // will have failed
    EXPECT_FALSE(Path::exists(getNandDir() + "/pkg-images/current")) ;
    EXPECT_FALSE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_FALSE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-666.pkg")) ;
    EXPECT_FALSE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-666.pkg")) ;
    EXPECT_FALSE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-666.pkg.md5")) ;
    EXPECT_FALSE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-666.pkg.md5")) ;



    std::cerr << "== Expect Fail ==" << std::endl ;
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ) ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // will have failed but package should now have downloaded
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;

    // Run again - should still fail
    std::cerr << "== Expect Fail Again ==" << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;


    // Switch to valid package - should now work
    std::cerr << "== Expect Pass ==" << std::endl ;
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;

    // Should now have installed app/lib/os
    std::string link ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/app-images/current")) ;
    Path::readLink(getNandDir() + "/app-images/current", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;
//    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
//    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    Path::readLink(getNandDir() + "/lib-images/current", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/pImage1")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/pImage1")) ;
    Path::readLink(getNandDir() + "/os-images/pImage1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/dtb1")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/dtb1")) ;
    Path::readLink(getNandDir() + "/os-images/dtb1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5"), link) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;

    // stop
	std::cerr << "Stopping task..." << std::endl ;
	im->shutdown() ;
}




//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, PackagePartFail)
{
	// NOTE: Need to manipulate via Singleton otherwise we aren't accessing the same Image objects that the Package Image object uses!
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;

    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;

    // APP fail
    im->getImage(IImageTypes::IMAGE_APPLICATION)->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ;
    im->getImage(IImageTypes::IMAGE_LIBRARY)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_ROS)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;

    im->showDetail() ;

    // Package will download but individual images will fail
    std::cerr << "==== Expect Fail (APP) ====" << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;

    im->showDetail() ;

    // LIB fail
    im->getImage(IImageTypes::IMAGE_APPLICATION)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_LIBRARY)->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ;
    im->getImage(IImageTypes::IMAGE_ROS)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;


    // Package will download but individual images will fail
    std::cerr << "==== Expect Fail (LIB) ====" << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;


    // OS fail
    im->getImage(IImageTypes::IMAGE_APPLICATION)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_LIBRARY)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_ROS)->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ;


    // Package will download but individual images will fail
    std::cerr << "==== Expect Fail (LIB) ====" << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect error
    EXPECT_FALSE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "EXPECTED: " << failReason << std::endl ;
    failReason.clear() ;



    im->getImage(IImageTypes::IMAGE_APPLICATION)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_LIBRARY)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;
    im->getImage(IImageTypes::IMAGE_ROS)->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ;


    std::cerr << "==== Expect Success ====" << std::endl ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-0.0-35.pkg", failReason) ) ;

    // Expect no error
    EXPECT_TRUE(im->isDownloadOk(failReason)) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    // Should now have installed app/lib/os
    std::string link ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/app-images/current")) ;
    Path::readLink(getNandDir() + "/app-images/current", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;
//    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz")) ;
//    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz.md5")) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    Path::readLink(getNandDir() + "/lib-images/current", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;
    EXPECT_EQ(1887039u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz")) ;
    EXPECT_EQ(72u, Path::fileSize(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz.md5")) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/pImage1")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/pImage1")) ;
    Path::readLink(getNandDir() + "/os-images/pImage1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5"), link) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/os-images/dtb1")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/dtb1")) ;
    Path::readLink(getNandDir() + "/os-images/dtb1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.30-ROS_FTU.tgz.md5"), link) ;

    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg")) ;
    EXPECT_TRUE(Path::exists(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-0.0-35.pkg.md5")) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, AlreadyDownloaded)
{
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    std::cerr << "NAND dir: " << getNandDir() << std::endl ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;


    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;

    // == INSTALL PACKAGE 249 ===

    std::cerr << "== INSTALL 249 ==" << std::endl ;
    installPkgCheckFiles("249") ;

    std::string status(getStatus()) ;
    std::cerr << "STATUS: " << status << std::endl ;

    std::vector<std::string> expectedStatus{
		"Download: FTU-sprice-249.pkg ",
		"Download: FTU-sprice-249.pkg.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list ",
		"Download: os.150-sprice.tgz ",
		"Download: os.150-sprice.tgz.md5 ",
		"Flash: pImage.150-sprice [boot1] ",
		"Flash: axis-dtb.150-sprice [dtb1] ",
    } ;

    status = getStatus() ;
    for (auto expect : expectedStatus)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) != std::string::npos) ;
    }

    // Should now have installed app/lib/os
    std::string link ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5")) ;


    // == INSTALL PACKAGE 252 ===

    std::cerr << "== INSTALL 252 ==" << std::endl ;
    installPkgCheckFiles("252") ;

    // Should use lib 249 as equivalent to 252
    status = getStatus() ;
    std::cerr << "STATUS: <" << status << ">"<< std::endl ;

    std::vector<std::string> expectedStatus2{
		"Download: FTU-sprice-252.pkg ",
		"Download: FTU-sprice-252.pkg.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5list ",
    } ;
    std::vector<std::string> notExpectedStatus2{
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5 ",
		"Download: os.150-sprice.tgz ",
		"Download: os.150-sprice.tgz.md5 ",
		"Flash: pImage.150-sprice [boot1] ",
		"Flash: axis-dtb.150-sprice [dtb1] ",
    } ;

    status = getStatus() ;
    for (auto expect : expectedStatus2)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) != std::string::npos) ;
    }
    for (auto expect : notExpectedStatus2)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) == std::string::npos) ;
    }


    // == SWITCH BACK TO PACKAGE 249 ===

    std::cerr << "== SWITCH TO 249 ==" << std::endl ;

    // Install with status updates
    clearStatus() ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-249.pkg",
       	IFileStatus::simpleOutput([this](const std::string& status){ writeStatus(status); }),
		failReason)
    ) ;
    if (!failReason.empty())
    	std::cerr << "FAIL: " << failReason << std::endl ;
    failReason.clear() ;


    status = getStatus() ;
    std::cerr << "STATUS: <" << status << ">"<< std::endl ;

    std::vector<std::string> expectedStatus3{
    } ;
    std::vector<std::string> notExpectedStatus3{
		"Download: FTU-sprice-249.pkg ",
		"Download: FTU-sprice-249.pkg.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz.md5 ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz ",
		"Download: ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5 ",
		"Download: os.150-sprice.tgz ",
		"Download: os.150-sprice.tgz.md5 ",
		"Flash: pImage.150-sprice [boot1] ",
		"Flash: axis-dtb.150-sprice [dtb1] ",
    } ;

    status = getStatus() ;
    for (auto expect : expectedStatus3)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) != std::string::npos) ;
    }
    for (auto expect : notExpectedStatus3)
    {
    	std::cerr << "Check: " << expect << std::endl ;
    	EXPECT_TRUE(status.find(expect) == std::string::npos) ;
    }


    // == Now check all the links/files are in place ==
    EXPECT_TRUE(Path::isLink(getNandDir() + "/app-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/app-images/previous")) ;
    Path::readLink(getNandDir() + "/app-images/current", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz"), link) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz.md5")) ;
    Path::readLink(getNandDir() + "/app-images/previous", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz"), link) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/app-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-APP.tgz.md5")) ;

    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/current")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/previous")) ;
    Path::readLink(getNandDir() + "/lib-images/current", link) ;

//    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz"), link) ;
//    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz")) ;
//    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5")) ;
//    EXPECT_TRUE(Path::isFile(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list")) ;

    Path::readLink(getNandDir() + "/lib-images/previous", link) ;

//    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz"), link) ;
//    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz")) ;
//    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5")) ;
//    EXPECT_TRUE(Path::isLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5list")) ;
//    Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz", link) ;
//    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz"), link) ;
//    Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5", link) ;
//    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5"), link) ;
//    Path::readLink(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-252-LIB.tgz.md5list", link) ;
//    EXPECT_EQ(std::string(getNandDir() + "/lib-images/ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz.md5list"), link) ;

    libIsLinked("252", "249") ;

    EXPECT_TRUE(Path::isFile(getNandDir() + "/os-images/os.150-sprice.tgz.md5")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/pImage1")) ;
    Path::readLink(getNandDir() + "/os-images/pImage1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.150-sprice.tgz.md5"), link) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/os-images/dtb1")) ;
    Path::readLink(getNandDir() + "/os-images/dtb1", link) ;
    EXPECT_EQ(std::string(getNandDir() + "/os-images/os.150-sprice.tgz.md5"), link) ;

    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/current")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-249.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-249.pkg.md5")) ;
    EXPECT_TRUE(Path::isLink(getNandDir() + "/pkg-images/previous")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-252.pkg")) ;
    EXPECT_TRUE(Path::isFile(getNandDir() + "/pkg-images/FTU-sprice-252.pkg.md5")) ;

}



//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, RevertDueToOsFail)
{
	// NOTE: Need to manipulate via Singleton otherwise we aren't accessing the same Image objects that the Package Image object uses!
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;

    // Install a good version
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-249.pkg", failReason) ) ;
    std::cerr << failReason << std::endl ;

    EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
    EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
    EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
    EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;

    // check OS has also been installed into bank2
    EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 2) ) ;

    // Fail to install new (OS fail)
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-255.pkg", failReason) ) ;
    std::cerr << "EXPECT: " << failReason << std::endl ;
std::cerr << "nand=" << getNandDir() << std::endl ;

	// Should revert back to package 249
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
    EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 2) ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, RevertDueToAppFail)
{
#ifdef DISABLED_DUE_TO_SERVER_ISSUES
	// NOTE: Need to manipulate via Singleton otherwise we aren't accessing the same Image objects that the Package Image object uses!
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;

    // Install a good version
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    std::cerr << "Install good" << std::endl ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-249.pkg", failReason) ) ;
    std::cerr << failReason << std::endl ;

    EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
    EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
    EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
    EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;

    // Fail to install new (app fail)
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    std::cerr << "Fail to install" << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-254.pkg", failReason) ) ;
    std::cerr << "EXPECT: " << failReason << std::endl ;
std::cerr << "nand=" << getNandDir() << std::endl ;

	// Should revert back to package 249
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
#endif
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, RevertDueToLibFail)
{
#ifdef DISABLED_DUE_TO_SERVER_ISSUES

	// NOTE: Need to manipulate via Singleton otherwise we aren't accessing the same Image objects that the Package Image object uses!
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;

    // Install a good version
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    EXPECT_TRUE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-249.pkg", failReason) ) ;
    std::cerr << failReason << std::endl ;

    EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
    EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
    EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
    EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;

    // Fail to install new (lib fail)
    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/bad-images", failReason) ) ;
    std::cerr << failReason << std::endl ;
    EXPECT_FALSE( im->getAndInstall(IImageTypes::IMAGE_PACKAGE, "FTU-sprice-252.pkg", failReason) ) ;
    std::cerr << "EXPECT: " << failReason << std::endl ;
std::cerr << "nand=" << getNandDir() << std::endl ;

	// Should revert back to package 249
	EXPECT_TRUE( checkInstallApp("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-APP.tgz") ) ;
	EXPECT_TRUE( checkInstallLib("ETNA-AXIS-FTU-TDD-CPRI-sprice-249-LIB.tgz") ) ;
	EXPECT_TRUE( checkInstallPkg("FTU-sprice-249.pkg") ) ;
	EXPECT_TRUE( checkInstallOs("os.150-sprice.tgz", 1) ) ;
#endif
}


//-------------------------------------------------------------------------------------------------------------
TEST_F(ImageMgrTest, Clean)
{
	std::shared_ptr<IImageManagement> im(IImageManagement::getInstance()) ;

    std::string failReason ;

    // clean out install
    Path::removeDirContents(getNandDir(), true) ;

    // clean out download areas
    Path::removeDirContents("/tmp/os-temp", true) ;
    Path::removeDirContents("/tmp/tmp", true) ;


    EXPECT_TRUE( im->setRemoteUrl("http://swin-11/~guest/test_files/images", failReason) ) ;


    // == Install packages ===
    installPkgCheckFiles("249") ;

    installPkgCheckFiles("252") ;
    libIsLinked("252", "249") ;

    installPkgCheckFiles("254") ;
    libIsLinked("252", "249") ;
    libIsLinked("254", "249") ;

    installPkgCheckFiles("255") ;
    libIsLinked("252", "249") ;
    libIsLinked("254", "249") ;
    libIsLinked("255", "249") ;

    installPkgCheckFiles("256") ;
    libIsLinked("252", "249") ;
    libIsLinked("254", "249") ;
    libIsLinked("255", "249") ;
    libIsLinked("256", "249") ;

    installPkgCheckFiles("257") ;
    libIsLinked("252", "249") ;
    libIsLinked("254", "249") ;
    libIsLinked("255", "249") ;
    libIsLinked("256", "249") ;
    libIsLinked("257", "249") ;

    // this install will trigger the auto-clean
    installPkgCheckFiles("258") ;

    libIsLinked("256", "249") ;
    libIsLinked("257", "249") ;
    libIsLinked("258", "249") ;

    libRemoved("252") ;
    libRemoved("254") ;
    libRemoved("255") ;


    // Now clean out the images - should remove 256
    EXPECT_TRUE(im->cleanImages(failReason)) ;

    libIsLinked("257", "249") ;
    libIsLinked("258", "249") ;

    libRemoved("252") ;
    libRemoved("254") ;
    libRemoved("255") ;
    libRemoved("256") ;
}
