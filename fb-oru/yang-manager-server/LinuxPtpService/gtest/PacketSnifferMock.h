/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PacketSnifferMock.h
 * \brief     Virtual interface to sniff packets on a network interface
 *
 *
 */


#ifndef SNIFFER_INC_PACKETSNIFFERMOCK_H_
#define SNIFFER_INC_PACKETSNIFFERMOCK_H_

#include <string>
#include <memory>
#include <functional>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "IPacketSniffer.h"


namespace Mplane {

/*!
 * \class  PacketSnifferMock
 * \brief  Virtual interface to sniff packets on a network interface
 *
 */
class PacketSnifferMock : public virtual IPacketSniffer {
public:

	PacketSnifferMock() {}
	virtual ~PacketSnifferMock() {}

	/**
	 * Register a callback that is called when a packet is received that passes the filter criteria
	 */
	virtual void registerPacketCbFunc(std::string filter, PacketCallbackFunc func) override ;

	void dispatchPacket(const unsigned char* data, unsigned int len);
private:

	std::vector<PacketCallbackFunc> mCallbacks;
} ;

}

#endif /* SNIFFER_INC_PACKETSNIFFERMOCK_H_ */
