/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangCarrierMgr.cpp
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
#include "YangCarrierMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
YangCarrierMgr::YangCarrierMgr() :
	mLeafContainer()
{
}

//-------------------------------------------------------------------------------------------------------------
YangCarrierMgr::~YangCarrierMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
bool YangCarrierMgr::initialise()
{
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void YangCarrierMgr::setLeafContainer(std::shared_ptr<ILeafContainer> leafContainer)
{
	mLeafContainer = leafContainer ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILeafContainer> YangCarrierMgr::leafContainer()
{
	return mLeafContainer ;
}

//-------------------------------------------------------------------------------------------------------------
std::string YangCarrierMgr::endpointName(const std::string &prefix, unsigned antenna, unsigned carrier)
{
	return std::string("cc") + std::to_string(carrier) + std::string(prefix) + std::to_string(antenna) ;
}
