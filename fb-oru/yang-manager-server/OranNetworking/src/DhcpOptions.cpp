/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file 	  DhcpOptions.cpp
 * \brief     DHCP options Interface
 *
 *
 * \details   Interface to get DHCP options
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "DhcpOptions.h"
#include "FileMap.h"

#include "stringfunc.hpp"
#include "IAppOptions.h"
#include "INetworkingService.h"

// for debug
#include "CdiNetworkingService.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

#ifdef OFF_TARGET
const std::string DhcpOptions::DhcpOptionFilePath("/tmp/") ;
#else
const std::string DhcpOptions::DhcpOptionFilePath("/var/log/") ;
#endif

const std::string DhcpOptions::DhcpOptionFileName("udhcpc-") ;
const std::string DhcpOptions::DhcpOptionFileExt(".log") ;

const std::string DhcpOptions::NetconfCallHomePort("4334");
const unsigned DhcpOptions::SuboptionNetconfClientIP(0x81);
const unsigned DhcpOptions::SuboptionNetconfClientName(0x82);
const unsigned DhcpOptions::SuboptionCaRaIP(0x01);
const unsigned DhcpOptions::SuboptionCaRaName(0x02);
const unsigned DhcpOptions::SuboptionCaRaPort(0x03);
const unsigned DhcpOptions::SuboptionCaRaPath(0x04);
const unsigned DhcpOptions::SuboptionCaRaSubName(0x05);
const unsigned DhcpOptions::SuboptionCaRaProtocol(0x06);
const unsigned DhcpOptions::SuboptionSeGwIP(0x07);
const unsigned DhcpOptions::SuboptionSeGwName(0x08);

//=============================================================================================================
// CLASSES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
struct DhcpOptions::InterfaceInfo {

	InterfaceInfo(std::string filename, std::string ipAddress, std::string macAddress) :
		mIpAddress(ipAddress),
		mMacAddress(macAddress),
		mDhcpServerId(),
		mDomainName(),
		mMtu(),
		mDomainNameServers(),
		mDefaultGateways(),
		mNetconfClientsInfo(),
		mLogFileName(filename),
		mLastTimestamp(0),
		mVendorSpecificInfo()
	{}

