/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FeatureWebsockLab.cpp
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

#include "FeatureWebsockLab.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
int FeatureWebsockLab::handle = BuildFeatureUtils<FeatureWebsockLab>::registerBuildFeature() ;

std::shared_ptr<IBuildFeature> FeatureWebsockLab::getInstance()
{
	return BuildFeatureUtils<FeatureWebsockLab>::getInstance() ;
}


//-------------------------------------------------------------------------------------------------------------
FeatureWebsockLab::FeatureWebsockLab() :
	BuildFeature()
{
}

//-------------------------------------------------------------------------------------------------------------
FeatureWebsockLab::~FeatureWebsockLab()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureWebsockLab::init(IApplication* app)
{
//	std::cerr << "FeatureWebsockLab::" << __FUNCTION__ << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FeatureWebsockLab::appPreRun()
{
//	std::cerr << "FeatureWebsockLab::" << __FUNCTION__ << std::endl ;

	if (LAB)
	{
		// server
		std::shared_ptr<SocketServer> server(
			TifControl::make_server<WebSocketServer>("TifWebsock", WebSocketServer::DEFAULT_PORT, 2)
		);

		return ITifControl::addServer(server) ;
	}

	return true ;
}
