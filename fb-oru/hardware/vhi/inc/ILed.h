#ifndef _ILED_H_
#define _ILED_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILed.h
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
#include "IDevice.h"

namespace Mplane
{

/**
 * This class provides a generic interface to the definition of an LED. The LED is internally
 * referenced to a unique index which is used by the implementation of the Mplane::LedControl
 * interface to identify the purpose of a particular LED.
 *
 * The interface provides methods that allow the user to get and set the LED colour, state
 * and rate of flash.
 *
 * Any unsupported colour or state will have no effect if requested and the implementation
 * condition will remain unchanged.
 *
 * \brief   Generic interface to a single LED
 */
class ILed
{
public:

    /**
     * \brief Enumeration of the current possible LED colours
     */
    enum LedColour
    {
        LED_GREEN,  //!> default LED colour of green.
        LED_AMBER,  //!> LED is Amber, (if supported)
        LED_BLUE,   //!> LED is Blue, (if supported)
        LED_RED,    //!> LED is Red, (if supported)
        LED_YELLOW, //!> LED is Yellow, (if supported)
        LED_WHITE   //!> LED is White, (if supported)
    };

    /**
     * \brief Enumeration of the current possible LED transition states
     */
    enum LedState
    {
        LED_OFF,    //!> Default state, the LED is OFF
        LED_ON,     //!> The LED is in the fully on state
        LED_FLASH,  //!> The LED is flashing on at the specified rate
        LED_BREATH  //!> the LED is breathing off to on and off again at the specific rate (if supported)
    };

    /**
     * \brief   Get the zero based index that can be used to reference the LED
     *          from a list of LED's.
     * \return  zero base index of the LED's
     */
    virtual const int getIndex() = 0;


    /**
     * \brief   Get the colour of the LED, defined by the LedColour enumeration
     * \return  LED Colour
     */
    virtual LedColour getColour() = 0;

    /**
     * The final implementation of this method will cause the colour of the LED associated
     * with the instance of this interface to change to the colour provided, assuming
     * that colour is supported by the hardware.
     *
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if colour not supported.
     */
    virtual ReturnType::State setColour( LedColour setLedColour) = 0;

    /**
     * \brief   Get the state of the LED, defined by the LedState enumeration
     * \return  LED state
     */
    virtual LedState getState() = 0;

    /**
     * The final implementation of this method will cause the state of the LED associated
     * with the instance of this interface to change to the state provided, assuming
     * that state is supported by the hardware.
     *
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if state not supported.
     */
    virtual ReturnType::State setState( LedState setLedState ) = 0;

    /**
     * \brief   Get the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  integer value
     */
    virtual unsigned getRate() = 0;

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if rate not supported.
     */
    virtual ReturnType::State setRate( unsigned transitionRate ) = 0;

    /**
     * Virtual destructor
     */
    virtual ~ILed() { };


    // Optimisation - set a collection of pending changes, then apply them all in one I2C transaction

    /**
     * The final implementation of this method will cause the colour of the LED associated
     * with the instance of this interface to change to the colour provided, assuming
     * that colour is supported by the hardware.
     *
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if colour not supported.
     */
    virtual ReturnType::State changeColour( LedColour setLedColour) = 0;

    /**
     * The final implementation of this method will cause the state of the LED associated
     * with the instance of this interface to change to the state provided, assuming
     * that state is supported by the hardware.
     *
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if state not supported.
     */
    virtual ReturnType::State changeState( LedState setLedState ) = 0;

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if rate not supported.
     */
    virtual ReturnType::State changeRate( unsigned transitionRate ) = 0;

    /**
     * Apply all of the pending changes
     * @return
     */
    virtual ReturnType::State applyChanges() = 0;



};

/**
 * The LedControl interface is used to describe a generic interface to the LED devices
 * supported by the hardware.
 *
 * The interface defines a method whereby an single instance of the LED control device
 * can be obtained. This interface defines the number of LEDs supported by the device
 * and a mechanism to get and set the LED characteristics using an LED index.
 *
 * The index can then be defined as a constant at the hardware implementation level for
 * use by the hardware specific application.
 *
 * \brief Generic LED control interface
 */
class ILedControl: public virtual IDevice
{
public:
    /**
     * \brief   Get a singleton instance of the LED interface
     * \return  SharePtr template to the ILedControl instance
     */
    static std::shared_ptr<ILedControl> getInterface( );

    /**
     * \brief   Get the number of LED supported by the control interface
     * \return  integer value
     */
    virtual int getNumberOfLeds() = 0;

    /**
     * \brief   Get the LED interface for a given LED index, throw exception
     *          if incorrect
     * \return  return a reference to the LED given by the supplied index.
     */
    virtual std::shared_ptr<ILed> getLed( int index ) =0 ; /* throw (std::out_of_range) */

    /**
     * Is the LED initialisation complete? Depending on the LED, the initialisation may take a number of seconds
     * to run through.
     * @return true if complete
     */
    virtual bool isInitComplete() const =0 ;

    /**
     * Make the LED group display themselves for the specified time
     * @param timeMs Run through the indication for this many milliseconds
     * @return RT_OK if OK
     */
    virtual ReturnType::State groupIndicate(unsigned timeMs) =0 ;


    // Direct ILed accessors

    /**
     * The final implementation of this method will cause the colour of the LED associated
     * with the instance of this interface to change to the colour provided, assuming
     * that colour is supported by the hardware.
     *
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if colour not supported.
     */
    virtual ReturnType::State setColour( unsigned index, ILed::LedColour setLedColour) = 0;

    /**
     * The final implementation of this method will cause the state of the LED associated
     * with the instance of this interface to change to the state provided, assuming
     * that state is supported by the hardware.
     *
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if state not supported.
     */
    virtual ReturnType::State setState( unsigned index, ILed::LedState setLedState ) = 0;

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if rate not supported.
     */
    virtual ReturnType::State setRate( unsigned index, unsigned transitionRate ) = 0;


    /**
     * Virtual destructor
     */
    virtual ~ILedControl() { };

protected:
    ILedControl() {};

};

} // namespace Mplane

#endif // _ILED_H_
