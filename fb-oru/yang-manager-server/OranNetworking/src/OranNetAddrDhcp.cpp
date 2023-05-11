/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetAddrDhcp.cpp
 * \brief
 *
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"
#include <sstream>
#include <iomanip>

#include "OranNetAddrDhcp.h"
#include "INetworkingService.h"
#include "stringfunc.hpp"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string ENV_HOSTNAME{"hostname"} ;
//const std::string ENV_PRODUCTCODE{"productCode"};
const std::string ENV_SERIALNUM{"hwBoardSerialNum"};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranNetAddrDhcp::OranNetAddrDhcp(const std::string& interface, const std::string& name, const std::string& script) :
	NetAddr(name, INetChange::NET_DHCP, interface),
	mHostname(""),
	mScript(script),
	mDhcp(std::make_shared<SystemTask>()),
	mCurrentIp(),
	mProductCode(PRODUCT_CODE),
	mSerialNumber("")
{
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
	mHostname = bootEnv->getVar(ENV_HOSTNAME) ;
//	mProductCode = bootEnv->getVar(ENV_PRODUCTCODE) ;
	mSerialNumber = bootEnv->getVar(ENV_SERIALNUM) ;

	// Get the MAC address of the interface
	auto ns(INetworkingService::singleton(interface)) ;
	auto policy(ns->getNetAddrPolicy()) ;
	mMacAddress = policy->macAddress();

	mDhcp->start() ;
}

