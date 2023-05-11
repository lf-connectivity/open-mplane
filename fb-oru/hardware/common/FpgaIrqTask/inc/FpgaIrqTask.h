/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqTask.h
 * \brief     Task that executes when the waited for fpga irq triggers
 *
 *
 * \details   This task sits in a loop blocked by reading the fpga irq device. Whenever an IRQ event occurs, the read()
 * 				call returns and the task executes the provided callback
 *
 */


#ifndef FPGAIRQTASK_H_
#define FPGAIRQTASK_H_

#include <memory>
#include <functional>

#include "Task.h"

namespace Mplane {

class FpgaIrqTask : public Task {
public:
	/**
	 * Callback function called when IRQ activates.
	 * NOTE: char* is used rather than std::string to ensure callback is called as fast as possible
	 */
	using FpgaIrqTaskFunction = std::function<void(char* timestamp)> ;

	FpgaIrqTask(unsigned irqBit, FpgaIrqTaskFunction callback) ;
	virtual ~FpgaIrqTask() ;

protected:
    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() override;

private:
    unsigned mIrqBit ;
    FpgaIrqTaskFunction mCallback ;

    // file descriptor used for reading from device
    int mDevFd ;

    // pipe used to wake task on shutdown
    int mReadFd ;
    int mWriteFd ;

    // flag set when shuttng down
    bool mShutdown ;
} ;

}

#endif /* FPGAIRQTASK_H_ */
