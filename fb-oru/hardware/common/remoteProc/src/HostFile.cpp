/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFile.cpp
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "HostFile.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HostFile::HostFile(const std::string &filename, int flags, mode_t mode) :
	HostFileLinux(filename, flags, mode)
{
std::cerr << "NEW HostFile " << filename << std::endl ;
	setFd( ::open(filename.c_str(), flags, mode) ) ;
}

//-------------------------------------------------------------------------------------------------------------
HostFile::~HostFile()
{
}
