#ifndef _RADIO_HARDWARE_COMMONATTEN_H_
#define _RADIO_HARDWARE_COMMONATTEN_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAttenuator.h
 * \brief     A file to contain the common implementation of a generic Attenuator.
 *
 *
 * \details   This file defines the common implementation of a generic Attenuator
 *            and expands on it if necessary.
 *
 */

#include "AttnBase.h"
#include <string>

namespace Mplane
{

class CommonAttenuator: public AttnBase
{

public:
    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the Attenuator
     *  \param name   name string for the Attenuator
     *  \param attenId the Id given to the Attenuator
     */
    CommonAttenuator( std::shared_ptr<IAttenuatorDriver> driver, int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonAttenuator();

};

} /* namespace Mplane */

#endif /* _RADIO_HARDWARE_COMMONATTEN_H_ */
