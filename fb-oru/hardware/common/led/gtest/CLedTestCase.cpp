
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestILed.cpp
 * \brief     Pure virtual interface that defines methods needed to access the
 *            LED indicators.
 *
 *
 * \details   Pure virtual interface that defines methods needed to access the
 *            LED indicators.
 *
 */

#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

#include "GlobalTypeDefs.h"

#include "gtest/gtest.h"

#include "ILed.h"
#include "CLed.h"
#include "CLedControl.h"
//#include "ILedTestCase.h"

/*! \brief
 *
 *
 */

using namespace Mplane;

static const int MAX_LEDS = 2 ;


class TestLed: public CLed
{
public:

    TestLed( int index, CLedControl &controller ):
        CLed( index, controller )
    {

    }

    virtual  ReturnType::State verifyColour( LedColour setLedColour )
    {
        ReturnType::State state = ReturnType::RT_OK;
        // for test purposes, reject WHITE
        if( setLedColour == ILed::LED_WHITE )
        {
            state = ReturnType::RT_OUT_OF_RANGE;
        }
        return state;
    }

};


class TestLedControl: public CLedControl
{
public:
    int               mIndex;     //!> Defines the LED instance index in the LED list
    ILed::LedState    mState;     //!> the LEDs current state
    ILed::LedColour   mColour;    //!> the LEDs current state
    int               mRate;      //!> the LEDs flash or breath rate

    TestLedControl(int deviceIndex):
        CLedControl( deviceIndex, MAX_LEDS ),
        mIndex(0),
        mState( ILed::LED_OFF ),
        mColour( ILed::LED_GREEN ),
        mRate(0)
    {
        for( int index = 0 ; index < MAX_LEDS ; index++ )
        {
            std::shared_ptr<ILed> led( new TestLed( index, *this ) );
            add( led );
        }
    }

    virtual ReturnType::State setLed( ILed& led ) /* throw (std::out_of_range) */
    {
        // for test purposes don't support the breath state
        if( led.getState() == ILed::LED_BREATH )
        {
            return ReturnType::RT_OUT_OF_RANGE;
        }
        // for test coverage purposes don't support the BLUE colour
        if( led.getColour() == ILed::LED_BLUE )
        {
            return ReturnType::RT_OUT_OF_RANGE;
        }

        if( led.getRate() > 10000)
        {
            return ReturnType::RT_OUT_OF_RANGE;
        }
        mIndex = led.getIndex();
        mState = led.getState();
        mColour = led.getColour();
        mRate = led.getRate();

        return ReturnType::RT_OK;
    }

    virtual ~TestLedControl()
    {
    }

    virtual void show(void)
    {

    }

    virtual ReturnType::State doInit()
    {
        ReturnType::State state = ReturnType::RT_OK;

        return state;
    }

    virtual int getNumberOfLeds()
    {
        return MAX_LEDS;
    }
};




