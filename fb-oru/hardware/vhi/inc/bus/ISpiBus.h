/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISpiBus.h
 * \brief     Generic SPI bus (implementing the IBus virtual interface)
 *
 *
 * \details   Generic SPI bus (implementing the IBus virtual interface)
 *
 */


#ifndef VHI_INC_BUS_ISPIBUS_H_
#define VHI_INC_BUS_ISPIBUS_H_

#include "IBus.h"

namespace Mplane {

/*!
 * \class  ISpiBus
 * \brief
 * \details
 *
 */
class ISpiBus : public virtual IBus {
public:
	ISpiBus() {}
	virtual ~ISpiBus() {}

	/**
	 * Allow the device using this bus to tell the SPI bus what it's device settings are
	 *
	 * Most SPI devices use a shift register of some size, with address bits using a portion of the shift register and data using the rest
	 *
	 * The shift register is treated as MS bit first, the MS bit being the size of the shift reg -1. Address bit locations are then the bit
	 * locations within the shift reg
	 *
	 * E.G. for a 32 bit shift register, the MS bit of the shift reg is bit 31. If address bits are 4 .. 0 then the shift register would be:
	 *
	 * MS 31       5  4 3 2 1 0
	 *    D27 .... D0 A4      A0
	 *
	 */
	virtual void setDeviceSettings(unsigned srRegisterWidth, unsigned addrMS, unsigned addrLS, bool useReadWriteBit, unsigned readWriteBit) =0 ;

} ;

}

#endif /* VHI_INC_BUS_ISPIBUS_H_ */
