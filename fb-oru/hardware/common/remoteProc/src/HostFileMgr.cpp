/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileMgr.cpp
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
#include "HostFileMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HostFileMgr::HostFileMgr() :
	mFiles(),
	mFileNames()
{
	//std::cerr << "NEW HostFileMgr @ " << (void*)this << std::endl ;

	// Add stdin, stdout, stderr
	addFile( IHostFile::factory("stdin", 0, 0)) ;
	addFile( IHostFile::factory("stdout", 0, 0)) ;
	addFile( IHostFile::factory("stderr", 0, 0)) ;
}

//-------------------------------------------------------------------------------------------------------------
HostFileMgr::~HostFileMgr()
{
	//std::cerr << "DEL HostFileMgr @ " << (void*)this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileMgr::open(const std::string &filename, int flags, mode_t mode)
{
	std::shared_ptr<IHostFile> file( IHostFile::factory(filename, flags, mode)) ;
//std::cerr << "HostFileMgr::open " << filename << " file=" << (void*)file.get() << std::endl ;
	if (!file)
		return -EINVAL ;

//std::cerr << "HostFileMgr::open * " << filename << " fd=" << file->fd() << std::endl ;
	// only store if a valid fd
	if (file->fd() > 0)
		addFile(file) ;

	return file->fd() ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileMgr::close(int fd)
{
	std::shared_ptr<IHostFile> file( hostFile(fd) ) ;
	if (!file)
		return -EBADF ;

	if (file->freeOnClose())
		delFile(file) ;

	return file->close() ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileMgr::read(int fd, uint8_t *buffer, unsigned buffer_len)
{
	std::shared_ptr<IHostFile> file( hostFile(fd) ) ;
	if (!file)
		return -EBADF ;

	return file->read(buffer, buffer_len) ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileMgr::write(int fd, const uint8_t *buffer, unsigned buffer_len)
{
	std::shared_ptr<IHostFile> file( hostFile(fd) ) ;
	if (!file)
		return -EBADF ;

	return file->write(buffer, buffer_len) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHostFile> HostFileMgr::hostFile(int fd)
{
	auto entry(mFiles.find(fd)) ;
	if (entry == mFiles.end())
		return std::shared_ptr<IHostFile>() ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHostFile> HostFileMgr::hostFile(const std::string &filename)
{
	auto entry(mFileNames.find(filename)) ;
	if (entry == mFileNames.end())
		return std::shared_ptr<IHostFile>() ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IHostFile> > HostFileMgr::hostFiles()
{
	std::vector<std::shared_ptr<IHostFile> > files ;
	for (auto& entry : mFiles)
		files.push_back(entry.second) ;

	return files ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void HostFileMgr::addFile(std::shared_ptr<IHostFile> file)
{
	mFiles[ file->fd() ] = file ;
	mFileNames[ file->filename() ] = file ;
}

//-------------------------------------------------------------------------------------------------------------
void HostFileMgr::delFile(std::shared_ptr<IHostFile> file)
{
	mFiles.erase( file->fd() ) ;
	mFileNames.erase( file->filename() ) ;
}
