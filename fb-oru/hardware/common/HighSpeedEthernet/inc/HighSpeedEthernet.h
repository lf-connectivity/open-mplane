/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HighSpeedEthernet.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef HIGHSPEEDETHERNET_INC_HIGHSPEEDETHERNET_H_
#define HIGHSPEEDETHERNET_INC_HIGHSPEEDETHERNET_H_

#include "IHighSpeedEthernet.h"

namespace Mplane {

/*!
 * \class  HighSpeedEthernet
 * \brief
 * \details
 *
 */
class HighSpeedEthernet : public virtual IHighSpeedEthernet {
public:
	HighSpeedEthernet() ;
	virtual ~HighSpeedEthernet() ;

	/**
	 * get the core's current speed
	 */
	virtual IHighSpeedEthernet::EthernetSpeed speed() const override ;

	/**
	 * Simplify the speed to 10G or 25G
	 */
	virtual bool is25G() const override ;

	/**
	 * Read any register offset
	 */
	virtual uint32_t read(uint32_t address) const override ;


} ;

}

#endif /* HIGHSPEEDETHERNET_INC_HIGHSPEEDETHERNET_H_ */
