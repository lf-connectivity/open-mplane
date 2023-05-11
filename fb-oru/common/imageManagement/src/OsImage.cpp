/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OsImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdlib.h>

#include <map>
#include <set>

#include "stringfunc.hpp"
#include "Path.h"
#include "IAppSettingsFactory.h"
#include "AppSettings.h"
#include "IBootEnv.h"

#include "OsImage.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANT
//=============================================================================================================

// Temp directory used for downloading and processing OS images
#ifdef OFF_TARGET
static std::string osTempDir("/tmp/os-temp") ;
#else
static const std::string osTempDir("/tmp/os-temp") ;
#endif

// Names of the links used to reflect NOR contents
static const std::string imageLink("pImage") ;
static const std::string dtbLink("dtb") ;
static const std::string ubootLink("u-boot") ;

// Expected flash times - use 1.5 times for timeout
static const std::map<std::string, unsigned> DefaultFlashTimes{
	{"boot1", 60},
	{"boot2", 60},
	{"dtb1", 2},
	{"dtb2", 2},
	{"u-boot", 4},
} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OsImage::OsImage(ImageTask& task) :
	ImageBase(task, "OsImage"),

	mBootEnv( IBootEnv::getInstance() ),
	mBootBank( getActiveBank() ),
	mActiveBank( mBootBank ),
	mUbootInstall(false)
{
#ifdef OFF_TARGET
	// Insert user name into temp path
    std::string user(::getenv("USER")) ;
    if (user.empty())
    	user = "test" ;
    osTempDir = std::string("/tmp/") + user + "-image/os-temp" ;
#endif
}

//-------------------------------------------------------------------------------------------------------------
OsImage::~OsImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::OsImage::numFiles() const
{
	// .tgz + tgz.md5 ; boot1 dtb1 boot2 dtb2 uboot
	return 7 ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/os-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string OsImage::formatName(const std::string& version, const std::string& buildNumber)
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	std::string name = "os." + buildNumber + "-ROS_" +
		appSettings->getAppString() + ".tgz" ;

	return name ;
}

