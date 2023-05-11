#ifndef _COMMON_MODULE_H_
#define _COMMON_MODULE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Module.h
 * \brief     A file to define generic interface to all radio physical modules
 *
 *
 * \details   A file to define generic interface to all radio physical modules
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <vector>
#include <string>
#include "Initialise.h"

namespace Mplane
{

/*! \brief  Generic Module interface
 *
 *  A virtual interface base class defining an interface
 *  that must be implemented by all physical radio modules
 *  such as Filters, FEMs and Clock References.
 *
 *  The interface allows all actual modules to be held in a
 *  module list that is used during start up to
 *  ensure all modules are initialised to their correct state.
 *
 *  All IModules must support the Initialise interface
 *
 */
class Module: public Initialise
{
public:

    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class ModuleTestCase;


    enum Type
    {
        FILTER,
        FEM
    };

    /**
     * This method is implemented by the actual module implementation
     * to indicate its type.
     *
     * @return enumerated module type.
     */
    Module::Type getType();

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    ReturnType::State initialise();

    /*! \brief Get the module index
     *
     * Get the zero based index that can be used to reference the module from
     * a list of radio modules.
     *
     * \return zero-based index of the module
     */
    int getIndex();

    /*! \brief Get the module number
     *
     * A one-based number that usually refers to a logical path or port
     * to which the module is associated.
     *
     * If a value of zero is returned this indicates that the module
     * is a single module that may be associated with multiple ports
     * or indeed none at all.
     *
     * \return one-based module number
     */
    int getNumber();

    /*! \brief Get the module name string
     *
     * A string name associated with the module used in logging and debugging.
     *
     * \return Module name string
     */
    const char* getName();

    /*! \brief  Display the module data and information related to its general
     * status.
     *
     *  Display the state of the module on the console or log file
     */
    virtual void show(void) = 0;

    /*! \brief Destructor
     *
     */
    virtual ~Module();


protected:

    Module(Module::Type type, int index, int number, const char* name);


private:

    /*!
     * the sub class module type.
     */
    Module::Type mType;

    /*!
     * zero-based index of the module, set by constructor
     */
    int mIndex;

    /*!
     * one-based module number, set by constructor
     */
    int mNumber;

    /*!
     * name string for the module, set by constructor
     */
    std::string mName;

};


} /* namespace Mplane */

#endif /* _COMMON_MODULE_H_ */
