/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemLed.cpp
 * \brief     Implements the Pheonix system led board interface
 *
 *
 * \details   Implements the Pheonix system led board interface
 *
 */


#include "Task.h"
#include "GlobalTypeDefs.h"

#include "SystemLed.h"

using namespace Mplane;

const char* SystemLedControl::mDevName="SystemLed";


class SystemLedControl::CycleLedTask : public Task {
public:

	explicit CycleLedTask(std::shared_ptr<LedSystem> sysLedDevice) :
        Task( Task::PRIORITY_LOW, Task::SMALL_STACK, "CycleLedTask", "LED"),
        mSysLedDevice(sysLedDevice),

        mMutex(),
        mTaskRunning(false),
        mShutdown(false),
        mComplete(false)
	{
	}

	virtual ~CycleLedTask()
	{
		// Need to ensure task is shutdown
		mShutdown = true ;
		while (mTaskRunning)
		{
			Task::msSleep(100) ;
		}
	}

	virtual bool isComplete() const
	{
		Mutex::Lock lock(mMutex) ;
		return mComplete ;
	}

protected:

    virtual int run() override
    {
    	mTaskRunning = true ;
        int ledActionId = 1;

        ILoggable::logEventInfo("Cycle through all LED colours - GREEN, YELLOW, RED");

        ReturnType::State returnState{ReturnType::RT_OK} ;

        /**
         * \verify{@req_8403{054}} \n
         * \verify{@req_8403{055}} \n
         * \verify{@req_8403{056}} \n
         * \verify{@req_8403{057}} \n
         *
         * Cycle through all LED colours.
         */
        while (!mShutdown && ReturnType::RT_OK == returnState && ledActionId < POST_LED_LAST_ACTION)
        {
        	switch (ledActionId)
        	{
        	case 1:
        	    //                                    Led,         Colour,         State,    Effect rate
        	    // green LED on
        	    returnState = mSysLedDevice->setLed(SYSTEM_LED,  ILed::LED_GREEN, ILed::LED_ON, 0);
        	    Task::msSleep(POST_LED_ON_TIME_MS);
            	ledActionId++;
        		break;

        	case 2:
        	    // Yellow LED on
        	    returnState = mSysLedDevice->setLed(SYSTEM_LED,  ILed::LED_YELLOW, ILed::LED_ON, 0);
        	    Task::msSleep(POST_LED_ON_TIME_MS);
            	ledActionId++;
        		break;

        	case 3:
        	    // Red LED on
        	    returnState = mSysLedDevice->setLed(SYSTEM_LED,  ILed::LED_RED, ILed::LED_ON, 0);
        	    Task::msSleep(POST_LED_ON_TIME_MS);
            	ledActionId++;
        		break;

        	case 4:
        	default:
            	ledActionId = POST_LED_LAST_ACTION;
        		break;

        	}
        }

        // If the initialisation went well set the LED to RED ON.  The application software will then set it to its appropriate
        // state depending on the underlying system condition.
        if ( ReturnType::RT_OK == returnState )
        {
            //                                    Led,         Colour,         State,    Effect rate
            returnState = mSysLedDevice->setLed(SYSTEM_LED,  ILed::LED_RED, ILed::LED_ON, 0); // RED LED ON
        }
        else
        {
        	ILoggable::logEventInfo("%s - setLed error! - %s", __func__, ReturnType::getState(returnState));

            returnState = ReturnType::RT_OK; // Fake the result @@TODO
        }

		Mutex::Lock lock(mMutex) ;
        mTaskRunning = false ;
        mComplete = true ;
        return 0 ;
    }

private:
    // POST LED constants
    static const int POST_LED_LAST_ACTION = 0xff;  //!> Last action in the LED POST actions, terminates the action sequence
    static const int POST_LED_ON_TIME_MS = 1000;   //!> LED on time, 1000ms

    std::shared_ptr<LedSystem>     mSysLedDevice; //!> Reference to the System LED device implementation.
    mutable Mutex mMutex ;
    bool mTaskRunning ;
    bool mShutdown ;
    bool mComplete ;
};


std::shared_ptr<ILedControl> SystemLedControl::getInstance(int deviceId )
{
    static std::shared_ptr<ILedControl> _sysLedInstance( std::make_shared<SystemLedControl>(deviceId) );

    return _sysLedInstance;
}


ReturnType::State SystemLedControl::setLed(ILed& led)
        /* throw (std::out_of_range) */
{
	ReturnType::State returnState = ReturnType::RT_ERROR;

	// Can't allow any LED setting while we're still initialising - if we get here then there's a problem!
	if (!isInitComplete())
		return returnState ;

    // Set the System LED if we have an index of 0
    if( SYSTEM_LED == led.getIndex() )
    {
        returnState = mSysLedDevice->setLed(led.getIndex(), led.getColour(), led.getState(), led.getRate());
    }

    return returnState;
}

void SystemLedControl::show(void)
{
}

void SystemLedControl::show(std::ostream& os)
{
}

SystemLedControl::~SystemLedControl()
{
}

SystemLedControl::SystemLedControl( int deviceIndex ):
	CLedControl( deviceIndex, NUM_LEDS ),
	Loggable(mDevName,"DV"),

	mSysLedDevice(),
	mLedCycle(),
	mInitComplete(false)

{
    // Create the System LED
    std::shared_ptr<ILed> led( new SystemLed( 0, *this ) );
    add( led );

    // Get an instance of the Led System object for us to use
    mSysLedDevice = std::shared_ptr<LedSystem>(new LedSystem(GPIO_REG_WRITE_ADDR));

}

ReturnType::State SystemLedControl::doInit()
{
	mInitComplete = false ;
    ReturnType::State returnState;

    eventInfo("System LED initialise");

    std::string resultString = "SYSTEMLED Init RESULT: ";

    // Initialise the System LED device
    returnState = mSysLedDevice->initialise();
    if (returnState != ReturnType::RT_OK)
    	mInitComplete = true ;

    // If set up was ok then cycle the LED colours
    if (returnState == ReturnType::RT_OK)
    {
    	// clear out any previous task
    	if (mLedCycle)
    	{
    		mLedCycle.reset() ;
    	}

    	// Start up new
    	mLedCycle = std::make_shared<SystemLedControl::CycleLedTask>(mSysLedDevice) ;
    	mLedCycle->start() ;
    }

    // Append the result to the result string and store it for longevity
    resultString += ReturnType::getState(returnState);
    setInitResultString(resultString);

    return returnState;
}

bool SystemLedControl::isInitComplete() const
{
	if (mInitComplete)
		return true ;

	// If there's not an instance of the LED cycler then we can stop now
	if (!mLedCycle)
	{
		mInitComplete = true ;
		return true ;
	}

	// Get the status of the LED cycler
	mInitComplete = mLedCycle->isComplete() ;
	return mInitComplete ;
}

int SystemLedControl::getNumberOfLeds()
{
    return NUM_LEDS;
}


SystemLed::SystemLed(int index, CLedControl &controller) : CLed( index, controller )
{
}

SystemLed::~SystemLed()
{
}

void SystemLed::show(std::ostream& os)
{
}

ReturnType::State SystemLed::verifyColour(LedColour setLedColour)
{
    ReturnType::State state = ReturnType::RT_OUT_OF_RANGE;

    switch( setLedColour )
    {
    case ILed::LED_RED:
    case ILed::LED_GREEN:
    case ILed::LED_YELLOW:
        state = ReturnType::RT_OK;
        break;
    case ILed::LED_BLUE:
    case ILed::LED_WHITE:
    case ILed::LED_AMBER:
        break;
    }

    return state;
}
