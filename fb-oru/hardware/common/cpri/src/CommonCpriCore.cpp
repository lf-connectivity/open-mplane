/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriCore.cpp
 * \brief     The implementation of the common radio CommonCpriCore class
 *
 *
 * \details   This file contains the implementation of the common radio CommonCpriCore class
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>
#include <string>
#include <sstream>

#include "stringfunc.hpp"
#include "CommonCpriCore.h"

using namespace Mplane;

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::map<ICpriCore::StatusCode, std::string> STATUS_STRINGS = {

	{ ICpriCore::RESET,						"RESET" },
	{ ICpriCore::ATTEMPTING_L1_SYNCH,		"ATTEMPTING_L1_SYNCH" },
	{ ICpriCore::PROTOCOL_VERSION_SETUP,	"PROTOCOL_VERSION_SETUP" },
	{ ICpriCore::CM_PARAM_SETUP,			"CM_PARAM_SETUP" },
	{ ICpriCore::PASSIVE_MODE,				"PASSIVE_MODE" },
	{ ICpriCore::OPERATIONAL,				"OPERATIONAL" }

} ;

//-------------------------------------------------------------------------------------------------------------
const std::map<ICpriCore::LineRate, std::string> LINE_RATE_STRINGS = {

	{ ICpriCore::RateUnknown,	"LINE RATE UNKNOWN" },
	{ ICpriCore::Rate614_4,		"614.4" },
	{ ICpriCore::Rate1228_8,	"1228.8" },
	{ ICpriCore::Rate2457_6,	"2457.6" },
	{ ICpriCore::Rate3072_0,	"3072.0" },
	{ ICpriCore::Rate4915_2,	"4915.2" },
	{ ICpriCore::Rate6144_0,	"6144.0" },
	{ ICpriCore::Rate9830_4,	"9830.4" },
	{ ICpriCore::Rate10137_6,	"10137.6" }

} ;
using LINE_RATE_STRINGS_ITER = std::map<ICpriCore::LineRate, std::string>::iterator ;
using LINE_RATE_STRINGS_PAIR = std::pair<ICpriCore::LineRate, std::string> ;

