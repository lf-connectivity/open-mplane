#ifndef _VHI_ITEMPERATURE_CHANGE__H_
#define _VHI_ITEMPERATURE_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITemperatureChange.h
 * \brief     A file to define generic interface to a Temperature changing implementation
 *
 *
 * \details   A file to define generic interface to a Temperature changing implementation
 *
 */

#include "Temperature.h"

namespace Mplane
{

/*! \brief  Generic Temperature Change interface
 *
 *  A virtual interface base class defining an interface to a Temperature changing implementation
 */
class ITemperatureChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~ITemperatureChange() { };

    /*! \brief Pure virtual method to get the temperature
     *
     * \return The Temperature
     */
    virtual const Temperature getTemperature( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_ITEMPERATURE_CHANGE__H_ */
