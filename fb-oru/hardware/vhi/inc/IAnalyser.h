#ifndef _MPLANE_IANALYSER_H_
#define _MPLANE_IANALYSER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISigGen.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Power.h"
#include "Frequency.h"
#include "GlobalTypeDefs.h"
#include <stdexcept>

namespace Mplane
{

/**
 * This class defines an interface to Signal Analyser Generator functionality provided by the
 * factory test unit implementation.
 */
class IAnalyser
{
public:
    /**
     * A static factory interface used to return a shared pointer
     * @param path
     * @return
     */
    static IAnalyser& getInterface( int path ) ; /* throw ( std::invalid_argument) */

    /**
     * Method used to set the amplitude of the signal generator output for the
     * path instance for the selected interface.
     *
     * @param amplitude output power in dBm
     * @return RT_OK is amplitude set, otherwise some other error case.
     */
    virtual  ReturnType::State setAmplitude( const Power& amplitude ) = 0;


    /*! \brief  Set the signal generator frequency
     *
     *  Used to set the signal generator output frequency
     *
     *  \param frequency  the frequency to set in Khz
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setFrequency(const Frequency& frequency) = 0;

    /**
     * Method used to get the current amplitude setting.
     *
     * @return currently set output amplitude in dBm
     */
    virtual const Power getAmplitude() = 0;

    /**
      * Method used to get the current scaler setting.
      *
      * @return currently set output amplitude in dBm
      */
     virtual const Power getScaler() = 0;

    /*! \brief  Get the signal; generator frequency
     *
     *  Used to read the set frequency for the signal generator
     *
     *  \return the set frequency
     */
    virtual const Frequency getFrequency(void) = 0;


    /**
     * Method used to get the current input power to the analyser.
     *
     * @return current measured input power in dBm
     */
    virtual const Power getPower() = 0;

    /**
     * Method used to return the dBfs to dBm correction factor for the current
     * analyser measurements at the current input amplitude.
     *
     * @return correction factor to convert dBfs to dBm
     */
    virtual Power getCorrection() = 0;

    /**
     * Method used to get dBFS to dBm offset at the current frequency.
     *
     * @return current offset in dBm's
     */
    virtual ReturnType::State getdBFS2dBm( Power& offst ) = 0;

    /**
     * Method used to get dBFS to dBm offset at the given frequency.
     *
     * @return current offset in dBm's
     */
    virtual ReturnType::State getdBFS2dBm( Power& offset, const Frequency& frequency ) = 0;

    virtual ~IAnalyser(){}
};


}




#endif /* _MPLANE_IANALYSER_H_ */
