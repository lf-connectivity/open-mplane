
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModel.cpp
 * \brief     Implementation of Common Carrier Model base class
 *
 *
 * \details   Implementation of Common Carrier Model base class. Mostly this just farms off all the calls
 * 			  to it's worker models.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ICarrier.h"
#include "CommonCarrierFail.h"
#include "CarrierUtils.hpp"
#include "CommonCarrierModel.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierModel::CommonCarrierModel(unsigned maxCarriers) :
	mMaxCarriers(maxCarriers),
	mFailureReason( new CommonCarrierFail() ),
	mWorkers(0)
{
}
//-------------------------------------------------------------------------------------------------------------
CommonCarrierModel::~CommonCarrierModel()
{
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModel::addWorker(std::shared_ptr<ICarrierModelWorker> worker)
{
	mWorkers.push_back(worker) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModel::addListWorker(std::shared_ptr<ICarrierModelWorker> worker)
{
	// ensure this "list worker" is placed at the start
	std::vector< std::shared_ptr<ICarrierModelWorker> >::iterator it(mWorkers.begin()) ;
	mWorkers.insert(it, worker) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModel::addCarrier(const ICarrier& carrier)
{
	bool ok = true ;
	mFailureReason->clearFailReason() ;
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		ok = mWorkers.at(i)->addCarrier(carrier) ;
		if (!ok)
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
	}
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModel::initialise(void)
{
	bool ok = true ;
	mFailureReason->clearFailReason() ;
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		ok = mWorkers[i]->initialise() ;
		if (!ok)
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
	}
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModel::validateChange(const ICarrier& carrier)
{
	bool ok = true ;
	mFailureReason->clearFailReason() ;
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		ok = mWorkers[i]->validateChange(carrier) ;
		if (!ok)
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
	}
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModel::carrierChange(const ICarrier& carrier)
{
	bool ok = true ;
	mFailureReason->clearFailReason() ;

	// change settings
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		// changes settings only, no hardware will change
		ok = mWorkers[i]->carrierChange(carrier) ;
		if (!ok)
		{
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
			return ok ;
		}
	}

    // -- Notify the carrier model that we are about to update the hardware
	// some workers will change the hardware
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		ok = mWorkers[i]->preUpdate() ;
		if (!ok)
		{
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
			return ok ;
		}
	}

	// now update the hardware
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		// changes hardware
		ok = mWorkers[i]->updateHardware() ;
		if (!ok)
		{
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
			return ok ;
		}
	}

    // -- Notify the carrier model the we've finished updating the hardware
	// some workers will change the hardware
	for (unsigned i=0; i < mWorkers.size() && ok; ++i)
	{
		ok = mWorkers[i]->postUpdate() ;
		if (!ok)
		{
			mFailureReason->setFailReason( mWorkers[i]->failReason() ) ;
			return ok ;
		}
	}

    // -- Notify the carrier model that all changes are complete
	for (unsigned i=0; i < mWorkers.size(); ++i)
	{
		mWorkers[i]->changeComplete() ;
	}


	return ok ;
}


//-------------------------------------------------------------------------------------------------------------
std::string CommonCarrierModel::failReason(void)
{
	return mFailureReason->failReason() ; ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierHardwareIeq> CommonCarrierModel::getCarrierHardwareIeq() const
{
	// Default is to return NULL pointer
	return std::shared_ptr<ICarrierHardwareIeq>() ;
}


//=============================================================================================================
// Loggable I/F
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModel::show()
{
	// Needs to be overridden
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModel::show(std::ostream& os)
{
	// Call show method for each worker
	for (unsigned i=0; i < mWorkers.size(); ++i)
	{
		mWorkers[i]->show(os) ;
	}
}
