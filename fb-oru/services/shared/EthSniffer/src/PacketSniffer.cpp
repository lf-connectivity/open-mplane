/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PacketSniffer.cpp
 * \brief     Virtual interface to sniff packets on a network interface
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "PacketSniffer.h"
#include "INetworkingService.h"
#include "INetAddrPolicy.h"

#include <cstring>

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PacketDispatcher::PacketDispatcher() :
		TaskEvent(Task::PRIORITY_MEDIUM, Task::StackSize::MEDIUM_STACK, "PacketDispatcher", "PCAP")
{
}

//-------------------------------------------------------------------------------------------------------------
PacketDispatcher::~PacketDispatcher()
{

}

//-------------------------------------------------------------------------------------------------------------
void PacketDispatcher::addCallback(IPacketSniffer::PacketCallbackFunc func)
{
	mCallbacks.push_back(func);
}

//-------------------------------------------------------------------------------------------------------------
void PacketDispatcher::dispatchPackets(const struct pcap_pkthdr *header, const unsigned char *packet)
{
	dispatchItem item;

	// Copy the header into the item structure
	item.header = *header;
	item.data = new u_char[header->caplen];
	item.len = header->caplen;

	// Copy the data into the item structure
	memcpy(item.data, packet, header->caplen);

	{
		std::unique_lock<std::mutex> guard(mMutex);
		// Queue the item
		mItems.push(item);
	}
	// Signal the task to run
	event();
}

//-------------------------------------------------------------------------------------------------------------
PacketSniffer::PacketSniffer(std::string interfaceName) :
		Task(Task::PRIORITY_LOW, Task::StackSize::MEDIUM_STACK, "PacketSniffer", "PCAP"),
		mRegisteredObjects(),
		mShutdown(false),
		mSnifferState(SNIFFER_IDLE),
		mInterfaceName(interfaceName),
		mInterfaceAllocatedIp(false),
		mDispatcher(std::make_shared<PacketDispatcher>()),
		mErrbuf(),
		mHandle()
{
	// Network services access
	auto ns(INetworkingService::singleton(mInterfaceName));
	ns->pause() ;
	auto policy(ns->getNetAddrPolicy()) ;

	policy->registerAllocatedFunc([this](const std::string& interface, const std::string& ipAddress, const std::string& macAddress,
			const std::string& allocatorName, INetChange::NetState allocatorType)
	{
		if (allocatorType == INetChange::NET_DHCP)
		{
			mInterfaceAllocatedIp = true;
		}
	}) ;

	ns->restart() ;

	// self start
	start();
}

//-------------------------------------------------------------------------------------------------------------
PacketSniffer::~PacketSniffer()
{
	mShutdown = true;

	// If pcap looping was started, then break the loop
	if (mHandle && mSnifferState == SNIFFER_RUN)
	{
		pcap_breakloop(mHandle);
	}
}

//-------------------------------------------------------------------------------------------------------------
void PacketSniffer::registerPacketCbFunc(std::string filter, IPacketSniffer::PacketCallbackFunc func)
{
	mRegisteredObjects.push_back(std::make_pair(filter, func));
	mDispatcher->addCallback(func);

	// Update filter in case the pcap is setup
	updateFilter();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<PacketDispatcher> PacketSniffer::dispatcher(void)
{
	return mDispatcher;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool PacketDispatcher::runEvent()
{
	std::unique_lock<std::mutex> guard(mMutex);

	// Loop till queue has items
	while (mItems.empty() == false)
	{
		// Get the front item
		dispatchItem item = mItems.front();

		// Pass the item to all callbacks
		for (auto & cb : mCallbacks)
		{
			if (cb)
			{
				cb(&item.header, item.data, item.len);
			}
		}

		delete [] mItems.front().data;

		// Pop the item from the queue
		mItems.pop();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
int PacketSniffer::run()
{
	int error = EXIT_FAILURE;

	while (!mShutdown)
	{
		switch (mSnifferState)
		{
		case SNIFFER_IDLE:
		{
			// Start capturing the packets once the IP is allocated to the network interface and
			// someone has registered to receive the packets
			if (mInterfaceAllocatedIp && mRegisteredObjects.size() > 0)
			{
				mSnifferState = SNIFFER_INIT;
			}
		}
		break;

		case SNIFFER_INIT:
		{
		    /* get network number and mask associated with capture device */
		    if (pcap_lookupnet(mInterfaceName.c_str(), &mNet, &mSubnetMask, mErrbuf) == -1)
		    {
		    	mNet = 0;
		    	mSubnetMask = 0;
		    	std::cout << "pcap_lookupnet error - " << mErrbuf << std::endl;
		    	break;
		    }

		    /* open capture device, promiscuous with 1000 msec timeout */
		    mHandle = pcap_open_live(mInterfaceName.c_str(), SNAP_LEN, 1, 1000, mErrbuf);
		    if (mHandle == NULL)
		    {
		    	eventError("pcap_open_live error - %s", mErrbuf);
		        return error;
		    }

		    /* make sure we're capturing on an Ethernet device [2] */
		    if (pcap_datalink(mHandle) != DLT_EN10MB)
		    {
		    	eventError("pcap_datalink - Handle is not for ethernet interface");

		    	return error;
		    }

		    // Filter as per registered objects
		    if (updateFilter() != 0)
		    {
		    	return error;
		    }

		    std::cout << "Pcap setup complete" << std::endl;

		    mSnifferState = SNIFFER_RUN;

		}
		break;

		case SNIFFER_RUN:
		{
			/* now we can set our callback function */
			int ret = pcap_loop(mHandle, -1, gotPacket,
					reinterpret_cast<u_char *>(this));
			if (ret == -1)
			{
				eventError("pcap_loop error - %s", pcap_geterr(mHandle));
			}
			else if (ret == -2)
			{
				eventError("pcap_loop stopped");
			}
		}
		break;

		default:
			break;
		}

		Task::msSleep(500);
	}

	// If pcap was started, then close the session and free the compiled filter expression code
	if (mHandle)
	{
		pcap_close(mHandle);
		pcap_freecode(&mFp);
	}

	return 0;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int PacketSniffer::updateFilter(void)
{
	if (mHandle)
	{
		std::unique_lock<std::mutex> guard(mMutex);

	    // Filter as per registered objects
	    std::string filter_exp = "";

	    for (auto & obj : mRegisteredObjects)
	    {
	    	if (filter_exp != "")
	    	{
	    		filter_exp += " or " + obj.first;
	    	}
	    	else
	    	{
	    		filter_exp = obj.first;
	    	}
	    }

	    /* compile the filter expression */
	    if (pcap_compile(mHandle, &mFp, filter_exp.c_str(), 0, mNet) == -1)
	    {
	    	eventError("pcap_compile error for filter expression - %s, Error - %s", filter_exp.c_str(), pcap_geterr(mHandle));
	    	return -1;
	    }

	    /* apply the compiled filter */
	    pcap_setfilter(mHandle, &mFp);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
void PacketSniffer::gotPacket(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet)
{
	PacketSniffer *sniffer=reinterpret_cast<PacketSniffer *>(args);

	// Call dispatch function of event based task that is created as a member
	sniffer->dispatcher()->dispatchPackets(header, packet);
}
