/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcState.cpp
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
#include "IFpgaMgr.h"

#include "QmcValType.hpp"
#include "QmcState.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
QmcState::QmcState(unsigned index) :
	mIndex(index),
	mState(),
	mAttenState( std::make_shared<QmcAttenState>(index) )
{
	std::vector<std::shared_ptr<ITxPort>> txPorts(ITxPortFactory::getPorts()) ;
	std::shared_ptr<ITxPort> txPort(txPorts[mIndex]) ;
    std::vector< std::shared_ptr<ISRxPort> > srxPorts(ISRxPortFactory::getPorts()) ;
	std::shared_ptr<ISRxPort> srxPort(srxPorts[0]) ;
	std::shared_ptr<IFpgaSystemRegs> fpga( IFpgaMgr::getIFpgaSystemRegs() ) ;

	// == create the list of values to be stored:

	//	SetSRxFreq
	std::shared_ptr<QmcVal> srxFreq(new QmcValType<Frequency>(
		[srxPort]()->Frequency { return srxPort->getFrequency(); },
		[srxPort](const Frequency& freq) { return srxPort->setFrequency(freq) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(srxFreq) ;

	//	SetSRxSourcePath
	std::shared_ptr<QmcVal> srxPath(new QmcValType<int>(
		[fpga]()->int { return fpga->read_paCalCntl(); },
		[fpga](const int& path) { return fpga->write_paCalCntl(path) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(srxPath) ;

	//	SetSRxPathControl
	std::shared_ptr<QmcVal> srxPathCntl(new QmcValType<int>(
		[fpga]()->int { return 0; },
		[fpga](const int& state) { return fpga->write_forceDpdOverride(state) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(srxPathCntl) ;


	//	CW mode
	std::shared_ptr<QmcVal> txCwMode(new QmcValType<ITxPort::Mode>(
		[txPort]()->ITxPort::Mode { return txPort->getMode(); },
		[txPort](const ITxPort::Mode& mode) { return txPort->setMode(mode) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txCwMode) ;

	//	SetTxDACCW
	std::shared_ptr<QmcVal> txCw(new QmcValType<Power>(
		[txPort]()->Power { return txPort->getCWPower(); },
		[txPort](const Power& power) { return txPort->setCWPower(power) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txCw) ;

	//	SetTxDACModulated
	std::shared_ptr<QmcVal> txMode(new QmcValType<ITxPort::Mode>(
		[txPort]()->ITxPort::Mode { return txPort->getMode(); },
		[txPort](const ITxPort::Mode& mode) { return txPort->setMode(mode) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txMode) ;

	//	SetTxDACNCO
	std::shared_ptr<QmcVal> txDacNco(new QmcValType<float>(
		[txPort]()->float { return txPort->getDacIfOffset(); },
		[txPort](const float& nco) { return txPort->setDacIfOffset(nco) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txDacNco) ;

	//	TX enable
	std::shared_ptr<QmcVal> txEnable(new QmcValType<bool>(
		[txPort]()->unsigned { return txPort->isTxOn() ; },
		[txPort](const bool& enable) {

			// only set if state is different
			bool isOn(txPort->isTxOn()) ;
			if (isOn == enable)
				return true ;

			if (enable)
				return txPort->setTxOn() == ReturnType::RT_OK ;

			return txPort->setTxOff() == ReturnType::RT_OK ;
		}
	)) ;
	mState.push_back(txEnable) ;

	//	SetTxOutputAtten
	std::shared_ptr<QmcVal> txOpAtten(new QmcValType<ITxPort::AttenPadState>(
		[txPort]()->ITxPort::AttenPadState { return txPort->getOpAttenPad(); },
		[txPort](const ITxPort::AttenPadState& atten) { return txPort->setOpAttenPad(atten) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txOpAtten) ;

	//	SetTxScaler
	//
	std::shared_ptr<QmcVal> txScaler(new QmcValType<Power>(
		[txPort]()->Power { return txPort->getDigitalPowerScaler(); },
		[txPort](const Power& scaler) { return txPort->setDigitalPowerScaler(scaler.get()) == ReturnType::RT_OK;  }
	)) ;
	mState.push_back(txScaler) ;



	// Process the list to store current values
	for (auto qmcVal : mState)
	{
		qmcVal->save() ;
	}

}

//-------------------------------------------------------------------------------------------------------------
QmcState::~QmcState()
{
	// Restore states
	for (auto qmcVal : mState)
	{
		qmcVal->restore() ;
	}

}
