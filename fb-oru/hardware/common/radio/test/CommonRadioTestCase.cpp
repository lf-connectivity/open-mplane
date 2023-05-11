/*
 * TestCase.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: gdurban
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "CommonRadio.h"

#include "CommonRadioTestCase.h"

#include "ITxPort.h"
#include "IRxPort.h"
#include "IRadioInfo.h"

#include "CommonRxPort.h"
#include "CommonTxPort.h"
#include "CommonAdc.h"
#include "CommonAttenuator.h"
#include "CommonDac.h"
#include "CommonSynth.h"

#include "TestCommonRadio.h"

#include <vector>

using namespace Mplane;



/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonRadioTestCase );

using namespace std;


/****** Area for unit test specifics  ******/
class CommonTestRadioPostInit : public IRadioPostInit
{
public:
	CommonTestRadioPostInit() {} ;
	~CommonTestRadioPostInit() {} ;

	virtual ReturnType::State operator ()()
	{
		return ReturnType::RT_OK ;
	}
};

std::shared_ptr<IRadioPostInit> IRadioPostInit::getInterface(void)
{
	static std::shared_ptr<IRadioPostInit> instance( new CommonTestRadioPostInit() );

	return instance;
}


/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonRadioTestCase::unittest()
{
	cout << "CommonRadio unit test" << endl;

	/**
	 * Create a test common radio instance
	 */
	int numRxPorts = 4;
	int numTxPorts = 4;
	int numAdcs = 0;
	int numDacs = 0;
	int numRxSynths = 4;
	int numTxSynths = 4;
	int numDpdSynths = 2;
	int numRxRfAtten = 0;
	int numRxIfAtten = 0;
	int numTxRfAtten = 0;
	int numTxIfAtten = 0;
	int numDpdAtten = 2;

	// get a reference to the TestCommonRadio that implements any pure virtual methods.
	std::shared_ptr<IRadio> radio( IRadioFactory::getInterface() );

	CPPUNIT_ASSERT(radio->getNumberOfRxPorts() == numRxPorts);
	if (numRxPorts > 0)
	{
		for (int port = 0; port < numRxPorts; port++ )
		{
			IRxPort &rxport = radio->getRxPort( port );

			CPPUNIT_ASSERT( rxport.getIndex() == port);
			CPPUNIT_ASSERT( rxport.getName() == "TestCommonRadio_RX" );

		}
		try
		{
			IRxPort &rxport = radio->getRxPort( numRxPorts );

			CPPUNIT_ASSERT( rxport.getIndex() == 0);
		}
		catch( std::invalid_argument &ia )
		{
			CPPUNIT_ASSERT( strcmp( ia.what(), "invalid index" ) == 0 );
		}

		try
		{
			IRxPort &rxport = radio->getRxPort( -1 );

			CPPUNIT_ASSERT( rxport.getIndex() == 0);
		}
		catch( std::invalid_argument &ia )
		{
			CPPUNIT_ASSERT( strcmp( ia.what(), "invalid index" ) == 0 );
		}
	}

	CPPUNIT_ASSERT(radio->getNumberOfTxPorts() == numTxPorts);
	if (numTxPorts > 0)
	{
		for (int port = 0; port < numTxPorts; port++ )
		{
			ITxPort &txport = radio->getTxPort( port );

			CPPUNIT_ASSERT( txport.getIndex() == port);
			CPPUNIT_ASSERT( txport.getName() == "TestCommonRadio_TX" );
		}

		try
		{
			ITxPort &txport = radio->getTxPort( numTxPorts );

			CPPUNIT_ASSERT( txport.getIndex() == 0);
		}
		catch( std::invalid_argument &ia )
		{
			CPPUNIT_ASSERT( strcmp( ia.what(), "invalid index" ) == 0 );
		}

		try
		{
			ITxPort &txport = radio->getTxPort( -1 );

			CPPUNIT_ASSERT( txport.getIndex() == 0);
		}
		catch( std::invalid_argument &ia )
		{
			CPPUNIT_ASSERT( strcmp( ia.what(), "invalid index" ) == 0 );
		}
	}

	if (numAdcs > 0)
	{
		for (int index = 0; index < numAdcs; index++ )
		{
			std::shared_ptr<IAdc> adc = radio->getDevices().getRxAdc( index );

			CPPUNIT_ASSERT( adc->getIndex() == index);
			CPPUNIT_ASSERT( strcmp( adc->getName().c_str(), "TestCommonAdc_Rx") == 0 );
		}

		std::shared_ptr<IAdc> adc = radio->getDevices().getRxAdc( numAdcs );
		CPPUNIT_ASSERT(adc == nullptr);
	}

	if (numDacs > 0)
	{
		for (int index = 0; index < numDacs; index++ )
		{
			std::shared_ptr<IDac> dac = radio->getDevices().getTxDac( index );

			CPPUNIT_ASSERT( dac->getIndex() == index);
			CPPUNIT_ASSERT( strcmp(dac->getName().c_str(), "TestCommonDac_Tx") == 0 );
		}

		std::shared_ptr<IDac> dac = radio->getDevices().getTxDac( numDacs );
		CPPUNIT_ASSERT(dac == nullptr);
	}

	if (numRxRfAtten > 0)
	{
		for (int index = 0; index < numRxRfAtten; index++ )
		{
			std::shared_ptr<IAttenuator> atten = radio->getDevices().getRxRFAttenuator( index );

			CPPUNIT_ASSERT( atten->getIndex() == index );
			CPPUNIT_ASSERT( strcmp(atten->getName().c_str(), "TestCommonAttenuator") == 0 );
		}

		std::shared_ptr<IAttenuator> atten = radio->getDevices().getRxRFAttenuator( numRxRfAtten );
		CPPUNIT_ASSERT(atten == nullptr);
	}

	if (numRxIfAtten > 0)
	{
		for (int index = 0; index < numRxIfAtten; index++ )
		{
			std::shared_ptr<IAttenuator> atten = radio->getDevices().getRxIFAttenuator( index );

			CPPUNIT_ASSERT( atten->getIndex() == index );
			CPPUNIT_ASSERT( strcmp(atten->getName().c_str(), "TestCommonAttenuator") == 0 );
		}

		std::shared_ptr<IAttenuator> atten = radio->getDevices().getRxIFAttenuator( numRxIfAtten );
		CPPUNIT_ASSERT(atten == nullptr);
	}

	if (numTxRfAtten > 0)
	{
		for (int index = 0; index < numTxRfAtten; index++ )
		{
			std::shared_ptr<IAttenuator> atten = radio->getDevices().getTxRFAttenuator( index );

			CPPUNIT_ASSERT( atten->getIndex() == index );
			CPPUNIT_ASSERT( strcmp(atten->getName().c_str(), "TestCommonAttenuator") == 0 );
		}

		std::shared_ptr<IAttenuator> atten = radio->getDevices().getTxRFAttenuator( numTxRfAtten );
		CPPUNIT_ASSERT(atten == nullptr);
	}

	if (numTxIfAtten > 0)
	{
		for (int index = 0; index < numTxIfAtten; index++ )
		{
			std::shared_ptr<IAttenuator> atten = radio->getDevices().getTxIFAttenuator( index );

			CPPUNIT_ASSERT( atten->getIndex() == index );
			CPPUNIT_ASSERT( strcmp(atten->getName().c_str(), "TestCommonAttenuator") == 0 );
		}

		std::shared_ptr<IAttenuator> atten = radio->getDevices().getTxIFAttenuator( numTxIfAtten );
		CPPUNIT_ASSERT(atten == nullptr);
	}

	if (numDpdAtten > 0)
	{
		for (int index = 0; index < numDpdAtten; index++ )
		{
			std::shared_ptr<IAttenuator> atten = radio->getDevices().getDpdAttenuator( index );

			CPPUNIT_ASSERT( atten->getIndex() == index );
			CPPUNIT_ASSERT( strcmp(atten->getName().c_str(), "TestCommonAttenuator") == 0 );
		}

		std::shared_ptr<IAttenuator> atten = radio->getDevices().getDpdAttenuator( numDpdAtten );
		CPPUNIT_ASSERT(atten == nullptr);
	}

	if (numRxSynths > 0)
	{
		for (int index = 0; index < numRxSynths; index++ )
		{
			std::shared_ptr<ISynth> synth = radio->getDevices().getRxSynth( index );

			CPPUNIT_ASSERT( synth->getIndex() == index );
			CPPUNIT_ASSERT( strcmp( synth->getName().c_str(), "Rx Synth" ) == 0 );
		}

		std::shared_ptr<ISynth> synth = radio->getDevices().getRxSynth( numRxSynths );
		CPPUNIT_ASSERT(synth == nullptr);
	}

	if (numTxSynths > 0)
	{
		for (int index = 0; index < numTxSynths; index++ )
		{
			std::shared_ptr<ISynth> synth = radio->getDevices().getTxSynth( index );

			CPPUNIT_ASSERT( synth->getIndex() == index );
			CPPUNIT_ASSERT( strcmp( synth->getName().c_str(), "Tx Synth" ) == 0 );
		}

		std::shared_ptr<ISynth> synth = radio->getDevices().getTxSynth( numTxSynths );
		CPPUNIT_ASSERT(synth == nullptr);
	}

	if (numDpdSynths > 0)
	{
		for (int index = 0; index < numDpdSynths; index++ )
		{
			std::shared_ptr<ISynth> synth = radio->getDevices().getDpdSynth( index );

			CPPUNIT_ASSERT( synth->getIndex() == index );
			CPPUNIT_ASSERT( strcmp( synth->getName().c_str(), "DPD Synth" ) == 0 );
		}

		std::shared_ptr<ISynth> synth = radio->getDevices().getDpdSynth( numDpdSynths );
		CPPUNIT_ASSERT(synth == nullptr);
	}

	CPPUNIT_ASSERT( radio->updateTemperatureData() == ReturnType::RT_OK );
	CPPUNIT_ASSERT( radio->updatePowerSupplyData() == ReturnType::RT_OK );

	CPPUNIT_ASSERT( radio->shutdown() == true );

	std::shared_ptr<IRadioInfo> cri = radio->getInfo();

	CPPUNIT_ASSERT( cri->getHardwareID() == 0xFF );

#if 0
	std::shared_ptr<CommonRadio> commRadio( std::dynamic_pointer_cast<CommonRadio>(radio) );

	CPPUNIT_ASSERT( commRadio->initialise() == ReturnType::RT_OK );


	cout << "The CommonRadio Initialise result:  " << commRadio->getInitResultString() << endl;
	CPPUNIT_ASSERT( commRadio->getInitResultString() == "COMMONRADIO INITIALISE RESULT: _OK");
	cout << "The CommonRadio Initialise execution duration was " << commRadio->getInitDurationTime() << " usecs" << endl;

	// Test the error return if calling the initialise method more than once
	CPPUNIT_ASSERT( commRadio->isInitComplete() == true );
	//CPPUNIT_ASSERT( commRadio->initialise() == ReturnType::RT_ALREADY_INITIALISED );
	CPPUNIT_ASSERT( commRadio->initialise() == ReturnType::RT_OK );
	// The result string is unchanged, as it shows the result from the initial
	// call to initialise
	CPPUNIT_ASSERT( commRadio->getInitResultString() == "COMMONRADIO INITIALISE RESULT: _OK");

	// DO *NOT* DELETE THE POINTER BY HAND - NEED TO LEAVE std::shared_ptr TO MANAGE IT
	//commRadio->~CommonRadio();
#endif
}
