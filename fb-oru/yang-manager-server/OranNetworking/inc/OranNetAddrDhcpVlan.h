/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetAddrDhcpVlan.h
 * \brief     ORAN DHCP ip address allocator with search for VLAN id
 *
 *
 */


#ifndef ORANNETWORKING_INC_ORANNETADDRDHCPVLAN_H_
#define ORANNETWORKING_INC_ORANNETADDRDHCPVLAN_H_

#include <functional>
#include "OranNetAddrDhcp.h"

namespace Mplane
{
class NetDevice ;

/*!
 * \class  		OranNetAddrDhcpVlan
 * \brief  		ORAN DHCP ip address allocator
 * \details		Runs DHCP on each of the VLAN interfaces in the list until gets an IP address. If doesn't get an ip address
 * 				over a vlan, then tries over the raw interface. Repeats the cycle of no address allocated.
 *
 */
class OranNetAddrDhcpVlan : public OranNetAddrDhcp
{
public:
	OranNetAddrDhcpVlan(const std::string& interface, const std::string& vlanMac = "", const std::string& script = "");

	virtual ~OranNetAddrDhcpVlan() ;

	/**
	 * Set the lower and upper limits of the vlan search
	 */
	void setSearchLimits(unsigned startVlan, unsigned endVlan) ;

	/**
	 * Add a VLAN id to the list
	 */
	void setVlan(unsigned vlanId) ;

	/**
	 * Add a set of VLAN ids to the list
	 */
	void setVlan(const std::vector<unsigned>& vlanIds) ;


	/**
	 * Callback function for when a vlan is found
	 */
	using VlanCallbackFunc = std::function<void(unsigned vlan)> ;

	/**
	 * Register a callback function called when a valid vlan is found
	 */
	void registerVlanCallback(VlanCallbackFunc func) ;

	/*
	 * Override normal interface name to replace it with the vlan interface
	 */
	virtual std::string interface() const override ;


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


private:
	// run the dhcp routine and check for timeout
	bool doDhcp() ;

	// move to next state
	void nextState() ;

	void startState() ;
	void startNoSearch() ;
	void startInterface() ;
	void startVlanList() ;
	void startVlanLimits() ;

private:
	enum DhcpVlanState {
		DHCP_NO_SEARCH,
		DHCP_SEARCH_INTERFACE,
		DHCP_SEARCH_VLAN_LIST,
		DHCP_SEARCH_VLAN_LIMITS,
	};

private:
	std::string mVlanMac ;
	unsigned mStartVlan ;
	unsigned mEndVlan ;
	std::vector<unsigned> mVlanList ;
	VlanCallbackFunc mVlanCallback ;
	int mCurrentVlanIndex ;
	unsigned mCurrentVlan ;
	DhcpVlanState mDhcpState ;
	std::shared_ptr<NetDevice> mVlanInterface ;

} ;

}

#endif /* ORANNETWORKING_INC_ORANNETADDRDHCPVLAN_H_ */