//-------------------------------------------------------------------------------------------------------------
void OsImage::show(std::ostream& os) const
{
	os << "== OS Image ==" << std::endl << std::endl ;

	os << "Current Settings:" << std::endl ;

	showPadValue(os, "Install Dir", getInstallDir()) ;
	showPadValue(os, "Server URL", getServerUrl()) ;
	showPadValue(os, "Bank", (mBootBank == IImageTypes::OS_BANK1 ? "BANK1" : "BANK2")) ;
	showPadValue(os, "U-Boot Install", (mUbootInstall ? "yes" : "no")) ;
	os << std::endl ;

	this->super::show(os) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string OsImage::info() const
{
	std::string info("") ;

	for (auto linkName : {
				ubootLink,
				bankName(imageLink, IImageTypes::OS_BANK1),
				bankName(dtbLink, IImageTypes::OS_BANK1),
				bankName(imageLink, IImageTypes::OS_BANK2),
				bankName(dtbLink, IImageTypes::OS_BANK2),
	})
	{
		std::string link ;
		if (!Path::readLink(getInstallDir() + "/" + linkName, link))
			continue ;

		if (!info.empty())
			info.append(", ") ;
		info.append(std::string("[") + toUpper(linkName) + "] " + Path::basename(link)) ;
	}
	return info ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::setUbootInstall(bool ubootInstall, std::string& failReason)
{
	mUbootInstall = ubootInstall ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank OsImage::getOsBank(void)
{
	return mBootBank ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::getUbootInstall(void)
{
	return mUbootInstall ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::usePrevious(std::string failReason)
{
	failReason = "Unable to rollback OS" ;
	return false ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool OsImage::alreadyDownloaded()
{
	if (isBankVersionInstalled(mBootBank))
	{
		skipFiles() ; // update file progress
		return true ;
	}

	// see if it's in the other bank
	IImageTypes::OsImageBank otherBank( getOtherBank(mBootBank) ) ;
	if (isBankVersionInstalled(otherBank))
	{
		skipFiles() ; // update file progress
		return true ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::alreadyInstalled()
{
	// If this returns true then all download/install is skipped. So it needs to check the currently active OS bank
	// to ensure the bootenv is set properly for this version.
	return isBankVersionInstalled(mActiveBank) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::download(std::string& failReason)
{
	// ensure install directory is present
	std::string installDir(getInstallDir()) ;
	if (!Path::exists(installDir))
	{
		if (Path::mkpath(installDir) != 0)
		{
			failReason = std::string("Unable to create directory path ") + installDir ;
			return false ;
		}
	}
	if (!Path::exists(osTempDir))
	{
		if (Path::mkpath(osTempDir) != 0)
		{
			failReason = std::string("Unable to create directory path ") + osTempDir ;
			return false ;
		}
	}
	if (!Path::removeDirContents(osTempDir))
	{
		failReason = std::string("Unable to clean directory ") + osTempDir ;
		return false ;
	}

	std::string serverUrl(getServerUrl()) ;
	std::string imageName(getImageName()) ;
	std::string md5Name(getMd5Name()) ;

	// download files
	IImage::DownloadFunction downloadFunc(getDownloadFunction()) ;

	keepAlive() ;
	if (!downloadFunc(imageName, serverUrl, osTempDir, failReason))
		return false ;

	keepAlive() ;
	if (!downloadFunc(md5Name, serverUrl, osTempDir, failReason))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::check(std::string& failReason)
{
	std::string imageName(getImageName()) ;
	std::string md5Name(getMd5Name()) ;

	bool ok = checkFile(osTempDir, imageName, md5Name, failReason) ;

	keepAlive() ;

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::install(std::string& failReason)
{
	IImageTypes::OsImageBank newBank( getOtherBank(mBootBank) ) ;
	IImageTypes::OsImageBank inactiveBank( getOtherBank(mActiveBank) ) ;

	// We will only get to this install method if:
	// a) no other installed OS matches this version
	// b) the currently active OS does not match, but the other OS does match the required version -
	//    in this case don't install anything, just update the active OS bootenv settings
	//
	logDebugVerbose("install() boot=%s, active=%s, inactive=%s, new=%s",
		bankName("BANK", mBootBank).c_str(),
		bankName("BANK", mActiveBank).c_str(),
		bankName("BANK", inactiveBank).c_str(),
		bankName("BANK", newBank).c_str()
	) ;

	// see if this version has already been installed into the inactive bank
	if (isBankVersionInstalled(inactiveBank))
	{
		// the required OS is already in the inactive bank, so just switch to that
		newBank = inactiveBank ;
		skipFiles() ; // update file progress
	}
	else
	{
		if (!mUbootInstall)
			skipUboot() ; // update file progress

		// not already installed, so install the files into the new bank
		if (! installBank(newBank, failReason) )
			return false ;

		// == Update links
		if (!manageLinks(newBank, failReason))
			return false ;


		// == See if the links are set up for the current bank - if not then overwrite this bank with this new image
		if (!isBankInstalled(mBootBank))
		{
			if (!installBank(mBootBank, failReason))
				return false ;

			// == Update links
			if (!manageLinks(mBootBank, failReason))
				return false ;
		}
		else
		{
			skipBank() ; // update file progress
		}


		// == Clean out temp directory
		if (!Path::removeDirContents(osTempDir))
		{
			failReason = std::string("Unable to clean directory ") + osTempDir ;
			return false ;
		}
		Path::rmdir(osTempDir) ;
	}

	// == Update active OS
	if (!setActiveBank(newBank))
	{
		failReason = "Unable to select new OS bank" ;
		return false ;
	}

	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool OsImage::flashNor(const std::string& filePath,
		const std::string& partition, std::string& failReason)
{
	std::string cmd = std::string("flashNor -p ") + partition + " -f " + filePath ;
	logDebugVerbose("CMD: %s", cmd.c_str()) ;

	// report start of flash
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;
	std::string name(Path::basename(filePath) + " [" + partition + "]") ;
	statusObj->start("Flash", name) ;

#ifdef OFF_TARGET

	// For test purposes, copy the image file into a "NOR" area under the partition sub-directory

    std::string user(::getenv("USER")) ;
    if (user.empty())
    	user = "test" ;
    osTempDir = std::string("/tmp/") + user + "-image/os-temp" ;

	std::string norPath = std::string("/tmp/") + user + "-image/"+ "NOR/" + partition ;
	Path::mkpath(norPath) ;
	Path::fileCopy(filePath, norPath) ;

	statusObj->progress(33);
	statusObj->progress(66);
	statusObj->progress(100);
	statusObj->end();
#else
	bool timedOut(false) ;
	unsigned defaultTime(DefaultFlashTimes.at(partition)) ;
    std::shared_ptr<SystemTask> systemTask( new SystemTask() ) ;
    systemTask->start();

	int ret = systemTask->runCmd(cmd,
		[statusObj](unsigned progress) { statusObj->progress(progress); },
		defaultTime,
		(3*defaultTime/2),
		timedOut);
	statusObj->end();
	if (ret != 0)
	{
		if (timedOut)
		{
			failReason = std::string("Timed out while flashing image ") + filePath ;
			return false ;
		}

		failReason = std::string("Failed to flash image ") + filePath + " to NOR" ;
		return false ;
	}
#endif

	keepAlive() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::flashBank(IImageTypes::OsImageBank bank, const std::string& filePath,
		const std::string& partition, std::string& failReason)
{
	return flashNor(filePath, bankName(partition, bank), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::manageLinks(IImageTypes::OsImageBank bank, std::string& failReason)
{
	std::string installDir(getInstallDir()) ;
	std::string md5Name(getMd5Name()) ;

	std::string md5Path = installDir + "/" + md5Name ;

	// Use current settings to create/update the various links that represent the NOR flash programming
	//
	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;
	std::string dtb = installDir + "/" + bankName(dtbLink, bank) ;
	std::string uboot = installDir + "/" + ubootLink ;
	if (Path::exists(pimage))
	{
		Path::remove(pimage) ;
	}
	Path::createLink(pimage, md5Path) ;

	if (Path::exists(dtb))
	{
		Path::remove(dtb) ;
	}
	Path::createLink(dtb, md5Path) ;

	if (mUbootInstall)
	{
		if (Path::exists(uboot))
		{
			Path::remove(uboot) ;
		}
		Path::createLink(uboot, md5Path) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string OsImage::bankName(const std::string& name, IImageTypes::OsImageBank bank) const
{
	std::string bankNameStr(name) ;
	if (bank == IImageTypes::OS_BANK1)
		bankNameStr.append("1") ;
	else
		bankNameStr.append("2") ;

	return bankNameStr ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::isBankInstalled(IImageTypes::OsImageBank bank) const
{
	std::string installDir(getInstallDir()) ;
	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;
	std::string dtb = installDir + "/" + bankName(dtbLink, bank) ;

	logDebugVerbose("isBankInstalled(bank=%s)", bankName("BANK", bank).c_str()) ;

	// pImage link exists
	if (!Path::exists(pimage))
		return false ;

	// dtb link exists
	if (!Path::exists(dtb))
		return false ;

	// links exist so we must have an installation
	logDebugVerbose("Bank is installed") ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::isBankVersionInstalled(IImageTypes::OsImageBank bank) const
{
	std::string installDir(getInstallDir()) ;
	std::string md5Name(getMd5Name()) ;

	std::string md5Path = installDir + "/" + md5Name ;

	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;
	std::string dtb = installDir + "/" + bankName(dtbLink, bank) ;
	std::string uboot = installDir + "/" + ubootLink ;


	// Must ensure all 3 elements are current
	if (!linkCurrent(pimage, md5Path))
		return false ;

	if (!linkCurrent(dtb, md5Path))
		return false ;

	if (mUbootInstall)
		if (!linkCurrent(uboot, md5Path))
			return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool OsImage::installBank(IImageTypes::OsImageBank bank, std::string& failReason)
{
	keepAlive() ;

	std::string installDir(getInstallDir()) ;
	std::string imageName(getImageName()) ;
	std::string md5Name(getMd5Name()) ;

	logDebugVerbose("installBank(bank=%s) image=%s",
		bankName("BANK", bank).c_str(),
		imageName.c_str()
	) ;

	// == Extract contents, and install
	std::string tgzPath = osTempDir + "/" + imageName ;

	// extract
	std::string cmd = std::string("tar xf ") + tgzPath + " -C " + osTempDir ;
    std::shared_ptr<SystemTask> systemTask( new SystemTask() ) ;
    systemTask->start();

	if ( systemTask->runCmd(cmd) != 0 )
	{
		failReason = std::string("Unable to extract OS tar into directory ") + osTempDir ;
		return false ;
	}

	// Work out names of the image files
	keepAlive() ;
	std::vector<std::string> contents(Path::dirContents(osTempDir)) ;
	std::string pImage, dtb, uboot ;
	for (auto file : contents)
	{
		if (file.find("pImage") != std::string::npos)
			pImage = file ;
		else if (file.find("dtb") != std::string::npos)
			dtb = file ;
		else if (file.find("uboot") != std::string::npos)
			uboot = file ;
	}

	logDebugVerbose("Install %s : pImage=%s dtb=%s uboot=%s", imageName.c_str(), pImage.c_str(), dtb.c_str(), uboot.c_str()) ;

	// check for images
	if (pImage.empty())
	{
		failReason = std::string("Unable to extract pImage from tar ") + tgzPath ;
		return false ;
	}
	if (dtb.empty())
	{
		failReason = std::string("Unable to extract DTB from tar ") + tgzPath ;
		return false ;
	}
	if (uboot.empty())
	{
		failReason = std::string("Unable to extract u-boot from tar ") + tgzPath ;
		return false ;
	}

	// Program images
	if (!flashBank(bank, pImage, "boot", failReason))
		return false ;

	if (!flashBank(bank, dtb, "dtb", failReason))
		return false ;

	if (mUbootInstall)
		if (!flashNor(uboot, "u-boot", failReason))
			return false ;

	// == Move MD5 into install directory
	keepAlive() ;
	std::string md5Path = installDir + "/" + md5Name ;
	std::string tempMd5Path = osTempDir + "/" + md5Name ;
	if (!Path::fileCopy(tempMd5Path, md5Path))
	{
		failReason = std::string("Unable to install ") + md5Name ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank OsImage::getOtherBank(IImageTypes::OsImageBank bank) const
{
	if (bank == IImageTypes::OS_BANK1)
		return IImageTypes::OS_BANK2 ;

	return IImageTypes::OS_BANK1 ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank OsImage::getActiveBank() const
{
	std::string activeos(mBootEnv->getVar("activeos")) ;
	logDebugVerbose("activeos=%s", activeos.c_str()) ;
	if (activeos == "2")
		return IImageTypes::OS_BANK2 ;

	return IImageTypes::OS_BANK1 ;
}

//-------------------------------------------------------------------------------------------------------------
bool OsImage::setActiveBank(IImageTypes::OsImageBank bank)
{
	std::string bankStr("1") ;
	if (bank == IImageTypes::OS_BANK2)
		bankStr = "2" ;

	if (!mBootEnv->setVar("activeos", bankStr))
		return false ;

	if (!mBootEnv->setVar("bootcmd", "run boot"+bankStr))
		return false ;

	mActiveBank = bank ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void OsImage::skipUboot()
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// skip uboot
	statusObj->skip() ;
}

//-------------------------------------------------------------------------------------------------------------
void OsImage::skipBank()
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// skip bootX dtbX
	statusObj->skip(2) ;
}

//-------------------------------------------------------------------------------------------------------------
void OsImage::skipFiles()
{
	// skip boot1 dtb1 & boot2 dtb2
	skipBank() ;
	skipBank() ;
	// skip uboot
	skipUboot() ;
}
