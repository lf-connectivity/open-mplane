#ifndef _RADIO_HARDWARE_COMMONSYNTH_H_
#define _RADIO_HARDWARE_COMMONSYNTH_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSynth.h
 * \brief     A file to contain the common implementation of a generic Synthesiser.
 *
 *
 * \details   This file defines the common implementation of a generic Synthesiser
 *            and expands on it if necessary.
 *
 */

// Includes go here, before the namespace
#include <string>
#include <memory>

#include "ISynth.h"
#include "Initialise.h"
#include "Device.h"
#include "ISynthDriver.h"

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
 *  This generic synthesiser interface is used in the ISynths interface, to provide
 *  a generic method of setting up and programming all the radios synthesiser devices.
 *
 */
class CommonSynth:  public virtual ISynth, public Device
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class CommonSynthTestCase;
    friend class CommonSynthsTestCase;

public:


    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /*! \brief  Program the synthesiser
     *
     *  Method to program the synthesiser, either to its fixed default frequency,
     *  or the frequency specified.
     *
     *  \return state of RT_OK if synthesiser is locked OK, RT_other if not.
     */
    virtual ReturnType::State program();

    /*! \brief  Post Program steps if any
     *
     *  Called after ISynth::program to perform any steps after frequency is changed
     *
     *  \return None
     */
    virtual void postProgram();

    /*! \brief  Set the synthesiser frequency
     *
     *  Set the frequency that the synthesiser is set to.
     *
     *  \param the synthesiser frequency
     */
    virtual void setFrequency(Frequency frequency);

    /*! \brief  Get the carrier frequency
     *
     *  Return the frequency in kHz that the carrier has requested synthesiser be set to.
     *
     *  \return the carrier frequency, in kHz
     */
    virtual Frequency getFrequency();

    /*! \brief  Get the synthesiser frequency
     *
     *  Return the frequency in kHz that the synthesiser has been set to.
     *  In some schemes this may be different to carrier frequency.
     *	e.g. avoiding a bad IBS frequency by shifting LO and compensating with NCOs
     *
     *  \return the synthesiser frequency, in kHz
     */
    virtual Frequency getSynthFrequency();

	/**
	 * Check if the frequency is a bad IBS frequency
	 *
	 * @return true if it is a bad IBS frequency
	 */
    virtual bool isBadIbsFreq( Frequency frequency ) override;

    /*! \brief  Determine whether the PLL is locked
     *
     *  Method used to check if the PLL is locked.
     *
     *  \return true if the PLL is locked
     */
    virtual bool isPllLocked(void) override;

    /*! \brief  Determine whether the synthesiser is locked
     *
     *  Method used to check if the synthesiser is out of lock.
     *
     *  \return true if the synthesiser is out of lock.
     */
    virtual bool isOutOfLock(void) override;

    /*! \brief  Force the synthesiser out of lock
     *
     *  Used for synthesiser testing by forcing the synth to go out lock.
     */
    virtual void forceOutOfLock(void) override;

    /*! \brief  Check if this frequency requires a special offset
     *
     *  Used for cases where a frequency may have something like an IBS issue requiring a different LO offset
     */
    virtual FrequencyOffset checkFrequency( int port, Frequency frequency );

    /*! \brief  Dump the Synth status
     *
     *  Dump the state of the synthesiser to the console or log file
     */
    virtual void show(std::ostream& os);
    virtual void show(void);


    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the synth
     *  \param name   name string for the synth
     *  \param frequency the frequency for the synthesiser to be set to
     */
    CommonSynth( std::shared_ptr<ISynthDriver> driver, int index, const std::string& name, Frequency frequency);

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~CommonSynth();


private:

    /*!
     * Used to store the set frequency
     */
    Frequency mFrequency;

    /*!
     * The synthesiser driver that gives access to the hardware
     */
    std::shared_ptr<ISynthDriver> mDriver;

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONSYNTH_H_ */
