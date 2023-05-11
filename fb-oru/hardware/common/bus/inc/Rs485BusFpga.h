/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Rs485BusFpga.h
 * \brief     Base-level Rs485 bus driven via the FPGA
 *
 *
 * \details   Base-level Rs485 bus driven via the FPGA
 *
 */


#ifndef COMMON_BUS_INC_RS485BUSFPGA_H_
#define COMMON_BUS_INC_RS485BUSFPGA_H_

#include <mutex>
#include <vector>
#include "SerialBusFpga.h"
#include "IFpgaMgr.h"

namespace Mplane {

/*!
 * \class  Rs485BusFpga
 * \brief
 * \details
 *
 */
class Rs485BusFpga : public SerialBusFpga {
public:
	Rs485BusFpga(const std::string& busName, const std::string& busDetails,
			unsigned baudRate, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings) ;
	virtual ~Rs485BusFpga() ;

protected:

	// Implement the data transfer calls

	/**
	 * Write a block of bytes.
	 * \return true if ok; false otherwise and sets the error string
	 */
	virtual bool doWriteData(const std::vector<uint8_t>& bytes) override ;

} ;

}

#endif /* COMMON_BUS_INC_RS485BUSFPGA_H_ */
