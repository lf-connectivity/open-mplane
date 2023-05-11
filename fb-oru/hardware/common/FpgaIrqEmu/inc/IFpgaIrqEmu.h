/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaIrqEmu.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef IFPGAIRQEMU_H_
#define IFPGAIRQEMU_H_

#include <memory>

namespace Mplane {

class IFpgaIrqEmu {
public:
	IFpgaIrqEmu() {}
	virtual ~IFpgaIrqEmu() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFpgaIrqEmu> getInstance() ;

	/**
	 * "open" the appropriate fpga irq device
	 * @return file descriptor
	 */
	virtual int open(const char* pathname, int flags) =0 ;

	/**
	 * "close" the fpga irq device
	 * @return file descriptor
	 */
	virtual int close(int fd) =0 ;

	/**
	 * Cause the device to create an IRQ event for the specified bit number
	 * @param irqBit
	 */
	virtual bool raiseIrq(unsigned irqBit) =0 ;

} ;

}

#endif /* IFPGAIRQEMU_H_ */
