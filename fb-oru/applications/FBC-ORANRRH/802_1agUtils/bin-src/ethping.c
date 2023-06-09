/*
 * Copyright (c) 2011
 * Author: Ronald van der Pol
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

#include "ieee8021ag.h"
#include "dot1ag_eth.h"

#include <pcap.h>

#define INTERVAL_MIN      1
#define INTERVAL_MAX      60
#define INTERVAL_DEFAULT  1   	/* send a LBM every second */
#define PCAP_TIMEOUT      100 	/* max number of ms to wait for packet */

/* incremented by 1 for each Loopback Message transmission */
static uint32_t nextLBMtransID;
static int transIDpos = 0;
int next_lbm = 0;
int got_reply = 0;
int count = 5;	/* default is to send five LBMs */
static pcap_t *handle;

static void
usage();


static void
timeout_handler(int sig) {
	next_lbm = 1;
	count--;
	nextLBMtransID++;
	pcap_breakloop(handle);   /* XXX is this needed? */
}


int
main(int argc, char **argv) {
	int ch;
	char *ifname = NULL;
	uint8_t md_level = 0;
	uint16_t vlan = 0;
	char *target;
	uint8_t outbuf[ETHER_MAX_LEN];
	int pktsize = 0;
	int size = 0;
	uint8_t localmac[ETHER_ADDR_LEN];
	uint8_t remotemac[ETHER_ADDR_LEN];
	struct timeval time_sent;
	struct bpf_program filter;  /* compiled BPF filter */
	char filter_src[1024];
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr *header;	/* header returned by pcap */
	const u_char *pkt_data;
	struct itimerval tval;
	struct sigaction act;
	struct timeval now;
	uint32_t interval = INTERVAL_DEFAULT;

	/* parse command line options */
	while ((ch = getopt(argc, argv, "hi:v:l:c:t:")) != -1) {
		switch(ch) {
		case 'h':
			usage();
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'v':
			vlan = atoi(optarg);
			break;
		case 'l':
			md_level = atoi(optarg);
			break;
		case 'c':
			count = atoi(optarg);
			break;
		case 't':
			interval = atoi(optarg);
			break;
		case '?':
		default:
			usage();
		}
	}
	if (argc - optind != 1) {
		usage();
	}

	/* check for mandatory '-i' flag */
	if (ifname == NULL) {
		usage();
	}

	/* final command line argument is Ethernet address to ethping */
	target = argv[optind];
	if (eth_addr_parse(remotemac, target) != 0) {
		usage();
		exit(EXIT_FAILURE);
	}
	/* command line argument parsing finished */

	/* get Ethernet address of outgoing interface */
	if (get_local_mac(ifname, localmac) != 0) {
		perror(ifname);
		exit(EXIT_FAILURE);
	}

	/*
	 * Below the outgoing Ethernet frame is built
	 */

	/* clear outgoing packet buffer */
	memset(outbuf, 0, sizeof(outbuf));

	/* add CFM encapsulation header to packet */
	cfm_addencap(vlan, localmac, remotemac, outbuf, &size);
	pktsize += size;
	
	/* add CFM common header to packet */
	cfm_addhdr(md_level, 0, FIRST_TLV_LBM, CFM_LBM, outbuf + pktsize);
	pktsize += sizeof(struct cfmhdr);

	/* add 4 octet Loopback Transaction Identifier to packet */
	transIDpos = pktsize;
	/* seed random generator */
	srandom(time(0));
	/* initialise transaction ID with random value */
	nextLBMtransID = random();
	*(uint32_t *)(outbuf + transIDpos) = htonl(nextLBMtransID);
	pktsize += sizeof(uint32_t);

	/* XXX code below needs cleanup */
	/*
	 *  finally add Sender ID TLV
	 */

	/* Type */
	*(uint8_t *)(outbuf + pktsize) = TLV_SENDER_ID;
	pktsize += sizeof(uint8_t);
	/* minimal length of 1 */
	*(uint16_t *)(outbuf + pktsize) = htons(1);
	pktsize += sizeof(uint16_t);
	/* Chassis ID Length is 0 (no Chassis ID present) */
	*(uint8_t *)(outbuf + pktsize) = 0;
	pktsize += sizeof(uint8_t);

	/* end packet with End TLV field */
	*(uint8_t *)(outbuf + pktsize) = htons(TLV_END);
	pktsize += sizeof(uint8_t);

	/* Assembled Ethernet frame is 'outbuf', its size is 'pktsize' */

	/* open pcap device for listening */
	handle = pcap_open_live(ifname, BUFSIZ, 1, 200, errbuf);
	if (handle == NULL) {
		perror(errbuf);
		exit(EXIT_FAILURE);
	}

	/* Compile and apply the filter */

	/*
	 * Filter on CFM frames, i.e. ether[12:2] == 0x8902 for untagged
	 * frames or ether[16:2] == 0x8902 for tagged frames. Destination
	 * MAC address should be our MAC address.
	 */
	sprintf(filter_src, "ether dst %02x:%02x:%02x:%02x:%02x:%02x and "
		"(ether[12:2] == 0x%x or "
		" (ether[12:2] == 0x%x and ether[16:2] == 0x%x))",
		localmac[0], localmac[1], localmac[2],
		localmac[3], localmac[4], localmac[5],
		ETYPE_CFM, ETYPE_8021Q, ETYPE_CFM);
	pcap_compile(handle, &filter, filter_src, 0, 0);
	pcap_setfilter(handle, &filter);

	printf("Sending CFM LBM to %02x:%02x:%02x:%02x:%02x:%02x...\n",
		remotemac[0], remotemac[1], remotemac[2],
		remotemac[3], remotemac[4], remotemac[5]);
	printf(" O-DU                     O-RU\n");
	printf("  |                        |\n");

	/* define signal handler */
	act.sa_handler = &timeout_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGALRM, &act, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	/* set timer to INTERVAL seconds */
	if ((interval < INTERVAL_MIN) || (interval > INTERVAL_MAX)) {
		interval = INTERVAL_DEFAULT;
	}
	tval.it_interval.tv_usec = 0;
	tval.it_interval.tv_sec = interval;
	tval.it_value.tv_usec = 0;
	tval.it_value.tv_sec = interval;
	if (setitimer(ITIMER_REAL, &tval, NULL) < 0) {
		perror("setitimer");
		exit(EXIT_FAILURE);
	}

	/* avoid starting with a request timeout message */
	got_reply = 1;

	while (1) {
		int n;

		if (next_lbm) {
			if (count < 0) {
				exit(EXIT_SUCCESS);
			}
			if (!got_reply) {
				printf("  |     Timeout %2dsec      |\n", interval);
				printf("  |                        |\n");
			}
			got_reply = 0;

			/* update packet transaction ID */
			*(uint32_t *)(outbuf + transIDpos) = htonl(nextLBMtransID);

			/* send the next LBM */
			if (send_packet(ifname, outbuf, pktsize) < 0) {
				perror("send_packet");
				exit(EXIT_FAILURE);
			}
			/* time_sent is time LBM was sent, set it to NOW */
			(void) gettimeofday(&time_sent, NULL);
			printf("  |---- LBM [%08X] --->|  %02x:%02x:%02x:%02x:%02x:%02x\n",
				nextLBMtransID,
				remotemac[0], remotemac[1], remotemac[2],
				remotemac[3], remotemac[4], remotemac[5]);
			next_lbm = 0;
		}

		n = pcap_next_ex(handle, &header, &pkt_data);
		switch (n) {
		case PCAP_ERROR:
			pcap_perror(handle, "pcap_next_ex");
			break;
		case 0: /* pcap_open_live timeout */
			break;
		case 1: /* Valid packet read */
			if (cfm_matchlbr((uint8_t *) pkt_data, localmac,
					remotemac, vlan, md_level,
					nextLBMtransID)) {
				(void) gettimeofday(&now, NULL);
				printf("  |  %4dbytes %8.3fms  |\n",
					header->caplen,
					(now.tv_sec - time_sent.tv_sec) * 1000 +
					(now.tv_usec - time_sent.tv_usec) /
					1000.0);
				printf("  |<--- LBR [%08X] ----|  %02x:%02x:%02x:%02x:%02x:%02x\n",
					nextLBMtransID,
					remotemac[0], remotemac[1], remotemac[2],
					remotemac[3], remotemac[4], remotemac[5]);
				got_reply = 1;
				printf("  |                        |\n");
			}
			break;
		case PCAP_ERROR_BREAK: /* loop terminated by pcap_breakloop */
		default:
			break;
		}
		(void) gettimeofday(&now, NULL);
	}

	exit(EXIT_SUCCESS);
}

static void
usage() {
	fprintf(stderr, "usage: ethping -i <interface> [-v <vlan>] [-l <mdlevel>] "
		"[-c <count>] [-t <timeSec>] <macAddress>\n");
	exit(EXIT_FAILURE);
}
