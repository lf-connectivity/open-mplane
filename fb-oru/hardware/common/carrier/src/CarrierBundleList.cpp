/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierBundleList.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ITxPort.h"
#include "CarrierBundle.h"
#include "CarrierBundleList.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierBundleListSetter> ICarrierBundleListSetter::getInstance()
{
static std::shared_ptr<ICarrierBundleListSetter> instance(std::make_shared<CarrierBundleList>()) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierBundleList> ICarrierBundleList::getInstance()
{
	return ICarrierBundleListSetter::getInstance() ;
}





//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierBundleList::CarrierBundleList() :
	mNumAntennas(0),
	mMutex(),
	mCarrierBundles(),
	mMultiCarrierBundles()
{
	// Get the number of TX ports
	std::vector< std::shared_ptr<ITxPort> > txPorts( ITxPortFactory::getPorts() ) ;
	mNumAntennas = txPorts.size() ;

	// Create the storage
	for (unsigned antenna=0; antenna < mNumAntennas; ++antenna)
	{
		mCarrierBundles.push_back( std::make_shared<CarrierBundle>() ) ;
		mMultiCarrierBundles.push_back( std::make_shared<CarrierBundle>() ) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
CarrierBundleList::~CarrierBundleList()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierBundle> CarrierBundleList::getMultiCarrierBundle(unsigned tx) const
{
	if (tx >= mNumAntennas)
		return std::shared_ptr<ICarrierBundle>() ;

	// make a copy of this carrier bundle while locked - this means the values won't change under whoever uses them
	std::shared_ptr<ICarrierBundle> copy(std::make_shared<CarrierBundle>()) ;
	Mutex::Lock lock(mMutex) ;
	copy->set(mMultiCarrierBundles[tx]) ;
	return copy ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICarrierBundle> CarrierBundleList::getCarrierBundle(unsigned tx) const
{
	if (tx >= mNumAntennas)
		return std::shared_ptr<ICarrierBundle>() ;

	// make a copy of this carrier bundle while locked - this means the values won't change under whoever uses them
	std::shared_ptr<ICarrierBundle> copy(std::make_shared<CarrierBundle>()) ;
	Mutex::Lock lock(mMutex) ;
	copy->set(mCarrierBundles[tx]) ;
	return copy ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierBundleList::setMultiCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle)
{
	if (tx >= mNumAntennas)
		return ;

#ifdef OFF_TARGET
std::cerr << "CarrierBundleList["<<tx<<"]: setMultiCarrierBundle " << carrierBundle << std::endl ;
#endif

	Mutex::Lock lock(mMutex) ;
	mMultiCarrierBundles[tx]->set(carrierBundle) ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierBundleList::setCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle)
{
	if (tx >= mNumAntennas)
		return ;

#ifdef OFF_TARGET
std::cerr << "CarrierBundleList["<<tx<<"]: setCarrierBundle " << carrierBundle << std::endl ;
#endif

	Mutex::Lock lock(mMutex) ;
	mCarrierBundles[tx]->set(carrierBundle) ;
}
