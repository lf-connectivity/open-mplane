/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AttnBase.h
 * \brief     Common shared attenuator methods
 *
 *
 * \details
 *
 */


#ifndef ATTNBASE_H_
#define ATTNBASE_H_

#include "IAttenuator.h"
#include "IAttenuatorDriver.h"
#include "Loggable.h"
#include "Device.h"

namespace Mplane {

class AttnBase : public virtual IAttenuator, public Device, public Loggable
{
public:
    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based device index of the Attenuator (0..MAX_NUM_DEVICES)
     *  \param name   name string for the Attenuator
     *  \param attenId the Id given to the Attenuator
     */
    AttnBase( std::shared_ptr<IAttenuatorDriver> driver, int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~AttnBase();


	// Loggable interface

    /*! \brief  Dump the Attenuator registers
     *
     *  Dump the state of the Attenuator registers to the console or log file
     */
    virtual void show(void) override ;


    // IAttenuator interface

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "ATTEN INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /*! \brief  Get the attenuator current setting
     *
     *  Get the attenuator current attenuation level. This is the attenuation as supported by the
     *  resolution of the attenuator hardware
     *
     *  \return the attenuation level
     */
    virtual Power getAttenuation(void) override;

    /*! \brief  Get the attenuator current setting residual
     *
     *  When an attenuation value is requested, it is quantised into the amount that the hardware
     *  can actually support (based on attenuation step resolution) and a residual amount which
     *  is the difference between the requested attenuation and the amount applied by the hardware
     *
     *  \return the attenuation residual amount
     */
    virtual Power getAttenuationResidual(void) override;


    /*! \brief  Set the attenuator attenuation level
     *
     *  Set the attenuator attenuation level.
     *
     *  \param  attenLevel  the required attenuation level
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual ReturnType::State setAttenuation(Power attenLevel) override ;

    /*! \brief  Set the attenuator attenuation level
     *
     *  Set the attenuator attenuation level.
     *
     *  \param  attenLevel  the required attenuation level
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual ReturnType::State setAttenuation(Power attenLevel, Temperature temperature) override;

    /**
     * Call this method so set the attenuator to the maximum attenuation it supports.
     * @return
     */
    virtual ReturnType::State setMaxAttenuation() override ;

    /*! \brief  Get the attenuator maximum attenuation level
     *
     *  Get the attenuator max attenuation level
     *
     *  \return the max attenuation level
     */
    virtual Power getMaxAttenuation(void) override ;

    /*! \brief  get the attenuator minimum attenuation level
     *
     *  Get the attenuator minimum.
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual Power getMinAttenuation(void) override ;

    /**
     * Convert a requested attenuation value into a control register value
     * @param attenuation Requested attenuation
     * @return control value
     */
    virtual unsigned int calcControl(Power attenuation) override ;

    /**
     * Convert a requested attenuation value into a control register value
     * @param attenuation Requested attenuation
     * @param temperature Current temperature
     * @return control value
     */
    virtual unsigned int calcControl(Power attenuation, Temperature temperature) override ;

    /**
     * Convert the control register value into an attenuation
     * @param control
     * @return attenuation
     */
    virtual Power calcAttenuation(unsigned int control) override ;



protected:
    /**
     * Given an attenuation value, return the value adjusted to fit within the min/max attenuation limits
     * @param attenuation
     * @return attenuation adjusted within the min/max limits
     */
    virtual Power limitAttenuation(const Power& attenuation) const override ;

    /**
     * Is the provided attenuation within limits?
     * @param attenuation
     * @return true if inside limits; false otherwise
     */
    virtual bool isValidAttenuation(const Power& attenuation) const override ;


protected:

    std::shared_ptr<IAttenuatorDriver> mDriver;             //!> Pointer to the driver instance                                 //!> The attenuator Id for this instance
    Power   	mAttenuation;
    Power   	mAttenuationResidual;
    unsigned	mAttenControl ;
} ;

}

#endif /* ATTNBASE_H_ */
