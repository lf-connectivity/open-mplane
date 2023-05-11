#ifndef _CLED_H_
#define _CLED_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CLed.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ILed.h"
#include "CLedControl.h"
#include "LedSettings.h"

namespace Mplane
{

class CLed: public ILed
{
public:

    CLed( int index, CLedControl &controller );

    CLed( int index, CLedControl &controller, LedState state, LedColour colour, unsigned rate );

    /**
     * \brief   Get the zero based index that can be used to reference the LED
     *          from a list of LED's.
     * \return  zero base index of the LED's
     */
    virtual const int getIndex();


    /**
     * \brief   Get the colour of the LED, defined by the LedColour enumeration
     * \return  LED Colour
     */
    virtual LedColour getColour();

    /**
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return state of the set process
     */
    virtual ReturnType::State setColour( LedColour setLedColour);

    /**
     * \brief   Get the state of the LED, defined by the LedState enumeration
     * \return  LED state
     */
    virtual LedState getState();

    /**
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  The return state of the set process
     */
    virtual ReturnType::State setState( LedState setLedState );

    /**
     * \brief   Get the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  integer value
     */
    virtual unsigned getRate();

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return state of the set process
     */
    virtual ReturnType::State setRate( unsigned transitionRate );

    /**
     * Virtual destructor
     */
    virtual ~CLed();

    // Optimisation - set a collection of pending changes, then apply them all in one I2C transaction

    /**
     * The final implementation of this method will cause the colour of the LED associated
     * with the instance of this interface to change to the colour provided, assuming
     * that colour is supported by the hardware.
     *
     * \brief   Set the colour of the LED, defined by the LedColour enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if colour not supported.
     */
    virtual ReturnType::State changeColour( LedColour setLedColour) override;

    /**
     * The final implementation of this method will cause the state of the LED associated
     * with the instance of this interface to change to the state provided, assuming
     * that state is supported by the hardware.
     *
     * \brief   Set the state of the LED, defined by the LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if state not supported.
     */
    virtual ReturnType::State changeState( LedState setLedState ) override;

    /**
     * \brief   Set the rate of the LED transition effects, defined by the
     *          LedState enumeration
     * \return  return RT_OK if changed OK, RT_OUT_OF_RANGE if rate not supported.
     */
    virtual ReturnType::State changeRate( unsigned transitionRate ) override;

    /**
     * Apply all of the pending changes
     * @return
     */
    virtual ReturnType::State applyChanges() override;



protected:

    /**
     * This method is called by the set colour method and must be implemented by the final
     * ILed implementation in order to verify that the colour being set is supported by
     * the final implementation.
     *
     * This is used to ensure that trying to set for example a RED/GREEN/AMBER tricolour LED
     * as BLUE.
     *
     * @param setLedColour
     * @return RT_OK if colour OK, other wise ?
     */
    virtual  ReturnType::State verifyColour( LedColour setLedColour ) = 0;

private:
    CLedControl &mController;    //!> a reference to our LEDs device controller
    int         mIndex;     //!> Defines the LED instance index in the LED list
    LedSettings	mSettings ;
    LedSettings	mPendingSettings ;
};


}


#endif /* _CLED_H_ */
