#ifndef _VRH_IFEM_H_
#define _VRH_IFEM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFem.h
 * \brief     A file to contain a generic interface to a Fem module.
 *
 *
 * \details   This file defines a generic interface to a Fem module.
 *
 */

#include "GlobalTypeDefs.h"
#include "Module.h"
#include <stdexcept>

namespace Mplane
{

// Forward declare IFem sub classes

/*! \brief  Generic Fem module interface
 *
 * A virtual interface base class defining an interface to a Fem module.
 * The Fem module contains hardware for controlling Tx and Rx powers on one or
 * more antenna ports.
 *
 * The generic Fem interface provides methods to access the controlling
 * aspects of the Fem and to retrieve the measurements.
 */
class IFem : public Module
{
public:

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible.
     *
     * \return true if successful, false otherwise
     */
    virtual bool shutdown(void) = 0;

    /**
     * Pure virtual method used to return the number of Tx/Rx antenna ports
     * supported by the Fem.
     *
     * \return the number of Tx/Rx antenna ports supported
     */
    virtual UINT32 getNumAntennaPorts() = 0;

    virtual ~IFem() { };

protected:

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    IFem( int index, int number, const char* name ):
        Module( Module::FEM, index, number, name ) { };


};


} /* namespace Mplane */

#endif /* _VRH_IFEM_H_ */
