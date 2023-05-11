/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSystem.cpp
 * \brief     Implementation of methods defined in the LedSystem class
 *
 *
 * \details   Implementation of methods defined in the LedSystem class
 *
 */

#include <string.h>
#include "ILed.h"

#include "LedSystem.h"
#include "GlobalTypeDefs.h"

#ifdef OFF_TARGET
#include "AnsiEsc.h"
#endif

using namespace Mplane;

// Set the priority of the task
static const int SYSLED_TASK_PRIORITY = (Task::PRIORITY_LOW + 5) ;

// tick time in ms
static const unsigned TASK_TICK_MS = 50 ;

Mplane::LedSystem::LedSystem( UINT16 writeGpioAddress) : Task(SYSLED_TASK_PRIORITY, Task::SMALL_STACK, "LedSystem", "LED"),
                                                          mWriteGpioAddress(writeGpioAddress),
														  gpioDevice( IGpioKernel::getInstance() ),
														  mEnableFlashLed(false),
														  mSolidColour(RED_LED),
														  mToggleState(SYS_LED_OFF),
														  mFlashColour(RED_LED),
														  mFlashRate(10),
														  mFlashTimerCounter(0),
														  mTaskRunning(true),
                                                          mConditional()
{
    // self start the associated task.
    start() ;
}

Mplane::LedSystem::~LedSystem()
{
	// stop the run() loop
	shutdown() ;
}

ReturnType::State Mplane::LedSystem::initialise(void)
{
    /*
     * This assumes that the I2C has already been initialised.
     */
    ReturnType::State returnState = ReturnType::RT_OK;

    eventInfo("--- LedSystem Initialisation ---");

    show();

    return returnState;
}

ReturnType::State Mplane::LedSystem::setLed( UINT8 ledNumber,
                                              UINT8 ledColour,
                                              UINT8 ledState,
                                              UINT8 ledRate)
{
    // Check that the led number does not exceed the maximum number of system LED's
    if( ledNumber > (NUM_LEDS - 1) )
    {
        // The supplied ledNumber exceeds the number of LED's supported.
        return ReturnType::RT_OUT_OF_RANGE;
    }

	switch( ledColour )
	{
	case ILed::LED_RED:
		mSolidColour = RED_LED;
		break;
	case ILed::LED_YELLOW:
		mSolidColour = YELLOW_LED;
		break;
	case ILed::LED_GREEN:
		mSolidColour = GREEN_LED;
		break;
	default:
		return ReturnType::RT_OUT_OF_RANGE;
	}

	ReturnType::State returnState{ReturnType::RT_OK} ;
	switch( ledState )
	{
	case ILed::LED_OFF:
		returnState = write( mWriteGpioAddress,
							 (UINT32)(SYS_LED_OFF  << SYS_LED_BASE_REG),
							 (UINT32)(SYS_LED_MASK << SYS_LED_BASE_REG) );
		mEnableFlashLed = false;
		break;
	case ILed::LED_ON:
		returnState = write( mWriteGpioAddress,
							 (UINT32)(mSolidColour << SYS_LED_BASE_REG),
							 (UINT32)(SYS_LED_MASK << SYS_LED_BASE_REG) );
		mEnableFlashLed = false;
		break;
	case ILed::LED_FLASH:
		mFlashColour    = mSolidColour;
		mEnableFlashLed = true;

		// Led flash rates have to be bigger than 1
		if( 0 == ledRate )
		{
			ledRate = 1;
		}

		mFlashRate  = ledRate * 5; // Scale the flash rate by 5 to prevent problems with values below 4!
		break;

	default:
		return ReturnType::RT_NOT_SUPPORTED;
	}

#ifdef OFF_TARGET
	std::string colour("BLACK") ;
	switch( ledColour )
	{
	case ILed::LED_RED:
		colour = "RED" ;
		break;
	case ILed::LED_YELLOW:
		colour = "YELLOW" ;
		break;
	case ILed::LED_GREEN:
		colour = "GREEN" ;
		break;
	default:
		colour = "BLACK" ;
	}

	std::string state("") ;
	switch( ledState )
	{
	case ILed::LED_OFF:
		state = "OFF" ;
		colour = "" ;
		break;
	case ILed::LED_ON:
		state = "ON" ;
		break;
	case ILed::LED_FLASH:
		state = "FLASH" ;
		break;

	default:
		state = "";
	}

	std::cerr << AnsiEsc::setColour(colour) <<
			"** LED " << state << " [" << colour << "] **" <<
			AnsiEsc::resetColour() <<
			std::endl ;
#endif
    return returnState ;
}

ReturnType::State Mplane::LedSystem::write(UINT32 regOffset, UINT32 value, UINT32 mask)
{
    // This method can be called from both run() and selectPath().
    // Protect with a mutex so that it cannot be called run at the same time.
    Mutex::Lock lock(mMutex) ;

    ReturnType::State returnValue;

    returnValue = gpioDevice->write(regOffset, value, mask);

    return returnValue;
}

void Mplane::LedSystem::show()
{
    eventInfo("LED SYSTEM");

    eventInfo("Write GPIO Address = 0x%04x", mWriteGpioAddress);
}

int Mplane::LedSystem::run()
{
    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRunning)
    {
        // keep this task alive
        kickSoftwareWatchdog();

        // Wait for timeout
        if (mConditional.wait(TASK_TICK_MS) == false)
        {
        	mFlashTimerCounter ++;

        	if( mFlashTimerCounter >= mFlashRate )
        	{
        		mFlashTimerCounter = 0;

				if( true == mEnableFlashLed )
				{
					if( SYS_LED_OFF == mToggleState )
					{
						// currently turned off, turn the LED on that we cached its colour
						write( mWriteGpioAddress, (UINT32)(mFlashColour << SYS_LED_BASE_REG), (UINT32)(SYS_LED_MASK << SYS_LED_BASE_REG) );

						mToggleState = SYS_LED_ON;
					}
					else
					{
						// currently turned on, turn LED off
						write( mWriteGpioAddress, (UINT32)(SYS_LED_OFF << SYS_LED_BASE_REG), (UINT32)(SYS_LED_MASK << SYS_LED_BASE_REG) );

						mToggleState = SYS_LED_OFF;
					}
				}
				else
				{
					// We are not flashing the LED, so there is nothing to do.
				}
        	}
        }
    }
    return 0;
}

void Mplane::LedSystem::shutdown(void)
{
    mTaskRunning = false ;
    msSleep(3*TASK_TICK_MS) ;
}
