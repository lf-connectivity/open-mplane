/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcAttenState.cpp
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
#include "ISRxPort.h"

#include "Frequency.h"
#include "Power.h"

#include "QmcValType.hpp"

#include "QmcAttenState.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
QmcAttenState::QmcAttenState(unsigned index) :
	mIndex(index),
	mState()
{
	std::vector<std::shared_ptr<ITxPort>> txPorts(ITxPortFactory::getPorts()) ;
	std::shared_ptr<ITxPort> txPort(txPorts[mIndex]) ;
    std::vector< std::shared_ptr<ISRxPort> > srxPorts(ISRxPortFactory::getPorts()) ;
	std::shared_ptr<ISRxPort> srxPort(srxPorts[0]) ;

	//	SetSRxAtten
	std::shared_ptr<QmcVal> srxAtten(new QmcValType<Power>(
		[srxPort]()->Power {
//			std::cerr << "SrxAtten : get" << std::endl ;
			return srxPort->getAttenuation();
		},
		[srxPort](const Power& atten) {
//			std::cerr << "SrxAtten : restore=" << atten << std::endl ;
			return srxPort->setAttenuation(atten) == ReturnType::RT_OK;
		}
	)) ;
	mState.push_back(srxAtten) ;

	//	SetTxIfAtten
	std::shared_ptr<QmcVal> txIfAtten(new QmcValType<Power>(
		[txPort]()->Power {
//			std::cerr << "TxIfAtten : get" << std::endl ;
			return txPort->getIFAttenuation();
		},
		[txPort](const Power& atten) {
//			std::cerr << "TxIfAtten : restore=" << atten << std::endl ;
			return txPort->setIFAttenuation(atten) == ReturnType::RT_OK;
		}
	)) ;
	mState.push_back(txIfAtten) ;

	//	SetTxRfAtten
	std::shared_ptr<QmcVal> txRfAtten(new QmcValType<Power>(
		[txPort]()->Power {
//			std::cerr << "TxRfAtten : get" << std::endl ;
			return txPort->getRFAttenuation();
		},
		[txPort](const Power& atten) {
//			std::cerr << "TxRfAtten : restore=" << atten << std::endl ;
			return txPort->setRFAttenuation(atten) == ReturnType::RT_OK;
		}
	)) ;
	mState.push_back(txRfAtten) ;


	// Process the list to store current values
	for (auto qmcVal : mState)
	{
		qmcVal->save() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
QmcAttenState::~QmcAttenState()
{
	// Restore states
	for (auto qmcVal : mState)
	{
		qmcVal->restore() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool QmcAttenState::maxAtten()
{
//	std::cerr << "Attens : set max" << std::endl ;

	for (auto qmcVal : mState)
	{
		auto qmcAttenVal( std::dynamic_pointer_cast< QmcValType<Power> >(qmcVal) ) ;
		if (!qmcAttenVal->setVal(Power(31.0)))
			return false ;
	}

	return true ;
}
