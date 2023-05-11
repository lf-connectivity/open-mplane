/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileBase.cpp
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

#include "HostFileBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HostFileBase::HostFileBase(const std::string &filename, int flags, mode_t mode) :
	mFilename(filename),
	mFlags(flags),
	mMode(mode),
	mFd(-1)
{
	//std::cerr << "NEW HostFileBase " << filename << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
HostFileBase::~HostFileBase()
{
	//std::cerr << "DEL HostFileBase " << filename() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::string HostFileBase::filename() const
{
	return mFilename ;
}

//-------------------------------------------------------------------------------------------------------------
std::string HostFileBase::name() const
{
	return mFilename ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileBase::fd() const
{
	return mFd ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileBase::flags() const
{
	return mFlags ;
}

//-------------------------------------------------------------------------------------------------------------
mode_t HostFileBase::mode() const
{
	return mMode ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileBase::freeOnClose() const
{
	// normal files can be freed on close
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileBase::isChannel() const
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileBase::registerWriteFunc(const std::string &funcId, IHostFile::WriteFunc func)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HostFileBase::unregisterWriteFunc(const std::string &funcId)
{
	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void HostFileBase::setFd(int fd)
{
	//std::cerr << "HostFileBase::setFd " << filename() << " fd=" << fd << std::endl ;
	mFd = fd ;
}
