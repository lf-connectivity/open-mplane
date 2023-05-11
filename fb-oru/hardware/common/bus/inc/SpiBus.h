/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBus.h
 * \brief     Generic SPI bus definition
 *
 *
 * \details   Generic SPI bus definition
 *
 */


#ifndef COMMON_BUS_INC_SPIBUS_H_
#define COMMON_BUS_INC_SPIBUS_H_

#include "ISpiBus.h"
#include "Bus.h"

namespace Mplane {

/*!
 * \class  SpiBus
 * \brief
 * \details
 *
 */
class SpiBus : public virtual ISpiBus, public Bus {
public:
	SpiBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~SpiBus() ;

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
	virtual void setDeviceSettings(unsigned srRegisterWidth, unsigned addrMS, unsigned addrLS, bool useReadWriteBit, unsigned readWriteBit) override ;


protected:
	/**
	 * Converts an offset address and a vector of bytes into shift register sized set of bytes
	 *
	 * The returned vector will be MS first. So, for example, a 32 bit shift reg will be returned
	 * as:
	 *
	 * [0] 31 .. 24
	 * [1] 23 .. 16
	 * [2] 15 ..  8
	 * [3]  7 ..  0
	 *
	 * If address bits are 4 .. 0 then the address will be in the LS part of the [3] byte. The data provided in bytes
	 * will be shifted to fit into the remaining data. Assumes the provided by data is also MS first. If the number of bytes
	 * provided is the same as the size of the shift register (or larger) then the MS bits will be dropped during the alignment
	 * to fit in the address.
	 */
	std::vector<uint8_t> writeBytes(uint32_t offset, const std::vector<uint8_t>& bytes) const ;

	/**
	 * Converts an offset address into shift register sized set of bytes
	 *
	 * The data bytes will be dummy values set to 0
	 */
	std::vector<uint8_t> readBytes(uint32_t offset) const ;

	/**
	 *                                                                     _
	 * Use the address size to convert address to a valid value with the R/W bit for a write
	 */
	uint32_t spiWriteOffset(uint32_t offset) const ;

	/**
	 *                                                                     _
	 * Use the address size to convert address to a valid value with the R/W bit for a read
	 */
	uint32_t spiReadOffset(uint32_t offset) const ;

private:
	unsigned mSrSize ;
	unsigned mAddrMs ;
	unsigned mAddrLs ;
	unsigned mAddrSize ;
	bool mUseReadWriteBit ;
	unsigned mReadWriteBit ;
} ;

}

#endif /* COMMON_BUS_INC_SPIBUS_H_ */
