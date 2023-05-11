/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangMgrService.cpp
 * \brief     YANG Manager service
 *
 *
 * \details   YANG Manager service - Loads YANG modules manager to access data stored in sysrepo.
 *
 */

#include "YangMgrService.h"

using namespace Mplane;


std::shared_ptr<YangMgrService> YangMgrService::singleton()
{
	static std::shared_ptr<YangMgrService> instance(std::make_shared<YangMgrService>());
	return instance;
}

YangMgrService::YangMgrService()
	: Service(SERVICE_LOW_PRIORITY,
	          SMALL_STACK,
	          100, // update stuff every 100 msec
	          "YangMgrService",
	          "YANG")
{
	if((mYangMgr = std::make_shared<YangMgrServer>()) == nullptr)
	{
		eventError("YangMgrService::YangMgrService() - Failed to start YANG Manager Server Service");
		return ;
	}

	if (std::string(YANG_MODS_PATH).empty())
		throw std::runtime_error("YANG_MODS_PATH must be set in the projects CMakeLists.txt file.");
	mYangMgr->setSearchPath(YANG_MODS_PATH);

	if(mYangMgr->initialise() != YangResult_E::OK)
	{
		eventError("YangMgrService::YangMgrService() - Failed to initialise YANG Manager Server Service");
		return ;
	}
}

void YangMgrService::show()
{
	eventInfo("*** YangMgrService has no specific data at this time ***");
}

int YangMgrService::service()
{
	logDebugVerbose("YangMgrService");

	// Process YANG manager events
	mYangMgr->processEvents();

	return 0;   // no errors
}

void YangMgrService::doReset()
{
}

YangMgrService::~YangMgrService()
{
}

std::shared_ptr<YangMgrServer> YangMgrService::getYangMgrServer() const
{
	return mYangMgr ;
}
