#ifndef _VRH_ISYNTH_H_
#define _VRH_ISYNTH_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISynth.h
 * \brief     A file to define generic interface to a radio Synthesiser device
 *
 *
 * \details   This file defines a generic interface to a radio Synthesiser device
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "FrequencyOffset.h"
#include "IDevice.h"

// forward declarations go here, before the namespace

namespace Mplane
{

/*! \brief  Generic Synthesiser interface
 *
 *  A generic virtual interface base class defining an interface to a
 *  radio synthesiser.
 *  The interface contains configuration and control aspects.
 *
 *  This class represents a virtual interface used to setup the synthesiser
 *  on a radio. It is designed to be implemented as a polymorphic base class
 *  for all synthesiser device programming classes.
 *
 *  The actual implementation of this interface, will be aware of the type
 *  of synthesiser in use and the synthesiser data that will define its frequency
 *  range, raster, prescale etc..
 *
 *  This generic synthesiser interface is used in the ISynths interface,
 *  to provide a generic method of setting up and programming all the radios
 *  synthesiser devices.
 *
 */
class ISynth: public virtual IDevice
{
public:
    ISynth() {};
    virtual ~ISynth() {};


    /*! \brief  Set the synthesiser frequency
     *
     *  Set the frequency in kHz that the synthesiser is set to.
     *
     *  \param the synthesiser frequency
     */
    virtual void setFrequency(Frequency frequency ) =0;

    /*! \brief  Program the synthesiser
     *
     *  Method to program the synthesiser, either to its fixed default frequency,
     *  or the frequency specified.
     *
     *  \return state of RT_OK if synthesiser is locked OK, RT_other if not.
     */
    virtual ReturnType::State program() =0;

    /*! \brief  Post Program steps if any
     *
     *  Called after ISynth::program to perform any steps after frequency is changed
     *
     *  \return None
     */
    virtual void postProgram() =0;

    /*! \brief  Get the carrier frequency
     *
     *  Return the frequency in kHz that the carrier has requested synthesiser be set to.
     *
     *  \return the carrier frequency, in kHz
     */
    virtual Frequency getFrequency() =0;

    /*! \brief  Get the synthesiser frequency
     *
     *  Return the frequency in kHz that the synthesiser has been set to.
     *  In some schemes this may be different to carrier frequency.
     *	e.g. avoiding a bad IBS frequency by shifting LO and compensating with NCOs
     *
     *  \return the synthesiser frequency, in kHz
     */
    virtual Frequency getSynthFrequency() =0;

	/**
	 * Check if the frequency is a bad IBS frequency
	 *
	 * @return true if it is a bad IBS frequency
	 */
    virtual bool isBadIbsFreq( Frequency frequency ) =0;

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) =0;

    /*! \brief  Determine whether the synthesiser is locked
     *
     *  Method used to check if the synthesiser is out of lock.
     *
     *  \return true if the synthesiser is out of lock.
     */
    virtual bool isOutOfLock(void) =0;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) =0;

    /*! \brief  Check if this frequency requires a special offset
     *
     *  Used for cases where a frequency may have something like an IBS issue requiring a different LO offset
     */
    virtual FrequencyOffset checkFrequency( int port, Frequency frequency ) =0;

    /*! \brief  Dump the Synth status
     *
     *  Dump the state of the synthesiser to the console or log file
     */
    virtual void show(std::ostream& os) =0;
    virtual void show(void) =0;


};

} /* namespace Mplane */

#endif /* _VRH_ISYNTH_H_ */
