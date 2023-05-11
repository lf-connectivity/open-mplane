/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SsdpSender.h
 * \brief     Send out SSDP messages
 *
 *
 * \details
 *
 */


#ifndef SSDPSENDER_H_
#define SSDPSENDER_H_

#include <sys/utsname.h>
#include <time.h>

#include <map>
#include <random>
#include <string>
#include <memory>
#include <functional>

#include "TaskPeriodicEvent.h"

namespace Mplane {

class MulticastSocket ;


class SsdpSender : public TaskPeriodicEvent {
public:
	SsdpSender(const std::string& uuid, const std::string& address, unsigned port,
			const std::string& ifAddress, unsigned cacheAgeSecs,
			const std::string& application, const std::string& appVersion,
			const std::string& xmlPath) ;
	virtual ~SsdpSender() ;

	/**
	 * Method called in response to an M-SEARCH
	 */
	void searchRequest(unsigned maxWaitSecs) ;

	/**
	 * Get the number of M-SEARCH messages responded to. An M-SEARCH is sent out by a controlling entity to discover what's connected
	 * to the network
	 */
	unsigned getSearchCount() const ;

	/**
	 * Get the number of NOTIFY messages sent. This node sends out notifications randomly (within a max delay period) in order to tell
	 * all controlling entities of it's presence
	 */
	unsigned getNotifyCount() const ;

	/**
	 * Add additional fields to the response message
	 */
	void injectExtraFields(const std::map<std::string, std::string>& fields) ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	unsigned secsToCount(unsigned secs) const ;
	std::string createOkMsg(const std::string& os, const std::string& osRelease,
			const std::string& node,
			const std::string& application, const std::string& appVersion) const ;
	std::string createNotifyMsg(const std::string& os, const std::string& osRelease,
			const std::string& node,
			const std::string& application, const std::string& appVersion) const ;
	std::string createBaseMsg(const std::string& head, const std::string& os, const std::string& osRelease,
			const std::string& node,
			const std::string& application, const std::string& appVersion) const ;

private:
	enum class SendState {
		NOTIFY,
		MSEARCH_REPLY
	};

private:
    std::string mUuid ;
    std::string mAddress ;
    unsigned mPort ;
    std::string mIfAddress ;
    unsigned mCacheAgeSecs ;
    std::string mXmlPath ;

	struct utsname mUnameInfo ;
	std::string mApplication ;
	std::string mAppVersion ;


	std::shared_ptr<MulticastSocket> mSock ;
    std::default_random_engine mRandGen ;
    std::uniform_int_distribution<unsigned> mRandBurstDist ;
    std::uniform_int_distribution<unsigned> mRandAgeDist ;
    unsigned mNotifyCountdown ;

    std::string mOkMsg ;
    std::string mNotifyMsg ;

    mutable Mutex mMutex ;
    SendState mState ;
    unsigned mMaxWaitSecs ;
    unsigned mSearchCount ;
    unsigned mNotifyCount ;

    std::map<std::string, std::string> mExtraFields ;
} ;

}

#endif /* SSDPSENDER_H_ */
