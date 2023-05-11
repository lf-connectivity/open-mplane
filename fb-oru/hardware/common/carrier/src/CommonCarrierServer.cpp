
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierServer.cpp
 * \brief     Implementation of Common Carrier Server base class
 *
 *
 * \details   Implementation of Common Carrier Server base class
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <sstream>

#include <assert.h>
#include <string.h>

#include "IAppSettings.h"
#include "IAppSettingsFactory.h"

#include "FrequencyUtils.hpp"
#include "IFrequencyConst.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ICarrier.h"
#include "ICarrierModel.h"
#include "CarrierUtils.hpp"
#include "CarrierFreqMgr.h"
#include "CarrierPowerMgr.h"

#include "CommonCarrier.h"
#include "CommonCarrierServer.h"


using namespace Mplane;

//=============================================================================================================
// DEBUG
//=============================================================================================================

#define DEBUG_CARRIER_SERVER

#ifdef OFF_TARGET
#define SHOW_CARRIER_SERVER_ERROR
#else
#ifdef DEBUG_CARRIER_SERVER
#define SHOW_CARRIER_SERVER_ERROR
#endif
#endif

#if 0
class LockDebug  {
public:
	LockDebug(Mutex &mutex, const std::string& name) :
		mMutex(mutex),
		mName(name)
	{
		std::cerr << "[" << ++mLockCount << "] LOCK: " << mName << std::endl ;
		if (mMutex.isLocked())
			std::cerr << "** Attempt to lock already locked : " << mName << std::endl ;
	    mMutex.lock();
		std::cerr << "[" << mLockCount << "] LOCKED: " << mName << std::endl ;
	}

	~LockDebug()
	{
		std::cerr << "[" << mLockCount << "] UNLOCK: " << mName << std::endl ;
	    mMutex.unlock();
		std::cerr << "[" << mLockCount << "] UNLOCKED: " << mName << std::endl ;
	}

private:
    Mutex& mMutex;
	std::string mName ;
	static unsigned mLockCount ;
};

unsigned LockDebug::mLockCount{0} ;
#endif

//=============================================================================================================
// CLASSES
//=============================================================================================================

class TxEventData : public ITxEventData {
public:
	explicit TxEventData(unsigned port) : mPort(port) {}
	virtual ~TxEventData() {}

