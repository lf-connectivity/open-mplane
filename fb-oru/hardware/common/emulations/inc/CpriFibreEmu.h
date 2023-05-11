/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriFibreEmu.h
 * \brief     CPRI Emulator
 *
 *
 * \details   Emulates the Fpga register interface for a CPRI port
 *
 */


#ifndef CPRIFIBREEMU_H_
#define CPRIFIBREEMU_H_

#include <memory>
#include <vector>
#include <iostream>

#include "Socket.h"
#include "SocketServer.h"

#include "OffTargetFPGA.h"
#include "GlobalTypeDefs.h"
#include "TaskEvent.h"

#include "IFpgaCpri.h"

namespace Mplane {

class CpriFibreEmu : public TaskEvent {
public:
	static unsigned constexpr CPRI_EMU_PORT = 55000 ;

	/**
	 * Create emulator
	 * @param fibre				Fibre number - emulator will control this fibre
	 * @param numSktConnections	Number of client sockets
	 * @param sktPortBase		Base port number (adds fibre number for each instance)
	 */
	explicit CpriFibreEmu(unsigned fibre, unsigned numSktConnections = 0, unsigned sktPortBase = CPRI_EMU_PORT) ;
	virtual ~CpriFibreEmu() ;

	// Test emulation interface
	virtual void pullFibre() ;
	virtual void pushFibre() ;
	virtual void pullModule() ;
	virtual void pushModule() ;
	virtual void syncAllow() ;
	virtual void syncProhibit() ;
	virtual void setRemoteRate(UINT16 rateBits) ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	UINT16 writeControlHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readControlHandler(const UINT32 address, const UINT16 mask) ;

	UINT16 writePrefRateHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readPrefRateHandler(const UINT32 address, const UINT16 mask) ;

	UINT16 writeCurrRateHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readCurrRateHandler(const UINT32 address, const UINT16 mask) ;

	UINT16 writeStatusHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readStatusHandler(const UINT32 address, const UINT16 mask) ;

	UINT16 writeRemoteHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readRemoteHandler(const UINT32 address, const UINT16 mask) ;

	void show(std::ostream& os = std::cout) ;

	std::string handleCmd(const std::string& cmd) ;

	void initFromEnv() ;

private:
	unsigned mFibre ;
    std::shared_ptr<SocketServer> mServer ;

	Mutex mEmuMutex ;
	std::shared_ptr<OffTargetFPGA> mFpga ;
	IFpgaCpri::CpriStatus mState ;
	UINT16 mControl ;
	bool mReset ;
	UINT16 mPrefRate ;
	UINT16 mCurrRate ;
	UINT16 mStatus ;
	bool mFibreFitted ;
	bool mModuleFitted ;
	bool mAllowSync ;
	UINT16 mRemoteRate ;
} ;

}

#endif /* CPRIFIBREEMU_H_ */
