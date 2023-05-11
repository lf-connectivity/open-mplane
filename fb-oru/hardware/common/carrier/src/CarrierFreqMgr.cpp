/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreqMgr.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>

#include "ITxPort.h"
#include "IRxPort.h"
#include "IRadio.h"
#include "IFrequencyConst.h"
#include "ICarrierHardware.h"
#include "CarrierUtils.hpp"

#include "CarrierFreqMgr/CarrierFreqBand.h"
#include "CarrierFreqMgr.h"

using namespace Mplane;

//=============================================================================================================
// NULL POLICIES - effectively disables autocentre
//=============================================================================================================

class NullUlFrequencyPolicy : public virtual IUlFrequencyPolicy
{
public:
	NullUlFrequencyPolicy() {}
	virtual ~NullUlFrequencyPolicy() {}

	/**
	 * "function" call which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre,
			const Frequency& bundleMin, const Frequency& bundleMax) override
	{
		// Return the current RX port centre
		return IRxPortFactory::getPorts()[port]->getFrequency() ;
	}

	/**
	 * Check that the carrier bundle is within max limits. If outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkBundle(unsigned port,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// assume always OK
		return true ;
	}

	/**
	 * Check the LO centre covers the carrier bundle. If centre is outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkCentre(unsigned port, const Frequency& centre,
			const Frequency& halfBandwidth,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// assume always OK
		return true ;
	}

	/**
	 * Set the current DL centre frequency for this antenna - does nothing here
	 */
	virtual void setDlCentre(const Frequency& dlCentre) override {}
};

class NullDlFrequencyPolicy : public virtual IDlFrequencyPolicy
{
public:
	NullDlFrequencyPolicy() {}
	virtual ~NullDlFrequencyPolicy() {}