//-------------------------------------------------------------------------------------------------------------
OranNetAddrDhcp::~OranNetAddrDhcp()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcp::doStart()
{
	// save the current ip address (if any)
	mCurrentIp = interfaceUp() ;

	logDebugVerbose("[%s:%s] Start IP=%s", name().c_str(), interface().c_str(), mCurrentIp.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcp::doAllocate()
{
	// Attempt DHCP
	if (runDhcp())
	{
		// All done
		setIpAddress(interfaceUp()) ;
		setStatus(INetAddr::NET_IP_ALLOCATED) ;
		return ;
	}

	// check to see if we've timed out yet
	if (timedOut())
		return ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

// ORAN Vendor-identifying Vendor Class Option = Option 124 (0x7c)
// From RFC 3925 - Vendor-Identifying Vendor Options - October 2004
//
//   The format of the V-I Vendor Class option is as follows:
//
//                       1 1 1 1 1 1
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |  option-code  |  option-len   |
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |      enterprise-number1       |
//  |                               |
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |   data-len1   |               |
//  +-+-+-+-+-+-+-+-+               |
//  /      vendor-class-data1       /

const std::string OranNetAddrDhcp::mOptionNumber124  = "0x7c"; 		// Option 124
const std::string OranNetAddrDhcp::mEnterpriseNmber  = "0000cf9c";	// 53148

// DHCP Vendor class identifier
// From RFC 2132 - DHCP Options and BOOTP Vendor Extensions - March 1997

// The format of the option 60 is as follows -
// Code   Len   Vendor class Identifier
// +-----+-----+-----+-----+---
// |  60 |  n  |  i1 |  i2 | ...
// +-----+-----+-----+-----+---

const std::string OranNetAddrDhcp::mOptionNumber60  = "0x3c"; 		// Option 60

// DHCP client identifier
// From RFC 2132 - DHCP Options and BOOTP Vendor Extensions - March 1997

// The format of the option 61 is as follows -
// Code   Len   Type  Client-Identifier
// +-----+-----+-----+-----+-----+---
// |  61 |  n  |  t1 |  i1 |  i2 | ...
// +-----+-----+-----+-----+-----+---

const std::string OranNetAddrDhcp::mOptionNumber61  = "0x3d"; 		// Option 61
const std::string OranNetAddrDhcp::mDuidType("0002");               // DUID type 2 containing enterprise number and identifier
const unsigned int OranNetAddrDhcp::mEnterpriseNumber(55756);// Enterprise Number assigned by IANA

// DHCP Parameter Request List
// From RFC 2132 - DHCP Options and BOOTP Vendor Extensions - March 1997
//
// The format of the Parameter Request List is as follows -
//
// Code   Len   Option Codes
// +-----+-----+-----+-----+---
// |  55 |  n  |  c1 |  c2 | ...
// +-----+-----+-----+-----+---

const std::string OranNetAddrDhcp::mOptionNumber55  = "0x37";		// Option 55 - Parameter Request List
const std::string OranNetAddrDhcp::mOptionCode		= "8F";		    // Option 143 - V4_ZEROTOUCH_REDIRECT
const std::string OranNetAddrDhcp::mDataLenOption55 = "01";			// 1 Octet

//-------------------------------------------------------------------------------------------------------------
bool OranNetAddrDhcp::runDhcp()
{
	logDebugVerbose("[%s:%s] Run DHCP ... ", name().c_str(), interface().c_str()) ;

	int rc(0) ;

	std::string dhcpCmd("udhcpc -n -i " + interface()) ;
	if (!mHostname.empty())
	{
		dhcpCmd += " -x hostname:" + mHostname ;
	}

	// Add option 124 to the DHCP command
	dhcpCmd += " -x " + OranNetAddrDhcp::mOptionNumber124 + ":" + getOption124();

	// Add option 61 to the DHCP command
	dhcpCmd += " -x " + OranNetAddrDhcp::mOptionNumber61 + ":" + getOption61();

	// Add option 55 to the DHCP command
	dhcpCmd += " -x " + OranNetAddrDhcp::mOptionNumber55 + ":" + getOption55();

	dhcpCmd += " -V o-ran-ru2/Mplane/" + OranNetAddrDhcp::mProductCode + "/" + OranNetAddrDhcp::mSerialNumber;

	if (!mScript.empty())
	{
		dhcpCmd += " -s " + mScript ;
	}
	dhcpCmd += " >/dev/null 2>&1" ;

	logDebugVerbose("[%s:%s] CMD: %s", name().c_str(), interface().c_str(), dhcpCmd.c_str()) ;

#ifndef OFF_TARGET
	if (isTimed())
	{
		bool timedOut(false) ;
		unsigned timeout(timeoutTimeMs() / 1000) ;
		if (timeout == 0) ++timeout ;
		rc = mDhcp->runCmd(dhcpCmd, timeout, timedOut) ;
	}
	else
	{
		rc = mDhcp->runCmd(dhcpCmd) ;
	}
#endif

	// rc will be 0 if the address is allocated
	if (rc == 0)
	{
		logDebugVerbose("[%s:%s] ** ALLOCATED **", name().c_str(), interface().c_str()) ;
		return true ;
	}

	// any other failure - treat as ip not allocated
	logDebugVerbose("[%s:%s] - Not ALLOCATED", name().c_str(), interface().c_str()) ;
	return false ;

}

//-------------------------------------------------------------------------------------------------------------
std::string OranNetAddrDhcp::getOption124()
{
	std::string optionStr;

	// Vendor class data string
	std::string vendorClassData = "o-ran-ru2/Mplane/" + OranNetAddrDhcp::mProductCode + "/" + OranNetAddrDhcp::mSerialNumber;

	// Get the hex string for vendor class data
	std::stringstream vendorClassDataHex;
    for (unsigned int index = 0; index != vendorClassData.size(); ++index)
    {
    	vendorClassDataHex << std::hex << std::setfill('0') << std::setw(2) << (unsigned)vendorClassData[index];
    }

    // Format the option 124 value
	std::stringstream opt124Value;

	opt124Value << OranNetAddrDhcp::mEnterpriseNmber;
	opt124Value << std::hex << vendorClassDataHex.str().size()/2;
	opt124Value << vendorClassDataHex.str();

	// Return the string for option 124
	optionStr = opt124Value.str();

	return optionStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string OranNetAddrDhcp::getOption61()
{
	std::string optionStr;

	// Format the option 61 value
	std::stringstream opt61Value;
	std::stringstream opt61ValueSize;
	std::stringstream iaid;
	std::stringstream duid;

	// DUID identifier unique to the client is the product code/serial number
	std::string duid_id = OranNetAddrDhcp::mProductCode + "/" + OranNetAddrDhcp::mSerialNumber;

	// DUID type is 2, followed by 4 octets of enterprise number
	duid << mDuidType;
	duid << std::hex << std::setfill('0') << std::setw(8) << mEnterpriseNumber;

	// Append the duid identifier to the duid
	for (unsigned int index = 0; index != duid_id.size(); ++index)
	{
		duid << std::hex << std::setfill('0') << std::setw(2) << (unsigned)duid_id[index];
	}

	// Set the IAID
	std::vector<std::string> fields = splitStr(mMacAddress, ':');
	if (fields.size() >= 6)
	{
		// Set the IAID as the last 4 numbers in the MAC address
		iaid << std::hex << std::setfill('0') << std::setw(2) << fields[2];
		iaid << std::hex << std::setfill('0') << std::setw(2) << fields[3];
		iaid << std::hex << std::setfill('0') << std::setw(2) << fields[4];
		iaid << std::hex << std::setfill('0') << std::setw(2) << fields[5];
	}
	else
	{
		// Set the IAID as all zeros
		iaid << "00000000";
	}

	opt61Value << "FF" << iaid.str() << duid.str();

	// Return the string for option 61
	optionStr = opt61Value.str();

	return optionStr;
}

//-------------------------------------------------------------------------------------------------------------
std::string OranNetAddrDhcp::getOption55()
{
	std::string optionStr;

	// Add option 143 to the parameter request list option 55
	optionStr = OranNetAddrDhcp::mOptionCode;

	return optionStr;

}
