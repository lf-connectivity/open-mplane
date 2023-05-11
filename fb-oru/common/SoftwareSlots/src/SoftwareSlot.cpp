/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlot.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "Path.h"

#include "SoftwareSlotConstants.h"
#include "SoftwareSlot.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SoftwareSlot::SoftwareSlot(const std::string& name, const std::string &mgmtPath) :
	mSlotName(name),
	mMgrPath(mgmtPath),
	mSlotLink(mMgrPath + "/" + SoftwareSlotConstants::SlotsSubdir + "/" + mSlotName),
	mPackage()

{
}

//-------------------------------------------------------------------------------------------------------------
SoftwareSlot::~SoftwareSlot()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string SoftwareSlot::name() const
{
	return mSlotName ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::isReadOnly() const
{
	if (!isAllocated())
		return false ;

	return mPackage->isReadOnly() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::setReadOnly(bool readOnly)
{
	if (!isAllocated())
		return false ;

	return mPackage->setReadOnly(readOnly) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::activate()
{
	if (!isAllocated())
		return false ;

	return mPackage->activate() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::isRunning() const
{
	if (!isAllocated())
		return false ;

	return mPackage->isRunning() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::isActive() const
{
	if (!isAllocated())
		return false ;

	return mPackage->isActive() ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::allocatePackage(std::shared_ptr<ISoftwarePackage> pkg)
{
	mPackage = pkg ;

	// Remove any existing link
	Path::remove(mSlotLink) ;

	// Create link
	return Path::createLink(mSlotLink, mPackage->manifestPath()) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISoftwarePackage> SoftwareSlot::package() const
{
	return mPackage ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::clearPackage()
{
	mPackage.reset() ;
	Path::remove(mSlotLink) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::isAllocated() const
{
	if (!mPackage)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::isValid() const
{
	if (!isAllocated())
		return false ;

	return mPackage->isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
void SoftwareSlot::show(std::ostream &os)
{
	os << "-- SLOT " << mSlotName << " -- " << std::endl ;
	os << "Link...........: " << mSlotLink << std::endl ;
	os << "Access.........: " << (isReadOnly() ? "READ-ONLY" : "READ-WRITE") << std::endl ;
	os << "Validity.......: " << (isValid() ? "VALID" : "INVALID") << std::endl ;
	if (isAllocated())
		mPackage->show(os) ;
	else
	os << "Package........: EMPTY" << std::endl ;
	os << "------------" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool SoftwareSlot::initialise(std::vector<std::shared_ptr<ISoftwarePackage> > packages)
{
	// See if we already have a link created from last reboot
	if (!Path::exists(mSlotLink))
		return true ;

	// use the link
	std::string manifestPath ;
	if (!Path::readLink(mSlotLink, manifestPath))
	{
		// link now invalid so remove it
		Path::remove(mSlotLink) ;
		return true ;
	}

	// Use the linked file to find the matching package
	for (auto pkg : packages)
	{
		if (manifestPath != pkg->manifestPath())
			continue ;

		// found the package
		mPackage = pkg ;
		return true ;
	}

	// not found package so clear the link
	Path::remove(mSlotLink) ;

	return true ;
}
