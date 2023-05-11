/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSettings.h
 * \brief     Settings for an LED
 *
 *
 * \details
 *
 */


#ifndef LEDSETTINGS_H_
#define LEDSETTINGS_H_

#include <iostream>
#include <string>
#include <map>
#include "ILed.h"

namespace Mplane {

class LedSettings {
public:
	~LedSettings() {}

    LedSettings() :
        mState( ILed::LED_OFF ),
        mColour( ILed::LED_GREEN ),
        mRate( 0 ),
        mStateChanged( false ),
        mColourChanged( false ),
        mRateChanged( false )
    {}

    LedSettings(const LedSettings& rhs) :
        mState( rhs.mState ),
        mColour( rhs.mColour ),
        mRate( rhs.mRate ),
        mStateChanged( rhs.mStateChanged ),
        mColourChanged( rhs.mColourChanged ),
        mRateChanged( rhs.mRateChanged )
    {}

    void clearChange()
    {
    	mStateChanged = false ;
    	mColourChanged = false ;
    	mRateChanged = false ;
    }

    void copyChanged(const LedSettings& src)
    {
    	if (src.mStateChanged)
    		mState = src.mState ;
    	if (src.mColourChanged)
    		mColour = src.mColour ;
    	if (src.mRateChanged)
    		mRate = src.mRate ;
    }



    ILed::LedColour getColour()
    {
    	return mColour ;
    }

    ILed::LedState getState()
    {
    	return mState ;
    }

    unsigned getRate()
    {
    	return mRate ;
    }


    bool isColourChanged()
    {
    	return mColourChanged ;
    }

    bool isStateChanged()
    {
    	return mStateChanged ;
    }

    bool isRateChanged()
    {
    	return mRateChanged ;
    }


    void setColour( ILed::LedColour colour)
    {
    	mColour = colour ;
    	mColourChanged = true ;
    }

    void setState( ILed::LedState state )
    {
    	mState = state ;
    	mStateChanged = true ;
    }

    void setRate( unsigned rate )
    {
    	mRate = rate ;
    	mRateChanged = true ;
    }


    void show(std::ostream& os) const
    {
    	const std::map<ILed::LedColour, std::string> COLOUR_NAMES {
			{ ILed::LED_GREEN,  "GREEN" },
			{ ILed::LED_AMBER,  "AMBER" },
			{ ILed::LED_BLUE,   "BLUE" },
			{ ILed::LED_RED,    "RED" },
			{ ILed::LED_YELLOW, "YELLOW" },
			{ ILed::LED_WHITE,   "WHITE" },
        };

    	const std::map<ILed::LedState, std::string> STATE_NAMES {
			{ ILed::LED_OFF,     "OFF" },
			{ ILed::LED_ON,      "ON" },
			{ ILed::LED_FLASH,   "FLASH" },
			{ ILed::LED_BREATH,  "BREATH" },
        };

    	os << "Settings" << std::endl ;
    	os << "Colour..........[" << (mColourChanged ? "*" : " ") << "]: " << COLOUR_NAMES.at(mColour) << std::endl ;
    	os << "State...........[" << (mStateChanged ? "*" : " ") << "]: " << STATE_NAMES.at(mState) << std::endl ;
    	os << "Rate............[" << (mRateChanged ? "*" : " ") << "]: " << mRate << std::endl ;
    }

private:
	ILed::LedState    mState;     //!> the LEDs current state
	ILed::LedColour   mColour;    //!> the LEDs current state
    unsigned          mRate;      //!> the LEDs flash or breath rate

    bool		mStateChanged ;
    bool		mColourChanged ;
    bool		mRateChanged ;
} ;

}

inline std::ostream& operator<<(std::ostream& os, const Mplane::LedSettings& rhs)
{
	rhs.show(os) ;
	return os ;
}

#endif /* LEDSETTINGS_H_ */
