/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SsdpReceiver.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "MulticastSocket.h"
#include "stringfunc.hpp"

#include "SsdpReceiver.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Don't expect search requests more often then every few seconds, so set periodic timeout to 1 sec
static const unsigned PERIOD_MS{1000} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::SsdpReceiver::SsdpReceiver(const std::string& uuid, const std::string& address, unsigned port,
		SearchRequest request) :
	TaskPeriodicEvent(PERIOD_MS, Task::PRIORITY_LOW, Task::SMALL_STACK, "SsdpRx", "SSDP"),
	mUuid(uuid),
	mAddress(address),
	mPort(port),
	mRequest(request),
	mSock( std::make_shared<MulticastSocket>() )
{
	// Turn on debugging
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "SSDP") ;

	eventInfo("SSDP: SsdpReceiver startup") ;

	if (!mSock->create())
	{
		eventError("SSDP: Failed to create multicast receive socket") ;
		return ;
	}

	if (!mSock->setMulticast(address, port))
	{
		eventError("SSDP: Failed to set multicast receive address:port") ;
		return ;
	}

	if (!mSock->bind(port))
	{
		eventError("SSDP: Failed to bind to multicast receive socket") ;
		return ;
	}

	// Ensure socket is non-blocking
	mSock->setNonBlocking(true) ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SsdpReceiver::~SsdpReceiver()
{
	eventInfo("SSDP: SsdpReceiver shutdown") ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Mplane::SsdpReceiver::runEvent()
{
	std::string buff ;
//	int numBytes(mSock->recv(buff)) ;
//	if (numBytes <= 0)
//		return true ;

	// keep reading buffer until empty
	int numBytes ;

	while ( (numBytes = mSock->recv(buff)) > 0)
	{
		// Got some input
		logDebugVerbose("SSDP: RX from IP=%s Size=%u '%s'", mSock->getIpAddress().c_str(), numBytes, buff.c_str()) ;

		// For now respond to any M-SEARCH
		if (buff.find("M-SEARCH") == std::string::npos)
			continue ;
//			return true ;

		// Find the MX entry
		unsigned maxWaitSecs{1} ;
		std::size_t pos(buff.find("MX:")) ;
		if (pos != std::string::npos)
		{
			bool ok ;
			unsigned mx(extractUnsigned(buff, ok, pos)) ;
			if (ok)
				maxWaitSecs = mx ;
		}

		logDebugNormal("SSDP: M-SEARCH IP=%s MX=%u", mSock->getIpAddress().c_str(), maxWaitSecs) ;

		// Request the sender to reply
		mRequest(maxWaitSecs) ;
	}
	return true ;
}
