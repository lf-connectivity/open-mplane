// Need to add route first as:
//
// sudo route add -net 224.0.0.0 netmask 240.0.0.0 dev eth0
//

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

const std::string MSEARCH(
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST: 239.255.255.250:1900\r\n"
    "MAN: \"ssdp:discover\"\r\n"
    "MX: 3\r\n"
    "ST: ssdp:all\r\n"
    "\r\n"
) ;

const std::string localIp("10.0.1.168");

using namespace std;

int main()
{
	// Structs needed
	struct sockaddr_in addr;
	struct ip_mreq mreq;

std::cerr << "Starting.." << std::endl ;

	// Create the Socket
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket < 0)
	{
        perror("UDP creation") ;
        return 3 ;
	}

	// Enable SO_REUSEADDR to allow multiple instances of this application to receive copies of the multicast datagrams.
	int on = 1;
	int off = 0 ;
	setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

std::cerr << "memset.." << std::endl ;
	// Initialize the group sockaddr structure with a group address of 239.255.255.250 and port 1900.
	memset((char *) &addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(1900);

std::cerr << "bind.." << std::endl ;
	if (bind(udpSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
        perror("Error binding") ;
        return 2 ;
	}

std::cerr << "mreq.." << std::endl ;
	// Join the multicast group on the local interface. Note that this IP_ADD_MEMBERSHIP option must be called for each local interface over which the multicast datagrams are to be received.
	mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(udpSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq));

    // disable loopback
	setsockopt(udpSocket, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&off, sizeof(off));

std::cerr << "M-SEARCH.." << std::endl ;
	// Chuck out a search
    socklen_t addrlen=sizeof(addr);
    int numBytes = sendto(udpSocket, MSEARCH.c_str(), MSEARCH.size(), 0, (struct sockaddr *) &addr, addrlen) ;
    if (numBytes < 0)
    {
        perror("Receive error") ;
        return 1 ;
    }


	// listen for client notifications
	char buff[1024] ;
	while(1)
	{

std::cerr << "Listening for messages.." << std::endl ;
        addrlen=sizeof(addr);
        int numBytes = recvfrom(udpSocket, buff, sizeof(buff), 0, (struct sockaddr *) &addr,&addrlen) ;
        if (numBytes < 0)
        {
            perror("Receive error") ;
            return 1 ;
        }

        if (numBytes == sizeof(buff))
            --numBytes ;
        buff[numBytes] = '\0' ;

        printf("RX: '%s'\n\n", buff) ;
	}

    return 0;
}

