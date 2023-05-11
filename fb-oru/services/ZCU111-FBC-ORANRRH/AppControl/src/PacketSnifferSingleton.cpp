/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PacketSnifferSingleton.cpp
 * \brief     Creates singleton for PacketSniffer
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IPacketSniffer.h"
#include "PacketSniffer.h"
#include "IAppOptions.h"

using namespace Mplane;

//=============================================================================================================
// Singleton
//=============================================================================================================
namespace {

	std::shared_ptr<IPacketSniffer> ethbbSingleton(const std::string& interface)
	{
		static std::shared_ptr<IPacketSniffer> instance(std::make_shared<PacketSniffer>(interface)) ;
		return instance ;
	}

	std::shared_ptr<IPacketSniffer> ethcdiSingleton(const std::string& interface)
	{
		static std::shared_ptr<IPacketSniffer> instance(std::make_shared<PacketSniffer>(interface)) ;
		return instance ;
	}

}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IPacketSniffer> IPacketSniffer::singleton(const std::string& interface)
{
	static std::string ethcdi(IAppOptions::getInstance()->getOption("ethcdi").toString()) ;
	static std::string ethbb(IAppOptions::getInstance()->getOption("ethbb").toString()) ;

	if (interface == ethcdi)
		return ethcdiSingleton(ethcdi) ;

	if (interface == ethbb)
		return ethbbSingleton(ethbb) ;

	return std::shared_ptr<IPacketSniffer>() ;
}
