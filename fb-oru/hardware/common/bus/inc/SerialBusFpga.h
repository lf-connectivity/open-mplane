/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SerialBusFpga.h
 * \brief     Base-level serial bus driven via the FPGA
 *
 *
 * \details   Base-level serial bus driven via the FPGA
 *
 */


#ifndef COMMON_BUS_INC_SERIALBUSFPGA_H_
#define COMMON_BUS_INC_SERIALBUSFPGA_H_

#include <mutex>
#include <vector>
#include "SerialBus.h"
#include "IFpgaMgr.h"

namespace Mplane {

/*!
 * \class  SerialBusFpga
 * \brief
 * \details
 *
 */
class SerialBusFpga : public SerialBus {
public:
	SerialBusFpga(const std::string& busName, const std::string& busDetails,
			unsigned baudRate, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~SerialBusFpga() ;

	static const unsigned int UART_BLOCK_SIZE;


protected:

	// Implement the data transfer calls

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) override ;

	/**
	 * Read a block of bytes. If specified number of bytes is 0 then reads
	 * whatever data is available
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doReadData(std::vector<uint8_t>& bytes, unsigned numBytes=0) override ;

	std::shared_ptr<IFpgaSystemRegs> mFpga;     //!> Pointer to FPGA system register space

} ;

}

#endif /* COMMON_BUS_INC_SERIALBUSFPGA_H_ */
