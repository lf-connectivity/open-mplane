#ifndef _VRH_IMODULES_H_
#define _VRH_IMODULES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IModules.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "GlobalTypeDefs.h"
#include <stdexcept>
#include <memory>

namespace Mplane
{

// Forward declare IModules sub classes
class IFilter;
class IFem;

class IModules
{
public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     *
     * \return true if successful
     */
    virtual bool shutdown(void) = 0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Filter module virtual interface. The index must be between zero
     * and the number of modules supported by the hardware.
     *
     * \param index zero-based index from 0 to maximum filter modules,
     *
     * \return a reference to the filter module for the given index.
     *
     * \throws invalid_argument exception if the index is invalid, or the module is not supported.
     */
    virtual IFilter& getFilter( int index ) =0 ; /* throw (std::invalid_argument) */

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
    virtual IFem& getFem( int index ) =0 ; /* throw (std::invalid_argument) */

    /**
     * Method used to show the status of all the modules in the module list.
     */
    virtual void show() = 0;


    virtual ~IModules() { };

};

/**
 * Defines a factory class that is called by the common radio during initialisation
 * to create all the physical modules fitted to the radio and initialise them.
 */
class IModulesFactory
{
public:

    /**
     * Factory method created by a radio specific implementation
     *
     * \return a reference to the radio modules interface.
     */
    static std::shared_ptr<IModules> create();
};


} /* namespace Mplane */

#endif /* _VRH_IMODULES_H_ */
