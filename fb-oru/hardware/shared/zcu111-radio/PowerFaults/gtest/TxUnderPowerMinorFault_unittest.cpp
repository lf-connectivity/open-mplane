/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxUnderPowerMinorFault_unittest.cpp
 * \brief     Google Test of SynthClockFault
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the TxUnderPowerMinorFault class.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IFault.h"
#include "IFaultOwner.h"
#include "Fault.h"
#include "FaultOwner.h"

#include "IRadio.h"
#include "ITxPort.h"
#include "IDevices.h"
#include "ISynth.h"
#include "ICarrier.h"
#include "ICarrierServer.h"

#include "TxUnderPowerFaultMinor.h"
#include "TxUnderPowerMinorFaultOwner.h"
#include "OffTargetFPGA.h"

using namespace Mplane;
using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(TxUnderPowerFaultMinor, Test)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IFault> faultTx1(make_fault<Tx1UnderPowerFaultMinor>());
	std::shared_ptr<IFault> faultTx2(make_fault<Tx2UnderPowerFaultMinor>());
	std::shared_ptr<IFault> faultTx3(make_fault<Tx3UnderPowerFaultMinor>());
	std::shared_ptr<IFault> faultTx4(make_fault<Tx4UnderPowerFaultMinor>());

	std::shared_ptr<IFaultOwner> faultOwner (make_faultOwner<TxUnderPowerMinorFaultOwner>());

	// no fault
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	EXPECT_FALSE(faultTx3->isFaultPresent()) ;
	EXPECT_FALSE(faultTx4->isFaultPresent()) ;

	std::cout << "** No Faults ** " << std::endl ;

	// fault
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    ITxPort& txPort1 = radio->getTxPort(0);
	ITxPort& txPort2 = radio->getTxPort(1);

    // Check over power major faults for all available Tx ports
    // Fault in ports 1,2
    // get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;
    fpgaEmu->reset() ;
    // start with no alarm
    fpgaEmu->writeField("lowPowerAlarm[0]", 0) ;
    fpgaEmu->writeField("lowPowerAlarm[1]", 0) ;

    Frequency frequency(2115000.0, Frequency::KHz);

    txPort1.setFrequency( frequency );
    txPort2.setFrequency( frequency );

    // Setup a 10Mhz LTE carrier on Tx path 2
	std::shared_ptr<ICarrierServer> server(ICarrierServer::getInstance());
    ICarrierSetter& cs( server->getCarrierSetter(0) );

    cs.setType(ICarrier::CARRTYPE_LTE10);
    cs.setTxPower( 33.0 );
    cs.setTxFrequency(frequency);
    cs.setRxFrequency(frequency);
    cs.setGroupSizeUp( 4 );
    cs.setGroupSizeDown( 4 );
    cs.setTxScaling( -18.0 );
    cs.setTxContainer( 0, 1 );
    cs.setTxContainer( 1, 5 );
    cs.setState(ICarrier::STATE_ENABLE);
    server->setCarrier(cs);

    // Alarm Tx1
    fpgaEmu->writeField("lowPowerAlarm[0]", 1) ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	faultOwner->updateFaults() ;;
	EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx1->isFaultPresent()) ;

    // Alarm Tx2
    fpgaEmu->writeField("lowPowerAlarm[1]", 1) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	faultOwner->updateFaults() ;;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
	faultOwner->updateFaults() ;
	EXPECT_TRUE(faultTx2->isFaultPresent()) ;

    cs.setState(ICarrier::STATE_DISABLE);
    server->setCarrier(cs);

    fpgaEmu->writeField("lowPowerAlarm[0]", 1) ;
    fpgaEmu->writeField("lowPowerAlarm[1]", 1) ;
    EXPECT_TRUE(faultTx1->isFaultPresent()) ;
    EXPECT_TRUE(faultTx2->isFaultPresent()) ;

    faultOwner->updateFaults() ;
    EXPECT_TRUE(faultTx1->isFaultPresent()) ;
	EXPECT_TRUE(faultTx2->isFaultPresent()) ;

	faultOwner->updateFaults() ;;
    EXPECT_TRUE(faultTx1->isFaultPresent()) ;
	EXPECT_TRUE(faultTx2->isFaultPresent()) ;

	faultOwner->updateFaults() ;
    EXPECT_FALSE(faultTx1->isFaultPresent()) ;
	EXPECT_FALSE(faultTx2->isFaultPresent()) ;
}
