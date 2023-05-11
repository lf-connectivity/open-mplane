/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpri.cpp
 * \brief     The implementation of the common radio CommonCpri class
 *
 *
 * \details   This file contains the implementation of the common radio CommonCpri class
 *
 */

// Includes go here, before the namespace
#include <string>
#include <assert.h>
#include <sstream>

#include "IRadio.h"
#include "ICpri.h"
#include "ICarrierServer.h"
#include "CommonCpriCore.h"
#include "CommonCpri.h"

using namespace Mplane;

const bool CommonCpri::MAKE_MAIN_MASTER = true;

Mplane::CommonCpri::CommonCpri(bool mainIsMaster, UINT32 numCpriPorts):
        Loggable ( "CommonCpri", "CP" ),
        mMainIsMaster( mainIsMaster ),
        mNumCpriPorts( numCpriPorts ),
        mInitialised ( ReturnType::RT_NOT_INITIALISED),
        mFpga ( IFpgaMgr::getIFpgaFibreRegs() ),
        mFibreClockSource ( 0 ),
		mCpriCores()
{
    // reserve vector space for all our CPRI port cores
    mCpriCores.reserve(getNumCpriPorts());

    // initialise the CPRI cores
    for ( UINT32 ii = 0; ii < getNumCpriPorts(); ii++ )
    {
        mCpriCores.push_back(std::make_shared<CommonCpriCore>(ii, getCpriPortInitialType(ii)));
    }

}

Mplane::CommonCpri::~CommonCpri()
{
}

void Mplane::CommonCpri::signalPortChange(unsigned cpriPort) const
{
	if (cpriPort >= mCpriCores.size())
		return ;

	// Notify ICpriCore observers
	std::dynamic_pointer_cast< Subject<ICpriCore> >(mCpriCores.at(cpriPort))->notify() ;
}


IFibre::FibreType_t Mplane::CommonCpri::getFibreType() const
{
    // the fibre type is CPRI
    return IFibre::FibreTypeCpri;
}

int Mplane::CommonCpri::getFibreClockSyncSource()
{
    // the fibre clock source
    return mFibreClockSource;
}

UINT32 Mplane::CommonCpri::getNumPorts() const
{
    return getNumCpriPorts();
}

const char* Mplane::CommonCpri::fibreTypeString() const
{
    return "CPRI";
}

void Mplane::CommonCpri::show()
{
    std::stringstream ss;
    ss << std::endl;
    showCpri(ss);
    eventInfo(ss.str());
}


void Mplane::CommonCpri::showCpri(std::ostream& os)
{
    ILoggable::logStream(os, "*** CommonCpri Show ***");

    ILoggable::logStream(os, "State [%s]", ReturnType::getState(mInitialised));
    ILoggable::logStream(os, "Number of CPRI ports [%d], FPGA version [%d]", getNumCpriPorts(), getVersion());
    ILoggable::logStream(os, "Port mappings: ");
    for ( UINT32 ii = 0; ii < getNumCpriPorts(); ii++ )
    {
        ILoggable::logStream(os, "   Port %d [%s],  Clocks Locked [%s]", ii,
                getCpriPortInitialType(ii) == ICpri::CpriPortSlave ? "SLAVE" : "MASTER",
                        areClocksLocked(ii) ? "YES" : "NO");
    }

    ILoggable::logStream(os, "CM Rate Stable [%s]", isCMRateStable() ? "YES" : "NO");

    // now show the cores that are active
    for ( UINT32 ii = 0; ii < getNumCpriPorts(); ii++ )
    {
        if (mCpriCores[ii] != NULL)
        {
            mCpriCores[ii]->showPort( os );
        }
    }

    ILoggable::logStream(os, "*** CommonCpri Show End ***");

}


ReturnType::State Mplane::CommonCpri::initialise(void)
{
    mInitialised = ReturnType::RT_OK;

    return mInitialised;
}

std::shared_ptr<ICpriCore> Mplane::CommonCpri::getPortCore(UINT32 cpriPort)
{
    assert(cpriPort <= getNumCpriPorts());

    return mCpriCores[cpriPort];
}

std::shared_ptr<ICpriCore> Mplane::CommonCpri::getPrimaryPortCore()
{
    return mCpriCores[getPrimaryCpriPort()];
}

UINT32 Mplane::CommonCpri::getNumCpriPorts() const
{
    return CommonCpri::mNumCpriPorts;
}

UINT32 Mplane::CommonCpri::getPrimaryCpriPort() const
{
    // the port which is the primary slave
    return CommonCpri::CPRI_PRIMARY_PORT;
}

unsigned int Mplane::CommonCpri::getVersion() const
{
    return (unsigned)IFpgaMgr::getIFpgaSystemRegs()->read_fpgaVersion();
}

const bool Mplane::CommonCpri::verifyFpgaVersion()
{
#if 1
    // temporary until we can get the FPGA version from the image
    unsigned int imageVer = (unsigned)IFpgaMgr::getIFpgaSystemRegs()->read_fpgaVersion();
#else
    unsigned int imageVer = IImageStore::getRunningImage()->getFpgaVersion();
#endif
    unsigned int runningVer = (unsigned)IFpgaMgr::getIFpgaSystemRegs()->read_fpgaVersion();

    return (imageVer == runningVer);
}

void Mplane::CommonCpri::enableCpriLoopback()
{
}

void Mplane::CommonCpri::disableCpriLoopback()
{
}

void Mplane::CommonCpri::fpgaSoftReset()
{
}

bool Mplane::CommonCpri::isCMRateStable()
{
    // Always stable on the common RRH
    return true;
}

bool Mplane::CommonCpri::areClocksLocked(UINT32 cpriPort)
{
    // Check the 'clocks locked' states for the port
    // Return true when all MGT PLLs are locked
    bool locked = mCpriCores[cpriPort]->getMgtPllLock() &&
                  mCpriCores[cpriPort]->getMgtTxClockLock() &&
                  mCpriCores[cpriPort]->getMgtRxClockLock();

    return locked;
}

bool Mplane::CommonCpri::isMainMaster()
{
    return mMainIsMaster;
}

ICpri::CpriPortType Mplane::CommonCpri::getCpriPortInitialType(UINT32 cpriPort)
{
    if( mMainIsMaster )
    {
        /*
         * For the ETNA FTU CPRI the initial port configuration is hard coded to
         * Master for the first port and slave for all others.
         *
         * Port 0:  Master
         * Port 1:  Slave
         */
        if (cpriPort == 0 )
        {
            return ICpri::CpriPortMaster;
        }
        else
        {
            return ICpri::CpriPortSlave;
        }

    }
    else
    {
        /*
         * For the common CPRI, for more than one CPRI port, the initial port configuration
         * is hard coded to all Slaves except the last port which is Master. Where there is only
         * a single CPRI port this is configured to be a slave.
         *
         * Port 0...n-1:  Slave
         * Port n:        Master
         */
        if ((cpriPort == getNumCpriPorts() - 1) && getNumCpriPorts() > 1 )
        {
            return ICpri::CpriPortMaster;
        }
        else
        {
            return ICpri::CpriPortSlave;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::CommonCpri::clearCpriCores()
{
	mCpriCores.clear();
}
