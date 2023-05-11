/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SsdpReceiver.h
 * \brief     Receiver task for SSDP
 *
 *
 * \details   Monitors for M-SEARCH requests
 *
 */


#ifndef SSDPRECEIVER_H_
#define SSDPRECEIVER_H_

#include <string>
#include <memory>
#include <functional>

#include "TaskPeriodicEvent.h"

namespace Mplane {

class MulticastSocket ;

class SsdpReceiver : public TaskPeriodicEvent {
public:
	using SearchRequest = std::function<void(unsigned maxWaitSecs)> ;

	SsdpReceiver(const std::string& uuid, const std::string& address, unsigned port,
			SearchRequest request) ;
	virtual ~SsdpReceiver() ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
    std::string mUuid ;
    std::string mAddress ;
    unsigned mPort ;
    SearchRequest mRequest ;
	std::shared_ptr<MulticastSocket> mSock ;
} ;

}

#endif /* SSDPRECEIVER_H_ */
