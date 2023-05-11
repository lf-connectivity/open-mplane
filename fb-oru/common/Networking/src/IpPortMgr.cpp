/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IpPortMgr.cpp
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
#include "Path.h"
#include "IpPortMgr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#ifdef OFF_TARGET
const std::string PATH("/tmp/nandflash/.settings/ip-ports") ;
#else
const std::string PATH("/nandflash/.settings/ip-ports") ;
#endif

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IIpPortMgrWriter> IIpPortMgrWriter::singleton()
{
	static std::shared_ptr<IIpPortMgrWriter> instance(std::make_shared<IpPortMgr>()) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IIpPortMgr> IIpPortMgr::singleton()
{
	return IIpPortMgrWriter::singleton() ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IpPortMgr::IpPortMgr() :
	mError(),
	mCurrent(),
	mSaved()
{
	// Ensure path exists
	Path::mkpath(Path::dir(PATH)) ;

	// Check for file existence
	mSaved.setPath(PATH) ;
	if (Path::exists(PATH))
	{
		// config exists so read it
		mSaved.read() ;
	}

	mCurrent = mSaved ;
}

//-------------------------------------------------------------------------------------------------------------
IpPortMgr::~IpPortMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, unsigned> > IpPortMgr::list() const
{
	std::vector<std::pair<std::string, std::string>> values(mCurrent.values()) ;

	std::vector<std::pair<std::string, unsigned> > ip_port ;
	for (auto pair : values)
	{
		ip_port.push_back(std::make_pair(pair.first, (unsigned)stoi(pair.second, 0, 0))) ;
	}
	return ip_port ;
}

//-------------------------------------------------------------------------------------------------------------
void IpPortMgr::addEntry(const std::string &ip, unsigned port)
{
	mCurrent.setValue(ip, std::to_string(port)) ;
}

//-------------------------------------------------------------------------------------------------------------
void IpPortMgr::clear()
{
	mCurrent.clear() ;
}


//-------------------------------------------------------------------------------------------------------------
std::string IpPortMgr::error()
{
	std::string err ;
	swap(err, mError) ;
	return err ;
}

//-------------------------------------------------------------------------------------------------------------
void IpPortMgr::setList(const std::vector<std::pair<std::string, unsigned> > &list)
{
	mCurrent.clear() ;

	for (auto pair : list)
	{
		mCurrent.setValue(pair.first, std::to_string(pair.second)) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool IpPortMgr::save()
{
	mSaved = mCurrent ;
	if (!mSaved.save())
		return setError(mSaved.error()) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool IpPortMgr::restore()
{
	mCurrent = mSaved ;
	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool IpPortMgr::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;

	// Always return false so we can set the error and return with a fail
	return false ;
}
