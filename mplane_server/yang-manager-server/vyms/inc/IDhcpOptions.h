/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDhcpOptions.h
 * \brief     Virtual interface to get DHCP options
 *
 *
 * \details   The virtual interface to get DHCP options
 *
 */


#ifndef VHI_INC_IDHCPOPTIONS_H_
#define VHI_INC_IDHCPOPTIONS_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdint>
#include <functional>

namespace Mplane {

/*!
 * \class  IDhcpOptions
 * \brief
 * \details
 *
 */
class IDhcpOptions{
public:
 IDhcpOptions() {}
 virtual ~IDhcpOptions() {}

 /*
  * Create singleton
  */
 static std::shared_ptr<IDhcpOptions> singleton();

 /**
  * Callback function for when the DHCP options on the interface changes
  */
 using DhcpOptionsNotifyFunc =
     std::function<void(const std::string& interface)>;

 /**
  * Register a callback for when the DHCP options on the interface change
  */
 virtual void registerDhcpOptionsFunc(DhcpOptionsNotifyFunc func) = 0;

 /*
  * Method to get the allocated IP address
  */
 virtual bool getIpAddress(std::string interface, std::string& ipAddress) = 0;

 /*
  * Method to get the MAC address
  */
 virtual bool getMacAddress(std::string interface, std::string& macAddress) = 0;

 /*
  * Method to get the DHCP server identifier
  */
 virtual bool getServerIdentifier(
     std::string interface, std::string& serverId) = 0;

 /*
  * Method to get the domain name
  */
 virtual bool getDomainName(std::string interface, std::string& domainName) = 0;

 /*
  * Method to get the MTU
  */
 virtual bool getMtu(std::string interface, std::string& mtu) = 0;

 /*
  * Method to get the dns
  */
 virtual bool getDns(std::string interface, std::vector<std::string>& dns) = 0;

 /*
  * Method to get the default gateways
  */
 virtual bool getDefaultGateways(
     std::string interface, std::vector<std::string>& gateways) = 0;

 /*
  * Method to get the netconf clients
  */
 virtual bool getNetConfClients(
     std::string interface, std::map<std::string, std::string>& clients) = 0;

 /*
  * Method to get the vendor specific information
  */
 virtual bool getVendorSpecificInfo(
     std::string interface,
     std::map<unsigned int, std::vector<std::string>>& vendorSpecificInfo) = 0;
} ;

}

#endif /* VHI_INC_IDHCPOPTIONS_H_ */
