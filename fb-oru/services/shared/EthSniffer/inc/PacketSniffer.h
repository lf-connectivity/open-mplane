/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PacketSniffer.h
 * \brief     Virtual interface to sniff packets on a network interface
 *
 *
 */


#ifndef SNIFFER_INC_PACKETSNIFFER_H_
#define SNIFFER_INC_PACKETSNIFFER_H_

#include <string>
#include <memory>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <mutex>
#include "Task.h"
#include "TaskEvent.h"
#include "IPacketSniffer.h"

namespace Mplane {

class PacketDispatcher : public TaskEvent
{
public:
	/*
	 * Constructor
	 */
	PacketDispatcher();

	/*
	 * Destructor
	 */
	~PacketDispatcher();

	/*
	 * Method to add callback
	 */
	void addCallback(IPacketSniffer::PacketCallbackFunc);

	struct dispatchItem {
	    struct pcap_pkthdr header;
	    u_char* data;
	    unsigned int len;
	};

	/*
	 * Method to dispatch the packets to the registered callbacks
	 */
	void dispatchPackets(const struct pcap_pkthdr *header, const unsigned char *packet);

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override;

private:

	std::vector<IPacketSniffer::PacketCallbackFunc> mCallbacks;
	std::queue<dispatchItem> mItems;
	std::mutex mMutex;

};

/*!
 * \class  PacketSniffer
 * \brief  Virtual interface to sniff packets on a network interface
 *
 */
class PacketSniffer : public virtual IPacketSniffer, public Task {
public:

	PacketSniffer(std::string interfaceName);
	virtual ~PacketSniffer();

	/**
	 * Register a callback that is called when a packet is received that passes the filter criteria
	 */
	virtual void registerPacketCbFunc(std::string filter, PacketCallbackFunc func) override ;

	std::shared_ptr<PacketDispatcher> dispatcher(void);

protected:

    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() override;

private:

    static const int SNAP_LEN = 1518;

    enum SnifferStates
	{
    	SNIFFER_IDLE,
    	SNIFFER_INIT,
		SNIFFER_RUN
	};

    std::vector<std::pair<std::string, PacketCallbackFunc>> mRegisteredObjects; //!> Vector of filters and callback functions that have registered with the Packet sniffer
    bool mShutdown;                                         //!> Flag to indicate that task needs to stop
    SnifferStates mSnifferState;                            //!> State of the packet sniffer
    std::string mInterfaceName;                             //!> Name of the network interface on which packets need to be captured
    bool mInterfaceAllocatedIp;                             //!> Flag to indicate that the interface got an IP address from DHCP server
    std::shared_ptr<PacketDispatcher> mDispatcher;          //!> Pointer to packet dispatcher
    char mErrbuf[PCAP_ERRBUF_SIZE];                         //!> error buffer
    pcap_t *mHandle;                                        //!> packet capture handle
    struct bpf_program mFp;                                 //!> compiled filter program (expression)
    bpf_u_int32 mSubnetMask;                                //!> subnet mask
    bpf_u_int32 mNet;                                       //!> ip
    std::mutex mMutex;

    /*
     * Method to compile and setup a filter expression
     */
    int updateFilter(void);

    /*
     * Callback function provided to pcap library
     */
    static void gotPacket(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet);


} ;

}

#endif /* SNIFFER_INC_PACKETSNIFFER_H_ */
