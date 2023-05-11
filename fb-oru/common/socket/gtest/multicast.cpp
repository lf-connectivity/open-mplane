/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      multicast.cpp
 * \brief
 *
 *
 * \details
 *
 */

// Need to add route first as:
//
// sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev eth0

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "MulticastSocket.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string MSEARCH(
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST: 239.255.255.250:1900\r\n"
    "MAN: \"ssdp:discover\"\r\n"
    "MX: 3\r\n"
    "ST: ssdp:all\r\n"
    "\r\n"
) ;


int main(void)
{
	MulticastSocket msock ;

	if (!msock.create())
	{
		std::cerr << "ERROR: Unable to create multicast socket" << std::endl ;
		return 1 ;
	}

	if (!msock.setMulticast(MulticastSocket::MULTICAST_ADDRESS, 1900))
	{
		std::cerr << "ERROR: Unable to bind to multicast port" << std::endl ;
		return 1 ;
	}


//std::cerr << "M-SEARCH.." << std::endl ;
//
//	// Chuck out a search
//	if (!msock.send(MSEARCH))
//	{
//		std::cerr << "ERROR: Unable to send message" << std::endl ;
//		return 1 ;
//	}


	if (!msock.bind(1900))
	{
		std::cerr << "ERROR: Unable to bind" << std::endl ;
		return 1 ;
	}

	// listen for client notifications
	std::string buff ;
	while(1)
	{

std::cerr << "Listening for messages.." << std::endl ;

		int numBytes(msock.recv(buff)) ;
		if (numBytes <= 0)
		{
			std::cerr << "ERROR: Unable to receive message" << std::endl ;
			return 1 ;
		}

        printf("RX: '%s'\n\n", buff.c_str()) ;
	}

    return 0;
}
