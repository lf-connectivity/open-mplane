/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SsdpSender.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <cstdint>

#include "IAppOptions.h"
#include "MulticastSocket.h"
#include "SsdpSender.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// Time everything in 100ms chunks
static const unsigned PERIOD_MS{100} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SsdpSender::SsdpSender(const std::string& uuid, const std::string& address, unsigned port,
		const std::string& ifAddress, unsigned cacheAgeSecs,
		const std::string& application, const std::string& appVersion,
		const std::string& xmlPath) :
	TaskPeriodicEvent(PERIOD_MS, Task::PRIORITY_LOW, Task::SMALL_STACK, "SsdpTx", "SSDP"),

	mUuid(uuid),
	mAddress(address),
	mPort(port),
	mIfAddress(ifAddress),
	mCacheAgeSecs(cacheAgeSecs),
	mXmlPath(xmlPath),

	mUnameInfo(),
	mApplication(application),
	mAppVersion(appVersion),


	mSock( std::make_shared<MulticastSocket>() ),
	mRandGen( ::time(0) ),
	mRandBurstDist(1, 8),
	mRandAgeDist( secsToCount(cacheAgeSecs/4), secsToCount(cacheAgeSecs/2) ),
	mNotifyCountdown( mRandBurstDist(mRandGen) ),
	mOkMsg(),
	mNotifyMsg(),

	mMutex(),
	mState( SendState::NOTIFY ),
	mMaxWaitSecs(1),
    mSearchCount(0),
    mNotifyCount(0),
	mExtraFields()
{
//	// Turn on debugging
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "SSDP") ;

	eventInfo("SSDP: SsdpSender startup") ;

	if (!mSock->create())
	{
		eventError("SSDP: Failed to create multicast send socket") ;
		return ;
	}

	if (!mSock->setMulticast(address, port))
	{
		eventError("SSDP: Failed to set multicast send address:port") ;
		return ;
	}

	// Get OS info
	::uname(&mUnameInfo);

	// create the messages
	mOkMsg = createOkMsg(
		mUnameInfo.sysname,
		mUnameInfo.release,
		mUnameInfo.nodename,
		mApplication,
		mAppVersion
	) ;
	mNotifyMsg = createNotifyMsg(
		mUnameInfo.sysname,
		mUnameInfo.release,
		mUnameInfo.nodename,
		mApplication,
		mAppVersion
	) ;
}

//-------------------------------------------------------------------------------------------------------------
SsdpSender::~SsdpSender()
{
	eventInfo("SSDP: SsdpSender shutdown") ;
}