//-------------------------------------------------------------------------------------------------------------
const std::map<ICpriCore::CMRateValue, std::string> CM_RATE_STRINGS = {

	{ ICpriCore::CMRateUnknown,	"CMRateUnknown" },
	{ ICpriCore::CMRate240,		"0.240" },
	{ ICpriCore::CMRate480,		"0.480" },
	{ ICpriCore::CMRate960,		"0.960" },
	{ ICpriCore::CMRate1920,	"1.920" },
	{ ICpriCore::CMRate2400,	"2.400" },
	{ ICpriCore::CMRate3840,	"3.840" },
	{ ICpriCore::CMRate4800,	"4.800" },
	{ ICpriCore::CMRate7680,	"7.680" },
	{ ICpriCore::CMRate21120,	"21.120" },
	{ ICpriCore::CMRate42240,	"42.240" },
	{ ICpriCore::CMRate84480,	"84.480" },
	{ ICpriCore::CMRate105600,	"105.600" },
	{ ICpriCore::CMRate168960,	"168.960" },
	{ ICpriCore::CMRate211200,	"211.200" },
	{ ICpriCore::CMRate337920,	"337.920" },
	{ ICpriCore::CMRateDisabled,"CMRate Disabled" }

} ;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string ICpriCore::statusToString(ICpriCore::StatusCode status)
{
	auto entry(STATUS_STRINGS.find(status)) ;
	if (entry == STATUS_STRINGS.end())
		return "INVALID STATUS";

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ICpriCore::lineRateToString(ICpriCore::LineRate rate)
{
	auto entry(LINE_RATE_STRINGS.find(rate)) ;
	if (entry == LINE_RATE_STRINGS.end())
	    return LINE_RATE_STRINGS.at(ICpriCore::RateUnknown) ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
std::string ICpriCore::cmRateToString(ICpriCore::CMRateValue cmrRate)
{
	auto entry(CM_RATE_STRINGS.find(cmrRate)) ;
	if (entry == CM_RATE_STRINGS.end())
	    return CM_RATE_STRINGS.at(ICpriCore::CMRateUnknown) ;

	return entry->second ;
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRate ICpriCore::stringToLineRate(const std::string& str)
{
	std::string upper(toUpper(str)) ;

	if (upper == "AUTO")
		return ICpriCore::RateUnknown ;

	unsigned rate( static_cast<unsigned>(std::stoul(upper)) ) ;
	if (rate == static_cast<unsigned>(ICpriCore::RateUnknown))
		return ICpriCore::RateUnknown ;
	if (rate > static_cast<unsigned>(ICpriCore::RateMax))
		return ICpriCore::RateUnknown ;
	return static_cast<ICpriCore::LineRate>(rate) ;
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRate ICpriCore::stringMbpsToLineRate(const std::string& str)
{
	std::string upper(toUpper(str)) ;
	auto entry(std::find_if(LINE_RATE_STRINGS.begin(), LINE_RATE_STRINGS.end(),
		[upper](LINE_RATE_STRINGS_PAIR pair)->bool {
			return upper == pair.second ;
		}
	)) ;
	if (entry == LINE_RATE_STRINGS.end())
		return ICpriCore::RateUnknown ;

	return entry->first ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ICpriCore::ICpriCore()
{
    // nothing to do
}

//-------------------------------------------------------------------------------------------------------------
CommonCpriCore::CommonCpriCore( int cpriPortNumber, ICpri::CpriPortType cpriPortType ):
        Loggable ( "CommonCpriCore", cpriPortNumber, "CP" ),
		mFpga ( IFpgaMgr::getIFpgaCpri() ),
		mFibreFpga ( IFpgaMgr::getIFpgaFibreRegs() ),
        mSfpData( ISfpData::getInstance(ISfpData::getPhysicalPortNum(cpriPortNumber)) ),
        mCoreId ( 0 ),
        mFibre ( cpriPortNumber ),
        mWaitSamples(0),
        mCpriReIdIsZeroCount ( 0 )
{

    // Uncomment to generate an appropriate debug trace level output.
    //ILoggable::setLogDebugLevel( ILoggable::LOG_DEBUG_VERBOSE );

    switch (cpriPortType)
    {
    case ICpri::CpriPortSlave:
        // Slave port
        mCoreId = CPRI_SLAVE_CORE;
        setMode();  // set the core into Slave mode
        break;

    case ICpri::CpriPortMaster:
        // Master port
        mCoreId = CPRI_MASTER_CORE;
        setMode();  // set the core into Master mode
        break;

    case ICpri::CpriPortInactive:
    default:
        // Inactive or invalid port, no mode to set
        mCoreId = CPRI_INACTIVE_CORE;
        break;  // nothing to do
    } // end switch

    // do the default core initialisation
    defaultCoreInitialisation();
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::show()
{
    std::stringstream ss;
    ss << std::endl;
    showPort(ss);
    eventInfo(ss.str());
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::showPort(std::ostream& os)
{
    ICpriCore::RemoteAlarms remoteAlarms = readRemoteAlarms();

    ILoggable::logStream(os, "*** CommonCpriCore Show -- mCoreId=%d [%s], mFibre=%d ***",
             mCoreId, mCoreId == CPRI_SLAVE_CORE ? "SLAVE" : "MASTER", mFibre);

    showPortStatus(os);

    ILoggable::logStream(os, "isCoreOutOfReset[%s], status code=%s",
             isCoreOutOfReset() ? "YES" : "NO", getStatusCodeString(getStatusCode()));
    ILoggable::logStream(os, "preferredProtocolVersion=%d", getPreferredProtocolVersion());
    ILoggable::logStream(os, "isAlarmCurrentlyActive[%s], haveLOS[%s],  haveLOF[%s]",
             isAlarmCurrentlyActive() ? "YES" : "NO",
             haveLOS() ? "YES" : "NO",
             haveLOF() ? "YES" : "NO");
    ILoggable::logStream(os, "RemoteAlarms: LOS=%d, LOF=%d, RAI=%d, SDI=%d, RST=%d",
             remoteAlarms.remoteLOS, remoteAlarms.remoteLOF,
             remoteAlarms.remoteRAI, remoteAlarms.remoteSDI,
             remoteAlarms.remoteRST);
    ILoggable::logStream(os, "LocalAlarms:  SFPLOS=%d, LOS=%d, LOF=%d",
            haveSFPLOS(), haveLOS(), haveLOF());
    ILoggable::logStream(os, "isSlave[%s],  isMaster[%s]", isSlave() ? "YES" : "NO", isMaster() ? "YES" : "NO");
    ILoggable::logStream(os, "currentEthernetPointer=%d,  preferredEthernetPointer=%d", getCurrentEthernetPointer(), getPreferredEthernetPointer());
    ILoggable::logStream(os, "ethernetBitRate = %d [%3.3f Mbps] ",
             getCurrentEthernetBitRate(getCurrentEthernetPointer()),
             (double)getCurrentEthernetBitRate(getCurrentEthernetPointer())/1000.0);
    ILoggable::logStream(os, "readRxSubChannel2Word[0]=%d, [1]=%d, [2]=%d, [3]=%d",
            readRxSubChannel2Word0(), readRxSubChannel2Word1(),
            readRxSubChannel2Word2(), readRxSubChannel2Word3());
    ILoggable::logStream(os, "GTPBarrelShiftPos=%d", getGTPBarrelShiftPos());
    ILoggable::logStream(os, "Line Rate Capability (Mbps): %s", getLineRateCapabilityString(getLineRateCapability()));
    ILoggable::logStream(os, "isTransmitResetAckActive[%s],  isTransmitSapDefectActive[%s]",
             isTransmitResetAckActive() ? "YES" : "NO",
             isTransmitSapDefectActive() ? "YES" : "NO");
    ILoggable::logStream(os, "R21CoarseTimer=%d,  R21FIFOTransitTime=%d", getR21CoarseTimer(), getR21FIFOTransitTime());
//    ILoggable::logStream(os, "TopologyPMRE=%d,  TopologyLinkId=%d,  TopologyREID=%d",
//             getTopologyPMRE(), getTopologyLinkId(), getTopologyREID());
    ILoggable::logStream(os, "Revision=0x%04x,  CpriReIdIsZeroCount=%d", getRevision(), getCpriReIdIsZeroCount());
    ILoggable::logStream(os, "Wait Samples=%u", getWaitSamples());
    ILoggable::logStream(os, "SFP Rate=%u Mbps", mSfpData->sfpSupportedRateMBps());
    ILoggable::logStream(os, "SFP Vendor=%s", mSfpData->sfpVendorName().c_str());
    ILoggable::logStream(os, "SFP Part=%s", mSfpData->sfpVendorPart().c_str());
    ILoggable::logStream(os, "SFP Rev=%s", mSfpData->sfpVendorRev().c_str());
    ILoggable::logStream(os, "*** CommonCpriCore Show End ***");

}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setWaitSamples(unsigned waitSamples)
{
	mFibreFpga->write_txWaitSamples(mFibre, waitSamples) ;
	mFibreFpga->write_waitSamples(mFibre, waitSamples) ;
	unsigned actualWaitSamples = static_cast<unsigned>(mFibreFpga->read_waitSamples(mFibre)) ;
	mWaitSamples = actualWaitSamples ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCpriCore::getWaitSamples() const
{
	return mWaitSamples ;
}


//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::takeCoreOutOfReset()
{
    mFpga->takeCpriOutOfReset(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::putCoreIntoReset()
{
    mFpga->putCpriIntoReset(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isCoreOutOfReset()
{
    return mFpga->isCpriOutOfReset(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::resetCore()
{
    mFpga->resetCpriCore(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::StatusCode_t CommonCpriCore::getStatusCode()
{
    IFpgaCpri::CpriStatus  status = mFpga->cpriStatusCode(mFibre);

    StatusCode retval = RESET;

    switch (status)
    {
    case IFpgaCpri::CPRI_RESET:
        retval = RESET;
        break;

    case IFpgaCpri::CPRI_L1_SYNC:
        retval = ATTEMPTING_L1_SYNCH;
        break;

    case IFpgaCpri::CPRI_VERSION_SETUP:
        retval = PROTOCOL_VERSION_SETUP;
        break;

    case IFpgaCpri::CPRI_PARAM_SETUP:
        retval = CM_PARAM_SETUP;
        break;

    case IFpgaCpri::CPRI_PASSIVE_MODE:
        retval = PASSIVE_MODE;
        break;

    case IFpgaCpri::CPRI_OPERATIONAL:
        retval = OPERATIONAL;
        break;

    default:
        eventFatal(__FILE__, __LINE__, CRITICAL_ERROR_UNSUPPORTED_CPRI_CORE_STATE, "Unsupported CPRI core state");
        break;
    }

    return retval;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setPreferredProtocolVersion(UINT16 prefProtValue)
{
    logDebugVerbose(
            "%s: port %d, protocol = %d",
            __func__, mFibre, prefProtValue);

    mFpga->setCpriPreferredProtocolVersion(mFibre, prefProtValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getPreferredProtocolVersion()
{
    return mFpga->getCpriPreferredProtocolVersion(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getCurrentProtocolVersion()
{
    return mFpga->getCpriCurrentProtocolVersion(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isAlarmCurrentlyActive()
{
    return mFpga->cpriIsAlarmActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::RemoteAlarms CommonCpriCore::readRemoteAlarms()
{
    IFpgaCpri::CpriRemoteAlarms fpgaAlarms = mFpga->cpriReadRemoteAlarms(mFibre);

    ICpriCore::RemoteAlarms alarms;

    alarms.remoteLOS = fpgaAlarms.remoteLOS;
    alarms.remoteLOF = fpgaAlarms.remoteLOF;
    alarms.remoteRAI = fpgaAlarms.remoteRAI;
    alarms.remoteSDI = fpgaAlarms.remoteSDI;
    alarms.remoteRST = fpgaAlarms.remoteRST;

    return alarms;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::haveSFPLOS()
{
    return mFpga->cpriIsSfpLosAlarmActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::haveLOS()
{
    return mFpga->cpriIsLosAlarmActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::haveLOF()
{
    return mFpga->cpriIsLofAlarmActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isSlave()
{
    return (!mFpga->cpriIsMasterPort(mFibre) &&  mCoreId == CPRI_SLAVE_CORE);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isMaster()
{
    return (mFpga->cpriIsMasterPort(mFibre) &&  mCoreId == CPRI_MASTER_CORE);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isInactive()
{
    return (mCoreId == CPRI_INACTIVE_CORE);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::readRxSubChannel2Word0()
{
    return mFpga->cpriReadRxSubChannelWord(mFibre, 0 );
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::readRxSubChannel2Word1()
{
    return mFpga->cpriReadRxSubChannelWord(mFibre, 1 );
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::readRxSubChannel2Word2()
{
    return mFpga->cpriReadRxSubChannelWord(mFibre, 2 );
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::readRxSubChannel2Word3()
{
    return mFpga->cpriReadRxSubChannelWord(mFibre, 3 );
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::cpriResetEthernet()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre);

    mFpga->cpriResetEthernet(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::cpriResetEthernetTx()
{
    // This FPGA does not support an ethernet reset per direction
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::cpriResetEthernetRx()
{
    // This FPGA does not support an ethernet reset per direction
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getGTPBarrelShiftPos()
{
    return mFpga->cpriGetGTPBarrelShift(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setGTPBarrelShiftPos(UINT16 shiftValue)
{
    logDebugVerbose(
            "%s: port %d, shift value = %d",
            __func__, mFibre, shiftValue);

    mFpga->cpriSetGTPBarrelShift(mFibre, shiftValue );
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setPreferredEthernetPointer(UINT16 prefEthPtrValue)
{
    logDebugVerbose(
            "%s: port %d, ethernet pointer = %d",
            __func__, mFibre, prefEthPtrValue);

    mFpga->cpriSetPreferredEthernetPointer(mFibre, prefEthPtrValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getPreferredEthernetPointer()
{
    return mFpga->cpriGetPreferredEthernetPointer(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getCurrentEthernetPointer()
{
    return mFpga->cpriGetCurrentEthernetPointer(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setPreferredHdlcRate(UINT16 prefHdlcRateValue)
{
    mFpga->cpriSetPreferredHdlcRate(mFibre, prefHdlcRateValue);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getPreferredHdlcRate()
{
    return mFpga->cpriGetPreferredHdlcRate(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRate_t CommonCpriCore::getCurrentLineRate()
{
    LineRate retval = RateUnknown;

    IFpgaCpri::CpriLineSpeed cpriSpeed = mFpga->cpriReadCurrentLineSpeed(mFibre);

    switch (cpriSpeed)
    {
    case IFpgaCpri::CPRI_10137MBITS:
        retval = Rate10137_6;
        break;

    case IFpgaCpri::CPRI_9830MBITS:
        retval = Rate9830_4;
        break;

    case IFpgaCpri::CPRI_6144MBITS:
        retval = Rate6144_0;
        break;

    case IFpgaCpri::CPRI_4915MBITS:
        retval = Rate4915_2;
        break;

    case IFpgaCpri::CPRI_3072MBITS:
        retval = Rate3072_0;
        break;

    case IFpgaCpri::CPRI_2457MBITS:
        retval = Rate2457_6;
        break;

    case IFpgaCpri::CPRI_1228MBITS:
        retval = Rate1228_8;
        break;

    case IFpgaCpri::CPRI_614MBITS:
        retval = Rate614_4;
        break;

    default:
        break;
    }

    return retval;
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::LineRateCapability CommonCpriCore::getLineRateCapability()
{
    ICpriCore::LineRateCapability retval;

    // Use the SFP rate
    unsigned lineRateMBps(mSfpData->sfpSupportedRateMBps()) ;

    retval.capableOfRate614_4  = (lineRateMBps >= 615);
    retval.capableOfRate1228_8 = (lineRateMBps >= 1229);
    retval.capableOfRate2457_6 = (lineRateMBps >= 2458);
    retval.capableOfRate3072_0 = (lineRateMBps >= 3072);
    retval.capableOfRate4915_2 = (lineRateMBps >= 4916);
    retval.capableOfRate6144_0 = (lineRateMBps >= 6144);
    retval.capableOfRate9830_4 = (lineRateMBps >= 9831);
    retval.capableOfRate10137_6 = (lineRateMBps >= 10138);

    return retval;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setNoLineRateCapability()
{
    UINT16 cpriRate = 0;

    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre);

    mFpga->cpriSetLineSpeedCapability(mFibre, cpriRate);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setLineRateCapability(LineRateCapability rateCapability)
{
    UINT16 cpriRate = 0;

    cpriRate |= (rateCapability.capableOfRate614_4 ? IFpgaCpri::CPRI_614MBITS : 0);
    cpriRate |= (rateCapability.capableOfRate1228_8 ? IFpgaCpri::CPRI_1228MBITS : 0);
    cpriRate |= (rateCapability.capableOfRate2457_6 ? IFpgaCpri::CPRI_2457MBITS : 0);
    cpriRate |= (rateCapability.capableOfRate3072_0 ? IFpgaCpri::CPRI_3072MBITS : 0);
    cpriRate |= (rateCapability.capableOfRate4915_2 ? IFpgaCpri::CPRI_4915MBITS: 0);
    cpriRate |= (rateCapability.capableOfRate6144_0 ? IFpgaCpri::CPRI_6144MBITS: 0);
    cpriRate |= (rateCapability.capableOfRate9830_4 ? IFpgaCpri::CPRI_9830MBITS: 0);
    cpriRate |= (rateCapability.capableOfRate10137_6 ? IFpgaCpri::CPRI_10137MBITS: 0);

    logDebugVerbose(
            "%s: port %d, line rate capability = %d",
            __func__, mFibre, cpriRate);

    mFpga->cpriSetLineSpeedCapability(mFibre, cpriRate);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::enableTransmitResetRequest()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    mFpga->cpriEnableTransmitResetRequest(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::disableTransmitResetRequest()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    mFpga->cpriDisableTransmitResetRequest(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isTransmitResetAckActive()
{
    return mFpga->cpriIsTransmitResetAckActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setTxAlarmSdi()
{
    mFpga->cpriSetTxAlarmSdi(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::clearTxAlarmSdi()
{
    mFpga->cpriClearTxAlarmSdi(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isTransmitSapDefectActive()
{
    return mFpga->cpriIsSapDefectActive(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::slaveTransmitEnable()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    mFpga->cpriSlaveTransmitEnable(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::slaveTransmitDisable()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    mFpga->cpriSlaveTransmitDisable(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isSlaveTransmitEnabled()
{
    return mFpga->cpriIsSlaveTransmitEnabled(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CommonCpriCore::getR21CoarseTimer()
{
    return mFpga->cpriReadR21coarseTimer(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getR21FIFOTransitTime()
{
    return mFpga->cpriReadR21FifoTransitTime(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getTopologyPMRE()
{
    return mFpga->cpriReadTopologyPMRE(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getTopologyLinkId()
{
    return mFpga->cpriReadTopologyLinkId(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getTopologyREID()
{
    UINT16 reid = mFpga->cpriReadTopologyReID(mFibre);

    if (reid == 0)
    {
        // keep count of the number of times the REID is zero
        mCpriReIdIsZeroCount++;
    }

    return reid;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setTopologyREID(UINT16 reid)
{
    logDebugVerbose(
            "%s: on port %d to reid = %d",
            __func__, mFibre, reid );

    mFpga->cpriWriteTopologyReID(mFibre, reid);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::getMgtPllLock()
{
    return mFpga->cpriGetMgtPllLock(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::getMgtTxClockLock()
{
    return mFpga->cpriGetMgtTxClockLock(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::getMgtRxClockLock()
{
    return mFpga->cpriGetMgtRxClockLock(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
/**
 *  Sets up a port.
 */
void CommonCpriCore::setPortParameters(CpriPortControl& portControl)
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    // setting the preferred line rate capability to a value that is not zero will take the core out of reset
    setLineRateCapability( portControl.allowableRates );

    cpriResetEthernet();
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::CpriPortStatus CommonCpriCore::getPortStatus()
{
    RemoteAlarms alarms = readRemoteAlarms();
    ICpriCore::CpriPortStatus status;

    // Default the "logicallyEnabled" flag to be true if core is not in reset
    status.logicallyEnabled = isCoreOutOfReset();

    /* For the port to be up and running we expect the status register to be 0x0f
     * The exception being the Service Defect Indicator. This is flagged as an alarm
     * but needs to be passed down the link so we need to leave the port enabled.
     */
    StatusCode statusCode = getStatusCode();
    status.active = false;
    status.status = statusCode;

    if (statusCode == OPERATIONAL)
    {
        if (isAlarmCurrentlyActive() == false)
        {
            status.active = true;
        }
        else
        {
            // Operational but alarm active - still ok if the only remote alarm is the SDI and
            // remote LOS/LOF not detected.
            if (alarms.remoteSDI == true &&
                alarms.remoteLOS == false &&
                alarms.remoteLOF == false )
            {
                status.active = true;
            }
        }
    }

    logDebugVerbose("%s: port %d active=%u : alarm=%u status=%u",
            __func__, mFibre, (unsigned)status.active, (unsigned)isAlarmCurrentlyActive(), (unsigned)statusCode );


    status.mgtPllLock = getMgtPllLock();
    status.mgtTxClockLock = getMgtTxClockLock();
    status.mgtRxClockLock = getMgtRxClockLock();
    status.lineRate = getCurrentLineRate();
    status.ethernetMinCMBandwidth = getCurrentMinEthernetRate();
    status.ethernetMaxCMBandwidth = getCurrentMaxEthernetRate();

    // Status now updated to use remote alarms rather than local CPRI status alarm settings
    IFpgaCpri::CpriRemoteAlarms fpgaAlarms = mFpga->cpriReadRemoteAlarms(mFibre);

    status.remoteSapDefect   = fpgaAlarms.remoteSDI;
    status.remoteLossOfFrame = fpgaAlarms.remoteLOF;
    status.remoteLossOfSync  = fpgaAlarms.remoteLOS;
    status.remoteAlarmInd    = fpgaAlarms.remoteRAI;

    status.sfpLos = haveSFPLOS();
    status.localLossOfFrame = haveLOF();
    status.localLossOfSync  = haveLOS();
    status.protocolVersion = getCurrentProtocolVersion();

    return status;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 CommonCpriCore::getRevision()
{
    return mFpga->cpriGetCoreRevision(mFibre);
}

//-------------------------------------------------------------------------------------------------------------
int CommonCpriCore::getCpriReIdIsZeroCount()
{
    return mCpriReIdIsZeroCount;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::resetCpriReIdIsZeroCount()
{
    mCpriReIdIsZeroCount = 0;
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::CMRateValue_t CommonCpriCore::getCurrentMinEthernetRate()
{
    UINT32 tempBitRate = getCurrentEthernetBitRate(63);

    switch(tempBitRate)
    {
    case 480:
        return CMRate480;
    case 960:
        return CMRate960;
    case 1920:
        return CMRate1920;
    case 2400:
        return CMRate2400;
    case 3840:
        return CMRate3840;
    case 4800:
        return CMRate4800;
    case 7680:
        return CMRate7680;
    default:
        return CMRateUnknown;
    }
}

//-------------------------------------------------------------------------------------------------------------
ICpriCore::CMRateValue_t CommonCpriCore::getCurrentMaxEthernetRate()
{
    UINT32 tempBitRate = getCurrentEthernetBitRate(20);

    switch(tempBitRate)
    {
    case 21120:
        return CMRate21120;
    case 42240:
        return CMRate42240;
    case 84480:
        return CMRate84480;
    case 105600:
        return CMRate105600;
    case 168960:
        return CMRate168960;
    case 211200:
        return CMRate211200;
    case 337920:
        return CMRate337920;
    default:
        return CMRateUnknown;
    }
}

//-------------------------------------------------------------------------------------------------------------
UINT32 CommonCpriCore::getCurrentEthernetBitRate(UINT32 currentEthernetPointer)
{
    UINT32 bitRate = (64 - currentEthernetPointer) * 4;

    switch (getCurrentLineRate())
    {
        // multiply by the length of the control word in bits
        case Rate614_4:
            bitRate *= 8;
            break;

        case Rate1228_8:
            bitRate *= 16;
            break;

        case Rate2457_6:
            bitRate *= 32;
            break;

        case Rate3072_0:
            bitRate *= 40;
            break;

        case Rate4915_2:
            bitRate *= 64;
            break;

        case Rate6144_0:
            bitRate *= 80;
            break;

        case Rate9830_4:
            bitRate *= 128;
            break;

        case Rate10137_6:
            bitRate *= 128;
            break;

        case RateUnknown:
        default:
            bitRate = 0;
            break;
    }

    bitRate *= 15;

    return bitRate;
}

//-------------------------------------------------------------------------------------------------------------
const char* CommonCpriCore::getStatusCodeString(StatusCode statusCode)
{
    switch (statusCode)
    {
    case RESET:
        return "RESET";
        break;

    case ATTEMPTING_L1_SYNCH:
        return "ATTEMPTING_L1_SYNCH";
        break;

    case PROTOCOL_VERSION_SETUP:
        return "PROTOCOL_VERSION_SETUP";
        break;

    case CM_PARAM_SETUP:
        return "CM_PARAM_SETUP";
        break;

    case PASSIVE_MODE:
        return "PASSIVE_MODE";
        break;

    case OPERATIONAL:
        return "OPERATIONAL";
        break;
    }

    return "INVALID STATUS";
}

//-------------------------------------------------------------------------------------------------------------
const char* ICpriCore::getCurrentLineRateString(LineRate rate)
{
    switch (rate)
    {
    case Rate10137_6:
        return "10137.6";
        break;

    case Rate9830_4:
        return "9830.4";
        break;

    case Rate6144_0:
        return "6144.0";
        break;

    case Rate4915_2:
        return "4915.2";
        break;

    case Rate3072_0:
        return "3072.0";
        break;

    case Rate2457_6:
        return "2457.6";
        break;

    case Rate1228_8:
        return "1228.8";
        break;

    case Rate614_4:
        return "614.4";
        break;

    case RateUnknown:
    default:
        return "LINE RATE UNKNOWN";
        break;

    }

    return "LINE RATE UNKNOWN";
}

//-------------------------------------------------------------------------------------------------------------
char* CommonCpriCore::getLineRateCapabilityString(ICpriCore::LineRateCapability rateCap)
{
    static std::string returnString;

    returnString = "" ;
    if (rateCap.capableOfRate614_4)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("614.4");
    }
    if (rateCap.capableOfRate1228_8)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("1228.8");
    }
    if (rateCap.capableOfRate2457_6)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("2457.6");
    }
    if (rateCap.capableOfRate3072_0)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("3072.0");
    }
    if (rateCap.capableOfRate4915_2)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("4915.2");
    }
    if (rateCap.capableOfRate6144_0)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("6144.0");
    }
    if (rateCap.capableOfRate9830_4)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("9830.4");
    }
    if (rateCap.capableOfRate10137_6)
    {
    	if (!returnString.empty())
    		returnString.append(", ") ;
    	returnString.append("10137.6");
    }

    if (returnString.empty())
    	returnString = "UNKNOWN" ;

    return (char*)returnString.c_str();
}

//-------------------------------------------------------------------------------------------------------------
const char* CommonCpriCore::getCurrentEthernetRateString(CMRateValue ethRate)
{
    switch(ethRate)
    {
    // These are the minimum rate values for each line rate
    case CMRate240:
        return "0.240";
    case CMRate480:
        return "0.480";
    case CMRate960:
        return "0.960";
    case CMRate1920:
        return "1.920";
    case CMRate2400:
        return "2.400";
    case CMRate3840:
        return "3.840";
    case CMRate4800:
        return "4.800";
    case CMRate7680:
        return "7.680";

    // These are the maximum rate values for each line rate
    case CMRate21120:
        return "21.120";
    case CMRate42240:
        return "42.240";
    case CMRate84480:
        return "84.480";
    case CMRate105600:
        return "105.600";
    case CMRate168960:
        return "168.960";
    case CMRate211200:
        return "211.200";
    case CMRate337920:
        return "337.920";
    case CMRateDisabled:
        return "CMRate Disabled";

    case CMRateUnknown:
    default:
        return "CMRateUnknown";
    }

    return "CMRateUnknown";
}

//-------------------------------------------------------------------------------------------------------------
const char* CommonCpriCore::getTxFormatString(TxFormat txFormat)
{
    switch(txFormat)
    {
    case TxFormat_16:
        return "TxFormat_16";
    case TxFormat_9e2:
        return "TxFormat_9e2";
    default:
        return "TxFormat unknown";
    }

    return "TxFormat unknown";
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::showPortStatus(std::ostream& os)
{
    ICpriCore::CpriPortStatus status = getPortStatus();
    char outStr[40];

    ILoggable::logStream(os, "CPRI Port Status:  Fibre connected[%s], active[%s]",
             status.sfpLos ? "NO" : "YES",
             status.active ? "YES" : "NO");
    ILoggable::logStream(os, "    MGT Clocks: PLL[%s], Tx Clock[%s], Rx Clock[%s]",
             status.mgtPllLock ? "LOCK" : "NO LOCK",
             status.mgtTxClockLock ? "LOCK" : "NO LOCK",
             status.mgtRxClockLock ? "LOCK" : "NO LOCK");
    ILoggable::logStream(os, "    LineRate = %s Mbps", getCurrentLineRateString(status.lineRate));
    ILoggable::logStream(os, "    ethernetMinCMBandwidth = %s Mbps", getCurrentEthernetRateString(status.ethernetMinCMBandwidth));
    ILoggable::logStream(os, "    ethernetMaxCMBandwidth = %s Mbps", getCurrentEthernetRateString(status.ethernetMaxCMBandwidth));
    sprintf(outStr, "ethernetBitRate = %3.3f Mbps", (double)getCurrentEthernetBitRate(getCurrentEthernetPointer())/1000.0);
    ILoggable::logStream(os, "    %s", outStr);
    ILoggable::logStream(os, "    remote sapDefect[%s]", status.remoteSapDefect ? "YES" : "NO");
    ILoggable::logStream(os, "    remote lossOfFrame[%s]", status.remoteLossOfFrame ? "YES" : "NO");
    ILoggable::logStream(os, "    remote lossOfSync[%s]", status.remoteLossOfSync ? "YES" : "NO");
    ILoggable::logStream(os, "    remote lossOfFrame[%s]", status.remoteLossOfFrame ? "YES" : "NO");
    ILoggable::logStream(os, "    remote lossOfSync[%s]", status.remoteLossOfSync ? "YES" : "NO");
    ILoggable::logStream(os, "    local lossOfFrame[%s]", status.localLossOfFrame ? "YES" : "NO");
    ILoggable::logStream(os, "    local lossOfSync[%s]", status.localLossOfSync ? "YES" : "NO");
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::changeMode(ICpri::CpriPortType cpriPortType)
{
    bool result = false;

    if (mCoreId != CPRI_SLAVE_CORE && cpriPortType == ICpri::CpriPortSlave)
    {
        logDebugVerbose(
                "%s: on port %d to SLAVE",
                __func__, mFibre );

        // changing to slave port
        mCoreId = CPRI_SLAVE_CORE;
        setMode();  // set the core into Slave mode
        result = true;
    }
    else if (mCoreId != CPRI_MASTER_CORE && cpriPortType == ICpri::CpriPortMaster)
    {
        logDebugVerbose(
                "%s: on port %d to MASTER",
                __func__, mFibre );
        // changing to master port
        mCoreId = CPRI_MASTER_CORE;
        setMode();  // set the core into Slave mode
        result = true;
    }
    else if (mCoreId != CPRI_INACTIVE_CORE && cpriPortType == ICpri::CpriPortInactive)
    {
        logDebugVerbose(
                "%s: on port %d to INACTIVE",
                __func__, mFibre );

        // changing to master port
        mCoreId = CPRI_INACTIVE_CORE;
        result = true;
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::setMode()
{
    if (mCoreId == CPRI_MASTER_CORE)
    {
        logDebugVerbose(
                "%s: on port %d to MASTER",
                __func__, mFibre );

        // master port
        mFpga->cpriSetPortMasterMode(mFibre);
    }
    else
    {
        logDebugVerbose(
                "%s: on port %d to SLAVE",
                __func__, mFibre );

        // slave port
        mFpga->cpriSetPortSlaveMode(mFibre);
    }
}

//-------------------------------------------------------------------------------------------------------------
void CommonCpriCore::defaultCoreInitialisation()
{
    logDebugVerbose(
            "%s: on port %d",
            __func__, mFibre );

    /* Pass this to the fpga
     */
	mFpga->cpriCoreInit(mFibre) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned CommonCpriCore::getPort() const
{
	return mFibre ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isLinkOK(ICpriCore::CpriPortStatus portStatus)
{
    bool linkActive = true;  // be optimistic, the most likely outcome

    /* NOTE: SAP defect Indication (SDI) is not considered a fault that should
     * take down the slave link. The fault handling system will handle the response to all detected faults
     * and may decide to block the Tx as it is an indication that IQ data is potentially invalid.
     *
     * The Master link is considered up if SDI bit is set on master.
     */

    if (!portStatus.logicallyEnabled || !portStatus.active
            || portStatus.remoteLossOfFrame || portStatus.remoteLossOfSync
            || portStatus.localLossOfFrame || portStatus.localLossOfSync
            || !isLineRateSupported(portStatus.lineRate))
    {
        linkActive = false;

        logDebugVerbose(
                "Port %d: Link Not Ok: portStatus: logicallyEnabled[%s]: active[%s]: remoteLossOfFrame[%s]: remoteLossOfSync[%s]: localLossOfFrame[%s]: localLossOfSync[%s]: isLineRateSupported[%s]",
                mFibre,
                portStatus.logicallyEnabled ? "Yes" : "No",
                portStatus.active ? "Yes" : "No",
                portStatus.remoteLossOfFrame ? "Yes" : "No",
                portStatus.remoteLossOfSync ? "Yes" : "No",
                portStatus.localLossOfFrame ? "Yes" : "No",
                portStatus.localLossOfSync ? "Yes" : "No",
                isLineRateSupported(portStatus.lineRate) ? "Yes" : "No");

#ifdef DEBUG_CPRI_CONTROL
        // For debug dump out the current register values
        unsigned addr(0x40000 + (0x1000 * mPort)) ;
        UINT16 rst(mFpga->readRegister(addr + 0x000)) ;
        UINT16 status(mFpga->readRegister(addr + 0x20c)) ;
        UINT16 prefRate(mFpga->readRegister(addr + 0x204)) ;
        UINT16 curRate(mFpga->readRegister(addr + 0x2010)) ;
        logDebugVerbose("Port %d: Rst=0x%04x Stat=0x%04x PrefRate=0x%04x CurRate=0x%04x",
        		mPort, (unsigned)rst, (unsigned)status, (unsigned)prefRate, (unsigned)curRate) ;
#endif
    }

    return linkActive;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCpriCore::isLineRateSupported(ICpriCore::LineRate lineRate)
{
	ICpriCore::LineRateCapability allowableRates(getLineRateCapability()) ;

    // Check if the port rate capabilities match the line rate.

    if (lineRate == ICpriCore::Rate614_4 && allowableRates.capableOfRate614_4)
    	return true ;

    if (lineRate == ICpriCore::Rate1228_8 && allowableRates.capableOfRate1228_8)
    	return true ;

    if (lineRate == ICpriCore::Rate2457_6 && allowableRates.capableOfRate2457_6)
    	return true ;

    if (lineRate == ICpriCore::Rate3072_0 && allowableRates.capableOfRate3072_0)
    	return true ;

    if (lineRate == ICpriCore::Rate4915_2 && allowableRates.capableOfRate4915_2)
    	return true ;

    if (lineRate == ICpriCore::Rate6144_0 && allowableRates.capableOfRate6144_0)
    	return true ;

    if (lineRate == ICpriCore::Rate9830_4 && allowableRates.capableOfRate9830_4)
    	return true ;

    if (lineRate == ICpriCore::Rate10137_6 && allowableRates.capableOfRate10137_6)
    	return true ;

    return false;
}
