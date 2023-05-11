
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModelWorker.cpp
 * \brief     Carrier Model Worker interface
 *
 *
 * \details    This class contains the information and methods for performing the carrier model actions
 *  			on particular areas of the hardware representation of the carriers.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonCarrierFail.h"
#include "CommonCarrierModelWorker.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierModelWorker::CommonCarrierModelWorker(unsigned maxCarriers, std::shared_ptr<ICarrierHardwareList> carrierList) :
	mMaxCarriers(maxCarriers),
	mCarrierList(carrierList),
	mFailureReason( new CommonCarrierFail() )
{
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierModelWorker::~CommonCarrierModelWorker()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::initialise(void)
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::addCarrier(const ICarrier& carrier)
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::validateChange(const ICarrier& carrier)
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::carrierChange(const ICarrier& carrier)
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::preUpdate()
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::updateHardware()
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierModelWorker::postUpdate()
{
	// Implement in derived class
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelWorker::changeComplete()
{
	// No op
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonCarrierModelWorker::failReason(void)
{
	return mFailureReason->failReason() ;
}


//=============================================================================================================
// Loggable I/F
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelWorker::show()
{
	// Needs to be overridden
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierModelWorker::show(std::ostream& os)
{
	// Needs to be overridden
}
