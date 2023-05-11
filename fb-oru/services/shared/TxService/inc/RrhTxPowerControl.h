/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhTxPowerControl.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef RRHTXPOWERCONTROL_H_
#define RRHTXPOWERCONTROL_H_

#include "TxPowerControl.h"

namespace Mplane {

/*!
 * \class RrhTxPowerControl
 */
class RrhTxPowerControl : public TxPowerControl {
public:
    explicit RrhTxPowerControl( int portIndex );
	virtual ~RrhTxPowerControl() ;

} ;

}

#endif /* RRHTXPOWERCONTROL_H_ */
