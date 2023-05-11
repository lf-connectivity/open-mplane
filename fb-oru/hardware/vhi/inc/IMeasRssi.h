/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IMeasRssi.h
 * \brief     Virtual interface for measuring wideband RSSI
 *
 *
 * \details
 *
 */


#ifndef IMEASRSSI_H_
#define IMEASRSSI_H_

#include <stdexcept>
#include <memory>
#include "Power.h"

namespace Mplane {

class IMeasRssi {
public:
	IMeasRssi() {}
	virtual ~IMeasRssi() {}

    /**
     * A static factory interface used to return a shared pointer
     * @param path
     * @return
     */
    static std::shared_ptr<IMeasRssi> getInterface( unsigned path ) ; /* throw ( std::invalid_argument); */

    /**
     * Read the wideband RSSI value for this path
     * @return RSSI in dBm
     */
    virtual Power getRssi() =0 ;

} ;

}

#endif /* IMEASRSSI_H_ */
