/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      tunctl.c
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//usage:#define tunctl_trivial_usage
//usage:       "[-f device] ([-t name] | -d name)" IF_FEATURE_TUNCTL_UG(" [-u owner] [-g group] [-b]")
//usage:#define tunctl_full_usage "\n\n"
//usage:       "Create or delete tun interfaces\n"
//usage:     "\n	-f name		tun device (/dev/net/tun)"
//usage:     "\n	-t name		Create iface 'name'"
//usage:     "\n	-d name		Delete iface 'name'"
//usage:	IF_FEATURE_TUNCTL_UG(
//usage:     "\n	-u owner	Set iface owner"
//usage:     "\n	-g group	Set iface group"
//usage:     "\n	-b		Brief output"
//usage:	)
//usage:
//usage:#define tunctl_example_usage
//usage:       "# tunctl\n"
//usage:       "# tunctl -d tun0\n"

#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define IOCTL(fd, b, c) \
{ \
	int err = 0 ; \
	if ( (err = ioctl(fd, b, c)) < 0) \
	{ \
		close(fd); \
		perror("ioctl error") ; \
		return err ; \
	} \
}

int main(int argc, char *argv[])
{
	struct ifreq ifr;
	int fd;
	char opt_name[512] = "tap0";
	char opt_device[512] = "/dev/net/tun";
	unsigned opts = 0;

	enum {
		OPT_f = 1 << 0, // control device name (/dev/net/tun)
		OPT_t = 1 << 1, // create named interface
		OPT_d = 1 << 2, // delete named interface
	};

	int opt ;
	while ( (opt = getopt(argc, argv, "t:d:f:bnpu:g:")) != -1)
	{
		switch (opt)
		{
		case 't':
			strncpy(opt_name, optarg, sizeof(opt_name)) ;
			opts |= OPT_t ;
			break ;

		case 'd':
			strncpy(opt_name, optarg, sizeof(opt_name)) ;
			opts |= OPT_d ;
			break ;

		case 'f':
			strncpy(opt_device, optarg, sizeof(opt_device)) ;
			opts |= OPT_f ;
			break ;

		case 'b':
		case 'n':
		case 'p':
		case 'u':
		case 'g':
			printf("Unsupported option. This version does not support the option specified\n") ;
			break ;

		default:
			printf("Unexpected option '%c'\n", opt) ;
			break ;
		}
	}

	// select device
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
	strncpy(ifr.ifr_name, opt_name, IFNAMSIZ);

	// open device
	fd = open(opt_device, O_RDWR);
	if (fd < 0)
	{
		printf("Error: Unable to open tun device '%s'\n", opt_device) ;
		return 1 ;
	}
	IOCTL(fd, TUNSETIFF, (void *)&ifr);

	// delete?
	if (opts & OPT_d)
	{
		IOCTL(fd, TUNSETPERSIST, (void *)(uintptr_t)0);
		printf("Set '%s' nonpersistent\n", opt_name) ;
		return 0;
	}

	// create
	IOCTL(fd, TUNSETPERSIST, (void *)(uintptr_t)1);

	// show info
	printf("Created TAP '%s'\n", ifr.ifr_name);

	return 0;
}

