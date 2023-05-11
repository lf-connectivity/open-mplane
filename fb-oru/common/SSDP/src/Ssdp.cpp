/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Ssdp.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "NetDevice.h"
#include "MulticastSocket.h"

#include "SsdpReceiver.h"
#include "SsdpSender.h"
#include "Ssdp.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string Ssdp::SSDP_ADDRESS{"239.255.255.250"} ;
const unsigned Ssdp::SSDP_PORT{41900} ;
//const unsigned Ssdp::SSDP_PORT{51900} ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Ssdp::Ssdp(const std::string& application, const std::string& appVersion,
		const std::string& netInterface,
		unsigned cacheAgeSecs,
		const std::string& xmlPath) :
	TaskEvent(Task::PRIORITY_LOW, Task::SMALL_STACK, "Ssdp", "SSDP"),

    mApp(application),
    mAppVersion(appVersion),
	mNetInterface(netInterface),
	mCacheAgeSecs(cacheAgeSecs),
	mXmlPath(xmlPath),

	mUuid(),
	mIfAddress() ,
	mSock(),
	mRx(),
	mTx()
{
//	// Turn on debugging
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "SSDP") ;

	eventInfo("SSDP start up - interface %s", mNetInterface.c_str()) ;

	// self start - will set up the rest of the class data when the interface is up
	start() ;

	// Register for net state change events
	INetStatus::getInstance()->attach(*this) ;
}

//-------------------------------------------------------------------------------------------------------------
Ssdp::~Ssdp()
{
	eventInfo("SSDP shutdown") ;
	INetStatus::getInstance()->detach(*this) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Ssdp::getIp() const
{
	return mIfAddress ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Ssdp::getUuid() const
{
	return mUuid ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Ssdp::getCacheAge() const
{
	return mCacheAgeSecs ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Ssdp::getSearchCount() const
{
	if (!mTx)
		return 0 ;

	return mTx->getSearchCount() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Ssdp::getNotifyCount() const
{
	if (!mTx)
		return 0 ;

	return mTx->getNotifyCount() ;
}


//-------------------------------------------------------------------------------------------------------------
void Ssdp::update(INetStatus& subject, const INetChange& data)
{
	eventInfo("SSDP update event: %s %s %s",
		data.getInterface().c_str(),
		data.getIp().c_str(),
		INetChange::stateStr(data.getState()).c_str()
	) ;

	// skip events from other interfaces
	if (data.getInterface() != mNetInterface)
		return ;

	// stop on disconnect events
	if (data.getState() == INetChange::NetState::NET_DISCONNECTED)
	{
		stopSsdp() ;
		return ;
	}

	// pass down event
	mIfAddress = data.getIp() ;
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
const char* Ssdp::name() const
{
	return "SSDP" ;
}

//-------------------------------------------------------------------------------------------------------------
void Ssdp::injectExtraFields(const std::map<std::string, std::string>& fields)
{
	for (auto entry : fields)
	{
		mExtraFields[entry.first] = entry.second ;
	}

	if (!mTx)
		return ;

	mTx->injectExtraFields(mExtraFields) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Ssdp::runEvent()
{
	stopSsdp() ;

	eventInfo("SSDP: Check '%s'...", mNetInterface.c_str()) ;

	// Wait for network up
	std::shared_ptr<NetDevice> nd(waitInterface(mNetInterface)) ;
	if (!nd)
	{
		eventInfo("SSDP: Error with '%s' - interface is not up", mNetInterface.c_str()) ;
		return true ;
	}

	mIfAddress = nd->getAddr() ;
	mUuid = createUuid(nd->getMac()) ;

	eventInfo("SSDP: '%s' up - IP=%s UUID=%s", mNetInterface.c_str(), mIfAddress.c_str(), mUuid.c_str()) ;

	// Add the multicast route
	bool routeOk = nd->addRoute("224.0.0.0", "240.0.0.0") ;

	eventInfo("SSDP: route added %s", (routeOk ? "OK" : "FAIL")) ;

	// Create sender
	mTx = std::make_shared<SsdpSender>(mUuid, SSDP_ADDRESS, SSDP_PORT,
			mIfAddress, mCacheAgeSecs,
			mApp, mAppVersion,
			mXmlPath) ;
	mTx->injectExtraFields(mExtraFields) ;

	// Create receiver
	mRx = std::make_shared<SsdpReceiver>(mUuid, SSDP_ADDRESS, SSDP_PORT,
		[this](unsigned maxWaitSecs){mTx->searchRequest(maxWaitSecs);}
	) ;

	// done
	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<NetDevice> Ssdp::waitInterface(const std::string& interfaceName) const
{
	std::shared_ptr<NetDevice> nd(std::make_shared<NetDevice>()) ;
	nd->open(interfaceName) ;

	// If interface isn't up with a valid IP address at this stage then there's been an error so stop
	if (!nd->isUp())
		return std::shared_ptr<NetDevice>() ;

	if (nd->getAddr() == "0.0.0.0")
		return std::shared_ptr<NetDevice>() ;

	if (nd->getAddr().empty())
		return std::shared_ptr<NetDevice>() ;

	return nd ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Ssdp::createUuid(const std::string& mac) const
{
	return "acea8150-0000-0000-0000-" + mac ;
}

//-------------------------------------------------------------------------------------------------------------
void Ssdp::stopSsdp()
{
	if (mTx)
	{
		mTx->shutdown() ;
		mTx.reset() ;
	}

	if (mRx)
	{
		mRx->shutdown() ;
		mRx.reset() ;
	}
}
