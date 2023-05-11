/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <iostream>

#include "ITxPort.h"
#include "ISRxPort.h"

#include "stringfunc.hpp"

// Uncomment (here or in file that includes this header) to gather expected register writes
//#define GATHER_SEQUENCES

#include "QmcCal_fixture.h"

#include "QmcState.h"

using namespace Mplane ;

//=============================================================================================================
// CLASS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class QmcValTestFixture : public QmcCalTestFixture
{
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(QmcValTestFixture, basic)
{

	std::vector<std::shared_ptr<ITxPort>> txPorts(ITxPortFactory::getPorts()) ;

    std::vector< std::shared_ptr<ISRxPort> > srxPorts(ISRxPortFactory::getPorts()) ;
	std::shared_ptr<ISRxPort> srxPort(srxPorts[0]) ;

	Frequency freq0(234000.0, Frequency::KHz) ;
	Frequency freq1(235000.0, Frequency::KHz) ;

	EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setFrequency(freq0)) ;
	EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setFrequency(freq1)) ;

	EXPECT_EQ(freq0, txPorts[0]->getFrequency()) ;
	EXPECT_EQ(freq1, txPorts[1]->getFrequency()) ;

	Power atten0(12.0) ;
	Power atten1(34.0) ;
	Power attenRf0(56.0) ;
	Power attenRf1(78.0) ;
	Power attenSrx(90.0) ;
	Power attenSrx2(190.0) ;

	EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setIFAttenuation(atten0)) ;
	EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setIFAttenuation(atten1)) ;
	EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setRFAttenuation(attenRf0)) ;
	EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setRFAttenuation(attenRf1)) ;
	EXPECT_EQ(ReturnType::RT_OK, srxPort->setAttenuation(attenSrx)) ;

	EXPECT_EQ(atten0, txPorts[0]->getIFAttenuation()) ;
	EXPECT_EQ(atten1, txPorts[1]->getIFAttenuation()) ;
	EXPECT_EQ(attenRf0, txPorts[0]->getRFAttenuation()) ;
	EXPECT_EQ(attenRf1, txPorts[1]->getRFAttenuation()) ;
	EXPECT_EQ(attenSrx, srxPort->getAttenuation()) ;

	// TxFreq should *NOT* be saved
	{
		QmcState state0(0) ;
		QmcState state1(1) ;

		// swap - should be swapped in this context
		EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setFrequency(freq1)) ;
		EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setFrequency(freq0)) ;

		EXPECT_EQ(freq1, txPorts[0]->getFrequency()) ;
		EXPECT_EQ(freq0, txPorts[1]->getFrequency()) ;


		EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setIFAttenuation(atten1)) ;
		EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setIFAttenuation(atten0)) ;
		EXPECT_EQ(ReturnType::RT_OK, txPorts[0]->setRFAttenuation(attenRf1)) ;
		EXPECT_EQ(ReturnType::RT_OK, txPorts[1]->setRFAttenuation(attenRf0)) ;
		EXPECT_EQ(ReturnType::RT_OK, srxPort->setAttenuation(attenSrx2)) ;

		EXPECT_EQ(atten1, txPorts[0]->getIFAttenuation()) ;
		EXPECT_EQ(atten0, txPorts[1]->getIFAttenuation()) ;

		EXPECT_EQ(attenRf1, txPorts[0]->getRFAttenuation()) ;
		EXPECT_EQ(attenRf0, txPorts[1]->getRFAttenuation()) ;
		EXPECT_EQ(attenSrx2, srxPort->getAttenuation()) ;

	}
	// All states should now be restored

	EXPECT_EQ(freq1, txPorts[0]->getFrequency()) ;
	EXPECT_EQ(freq0, txPorts[1]->getFrequency()) ;

	EXPECT_EQ(atten0, txPorts[0]->getIFAttenuation()) ;
	EXPECT_EQ(atten1, txPorts[1]->getIFAttenuation()) ;
	EXPECT_EQ(attenRf0, txPorts[0]->getRFAttenuation()) ;
	EXPECT_EQ(attenRf1, txPorts[1]->getRFAttenuation()) ;
	EXPECT_EQ(attenSrx, srxPort->getAttenuation()) ;


}
