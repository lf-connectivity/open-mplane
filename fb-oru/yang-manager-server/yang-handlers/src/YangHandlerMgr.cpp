/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangHandlerMgr.cpp
 * \brief     Defines the functions declared in YangHandlerMgr.h
 *
 *
 * \details   Sets up the basic routines to manage the Yang Handlers
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "YangHandlerMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangHandlerMgr::YangHandlerMgr(std::shared_ptr<IYangModuleMgr> moduleMgr)
	: mModuleMgr(moduleMgr)
	, mHandlers()
	, mCarrierMgr( IYangCarrierMgr::singleton() )
{
}

//-------------------------------------------------------------------------------------------------------------
YangHandlerMgr::~YangHandlerMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandlerMgr::initialise()
{
	bool ok(true) ;
	for (auto handler : mHandlers)
	{
		ok &= handler->initialise() ;
	}

	ok &= mCarrierMgr->initialise() ;

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandlerMgr::registerHandler(std::shared_ptr<IYangHandler> handler)
{
	mHandlers.push_back(handler) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool YangHandlerMgr::testCallback(const std::string &xpath, std::shared_ptr<DataVariant> value)
{
	unsigned numModules(mModuleMgr->getNumModules()) ;
	for (unsigned id=0; id < numModules; id++)
	{
		std::shared_ptr<IYangModule> module(mModuleMgr->getModule(id));
		if (module->testCallback(xpath, value))
			return true ;
	}
	return false ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IYangModuleMgr> YangHandlerMgr::moduleMgr() const
{
	return mModuleMgr ;
}
