#ifndef _VRH_IFPGADEV_H_
#define _VRH_IFPGADEV_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaDev.h
 * \brief     A file to define generic interface to an FPGA device
 *
 *
 * \details   This file defines a generic interface to an FPGA device
 *
 */

#include "IDevice.h"

namespace Mplane
{

/*! \brief  Generic FPGA interface
 *
 *  A virtual interface base class defining an interface to an FPGA.
 *  The interface contains configuration and control aspects.
 */
class IFpgaDev: public virtual IDevice
{
public:


protected:

    IFpgaDev() {}

    /*! \brief Destructor
     *
     *  Ensure we can only be destructed via an implementing class
     *
     */
    virtual ~IFpgaDev() { };

};

} /* namespace Mplane */

#endif /* _VRH_IFPGADEV_H_ */
