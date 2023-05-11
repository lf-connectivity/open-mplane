#ifndef _VHI_IMDIO_H_
#define _VHI_IMDIO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMdio.h
 * \brief     A file to define generic interface to an IMdio Management Data Input/Output (Ethernet) device
 *
 *
 * \details   A file to define generic interface to an IMdio Management Data Input/Output (Ethernet) device
 *
 */

#include <vector>
#include <stdexcept>
#include <memory>

#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic IMdio interface
 *
 *  A virtual interface base class defining an interface to a IMdio bus.
 *  The interface contains configuration and control aspects.
 */
class IMdio : public virtual IDevice
{
public:

    /*! \brief Destructor
     */
    virtual ~IMdio() { };

    /*! \brief  The initialise method
     *
     *  Method called during system startup, to fully
     *  initialise the device and to override any initial settings with
     *  board-specific ones.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise( void ) = 0;

    /*! \brief Get an instance of the Reference interface
     *
     * \return return a reference to the interface
     */
    static std::shared_ptr<IMdio> getInterface( int deviceIndex );

protected:
    IMdio() {};

};

} /* namespace Mplane */

#endif /* _VHI_IMDIO_H_ */
