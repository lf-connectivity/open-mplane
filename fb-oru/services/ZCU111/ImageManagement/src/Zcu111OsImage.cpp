/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OsImage.cpp
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

#include "Zcu111OsImage.h"

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
static const std::string imageLink("kernel") ;
static const std::string bootLink("boot") ;

// Timing factor (measured on ZCU111 board - 64M took ~2m25s
// (time depends on whether partition is already empty)
const float TIMING_FACTOR( 145.0 / (float)(64*1024*1024) ) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111OsImage::Zcu111OsImage(ImageTask& task) :
	ImageBase(task, "Zcu111OsImage"),

	mBootEnv( IBootEnv::getInstance() ),
	mBootBank( getActiveBank() ),
	mActiveBank( mBootBank ),
	mUbootInstall(false),

	mPartitionNames(),
	mDefaultFlashTimes()
{
#ifdef OFF_TARGET
	// Insert user name into temp path
    std::string user(::getenv("USER")) ;
    if (user.empty())
    	user = "test" ;
    osTempDir = std::string("/tmp/") + user + "-image/os-temp" ;

    mPartitionNames["boot"] = "/dev/mtd0" ;
    mPartitionNames["kernel1"] = "/dev/mtd2" ;
    mPartitionNames["kernel2"] = "/dev/mtd3" ;

    mDefaultFlashTimes["boot"] = 79 ;
    mDefaultFlashTimes["kernel1"] = 145 ;
    mDefaultFlashTimes["kernel2"] = 145 ;
#else
    // Read the mtd proc file to get the partition names and the devices
    /*
     * Read the mtd proc file to get the partition names and the devices. Should be of the form:
     *
     * dev:    size   erasesize  name
     * mtd0: 02300000 00002000 "boot"
     * mtd1: 00040000 00002000 "bootenv"
     * mtd2: 08000000 00002000 "kernel1"
     * mtd3: 08000000 00002000 "kernel2"
     */

	std::string linebuff ;
	std::ifstream infile;
	infile.open("/proc/mtd");
	if (!infile.is_open())
	{
		return ;
	}

	while(infile.good())
	{
		// get the line text string
		std::getline(infile, linebuff);

		// process the line - get partition name
		std::size_t qspos(linebuff.find("\"")) ;
		if (qspos == std::string::npos)
			continue ;
		std::size_t qepos(linebuff.find("\"", qspos+1)) ;
		if (qepos == std::string::npos)
			continue ;
		std::string partition(linebuff.substr(qspos+1, qepos-qspos-1)) ;

		// get the device name
		std::size_t pos(linebuff.find(":")) ;
		if (pos == std::string::npos)
			continue ;
		std::string devName("/dev/" + linebuff.substr(0, pos)) ;

		std::size_t sizepos(linebuff.find_first_not_of(" ", pos+1)) ;
		if (sizepos == std::string::npos)
			continue ;
		unsigned size( (unsigned)strtoul(linebuff.substr(sizepos).c_str(), nullptr, 16) ) ;

		// map partition name to device
		mPartitionNames[partition] = devName ;

		// map partition name to flash time estimated based on partition length
		float timing(size * TIMING_FACTOR) ;
		if (timing < 1.0)
			timing = 1.0 ;
		mDefaultFlashTimes[partition] = (unsigned)timing ;

		logDebugVerbose("Found partition %s device %s size %u (flash time %u)",
				partition.c_str(), devName.c_str(), size, (unsigned)timing) ;
	}

#endif
}

