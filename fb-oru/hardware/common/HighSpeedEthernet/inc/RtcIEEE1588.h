/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RtcIEEE1588.h
 * \brief     Virtual interface to IEEE 1588 RTC module
 *
 *
 * \details   Virtual interface to IEEE 1588 RTC module
 *
 */


#ifndef HIGHSPEEDETHERNET_INC_IRTCIEEE1588_H_
#define HIGHSPEEDETHERNET_INC_IRTCIEEE1588_H_

#include "IRtcIEEE1588.h"

namespace Mplane {

/*!
 * \class  RtcIEEE1588
 * \brief
 * \details
 *
 */
class RtcIEEE1588 : public virtual IRtcIEEE1588 {
public:
	RtcIEEE1588();
	virtual ~RtcIEEE1588();

	/**
	 * get the Ethernet core's speed into the RTC module
	 */
	virtual void setSpeed(IHighSpeedEthernet::EthernetSpeed speed) override ;

	/**
	 * Read any register offset
	 */
	virtual uint32_t read(uint32_t address) const override ;

} ;

}

#endif /* HIGHSPEEDETHERNET_INC_IRTCIEEE1588_H_ */
