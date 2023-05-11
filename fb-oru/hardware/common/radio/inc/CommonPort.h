#ifndef _MPLANE_COMMONPORT_H_
#define _MPLANE_COMMONPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string>
#include <functional>

#include "IPort.h"

#include "GlobalTypeDefs.h"

namespace Mplane
{

class CommonPort: public virtual IPort
{

public:
    /**
     * Get the zero based index that can be used to reference the port from
     * a list of ports.
     * @return zero base index of the port
     */
    virtual int getIndex() const;

    /**
     * A string name associated with the port type used in logging and debugging.
     * @return port name
     */
    virtual std::string getName() const;


    CommonPort( int index, const char* name);

    /**
     * Virtual destructor
     */
    virtual ~CommonPort();

protected:
    // Shared utilities

    using SynthLockFunc = std::function<bool()> ;
    int mIndex;

    /**
     * Uses the provided lockFunc to wait until the synthesiser is locked. If it does not lock after timeMs milliseconds
     * then the method times out and returns an error
     * @param timeMs
     * @param lockFunc
     * @return RT_OK if locked
     */
    ReturnType::State waitSynthLocked(unsigned timeMs, SynthLockFunc lockFunc) ;

private:
    std::string mName;
};

}

#endif /* _MPLANE_COMMONPORT_H_ */
