/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EmbeddedMgr.cpp
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
#include <regex>

#include "Path.h"
#include "EmbeddedMgr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string DEFAULT_FIRMWARE_PATH("/embedded-firmware") ;

const std::map<IEmbeddedMgr::ProcState, std::string> STATE_MAP{
	{IEmbeddedMgr::PROC_OFFLINE,		"offline"},
	{IEmbeddedMgr::PROC_RUNNING,		"running"},
	{IEmbeddedMgr::PROC_SUSPENDED,		"suspended"},
	{IEmbeddedMgr::PROC_CRASHED,		"crashed"},
	{IEmbeddedMgr::PROC_DELETED,		"deleted"},
	{IEmbeddedMgr::PROC_INVALID,		"invalid"},
};

//=============================================================================================================
// IEmbeddedMgr STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IEmbeddedMgr::state2str(ProcState state)
{
	if (STATE_MAP.find(state) == STATE_MAP.end())
		return "invalid" ;

	return STATE_MAP.at(state) ;
}

//-------------------------------------------------------------------------------------------------------------
IEmbeddedMgr::ProcState IEmbeddedMgr::str2state(const std::string &str)
{
	//std::cerr << std::endl << "RemoteProc::str2state '" << str << "'" << std::endl ;

	for (auto& entry : STATE_MAP)
	{
		//std::cerr << std::endl << " * '" << entry.second << "' => " << entry.first << std::endl ;
		if (entry.second != str)
			continue ;

		return entry.first ;
	}

	return IEmbeddedMgr::PROC_INVALID ;
}



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
EmbeddedMgr::EmbeddedMgr(const std::vector<std::pair<std::string, std::string> > &firmwareList,
		const std::string& firmwarePath) :
	mFirmwarePath(firmwarePath),
	mNameIndexMap(),
	mNames(firmwareList.size(), ""),
	mFirmware(firmwareList.size(), ""),
	mMsgHandler(firmwareList.size(), std::shared_ptr<IRemoteMsgHandler>()),
	mError("")
{
//	std::cerr << "NEW EmbeddedMgr @ " << (void*)this << std::endl ;

	if (mFirmwarePath.empty())
		mFirmwarePath = DEFAULT_FIRMWARE_PATH ;

	for (unsigned i=0; i < firmwareList.size(); ++i)
	{
		// always build the message handlers so we have valid pointers in all cases. We'll only use/connect via these
		// handlers when we actually need to access that remote
		mMsgHandler[i] = IRemoteMsgHandler::factory(i) ;

		// skip any indices that don't have matching firmware
		if (!firmwareMap(i, firmwareList[i].second))
			continue ;

		mNames[i] = firmwareList[i].first ;
		mNameIndexMap[firmwareList[i].first] = i ;
	}

	mError.clear() ;
}


