/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierPowerMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CarrierUtils.hpp"

#include "CarrierPowerMgr.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

class CarrierPowerMgrInstance : public CarrierPowerMgr {
public:
	explicit CarrierPowerMgrInstance(unsigned maxCarriers) : CarrierPowerMgr(maxCarriers) {}
	virtual ~CarrierPowerMgrInstance() {}
};

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CarrierPowerMgr> CarrierPowerMgr::getInstance(unsigned maxCarriers)
{
	static std::shared_ptr<CarrierPowerMgr> instance(std::make_shared<CarrierPowerMgrInstance>(maxCarriers)) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierPowerMgr::~CarrierPowerMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::CarrierPowerMgr::getTotalPower(unsigned port) const
{
	if (port >= mTxCarrierPowers.size())
		return Power(0.0) ;

	return mTxCarrierPowers[port]->getPower() ;
}

Power Mplane::CarrierPowerMgr::getSmallestCarrierPower(unsigned path) const
{
	if (path >= mTxCarrierPowers.size())
	{
		std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
		std::shared_ptr<ITxPort> txPort = txPorts[path];
		Power pathMax = txPort->getMaxFreqDepPower();
		return pathMax ;
	}
	return mTxCarrierPowers[path]->getSmallestPower() ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerMgr::validateCarrier(const ICarrier& carrier, std::string& failReason)
{
	// See if any TX ports are activating
	bool activating{false} ;
	for (unsigned port=0; port < mTxCarrierPowers.size(); ++port)
	{
		if (isTxActivating(carrier, port))
		{
			activating = true ;
			break ;
		}
	}

	// if nothing is activating then we can safely say the carrier is valid
	if (!activating)
		return true ;

	// ** Activating - see if we can fit this carrier
	unsigned port ;

	// TX
	port = 0 ;
	for (auto pathPower : mTxCarrierPowers)
	{
		// Update external filter settings
		pathPower->setExtFilter(mTxPorts[port]->getExtFilterLoss()) ;

		// check
		if (isTxActivating(carrier, port))
			if (!pathPower->canFit(carrier.getIndex(), carrier.getTxPower(), failReason))
				return false ;
		++port ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerMgr::carrierChange(const ICarrier& carrier, std::string& failReason)
{
	unsigned carrierIndex(carrier.getIndex()) ;

	// TX
	for (unsigned port=0; port < mTxCarrierPowers.size(); ++port)
	{
		std::shared_ptr<CarrierPowerPath> pathPower(mTxCarrierPowers[port]) ;

		// Going active
		if (isTxActivating(carrier, port))
		{
			// Add carrier to port
			mTxCarrierActive[port][carrierIndex] = true ;
			if (!pathPower->add(carrierIndex, carrier.getTxPower(), failReason))
				return false ;

			continue ;
		}

		// Going inactive
		if (isTxDeactivating(carrier, port))
		{
			// Delete carrier from port
			mTxCarrierActive[port][carrierIndex] = false ;
			if (!pathPower->del(carrierIndex, failReason))
				return false ;

			continue ;
		}
	}

	return true ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierPowerMgr::CarrierPowerMgr(unsigned maxCarriers) :
	Loggable("CarrierPowerMgr", "CarrierPower"),

	mTxPorts(ITxPortFactory::getPorts()),
	mTxCarrierActive(),
	mTxCarrierPowers()
{
	for (auto tx : mTxPorts)
	{
		std::vector<bool> active(maxCarriers, false) ;
		mTxCarrierActive.push_back(active) ;

		mTxCarrierPowers.push_back(std::make_shared<CarrierPowerPath>(
			"Tx" + std::to_string(tx->getIndex()) + "PowerPath",
			tx->getIndex(),
			tx->getExtFilterLoss(),
			tx->getMaxPaPower()
		)) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerMgr::isTxActivating(const ICarrier& carrier, unsigned port) const
{
	// Actually, we now just need to know if the TX is active - the add() method will
	// take care of adding or updating the carrier power

	if (!carrier.isTx(port))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerMgr::isTxDeactivating(const ICarrier& carrier, unsigned port) const
{
	unsigned carrierIndex(carrier.getIndex()) ;

	if (!mTxCarrierActive.at(port).at(carrierIndex))
		return false ;

	if (carrier.isTx(port))
		return false ;

	return true ;
}