	/**
	 * "function" call which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre,
			const Frequency& bundleMin, const Frequency& bundleMax) override
	{
		// Return the current TX port centre
		return ITxPortFactory::getPorts()[port]->getFrequency() ;
	}

	/**
	 * Check that the carrier bundle is within max limits. If outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkBundle(unsigned port,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// assume always OK
		return true ;
	}

	/**
	 * Check the LO centre covers the carrier bundle. If centre is outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkCentre(unsigned port, const Frequency& centre,
			const Frequency& halfBandwidth,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// assume always OK
		return true ;
	}

};


//=============================================================================================================
// SINGLETON
//=============================================================================================================

class CarrierFreqMgrInstance : public CarrierFreqMgr {
public:
	explicit CarrierFreqMgrInstance(unsigned maxCarriers) : CarrierFreqMgr(maxCarriers)
	{
		// Check that we never get created with 0 carriers
		if (maxCarriers == 0)
			throw std::runtime_error("CarrierFreqMgr created with maxCarriers=0.") ;
	}
	virtual ~CarrierFreqMgrInstance() {}
};

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CarrierFreqMgr> CarrierFreqMgr::getInstance(unsigned maxCarriers)
{
	static std::shared_ptr<CarrierFreqMgr> instance(std::make_shared<CarrierFreqMgrInstance>(maxCarriers)) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierBundleFreq> ICarrierBundleFreq::getInstance()
{
	// Assumes singleton has already been created before this is called
	return CarrierFreqMgr::getInstance(0) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierFreqMgr::~CarrierFreqMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::validateCarrier(const ICarrier& carrier, std::string& failReason)
{
	unsigned carrierIndex(carrier.getIndex()) ;
	unsigned port ;

	// TX
	std::vector<Frequency> txCentre(mTxFreqBands.size(), Frequency(0.0)) ;
	port = 0 ;
    for (auto freqBand : mTxFreqBands)
    {
    	if (CarrierUtils::isTxActive(carrier, port))
    	{
        	CarrierFreq carrierFreq(carrier.getTxFrequency(), carrier.getType()) ;
    		if (!freqBand->canFit(carrierIndex, carrierFreq, mActiveDlFreqPolicy, txCentre[port], failReason))
    			return false ;
    	}
    	++port ;
    }

    // RX
    std::vector<Frequency> rxCentre(mRxFreqBands.size(), Frequency(0.0)) ;
	port = 0 ;
    for (auto freqBand : mRxFreqBands)
    {
        // We may not have the same number of tx and rx ports. Make sure we will not
        // exceed the number of tx ports for indexing to set the downlink centre frequency.
        unsigned txport ;
        if( port < (unsigned)IRadioFactory::getInterface()->getNumberOfTxPorts())
        {
            txport = port;
        }
        else
        {
            txport = IRadioFactory::getInterface()->getNumberOfTxPorts() - 1;
        }

        // adjust policy with current settings
        mActiveUlFreqPolicy->setDlCentre(txCentre[txport]) ;

    	if (CarrierUtils::isRxActive(carrier, port))
    	{
        	CarrierFreq carrierFreq(carrier.getRxFrequency(), carrier.getType()) ;
    		if (!freqBand->canFit(carrierIndex, carrierFreq, mActiveUlFreqPolicy, rxCentre[port], failReason))
    			return false ;
    	}
    	++port ;
    }

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::carrierChange(const ICarrier& carrier, std::string& failReason)
{
	unsigned carrierIndex(carrier.getIndex()) ;

	// TX
    for (unsigned port=0; port < mTxFreqBands.size(); ++port)
    {
    	std::shared_ptr<CarrierFreqBand> freqBand(mTxFreqBands[port]) ;

//std::cerr << "CarrierFreqMgr [START] TX" << port << " = " << mTxFreqs[port] << std::endl ;

    	// Going active
    	if (isTxActivating(carrier, port))
    	{
    		// Add carrier to band
        	CarrierFreq carrierFreq(carrier.getTxFrequency(), carrier.getType()) ;
    		mTxCarrierActive[port][carrierIndex] = true ;
    		if (!freqBand->add(carrierIndex, carrierFreq, mActiveDlFreqPolicy, failReason))
    			return false ;

    		// Handle LO frequency change
    		if (!checkTxFreq(port, freqBand, failReason))
    			return false ;

    		continue ;
    	}

    	// Going inactive
    	if (isTxDeactivating(carrier, port))
    	{
    		// Delete carrier from band
    		mTxCarrierActive[port][carrierIndex] = false ;
    		if (!freqBand->del(carrierIndex, mActiveDlFreqPolicy, failReason))
    			return false ;

    		// Handle LO frequency change
    		if (!checkTxFreq(port, freqBand, failReason))
    			return false ;

    		continue ;
    	}
    }

    // RX
    for (unsigned port=0; port < mRxFreqBands.size(); ++port)
    {
    	std::shared_ptr<CarrierFreqBand> freqBand(mRxFreqBands[port]) ;

//std::cerr << "CarrierFreqMgr [START] RX" << port << " = " << mRxFreqs[port] << std::endl ;

        // We may not have the same number of tx and rx ports. Make sure we will not
        // exceed the number of tx ports for indexing to set the downlink centre frequency.
        unsigned txport ;
        if( port < (unsigned)IRadioFactory::getInterface()->getNumberOfTxPorts())
        {
            txport = port;
        }
        else
        {
            txport = IRadioFactory::getInterface()->getNumberOfTxPorts() - 1;
        }

    	// adjust policy with current settings
    	mActiveUlFreqPolicy->setDlCentre(mTxFreqs[txport]) ;

    	// Going active
    	if (isRxActivating(carrier, port))
    	{
    		// Add carrier to band
        	CarrierFreq carrierFreq(carrier.getRxFrequency(), carrier.getType()) ;
    		mRxCarrierActive[port][carrierIndex] = true ;
    		if (!freqBand->add(carrierIndex, carrierFreq, mActiveUlFreqPolicy, failReason))
    			return false ;

    		// Handle LO frequency change
    		if (!checkRxFreq(port, freqBand, failReason))
    			return false ;

    		continue ;
    	}

    	// Going inactive
    	if (isRxDeactivating(carrier, port))
    	{
    		// Delete carrier from band
    		mRxCarrierActive[port][carrierIndex] = false ;
    		if (!freqBand->del(carrierIndex, mActiveUlFreqPolicy, failReason))
    			return false ;

    		// Handle LO frequency change
    		if (!checkRxFreq(port, freqBand, failReason))
    			return false ;

    		continue ;
    	}
    }

    // Update CarrietHardware
    std::vector<ICarrierHardware*> carrierHardwareList(
    	ICarrierHardwareList::getInstance()->getList()
    );

	for (unsigned port=0; port < mTxFreqChange.size(); ++port)
	{
		if (mTxFreqChange[port])
		{
			for (auto ch : carrierHardwareList)
			{
//				std::cerr << "CarrierFreqMgr TX update : CarrierHardware @ " << ch << " TX" << port << "=" << mTxFreqs[port] << std::endl ;
				ch->txFrequencyChange(port, mTxFreqs[port]) ;
			}
		}
		mTxFreqChange[port] = false ;
	}
	for (unsigned port=0; port < mRxFreqChange.size(); ++port)
	{
		if (mRxFreqChange[port])
		{
			for (auto ch : carrierHardwareList)
			{
//				std::cerr << "CarrierFreqMgr RX update : CarrierHardware @ " << ch << " RX" << port << "=" << mRxFreqs[port] << std::endl ;
				ch->rxFrequencyChange(port, mRxFreqs[port]) ;
			}
		}
		mRxFreqChange[port] = false ;
	}

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::setDlFrequencyPolicy(std::shared_ptr<IDlFrequencyPolicy> dlFreqPolicy)
{
	mDlFreqPolicy = dlFreqPolicy ;
	mActiveDlFreqPolicy = mDlFreqPolicy ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::setUlFrequencyPolicy(std::shared_ptr<IUlFrequencyPolicy> ulFreqPolicy)
{
	mUlFreqPolicy = ulFreqPolicy ;
	mActiveUlFreqPolicy = mUlFreqPolicy ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::disablePolicies(bool disable)
{
	// skip if no change
	if (mDisablePolicies == disable)
		return ;

	mDisablePolicies = disable ;

	// Disable
	if (mDisablePolicies)
	{
		mActiveDlFreqPolicy = std::make_shared<NullDlFrequencyPolicy>() ;
		mActiveUlFreqPolicy = std::make_shared<NullUlFrequencyPolicy>() ;
		return ;
	}

	// Enable
	mActiveDlFreqPolicy = mDlFreqPolicy ;
	mActiveUlFreqPolicy = mUlFreqPolicy ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::attachRx(unsigned port, Observer<IFrequencyChange>& observer)
{
	if (port >= mRxFreqBands.size())
		return ;

	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mRxFreqBands[port])->attach( observer );
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::detachRx(unsigned port, Observer<IFrequencyChange>& observer)
{
	if (port >= mRxFreqBands.size())
		return ;

	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mRxFreqBands[port])->detach( observer );
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::attachTx(unsigned port, Observer<IFrequencyChange>& observer)
{
	if (port >= mTxFreqBands.size())
		return ;

	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mTxFreqBands[port])->attach( observer );
}

//-------------------------------------------------------------------------------------------------------------
void CarrierFreqMgr::detachTx(unsigned port, Observer<IFrequencyChange>& observer)
{
	if (port >= mTxFreqBands.size())
		return ;

	std::dynamic_pointer_cast<Subject<IFrequencyChange>>(mTxFreqBands[port])->detach( observer );
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierFreqMgr::CarrierFreqMgr(unsigned maxCarriers) :
	Loggable("CarrierFreqMgr", "CarrierFreq"),

	mTxPorts(ITxPortFactory::getPorts()),
	mRxPorts(IRxPortFactory::getPorts()),
	mTxCarrierActive(),
	mRxCarrierActive(),
	mTxFreqs(),
	mRxFreqs(),
	mTxFreqChange(),
	mRxFreqChange(),
	mTxFreqBands(),
	mRxFreqBands(),

	// create default policies
	mDlFreqPolicy(std::make_shared<NullDlFrequencyPolicy>()),
	mUlFreqPolicy(std::make_shared<NullUlFrequencyPolicy>()),
	mActiveDlFreqPolicy(mDlFreqPolicy),
	mActiveUlFreqPolicy(mUlFreqPolicy)
{
	std::shared_ptr<ITxFrequencyConst> txFreqConst(ITxFrequencyConstFactory::getInterface()) ;
	std::pair<Frequency, Frequency> txLimits(getFreqLimits(txFreqConst)) ;

    for (auto tx : mTxPorts)
    {
    	std::vector<bool> active(maxCarriers, false) ;
    	mTxCarrierActive.push_back(active) ;

    	mTxFreqChange.push_back(false) ;
    	mTxFreqs.push_back(Frequency(0.0)) ;

    	mTxFreqBands.push_back(std::make_shared<CarrierFreqBand>(
    			"Tx" + std::to_string(tx->getIndex()) + "FreqBand",
    			tx->getIndex(),
    			txFreqConst->getBandwidth(),
    			txLimits.first,
    			txLimits.second,
    			txFreqConst->getCentre())) ;
    }

	std::shared_ptr<IRxFrequencyConst> rxFreqConst(IRxFrequencyConstFactory::getInterface()) ;
	std::pair<Frequency, Frequency> rxLimits(getFreqLimits(rxFreqConst)) ;

	for (auto rx : mRxPorts)
    {
    	std::vector<bool> active(maxCarriers, false) ;
    	mRxCarrierActive.push_back(active) ;

    	mRxFreqChange.push_back(false) ;
    	mRxFreqs.push_back(Frequency(0.0)) ;

    	mRxFreqBands.push_back(std::make_shared<CarrierFreqBand>(
    			"Rx" + std::to_string(rx->getIndex()) + "FreqBand",
    			rx->getIndex(),
    			rxFreqConst->getBandwidth(),
    			rxLimits.first,
    			rxLimits.second,
    			rxFreqConst->getCentre())) ;
    }

}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::isTxActivating(const ICarrier& carrier, unsigned port) const
{
//	unsigned carrierIndex(carrier.getIndex()) ;
//
//	if (mTxCarrierActive.at(port).at(carrierIndex))
//		return false ;
//
//	if (!CarrierUtils::isTxActive(carrier, port))
//		return false ;

	if (!carrier.isTx(port))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::isTxDeactivating(const ICarrier& carrier, unsigned port) const
{
	unsigned carrierIndex(carrier.getIndex()) ;

	if (!mTxCarrierActive.at(port).at(carrierIndex))
		return false ;

//	if (CarrierUtils::isTxActive(carrier, port))
//		return false ;

	if (carrier.isTx(port))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::isRxActivating(const ICarrier& carrier, unsigned port) const
{
//	unsigned carrierIndex(carrier.getIndex()) ;
//
//	if (mRxCarrierActive.at(port).at(carrierIndex))
//		return false ;
//
//	if (!CarrierUtils::isRxActive(carrier, port))
//		return false ;

	if (!carrier.isRx(port))
		return false ;


	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::isRxDeactivating(const ICarrier& carrier, unsigned port) const
{
	unsigned carrierIndex(carrier.getIndex()) ;

	if (!mRxCarrierActive.at(port).at(carrierIndex))
		return false ;

//	if (CarrierUtils::isRxActive(carrier, port))
//		return false ;

	if (carrier.isRx(port))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::checkTxFreq(unsigned port, std::shared_ptr<CarrierFreqBand> freqBand, std::string& failReason)
{
	if (mTxFreqs[port] != freqBand->getCentre())
	{
		Frequency newFreq( freqBand->getCentre() ) ;
		logDebugNormal("Moving LO of TX%d to %lld kHz", port, newFreq.getInt(Frequency::KHz)) ;
		if (mTxPorts[port]->setFrequency(newFreq) != ReturnType::RT_OK)
		{
			failReason = "Unable to set TX" + std::to_string(port) + " frequency " +
					std::to_string(newFreq.get(Frequency::KHz)) + "kHz" ;
			return false ;
		}

		mTxFreqChange[port] = true ;
		mTxFreqs[port] = newFreq ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierFreqMgr::checkRxFreq(unsigned port, std::shared_ptr<CarrierFreqBand> freqBand, std::string& failReason)
{
	if (mRxFreqs[port] != freqBand->getCentre())
	{
		Frequency newFreq( freqBand->getCentre() ) ;
		logDebugNormal("Moving LO of RX%d to %lld kHz", port, newFreq.getInt(Frequency::KHz)) ;
		if (mRxPorts[port]->setFrequency(newFreq) != ReturnType::RT_OK)
		{
			failReason = "Unable to set RX" + std::to_string(port) + " frequency " +
					std::to_string(newFreq.get(Frequency::KHz)) + "kHz" ;
			return false ;
		}

		mRxFreqChange[port] = true ;
		mRxFreqs[port] = newFreq ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::pair<Frequency, Frequency> CarrierFreqMgr::getFreqLimits(std::shared_ptr<IFrequencyConst> freqConst)
{
	// Min frequency is the max of the frequency minimums
	Frequency min(freqConst->getMinimum());
	if (min < freqConst->getFilterMinimum())
		min = freqConst->getFilterMinimum() ;
	if (min < freqConst->get3GMinimum())
		min = freqConst->get3GMinimum() ;

	// Max frequency is the min of the frequency maximums
	Frequency max(freqConst->getMaximum());
	if (max > freqConst->getFilterMaximum())
		max = freqConst->getFilterMaximum() ;
	if (max > freqConst->get3GMaximum())
		max = freqConst->get3GMaximum() ;

	return std::pair<Frequency, Frequency>(min, max) ;
}
