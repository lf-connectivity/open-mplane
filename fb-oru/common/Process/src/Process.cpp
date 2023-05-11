/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Process.cpp
 * \brief     Application process utilities
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <iostream>

#include "Process.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
long int Mplane::Process::getResidentSetSize()
{
	struct rusage usageSelf ;
	int rc = ::getrusage(RUSAGE_SELF, &usageSelf) ;
	if (rc != 0)
		return -1L ;

	return usageSelf.ru_maxrss ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Process::getSystemMemory(unsigned long& total, unsigned long& free, unsigned long& used,
		unsigned long& shared, unsigned long& buffer)
{
	total = 0 ;
	free = 0 ;
	used = 0 ;
	shared = 0 ;
	buffer = 0 ;

	// read system info
	struct sysinfo info;
	if (sysinfo(&info) != 0)
		return false ;

	total = info.totalram ;
	free = info.freeram ;
	used = total - free ;
	shared = info.sharedram ;
	buffer = info.bufferram ;

	return true ;
}
