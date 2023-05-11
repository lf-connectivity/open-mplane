/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcDacState.cpp
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

#include "QmcValType.hpp"
#include "QmcDacState.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
QmcDacState::QmcDacState(unsigned index) :
	mRestore(true),
	mIndex(index),
	mState()
{
	std::vector<std::shared_ptr<ITxPort>> txPorts(ITxPortFactory::getPorts()) ;
	std::shared_ptr<ITxPort> txPort(txPorts[mIndex]) ;

	// == create the list of values to be stored:

	//	DacDCOffset
	std::shared_ptr<QmcVal> dc(new QmcValPairType<int>(
		[txPort](int& a, int& b) { txPort->getDacDCOffset(a, b); },
		[txPort](const int& a, const int& b) { return txPort->setDacDCOffset(a, b) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(dc) ;

	//	DacMagOffset
	std::shared_ptr<QmcVal> mag(new QmcValPairType<int>(
		[txPort](int& a, int& b) { txPort->getDacMagOffset(a, b); },
		[txPort](const int& a, const int& b) { return txPort->setDacMagOffset(a, b) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(mag) ;

	//	DacPhaseOffset
	std::shared_ptr<QmcVal> phase(new QmcValPairType<int>(
		[txPort](int& a, int& b) { txPort->getDacPhaseOffset(a, b); },
		[txPort](const int& a, const int& b) { return txPort->setDacPhaseOffset(a, b) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(phase) ;


	// Process the list to store current values
	for (auto qmcVal : mState)
	{
		qmcVal->save() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
QmcDacState::~QmcDacState()
{
	if (!mRestore)
		return ;

	// Restore states
	for (auto qmcVal : mState)
	{
		qmcVal->restore() ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void QmcDacState::noRestore()
{
	mRestore = false ;
}
