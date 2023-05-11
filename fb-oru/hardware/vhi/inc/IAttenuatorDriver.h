#ifndef _VRH_IATTENUATORDRIVER_H_
#define _VRH_IATTENUATORDRIVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAttenuatorDriver.h
 * \brief     A file to define generic interface to a Attenuator driver
 *
 *
 * \details   This file defines a generic interface to a Attenuator driver
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Power.h"
#include "Temperature.h"

namespace Mplane
{

/*! \brief  Generic Attenuator driver interface
 *
 *  A virtual interface base class defining an interface to an attenuator.
 *  The interface contains configuration and control aspects.
 */
class IAttenuatorDriver
{
public:

    /*! \brief  Destructor
     *
     *  Should never be called.
     */
    virtual ~IAttenuatorDriver() { };

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) = 0;

    /*! \brief  Dump the attenuator status
     *
     *  Dump the state of the attenuator driver to the log file
     */
    virtual void show ( std::ostream& os ) = 0;

    /*! \brief  Dump the attenuator status
     *
     *  Dump the state of the attenuator driver to the console
     */
    virtual void show ( void ) = 0;

    /*! \brief  Get the attenuator maximum attenuation level
     *
     *  Get the attenuator max attenuation level
     *
     *  \return the max attenuation level
     */
    virtual Power getMaxAttenuation(void) = 0 ;

    /*! \brief  get the attenuator minimum attenuation level
     *
     *  Get the attenuator minimum.
     *
     *  \return true if the attenuation has been successfully set
     */
    virtual Power getMinAttenuation(void) = 0 ;

    /*! \brief  Apply the attenuation level
     *
     *  Write the attenuation control value to the attenuator.
     *
     *  \param  attenLevel  the attenuation control value
     *
     *  \return true if the attenuation has been successfully applied
     */
    virtual ReturnType::State applyAttenuation(unsigned int control) = 0;

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
    virtual unsigned calcControl(Power attenuation, Temperature temperature) =0 ;

    /**
     * Convert the control register value into an attenuation
     * @param control
     * @return attenuation
     */
    virtual Power calcAttenuation(unsigned int control) =0 ;

protected:
    IAttenuatorDriver() {};
};


} /* namespace Mplane */

#endif /* _VRH_IATTENUATORDRIVER_H_ */
