#ifndef _RADIO_HARDWARE_COMMONFEM_H_
#define _RADIO_HARDWARE_COMMONFEM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFem.h
 * \brief     A file to contain the common implementation of a generic Fem.
 *
 *
 * \details   This file defines the common implementation of a generic Fem
 *            and expands on it if necessary.
 *
 */

#include "IFem.h"
#include <string>

namespace Mplane
{

class CommonFem: public IFem
{

public:

    static const UINT32 numAntennaPorts = 1;

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonFem class does not provide any Fem-type
     *  specific initialisation. That is left to the inheritors who know what
     *  Fem module is being used.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "Fem INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible.
     *
     * \return true if successful, false otherwise
     */
    virtual bool shutdown(void);

    /**
     * Pure virtual method used to return the number of Tx/Rx antenna ports
     * supported by the Fem.
     *
     * \return the number of Tx/Rx antenna ports supported
     */
    virtual UINT32 getNumAntennaPorts();

    /*! \brief  Dump the Fem status
     *
     *  Dump the state of the Fem to the console or log file
     */
    virtual void show(void);

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the Fem
     *  \param number one-based Fem number
     *  \param name   name string for the Fem
     */
    CommonFem(int index, int number, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonFem();


private:

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONFEM_H_ */
