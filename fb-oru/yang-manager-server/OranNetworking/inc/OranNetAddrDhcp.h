/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetAddrDhcp.h
 * \brief     ORAN DHCP ip address allocator
 *
 *
 */


#ifndef ORANNETWORKING_INC_ORANNETADDRDHCP_H_
#define ORANNETWORKING_INC_ORANNETADDRDHCP_H_

#include <string>
#include <memory>

#include "SystemTask.h"
#include "NetAddr.h"

namespace Mplane
{

/*!
 * \class  		OranNetAddrDhcp
 * \brief  		ORAN DHCP ip address allocator
 * \details		Runs DHCP to get an ip address allocated. May be run "in the background" to get a dynamic address after assigning
 * 				an address some other way (static/link local etc)
 *
 */
class OranNetAddrDhcp : public NetAddr
{
public:
	OranNetAddrDhcp(const std::string& interface, const std::string& name = "ORAN-DHCP", const std::string& script = "");

	virtual ~OranNetAddrDhcp() ;

protected:
	// Hooks which must be overridden by the derived classes

	/**
	 * Initialise the allocator
	 */
	virtual void doStart() override ;

	/**
	 * Run a single cycle of address allocation
	 */
	virtual void doAllocate() override ;

protected:
	bool runDhcp() ;

private:
	std::string mHostname;
	std::string mScript ;
	std::shared_ptr<SystemTask> mDhcp ;
	std::string mCurrentIp ;

	// DHCP option 124 - Vendor class data
	std::string mProductCode;
	std::string mSerialNumber;
	static const std::string mOptionNumber124;
	static const std::string mEnterpriseNmber;

	// DHCP option 60 - Vendor class identifier
	static const std::string mOptionNumber60;

	// DHCP option 61 - client identifier
	std::string mMacAddress;
	static const std::string mOptionNumber61;
	static const std::string mDuidType;
	static const unsigned int mEnterpriseNumber;

	// DHCP option 55 - Parameter Request List
	static const std::string mOptionNumber55;
	static const std::string mOptionCode;
	static const std::string mDataLenOption55;

	std::string getOption124();
	std::string getOption61();
	std::string getOption55();
} ;

}

#endif /* ORANNETWORKING_INC_ORANNETADDRDHCP_H_ */
