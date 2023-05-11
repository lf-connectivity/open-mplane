/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierPowerPath.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <vector>
#include "CarrierPowerPath.h"
#include "ITxPort.h"

using namespace Mplane;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierPowerPath::CarrierPowerPath(const std::string& name,
		unsigned portIndex,
		const Power& extFilter, const Power& extFilterMax) :
	Loggable(name, "CarrierPower"),

	mName(name),
	mPort(portIndex),
	mExtFilter(extFilter),
	mExtFilterMax(extFilterMax),

	mCarrierPowers(),
	mTotalPower(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
CarrierPowerPath::~CarrierPowerPath()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerPath::canFit(unsigned index, const Power& carrierPower, std::string& failReason) const
{
	std::map<unsigned, Power> carrierPowers(mCarrierPowers) ;

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s canFit: Power %.2f dB",
			mName.c_str(),
			carrierPower.get()
		) ;
	}

	// We now have the possibility for multiple max powers dependent on frequency due to 6G
	// max power is adjusted in tx port when changing frequency
	// In this case we apply the widest limit as a general sanity check
	// This change 'shouldn't' affect other products!
	std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
	std::shared_ptr<ITxPort> txPort = txPorts[mPort];
	Power pathMax = txPort->getMaxPower();
	Power pathMin = txPort->getMinPower();
	Power totalPower ;
	carrierPowers[index] = carrierPower ;
	return calcPowers(carrierPowers, totalPower, failReason, pathMax, pathMin) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerPath::add(unsigned index, const Power& carrierPower, std::string& failReason)
{
	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s add: Power %.2f dB",
			mName.c_str(),
			carrierPower.get()
		) ;
	}

	// We now have the possibility for multiple max powers dependent on frequency due to 6G
	// max power is adjusted in tx port when changing frequency
	// In this case we apply the frequency specific max power as frequency will have been set
	// This is a last chance saloon check and carrier setup will be rejected, but freq will have been set...
	// Sad, but true.  We have to rely on fact engineers know what they are doing.
	// This change 'shouldn't' affect other products!
	std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
	std::shared_ptr<ITxPort> txPort = txPorts[mPort];
	Power pathMax = txPort->getMaxFreqDepPower();
	Power pathMin = txPort->getMinFreqDepPower();

	Power totalPower ;
	std::map<unsigned, Power> carrierPowers(mCarrierPowers) ;

	carrierPowers[index] = carrierPower ;
	if (!calcPowers(carrierPowers, totalPower, failReason, pathMax, pathMin))
		return false ;

	mTotalPower = totalPower ;
	mCarrierPowers[index] = carrierPower ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerPath::del(unsigned index, std::string& failReason)
{
	failReason = "" ;
	auto entry(mCarrierPowers.find(index)) ;
	if (entry == mCarrierPowers.end())
	{
		failReason = "Carrier not active on port. Index " + std::to_string(index) ;
		return false ;
	}

	if (isDebug(Loggable::LOG_DEBUG_VERBOSE))
	{
		logDebugVerbose("%s del: Power %.2f dB",
			mName.c_str(),
			entry->second.get()
		) ;
	}

	// We now have the possibility for multiple max powers dependent on frequency due to 6G
	// max power is adjusted in tx port when changing frequency
	// In this case we apply the frequency specific max power as frequency will have been set
	// This is a last chance saloon check and carrier setup will be rejected, but freq will have been set...
	// Sad, but true.  We have to rely on fact engineers know what they are doing.
	// This change 'shouldn't' affect other products!
	std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
	std::shared_ptr<ITxPort> txPort = txPorts[mPort];
	Power pathMax = txPort->getMaxFreqDepPower();
	Power pathMin = txPort->getMinFreqDepPower();

	mCarrierPowers.erase(entry) ;
	Power totalPower ;
	if (!calcPowers(mCarrierPowers, totalPower, failReason, pathMax, pathMin))
		return false ;

	mTotalPower = totalPower ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
Power CarrierPowerPath::getPower() const
{
	return mTotalPower ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierPowerPath::setExtFilter(const Power& extFilter)
{
	mExtFilter = extFilter ;
}

Power CarrierPowerPath::getSmallestPower() const
{
	std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
	std::shared_ptr<ITxPort> txPort = txPorts[mPort];
	Power pathMax = txPort->getMaxFreqDepPower();

	Power smallestTxPower = pathMax;

	for (auto entry : mCarrierPowers)
	{
	    Power txPower = entry.second.get() ;
		if ( txPower < smallestTxPower )
		{
			smallestTxPower = txPower;
		}
	}

	return smallestTxPower;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool CarrierPowerPath::calcPowers(const std::map<unsigned, Power>& carrierPowers,
		Power& totalPower,
		std::string& failReason, Power pathMax, Power pathMin) const
{
	// special case of empty list
	if (carrierPowers.empty())
	{
		totalPower = Power(0.0) ;
		return true ;
	}

	// Sum up the TX powers in mW of any enabled carriers
	float txPower{0.0} ;
	for (auto entry : carrierPowers)
	{
		txPower += entry.second.get(Power::mW) ;

		logDebugVerbose("%s calcPowers: Adding C%u Power %.2f dB",
			mName.c_str(),
			entry.first,
			entry.second.get()
		) ;
	}
	totalPower = Power(txPower, Power::mW) ;

	logDebugVerbose("%s calcPowers: Total Power %.2f dB (Ext Filter %.2f dB)",
		mName.c_str(),
		totalPower.get(),
		mExtFilter.get()
	) ;

	// Now check it fits the limits
	std::stringstream ss ;
	if (totalPower.getWatts() < pathMin.getWatts())
	{
		ss << "Total carrier power " << totalPower << " less than limit " << pathMin ;
		failReason = ss.str() ;
		logDebugVerbose("%s calcPowers: FAIL %s", mName.c_str(), failReason.c_str()) ;
		return false ;
	}
	if (totalPower.getWatts() > pathMax.getWatts())
	{
		ss << "Total carrier power " << totalPower << " greater than limit " << pathMax ;
		failReason = ss.str() ;
		logDebugVerbose("%s calcPowers: FAIL %s", mName.c_str(), failReason.c_str()) ;
		return false ;
	}

	// Check that target + filter < max
	Power powerMargin(0.1, Power::dB) ;
	if (totalPower.getWatts() + mExtFilter.getWatts() > mExtFilterMax.getWatts() + powerMargin.getWatts())
	{
		ss << "Total carrier power + external filter greater than limit " << mExtFilterMax ;
		failReason = ss.str() ;
		logDebugVerbose("%s calcPowers: FAIL %s", mName.c_str(), failReason.c_str()) ;
		return false ;
	}

	return true ;
}
