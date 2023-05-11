/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HighSpeedEthernet.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "HighSpeedEthernet.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::map<IHighSpeedEthernet::EthernetSpeed, std::string> SPEED_NAMES{
	{IHighSpeedEthernet::ENET_STANDALONE_25G, 	"Standalone 25G"},
	{IHighSpeedEthernet::ENET_STANDALONE_10G, 	"Standalone 10G"},
	{IHighSpeedEthernet::ENET_AUTO_25G, 			"Auto-negotiated 25G"},
	{IHighSpeedEthernet::ENET_AUTO_10G, 			"Auto-negotiated 10G"},
};


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IHighSpeedEthernet::enetSpeed2Str(EthernetSpeed speed)
{
	return SPEED_NAMES.at(speed) ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HighSpeedEthernet::HighSpeedEthernet()
{
}

//-------------------------------------------------------------------------------------------------------------
HighSpeedEthernet::~HighSpeedEthernet()
{
}

//-------------------------------------------------------------------------------------------------------------
IHighSpeedEthernet::EthernetSpeed HighSpeedEthernet::speed() const
{
	// just return a fixed default
	return IHighSpeedEthernet::ENET_STANDALONE_10G ;
}

//-------------------------------------------------------------------------------------------------------------
bool HighSpeedEthernet::is25G() const
{
	EthernetSpeed speedVal(speed()) ;
	if (speedVal == IHighSpeedEthernet::ENET_STANDALONE_25G)
		return true ;
	if (speedVal == IHighSpeedEthernet::ENET_AUTO_25G)
		return true ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
uint32_t HighSpeedEthernet::read(uint32_t address) const
{
	// return (obviously) dummy value
	return 0xFEEDBEEF ;
}
