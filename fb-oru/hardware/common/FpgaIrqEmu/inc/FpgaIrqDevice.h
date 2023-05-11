/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqDevice.h
 * \brief     Emulates an fpga irq device
 *
 *
 * \details   Each fpga irq bit has it's own device entry "/dev/fpga-irq.X" where X is the bit number.
 * 			 This class emulates a device by creating file pipes which allow the application to read from it's end
 * 			 while this emulator writes irq event data in at the other end
 *
 */


#ifndef FPGAIRQDEVICE_H_
#define FPGAIRQDEVICE_H_

#include <memory>
#include <map>

namespace Mplane {

class FpgaIrqDevice {
public:
	explicit FpgaIrqDevice(unsigned bitNum) ;
	virtual ~FpgaIrqDevice() ;

	/**
	 * Creates a new pipe and returns the app's end fd
	 * @return file descriptor
	 */
	virtual int open(const char* pathname, int flags) ;

	/**
	 * closes the pipe
	 * @return file descriptor
	 */
	virtual int close(int fd) ;

	/**
	 * Create an IRQ event
	 */
	virtual void raiseIrq() ;

private:
	// Which irq bit number this object is emulating
	unsigned mBitNum ;

	// Map of file descriptors - key is fd for the app's end of the pipe; value is fd for this end of the pipe
	std::map<int, int> mPipeList ;
} ;

}

#endif /* FPGAIRQDEVICE_H_ */
