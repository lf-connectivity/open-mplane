/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LibImage.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>
#include <vector>
#include <set>

#include "Md5List.h"
#include "Path.h"

#include "LibImage.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LibImage::LibImage(ImageTask& task) :
	ImageBase(task, "LibImage")
{
}

//-------------------------------------------------------------------------------------------------------------
LibImage::~LibImage()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned LibImage::numFiles() const
{
	// (tgz.md5list + tgz + tgz.md5 + tgz.md5list)
	return 4 ;
}

//-------------------------------------------------------------------------------------------------------------
bool LibImage::initialise(std::string& failReason)
{
	if (!this->super::initialise(failReason))
		return false ;
	return setInstallDir("/nandflash/lib-images", failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LibImage::formatName(const std::string& version, const std::string& buildNumber)
{
	std::string name(this->super::formatName(version, buildNumber)) ;
	name.append("-LIB.tgz") ;
	return name ;
}

//-------------------------------------------------------------------------------------------------------------
bool LibImage::clean(std::string& failReason)
{
//std::cerr << "LinkImage::clean()" << std::endl ;
	// This is the tricky bit! We now possibly have 2 levels of link indirection. If a "tree" of links
	// is not pointed at by a 'current/previous' link then we can delete that tree. All we need to do
	// to delete the tree is delete the base tarball that they point at, creating broken links that the
	// default clean will handle.
	//
	// Tree1 - must keep:
	//
	//              aaaa.tgz -------+------> xxxx.tgz
	// current ---> bbbb.tgz -------'
	//              cccc.tgz -------'
	//
	// Tree2 - delete:
	//
	//              mmmm.tgz -------+------> yyyy.tgz
	//              nnnn.tgz -------'
	//              oooo.tgz -------'
	//
	// So, to work out what to delete we first scan just those links with .tgz extensions to create a map of
	// linked to files and mark all the tgz files as potentials to be deleted
	//
	// Next we look at all links that don't have .tgz extension. If they point to a link then we can remove the tgz file
	// that the link points at from the list of potentials to be deleted.
	//
	// Finally we delete all the potentials and let the default clean() polish up the mess.
	//
	std::map<std::string, std::string> tgzLinks ;
	std::set<std::string> tgzToDelete ;

	std::vector<std::string> dirContents( Path::dirContents(getInstallDir()) ) ;

//std::cerr << "LinkImage: Pass1" << std::endl ;

	// first pass: get details of all links with .tgz extension
	for (auto file : dirContents)
	{
		if (!Path::isLink(file))
			continue ;

		if (Path::extension(file) != ".tgz")
			continue ;

		// get target
		std::string link ;
		if (!Path::readLink(file, link))
			continue ;

//std::cerr << " [pass1] + tgz=" << file << " link=" << link << std::endl ;

		// Save the link
		tgzLinks[file] = link ;

		// add to list of files to possibly delete
		tgzToDelete.insert(link) ;	// the real tgz file
		tgzToDelete.insert(file) ;	// the link to the tgz file
	}

//std::cerr << "[pass1] results - potential tgz to del:" << std::endl ;
//for (auto link : tgzToDelete)
//{
//	std::cerr << link << std::endl ;
//}
//
//std::cerr << "LinkImage: Pass2" << std::endl ;
	// second pass: get details of all links without .tgz extension
	for (auto file : dirContents)
	{
		if (!Path::isLink(file))
			continue ;

		if (Path::extension(file) == ".tgz")
			continue ;

		// get target
		std::string link ;
		if (!Path::readLink(file, link))
			continue ;

//std::cerr << " [pass2] + file=" << file << " link=" << link << std::endl ;

		// if we're pointing at a tgz link, then we can mark the target tarball as being safe (i.e. don't delete)
		auto iter( tgzLinks.find(link) ) ;
		if (iter == tgzLinks.end())
			continue ;

//std::cerr << " [pass2] + + save tgz=" << iter->second << " link=" << iter->first << std::endl ;

		// remove from list of files to possibly delete
		tgzToDelete.erase( iter->first ) ; // the link
		tgzToDelete.erase( iter->second ) ; // the file
	}

//std::cerr << "[pass2] results - potential tgz to del:" << std::endl ;
//for (auto link : tgzToDelete)
//{
//	std::cerr << link << std::endl ;
//}


//std::cerr << "LinkImage: Pass3" << std::endl ;
	// final pass: delete all tgz we don't need
	for (auto tgz : tgzToDelete)
	{
		// Remove all files related to this tgz
		for (auto file : dirContents)
		{
			if (file.find(tgz) != 0)
				continue ;

//std::cerr << " [pass3] + DELETE file=" << file << std::endl ;
			Path::remove(file) ;
		}
	}

	// let default clean handle the rest
	return this->super::clean(failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
void LibImage::show(std::ostream& os) const
{
	os << "== Lib Image ==" << std::endl << std::endl ;

	os << "Current Settings:" << std::endl ;

	showPadValue(os, "Install Dir", getInstallDir()) ;
	showPadValue(os, "Server URL", getServerUrl()) ;
	os << std::endl ;

	this->super::show(os) ;
}

//-------------------------------------------------------------------------------------------------------------
bool LibImage::setImageName(const std::string& name, std::string& failReason)
{
	// set the image name
	if (!this->super::setImageName(name, failReason))
		return false ;

	// No we set the md5list name based on the image name - this will cause the base object to download this file too
	setMd5ListName( md5ListFilename( getImageName() ) ) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LibImage::info() const
{
	// Default behaviour is to read the 'current' link and return the base filename pointed at
	if (getInstallDir().empty())
		return "" ;

	// get current link
	std::string current(getInstallDir() + "/" + getCurrentLink()) ;
	std::string link ;
	if (!Path::exists(current) || !Path::readLink(current, link))
		return "" ;

	std::string info( Path::basename(link) ) ;

	// see if this link actually points at another link - if so, get the base
	if (!Path::isLink(link))
		return info ;

	// get link that this points at
	std::string link2 ;
	if (!Path::readLink(link, link2))
		return info ;
	info.append(std::string(" (") + Path::basename(link2) + ")") ;

	return info ;

}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool LibImage::alreadyDownloaded()
{
//std::cerr << "LibImage::alreadyDownloaded" << std::endl ;

	// do standard check for file already downloaded
	if (this->super::alreadyDownloaded())
		return true ;

//std::cerr << "LibImage::alreadyDownloaded - not already loaded (based on default behaviour), checking..." << std::endl ;

	// get the md5list file for this image
	std::string tmpDir("/tmp") ;


	// Download to temp file
	std::string md5listName(md5ListFilename(getImageName())) ;
	std::string failReason ;
	IImage::DownloadFunction downloadFunc(getDownloadFunction()) ;
	if (!downloadFunc(md5listName, getServerUrl(), tmpDir, failReason))
		return false ;

	// load md5list
	Md5List requestedMd5list(tmpDir + "/" + md5listName) ;

//std::cerr << "LibImage::alreadyDownloaded - matching with existing md5lists..." << std::endl ;

	// See if any already downloaded files match
	std::vector<std::string> dirContents( Path::dirContents(getInstallDir()) ) ;
	for (auto file : dirContents)
	{
		if (!Path::isFile(file))
			continue ;

		// find an md5list file with a valid tarball
		if ( Path::extension(file) != ".tgz" )
			continue ;

		Md5List md5list( md5ListFilename(file) ) ;
		if (md5list == requestedMd5list)
		{
			// This tarball has the same contents as the requested download, so we can create a link to
			// mark this equivalent and say it's already downloaded
			std::string imagePath = getInstallDir() + "/" + getImageName() ;
			if (! Path::createLink(imagePath, file) )
				return false ;

			// Need to also "install" the md5 file to match so that default check will work
			if (! Path::createLink( md5Filename(imagePath), md5Filename(file) ) )
				return false ;

			// Similarly, "install" the md5list file
			if (! Path::createLink( md5ListFilename(imagePath), md5ListFilename(file) ) )
				return false ;

			// now return saying we've downloaded already
			return true ;
		}
	}

	return false ;
}
