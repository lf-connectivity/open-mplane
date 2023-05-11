/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRtcIEEE1588.h
 * \brief     Virtual interface to IEEE 1588 RTC module
 *
 *
 * \details   Virtual interface to IEEE 1588 RTC module
 *
 */


#ifndef VHI_INC_IRTCIEEE1588_H_
#define VHI_INC_IRTCIEEE1588_H_

#include <cstdint>
#include <memory>
#include <string>
#include "IHighSpeedEthernet.h"

namespace Mplane {

/*!
 * \class  IRtcIEEE1588
 * \brief
 * \details
 *
 */
class IRtcIEEE1588 {
public:
	IRtcIEEE1588() {}
	virtual ~IRtcIEEE1588() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IRtcIEEE1588> singleton() ;

	/**
	 * get the Ethernet core's speed into the RTC module
	 */
	virtual void setSpeed(IHighSpeedEthernet::EthernetSpeed speed) =0 ;

	/**
	 * Read any register offset
	 */
	virtual uint32_t read(uint32_t address) const =0 ;

} ;

}

#endif /* VHI_INC_IRTCIEEE1588_H_ */
