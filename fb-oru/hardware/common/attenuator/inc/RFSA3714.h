/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RFSA3714.h
 * \brief     Class representing the RFSA3714 attenuator device
 *
 *
 * \details
 *
 */


#ifndef ATTNRFSA3714_H_
#define ATTNRFSA3714_H_

#include <memory>

#include "bus/ISpiBus.h"
#include "IAttenuatorDriver.h"
#include "RegDriver.h"
#include "RegModel.h"

namespace Mplane {

class RFSA3714 : public virtual IAttenuatorDriver, public RegDriver
{
public:

	RFSA3714(std::shared_ptr<ISpiBus> spi, const std::string& name,
			const Power& minAtten = Power(0.0),
			const Power& maxAtten = Power(31.75));

	virtual ~RFSA3714() ;

	/**
	 * Initialise the driver
	 */
	virtual ReturnType::State initialise( void ) override;

    /*! \brief  Dump the attenuator status
     *
     *  Dump the state of the attenuator driver to the log file
     */
    virtual void show ( std::ostream& os ) override;

    /*! \brief  Dump the attenuator status
     *
     *  Dump the state of the attenuator driver to the console
     */
    virtual void show ( void ) override;

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

    /*! \brief  Apply the attenuation level
     *
     *  Write the attenuation control value to the attenuator.
     *
     *  \param  attenLevel  the attenuation control value
     *
     *  \return true if the attenuation has been successfully applied
     */
    virtual ReturnType::State applyAttenuation(unsigned int control) override;

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

private:

    std::shared_ptr<ISpiBus> mSpi;                    //!> Bus interface to communicate to the attenuator
    Power   	mMinAttenuation;                      //!> Min attenuation
    Power   	mMaxAttenuation;                      //!> Max attenuation
} ;

}

#endif /* ATTNRFSA3714_H_ */
