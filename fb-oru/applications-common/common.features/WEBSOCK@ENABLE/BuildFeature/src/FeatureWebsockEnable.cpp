/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureWebsockEnable.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "config.h"
#include "ITif.h"
#include "TifControl.hpp"
#include "BuildFeatureUtils.hpp"
#include "BuildFeatureList.h"

#include "ILoggable.h"

#include "WebSocketServer.h"

#include "FeatureWebsockEnable.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
int FeatureWebsockEnable::handle = BuildFeatureUtils<FeatureWebsockEnable>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureWebsockEnable::getInstance()
{
	return BuildFeatureUtils<FeatureWebsockEnable>::getInstance() ;
}


//-------------------------------------------------------------------------------------------------------------
FeatureWebsockEnable::FeatureWebsockEnable() :
	BuildFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureWebsockEnable::~FeatureWebsockEnable()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureWebsockEnable::init(IApplication* app)
{
//	std::cerr << "FeatureWebsockEnable::" << __FUNCTION__ << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureWebsockEnable::appPreRun()
{
//	std::cerr << "FeatureWebsockEnable::" << __FUNCTION__ << std::endl ;

	// server
	std::shared_ptr<SocketServer> server(
		TifControl::make_server<WebSocketServer>("TifWebsock", WebSocketServer::DEFAULT_PORT, 2)
	);

	return ITifControl::addServer(server) ;
}
