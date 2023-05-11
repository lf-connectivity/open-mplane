#ifndef _VRH_IRFMODULE_H_
#define _VRH_IRFMODULE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRfModule.h
 * \brief     A file to define generic interface to RF module
 *
 *
 * \details   A file to define generic interface to RF module
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Mplane
{

/*! \brief  Generic RF module interface
 *
 *  A virtual interface base class defining an interface to RF module.
 *  The interface contains control aspects.
 */
class IRfModule
{
public:

    /*! \brief Constructor
     *
     */
	IRfModule() { };

    /**
     * Singleton
     */
    static std::shared_ptr<IRfModule> getInterface();

	/**
	 * Activate/deactivate Switch on RF module
	 */
    virtual bool setSwitch(unsigned sw, bool enable) =0 ;

	/**
	 * Read switch on RF module
	 */
    virtual bool getSwitch(unsigned sw) =0 ;

    /*! \brief Destructor
     *
     */
    virtual ~IRfModule() { };
};

} /* namespace Mplane */

#endif /* _VRH_IRFMODULE_H_ */
