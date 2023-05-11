#ifndef _VHI_IRXAGCMODE_CHANGE__H_
#define _VHI_IRXAGCMODE_CHANGE__H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxAgcModeChange.h
 * \brief     A file to define generic interface to a change in Rx AGC mode
 *
 *
 * \details   A file to define generic interface to a change in Rx AGC mode
 *
 */

#include "IRxAgc.h"

namespace Mplane
{

class IRxAgc;

/*! \brief  Generic Rx AGC mode interface
 *
 *  A virtual interface base class defining an interface to a Rx AGC mode changing implementation
 */
class IRxAgcModeChange
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~IRxAgcModeChange() { };

    /*! \brief Pure virtual method to get the agc mode
     *
     * \return The agc mode
     */
    virtual IRxAgc::RxAgcMode getRxAttenMode( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_IRXAGCMODE_CHANGE__H_ */
