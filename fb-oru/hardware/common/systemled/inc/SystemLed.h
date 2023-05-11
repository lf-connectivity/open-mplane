#ifndef _COMMON_SYSTEMLED_H_
#define _COMMON_SYSTEMLED_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SystemLed.h
 * \brief     Defines the implementation of an led control interface for the Pheonix 8 port LED board
 *
 *
 * \details   This file defines the implementation of the Mplane::ILedControl and Mplane::ILed
 * interface as defined by the physical requirements of the Pheonix 8 port LED board. The board
 * supports 8 leds, identified as  T1, B1, T2, B2, T3, B3, T4, B4 - where T/B = top/bottom and
 * 1 to 4 is left to right.
 *
 * Each LED can support the colours RED, GREEN and AMBER (ORANGE) and can be either ON, OFF,
 * FLASHING or BREATHING.
 *
 *
 */

#include "CLedControl.h"
#include "CLed.h"

#include "Loggable.h"


#include "LedSystem.h"


namespace Mplane
{

class LedSystem;


/**
 * This class provides an implementation of the Mplane::ILedControl interface
 * for the Pheonix System LED
 */
class SystemLedControl: public CLedControl, public Loggable
{
public:

    // Definition of LED references. NOTE - This must align to the definitions in LedSystem.h
    static const int SYSTEM_LED = 0;    //!> Index for the System LED

    static const int NUM_LEDS = 1;  //!> number of LEDs supported

    /**
     * Constructor for
     *
     * The device index is provided during board initialisation and is a unique device
     * identifier.
     */
    explicit SystemLedControl( int deviceIndex );

    /**
     * Method used to get an instance of an LED board that supports 8 tri-colour LEDs.
     * This class supports the ILedControl interface
     *
     *
     * @param deviceIndex - optional index used to retrieve multiple devices
     * @return an ILedControl interface.
     */
    static std::shared_ptr<ILedControl> getInstance( int deviceId );


    /**
     * Implement the virtual method used to set the colour and state of an
     * LED interface into the device.
     * @param
     * @return
     */
    virtual ReturnType::State setLed( ILed& ) ; /* throw (std::out_of_range) */

    /**
     * Method defined by the base Device class to enforce show state data.
     */
    virtual void show(void);

    /**
     * @brief Show system LED data settings to output stream
     *
     * Write the details of the system LED settings to the given output stream for TIF
     *
     * @param os target output stream
     */
    virtual void show(std::ostream& os);


    /**
     * Method defined by the base Initialise class in order to initialise the LED board
     * during board bring up.
     *
     * This is equivalent to a Power-On Self Test (POST) procedure named in requirement documentation.\n
     * For the ATG project this meets requirements:\n
     * \satisfy{@req_8403{054}} \n
     * \satisfy{@req_8403{055}} \n
     * \satisfy{@req_8403{056}} \n
     * \satisfy{@req_8403{057}} \n
     *
     * Initialises the LED, then cycles through all LED colours - GREEN, YELLOW, RED.
     * Leaves the initialisation with the LED set to RED ON.
     *
     * @return RT_OK if all ok
     */
    virtual ReturnType::State doInit();

    /**
     * Is the LED initialisation complete? Depending on the LED, the initialisation may take a number of seconds
     * to run through.
     * @return true if complete
     */
    virtual bool isInitComplete() const override ;


    /**
     * Default constructor
     */
    virtual ~SystemLedControl();

    /**
     * \brief   Get the number of LED supported by the control interface
     * \return  integer value
     */
    virtual int getNumberOfLeds();

private:

    static const ULONG GPIO_REG_WRITE_ADDR = 0x0800; //!> GPIO address to write to to update the system LED.

//    // POST LED constants
//    static const int POST_LED_LAST_ACTION = 0xff;  //!> Last action in the LED POST actions, terminates the action sequence
//    static const int POST_LED_ON_TIME_MS = 1000;   //!> LED on time, 1000ms

protected:
    std::shared_ptr<LedSystem>     mSysLedDevice; //!> Reference to the System LED device implementation.

    static const char*             mDevName;      //!> Reference for device name, used for debug.

    // Create a separate thread to handle toggling the LEDs
    class CycleLedTask ;
    std::shared_ptr<CycleLedTask>	mLedCycle ;

    mutable bool					mInitComplete ;	// Flag set once all LED initialisation is completed - can take a number of seconds
};

/**
 * This class provides an implementation of the Mplane::ILed interface for the type
 * of LED used as the system LED.
 *
 * It will support colours, RED, GREEN and YELLOW and the states ON, OFF & FLASH
 *
 */
class SystemLed: public CLed
{
public:
    SystemLed( int index, CLedControl &controller );

    virtual ~SystemLed();

    /**
     * @brief Show system LED data settings to output stream
     *
     * Write the details of the system LED settings to the given output stream for TIF
     *
     * @param os target output stream
     */
    virtual void show(std::ostream& os);

protected:
    /**
     * This method is called by the Mplane::CLed::setColour method and must be implemented
     * here to verify that the colour being set is supported.
     *
     * This is used to ensure that only RED, GREEN, YELLOW are supported
     *
     * @param setLedColour
     * @return RT_OK if colour OK, other wise ?
     */
    virtual  ReturnType::State verifyColour( LedColour setLedColour );

};

}


#endif /* _COMMON_SYSTEMLED_H_ */