	std::string mIpAddress;                      //!> IP address allocated to the interface
	std::string mMacAddress;                     //!> MAC address of the interface
	std::string mDhcpServerId;                   //!> DHCP server Identifier
	std::string mDomainName;                     //!> Domain name to be used by the client
	std::string mMtu;                            //!> MTU to be used for this network
	std::vector<std::string> mDomainNameServers; //!> List of DNS servers to be used by the client
	std::vector<std::string> mDefaultGateways;   //!> List of default gateways (the first router or L3 switch seen by the client to get to the Internet)
	std::map<std::string, std::string> mNetconfClientsInfo; //!> Netconf client url and port numbers to be used for call home functionality
	std::string mLogFileName;                    //!> Log file that contains the options for this interface
	unsigned long mLastTimestamp;                //!> Timestamp that the file was last updated
	std::map<unsigned int, std::vector<std::string>> mVendorSpecificInfo; //!> Information provided by the DHCP server in the vendor specific option 43
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDhcpOptions> IDhcpOptions::singleton(void)
{
	static std::shared_ptr<IDhcpOptions> _instance = std::make_shared<DhcpOptions>();
	return _instance;
}

//-------------------------------------------------------------------------------------------------------------
DhcpOptions::DhcpOptions(void) :
	Task(Task::PRIORITY_DEFAULT, Task::MEDIUM_STACK,
		 "DhcpOptions", "DhcpOptionsTask"
	),
	mMutex(),
	mInterfaceInfo(),
	mCallbackFunc(),
	mShutdown(false)
{
#ifdef TEST_BB_ON_CDI
	const std::string itfc("ethcdi") ;
#else
	const std::string itfc("ethbb") ;
#endif
	std::string interfaceName(IAppOptions::getInstance()->getOption(itfc).toString()) ;

	auto ns(INetworkingService::singleton(interfaceName)) ;
	ns->pause() ;
	auto policy(ns->getNetAddrPolicy()) ;

	policy->registerAllocatedFunc([this](const std::string& interface, const std::string& ipAddress, const std::string& macAddress,
			const std::string& allocatorName, INetChange::NetState allocatorType)
	{
		if (allocatorType == INetChange::NET_DHCP)
		{
			// Get the DHCP options
			handleInterfaceIp(interface, ipAddress, macAddress);
		}
	}) ;

	ns->restart() ;

	// self start
	start();

#ifdef OFF_TARGET
	// Set eth1 for call home
	handleInterfaceIp("eth1", "0.0.0.0", "01:02:03:04:05:06");
#endif
}

//-------------------------------------------------------------------------------------------------------------
DhcpOptions::~DhcpOptions()
{
	mShutdown = true;
}

//-------------------------------------------------------------------------------------------------------------
void DhcpOptions::registerDhcpOptionsFunc(DhcpOptionsNotifyFunc func)
{
	mCallbackFunc.push_back(func);
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getIpAddress(std::string interface, std::string& ipAddress)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		ipAddress = interfaceInfo[interface]->mIpAddress;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getMacAddress(std::string interface, std::string& macAddress)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		macAddress = interfaceInfo[interface]->mMacAddress;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getServerIdentifier(std::string interface, std::string& serverId)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		serverId = interfaceInfo[interface]->mDhcpServerId;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getDomainName(std::string interface, std::string& domainName)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		domainName = interfaceInfo[interface]->mDomainName;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getMtu(std::string interface, std::string& mtu)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		mtu = interfaceInfo[interface]->mMtu;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getDns(std::string interface, std::vector<std::string>& dns)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		dns = interfaceInfo[interface]->mDomainNameServers;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getDefaultGateways(std::string interface, std::vector<std::string>& gateways)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		gateways = interfaceInfo[interface]->mDefaultGateways;
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getNetConfClients(std::string interface, std::map<std::string, std::string>& clients)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		clients = interfaceInfo[interface]->mNetconfClientsInfo;

		// If netconf clients are discovered from vendor specific info, then include them as well
		for (auto & info : interfaceInfo[interface]->mVendorSpecificInfo)
		{
			if (info.first == DhcpOptions::SuboptionNetconfClientIP ||
				info.first == DhcpOptions::SuboptionNetconfClientName)
			{
				for (auto & elem : info.second)
				{
					clients[elem] = NetconfCallHomePort;
				}
			}
		}
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::getVendorSpecificInfo(std::string interface, std::map<unsigned int, std::vector<std::string>>& vendorSpecificInfo)
{
	std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		interfaceInfo = mInterfaceInfo;
	}

	if (interfaceInfo.find(interface) != interfaceInfo.end())
	{
		vendorSpecificInfo = interfaceInfo[interface]->mVendorSpecificInfo;
		return true;
	}

	return false;
}
//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DhcpOptions::handleInterfaceIp(const std::string &interface, const std::string &ipAddress, const std::string &macAddress)
{
	// The interface has been allocated an ip address
	std::cerr << "DhcpOptions::handleInterfaceIp interface '" << interface << "' ip " << ipAddress << std::endl ;

	{
		std::unique_lock<std::mutex> lock(mMutex) ;
		if (mInterfaceInfo.find(interface) == mInterfaceInfo.end())
		{
			// use the interface name to set the DHCP properties filename
			std::string dhcpFile = DhcpOptions::DhcpOptionFilePath +
					DhcpOptions::DhcpOptionFileName +
					interface + DhcpOptions::DhcpOptionFileExt ;

			// create entry
			mInterfaceInfo[interface] = std::make_shared<InterfaceInfo>(dhcpFile, ipAddress, macAddress) ;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void DhcpOptions::getDhcpOptions(const std::string interface)
{
	std::unique_lock<std::mutex> lock(mMutex) ;

	if (mInterfaceInfo.find(interface) != mInterfaceInfo.end())
	{
		// use the interface name to set the DHCP properties filename
		std::string dhcpFile(DhcpOptions::DhcpOptionFilePath +
				DhcpOptions::DhcpOptionFileName +
				interface + DhcpOptions::DhcpOptionFileExt) ;
		FileMap fmap ;
		if (!fmap.setPath(dhcpFile))
		{
	#ifndef OFF_TARGET
			std::cerr << "Unable to read file '" << dhcpFile << "'" << std::endl ;
			return ;
	#else
			// We can set some values for debugging
			fmap.setValues(std::map<std::string, std::string>{
				{ "lease", 		"86400" },
				{ "mask", 		"24" },
				{ "ip", 		"10.0.1.115" },
				{ "router", 	"10.0.1.1" },
				{ "domain", 	"quartz.com" },
				{ "dns", 		"10.0.1.1" },
				{ "serverid", 	"10.0.1.1" },
				{ "subnet", 	"255.255.255.0" },
				{ "opt53", 		"05" },
				{ "interface", 	interface },
			}) ;
	#endif
		}

		mInterfaceInfo[interface]->mDhcpServerId = fmap.value("serverid");
		mInterfaceInfo[interface]->mDomainName = fmap.value("domain");
		mInterfaceInfo[interface]->mMtu = fmap.value("mtu");
		mInterfaceInfo[interface]->mDomainNameServers = splitStr(fmap.value("dns"), ',');
		mInterfaceInfo[interface]->mDefaultGateways = splitStr(fmap.value("router"), ',');

		// Populate the netconf client information if available in the file map
		if (fmap.isValue("opt143"))
		{
			std::string opt143 = fmap.value("opt143");
			if (parseOption143(opt143, mInterfaceInfo[interface]->mNetconfClientsInfo) == false)
			{
				eventError("Invalid DHCP option 143 reply : %s", opt143.c_str());
			}
		}

		// Populate the vendor specific information if available in the file map
		if (fmap.isValue("opt43"))
		{
			std::string opt43 = fmap.value("opt43");
			if (parseOption43(opt43, mInterfaceInfo[interface]->mVendorSpecificInfo) == false)
			{
				eventError("Invalid DHCP option 43 reply : %s", opt43.c_str());
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::parseOption143(std::string opt143, std::map<std::string, std::string>& netconfClientsInfo)
{
	bool ret = true;
	size_t opt143len = opt143.size();
	unsigned int pos = 0;

	try
	{
		// Loop through the option string
		while (pos <= opt143len)
		{
			// Check if option string contains number of characters equal to the uri length
			if (opt143.size() >= pos + 4)
			{
				// Get the uri length
				std::string uri_len = opt143.substr(pos, 4);

				// Convert the uri length to decimal
				// Uri length needs to be doubled to account for 2 characters making one octet
				unsigned int len = std::stoul(uri_len, NULL, 16) * 2;

				// Check if the option string contains remaining characters equal to the uri
				if (len > 0 && (opt143.size() >= (len + pos + 4)))
				{
					// Get the uri in hex
					std::string uriHex = opt143.substr(pos + 4, len);

					// Convert the uri to string
					std::string uriStr = convertHexToString(uriHex);

					// Parse the url and port
					size_t portPos = uriStr.find_last_of(':');
					std::string url = uriStr;
					std::string port = "4334";
					if (portPos != std::string::npos)
					{
						url = uriStr.substr(0, portPos);
						port = uriStr.substr(portPos + 1);
					}

					// Add the url and port to the netconf clients list
					netconfClientsInfo[url] = port;
					pos += len + 4;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	catch (std::exception & e)
	{
		ret = false;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::parseOption43(std::string opt43, std::map<unsigned int, std::vector<std::string>>& vendorSpecificInfo)
{
	bool ret = true;
	size_t opt43len = opt43.size();
	unsigned int pos = 0;

	try
	{
		// Loop through the option string
		while (pos <= opt43len)
		{
			// Check if option string contains number of characters equal to the sub option type and length
			if (opt43.size() >= pos + 4)
			{
				// Get the sub option type and length
				std::string type_str = opt43.substr(pos, 2);
				std::string len_str = opt43.substr(pos+2, 2);

				// Convert the sub option to decimal
				// sub option needs to be doubled to account for 2 characters making one octet
				unsigned int type = std::stoul(type_str, NULL, 16);
				unsigned int len = std::stoul(len_str, NULL, 16) * 2;

				// Check if the option string contains remaining characters equal to the option
				if (len > 0 && (opt43.size() >= (len + pos + 4)))
				{
					// Get the sub option value in hex
					std::string valueHex = opt43.substr(pos + 4, len);

					switch (type)
					{
					case DhcpOptions::SuboptionNetconfClientIP:
					case DhcpOptions::SuboptionCaRaIP:
					case DhcpOptions::SuboptionSeGwIP:
					{
						std::string ip = "";

						if (convertHexStringToIP(valueHex, ip) == true)
						{
							vendorSpecificInfo[type].push_back(ip);
						}
					}
					break;

					case DhcpOptions::SuboptionNetconfClientName:
					case DhcpOptions::SuboptionCaRaName:
					case DhcpOptions::SuboptionCaRaPath:
					case DhcpOptions::SuboptionCaRaSubName:
					case DhcpOptions::SuboptionCaRaProtocol:
					case DhcpOptions::SuboptionSeGwName:
					{
						// Convert the value to string
						std::string valueStr = convertHexToString(valueHex);
						vendorSpecificInfo[type].push_back(valueStr);
					}
					break;

					case DhcpOptions::SuboptionCaRaPort:
					{
						unsigned int val = std::stoul(valueHex, nullptr, 16);
						vendorSpecificInfo[type].push_back(std::to_string(val));
					}
					break;

					default:
						break;
					}

					pos += len + 4;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	catch (std::exception & e)
	{
		ret = false;
	}

	return ret;
}

//-------------------------------------------------------------------------------------------------------------
bool DhcpOptions::convertHexStringToIP(std::string hexStr, std::string& ip)
{
	if (hexStr.size() == 8)
	{
		ip = "";

		for (size_t index = 0; index < hexStr.size(); index += 2)
		{
			if (index != 0)
			{
				ip += ".";
			}
			//taking two characters from hex string
			std::string part = hexStr.substr(index, 2);
			//changing it into base 16
			unsigned int val = std::stoul(part, nullptr, 16);

			ip += std::to_string(val);
		}

		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
int DhcpOptions::run(void)
{
	while(!mShutdown)
	{
		std::map<std::string, std::shared_ptr<InterfaceInfo>> interfaceInfo ;
		{
			std::unique_lock<std::mutex> lock(mMutex) ;
			interfaceInfo = mInterfaceInfo;
		}
		for (auto & interface : interfaceInfo)
		{
			struct stat st;
			std::string fileName = interface.second->mLogFileName;
			if (stat (fileName.c_str(), &st) == 0)
			{
				unsigned long timestamp = st.st_mtim.tv_sec;
				if (timestamp != interface.second->mLastTimestamp)
				{
					std::cerr << "Dhcp options file updated for " << interface.first << std::endl ;

					interface.second->mLastTimestamp = timestamp;

					// Update DHCP options
					getDhcpOptions(interface.first);

					// Notify observers
					for (auto & func : mCallbackFunc)
					{
						func(interface.first);
					}

				}
			}
		}

		Task::msSleep(2000);
	}
	return 0;
}
