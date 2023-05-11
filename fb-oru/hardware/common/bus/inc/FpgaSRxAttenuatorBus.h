/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaSRxAttenuatorBus.h
 * \brief     Bus interface to the SRx attenuator via the FPGA
 *
 *
 * \details   Bus interface to the SRx attenuator via the FPGA
 *
 */


#ifndef COMMON_BUS_INC_FPGASRXATTNBUS_H_
#define COMMON_BUS_INC_FPGASRXATTNBUS_H_

#include "IFpgaMgr.h"
#include "SpiBus.h"
#include "ISpiBusSettings.h"
#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  FpgaSRxAttenuatorBus
 * \brief
 * \details
 *
 */
class FpgaSRxAttenuatorBus : public SpiBus {
public:

	FpgaSRxAttenuatorBus(const std::string& busName, const std::string& busDetails, std::shared_ptr<IBusLock> busLock,
			std::shared_ptr<ISpiBusReadonlySettings> busSettings, unsigned index) ;
	virtual ~FpgaSRxAttenuatorBus() ;


protected:

	/**
	 * Write a byte to a particular offset address / register in the device
	 */
	virtual bool doWriteByte(uint32_t offset, uint8_t byte) override ;

private:

	std::shared_ptr<IFpgaAntennaRegs> mFpga;     //!> Pointer to FPGA antenna register space
	unsigned mIndex;                                  //!> Antenna index

} ;

}

#endif /* COMMON_BUS_INC_FPGASRXATTNBUS_H_ */
