/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranNetAddrDhcpVlan.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IBootEnv.h"

#include "NetDevice.h"
#include "OranNetAddrDhcpVlan.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

// can we DHCP over the raw interface?
//#define USE_NON_VLAN

//-------------------------------------------------------------------------------------------------------------
const std::string ENV_VLANMAC{"ethaddr2"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranNetAddrDhcpVlan::OranNetAddrDhcpVlan(const std::string &interface, const std::string& vlanMac, const std::string& script) :
	OranNetAddrDhcp(interface, "ORAN-VLAN-DHCP", script),
	mVlanMac(vlanMac),
//	mStartVlan(0),
//	mEndVlan(0),
	mStartVlan(1),
	mEndVlan(4094),
	mVlanList(),
	mVlanCallback(),
	mCurrentVlanIndex(-1),
	mCurrentVlan(0),
	mDhcpState(DHCP_NO_SEARCH),
	mVlanInterface()
{
	if (mVlanMac.empty())
	{
		std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;
		mVlanMac = bootEnv->getVar(ENV_VLANMAC) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
OranNetAddrDhcpVlan::~OranNetAddrDhcpVlan()
{
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::setSearchLimits(unsigned startVlan, unsigned endVlan)
{
	mStartVlan = startVlan ;
	mEndVlan = endVlan ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::registerVlanCallback(VlanCallbackFunc func)
{
	mVlanCallback = func ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::setVlan(unsigned vlanId)
{
	// can only set vlan if we have a MAC
	if (mVlanMac.empty())
		return ;

	mVlanList.push_back(vlanId) ;
	mCurrentVlanIndex = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::setVlan(const std::vector<unsigned> &vlanIds)
{
	// can only set vlan if we have a MAC
	if (mVlanMac.empty())
		return ;

	mVlanList.insert(mVlanList.end(), vlanIds.begin(), vlanIds.end()) ;
	mCurrentVlanIndex = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
std::string OranNetAddrDhcpVlan::interface() const
{
	std::string itfc(this->OranNetAddrDhcp::interface()) ;
	if (mDhcpState == DHCP_SEARCH_INTERFACE)
		return itfc ;
	if (mDhcpState == DHCP_NO_SEARCH)
		return itfc ;

	itfc += std::string(".") + std::to_string(mCurrentVlan) ;
	return itfc ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::doStart()
{
	startState() ;

	logDebugVerbose("[%s:%s] Start", name().c_str(), interface().c_str()) ;

	this->OranNetAddrDhcp::doStart() ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::doAllocate()
{
	logDebugVerbose("[%s:%s] Allocate : state=%d Index=%d", name().c_str(), interface().c_str(), mDhcpState, mCurrentVlanIndex) ;

	// ** Now do the DHCP on the appropriate interface

	// for normal interface, just run dhcp
	if (mDhcpState == DHCP_SEARCH_INTERFACE)
	{
		if (doDhcp())
			return ;
	}
	// for VLAN search, create the VLAN interface then run dhcp
	else
	{
		// Create vlan interface
		auto nd(std::make_shared<NetDevice>(this->OranNetAddrDhcp::interface())) ;
		mVlanInterface = nd->createVlan(mCurrentVlan, mVlanMac) ;
		mVlanInterface->setUp(true) ;

		// run dhcp on the interface
		if (doDhcp())
		{
			// save the VLAN id
			if (mVlanCallback)
				mVlanCallback(mCurrentVlan) ;
			return ;
		}
	}


	// If we get here then step to next state
	nextState() ;

}

//-------------------------------------------------------------------------------------------------------------
bool OranNetAddrDhcpVlan::doDhcp()
{
	if (runDhcp())
	{
		// All done
		setIpAddress(interfaceUp()) ;
		setStatus(INetAddr::NET_IP_ALLOCATED) ;
		return true ;
	}

	// check to see if we've timed out yet
	timedOut() ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::nextState()
{
	logDebugVerbose("[%s:%s] nextState : state=%d index=%d vlan=%u : %d vlan ids : vlan start %u, vlan end %u",
			name().c_str(), interface().c_str(), mDhcpState, mCurrentVlanIndex, mCurrentVlan,
			(int)mVlanList.size(), mStartVlan, mEndVlan) ;

	// disabled search
	if (mDhcpState == DHCP_NO_SEARCH)
	{
		return ;
	}

	// raw interface search
	if (mDhcpState == DHCP_SEARCH_INTERFACE)
	{
		// step to VLAN search if we have anything in the list
		if (!mVlanList.empty())
		{
			startVlanList() ;
			return ;
		}

		if ( (mStartVlan > 0) && (mEndVlan > 0) )
		{
			// We can do the limits search
			startVlanLimits() ;
			return ;
		}

		return ;
	}

	// search from vlan list
	if (mDhcpState == DHCP_SEARCH_VLAN_LIST)
	{
		// close existing vlan interface

		// next in list and see if we've finished
		if (++mCurrentVlanIndex >= (int)mVlanList.size())
		{
			if ( (mStartVlan > 0) && (mEndVlan > 0) )
			{
				// We can do the limits search
				startVlanLimits() ;
				return ;
			}

			// otherwise go back to start
			startState() ;
			return ;
		}

		// carry on with next in list
		mCurrentVlan = mVlanList[mCurrentVlanIndex] ;
		return ;
	}

	// search vlans within limits
	if (mDhcpState == DHCP_SEARCH_VLAN_LIMITS)
	{
		// close existing vlan interface

		// next in list and see if we've finished
		if (++mCurrentVlan > mEndVlan)
		{
			// back to start
			startState() ;
			return ;
		}

		return ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::startState()
{
#ifdef USE_NON_VLAN
	startInterface() ;
	return ;
#else

	// If we have a vlan list then we can use it
	if (!mVlanList.empty())
	{
		startVlanList() ;
		return ;
	}

	// Otherwise, if we have a set of limits then use them
	if ( (mStartVlan > 0) && (mEndVlan > 0) )
	{
		// We can do the limits search
		startVlanLimits() ;
		return ;
	}

	startNoSearch() ;
#endif

}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::startNoSearch()
{
	mDhcpState = DHCP_NO_SEARCH ;
	mCurrentVlanIndex = 0 ;
	mCurrentVlan = 0 ;
	mVlanInterface.reset() ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::startInterface()
{
	mDhcpState = DHCP_SEARCH_INTERFACE ;
	mCurrentVlanIndex = 0 ;
	mCurrentVlan = 0 ;
	mVlanInterface.reset() ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::startVlanList()
{
	mDhcpState = DHCP_SEARCH_VLAN_LIST ;
	mCurrentVlanIndex = 0 ;
	mCurrentVlan = mVlanList[mCurrentVlanIndex] ;
}

//-------------------------------------------------------------------------------------------------------------
void OranNetAddrDhcpVlan::startVlanLimits()
{
	mDhcpState = DHCP_SEARCH_VLAN_LIMITS ;
	mCurrentVlanIndex = 0 ;
	mCurrentVlan = mStartVlan ;
}
