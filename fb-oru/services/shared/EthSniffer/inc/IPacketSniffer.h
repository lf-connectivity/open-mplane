/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPacketSniffer.h
 * \brief     Virtual interface to sniff packets on a network interface
 *
 *
 */


#ifndef SNIFFER_INC_IPACKETSNIFFER_H_
#define SNIFFER_INC_IPACKETSNIFFER_H_

#include <string>
#include <memory>
#include <functional>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>


namespace Mplane {

/*!
 * \class  IPacketSniffer
 * \brief  Virtual interface to sniff packets on a network interface
 *
 */
class IPacketSniffer {
public:

	/**
	 * Singleton
	 */
	static std::shared_ptr<IPacketSniffer> singleton(const std::string& interface) ;

	IPacketSniffer() {}
	virtual ~IPacketSniffer() {}

	/* Ethernet addresses are 6 bytes */
	static const int ETHER_ADDR_LEN = 6;
	static const int ETHER_TYPE_LEN = 2;
	static const int SIZE_ETHERNET = 14;

	/* Ethernet header */
	struct sniff_ethernet {
		u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
		u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
		u_char ether_type[ETHER_TYPE_LEN]; /* IP? ARP? RARP? etc */
	}__attribute__((packed, aligned(1)));

	/* IP header */
	struct sniff_ip {
		u_char ip_vhl;		/* version << 4 | header length >> 2 */
		u_char ip_tos;		/* type of service */
		u_short ip_len;		/* total length */
		u_short ip_id;		/* identification */
		u_short ip_off;		/* fragment offset field */
    #define IP_RF 0x8000		/* reserved fragment flag */
	#define IP_DF 0x4000		/* don't fragment flag */
	#define IP_MF 0x2000		/* more fragments flag */
	#define IP_OFFMASK 0x1fff	/* mask for fragmenting bits */
		u_char ip_ttl;		/* time to live */
		u_char ip_p;		/* protocol */
		u_short ip_sum;		/* checksum */
		struct in_addr ip_src,ip_dst; /* source and dest address */
	};

    #define IP_HL(ip)		(((ip)->ip_vhl) & 0x0f)
    #define IP_V(ip)		(((ip)->ip_vhl) >> 4)

	/* TCP header */
	typedef u_int tcp_seq;

	struct sniff_tcp {
		u_short th_sport;	/* source port */
		u_short th_dport;	/* destination port */
		tcp_seq th_seq;		/* sequence number */
		tcp_seq th_ack;		/* acknowledgement number */
		u_char th_offx2;	/* data offset, rsvd */
	#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)
		u_char th_flags;
	#define TH_FIN 0x01
	#define TH_SYN 0x02
	#define TH_RST 0x04
	#define TH_PUSH 0x08
	#define TH_ACK 0x10
	#define TH_URG 0x20
	#define TH_ECE 0x40
	#define TH_CWR 0x80
	#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
		u_short th_win;		/* window */
		u_short th_sum;		/* checksum */
		u_short th_urp;		/* urgent pointer */
	};
	/**
	 * Callback function for when a packet is received
	 */
	using PacketCallbackFunc = std::function<void(const struct pcap_pkthdr *, const unsigned char*, unsigned int)> ;

	/**
	 * Register a callback that is called when a packet is received that passes the filter criteria
	 */
	virtual void registerPacketCbFunc(std::string filter, PacketCallbackFunc func) =0 ;
} ;

}

#endif /* SNIFFER_INC_IPACKETSNIFFER_H_ */
