#ifndef _IPORT_H_
#define _IPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string>

namespace Mplane
{

/**
 * This pure virtual base class defines access to the basic functionality that
 * is defined for any port types and is therefore inherited by other port
 * types.
 */
class IPort
{
public:
    /**
     * Get the zero based index that can be used to reference the port from
     * a list of ports.
     * @return zero base index of the port
     */
    virtual int getIndex() const =0;

    /**
     * A string name associated with the port type used in logging and debugging.
     * @return port name
     */
    virtual std::string getName() const =0;

    /**
     * Virtual destructor
     */
    virtual ~IPort(){};
};


}



#endif /* _IPORT_H_ */
