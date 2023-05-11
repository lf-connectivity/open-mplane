
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModelListWorker.cpp
 * \brief     Carrier Model Worker list manager
 *
 *
 * \details    	This class contains the information and methods for performing the carrier model actions
 *  			on a CarrierHardwareList (i.e. a list of CarrierHardware objects).
 *
 *  			Class just implements the generic ICarrierModelWorker interface but passes the calls
 *  			to the ICarrierHardwareList
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonCarrierFail.h"
#include "CommonCarrierModelListWorker.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierModelListWorker::CommonCarrierModelListWorker(unsigned maxCarriers, std::shared_ptr<ICarrierHardwareList> carrierList) :
	mMaxCarriers(maxCarriers),
	mFailureReason( new CommonCarrierFail() ),
	mCarrierList(carrierList)
{
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierModelListWorker::~CommonCarrierModelListWorker()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::initialise(void)
{
	// No op
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::addCarrier(const ICarrier& carrier)
{
	// Pass to list
	mCarrierList->addCarrier(carrier) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::validateChange(const ICarrier& carrier)
{
	// No op
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::carrierChange(const ICarrier& carrier)
{
	// Pass to list
	bool status = mCarrierList->carrierChange(carrier) ;
	if (!status)
		mFailureReason->setFailReason( mCarrierList->failReason() ) ;
	return status ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::preUpdate()
{
	// Pass to list
	bool status = mCarrierList->preUpdate() ;
	if (!status)
		mFailureReason->setFailReason( mCarrierList->failReason() ) ;
	return status ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::updateHardware()
{
	// Pass to list
	bool status = mCarrierList->updateHardware() ;
	if (!status)
		mFailureReason->setFailReason( mCarrierList->failReason() ) ;
	return status ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelListWorker::postUpdate()
{
	// Pass to list
	bool status = mCarrierList->postUpdate() ;
	if (!status)
		mFailureReason->setFailReason( mCarrierList->failReason() ) ;
	return status ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelListWorker::changeComplete()
{
	// Pass to list
	mCarrierList->changeComplete() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonCarrierModelListWorker::failReason(void)
{
	return mFailureReason->failReason() ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CommonCarrierModelListWorker::setFailReason(std::string reason)
{
	mFailureReason->setFailReason(reason);
}

//=============================================================================================================
// Loggable I/F
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelListWorker::show()
{
	// Needs to be overridden
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelListWorker::show(std::ostream& os)
{
	// Needs to be overridden
}
