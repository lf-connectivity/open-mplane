#ifndef _VRH_IATTENUATOR_H_
#define _VRH_IATTENUATOR_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAttenuator.h
 * \brief     A file to define generic interface to a Attenuator device
 *
 *
 * \details   This file defines a generic interface to a Attenuator device
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Power.h"
#include "Temperature.h"

#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic Attenuator interface
 *
 *  A virtual interface base class defining an interface to an attenuator.
 *  The interface contains configuration and control aspects.
 */
class IAttenuator: public virtual IDevice
{
public:


    /*! \brief  Get the attenuator current setting
     *
     *  Get the attenuator current attenuation level. This is the attenuation as supported by the
     *  resolution of the attenuator hardware
     *
     *  \return the attenuation level
     */
    virtual Power getAttenuation(void) = 0;

    /*! \brief  Get the attenuator current setting residual
     *
     *  When an attenuation value is requested, it is quantised into the amount that the hardware
     *  can actually support (based on attenuation step resolution) and a residual amount which
     *  is the difference between the requested attenuation and the amount applied by the hardware
     *
     *  \return the attenuation residual amount
     */
    virtual Power getAttenuationResidual(void) = 0;

    /*! \brief  Set the attenuator attenuation level
     *
     *  Set the attenuator attenuation level.
     *
     *  \param  attenLevel  the required attenuation level
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual ReturnType::State setAttenuation(Power attenLevel) = 0;

    /*! \brief  Set the attenuator attenuation level
     *
     *  Set the attenuator attenuation level.
     *
     *  \param  attenLevel  the required attenuation level
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual ReturnType::State setAttenuation(Power attenLevel, Temperature temperature) = 0;


    /**
     * Call this method so set the attenuator to the maximum attenuation it supports.
     * @return
     */
    virtual ReturnType::State setMaxAttenuation() = 0;

    /*! \brief  Get the attenuator maximum attenuation level
     *
     *  Get the attenuator max attenuation level
     *
     *  \return the max attenuation level
     */
    virtual Power getMaxAttenuation(void) = 0;

    /*! \brief  get the attenuators minimum attenuation level
     *
     *  Get the attenuators minimum possible attenuation value.
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual Power getMinAttenuation(void) = 0;

    /*! \brief  Destructor
     *
     *  Should never be called.
     */
    virtual ~IAttenuator() { };


    /**
     * Convert a requested attenuation value into a control register value
     * @param attenuation Requested attenuation
     * @return control value
     */
    virtual unsigned int calcControl(Power attenuation) =0 ;

    /**
     * Convert a requested attenuation value into a control register value
     * @param attenuation Requested attenuation
     * @param temperature Current temperature
     * @return control value
     */
    virtual unsigned int calcControl(Power attenuation, Temperature temperature) =0 ;

    /**
     * Convert the control register value into an attenuation
     * @param control
     * @return attenuation
     */
    virtual Power calcAttenuation(unsigned int control) =0 ;



protected:
    /**
     * Given an attenuation value, return the value adjusted to fit within the min/max attenuation limits
     * @param attenuation
     * @return attenuation adjusted within the min/max limits
     */
    virtual Power limitAttenuation(const Power& attenuation) const =0 ;

    /**
     * Is the provided attenuation within limits?
     * @param attenuation
     * @return true if inside limits; false otherwise
     */
    virtual bool isValidAttenuation(const Power& attenuation) const =0 ;


protected:
    IAttenuator() {}


};


} /* namespace Mplane */

#endif /* _VRH_IATTENUATOR_H_ */
