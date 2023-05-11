#ifndef _COMMON_CLEDCONTROL_H_
#define _COMMON_CLEDCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CLedControl.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <vector>
#include "ILed.h"
#include "Device.h"

namespace Mplane
{

class CLedControl: public virtual ILedControl, public Device
{
public:
    /**
     *
     */
    CLedControl( int deviceIndex, int numLeds );

    /**
     * \brief   Get the number of LED supported by the control interface
     * \return  integer value
     */
    virtual int getNumberOfLeds() override;

    /**
     * \brief   Get the LED interface for a given LED index, throw exception
     *          if incorrect
     * \return  return a reference to the LED given by the supplied index.
     */
    virtual std::shared_ptr<ILed>  getLed( int index ) override; /* throw (std::out_of_range) */

    /**
     * Is the LED initialisation complete? Depending on the LED, the initialisation may take a number of seconds
     * to run through.
     * @return true if complete
     */
    virtual bool isInitComplete() const override ;

    /**
     * \brief   Set the LED colour and state based on the value of the LED
     *          interface, throw exception if index is invalid.
     * \return  return state of the set process
     */
    virtual ReturnType::State setLed( ILed& ) =0; /* throw (std::out_of_range) */

    /**
     * Method use by final implementation to add an instance of an ILed
     * interface to the LED list.
     *
     * @param led
     * @return
     */
    ReturnType::State add( std::shared_ptr<ILed> led );


    /**
     * Make the LED group display themselves for the specified time
     * @param timeMs Run through the indication for this many milliseconds
     * @return RT_OK if OK
     */
    virtual ReturnType::State groupIndicate(unsigned timeMs) override ;


    // Direct ILed accessors

    /**
     * The final implementation of this method will cause the colour of the LED associated
     * with the instance of this interface to change to the colour provided, assuming
     * that colour is supported by the hardware.
     *
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if colour not supported.
     */
    virtual ReturnType::State setColour( unsigned index, ILed::LedColour setLedColour) override;

    /**
     * The final implementation of this method will cause the state of the LED associated
     * with the instance of this interface to change to the state provided, assuming
     * that state is supported by the hardware.
     *
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if state not supported.
     */
    virtual ReturnType::State setState( unsigned index, ILed::LedState setLedState ) override;

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if rate not supported.
     */
    virtual ReturnType::State setRate( unsigned index, unsigned transitionRate ) override;



    /**
     * Virtual destructor
     */
    virtual ~CLedControl();

protected:
    int mNumLeds;
    std::vector<std::shared_ptr<ILed>> mLeds;
};

}

#endif /* _COMMON_CLEDCONTROL_H_ */
