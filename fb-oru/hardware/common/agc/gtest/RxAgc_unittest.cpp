/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgc_unittest.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string.h>
#include <iostream>

#include "IRxPort.h"
#include "IRadio.h"
#include "IDevices.h"
#include "IAttenuator.h"
#include "RxAgc.h"

#include "TestCommonRxPort.h"
#include "TestCommonAttenuator.h"

#include "RxAgc_fixture.h"


using namespace Mplane ;

class TestRxAgc : public RxAgc
{
public:

	TestRxAgc(unsigned index, const std::string& name,
			std::shared_ptr<IRxPort> rxPort,
			std::shared_ptr<IAttenuator> rfAtten) :
				RxAgc(index, name, rxPort, rfAtten),
				mCalculateTable(false),
				mWriteTable(false)
	{
	}

	~TestRxAgc() {}

	bool isTableCalculated(void)
	{
		return mCalculateTable;
	}

	bool isTableWritten(void)
	{
		return mWriteTable;
	}

	void resetTable(void)
	{
		mCalculateTable = false;
		mWriteTable = false;
	}

protected:

    /**
     * Calculate table
     * Protected hook to be implemented by derived class
     */
    virtual void calculateTable( void ) override
    {
    	mCalculateTable = true;
    }

    /**
     * Program table
     * Protected hook to be implemented by derived class
     */
    virtual void writeTable( void ) override
    {
    	mWriteTable = true;
    }

    /**
     * Update the IF attenuation for current frequency from the table
     * Protected hook to be implemented by derived class
     */
    virtual void updateIfAtten() override
    {
    }

    /**
     * Read the desired attenuation for the FE level from the table
     * Protected hook to be implemented by derived class
     */
    virtual Power getDesiredAtten(unsigned feLevel) const override
    {
    	return Power(feLevel * 1.0);
    }

    bool mCalculateTable;
    bool mWriteTable;
};


class TestRxPortSubject : public TestCommonRxPort {
public:
	TestRxPortSubject(int index, const char* name) : TestCommonRxPort(index, name) {}

	ReturnType::State setFrequency(const Frequency& frequency)
	{
		TestCommonRxPort::setFrequency(frequency);

	    // Notify observers of the rx frequency that something has changed
	    static_cast< Subject<IFrequencyChange>* >(this)->notify();

	    return ReturnType::RT_OK;
	}

	void setTemperature(const Temperature temp)
	{
		mTemperature = temp;
		// Notify observers of the rx temperature that something has changed
		static_cast< Subject<ITemperatureChange>* >(this)->notify();
	}


};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(RxAgcTestFixture, AgcUpdate)
{
	std::shared_ptr<IRxPort> rxPort(std::make_shared<TestRxPortSubject>(1, "Rx1-Port"));
    std::shared_ptr<IAttenuator> rxRfAttn( std::make_shared<TestCommonAttenuator>(1, "Rx1-RfAtten", 1) ) ;

	std::cerr << "Get AGC" << std::endl ;
	std::shared_ptr<IRxAgc> agc(std::make_shared<TestRxAgc>(1, "RxAgc",
    		rxPort, rxRfAttn	)) ;

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set digital gain
	std::cerr << "Set Digital gain" << std::endl ;
	agc->setDigitalGain(3.0);
	sleep(1) ;

	// *should* have caused an update
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Reset table
	std::dynamic_pointer_cast<TestRxAgc>(agc)->resetTable();

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set freq
	std::cerr << "Set Frequency" << std::endl ;
	rxPort->setFrequency(2440000.0);
	sleep(1) ;

	// *should* have caused an update
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Reset table
	std::dynamic_pointer_cast<TestRxAgc>(agc)->resetTable();

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set temperature
	std::cerr << "Set Temperature" << std::endl ;
	std::dynamic_pointer_cast<TestRxPortSubject>(rxPort)->setTemperature(-10.0);
	sleep(1) ;

	// *should* have caused an update
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Reset table
	std::dynamic_pointer_cast<TestRxAgc>(agc)->resetTable();

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set temperature within hysterisis limit
	std::cerr << "Set Temperature within hysterisis" << std::endl ;
	std::dynamic_pointer_cast<TestRxPortSubject>(rxPort)->setTemperature(-8.0);
	sleep(1) ;

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set same frequency
	std::cerr << "Set same frequency" << std::endl ;
	rxPort->setFrequency(2440000.0);
	sleep(1) ;

	// No update expected
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_FALSE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// Set Rx point adjust
	std::cerr << "Set Rx point adjust" << std::endl ;
	agc->setRxPointAdjust(4.0);
	sleep(1) ;

	// *should* have caused an update
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableCalculated());
	EXPECT_TRUE(std::dynamic_pointer_cast<TestRxAgc>(agc)->isTableWritten());

	// test display
	std::stringstream ss ;
	agc->show(ss) ;
	std::cerr << ss.str() << std::endl ;
	ss.str("") ;
	agc->showDetail(ss) ;
	std::cerr << ss.str() << std::endl ;
	ss.str("") ;

}
