/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PowerSaver.cpp
 * \brief     TIF helper class which puts the board into a power saving mode
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>

#include "ISystemClockInput.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "PowerSaver.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
class PowerSaverInst : public PowerSaver {
public:
	PowerSaverInst() : PowerSaver() {}
	virtual ~PowerSaverInst() {}
};
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<PowerSaver> PowerSaver::getInstance()
{
	static std::shared_ptr<PowerSaver> instance(std::make_shared<PowerSaverInst>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PowerSaver::~PowerSaver()
{
}

void PowerSaver::shutdown()
{
	Conditional::Lock lock(mStartShutdown) ;
	mStartShutdown.signal() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PowerSaver::PowerSaver() :
	Task(),
	mStartShutdown()
{
	start() ;
}

//-------------------------------------------------------------------------------------------------------------
int PowerSaver::run()
{
	// this is a one-time run - once started we'll exit the application
	mStartShutdown.wait() ;

	// start up the external power save utility to unload the fpga
	int pid(::getpid()) ;
	std::string cmd("powersave " + std::to_string(pid) + "&") ;
	system(cmd.c_str()) ;

	// Turn off the TX
    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;
	for (auto tx : txPorts)
	{
		tx->setTxOff() ;
	}

	// @TODO - When IRxPort has the setRxOff() method declared
//	// Turn off the RX
//    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;
//	for (auto rx : rxPorts)
//	{
//		rx->setRxOff() ;
//	}

	// Kill the clocks
	std::shared_ptr<ISystemClockInput> clockInput(ISystemClockInput::getInstance()) ;
	clockInput->setClockInput(ISystemClockInput::CLKIN_NONE) ;

	// Wait a short time to let the TIF reply to client - if they start sending more commands then tough!
	Task::msSleep(2000) ;

	// Kill off the application
	::exit(0) ;

	return 1 ;
}
