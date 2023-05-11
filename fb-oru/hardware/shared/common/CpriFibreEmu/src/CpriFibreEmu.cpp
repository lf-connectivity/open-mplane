/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CpriFibreEmu.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "xstringfunc.hpp"
#include "SocketHandler.h"

// NOTE: This should pull in the register definition for the specific application build
#include "regs/CommonFpgaFibreRegs.h"

#include "CpriFibreEmu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTF(fmt, args...)	printf(fmt, ##args)
#else
#define DEBUG_PRINTF(fmt, args...)
#endif

static const unsigned STATE_CHANGE_TIME_MS{200} ;

static const unsigned ADDR_CONTROL{0x000} ;
static const unsigned ADDR_PREF_RATE{0x204} ;
static const unsigned ADDR_CURR_RATE{0x210} ;
static const unsigned ADDR_STATUS{0x20c} ;
static const unsigned ADDR_REMOTE{0x238} ;

static const unsigned DEFAULT_RATE{0x7f} ;

//=============================================================================================================
// MACROS
//=============================================================================================================

#define WRFIELD(nm, buff, val)	\
	(buff) &= ~(CommonFpgaFibreRegs::nm##_MASK << CommonFpgaFibreRegs::nm##_SHIFT) ; \
	(buff) |= ((val) & CommonFpgaFibreRegs::nm##_MASK) << CommonFpgaFibreRegs::nm##_SHIFT

#define RDFIELD(nm, buff)	\
	(((buff) >> CommonFpgaFibreRegs::nm##_SHIFT) & CommonFpgaFibreRegs::nm##_MASK)


//=============================================================================================================
// SOCKET HANDLER
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class EmuSocketHandler: public SocketHandler
{
public:

	using HandleFunc = std::function<std::string(const std::string&)> ;

	static std::shared_ptr<SocketHandler> factory(const std::string& prompt, HandleFunc func)
	{
		std::shared_ptr<SocketHandler> handler(new EmuSocketHandler(prompt, func)) ;
		return handler ;
	}

	explicit EmuSocketHandler(const std::string& prompt, HandleFunc func):
		mPrompt(prompt),
		mFunc(func),
		mConnected(false),
		mThereWasAnException(false)
	{
	}

    virtual ~EmuSocketHandler()
    {

    }



protected:
    virtual int handler()
    {
        mConnected = true;
        mThereWasAnException = false;

        while (mConnected)
        {
            try
            {
            	*this << mPrompt ;

                std::string cmd;
                *this >> cmd;

                std::string reply(mFunc(cmd)) ;
                *this << reply ;
                *this << "\n" ;
            }
            catch (SocketException& e)
            {
                std::cout << " EmuServerHandler Exception caught:" << e.description() << std::endl;
                mThereWasAnException = true;
                mConnected = false;
            }
        }
        if( mThereWasAnException )
            return 1;
        return 0;
    }

private:
    std::string mPrompt ;
    HandleFunc mFunc ;
    bool mConnected;
    bool mThereWasAnException;
};



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CpriFibreEmu::CpriFibreEmu(unsigned fibre, unsigned numSktConnections, unsigned sktPortBase) :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::MEDIUM_STACK, "CpriFibreEmu" + std::to_string(fibre), "FibreEmu"),
	mFibre(fibre),
	mServer(),

	mEmuMutex(),
	mFpga(OffTargetFPGA::getInstance()),
	mState(IFpgaCpri::CPRI_RESET),
	mControl(0),
	mReset(false),
	mPrefRate(DEFAULT_RATE),
	mCurrRate(0),
	mStatus(0),
	mFibreFitted(true),
	mModuleFitted(true),
	mAllowSync(true),
	mRemoteRate(0xffff)

{
	//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "FibreEmu") ;
	DEBUG_PRINTF("FibreEmu @ %p\n", this) ;

	unsigned fibreBase(0x40000 + mFibre*0x1000) ;

	// Set up the register values
	WRFIELD(FIBRE_BLK_RESET, mControl, 1) ;
	WRFIELD(FIBRE_TYPE, mControl, 1) ;
	mReset = true ;

	// register ourself to handle the memory locations
	mFpga->registerHandler(fibreBase+ADDR_CONTROL, fibreBase+ADDR_CONTROL,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeControlHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readControlHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(fibreBase+ADDR_PREF_RATE, fibreBase+ADDR_PREF_RATE,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writePrefRateHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readPrefRateHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(fibreBase+ADDR_CURR_RATE, fibreBase+ADDR_CURR_RATE,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeCurrRateHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readCurrRateHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(fibreBase+ADDR_STATUS, fibreBase+ADDR_STATUS,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeStatusHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readStatusHandler(address, mask) ;
		}
	) ;

	mFpga->registerHandler(fibreBase+ADDR_REMOTE, fibreBase+ADDR_REMOTE,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeRemoteHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readRemoteHandler(address, mask) ;
		}
	) ;

	show() ;

	// Register socket handlers
	if (numSktConnections > 0)
	{
		mServer = std::shared_ptr<SocketServer>(
			new SocketServer("CpriEmuServer" + std::to_string(mFibre), sktPortBase+mFibre, numSktConnections, 0)
		) ;
		for (unsigned idx=0; idx < numSktConnections; ++idx)
		{
			mServer->addSocketHandlers( EmuSocketHandler::factory(
				"CpriEmu" + std::to_string(mFibre) + "->",
				[this](const std::string& cmd)->std::string { return handleCmd(cmd) ; }
			));
		}
		mServer->start() ;
	}

	// update the module absence bit
	mModuleFitted = ( mFpga->internalReadField("sfpModAbs[" + std::to_string(mFibre) + "]") == 0) ;

	// check for settings passed in through the environment variable
	initFromEnv() ;

}

//-------------------------------------------------------------------------------------------------------------
CpriFibreEmu::~CpriFibreEmu()
{
	unsigned fibreBase(0x40000 + mFibre*0x1000) ;
	mFpga->unRegisterHandler(fibreBase+ADDR_CONTROL) ;
	mFpga->unRegisterHandler(fibreBase+ADDR_PREF_RATE) ;
	mFpga->unRegisterHandler(fibreBase+ADDR_CURR_RATE) ;
	mFpga->unRegisterHandler(fibreBase+ADDR_STATUS) ;
	mFpga->unRegisterHandler(fibreBase+ADDR_REMOTE) ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::pullFibre()
{
	{
	Mutex::Lock lock(mEmuMutex) ;
	if (!mFibreFitted)
		return ;

	mFibreFitted = false ;
	}

	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::pushFibre()
{
	{
	Mutex::Lock lock(mEmuMutex) ;
	if (mFibreFitted)
		return ;

	mFibreFitted = true ;
	}

	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::pullModule()
{
	{
	Mutex::Lock lock(mEmuMutex) ;
	if (!mModuleFitted)
		return ;

	mModuleFitted = false ;

	// update the module absence bit
	mFpga->internalWriteField("sfpModAbs[" + std::to_string(mFibre) + "]", 1) ;
	}

	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::pushModule()
{
	{
	Mutex::Lock lock(mEmuMutex) ;
	if (mModuleFitted)
		return ;

	mModuleFitted = true ;

	// update the module absence bit
	mFpga->internalWriteField("sfpModAbs[" + std::to_string(mFibre) + "]", 0) ;
	}

	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::syncAllow()
{
	{
		Mutex::Lock lock(mEmuMutex) ;
		mAllowSync = true ;
	}
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::syncProhibit()
{
	{
		Mutex::Lock lock(mEmuMutex) ;
		mAllowSync = false ;
	}
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::setRemoteRate(UINT16 rateBits)
{
	{
		Mutex::Lock lock(mEmuMutex) ;
		mRemoteRate = rateBits ;
	}
	event() ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool CpriFibreEmu::runEvent()
{
	printf("[FibreEmu%u] EVENT : reset=%u pref rate=0x%02x, FibreFitted=%d, ModuleFitted=%d\n",
			mFibre, (unsigned)mReset, mPrefRate, mFibreFitted, mModuleFitted);

	// iterate state machine until exit
	while(true)
	{
		// Handle special cases
		{
			Mutex::Lock lock(mEmuMutex) ;
			if (mReset)
			{
				mState = IFpgaCpri::CPRI_RESET ;
				mPrefRate = DEFAULT_RATE ;
				mCurrRate = 0 ;
				printf("[FibreEmu%u] in reset, exit now\n", mFibre) ;
				return true ;
			}

			if (mPrefRate == 0)
			{
				mState = IFpgaCpri::CPRI_L1_SYNC ;
				mCurrRate = 0 ;
				printf("[FibreEmu%u] rate 0, exit now\n", mFibre) ;
				return true ;
			}

			if (!mFibreFitted || !mModuleFitted)
			{
				mState = IFpgaCpri::CPRI_L1_SYNC ;
				printf("[FibreEmu%u] no fibre or module fitted, exit now\n", mFibre) ;
				return true ;
			}
		}

		switch (mState)
		{
		case IFpgaCpri::CPRI_RESET:
			printf("[FibreEmu%u] <RESET>\n", mFibre) ;
			Task::msSleep(STATE_CHANGE_TIME_MS) ;

			{
			Mutex::Lock lock(mEmuMutex) ;
			mState = IFpgaCpri::CPRI_L1_SYNC ;
			}
			break ;

		case IFpgaCpri::CPRI_L1_SYNC:
			printf("[FibreEmu%u] <L1_SYNCH>\n", mFibre) ;

			// stay in L1 sync for 1 sec to emulate negotiation
			Task::msSleep(1000) ;

			{
			Mutex::Lock lock(mEmuMutex) ;
			// Use the preferred rate - if 0 then just stay in this state
			if (mPrefRate == 0)
				return true ;

			// stop now until we're allowed to sync
			if (!mAllowSync)
				return true ;

			// Mask with the "remote" allowed rates
			UINT16 rate(mPrefRate & mRemoteRate) ;

			// Cycle down from the highest rate and use the highest we can
			for (unsigned mask=IFpgaCpri::CPRI_10137MBITS; mask > 0; mask >>= 1)
			{
				if (rate & mask)
				{
					mCurrRate = mask ;
					break ;
				}
			}

			// if no rate achieved then stop now
			if (mCurrRate == 0)
				return true ;

			mState = IFpgaCpri::CPRI_VERSION_SETUP ;
			}
			break ;

		case IFpgaCpri::CPRI_VERSION_SETUP:
			printf("[FibreEmu%u] <PROTOCOL_VERSION_SETUP>\n", mFibre) ;
			Task::msSleep(STATE_CHANGE_TIME_MS) ;
			{
			Mutex::Lock lock(mEmuMutex) ;
			mState = IFpgaCpri::CPRI_PARAM_SETUP ;
			}
			break ;

		case IFpgaCpri::CPRI_PARAM_SETUP:
			printf("[FibreEmu%u] <CM_PARAM_SETUP>\n", mFibre) ;
			Task::msSleep(STATE_CHANGE_TIME_MS) ;
			{
			Mutex::Lock lock(mEmuMutex) ;
			mState = IFpgaCpri::CPRI_PASSIVE_MODE ;
			}
			break ;

		case IFpgaCpri::CPRI_PASSIVE_MODE:
			printf("[FibreEmu%u] <PASSIVE_MODE>\n", mFibre) ;
			Task::msSleep(STATE_CHANGE_TIME_MS) ;
			{
			Mutex::Lock lock(mEmuMutex) ;
			mState = IFpgaCpri::CPRI_OPERATIONAL ;
			}
			break ;

		case IFpgaCpri::CPRI_OPERATIONAL:
			printf("[FibreEmu%u] <OPERATIONAL>\n", mFibre) ;
			Task::msSleep(STATE_CHANGE_TIME_MS) ;
			{
			Mutex::Lock lock(mEmuMutex) ;
			mState = IFpgaCpri::CPRI_OPERATIONAL ;

			// stay in this state
			return true ;
			}
			break ;

		default:
			return false ;
			break ;

		}
	}
	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::writeControlHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[FibreEmu%u] write control 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

//	// debug breakpoint locations
//	if (mFibre == 0)
//		std::cerr << "write fibre 0" <<std::endl ;
//	if (mFibre == 1)
//		std::cerr << "write fibre 1" <<std::endl ;

	bool reset(mReset);

	// Can't change fibre type
	UINT16 ctlMask(mask) ;
	ctlMask &= ~(CommonFpgaFibreRegs::FIBRE_TYPE_MASK << CommonFpgaFibreRegs::FIBRE_TYPE_SHIFT) ;

	DEBUG_PRINTF("[FibreEmu%u] ctl mask 0x%04x\n", mFibre, ctlMask) ;

	bool notify(false) ;
	{
		Mutex::Lock lock(mEmuMutex) ;
		mControl &= ~ctlMask ;
		mControl |= (value & ctlMask) ;

		mReset = RDFIELD(FIBRE_BLK_RESET, mControl) == 1 ;

		DEBUG_PRINTF("[FibreEmu%u] control=0x%04x reset=%u\n", mFibre, mControl, mReset) ;
		if (reset != mReset)
		{
			// notify state machine
			notify = true ;
		}

	}

	if (notify)
	{
		// notify state machine
		DEBUG_PRINTF("[FibreEmu%u] notified...\n", mFibre) ;
		event() ;
	}

	return mControl ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::readControlHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	DEBUG_PRINTF("[FibreEmu%u] read control 0x%04x / 0x%04x => 0x%04x\n", mFibre,
		(unsigned)mControl, (unsigned)mask,
		(unsigned)(mControl & mask)
	) ;

	return mControl & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::writePrefRateHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	DEBUG_PRINTF("[FibreEmu%u] write pref rate 0x%05x = 0x%04x / 0x%04x\n", mFibre, address, (unsigned)value, (unsigned)mask) ;

	UINT16 rate(0) ;
	bool notify(false) ;
	{
	Mutex::Lock lock(mEmuMutex) ;
	UINT16 prefRate(mPrefRate) ;
	mPrefRate &= ~mask ;
	mPrefRate |= (value & mask) ;
	rate = mPrefRate ;

	if (prefRate != mPrefRate)
		notify=true ;
	}

	if (notify)
		event() ;

	return rate ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::readPrefRateHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	return mPrefRate & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::writeCurrRateHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::readCurrRateHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	return mCurrRate & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::writeStatusHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::readStatusHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	UINT16 value{0} ;
	WRFIELD(STAT_CODE, value, mState) ;
	WRFIELD(MGTPLL_LOCK, value, 1) ;
	WRFIELD(MGT_TX_CLOCK_LOCK, value, 1) ;
	WRFIELD(MGT_RX_CLOCK_LOCK, value, 1) ;

	if (mState == IFpgaCpri::CPRI_OPERATIONAL)
	{
		WRFIELD(STAT_ALARM, value, 0) ;
		WRFIELD(SFPLOS, value, 0) ;
		WRFIELD(LOS, value, 0) ;
		WRFIELD(LOF, value, 0) ;
		WRFIELD(RAI, value, 0) ;
		WRFIELD(SDI, value, 0) ;
	}
	else
	{
		WRFIELD(STAT_ALARM, value, 1) ;
		WRFIELD(SFPLOS, value, 1) ;
		WRFIELD(LOS, value, 1) ;
		WRFIELD(LOF, value, 1) ;
		WRFIELD(RAI, value, 1) ;
		WRFIELD(SDI, value, 0) ;
	}
	DEBUG_PRINTF("[FibreEmu%u] read status 0x%05x = 0x%04x / 0x%04x (State 0x%x)\n",
			mFibre, address, (unsigned)value, (unsigned)mask, mState) ;
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::writeRemoteHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	// IGNORE
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CpriFibreEmu::readRemoteHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	UINT16 value{0} ;

	if (mState == IFpgaCpri::CPRI_OPERATIONAL)
	{
		WRFIELD(REMOTE_LOS, value, 0) ;
		WRFIELD(REMOTE_LOF, value, 0) ;
		WRFIELD(REMOTE_RAI, value, 0) ;
	}
	else
	{
		WRFIELD(REMOTE_LOS, value, 1) ;
		WRFIELD(REMOTE_LOF, value, 1) ;
		WRFIELD(REMOTE_RAI, value, 1) ;
	}
	DEBUG_PRINTF("[FibreEmu%u] read remote status 0x%05x = 0x%04x / 0x%04x (State 0x%x)\n",
			mFibre, address, (unsigned)value, (unsigned)mask, mState) ;
	return value & mask ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::show(std::ostream& os)
{
	os << "FibreEmu @ " << this << std::endl ;
	os << "  " << "mFibre        : " << mFibre << std::endl ;
	os << "  " << "mModuleFitted : " << mModuleFitted << std::endl ;
	os << "  " << "mFibreFitted  : " << mFibreFitted << std::endl ;
	os << "  " << "mAllowSync    : " << mAllowSync << std::endl ;
	os << "  " << "mState        : 0x" << std::hex << (unsigned)mState << std::dec << std::endl ;
	os << "  " << "mControl      : 0x" << std::hex << mControl << std::dec << std::endl ;
	os << "  " << "mPrefRate     : 0x" << std::hex << mPrefRate << std::dec << std::endl ;
	os << "  " << "mCurrRate     : 0x" << std::hex << mCurrRate << std::dec << std::endl ;
	os << "  " << "mRemoteRate   : 0x" << std::hex << mRemoteRate << std::dec << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CpriFibreEmu::handleCmd(const std::string& cmd)
{
	std::size_t pos ;
	if ( (cmd.find("help") != std::string::npos) || (cmd.find("?") != std::string::npos) )
	{
		return
			"?       Help\n"
			"help    Help\n"
			"module  [in|out]\n"
			"fibre   [in|out]\n"
			"sync    [yes|no]\n"
			"remote  <rate>\n"
			"show\n"
		;
	}

	if (cmd.find("mod") != std::string::npos)
	{
		if (cmd.find("out") != std::string::npos)
		{
			pullModule() ;
		}
		else
		{
			pushModule() ;
		}
		return "OK" ;
	}

	if (cmd.find("fib") != std::string::npos)
	{
		if (cmd.find("out") != std::string::npos)
		{
			pullFibre() ;
		}
		else
		{
			pushFibre() ;
		}
		return "OK" ;
	}

	if (cmd.find("syn") != std::string::npos)
	{
		if (cmd.find("yes") != std::string::npos)
		{
			syncAllow() ;
		}
		else
		{
			syncProhibit() ;
		}
		return "OK" ;
	}

	if ( (pos=cmd.find("rem")) != std::string::npos)
	{
		std::size_t gap(cmd.find_first_of(" \t", pos)) ;
		if (gap == std::string::npos)
			return "INVALID" ;
		std::size_t ratePos(cmd.find_first_not_of(" \t", gap)) ;
		if (ratePos == std::string::npos)
			return "INVALID" ;

		unsigned rate(strtoul(cmd.substr(ratePos).c_str(), NULL, 0)) ;
		setRemoteRate((UINT16)(rate & 0xffff)) ;

		return "OK" ;
	}



	if (cmd.find("show") != std::string::npos)
	{
		std::stringstream ss ;
		show(ss) ;
		return ss.str() ;
	}

	return "Invalid command" ;
}

//-------------------------------------------------------------------------------------------------------------
void CpriFibreEmu::initFromEnv()
{
	// Looking for settings string stored in environment variable: CPRIEMUx
	std::string envVar("CPRIEMU" + std::to_string(mFibre)) ;
	char* env(::getenv(envVar.c_str())) ;
	if (!env)
		return ;

	// split string on ';' and process each as a command
	std::string settings(env) ;
	std::vector<std::string> cmds(split(settings, ';')) ;
	for (auto cmd : cmds)
	{
		handleCmd(cmd) ;
	}
}
