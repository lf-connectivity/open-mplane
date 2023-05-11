/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommsEmuHandler.h
 * \brief     Base class that handles accesses to FPGA comms memory
 *
 *
 * \details   Provides a Task in which the comms protocol can be implemented. Provides default methods for reading/writing
 * 				into the FPGA comms memory
 *
 */


#ifndef COMMSEMUHANDLER_H_
#define COMMSEMUHANDLER_H_

#include <vector>
#include <memory>

#include "Conditional.h"
#include "Mutex.h"
#include "Task.h"
#include "OffTargetFPGA.h"

#include "CommsEmuMsg.h"


namespace Mplane {

class CommsEmuHandler : public Task
{
public:
	/**
	 * Create an object which handles a one of the FPGA comms channels
	 * @param name	Name of derived object (used as the logging instance name)
	 * @param startAddress	Start fpga register address handled by this object
	 * @param numAddresses	Number of 16-bit words handled (from the start address)
	 * @param triggerAddress	Fpga register address used to trigger protocol handling
	 */
	CommsEmuHandler(const std::string& name, UINT32 startAddress, unsigned numAddresses, UINT32 triggerAddress) ;
	virtual ~CommsEmuHandler() ;

protected:
	/**
	 * Raw memory write
	 * @param address
	 * @param value
	 * @param mask
	 * @return value in memory at this location
	 */
	UINT16 memWrite(const UINT32 address, const UINT16 value, const UINT16 mask) ;

	/**
	 * Raw memory read
	 * @param address
	 * @param mask
	 * @return value in memory at this location
	 */
	UINT16 memRead(const UINT32 address, const UINT16 mask) ;

protected:
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() =0 ;

private:
	/**
	 * Handler that processes fpga register writes from the fpga emulator
	 * @param address
	 * @param value
	 * @param mask
	 * @return final write value in memory
	 */
	UINT16 writeHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;

	/**
	 * Handler that processes fpga register reads from the fpga emulator
	 * @param address
	 * @param mask
	 * @return value in memory
	 */
	UINT16 readHandler(const UINT32 address, const UINT16 mask) ;

protected:
	// Conditional used to signal to task - derived objects define their own run() and need access to this variable
	Conditional mTrigger ;

	// Address range
	UINT32 mStartAddress ;
	unsigned mNumAddresses ;
	UINT32 mTriggerAddress ;

private:
	std::shared_ptr<OffTargetFPGA> mFpga ;

	// protect the data
	Mutex mMutex ;

	// Store the register values
	std::vector<UINT16> mRegs ;


} ;

}

#endif /* COMMSEMUHANDLER_H_ */
