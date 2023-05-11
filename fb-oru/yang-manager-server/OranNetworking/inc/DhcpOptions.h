/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DhcpOptions.h
 * \brief     DHCP options Interface
 *
 *
 * \details   Interface to get DHCP options
 *
 */


#ifndef VHI_INC_DHCPOPTIONS_H_
#define VHI_INC_DHCPOPTIONS_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
#include <mutex>
#include "Task.h"
#include "IDhcpOptions.h"
#include "INetworkingService.h"

// for debug
#include "CdiNetworkingService.h"

namespace Mplane {

/*!
 * \class  DhcpOptions
 * \brief
 * \details
 *
 */
class DhcpOptions: public virtual IDhcpOptions, public Task{
public:
	DhcpOptions();
	virtual ~DhcpOptions();


	static const std::string DhcpOptionFilePath;	/// The DHCP file is in /tmp for simulator or /var/log for real use
	static const std::string DhcpOptionFileName;	/// The filed file name
	static const std::string DhcpOptionFileExt;
	static const std::string NetconfCallHomePort;
	static const unsigned SuboptionNetconfClientIP;
	static const unsigned SuboptionNetconfClientName;
	static const unsigned SuboptionCaRaIP;
	static const unsigned SuboptionCaRaName;
	static const unsigned SuboptionCaRaPort;
	static const unsigned SuboptionCaRaPath;
	static const unsigned SuboptionCaRaSubName;
	static const unsigned SuboptionCaRaProtocol;
	static const unsigned SuboptionSeGwIP;
	static const unsigned SuboptionSeGwName;

	/// Register a callback for when the DHCP options on the interface change
	virtual void registerDhcpOptionsFunc(DhcpOptionsNotifyFunc func) override;

	/// Method to get the allocated IP address, which is read in with getDhcpOptions()
	virtual bool getIpAddress(std::string interface, std::string& ipAddress) override;

	/// Method to get the MAC address
	virtual bool getMacAddress(std::string interface, std::string& macAddress) override;

	/// Method to get the DHCP server identifier
	bool getServerIdentifier(std::string interface, std::string& serverId) override;

	///  Method to get the domain name
	bool getDomainName(std::string interface, std::string& domainName) override;

	/// Method to get the MTU
	bool getMtu(std::string interface, std::string& mtu) override;

	/// Method to get the dns
	bool getDns(std::string interface, std::vector<std::string>& dns) override;

	///  Method to get the default gateways
	bool getDefaultGateways(std::string interface, std::vector<std::string>& gateways) override;

	/// Method to get the netconf clients
	bool getNetConfClients(std::string interface, std::map<std::string, std::string>& clients) override;

	/// Method to get the vendor specific information
	virtual bool getVendorSpecificInfo(std::string interface, std::map<unsigned int, std::vector<std::string>>& vendorSpecificInfo) override;

protected:

	class InterfaceInfo ;
	std::mutex mMutex ;
	std::map<std::string, std::shared_ptr<InterfaceInfo>> mInterfaceInfo ;
	std::vector<DhcpOptionsNotifyFunc> mCallbackFunc;
	bool mShutdown;                       //!> flag set when shutting down

	void handleInterfaceIp(const std::string& interface, const std::string& ipAddress, const std::string& macAddress) ;

	/*!
	 * \brief read in the file containing the DHCP options (udhcpc-eth1.log)
	 * \details Parse contents of file (in CFG format) into internal variables.
	 * The file location is spec
	 * \param interface eg eth1. This gets tacked on to end of file name
	 */
	void getDhcpOptions(const std::string interface);

	bool parseOption143(std::string optStr, std::map<std::string, std::string>& netconfClientsInfo);

	bool parseOption43(std::string optStr, std::map<unsigned int, std::vector<std::string>>& vendorSpecificInfo);

	bool convertHexStringToIP(std::string hexStr, std::string& ip);

    /**
     * \brief This method deals with NETCONF call home.
     * \details This checks for the file called udhcpc.log, if found and updated\n
     *  call Mplane::DhcpOptions::getDhcpOptions()
     *  Then call all methods in callback list
     * \return the exit status of task process
     */
    virtual int run() override;

} ;

}

#endif /* VHI_INC_DHCPOPTIONS_H_ */
