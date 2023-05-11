#ifndef _COMMONMODULES_H_
#define _COMMONMODULES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonModules.h
 * \brief     A file to define the common implementation of the IModules class.
 *
 *
 * \details   This file defines the common implementation of the IModules class.
 *
 */

#include "IModules.h"

namespace Mplane
{


class CommonModules: public IModules
{
public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise();

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     *
     * \return true if successful
     */
    virtual bool shutdown(void);

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Filter module virtual interface. The port index must be between zero
     * and the number of modules supported by the hardware.
     *
     * \param index zero-based index from 0 to maximum filter modules,
     *
     * \return a reference to the filter module for the given index.
     *
     * \throws invalid_argument exception if the index is invalid, or the module is not supported.
     */
    virtual IFilter& getFilter( int index ) ; /* throw (std::invalid_argument);*/

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a FEM (Front End Module) module virtual interface. The index must be
     * between zero and the number of modules supported by the hardware.
     *
     * \param index zero-based index from 0 to maximum FEM modules,
     *
     * \return a reference to the filter module for the given index.
     *
     * \throws invalid_argument exception if the index is invalid, or the module is not supported.
     */
    virtual IFem& getFem( int index ) ; /*throw (std::invalid_argument);*/

    /**
     * Method used to show the status of all the modules in the module list.
     */
    virtual void show();

    /**
     * Protected constructor is intended to be sub classes
     */
    CommonModules();

    /**
     * Virtual destructor, should never be called.
     */
    virtual ~CommonModules();

};

} /* namespace Mplane */

#endif /* _COMMONMODULES_H_ */
