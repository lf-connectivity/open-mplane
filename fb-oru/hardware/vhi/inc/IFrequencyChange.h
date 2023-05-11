#ifndef _VHI_IFREQUENCY_CHANGE__H_
#define _VHI_IFREQUENCY_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFrequencyChange.h
 * \brief     A file to define generic interface to a Frequency changing implementation
 *
 *
 * \details   A file to define generic interface to a Frequency changing implementation
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include "Frequency.h"

namespace Mplane
{

/*! \brief  Generic Frequency Change interface
 *
 *  A virtual interface base class defining an interface to a Frequency changing implementation
 */
class IFrequencyChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~IFrequencyChange() { };

    /*! \brief Pure virtual method to get the frequency
     *
     * \return The Frequency
     */
    virtual const Frequency getFrequency( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_IFREQUENCY_CHANGE__H_ */