//-------------------------------------------------------------------------------------------------------------
Zcu111OsImage::~Zcu111OsImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::Zcu111OsImage::numFiles() const
{
	// .tgz + tgz.md5 ; kernel1 kernel2 boot
	return 5 ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/os-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111OsImage::formatName(const std::string& version, const std::string& buildNumber)
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	std::string name = "os." + buildNumber + "-ROS_" +
		appSettings->getAppString() + ".tgz" ;

	return name ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111OsImage::show(std::ostream& os) const
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
std::string Zcu111OsImage::info() const
{
	std::string info("") ;

	for (auto linkName : {
		bootLink,
		bankName(imageLink, IImageTypes::OS_BANK1),
		bankName(imageLink, IImageTypes::OS_BANK2),
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
bool Zcu111OsImage::setUbootInstall(bool ubootInstall, std::string& failReason)
{
	mUbootInstall = ubootInstall ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank Zcu111OsImage::getOsBank(void)
{
	return mBootBank ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::getUbootInstall(void)
{
	return mUbootInstall ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::usePrevious(std::string failReason)
{
	failReason = "Unable to rollback OS" ;
	return false ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::alreadyDownloaded()
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
bool Zcu111OsImage::alreadyInstalled()
{
	// If this returns true then all download/install is skipped. So it needs to check the currently active OS bank
	// to ensure the bootenv is set properly for this version.
	return isBankVersionInstalled(mActiveBank) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::download(std::string& failReason)
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
bool Zcu111OsImage::check(std::string& failReason)
{
	std::string imageName(getImageName()) ;
	std::string md5Name(getMd5Name()) ;

	bool ok = checkFile(osTempDir, imageName, md5Name, failReason) ;

	keepAlive() ;

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::install(std::string& failReason)
{
	IImageTypes::OsImageBank newBank( getOtherBank(mBootBank) ) ;
	IImageTypes::OsImageBank inactiveBank( getOtherBank(mActiveBank) ) ;

	// We will only get to this install method if:
	// a) no other installed OS matches this version
	// b) the currently active OS does not match, but the other OS does match the required version -
	//    in this case don't install anything, just update the active OS bootenv settings
	//
	logDebugVerbose("install() kernel=%s, active=%s, inactive=%s, new=%s",
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
bool Zcu111OsImage::flashNor(const std::string& filePath,
		const std::string& partition, std::string& failReason)
{
	auto entry(mPartitionNames.find(partition)) ;
	if (entry == mPartitionNames.end())
	{
		failReason = "Invalid partition" ;
		return false ;
	}

	std::string cmd = std::string("flashcp ") + filePath + " " + entry->second ;
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
	unsigned defaultTime(mDefaultFlashTimes.at(partition)) ;
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
bool Zcu111OsImage::flashBank(IImageTypes::OsImageBank bank, const std::string& filePath,
		const std::string& partition, std::string& failReason)
{
	return flashNor(filePath, bankName(partition, bank), failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::manageLinks(IImageTypes::OsImageBank bank, std::string& failReason)
{
	std::string installDir(getInstallDir()) ;
	std::string md5Name(getMd5Name()) ;

	std::string md5Path = installDir + "/" + md5Name ;

	// Use current settings to create/update the various links that represent the NOR flash programming
	//
	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;
	std::string boot = installDir + "/" + bootLink ;
	if (Path::exists(pimage))
	{
		Path::remove(pimage) ;
	}
	Path::createLink(pimage, md5Path) ;

	if (mUbootInstall)
	{
		if (Path::exists(boot))
		{
			Path::remove(boot) ;
		}
		Path::createLink(boot, md5Path) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Zcu111OsImage::bankName(const std::string& name, IImageTypes::OsImageBank bank) const
{
	std::string bankNameStr(name) ;
	if (bank == IImageTypes::OS_BANK1)
		bankNameStr.append("1") ;
	else
		bankNameStr.append("2") ;

	return bankNameStr ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::isBankInstalled(IImageTypes::OsImageBank bank) const
{
	std::string installDir(getInstallDir()) ;
	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;

	logDebugVerbose("isBankInstalled(bank=%s)", bankName("BANK", bank).c_str()) ;

	// kernel link exists
	if (!Path::exists(pimage))
		return false ;

	// links exist so we must have an installation
	logDebugVerbose("Bank is installed") ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::isBankVersionInstalled(IImageTypes::OsImageBank bank) const
{
	std::string installDir(getInstallDir()) ;
	std::string md5Name(getMd5Name()) ;

	std::string md5Path = installDir + "/" + md5Name ;

	std::string pimage = installDir + "/" + bankName(imageLink, bank) ;
	std::string boot = installDir + "/" + bootLink ;


	// Must ensure all 3 elements are current
	if (!linkCurrent(pimage, md5Path))
		return false ;

	if (mUbootInstall)
		if (!linkCurrent(boot, md5Path))
			return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::installBank(IImageTypes::OsImageBank bank, std::string& failReason)
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
	std::string kernel, boot ;
	for (auto file : contents)
	{
		if (file.find("image.ub") != std::string::npos)
			kernel = file ;
		else if (file.find("BOOT.BIN") != std::string::npos)
			boot = file ;
	}

	logDebugVerbose("Install %s : kernel=%s boot=%s", imageName.c_str(), kernel.c_str(), boot.c_str()) ;

	// check for images
	if (kernel.empty())
	{
		failReason = std::string("Unable to extract kernel from tar ") + tgzPath ;
		return false ;
	}
	if (boot.empty())
	{
		failReason = std::string("Unable to extract boot from tar ") + tgzPath ;
		return false ;
	}

	// Program images
	if (!flashBank(bank, kernel, "kernel", failReason))
		return false ;

	if (mUbootInstall)
		if (!flashNor(boot, "boot", failReason))
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
IImageTypes::OsImageBank Zcu111OsImage::getOtherBank(IImageTypes::OsImageBank bank) const
{
	if (bank == IImageTypes::OS_BANK1)
		return IImageTypes::OS_BANK2 ;

	return IImageTypes::OS_BANK1 ;
}

//-------------------------------------------------------------------------------------------------------------
IImageTypes::OsImageBank Zcu111OsImage::getActiveBank() const
{
	std::string activeos(mBootEnv->getVar("activeos")) ;
	logDebugVerbose("activeos=%s", activeos.c_str()) ;
	if (activeos == "2")
		return IImageTypes::OS_BANK2 ;

	return IImageTypes::OS_BANK1 ;
}

//-------------------------------------------------------------------------------------------------------------
bool Zcu111OsImage::setActiveBank(IImageTypes::OsImageBank bank)
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
void Zcu111OsImage::skipUboot()
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// skip boot
	statusObj->skip() ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111OsImage::skipBank()
{
	std::shared_ptr<IFileStatus> statusObj(getStatusObject()) ;

	// skip bootX
	statusObj->skip(1) ;
}

//-------------------------------------------------------------------------------------------------------------
void Zcu111OsImage::skipFiles()
{
	// skip boot1 & boot2
	skipBank() ;
	skipBank() ;
	// skip boot
	skipUboot() ;
}
