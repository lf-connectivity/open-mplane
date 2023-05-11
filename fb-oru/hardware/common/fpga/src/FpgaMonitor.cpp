/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMonitor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>

#include "stringfunc.hpp"
#include "QueueBuffer.hpp"
#include "IFpga.h"
#include "FpgaMonitor.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static const unsigned TICK_MS = 3 ;

// Sentinel use to ensure FPGA object remains constructed until the program terminates
// NOTE: Using this means that the off target fpga is constructed *BEFORE* main() so you don't have chance
// to change the OFFTARGET_CFG_DIR
static std::shared_ptr<IFpga> fpgaPtr( IFpga::getInstance() ) ;

//=============================================================================================================
// CLASSES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class MonitorData {
public:
	MonitorData(unsigned newValue, unsigned oldValue) :
		mNewValue( newValue ),
		mOldValue( oldValue )
	{
	}

	MonitorData() :
		mNewValue( 0 ),
		mOldValue( 0 )
	{
	}

	~MonitorData() {}

	UINT16 getNewValue() const {
		return mNewValue;
	}

	UINT16 getOldValue() const {
		return mOldValue;
	}

private:
	UINT16 mNewValue ;
	UINT16 mOldValue ;
};

//-------------------------------------------------------------------------------------------------------------
class Mplane::FpgaMonitor::Monitor {
public:
	Monitor(unsigned address, UINT16 mask, RegisterCallback callback, ShowCallback showCallback) :
		mFpga( IFpga::getInstance() ),
		mAddress(address),
		mMask(mask),
		mCallback(callback),
		mShowCallback(showCallback),
		mQueue(new QueueBuffer<MonitorData>("FpgaMonitorQ", "FPGA", [this](const MonitorData& data){queueCallback(data);}) ),

		mCurrentValue( mMask & mFpga->readRegister(mAddress) )
	{
		// send initial value
		mQueue->add( MonitorData(mCurrentValue, mCurrentValue) ) ;
	}

	~Monitor()
	{
	}

	// Check register value - call callback if change
	void check()
	{
		UINT16 value( mMask & mFpga->readRegister(mAddress) ) ;

//std::cerr << std::hex << "Check 0x" << mAddress << " : Current 0x" << value << " Prev 0x" << mCurrentValue << std::dec << std::endl ;

		// if changed then add to queue
		if (value != mCurrentValue)
			mQueue->add( MonitorData(value, mCurrentValue) ) ;

		mCurrentValue = value ;
	}

	// see if address & mask match
	bool isEqual(unsigned address, UINT16 mask)
	{
		return ( (address==mAddress) && (mask=mMask) ) ;
	}

	// Callback used by QueueBuffer
	void queueCallback(const MonitorData& data)
	{
		mCallback(mAddress, data.getNewValue(), data.getOldValue(), mMask) ;
	}

	// Output info
	void show(std::ostream& os)
	{
		char addrStr[16] ;
		char maskStr[16] ;
		snprintf(addrStr, sizeof(addrStr), "0x%05x", mAddress) ;
		snprintf(maskStr, sizeof(maskStr), "0x%04x", mMask) ;

		os <<
			padLeft(addrStr, 7) << " " <<
			padLeft(maskStr, 6) << " " ;

		if (mShowCallback)
			mShowCallback(os) ;

		os << std::endl ;
	}

	// Output title
	static void showTitle(std::ostream& os, const std::string& clientTitle)
	{
		os <<
			padLeft("Address", 7) << " " <<
			padLeft("Mask", 6) << " " <<
			clientTitle << std::endl ;
	}

private:
	std::shared_ptr<IFpga> mFpga ;
	const unsigned mAddress ;
	const UINT16 mMask ;
	RegisterCallback mCallback ;
	ShowCallback mShowCallback ;
	std::shared_ptr<QueueBuffer<MonitorData>> mQueue ;

	UINT16 mCurrentValue ;
};


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMonitor> IFpgaMonitor::getInstance()
{
	static std::shared_ptr<IFpgaMonitor> instance(new FpgaMonitor) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::FpgaMonitor::FpgaMonitor() :
	Task(50, Task::SMALL_STACK, "FpgaMonitor", "FPGA"),

	mTaskRun(true),
	mTaskRunning(false),
	mDataReady(),
	mMutex(),
	mMonitors()
{
	// self start
	start() ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::FpgaMonitor::~FpgaMonitor()
{
	if (!mTaskRunning)
		return ;

	mTaskRun = false ;
	{
	Conditional::Lock condLock(mDataReady) ;
	mDataReady.signal() ;
	}
	msSleep(2*TICK_MS) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaMonitor::addRegister(unsigned address, UINT16 mask, RegisterCallback callback, ShowCallback showCallback)
{
	{
	Mutex::Lock lock(mMutex) ;
	mMonitors.push_back( std::shared_ptr<Monitor>(new FpgaMonitor::Monitor(address, mask, callback, showCallback)) ) ;
	}

	Conditional::Lock condLock(mDataReady) ;
	mDataReady.signal() ;

}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaMonitor::delRegister(unsigned address, UINT16 mask)
{
	Mutex::Lock lock(mMutex) ;
	mMonitors.erase(
		std::remove_if(mMonitors.begin(), mMonitors.end(),
			[address, mask](const std::shared_ptr<Monitor>& mon)->bool {
				return mon->isEqual(address, mask) ;
			}
		), mMonitors.end());
}


//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaMonitor::show(std::ostream& os, const std::string& clientTitle)
{
	Monitor::showTitle(os, clientTitle) ;

	Mutex::Lock lock(mMutex) ;
	for (auto monitor : mMonitors)
	{
		// see if register has change
		monitor->show(os) ;
	}

}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int Mplane::FpgaMonitor::run()
{
	mTaskRunning = true ;

    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRun)
    {
    	// wait for registers to become available
    	mDataReady.wait() ;

		// check for task stop
		if (!mTaskRun)
			break ;

		// process all registers
		bool registers(true) ;
		while (registers && mTaskRun)
		{
			// check monitor list
			{
				Mutex::Lock lock(mMutex) ;
				for (auto monitor : mMonitors)
				{
					// see if register has change
					monitor->check() ;
				}
			}

			// now go to sleep for the tick time
			msSleep(TICK_MS) ;

			// check monitor list
			{
				Mutex::Lock lock(mMutex) ;
				registers = !mMonitors.empty() ;
			}
		}
    }

	mTaskRunning = false ;
    return 0;
}
