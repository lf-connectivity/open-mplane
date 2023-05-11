/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteProc.cpp
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
#include <map>
#include <cstdint>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include "Path.h"
#include "stringfunc.hpp"
#include "RemoteProc.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::map<RemoteProc::ProcState, std::string> STATE_MAP{
	{RemoteProc::PROC_OFFLINE,		"offline"},
	{RemoteProc::PROC_RUNNING,		"running"},
	{RemoteProc::PROC_SUSPENDED,	"suspended"},
	{RemoteProc::PROC_CRASHED,		"crashed"},
	{RemoteProc::PROC_DELETED,		"deleted"},
	{RemoteProc::PROC_INVALID,		"invalid"},
};

const std::string FIRMWARE_PATH("/lib/firmware/") ;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string RemoteProc::state2str(ProcState state)
{
	if (STATE_MAP.find(state) == STATE_MAP.end())
		return "invalid" ;

	return STATE_MAP.at(state) ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteProc::ProcState RemoteProc::str2state(const std::string &str)
{
	//std::cerr << std::endl << "RemoteProc::str2state '" << str << "'" << std::endl ;

	for (auto& entry : STATE_MAP)
	{
		//std::cerr << std::endl << " * '" << entry.second << "' => " << entry.first << std::endl ;
		if (entry.second != str)
			continue ;

		return entry.first ;
	}

	return RemoteProc::PROC_INVALID ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteProc::RemoteProc(unsigned index) :
	mIndex(index),
	mFirmwarePath(),
	mInstanceFirmware(),
	mClassPath("/sys/class/remoteproc/remoteproc" + std::to_string(mIndex) + "/")
{
	//std::cerr << std::endl << "NEW RemoteProc @ " << this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteProc::~RemoteProc()
{
	//std::cerr << std::endl << "DEL RemoteProc @ " << this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::setFirmware(const std::string &path)
{
//std::cerr << std::endl << "RemoteProc::setFirmware " << path << std::endl ;

	mFirmwarePath.clear() ;
	mInstanceFirmware.clear() ;

	// check exists
	if (Path::exists(path))
	{
		mFirmwarePath = path ;
	}
	else
	{
		// might be in firmware area, check there...
		if (!Path::exists(FIRMWARE_PATH + path))
		{
			setError("Firmware " + path + " not found") ;
			return false ;
		}
		else
		{
			mFirmwarePath = FIRMWARE_PATH + path ;
		}
	}

	// copy to firmware area
	mInstanceFirmware = std::to_string(mIndex) + "-" + Path::basename(mFirmwarePath) ;
//std::cerr << std::endl << "RemoteProc::setFirmware copy " << mFirmwarePath << " to " << mInstanceFirmware << std::endl ;
	if (!Path::fileCopy(mFirmwarePath, FIRMWARE_PATH + mInstanceFirmware))
	{
		setError("Unable to copy firmware to " + FIRMWARE_PATH) ;
		return false ;
	}

	// set the processor firmware setting
//std::cerr << std::endl << "RemoteProc::setFirmware set firmware " << mInstanceFirmware << std::endl ;
	if (!writeClass("firmware", mInstanceFirmware))
		return false ;

//std::cerr << std::endl << "RemoteProc::setFirmware - DONE" << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::setState(bool start)
{
	return writeClass("state", start ? "start" : "stop") ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::start()
{
	return setState(true) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::stop()
{
	if  (!setState(false))
		return false ;

	// allow remote processor to stop
	for (unsigned retry=1; retry<=5; ++retry)
	{
		if (state() == RemoteProc::PROC_OFFLINE)
			break ;
		sleep(1) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::loadFirmware(const std::string &path)
{
//std::cerr << std::endl << "RemoteProc::loadFirmware " << path << std::endl ;

	// get current state & stop if running
	////std::cerr << std::endl << "RemoteProc::loadFirmware check state..." << std::endl ;
	if (state() == RemoteProc::PROC_RUNNING)
		stop() ;

	// set firmware
//std::cerr << std::endl << "RemoteProc::loadFirmware set firmware..." << std::endl ;
	if (!setFirmware(path))
	{
//std::cerr << std::endl << "RemoteProc::loadFirmware unable to set firmware" << std::endl ;
		return false ;
	}

	// start
//std::cerr << std::endl << "RemoteProc::loadFirmware start..." << std::endl ;
	return start() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteProc::error()
{
	std::string err ;
	std::swap(err, mError) ;
	return err ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteProc::ProcState RemoteProc::state()
{
	std::string state ;
	if (!readClass("state", state))
	{
		return RemoteProc::PROC_INVALID ;
	}

	//std::cerr << std::endl << "RemoteProc::state " << state << " " << str2state(state) << std::endl ;

	return str2state(state) ;
}


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::writeSysFile(const std::string &path, const std::string &str)
{
//std::cerr << std::endl << "RemoteProc::writeClass " << name << "=" << str << std::endl ;

	int fd = open(path.c_str(), O_WRONLY);
	if (fd == -1)
	{
//		setError("Unable to open " + path);
		return false;
	}
	ssize_t bytes_written = write(fd, str.c_str(), str.size());
	if (bytes_written != (ssize_t)str.size())
	{
//std::cerr << std::endl << "RemoteProc::writeClass - Unable to write to " << path << " : bytes written=" << bytes_written << " str size=" << str.size() << std::endl ;
//		setError("Unable to write to " + path);
		close(fd);
		return false;
	}

	close(fd) ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::readSysFile(const std::string &path, std::string &data)
{
	data.clear() ;

	int fd = open(path.c_str(), O_RDONLY);
	if (fd == -1)
	{
//		setError("Unable to open " + path);
		return false;
	}

	char buff[512] ;
	ssize_t bytes_read = read(fd, buff, sizeof(buff)-1);
	close(fd);

	if (bytes_read < 0)
	{
//		setError("Unable to read " + path);
		return false;
	}

	buff[bytes_read] = '\0' ;
	data = std::string(buff) ;

	data = trim(data, " \t\r\n") ;

	//std::cerr << std::endl << "RemoteProc::readClass " << name << "=" << data << std::endl ;

	return true;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RemoteProc::setError(const std::string &error)
{
	//std::cerr << std::endl << "RemoteProc::setError " << error << std::endl ;

	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::writeClass(const std::string &name, const std::string &str)
{
	if ( writeSysFile(mClassPath + name, str) )
		return true ;

	setError("Unable to write " + mClassPath + name);
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteProc::readClass(const std::string &name, std::string &data)
{
	if ( readSysFile(mClassPath + name, data) )
		return true ;

	setError("Unable to read " + mClassPath + name);
	return false ;
}