//-------------------------------------------------------------------------------------------------------------
EmbeddedMgr::~EmbeddedMgr()
{
//	std::cerr << "DEL EmbeddedMgr @ " << (void*)this << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> EmbeddedMgr::names() const
{
	return mNames ;
}

//-------------------------------------------------------------------------------------------------------------
IEmbeddedMgr::ProcState EmbeddedMgr::status(unsigned index)
{
	if (index >= mNames.size())
		return IEmbeddedMgr::PROC_INVALID ;

	return doStatus(index) ;
}

//-------------------------------------------------------------------------------------------------------------
IEmbeddedMgr::ProcState EmbeddedMgr::status(const std::string &name)
{
	int index(procIndex(name)) ;
	if (index < 0)
		return IEmbeddedMgr::PROC_INVALID ;

	return doStatus( (unsigned)index ) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EmbeddedMgr::error()
{
	std::string error ;
	using std::swap ;
	swap(error, mError) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
int EmbeddedMgr::procIndex(const std::string &name) const
{
	if (mNameIndexMap.find(name) == mNameIndexMap.end())
		return -1 ;

	return mNameIndexMap.at(name) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EmbeddedMgr::name(unsigned index) const
{
	if (index >= mNames.size())
		return "" ;

	return mNames.at(index) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EmbeddedMgr::firmware(unsigned index) const
{
	if (index >= mNames.size())
		return "" ;

	return mFirmware.at(index) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EmbeddedMgr::firmware(const std::string &name) const
{
	int index(procIndex(name)) ;
	if (index < 0)
		return "" ;

	return firmware( (unsigned)index ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::setFirmware(unsigned index, const std::string &path)
{
	if (index >= mNames.size())
		return setError("Invalid processor index") ;

	return firmwareMap(index, path) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::setFirmware(const std::string &name, const std::string &path)
{
	int index(procIndex(name)) ;
	if (index < 0)
		return setError("Invalid processor name") ;

	return setFirmware( (unsigned)index, path ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::setState(unsigned index, bool start)
{
	if (index >= mNames.size())
		return setError("Invalid processor index") ;

	return doSetState(index, start) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::setState(const std::string &name, bool start)
{
	int index(procIndex(name)) ;
	if (index < 0)
		return setError("Invalid processor name") ;

	return setState( (unsigned)index, start ) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::start(unsigned index)
{
	return setState(index, true) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::start(const std::string &name)
{
	return setState(name, true) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::stop(unsigned index)
{
	return setState(index, false) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::stop(const std::string &name)
{
	return setState(name, false) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::loadFirmware(unsigned index)
{
	if (index >= mNames.size())
		return setError("Invalid processor index") ;

	// get current state & stop if running
//std::cerr << std::endl << "RemoteProc::loadFirmware check state..." << std::endl ;
	if (status(index) == IEmbeddedMgr::PROC_RUNNING)
		stop(index) ;

	// set firmware
//std::cerr << std::endl << "RemoteProc::loadFirmware set firmware..." << std::endl ;
	if (!doSetFirmware(index))
	{
//std::cerr << std::endl << "RemoteProc::loadFirmware unable to set firmware" << std::endl ;
		return false ;
	}

	// start
//std::cerr << std::endl << "RemoteProc::loadFirmware start..." << std::endl ;
	return start(index) ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::loadFirmware(const std::string &name)
{
	int index(procIndex(name)) ;
	if (index < 0)
		return setError("Invalid processor name") ;

	return loadFirmware( (unsigned)index ) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRemoteMsgHandler> EmbeddedMgr::msgHandler(unsigned index)
{
	if (index >= mNames.size())
	{
		setError("Invalid processor index") ;
		return std::shared_ptr<IRemoteMsgHandler>() ;
	}

	return mMsgHandler[index] ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::eventLoop(unsigned index, bool start)
{
	if (index >= mNames.size())
	{
		setError("Invalid processor index") ;
		return false ;
	}

	return mMsgHandler[index]->eventLoop(start) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string EmbeddedMgr::firmarePath() const
{
	return mFirmwarePath ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::firmwareMap(unsigned index, const std::string &firmwareName)
{
	std::string path ;
#ifdef OFF_TARGET
	path = mFirmwarePath + "/r5-" + std::to_string(index) + "-echo-test.bin" ;
#else
	// First see if we can find this firmware (which may be a REGEXP) in the firmware directory
	std::vector<std::string> contents(Path::dirContents(mFirmwarePath)) ;
	std::regex re(firmwareName) ;
	for (auto& p : contents)
	{
		//std::cerr << "EmbeddedMgr::firmwareMap regex=" << firmwareName << " path=" << p << " base=" << Path::basename(p) << std::endl ;

		if (!std::regex_match(Path::basename(p), re))
			continue ;

		path = p ;
		//std::cerr << "EmbeddedMgr::firmwareMap FOUND=" << path << std::endl ;
		break ;
	}

	if (path.empty())
		return setError("Unable to find: " + firmwareName) ;
#endif

	mFirmware[index] = path ;
	return true ;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::doSetState(unsigned index, bool start)
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool EmbeddedMgr::doSetFirmware(unsigned index)
{
//std::cerr << "EmbeddedMgr::doSetFirmware NOOP" << std::endl ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
IEmbeddedMgr::ProcState EmbeddedMgr::doStatus(unsigned index)
{
	return IEmbeddedMgr::PROC_INVALID ;
}
