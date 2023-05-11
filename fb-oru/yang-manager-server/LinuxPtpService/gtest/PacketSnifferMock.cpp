/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PacketSnifferMock.cpp
 * \brief
 *
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "PacketSnifferMock.h"

using namespace Mplane;


std::shared_ptr<IPacketSniffer> IPacketSniffer::singleton(const std::string& interface)
{
	static std::shared_ptr<IPacketSniffer> instance(std::make_shared<PacketSnifferMock>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

void PacketSnifferMock::registerPacketCbFunc(std::string filter, IPacketSniffer::PacketCallbackFunc func)
{
	mCallbacks.push_back(func);
}

void PacketSnifferMock::dispatchPacket(const unsigned char* data, unsigned int len)
{
	for (auto & cb : mCallbacks)
	{
		if (cb)
		{
			cb(nullptr, data, len);
		}
	}
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================