/* Google Tests */
TEST(CommonLedControl, unittest)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    std::shared_ptr<ILedControl> ledControl = std::make_shared<TestLedControl>(0);
    ASSERT_NE( ledControl, nullptr );
    ASSERT_TRUE(ledControl->getNumberOfLeds() == 2);

    std::shared_ptr<TestLedControl> ledc = std::dynamic_pointer_cast<TestLedControl>(ledControl);

    std::shared_ptr<ILed> l1 = ledc->getLed( 0 );
    ASSERT_NE( l1, nullptr );
    ASSERT_EQ( l1->getIndex(), 0 );

    std::shared_ptr<ILed> l2 = ledc->getLed( 1 );
    ASSERT_NE( l2, nullptr );
    ASSERT_EQ( l2->getIndex(), 1 );

    std::shared_ptr<ILed> l3 = 0;
    try
    {
        // try and get an invalid led
        l3 = ledc->getLed( 2 );
        ASSERT_TRUE( false );   // should not get here so test won't fail

    }catch( std::out_of_range &e)
    {
        ASSERT_TRUE( l3 == nullptr );
    }

    ASSERT_EQ( l1->setColour( ILed::LED_RED ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getColour(), ILed::LED_RED );
    ASSERT_EQ( ledc->mColour, ILed::LED_RED );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l1->setColour( ILed::LED_GREEN ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getColour(), ILed::LED_GREEN );
    ASSERT_EQ( ledc->mColour, ILed::LED_GREEN );

    ASSERT_EQ( l1->setColour( ILed::LED_AMBER ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getColour(), ILed::LED_AMBER );
    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );

    // use WHITE to test the set fail case, colour shouldn't change
    ASSERT_EQ( l1->setColour( ILed::LED_WHITE ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l1->getColour(), ILed::LED_AMBER ); // check led is unchanged
    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );

    // use BLUE to test failure in the controller setLed method for conditional
    // code coverage in CLed implementation
    // use WHITE to test the set fail case, colour shouldn't change
    ASSERT_EQ( l1->setColour( ILed::LED_BLUE ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l1->getColour(), ILed::LED_AMBER ); // check led is unchanged
    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l2->setColour( ILed::LED_RED ), ReturnType::RT_OK);
    ASSERT_EQ( ledc->mIndex, 1);

    ASSERT_EQ( ledc->mColour, ILed::LED_RED );

    ASSERT_EQ( l2->setColour( ILed::LED_GREEN ), ReturnType::RT_OK);

    ASSERT_EQ( ledc->mColour, ILed::LED_GREEN );

    ASSERT_EQ( l2->setColour( ILed::LED_AMBER ), ReturnType::RT_OK);

    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );

    // use WHITE to test the set fail case, colour shouldn't change
    ASSERT_EQ( l2->setColour( ILed::LED_WHITE ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l2->getColour(), ILed::LED_AMBER ); // check led is unchanged
    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );

    // use BLUE to test failure in the controller setLed method for conditional
    // code coverage in CLed implementation
    // use WHITE to test the set fail case, colour shouldn't change
    ASSERT_EQ( l2->setColour( ILed::LED_BLUE ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l2->getColour(), ILed::LED_AMBER ); // check led is unchanged
    ASSERT_EQ( ledc->mColour, ILed::LED_AMBER );
    ASSERT_EQ( ledc->mIndex, 1);


    // now test the state change
    ASSERT_EQ( l1->setState( ILed::LED_ON ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getState(), ILed::LED_ON );
    ASSERT_EQ( ledc->mState, ILed::LED_ON );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l1->setState( ILed::LED_FLASH ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getState(), ILed::LED_FLASH );
    ASSERT_EQ( ledc->mState, ILed::LED_FLASH );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l2->setState( ILed::LED_ON ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getState(), ILed::LED_ON );
    ASSERT_EQ( ledc->mState, ILed::LED_ON );
    ASSERT_EQ( ledc->mIndex, 1);
    // I know it's silly but check led 1 didnt change
    ASSERT_EQ( l1->setState( ILed::LED_FLASH ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getState(), ILed::LED_FLASH );

    ASSERT_EQ( l2->setState( ILed::LED_FLASH ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getState(), ILed::LED_FLASH );
    ASSERT_EQ( ledc->mState, ILed::LED_FLASH );
    ASSERT_EQ( ledc->mIndex, 1);
    // I know it's silly but check led 1 didnt change
    ASSERT_EQ( l1->setState( ILed::LED_FLASH ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getState(), ILed::LED_FLASH );

    ASSERT_EQ( l1->setState( ILed::LED_OFF ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getState(), ILed::LED_OFF );
    ASSERT_EQ( ledc->mState, ILed::LED_OFF );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l1->setState( ILed::LED_BREATH ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l1->getState(), ILed::LED_OFF );
    ASSERT_EQ( ledc->mState, ILed::LED_OFF );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l2->setState( ILed::LED_OFF ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getState(), ILed::LED_OFF );
    ASSERT_EQ( ledc->mState, ILed::LED_OFF );
    ASSERT_EQ( ledc->mIndex, 1);

    ASSERT_EQ( l2->setState( ILed::LED_BREATH ), ReturnType::RT_OUT_OF_RANGE );
    ASSERT_EQ( l2->getState(), ILed::LED_OFF );
    ASSERT_EQ( ledc->mState, ILed::LED_OFF );
    ASSERT_EQ( ledc->mIndex, 1);

    // now check the rate, fails over 10,000
    ASSERT_EQ( l1->setRate( 1000 ), ReturnType::RT_OK);
    ASSERT_EQ( l1->getRate(),1000u );
    ASSERT_EQ( ledc->mRate, 1000 );
    ASSERT_EQ( ledc->mIndex, 0);

    // now check the rate, fails over 10,000
    ASSERT_EQ( l1->setRate( 100000 ), ReturnType::RT_OUT_OF_RANGE);
    ASSERT_EQ( l1->getRate(),1000u );
    ASSERT_EQ( ledc->mRate, 1000 );
    ASSERT_EQ( ledc->mIndex, 0);

    ASSERT_EQ( l2->setRate( 1000 ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getRate(),1000u );
    ASSERT_EQ( ledc->mRate, 1000 );
    ASSERT_EQ( ledc->mIndex, 1);

    // now check the rate, fails over 10,000
    ASSERT_EQ( l2->setRate( 100000 ), ReturnType::RT_OUT_OF_RANGE);
    ASSERT_EQ( l2->getRate(),1000u );
    ASSERT_EQ( ledc->mRate, 1000 );
    ASSERT_EQ( ledc->mIndex, 1);

    ASSERT_EQ( l1->setRate( 0 ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getRate(),1000u );
    ASSERT_EQ( l1->getRate(),0u );
    ASSERT_EQ( ledc->mRate, 0 );

    ASSERT_EQ( l2->setRate( 0 ), ReturnType::RT_OK);
    ASSERT_EQ( l2->getRate(),0u );
    ASSERT_EQ( ledc->mRate, 0 );
    ASSERT_EQ( ledc->mIndex, 1);

}