//-------------------------------------------------------------------------------------------------------------
void SsdpSender::searchRequest(unsigned maxWaitSecs)
{
	// Lock state
	{
		Mutex::Lock lock(mMutex) ;

		logDebugVerbose("SSDP: Search Request MX=%u [STATE %s]", maxWaitSecs,
				(mState == SendState::MSEARCH_REPLY ? "MSEARCH" : "NOTIFY")) ;


		// skip if already responding
		if (mState == SendState::MSEARCH_REPLY)
		{
			logDebugVerbose("SSDP: Search Request SKIPPED (Notify countdown %u)",mNotifyCountdown) ;
			return ;
		}

		mMaxWaitSecs = maxWaitSecs ;
	}

	// Just create an event to cause the response from the search
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SsdpSender::getSearchCount() const
{
	Mutex::Lock lock(mMutex) ;
	return mSearchCount ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SsdpSender::getNotifyCount() const
{
	Mutex::Lock lock(mMutex) ;
	return mNotifyCount ;
}

//-------------------------------------------------------------------------------------------------------------
void SsdpSender::injectExtraFields(const std::map<std::string, std::string>& fields)
{
	Mutex::Lock lock(mMutex) ;
	for (auto entry : fields)
	{
		mExtraFields[entry.first] = entry.second ;
	}

	// create the messages
	mOkMsg = createOkMsg(
		mUnameInfo.sysname,
		mUnameInfo.release,
		mUnameInfo.nodename,
		mApplication,
		mAppVersion
	) ;
	mNotifyMsg = createNotifyMsg(
		mUnameInfo.sysname,
		mUnameInfo.release,
		mUnameInfo.nodename,
		mApplication,
		mAppVersion
	) ;

}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool SsdpSender::runEvent()
{
	// Lock state
	Mutex::Lock lock(mMutex) ;

	// if this is an event, schedule send the OK response
	if (isEvent())
	{
		mState = SendState::MSEARCH_REPLY ;

		unsigned maxCount( secsToCount( mMaxWaitSecs ) ) ;
		std::uniform_int_distribution<unsigned> randWaitDist(1, maxCount) ;
		mNotifyCountdown = randWaitDist(mRandGen) ;
		if (mNotifyCountdown == 0)
			mNotifyCountdown = 1 ;

		logDebugVerbose("SSDP: Search Request MX=%u scheduled OK - count %u",
				mMaxWaitSecs,
				mNotifyCountdown) ;

		return true ;
	}

	// Periodic timeout - see if counter has reached the point where we need to send a NOTIFY or OK
	if (--mNotifyCountdown == 0)
	{
		// Schedule the next notification
		mNotifyCountdown = mRandAgeDist(mRandGen) ;

		logDebugVerbose("SSDP: Countdown=0 [STATE %s] New Count=%u (for age=%u secs)",
			(mState == SendState::MSEARCH_REPLY ? "MSEARCH" : "NOTIFY"),
			mNotifyCountdown, mCacheAgeSecs) ;

		// If in M-SEARCH response state, send the response
		if (mState == SendState::MSEARCH_REPLY)
		{
			mState = SendState::NOTIFY ;
			++mSearchCount ;

			logDebugNormal("SSDP: Send OK") ;

			// send OK
			if (!mSock->send(mOkMsg))
			{
//				std::cerr << "SsdpSender::runEvent() send OK - FAIL" << std::endl ;
			}
		}
		else
		{
			++mNotifyCount ;

			logDebugNormal("SSDP: Send NOTIFY") ;

			// send NOTIFY
			if (!mSock->send(mNotifyMsg))
			{
//				std::cerr << "SsdpSender::runEvent() send NOTIFY - FAIL" << std::endl ;
			}
		}
	}

	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned SsdpSender::secsToCount(unsigned secs) const
{
	return secs * 1000 / PERIOD_MS ;
}


//-------------------------------------------------------------------------------------------------------------
std::string SsdpSender::createOkMsg(const std::string& os, const std::string& osRelease,
		const std::string& node,
		const std::string& application, const std::string& appVersion) const
{
	return createBaseMsg("HTTP/1.1 200 OK\r\n", os, osRelease, node, application, appVersion) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SsdpSender::createNotifyMsg(const std::string& os, const std::string& osRelease,
		const std::string& node,
		const std::string& application, const std::string& appVersion) const
{
	return createBaseMsg("NOTIFY * HTTP/1.1\r\n", os, osRelease, node, application, appVersion) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SsdpSender::createBaseMsg(const std::string& head,
		const std::string& os, const std::string& osRelease,
		const std::string& node,
		const std::string& application, const std::string& appVersion) const
{
	std::string msg(head) ;

	msg += "HOST: " + mAddress + ":" + std::to_string(mPort) + "\r\n" ;
	msg += "CACHE-CONTROL: max-age=" + std::to_string(mCacheAgeSecs) + "\r\n" ;

	if (mXmlPath.empty())
	{
		// no xml file so return the ip:port access for tif
		std::shared_ptr<IAppOptions> appOptions(IAppOptions::getInstance()) ;
		unsigned tifPort{ static_cast<unsigned>(appOptions->getOption("port").toInt()) } ;
		msg += "LOCATION: " + mIfAddress + ":" + std::to_string(tifPort) + "\r\n" ;
	}
	else
	{
		msg += "LOCATION: http://" + mIfAddress + "/" + mXmlPath + "\r\n" ;
	}

	msg += "NT: uuid:" + mUuid + "\r\n" ;
	msg += "NTS: \"sdp-alive\" \r\n" ;
	msg += "SERVER: " + os + "/" + osRelease + " UPnP/1.1 " + application + "/" + appVersion  + "\r\n" ;
	msg += "USN: uuid:" + mUuid + "\r\n" ;

	// Add a few AXIS-specific fields
	msg += "AXIS-IP: " + mIfAddress + "\r\n" ;
	msg += "AXIS-UNIT: " + application + "\r\n" ;
	msg += "AXIS-HOST: " + node + "\r\n" ;

	// Add any extra fields
	for (auto entry : mExtraFields)
	{
		msg += entry.first + ": " + entry.second + "\r\n" ;
	}

	// EOM
	msg += "\r\n" ;

	return msg ;
}
