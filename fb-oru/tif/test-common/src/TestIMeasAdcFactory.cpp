/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIMeasAdcFactory.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <vector>
#include "TestIMeasAdc.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
const unsigned RX_PORTS{4} ;

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IMeasAdc> IMeasAdc::getInterface( unsigned path ) /* throw ( std::invalid_argument) */
{
	static std::vector<std::shared_ptr<IMeasAdc>> portList ;
	if (portList.empty())
	{
		for (unsigned port=0; port < RX_PORTS; ++port)
		{
			portList.push_back(std::make_shared<TestIMeasAdc>()) ;
		}
	}

	if (path >= portList.size())
		throw std::invalid_argument("Inavlid RX port") ;

	return portList[path] ;
}
