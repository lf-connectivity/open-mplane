#ifndef _VHI_IRFATTEN_CHANGE__H_
#define _VHI_IRFATTEN_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRfAttenChange.h
 * \brief     A file to define generic interface to a change in RF attenuation implementation
 *
 *
 * \details   A file to define generic interface to a change in RF attenuation implementation
 *
 */

#include "Power.h"

namespace Mplane
{

/*! \brief  Generic RF attenuation change interface
 *
 *  A virtual interface base class defining an interface to a RF attenuation changing implementation
 */
class IRfAttenChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~IRfAttenChange() { };

    /*! \brief Pure virtual method to get the Rf attenuation
     *
     * \return The cal mode
     */
    virtual Power getRfAttenuation( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_IRFATTEN_CHANGE__H_ */
