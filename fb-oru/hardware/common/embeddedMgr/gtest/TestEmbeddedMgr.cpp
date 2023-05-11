/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestEmbeddedMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdlib>
#include <iostream>

#include "TestEmbeddedMgr.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::vector<std::pair<std::string, std::string>> TEST_FIRMWARE_LIST{
	{ "R5-0", "r5-0-.*"},
	{ "R5-1", "r5-1-.*"},
};

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRemoteMsgHandler> IRemoteMsgHandler::factory(unsigned index)
{
	std::cerr << "IRemoteMsgHandler::factory <gtest NULL>" << std::endl ;
	return std::shared_ptr<IRemoteMsgHandler>() ;
}

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IEmbeddedMgr> IEmbeddedMgr::singleton()
{
	static std::shared_ptr<IEmbeddedMgr> instance(std::make_shared<TestEmbeddedMgr>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TestEmbeddedMgr::TestEmbeddedMgr() :
	EmbeddedMgr(TEST_FIRMWARE_LIST, testFirmwarePath()),
	mStates(TEST_FIRMWARE_LIST.size(), IEmbeddedMgr::PROC_OFFLINE)
{
}

TestEmbeddedMgr::~TestEmbeddedMgr()
{
}

void TestEmbeddedMgr::changeState(unsigned index, IEmbeddedMgr::ProcState state)
{
	mStates[index] = state ;
}

std::string Mplane::TestEmbeddedMgr::testFirmwarePath()
{
	std::string user(::getenv("USER")) ;
	if (user.empty())
		user = "test" ;

	std::string path("/tmp/" + user + "/firmware") ;
	return path ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool TestEmbeddedMgr::doSetState(unsigned index, bool start)
{
	std::cerr << "TestEmbeddedMgr::doSetState index=" << index << " start=" << start << std::endl ;
	mStates[index] = (start ? IEmbeddedMgr::PROC_RUNNING : IEmbeddedMgr::PROC_OFFLINE) ;
	return true ;
}

bool TestEmbeddedMgr::doSetFirmware(unsigned index)
{
	return true ;
}

IEmbeddedMgr::ProcState TestEmbeddedMgr::doStatus(unsigned index)
{
	return mStates.at(index) ;
}