	/**
	 * Returns the 0-based port index relating to this event
	 */
	virtual unsigned getPort() const override { return mPort; }

private:
	unsigned mPort ;
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::registerObserver(
        ICarrierServerObserver& observer)
{
    CommonCarrierServerObserver carrierServerObserver;
    carrierServerObserver.observer = &observer;
    mCarrierServerObservers.push_back( carrierServerObserver );
    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::unregisterObserver(
        ICarrierServerObserver& observer)
{
	std::vector<CommonCarrierServerObserver>::iterator iter ;
	for (iter=mCarrierServerObservers.begin(); iter != mCarrierServerObservers.end(); ++iter)
	{
		if (iter->observer == &observer)
		{
			mCarrierServerObservers.erase(iter) ;
			return true ;
		}
	}

    return false;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier& CommonCarrierServer::getCarrier(unsigned carrierIndex) const
{
    if( carrierIndex < getMaxCarriers() )
    {
        return *mCommittedCarrierList[ carrierIndex ];
    }
    return *mCommittedCarrierList[ 0 ];
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::getMaxCarriers(void) const
{
    return mMaxCarriers;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::getMaxTxPaths(void) const
{
    return mMaxTxPaths;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::getMaxRxPaths(void) const
{
    return mMaxRxPaths;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::getMaxTxCarriersPerPort(void) const
{
    return mMaxCarriersPerTxPath;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::getMaxRxCarriersPerPort(void) const
{
    return mMaxCarriersPerRxPath;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierSetter& CommonCarrierServer::getCarrierSetter(unsigned carrierIndex)
{
    if( carrierIndex < getMaxCarriers() )
    {
        return *mCarrierSetList[carrierIndex];
    }
    return *mCarrierSetList[0];

}

//-------------------------------------------------------------------------------------------------------------
const unsigned CommonCarrierServer::lastCarrierIndexModified() const
{
    return mLastModifiedIndex;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::setCarrier( ICarrierSetter &carrier )
{
	logDebugNormal("Set Carrier C%d : STATE=%s",
			carrier.getIndex(),
			(CarrierUtils::isEnabled(carrier) ? "ENABLE" : "DISABLE") ) ;

	ICarrierSetter* commit(nullptr) ;
	std::vector<bool> carrierTxChange ;

	{
		// Make all of this code atomic (i.e. wrap in a mutex lock) just to ensure we don't get funny results
		// where 2 threads (e.g. 2 ARD0546 sessions) attempt to schedule 2 carriers on to the hardware at the same time
		Mutex::Lock lock(mCarrierMutex) ;
	//	LockDebug lock(mCarrierMutex, __FUNCTION__) ;


		// Start by clearing out any previous errors
		setCarrierFailureStr("") ;

		// -- Validate changes before applying them (carrier checks)
		if (!validateChange(carrier))
			return false ;

		// Get the carrier ready for setting it's properties
		mLastModifiedIndex = carrier.getIndex();
		commit = (ICarrierSetter*) mCommittedCarrierList[mLastModifiedIndex];

		// check - cannot allow changes on an enabled carrier
		if (CarrierUtils::isEnabled(commit))
		{
			// Ok if we're disabling
			if (CarrierUtils::isEnabled(carrier))
			{
				setCarrierFailureStr("Cannot change enabled carrier") ;
				return false ;
			}
		}

		// -- Validate changes before applying them (carrier model checks)
		if (!mCarrierModel->validateChange(carrier))
		{
			setCarrierFailureStr(mCarrierModel->failReason()) ;
			return false ;
		}

		// For each TX, work out if this carrier is changing active state
		carrierTxChange = calcCarrierTxChange(commit, carrier) ;

		// -- Apply changes
		commit->setCarrier(carrier) ;

		// update any managers
		if (!updateManagers(*commit))
			return false ;
	}

    // -- notify observers of any TXOFF events - ensure this is done outside of the lock
    // NOTE: *MUST* do this BEFORE updating the hardware to give PCL etc a chance to turn off the TX
    updateTxOffEvent(carrier) ;


	{
		Mutex::Lock lock(mCarrierMutex) ;
	//	LockDebug lock(mCarrierMutex, __FUNCTION__) ;

		// -- Pass the modified carrier to the carrier model to apply HW changes
		if (!mCarrierModel->carrierChange(*commit))
		{
			setCarrierFailureStr(mCarrierModel->failReason()) ;
			return false ;
		}

		// -- clear changed flags
		commit->applyChanges() ;
	}


    // -- notify observers - ensure this is done outside of the lock
    callCarrierServerObservers();
    updateTxOnPowerEvent(carrier, carrierTxChange) ;

    return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::validateChange(const ICarrierSetter& carrier)
{
	std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;

	if (carrier.getState() == ICarrier::STATE_ENABLE && !carrier.isConfigured())
	{
		// Well this was a pointless waste of processing!
		setCarrierFailureStr("Pointless carrier enable with neither TX or RX configured") ;
		return false ;
	}

	// only check active/enabling carriers
	if (CarrierUtils::isEnabled(carrier))
	{
		std::stringstream ss ;

		// Ensure basic settings
		if (carrier.getType() == ICarrier::CARRTYPE_NONE)
		{
			setCarrierFailureStr("Carrier enable without valid type") ;
			return false ;
		}

		// TX checks
		if (carrier.isTx())
		{
			// general checks
			if (carrier.isCPRI() && (carrier.getGroupSizeDown() == 0))
			{
				setCarrierFailureStr("Carrier enable without valid GroupSizeDown") ;
				return false ;
			}

			// ensure frequency set up on carrier
			if (carrier.getTxFrequency() == 0 && carrier.getTxFrequencyOffset() == 0)
			{
				setCarrierFailureStr("Carrier TX frequency not set up") ;
				return false ;
			}

			// Ensure frequencies have been set up on used ports
			std::vector< std::shared_ptr<ITxPort> > txPorts( ITxPortFactory::getPorts( ) ) ;
			// check the antennas
			for (unsigned antenna = 0; antenna < carrier.getNumberTxPaths(); ++antenna)
			{
				if (!carrier.isTx(antenna))
					continue ;

				// Check min & max against the TX port bandwidth
				if (antenna >= txPorts.size())
				{
					ss << "Antenna " << antenna << " outside range of TX ports (" << txPorts.size() << ")" ;
					setCarrierFailureStr(ss.str()) ;
					return false ;
				}

				Frequency txFreq = txPorts.at(antenna)->getFrequency() ;
				if (txFreq == 0)
				{
					ss << "TX Port " << antenna << " frequency not set up" ;
					setCarrierFailureStr(ss.str()) ;
					return false ;
				}
			}
		}

		// RX checks
		if (carrier.isRx())
		{
			// general checks
			if (carrier.isCPRI() && (carrier.getGroupSizeUp() == 0))
			{
				setCarrierFailureStr("Carrier enable without valid GroupSizeUp") ;
				return false ;
			}

			// ensure frequency set up on carrier
			if (carrier.getRxFrequency() == 0 && carrier.getRxFrequencyOffset() == 0)
			{
				setCarrierFailureStr("Carrier RX frequency not set up") ;
				return false ;
			}

			// Ensure frequencies have been set up on used ports
			std::vector< std::shared_ptr<IRxPort> > rxPorts( IRxPortFactory::getPorts( ) ) ;
			// check the antennas
			for (unsigned antenna = 0; antenna < carrier.getNumberRxPaths(); ++antenna)
			{
				if (!carrier.isRx(antenna))
					continue ;

				// Check min & max against the RX port bandwidth
				if (antenna >= rxPorts.size())
				{
					ss << "Antenna " << antenna << " outside range of RX ports (" << rxPorts.size() << ")" ;
					setCarrierFailureStr(ss.str()) ;
					return false ;
				}

				Frequency rxFreq = rxPorts.at(antenna)->getFrequency() ;
				if (rxFreq == 0)
				{
					ss << "RX Port " << antenna << " frequency not set up" ;
					setCarrierFailureStr(ss.str()) ;
					return false ;
				}
			}
		}

		// issue#4740 - if both TX and RX ensure the same containers are set. Currently the hardware can only support the
		// same settings
		if (carrier.isCPRI() && carrier.isTx() && carrier.isRx())
		{
			// Simple check that the group sizes match
			if (carrier.getGroupSizeDown() != carrier.getGroupSizeUp())
			{
				ss << "TX and RX group sizes do not match (TX is " <<
					carrier.getGroupSizeDown() <<
					", RX is " << carrier.getGroupSizeUp() <<
					")" ;
				setCarrierFailureStr(ss.str()) ;
				return false ;
			}

			// We only need to check the cases where TX and RX can be active at the same time. So we only need to look
			// at the minimum set of antenna indices
			unsigned numAntennas(std::min(mMaxTxPaths, mMaxRxPaths)) ;
			for (unsigned ant=0; ant < numAntennas; ++ant)
			{
				if (!carrier.isTx() || !carrier.isRx())
					continue ;

				unsigned txAxc(carrier.getTxContainer(ant)) ;
				unsigned rxAxc(carrier.getRxContainer(ant)) ;
				if (txAxc == 0)
					continue ;
				if (rxAxc == 0)
					continue ;

				if (txAxc != rxAxc)
				{
					ss << "Antenna " << ant << " has different TX and RX container setting (TX is " <<
						txAxc <<
						", RX is " << rxAxc <<
						")" ;
					setCarrierFailureStr(ss.str()) ;
					return false ;
				}
			}
		}
	}

    // carrier frequency checks
    std::string failureReason ;
    if (!mCarrierFreqMgr->validateCarrier(carrier, failureReason))
    {
    	setCarrierFailureStr(failureReason) ;
    	return false ;
    }

    // carrier power checks
    if (!mCarrierPowerMgr->validateCarrier(carrier, failureReason))
    {
    	setCarrierFailureStr(failureReason) ;
    	return false ;
    }

    if (appSettings->getDuplex() == IAppSettings::DUPLEX_TDD)
	{
    	//Only check for enabling carrier
    	if (CarrierUtils::isEnabled(carrier))
    	{
			//Check if TDD configuration is not changed while some carrier is already enabled
			for( unsigned index = 0; index < mCommittedCarrierList.size(); index++ )
			{
				if (CarrierUtils::isEnabled(mCommittedCarrierList[index]) && index != carrier.getIndex())
				{
					//If TDD parameters are changed, then return error
					if (carrier.getUlDlConfigChanged() ||
						carrier.getSpSuConfigChanged() ||
						carrier.getUlPrefixLenChanged() ||
						carrier.getUlDlConfigChanged())
					{
						setCarrierFailureStr("TDD configuration cannot be changed when a carrier is enabled");
						return false;
					}
				}
			}

			//Check if Tx and Rx frequencies are same
			if (carrier.getTxFrequency().getInt(Frequency::Hz) != carrier.getRxFrequency().getInt(Frequency::Hz))
			{
				std::stringstream ss ;

				ss << "Tx and Rx cannot have different frequency when duplex type is TDD: " << carrier.getTxFrequency().getInt(Frequency::Hz) << "," << carrier.getRxFrequency().getInt(Frequency::Hz) << "," << carrier.getIndex() << std::endl;
				setCarrierFailureStr(ss.str()) ;
				return false;
			}
    	}
	}

	return true ;
}



//-------------------------------------------------------------------------------------------------------------
const std::string CommonCarrierServer::getSetCarrierFailureStr()
{
    return mErrorMsg;
}


//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::show()
{
	// Override
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::show(std::ostream& os)
{
	os << "Carrier Models" << std::endl ;
	mCarrierModel->show(os) ;

	os << "== Carriers ==" << std::endl ;
    for( unsigned index = 0; index < mMaxCarriers; index++ )
    {
    	const ICarrier& carrier( getCarrier(index) ) ;
    	carrier.showCarrier(os) ;
    }
}

//-------------------------------------------------------------------------------------------------------------
Power CommonCarrierServer::getTxPower(unsigned path) const
{
	return mCarrierPowerMgr->getTotalPower(path) ;
}

//-------------------------------------------------------------------------------------------------------------
Power CommonCarrierServer::getLowestCarrierPower(unsigned path) const
{
	return mCarrierPowerMgr->getSmallestCarrierPower(path) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::setCalibrationMode(bool calibrationMode)
{
	// skip on no change
	if (mCalibrationMode == calibrationMode)
		return ;

	// Pass setting down to CarrierFreqMgr
	mCalibrationMode = calibrationMode ;
	mCarrierFreqMgr->disablePolicies(mCalibrationMode) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::isCalibrationMode() const
{
	return mCalibrationMode ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::shutdownPath(unsigned path)
{
	logDebugNormal("Shutdown Path TX%u", path) ;

	// For all carriers, it it's enabled on this TX path then shut down that path
	for (auto carrierp : mCommittedCarrierList)
	{
		if (!CarrierUtils::isTxActive(carrierp, path))
			continue ;

		// See if we are TXing on any other path, if not then we can just disable this carrier and stop; if we are,
		// then we need to re-enable after de-activating this TX path
		bool reEnable(false) ;
		for (unsigned tx=0; !reEnable && tx < mMaxTxPaths; ++tx)
		{
			// skip this path
			if (tx == path)
				continue ;

			if (CarrierUtils::isTxActive(carrierp, tx))
			reEnable = true ;
		}

		// Use this carrier's values - shutdown it's TX
        ICarrierSetter& commit = getCarrierSetter( carrierp->getIndex() );

	    // need to disable the carrier before we can change anything
	    commit.setShutdownTx(path) ;
	    commit.setState(ICarrier::STATE_DISABLE) ;

	    // use normal method to modify the carrier, this ensures all the normal checks/updates/events are
	    // performed
	    if (!setCarrier(commit))
	    {
	    	std::cerr << "ERROR: Unable to disable carrier " << carrierp->getIndex() << " on TX" << path << " : " << getSetCarrierFailureStr() << std::endl ;
	    }

	    // Do we now need to re-enable?
	    if (reEnable)
	    {
		    commit.setShutdownTx(path) ;
		    commit.setState(ICarrier::STATE_ENABLE) ;
		    if (!setCarrier(commit))
		    {
		    	std::cerr << "ERROR: Unable to re-enable carrier " << carrierp->getIndex() << " on TX" << path << " : " << getSetCarrierFailureStr() << std::endl ;
		    }
	    }
	}
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::isTxActivePath(unsigned path)
{
	// For all commited carriers, if carrier is enabled on this TX path then return TRUE
	for (auto carrierp : mCommittedCarrierList)
	{
		if (true == CarrierUtils::isTxActive(carrierp, path))
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::unconfigCarrier(unsigned carrierIndex)
{
    if( carrierIndex >= getMaxCarriers() )
    	return false ;

    // Clear out settings - need to use normal setCarrier() method to ensure
    // all managers/observers etc are notified as usual
    ICarrierSetter& commit = getCarrierSetter( carrierIndex );
    for( unsigned index = 0 ; index < mMaxRxPaths; index++ )
    {
        commit.setRxContainer(index,  0 );
        commit.setRxFibre(index, 0 );
    }

    for( unsigned index = 0 ; index < mMaxTxPaths; index++ )
    {
    	commit.setTxContainer(index, 0 );
    	commit.setTxFibre( index, 0 );
    }

    commit.setTxPower( 0.0 );
    commit.setRxFrequency( 0.0 );
    commit.setTxFrequency( 0.0 );
    commit.setRxFrequencyOffset( 0.0 );
    commit.setTxFrequencyOffset( 0.0 );
    commit.setSigType( ICarrier::SIGTYPE_NONE );
    commit.setType( ICarrier::CARRTYPE_NONE );
    commit.setUplinkNoise( 0.0 );
    commit.setGroupSizeUp( 0 );
    commit.setGroupSizeDown( 0 );
    commit.setTxScaling( 0.0 );
    commit.setLoopback( false );

    commit.setState( ICarrier::STATE_DISABLE );

    // set the carrier with it's new settings
    if (!setCarrier(commit))
    {
    	std::cerr << "ERROR: Unable to un-configure carrier " << carrierIndex << " : " << getSetCarrierFailureStr() << std::endl ;
    	return false ;
    }


    // Clear any flags
    ICarrierSetter* carrier = (ICarrierSetter*) mCommittedCarrierList[mLastModifiedIndex];
    if (!carrier->unconfigure())
    {
    	std::cerr << "ERROR: Unable to un-configure carrier " << carrierIndex << std::endl ;
    	return false ;
    }

    return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierServer::CommonCarrierServer(unsigned maxCarriers,
        unsigned maxCarriersPerTxPath, unsigned maxCarriersPerRxPath, unsigned maxTxPaths,
        unsigned maxRxPaths):

	Loggable("CarrierServer", "Carrier"),

	mCalibrationMode(false),
	mLowestRxFrequency(0ULL),
	mLowestTxFrequency(0ULL),
	mWideBand( false ),
	mLastModifiedIndex(0),
	mMaxCarriers( maxCarriers ),
	mMaxCarriersPerTxPath( maxCarriersPerTxPath ),
	mMaxCarriersPerRxPath( maxCarriersPerRxPath ),
	mMaxTxPaths( maxTxPaths ),
	mMaxRxPaths( maxRxPaths ),
	mErrorMsg(""),
	mCarrierModel( ICarrierModel::createInstance(maxCarriers) ),
	mCarrierFreqMgr( CarrierFreqMgr::getInstance(maxCarriers) ),
	mCarrierPowerMgr( CarrierPowerMgr::getInstance(maxCarriers) ),
	mCarrierMutex(),
	mTxOn(maxTxPaths, false),
	mTxPower(maxTxPaths, Power(0.0))
{
    // Initialise the default dynamic ranges, these may be overridden by any specific implementations

    mCarrierSetList.resize( mMaxCarriers );
    mCommittedCarrierList.resize( mMaxCarriers );

    // Initialise the model
    mCarrierModel->initialise() ;

}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierServer::~CommonCarrierServer()
{
    for( unsigned index = 0; index < mMaxCarriers; index++ )
    {
        delete mCarrierSetList[ index ];
        delete mCommittedCarrierList[ index ];
    }
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::setCarrierFailureStr(const std::string& errorMsg)
{
	mErrorMsg = errorMsg ;
#ifdef SHOW_CARRIER_SERVER_ERROR
	// Make a bang for test purposes!
	if (!mErrorMsg.empty())
		std::cerr << "Carrier Server FAIL - reason: " << mErrorMsg << std::endl ;
#endif
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::callCarrierServerObservers()
{
	// Notify all observers of a carrier change
    for (unsigned index = 0; index <  mCarrierServerObservers.size(); index++)
    {
        CommonCarrierServerObserver *observer = &mCarrierServerObservers[index];
        observer->observer->notify( *this );
    }
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::addCarrierSetter(ICarrierSetter& carrierSetter)
{
    if( carrierSetter.getIndex() < mMaxCarriers )
    {
        mCarrierSetList[ carrierSetter.getIndex() ] = &carrierSetter;

        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::addCarrier(ICarrier& carrier)
{
    if( carrier.getIndex() < mMaxCarriers )
    {
        mCommittedCarrierList[ carrier.getIndex() ] = &carrier;

        // Add this carrier to the hardware model's list
        if (!mCarrierModel->addCarrier(carrier) )
        	return false ;

        return true;
    }
    return  false;

}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::updateTxOffEvent(const ICarrier& carrier)
{
	// TX OFF Events
	for (unsigned path=0; path < mMaxTxPaths; ++path)
	{
		// see if any carriers are active on this TX antenna
		bool txOn{false} ;
		for (auto carrierp : mCommittedCarrierList)
		{
			if (!CarrierUtils::isTxActive(carrierp, path))
				continue ;

			txOn = true ;
		}

		// See if the latest state is a change
		if (txOn != mTxOn[path])
		{
			TxEventData txOnOffData(path) ;

			// Notify clients -  TXOFF events only
			if (!txOn)
			{
				static_cast<Subject<ITxOff, const ITxEventData&>*>(this)->notify(txOnOffData) ;
				logDebugNormal("TXOFF EVENT : TX%d", path) ;
			}
		}
	}
}


//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::updateTxOnPowerEvent(const ICarrier& carrier, const std::vector<bool>& carrierTxChange)
{
	// TX POWER Events
	for (unsigned path=0; path < mMaxTxPaths; ++path)
	{
		TxEventData txPowerData(path) ;

		// Notify clients on power change
		if (mTxPower[path] != mCarrierPowerMgr->getTotalPower(path))
		{
			static_cast<Subject<ITxPower, const ITxEventData&>*>(this)->notify(txPowerData) ;

			logDebugNormal("TXPOWER EVENT : TX%d %.2fdB -> %.2fdB", path,
					mTxPower[path].get(), mCarrierPowerMgr->getTotalPower(path).get()) ;

			mTxPower[path] = mCarrierPowerMgr->getTotalPower(path) ;
		}
	}

	// TXON/TXCHANGE Events
	for (unsigned path=0; path < mMaxTxPaths; ++path)
	{
		// see if any carriers are active on this TX antenna
		bool txOn{false} ;
		for (auto carrierp : mCommittedCarrierList)
		{
			if (!CarrierUtils::isTxActive(carrierp, path))
				continue ;

			txOn = true ;
		}

		// TXON
		// See if the latest state is a change
		bool txonEvent{false} ;
		if (txOn != mTxOn[path])
		{
			mTxOn[path] = txOn ;

			// Notify clients - TXON events only
			if (txOn)
			{
				txonEvent = true ;
				TxEventData txOnOffData(path) ;
				static_cast<Subject<ITxOn, const ITxEventData&>*>(this)->notify(txOnOffData) ;
				logDebugNormal("TXON EVENT : TX%d", path) ;
			}
		}

		// TXCHANGE
		// only report change if tx is on AND not reporting a TXON
		if (txOn && !txonEvent && carrierTxChange[path])
		{
			// Notify clients
			TxEventData txOnOffData(path) ;
			static_cast<Subject<ITxChange, const ITxEventData&>*>(this)->notify(txOnOffData) ;
			logDebugNormal("TXCHANGE EVENT : TX%d", path) ;
		}

	}

}


//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierServer::updateManagers(const ICarrier& carrier)
{
    std::string failureReason ;

    // -- Update the LO frequencies
    if (!mCarrierFreqMgr->carrierChange(carrier, failureReason))
    {
    	setCarrierFailureStr(failureReason) ;
    	return false ;
    }

    // -- Update the powers
    if (!mCarrierPowerMgr->carrierChange(carrier, failureReason))
    {
    	setCarrierFailureStr(failureReason) ;
    	return false ;
    }

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierSetter* CommonCarrierServer::createCarrierSetter(unsigned index, unsigned maxTxPaths, unsigned maxRxPaths)
{
	return new CommonCarrier(index, maxTxPaths, maxRxPaths, true) ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrier* CommonCarrierServer::createCarrier(unsigned index, unsigned maxTxPaths, unsigned maxRxPaths)
{
	return new CommonCarrier(index, maxTxPaths, maxRxPaths, false) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::clearCarrierSetters()
{
    for( unsigned index = 0; index < mCarrierSetList.size(); index++ )
    {
        delete mCarrierSetList[ index ];
    }
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierServer::clearCarriers()
{
    for( unsigned index = 0; index < mCommittedCarrierList.size(); index++ )
    {
        delete mCommittedCarrierList[ index ];
    }
}

//-------------------------------------------------------------------------------------------------------------
std::vector<bool> CommonCarrierServer::calcCarrierTxChange(const ICarrier* currentCarrier, const ICarrier& newCarrier)
{
	std::vector<bool> carrierTxChange ;
	for (unsigned path=0; path < mMaxTxPaths; ++path)
	{
		bool change{false} ;
		if (CarrierUtils::isTxActive(currentCarrier, path) != CarrierUtils::isTxActive(newCarrier, path))
			change = true ;

		carrierTxChange.push_back(change) ;
	}

	return carrierTxChange ;
}
