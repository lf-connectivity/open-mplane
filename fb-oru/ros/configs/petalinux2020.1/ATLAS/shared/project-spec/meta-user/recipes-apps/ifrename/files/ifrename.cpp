/*
*
*/
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <linux/sockios.h>

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

#ifndef IFNAMSIZ
    enum { IFNAMSIZ = 16 };
#endif

//const bool debug(true) ;
const bool debug(false) ;

namespace {

	void help()
	{
		std::cout << "usage: ifrename {ifname macaddress} [ {ifname macaddress} ... ]" << std::endl ;
		exit(1) ;
	}

	/**
	 * Remove all spaces from string
	 * @param str
	 * @return copy of str with *all* spaces removed
	 */
	std::string removeSpaces(const std::string& str)
	{
	    std::string result;
	    std::string::const_iterator iter;

	    for (iter = str.begin(); iter != str.end(); ++iter)
	    {
	        char ch = *iter;

	        if (ch != ' ')
	        {
	            result += ch;
	        }
	    }
	    return result;
	}

	std::vector<std::string> getDeviceList()
	{
		// Parse /proc/net/dev device list. This will be of the form:
		//		Inter-|   Receive                                                |  Transmit
		//		 face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
		//		  tun0:   99213     411    0    0    0     0          0         0    44173     586    0    0    0     0       0          0
		//		  p7p1: 202143730  151204    0    1    0     0          0         1  6675211   68630    0    0    0     0       0          0
		//		vmnet8:       0     641    0    0    0     0          0         0        0      39    0    0    0     0       0          0
		//		    lo:    3144      40    0    0    0     0          0         0     3144      40    0    0    0     0       0          0
		//		virbr0-nic:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
		//		virbr0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
		//		vmnet1:       0       0    0    0    0     0          0         0        0      39    0    0    0     0       0          0

		std::vector<std::string> deviceList ;

		std::string linebuff ;
		std::ifstream infile;
		infile.open("/proc/net/dev");
		if (!infile.is_open())
		{
			std::cerr << "Unable to read /proc/net/dev" << std::endl ;
			exit(1) ;
		}

		while(infile.good())
		{
			// get the line text string
			std::getline(infile, linebuff);

			std::size_t pos(linebuff.find(':')) ;
			if (pos == std::string::npos)
				continue ;

			std::string device(removeSpaces(linebuff.substr(0, pos))) ;

			// skip lo
			if (device == "lo")
				continue ;

			deviceList.push_back(device) ;
		}
		infile.close() ;

		return deviceList ;
	}

	std::string macToStr(const struct ether_addr *lmac)
	{
		if (lmac == nullptr)
			return "INVALID" ;

		const uint8_t* ptr( (const uint8_t*)lmac) ;
		std::stringstream ss ;
		for (unsigned i=0; i < ETH_ALEN; i++, ptr++)
		{
			if (i > 0)
				ss << ":" ;
			ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)*ptr ;
		}
		return ss.str() ;
	}

	void parseMAC(const char* mac, struct ether_addr *lmac)
	{
		struct ether_addr *ptr = ether_aton_r(mac, lmac) ;
//		std::cout << "parseMAC '" << mac << "' = " << macToStr(lmac) << std::endl ;

		if (ptr != nullptr)
			return ;

		std::cerr << "ERROR: Cannot process MAC" << std::endl ;
		exit(1) ;
	}


}

int main(int argc, char *argv[])
{
	if (argc < 3)
		help() ;

	if ( (argc-1) % 2 != 0)
		help() ;

	// get command args
	struct ether_addr dummy ;
	std::vector<std::pair<std::string, struct ether_addr>> renameList ;
	for(unsigned i=1; i < argc; i+=2)
	{
		auto pair(std::make_pair(std::string(argv[i]), dummy)) ;
		parseMAC(argv[i+1], &pair.second) ;
		renameList.push_back( pair ) ;
	}

	// Debug
	if (debug)
	{
		std::cout << "Rename List:" << std::endl ;
		for (auto pair : renameList)
		{
			std::cout << " * " << pair.first << " - " << macToStr(&pair.second) << std::endl ;
		}
	}

	// NOTE: Socket is just any old socket handle. It's used to provide the "file" argument to ioctl
	int skt(socket(PF_INET, SOCK_DGRAM, 0));
	if (skt < 0)
	{
		std::cerr << "ERROR: Cannot open socket" << std::endl ;
		exit(1) ;
	}

	// process rename pairs
	for (auto pair : renameList)
	{
		// get latest device names
		std::vector<std::string> deviceList(getDeviceList()) ;

		// Debug
		if (debug)
		{
			std::cout << "RENAME: " << pair.first << std::endl ;
			for (auto device : deviceList)
			{
				std::cout << " * IF " << device << std::endl ;
			}
		}

		// Search each device to find a matching MAC
		struct ifreq ifr;
		bool found(false) ;
		for (auto device : deviceList)
		{
			/* Find the current interface name and copy it to ifr.ifr_name */
			memset(&ifr, 0, sizeof(struct ifreq));
		    strncpy(ifr.ifr_name, device.c_str(), IFNAMSIZ);
			ioctl(skt, SIOCGIFHWADDR, &ifr);

			if (debug)
			{
				std::cout << " + Checking MAC of " << device << " = " <<
						macToStr( (const struct ether_addr*)ifr.ifr_hwaddr.sa_data ) <<
						std::endl ;
			}

			// see if this device's MAC matches the requested MAC
			if (memcmp(&pair.second, ifr.ifr_hwaddr.sa_data, ETH_ALEN) != 0)
				continue ;

			// found
			found = true ;
			if (debug)
				std::cout << " + RENAMING: " << ifr.ifr_name << " -> " << pair.first << std::endl ;
			strcpy(ifr.ifr_newname, pair.first.c_str());
			if (ioctl(skt, SIOCSIFNAME, &ifr) < 0)
			{
				std::cerr << "ERROR: can't rename " << ifr.ifr_name << " to " << pair.first << std::endl ;
				if (errno == EBUSY)
					std::cerr << "Interface is active, must shut it down before renaming" << std::endl ;
				if (errno == EPERM)
					std::cerr << "You do not have permissions to perform this action. Are you root?" << std::endl ;
				exit(1) ;
			}
			break ;
		}

		if (!found)
		{
			std::cerr << "ERROR: can't find MAC id for " << pair.first << std::endl ;
			exit(1) ;
		}
	}


	return 0;
}


