#ifndef _VRS_TESTIFIBRECONTROL_H_
#define _VRS_TESTIFIBRECONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIFibreControlControl.h
 * \brief     A file to contain a stub interface to a FIBRE control interface.
 *
 *
 * \details   This file defines a stub interface to a FIBRE control interface.
 *
 */

#include "IFibreControl.h"

namespace Mplane
{

/*! \brief  Stub of the FIBRE control Interface
 *
 * This class provides an implementation of the IFibreControl interface, for use
 * by unit tests.
 * Users/coders of the unit tests that use an IFibreControl interface must ensure
 * that they code the TestIFibreControl implementation that meets their unit test
 * cases.
 */
class TestIFibreControl: public IFibreControl
{
public:

    TestIFibreControl();

    virtual ~TestIFibreControl() { }

    /**
     * This method is to show the fibre control status.
     */
    virtual void showFibreControl();

    /**
     * This method is the entry point to the fibre controlling application.
     * It will start the radio specific Fibre controlling task and initialise the fibre
     * hardware.
     *
     * After a successful start up process, it will implement fibre control operations,\n
     * eg. monitoring for alarms, responding to OAM requests.
     */
    virtual void startFibreControl();

    /**
     * Method that is called periodically, eg. 1 second, to perform fibre controlling functions.
     */
    virtual void serviceFibreControl();

    /**
     * This method will reset the fibre control
     */
    virtual void resetFibreControl();

};


} /* namespace Mplane */

#endif // _VRS_TESTIFIBRECONTROL_H_
