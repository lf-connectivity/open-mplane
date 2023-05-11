/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HostFileFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IHostFile.h"
#include "HostFile.h"
#include "HostFileChannel.h"
#include "HostFileStdout.h"
#include "HostFileStdin.h"
#include "HostFileStderr.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHostFile> IHostFile::factory(const std::string& name, int flags, mode_t mode)
{
	if (name.empty())
		return std::shared_ptr<IHostFile>() ;

	// special "channel" file
	if (name[0] == '>')
		return std::make_shared<HostFileChannel>(name, flags, mode) ;

	// stdout
	if (name == "stdout")
		return std::make_shared<HostFileStdout>() ;

	// stderr
	if (name == "stderr")
		return std::make_shared<HostFileStderr>() ;

	// stdin
	if (name == "stdin")
		return std::make_shared<HostFileStdin>() ;

	// Linux file
	return std::make_shared<HostFile>(name, flags, mode) ;
}
