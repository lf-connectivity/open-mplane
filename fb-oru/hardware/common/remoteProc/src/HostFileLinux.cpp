/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileLinux.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>

#include "HostFileLinux.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HostFileLinux::HostFileLinux(const std::string &filename, int flags, mode_t mode) :
	HostFileBase(filename, flags, mode)
{
}

//-------------------------------------------------------------------------------------------------------------
HostFileLinux::~HostFileLinux()
{
}

//-------------------------------------------------------------------------------------------------------------
int HostFileLinux::close()
{
	return ::close(fd()) ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileLinux::read(uint8_t* buffer, unsigned buffer_len)
{
	return ::read(fd(), buffer, buffer_len) ;
}

//-------------------------------------------------------------------------------------------------------------
int HostFileLinux::write(const uint8_t* buffer, unsigned buffer_len)
{
	return ::write(fd(), buffer, buffer_len) ;
}
