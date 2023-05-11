/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISerialDataReceived.h
 * \brief     A file to define generic interface to notify about new serial data
 *
 *
 * \details   A file to define generic interface to notify about new serial data
 *
 */

#ifndef _VHI_ISERIALDATARECEIVED__H_
#define _VHI_ISERIALDATARECEIVED__H_

#include "SerialData.h"

namespace Mplane
{

/*! \brief  Generic Serial data received interface
 *
 *  A virtual interface base class defining an interface to notify about new serial data
 */
class ISerialDataReceived
{
public:

    /*! \brief Destructor
     *
     */
    virtual ~ISerialDataReceived() { };

    /*! \brief Pure virtual method to get the serial data mode
     *
     * \return The serial data object
     */
    virtual SerialData getSerialData( void ) = 0;
};

} /* namespace Mplane */

#endif /* _VHI_ISERIALDATARECEIVED__H_ */
