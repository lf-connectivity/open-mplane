/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaTxVVABus.h
 * \brief     Bus interface to the Tx VVA via the FPGA
 *
 *
 * \details   Bus interface to the Tx VVA via the FPGA
 *
 */


#ifndef COMMON_BUS_INC_FPGATXVVABUS_H_
#define COMMON_BUS_INC_FPGATXVVABUS_H_

#include "IFpgaMgr.h"
#include "Bus.h"
#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  FpgaTxVVABus
 * \brief
 * \details
 *
 */
class FpgaTxVVABus : public Bus {
public:

	FpgaTxVVABus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<IBusReadonlySettings> busSettings, unsigned index) ;
	virtual ~FpgaTxVVABus() ;


protected:

	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool doWriteShort(uint32_t offset, uint16_t val) override ;

private:

	std::shared_ptr<IFpgaAntennaRegs> mFpga;     //!> Pointer to FPGA antenna register space
	unsigned mIndex;                                  //!> Antenna index

} ;

}

#endif /* COMMON_BUS_INC_FPGATXVVABUS_H_ */
