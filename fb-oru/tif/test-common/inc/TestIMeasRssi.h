/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIMeasRssi.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTIMEASRSSI_H_
#define TESTIMEASRSSI_H_

#include "IMeasRssi.h"

namespace Mplane {

class TestIMeasRssi : public virtual IMeasRssi {
public:
	TestIMeasRssi() ;
	virtual ~TestIMeasRssi() ;

    /**
     * Read the wideband RSSI value for this path
     * @return RSSI in dBm
     */
    virtual Power getRssi() override ;
} ;

}

#endif /* TESTIMEASRSSI_H_ */
