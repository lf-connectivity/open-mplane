/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MulticastSocket.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>  // needed for memset

#include <iostream>
#include "MulticastSocket.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
std::string MulticastSocket::MULTICAST_ADDRESS{"239.255.255.250"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
MulticastSocket::MulticastSocket() :
	Socket()
{
}

//-------------------------------------------------------------------------------------------------------------
MulticastSocket::~MulticastSocket()
{
}

//-------------------------------------------------------------------------------------------------------------
bool MulticastSocket::create()
{
    mSock = ::socket(AF_INET, SOCK_DGRAM, 0);

	if (!isValid())
		return false ;

	// Set socket options
	int off = 0;
	int on = 1;
	u_char ttl{16} ; // default TTL to 16

	// Join the multicast group on the local interface. Note that this IP_ADD_MEMBERSHIP option must be called for each local interface over which the multicast datagrams are to be received.
	if (
		(setsockopt(mSock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) != ERROR)
		&& (setsockopt(mSock, IPPROTO_IP, IP_MULTICAST_TTL, (const char*) &ttl, sizeof(ttl)) != ERROR)
		&& (setsockopt(mSock, IPPROTO_IP, IP_MULTICAST_LOOP, (const char*) &off, sizeof(off)) != ERROR)
	)
	{
		return true;
	}

    close();
    return false;
}

//-------------------------------------------------------------------------------------------------------------
bool MulticastSocket::setMulticast(const std::string& addr, unsigned port)
{
	// Initialize the address
	memset((char *) &mAddress, 0, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(addr.c_str());
	mAddress.sin_port = htons(port);

	struct ip_mreq mreq ;
	mreq.imr_multiaddr.s_addr = ::inet_addr(addr.c_str());
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if (
		(setsockopt(mSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) != ERROR)
	)
	{
		return true;
	}

//std::cerr << "MulticastSocket::setMulticast(" << addr << ":" << port << ") FAIL errno=" << errno << std::endl ;

	close() ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool MulticastSocket::send(const std::string& s)
{
    socklen_t addrlen=sizeof(mAddress);

	// Send the data - if we get the EAGAIN error then try resending a few times before bailing
	unsigned retryCount(10) ;
	while (retryCount > 0)
	{
		if (::sendto(mSock, s.c_str(), s.size(), MSG_NOSIGNAL, (struct sockaddr *) &mAddress, addrlen) != ERROR)
			return true;

		std::cerr << "MulticastSocket::send errno=" << errno << " retry=" << retryCount << std::endl ;

		if ( (errno != EAGAIN) && (errno != EWOULDBLOCK) )
			return false ;

		if (--retryCount == 0)
			return false ;

		// Pause briefly
	    struct timespec ts{0, 1000};
	    nanosleep(&ts, (struct timespec *)0);
	}
    return false;

}

//-------------------------------------------------------------------------------------------------------------
int MulticastSocket::recv(std::string& s)
{
    int maxRecBuf = 512;
    char buf[maxRecBuf + 1];

    s = "";

    memset(buf, 0, maxRecBuf + 1);

    socklen_t addrlen(sizeof(mAddress));
    int status = ::recvfrom(mSock, buf, maxRecBuf, 0, (struct sockaddr *) &mAddress, &addrlen);

    if (status == ERROR)
    {
    	if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
    	{
    		// non-blocking
    		s = buf ;
    		return 0 ;
    	}
    	else
    	{
//			std::cout << "status == -1   errno == " << errno
//					<< "  in Socket::recv\n";
			return status;
    	}
    }

	if (status == 0)
		return 0;

	if (mBinary)
	{
		// Use range constructor to ensure binary data (e.g. telnet control sequences) get copied across
		// properly (otherwise 0 will terminate the string prematurely)
		s = std::string(buf, buf+status) ;
	}
	else
	{
		// text copy
		s = buf ;
	}
    return status;
}
