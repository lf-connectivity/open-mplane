/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PkgImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <fstream>
#include <vector>

#include "IImageManagement.h"

#include "IAppSettingsFactory.h"
#include "AppSettings.h"

#include "stringfunc.hpp"
#include "Path.h"
#include "Tokeniser.h"
#include "PkgImage.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PkgImage::PkgImage(ImageTask& task) :
	ImageBase(task, "PkgImage")
{
}

//-------------------------------------------------------------------------------------------------------------
PkgImage::~PkgImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned PkgImage::numFiles() const
{
	// .pkg .pkg.md5
	unsigned numFiles{2} ;

	// add others
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	for (auto type : IImageTypes::typesList())
	{
		if (type == IImageTypes::IMAGE_PACKAGE)
			continue ;

		// get image
		std::shared_ptr<IImage> image(imageMgr->getImage(type) ) ;
		numFiles += image->numFiles() ;
	}

	return numFiles ;
}

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/pkg-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string PkgImage::formatName(const std::string& version, const std::string& buildNumber)
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	std::string name =
			appSettings->getBoardString() + "-" +
			appSettings->getAppString() + "-" +
			version + "-" +
			buildNumber +
			".pkg" ;

	return name ;
}

//-------------------------------------------------------------------------------------------------------------
void PkgImage::show(std::ostream& os) const
{
	os << "== PKG Image ==" << std::endl << std::endl ;

	os << "Current Settings:" << std::endl ;

	showPadValue(os, "Install Dir", getInstallDir()) ;
	showPadValue(os, "Server URL", getServerUrl()) ;
	os << std::endl ;

	this->super::show(os) ;
}

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::setRemoteUrl(const std::string& url, std::string& failReason)
{
	// set this
	if (!this->super::setRemoteUrl(url, failReason))
		return false ;

	// set the others
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;
	for (auto type : IImageTypes::typesList())
	{
		if (type == IImageTypes::IMAGE_PACKAGE)
			continue ;

		// get image
		std::shared_ptr<IImage> image(imageMgr->getImage(type) ) ;

		// set url
		if (!image->setRemoteUrl(url, failReason))
			return false ;

	}
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
unsigned PkgImage::numPackagesInstalled() const
{
	std::vector<std::string> dirContents( Path::dirContents(getInstallDir()) ) ;

	// Count all .pkg files
	unsigned numInstalled{0} ;
	for (auto file : dirContents)
	{
		if (Path::isLink(file))
			continue ;

		if (Path::extension(file) != ".pkg")
			continue ;

		++numInstalled ;
	}

	return numInstalled ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::alreadyDownloaded()
{
//std::cerr << "PACKAGE: alreadyDownloaded?=" << this->super::alreadyDownloaded() << std::endl ;
	// For now just use the default behaviour
	return this->super::alreadyDownloaded() ;
}

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::alreadyInstalled()
{
//std::cerr << "PACKAGE: alreadyInstalled?=" << this->super::alreadyInstalled() << std::endl ;
	// Check that package is already installed
	if (! this->super::alreadyInstalled() )
		return false ;

	// Now need to check the images that make up this package
	std::string current = getInstallDir() + "/" + getCurrentLink() ;
	std::map<IImageTypes::Type, std::string> pkgMap ;
	std::string failReason ;
	if (!readPackageFile(pkgMap, current, failReason))
		return false ;

	// Use the main image management singleton to get the appropriate Image objects
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	// Handle each of the entries
	for (auto mapEntry : pkgMap)
	{
		// get image
		std::shared_ptr<IImage> image(imageMgr->getImage(mapEntry.first) ) ;

		// Is this installed?
		if (!image->isInstalled())
			return false ;
	}

	// having got here then everything is installed
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::install(std::string& failReason)
{
	// Use base to set up links
	if (!this->super::install(failReason))
		return false ;

	// Now need to process the file
	std::string current = getInstallDir() + "/" + getCurrentLink() ;
	std::map<IImageTypes::Type, std::string> pkgMap ;
	if (!readPackageFile(pkgMap, current, failReason))
		return false ;

	// Use the main image management singleton to get the appropriate Image objects
	std::shared_ptr<IImageManagement> imageMgr( IImageManagement::getInstance() ) ;

	// Track which installs worked so we can roll back
	std::vector<std::shared_ptr<IImage>> installedOk ;

	// Handle each of the entries
	bool ok(true);
	for (auto mapEntry : pkgMap)
	{
		// get image
		std::shared_ptr<IImage> image(imageMgr->getImage(mapEntry.first) ) ;

		// tell it to install this file
		if (!image->setImageName(mapEntry.second, failReason))
		{
			ok = false ;
			break ;
		}

		if (!image->getAndInstall(failReason))
		{
			ok = false ;
			break ;
		}

		// ok, so save this object
		installedOk.push_back(image) ;
	}

	// On failure, rollback any installs that were successful
	if (!ok)
	{
		std::string errStr ;

		// roll back the installed images
		for (auto image : installedOk)
		{
			image->usePrevious(errStr) ;
		}

		// roll back the package
		usePrevious(errStr) ;
	}

	return ok ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool PkgImage::readPackageFile(std::map<IImageTypes::Type, std::string>& pkgMap, const std::string& filePath,
		std::string& failReason)
{
	std::string linebuff ;
	std::ifstream infile;
	infile.open(filePath.c_str());
	if (!infile.is_open())
	{
		failReason = "Unable to read package file " + filePath ;
		return false ;
	}

	while(infile.good())
	{
		// get the line text string
		std::getline(infile, linebuff);

		// skip blank lines
		std::string trimmed( trim_left(linebuff)) ;
		trimmed = trim_right(trimmed) ;
		if (trimmed.empty())
			continue ;

		// find comment
		if (trimmed[0] == '#')
			continue ;

		// Expect form:
		//
		//	type	filename	MD5
		//
		//		os	os.30-ROS_FTU.tgz			399ca28c621dba14b45e506ec7d2acad
		//		app	ETNA-AXIS-FTU-TDD-CPRI-0.0-35-APP.tgz	b73c958b4ce40a45acbba21c2757e6a2
		//		lib	ETNA-AXIS-FTU-TDD-CPRI-0.0-35-LIB.tgz	b7ad5de353dc534dd9546d7e32b69c24
		//
		Tokeniser token(trimmed);
		std::vector<std::string> tokens(token.getTokens()) ;
		if (tokens.size() == 3)
		{
			// is the first token a valid type
			IImageTypes::Type type ;
			if (IImageTypes::strToType(tokens[0], type))
			{
				pkgMap[type] = tokens[1] ;

//				std::cerr << "Type:" << tokens[0] << " File:" << tokens[1] << " MD5:" << tokens[2] << std::endl ;
			}
		}
	}
	infile.close() ;

	if (pkgMap.empty())
	{
		failReason = "Empty package file" ;
		return false ;
	}

	return true ;
}
