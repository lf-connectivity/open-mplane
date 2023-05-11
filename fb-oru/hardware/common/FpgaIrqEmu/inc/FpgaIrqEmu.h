/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqEmu.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef FPGAIRQEMU_H_
#define FPGAIRQEMU_H_

#include <vector>
#include <map>

#include "IFpgaIrqEmu.h"

namespace Mplane {

class FpgaIrqDevice ;

class FpgaIrqEmu : public virtual IFpgaIrqEmu {
public:
	FpgaIrqEmu() ;
	virtual ~FpgaIrqEmu() ;

	/**
	 * "open" the appropriate fpga irq device
	 * @return file descriptor
	 */
	virtual int open(const char* pathname, int flags) override ;

	/**
	 * "close" the fpga irq device
	 * @return file descriptor
	 */
	virtual int close(int fd) override ;

	/**
	 * Cause the device to create an IRQ event for the specified bit number
	 * @param irqBit
	 */
	virtual bool raiseIrq(unsigned irqBit) override ;


private:
	std::vector<std::shared_ptr<FpgaIrqDevice>> mDevices ;

	// map fd to device
	std::map<int, std::shared_ptr<FpgaIrqDevice>> mDeviceMap ;
} ;

}

#endif /* FPGAIRQEMU_H_ */
