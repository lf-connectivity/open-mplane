#ifndef _HARDWARE_COMMON_RFMODULE_H_
#define _HARDWARE_COMMON_RFMODULE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRfModule.h
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
#include "IRfModule.h"

namespace Mplane
{

/*! \brief  Generic RF module interface
 *
 *  A virtual interface base class defining an interface to RF module.
 *  The interface contains control aspects.
 */
class CommonRfModule : public IRfModule
{
public:

    /*! \brief Constructor
     *
     */
	CommonRfModule() { };

	/**
	 * Activate/deactivate Switch on RF module
	 */
    virtual bool setSwitch(unsigned sw, bool enable) override;

	/**
	 * Read switch on RF module
	 */
    virtual bool getSwitch(unsigned sw) override;

    /*! \brief Destructor
     *
     */
    virtual ~CommonRfModule() { };
};

} /* namespace Mplane */

#endif /* _HARDWARE_COMMON_RFMODULE_H_ */
