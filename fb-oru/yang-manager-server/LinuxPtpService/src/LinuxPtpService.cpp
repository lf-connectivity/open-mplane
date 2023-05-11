/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LinuxPtpService.cpp
 * \brief     interface to the Linux PTP application
 *
 *
 * \details   The interface is responsible for starting Linux PTP application,
 *            monitoring it, configuring data to be used by the PTP application and reading
 *            the PTP synchronisation status
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

#include "LinuxPtpService.h"
#include "stringfunc.hpp"
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "IPacketSniffer.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::string LinuxPtp::mPmcCommand("pmc");
const std::string LinuxPtp::mPtpStartCommand("ptp4l");
const std::string LinuxPtp::mPtpConfFile("/etc/network/ptp.conf");
const std::string LinuxPtp::mPtpProcessOutputFile("/tmp/ptpOutput.txt");
const std::string LinuxPtp::mPmcResponseTxtStr("/tmp/pmcResponse.txt");
const std::string LinuxPtp::mFindLinuxPtpProcessStr = "ps -aux | grep \"ptp4l\" > /tmp/ptp4lProcess.txt";
const std::string LinuxPtp::mQuickFindLinuxPtpProcessStr = "ps -aux | grep \"ptp4l\" -c > /tmp/ptp4lProcess.txt";
const std::string LinuxPtp::mServerProcessTxtStr = "/tmp/ptp4lProcess.txt";
const std::string LinuxPtp::mRmsStr = "rms";
const int LinuxPtp::mPtpRmsThreshold = 20;
const unsigned int LinuxPtp::mNumConsecutiveRmsChecks = 3;
const unsigned int LinuxPtp::mParamsRefreshMs(1000);
const std::map<LinuxPtp::MulticastMACAddr_T, std::string> LinuxPtp::mMacAddr = {
		{MulticastMACAddr_T::MAC_FORWARDABLE, "01:1B:19:00:00:00"},
		{MulticastMACAddr_T::MAC_NONFORWARDABLE, "01-80-C2-00-00-0E"},
};
const unsigned int LinuxPtp::mPtpTimeoutMs(30000);
const unsigned int LinuxPtp::mAirframeLockTimeoutMs(3000);
const std::vector<std::string> LinuxPtp::mPmcCommandsToSend = {
		"CURRENT_DATA_SET",
		"DEFAULT_DATA_SET",
		"PARENT_DATA_SET",
		"TIME_PROPERTIES_DATA_SET"
};

// SSM code mapping. ST3 value is same as EEC2, so it is not included as a separate entry
// TNC code conflicts with SSU-A (both encoded as 0x04). But it is not required by o-ran-sync and hence it is excluded for now
// The conflict can be resolved if we know the network option of the clock. TNC code is sent only in option 2 networks whilst
// SSU-A code is sent only in option 1 networks. So we can encode the SSM correctly if we know the network option.
// Refer http://twiki/twiki/pub/Engineering/OranSPlane/T-REC-G.8264-201708-IPDF-E.pdf for the mapping
const std::map<unsigned char, ILinuxPtpConfig::SsmCodes_T> LinuxPtp::mSSMMapping =
{
	{0x02, ILinuxPtpConfig::PRC},
	{0x04, ILinuxPtpConfig::SSU_A},
	{0x08, ILinuxPtpConfig::SSU_B},
	{0x0B, ILinuxPtpConfig::EEC1},
	{0x01, ILinuxPtpConfig::PRS},
	{0x07, ILinuxPtpConfig::ST2},
	{0x0D, ILinuxPtpConfig::ST3E},
	{0x0A, ILinuxPtpConfig::EEC2},
};

const std::map<ILinuxPtpConfig::SsmCodes_T, std::string> LinuxPtp::mSsmCodeToStr =
{
	{ILinuxPtpConfig::PRC, "PRC"},
	{ILinuxPtpConfig::PRS, "PRS"},
	{ILinuxPtpConfig::SSU_A, "SSU_A"},
	{ILinuxPtpConfig::SSU_B, "SSU_B"},
	{ILinuxPtpConfig::ST2, "ST2"},
	{ILinuxPtpConfig::ST3, "ST3"},
	{ILinuxPtpConfig::ST3E, "ST3E"},
	{ILinuxPtpConfig::EEC1, "EEC1"},
	{ILinuxPtpConfig::EEC2, "EEC2"},
	{ILinuxPtpConfig::DNU, "DNU"},
	{ILinuxPtpConfig::NONE, "NONE"}
};

const unsigned char LinuxPtp::ESMC_PDU_DA[] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x02};
const unsigned char LinuxPtp::ESMC_PDU_ETHER_TYPE[] = {0x88, 0x09};
const unsigned char LinuxPtp::ESMC_PDU_SLOW_PROTOCOL_SUBTYPE = 0x0A;
const unsigned char LinuxPtp::ESMC_PDU_ITU_OUI[] = {0x00, 0x19, 0xA7};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::LinuxPtp() : Service(SERVICE_MEDIUM_PRIORITY,
								SMALL_STACK,
								1000, // update stuff every 1000 msec
								"LinuxPtpService",
								"LINUXPTP"),
#ifdef TEST_PTP_NOTIFICATION
								mTestLockStatus(LockStatus_T::NOT_LOCKED),
#endif
								mGpsTickEnableTime(),
								mPtpStartTime(),
								mSsmMutex(),
								mDataMutex(),
								mEthbbInterfaceName(),
								mEthInterfaceNumber(),
								mInterfaceReady(false),
								mDomainNumber(),
								mMultiMacAddr(),
								mMaxAcceptableClockClass(),
								mPtpConfUpdated(false),
								mNumRmsChecksPassed(0),
								mLastUpdate(),
								mParamsReadOnce(false),
								mPtpLockChangeFunc(),
								mAirframeLockChangeFunc(),
								mPtpLockStatus(LockStatus_T::NOT_LOCKED),
								mPrevPtpLockStatus(LockStatus_T::NOT_LOCKED),
								mAirframeLockStatus(LockStatus_T::NOT_LOCKED),
								mPrevAirframeLockStatus(LockStatus_T::NOT_LOCKED),
								mConfiguredSsmCode(),
								mSsmStatus(SSM_CODE_NOT_RECEIVED),
								mSsmMismatchDetected(false),
								mSynceLockChangeFunc(),
								mSynceLockStatus(LockStatus_T::NOT_LOCKED),
								mPrevSynceLockStatus(LockStatus_T::NOT_LOCKED),
								mSsmTimeoutSec(SSM_DEFAULT_TIMEOUT_SEC),
								mSynceSourceStatus(),
								mRuClockClass(),
								mRuClockIdentity(),
								mPtpSourceStatus(),
								mServiceState(LinuxPtpServiceState::WAIT_FOR_INTERFACE),
								mPtpProcessResult(),
								mPtpResponseData()
{
	mEthbbInterfaceName = IAppOptions::getInstance()->getOption("ethbb").toString() ;

	// Network services access
	auto ns(INetworkingService::singleton(mEthbbInterfaceName));
	auto policy(ns->getNetAddrPolicy());

	mEthInterfaceNumber = policy->interfacePort() ;

	// Write default parameters
	mDomainNumber = 24;
	mMultiMacAddr = mMacAddr.at(MulticastMACAddr_T::MAC_FORWARDABLE);
	mPtpSourceStatus.mState = SourceState_T::DISABLED;
	mMaxAcceptableClockClass = 7;

	// Populate PMC response information
	mPmcResponseInfo.push_back({"clockClass",                 &mRuClockClass,                              PmcParamType_E::UINT8_DEC});
	mPmcResponseInfo.push_back({"clockIdentity",              &mRuClockIdentity,                           PmcParamType_E::STRING});
	mPmcResponseInfo.push_back({"twoStepFlag",                &mPtpSourceStatus.mTwoStepFlag,              PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"leap61",                     &mPtpSourceStatus.mLeap61,                   PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"leap59",                     &mPtpSourceStatus.mLeap59,                   PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"currentUtcOffset",           &mPtpSourceStatus.mCurrentUtcOffset,         PmcParamType_E::UINT16_DEC});
	mPmcResponseInfo.push_back({"currentUtcOffsetValid",      &mPtpSourceStatus.mCurrentUtcOffsetValid,    PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"ptpTimescale",               &mPtpSourceStatus.mPtpTimescale,             PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"timeTraceable",              &mPtpSourceStatus.mTimeTraceable,            PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"frequencyTraceable",         &mPtpSourceStatus.mFreqTraceable,            PmcParamType_E::BOOL});
	mPmcResponseInfo.push_back({"timeSource",                 &mPtpSourceStatus.mTimeSource,               PmcParamType_E::UINT8_HEX});
	mPmcResponseInfo.push_back({"stepsRemoved",               &mPtpSourceStatus.mStepsRemoved,             PmcParamType_E::UINT16_DEC});
	mPmcResponseInfo.push_back({"grandmasterPriority1",       &mPtpSourceStatus.mPriority1,                PmcParamType_E::UINT8_DEC});
	mPmcResponseInfo.push_back({"grandmasterPriority2",       &mPtpSourceStatus.mPriority2,                PmcParamType_E::UINT8_DEC});
	mPmcResponseInfo.push_back({"gm.ClockClass",              &mPtpSourceStatus.mClockClass,               PmcParamType_E::UINT8_DEC});
	mPmcResponseInfo.push_back({"gm.ClockAccuracy",           &mPtpSourceStatus.mClockAccuracy,            PmcParamType_E::UINT8_HEX});
	mPmcResponseInfo.push_back({"gm.OffsetScaledLogVariance", &mPtpSourceStatus.mOffsetScaledLogVariance,  PmcParamType_E::UINT16_HEX});
	mPmcResponseInfo.push_back({"grandmasterIdentity",        &mPtpSourceStatus.mGrandmasterIdentity,      PmcParamType_E::STRING});
	mPmcResponseInfo.push_back({"parentPortIdentity",         &mPtpSourceStatus.mSourceClockIdentity,      PmcParamType_E::STRING});

	// Update the networking service - add a callback for interface up
	ns->pause() ;

	policy->registerUpFunc([this](void){
		mInterfaceReady = true;
		std::cerr << "LinuxPtp: Ethbb interface up" << std::endl ;
	}) ;

	policy->registerDownFunc([this](void){
		mInterfaceReady = false;
		std::cerr << "LinuxPtp: Ethbb interface down" << std::endl ;
	}) ;

	ns->restart() ;

	std::shared_ptr<IPacketSniffer> sniffer = IPacketSniffer::singleton(mEthbbInterfaceName);
	sniffer->registerPacketCbFunc("ether multicast", [this](
			const struct pcap_pkthdr * header, const unsigned char* packet, unsigned int len){
		packetCallback(header, packet, len);
	});

	mSynceSourceStatus.mQualityLevel = 0;
	mSynceSourceStatus.mState = SourceState_T::DISABLED;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::~LinuxPtp()
{
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::initialise(void)
{
	// Write the default PTP configuration file
	writePtpConf();
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::isPtpRunning(void)
{
	return (mServiceState != AIRFRAME_LOCKED &&
			mServiceState != PTP_FAILED &&
			mServiceState != WAIT_FOR_INTERFACE &&
			mServiceState != WAIT_FOR_ESMC);
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getSfpEthPortNumber(void)
{
	return mEthInterfaceNumber;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::LockStatus_T LinuxPtp::getPtpLockStatus(void)
{
	return mPtpLockStatus;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::LockStatus_T LinuxPtp::getAirframeLockStatus(void)
{
	return mAirframeLockStatus;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getRuClockClass(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mRuClockClass;
}

//-------------------------------------------------------------------------------------------------------------
std::string LinuxPtp::getRuClockIdentity(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mRuClockIdentity;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::SourceState_T LinuxPtp::getPtpSourceState(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mState;
}

//-------------------------------------------------------------------------------------------------------------
std::string LinuxPtp::getSourceStateStr(SourceState_T state)
{
	std::string str = "DISABLED";
	switch (state)
	{
	case SourceState_T::DISABLED:
		str = "DISABLED";
		break;

	case SourceState_T::NOK:
		str = "NOK";
		break;

	case SourceState_T::OK:
		str = "OK";
		break;

	case SourceState_T::PARENT:
		str = "PARENT";
		break;

	default:
		break;
	}

	return str;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getTwoStepFlag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mTwoStepFlag;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getLeap61Flag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mLeap61;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getLeap59Flag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mLeap59;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getCurrentUtcOffsetValidFlag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mCurrentUtcOffsetValid;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getPtpTimescaleFlag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mPtpTimescale;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getTimeTraceableFlag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mTimeTraceable;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::getFrequencyTraceableFlag(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mFreqTraceable;
}

//-------------------------------------------------------------------------------------------------------------
std::string LinuxPtp::getSourceClockIdentity(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mSourceClockIdentity;
}

//-------------------------------------------------------------------------------------------------------------
uint16_t LinuxPtp::getSourcePortNumber(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mSourcePortNumber;
}

//-------------------------------------------------------------------------------------------------------------
uint16_t LinuxPtp::getCurrentUtcOffset(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mCurrentUtcOffset;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getPriority1(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mPriority1;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getSourceClockClass(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mClockClass;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getClockAccuracy(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mClockAccuracy;
}

//-------------------------------------------------------------------------------------------------------------
uint16_t LinuxPtp::getoffsetScaledLogVariance(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mOffsetScaledLogVariance;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getPriority2(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mPriority2;
}

//-------------------------------------------------------------------------------------------------------------
std::string LinuxPtp::getGMClockIdentity(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mGrandmasterIdentity;
}

//-------------------------------------------------------------------------------------------------------------
uint16_t LinuxPtp::getStepsRemoved(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mStepsRemoved;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getTimeSource(void)
{
	std::unique_lock<std::mutex> guard2(mDataMutex);
	updateParams(false);
	return mPtpSourceStatus.mTimeSource;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::LockStatus_T LinuxPtp::getSynceLockStatus(void)
{
	return mSynceLockStatus;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::SourceState_T LinuxPtp::getSynceSourceState(void)
{
	std::unique_lock<std::mutex> guard1(mSsmMutex);

	if (mSynceLockStatus == LockStatus_T::LOCKED)
	{
		mSynceSourceStatus.mState = SourceState_T::PARENT;
	}
	else if (mSsmStatus == SSM_CODE_RECEIVED)
	{
		mSynceSourceStatus.mState = SourceState_T::NOK;
	}
	else
	{
		mSynceSourceStatus.mState = SourceState_T::DISABLED;
	}

	return mSynceSourceStatus.mState;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getSsmQualityLevel(void)
{
	std::unique_lock<std::mutex> guard1(mSsmMutex);

	return mSynceSourceStatus.mQualityLevel;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::setDomainNumber(uint8_t domainNum)
{
	if (mDomainNumber != domainNum)
	{
		mDomainNumber = domainNum;

		// The PTP configuration has changed. Signal to the service state machine.
		mPtpConfUpdated = true;
		mNotify.signal();
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::setMulticastMac(MulticastMACAddr_T mac)
{
	std::string newAddr = mMacAddr.at(mac);
	if (newAddr != mMultiMacAddr)
	{
		mMultiMacAddr = newAddr;

		// The PTP configuration has changed. Signal to the service state machine.
		mPtpConfUpdated = true;
		mNotify.signal();
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
uint8_t LinuxPtp::getMaxAcceptableClockClass(void)
{
	return mMaxAcceptableClockClass;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::setAcceptableSsmCode(SsmCodes_T ssm, bool add)
{
	if (ssm == ILinuxPtpConfig::ST3)
	{
		ssm = ILinuxPtpConfig::EEC2;
	}
	if (add)
	{
		mConfiguredSsmCode.insert(ssm);
	}
	else
	{
		mConfiguredSsmCode.erase(ssm);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::setSsmTimeout(uint16_t timeout)
{
	mSsmTimeoutSec = timeout;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
std::string LinuxPtp::getSsmStrFromCode(SsmCodes_T code)
{
	std::string str = "NONE";

	if (mSsmCodeToStr.find(code) != mSsmCodeToStr.end())
	{
		str = mSsmCodeToStr.at(code);
	}
	return str;
}

//-------------------------------------------------------------------------------------------------------------
LinuxPtp::SsmCodes_T LinuxPtp::getSsmCodeFromStr(std::string str)
{
	LinuxPtp::SsmCodes_T code = LinuxPtp::SsmCodes_T::NONE;

	for (auto& entry : mSsmCodeToStr)
	{
		if (entry.second == str)
		{
			code = entry.first;
			break;
		}
	}

	return code;
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::registerPtpStatusFunc(LockStatusChangeFunc func)
{
	mPtpLockChangeFunc.push_back(func);
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::registerAirframeStatusFunc(LockStatusChangeFunc func)
{
	mAirframeLockChangeFunc.push_back(func);
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::registerSynceStatusFunc(LockStatusChangeFunc func)
{
	mSynceLockChangeFunc.push_back(func);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::show()
{
	eventInfo("LinuxPtpService::show()");
}

//-------------------------------------------------------------------------------------------------------------
int LinuxPtp::service()
{
	// Check if the PTP configuration has changed and restart the PTP application
	if (mPtpConfUpdated && (isPtpRunning() == false))
	{
		// Update the PTP configuration
		writePtpConf();

		// If SYNCE is not locked, then wait for ESMC PDU
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			if (mInterfaceReady)
			{
				eventInfo("LinuxPTPState : PTP_START");
				mServiceState = PTP_START;
			}
			else
			{
				eventInfo("LinuxPTPState : WAIT_FOR_INTERFACE");
				mServiceState = WAIT_FOR_INTERFACE;
			}
		}
		mPtpConfUpdated = false;
	}

	switch (mServiceState)
	{
	case WAIT_FOR_INTERFACE:
	{
		if (mInterfaceReady)
		{
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
	}
	break;

	case WAIT_FOR_ESMC:
	{
		bool ssmCodeAccepted = false;
		{
			std::unique_lock<std::mutex> guard1(mSsmMutex);

			ssmCodeAccepted = isSsmCodeAccepted();
		}
		// Check if SSM code is received and accepted
		if (ssmCodeAccepted)
		{
			mSynceLockStatus = LockStatus_T::LOCKED;
			eventInfo("LinuxPTPState : PTP_START");
			mServiceState = PTP_START;
		}
	}
	break;

	case PTP_START:
	{
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			// Start the PTP application
			if (startPtp())
			{
				eventInfo("LinuxPTPState : DETECT_PTP_LOCK_STATUS");
				mServiceState = DETECT_PTP_LOCK_STATUS;
				mPtpStartTime = std::chrono::system_clock::now();
				mNumRmsChecksPassed = 0;
			}
			else
			{
				eventInfo("LinuxPTPState : PTP_FAILED");
				mServiceState = PTP_FAILED;
				stopPtp();
			}
		}
	}
	break;

	case DETECT_PTP_LOCK_STATUS:
	{
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			stopPtp();
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			// Check if the PTP is synchronised
			if (prelockRmsValueCheck())
			{
				eventInfo("LinuxPTPState : PTP_LOCKED");
				mServiceState = PTP_LOCKED;
			}
			else
			{
				// If timeout is elapsed, then PTP has failed
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

				if (std::chrono::duration_cast<std::chrono::milliseconds>(now - mPtpStartTime).count() >= mPtpTimeoutMs)
				{
					eventInfo("LinuxPTPState : PTP_FAILED");
					mServiceState = PTP_FAILED;
					stopPtp();
				}
			}
		}
	}
	break;

	case PTP_LOCKED:
	{
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			stopPtp();
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			// Lock the airframe
			auto fpga = IFpgaMgr::getIFpgaSystemRegs();

			// Set the enable bit
			fpga->write_Sync_GpsTickEna_Bit(1);

			mGpsTickEnableTime = std::chrono::system_clock::now();

			eventInfo("LinuxPTPState : DETECT_AIRFRAME_LOCK");
			mServiceState = DETECT_AIRFRAME_LOCK;
		}
	}
	break;

	case DETECT_AIRFRAME_LOCK:
	{
		auto fpga = IFpgaMgr::getIFpgaSystemRegs();

		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			// reset the enable bit
			fpga->write_Sync_GpsTickEna_Bit(0);

			stopPtp();
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			unsigned lockBit = fpga->read_Sync_GpsTickLock_Bit();

			// If lock bit is set, then check the RMS post lock condition
			if (lockBit)
			{
				// reset the enable bit
				fpga->write_Sync_GpsTickEna_Bit(0);

				eventInfo("LinuxPTPState : CHECK_POST_PTP_LOCK_STATUS");
				mServiceState = CHECK_POST_PTP_LOCK_STATUS;
			}
			else
			{
				// If timeout is elapsed, then PTP has failed
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

				// If airframe lock timeout has not elapsed, then wait
				if (std::chrono::duration_cast<std::chrono::milliseconds>(now - mGpsTickEnableTime).count() >= mAirframeLockTimeoutMs)
				{
					// reset the enable bit
					fpga->write_Sync_GpsTickEna_Bit(0);

					if (std::chrono::duration_cast<std::chrono::milliseconds>(now - mPtpStartTime).count() >= mPtpTimeoutMs)
					{
						eventInfo("LinuxPTPState : PTP_FAILED");
						mServiceState = PTP_FAILED;
						stopPtp();
					}
					// Else try to lock PTP all over again
					else
					{
						eventInfo("LinuxPTPState : DETECT_PTP_LOCK_STATUS");
						mNumRmsChecksPassed = 0;
						mServiceState = DETECT_PTP_LOCK_STATUS;
					}

					eventWarning("Not able to lock airframe");
				}
			}
		}
	}
	break;

	case CHECK_POST_PTP_LOCK_STATUS:
	{
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			stopPtp();
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			// Check that the RMS value is still less than the threshold
			int rmsValue = getRmsValue();
			// Check if RMS value is still less than the threshold
			if (rmsValue >= 0 && rmsValue <= mPtpRmsThreshold)
			{
				eventInfo("LinuxPTPState : AIRFRAME_LOCKED");
				mServiceState = AIRFRAME_LOCKED;
				{
					std::unique_lock<std::mutex> guard1(mDataMutex);
					updateParams(true);
				}
				stopPtp();
			}
			else
			{
				eventWarning("Post PTP lock RMS check failed");

				// If timeout is elapsed, then PTP has failed
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

				if (std::chrono::duration_cast<std::chrono::milliseconds>(now - mPtpStartTime).count() >= mPtpTimeoutMs)
				{
					eventInfo("LinuxPTPState : PTP_FAILED");
					mServiceState = PTP_FAILED;
					stopPtp();
				}
				// Else try to lock PTP all over again
				else
				{
					mNumRmsChecksPassed = 0;
					eventInfo("LinuxPTPState : DETECT_PTP_LOCK_STATUS");
					mServiceState = DETECT_PTP_LOCK_STATUS;
				}
			}
		}
	}
	break;

	case AIRFRAME_LOCKED:
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		break;

	case PTP_FAILED:
	{
		// If SYNCE loses lock, then stop PTP sync
		if (mSynceLockStatus == LockStatus_T::NOT_LOCKED)
		{
			eventInfo("LinuxPTPState : WAIT_FOR_ESMC");
			mServiceState = WAIT_FOR_ESMC;
		}
		else
		{
			// Restart PTP till we get a lock
			if (mInterfaceReady)
			{
				eventInfo("LinuxPTPState : PTP_START");
				mServiceState = PTP_START;
			}
			else
			{
				eventInfo("LinuxPTPState : WAIT_FOR_INTERFACE");
				mServiceState = WAIT_FOR_INTERFACE;
			}
		}
	}
	break;

	default:
		break;
	}

	// Keep monitoring SYNCE status
	monitorSynceStatus();

	// Monitor PTP status
	monitorPtpStatus();

	// Monitor Airframe status
	monitorAirframeStatus();

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
// Warning! This function won't do anything as the base class function has not been overridden
void LinuxPtp::doReset()
{

}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::startPtp(void)
{
	eventInfo("LinuxPtpService::startPtp()");

	std::string cmd;

	// Create the PTP start command and redirect output to a file
	cmd = mPtpStartCommand + " -i " + mEthbbInterfaceName +
			" -m -f " + mPtpConfFile + " > " + mPtpProcessOutputFile + " &";

	int processReturn = system(cmd.c_str());

	// Check to see if the command was successful
	if (processReturn == 0)
	{
		// Open the file that contains the PTP output log
		mPtpProcessResult.open(mPtpProcessOutputFile, std::ios::in);
		return true;
	}
	else
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::stopPtp(void)
{
	eventInfo("LinuxPtpService::stopPtp()");

	bool returnValue = true;

	int processRunningReturn = system(mQuickFindLinuxPtpProcessStr.c_str());

	// Check to see if the command was successful
	if (0 == processRunningReturn)
	{
		std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

		if (serverProcessTxtFile.is_open())
		{
			std::string numberFoundStr = "\0";

			std::getline(serverProcessTxtFile, numberFoundStr);

			unsigned long int numberFound = std::strtoul(numberFoundStr.c_str(), 0, 10);

			// If the process is running then we will find two entries - the process and the grep for it!
			if (numberFound > 2)
			{
				int processFindReturn = system(mFindLinuxPtpProcessStr.c_str());

				// Check to see if the command was successful
				if(0 == processFindReturn)
				{
					std::ifstream serverProcessTxtFile(mServerProcessTxtStr.c_str());

					if(serverProcessTxtFile.is_open())
					{
						std::string processStr = "\0";

						std::getline(serverProcessTxtFile, processStr);

						std::vector<std::string> fields(splitStr(processStr));
						if (fields.size() >= 2)
						{
							std::string killCommand = "kill -9 " + fields[1];

							int killProcessReturn = system(killCommand.c_str());

							if(0 == killProcessReturn)
							{
								returnValue = true;
							}
							else
							{
								// Kill failed
								eventError("LinuxPtpService::stopPtp() - process kill failed");
								returnValue = false;
							}
						}
					}
					else
					{
						// Could not open process file
						eventError("LinuxPtpService::stopPtp() - could not open process file");
						returnValue = false;
					}

					// Clean up after ourselves
					serverProcessTxtFile.close();
				}
				else
				{
					// Find LinuxPtp process failed
					eventError("LinuxPtpService::stopPtp() - find LinuxPtp process failed");
					returnValue = false;
				}
			}
			else
			{
				// Process is already dead!
				eventWarning("LinuxPtpService::stopPtp() - Process is already dead!");
			}
		}
		else
		{
			// Cannot open quick find file
			eventError("LinuxPtpService::stopPtp() - quick find could not open process file");
			returnValue = false;
		}

		// Close the file we opened
		serverProcessTxtFile.close();
	}
	else
	{
		// Quick find system command failed
		eventError("LinuxPtpService::stopPtp() - quick find system command failed");
		returnValue = false;
	}

	// Remove the file we created
	std::remove(mServerProcessTxtStr.c_str());

	// Close the process output log
	mPtpProcessResult.close();

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::writePtpConf(void)
{
	std::ofstream ptpConf(mPtpConfFile, std::ofstream::out);

	if (!ptpConf.is_open())
	{
		return false;
	}

	ptpConf << "[global]" << std::endl;
	ptpConf << "verbose\t1" << std::endl;
	ptpConf << "time_stamping\thardware" << std::endl;
	ptpConf << "logAnnounceInterval\t-3" << std::endl;
	ptpConf << "logSyncInterval\t-4" << std::endl;
	ptpConf << "logMinDelayReqInterval\t-4" << std::endl;
	ptpConf << "slaveOnly\t1" << std::endl;
	ptpConf << "domainNumber\t" << (unsigned int)mDomainNumber << std::endl;
#ifdef OFF_TARGET
	ptpConf << "[em" << (unsigned int)mEthInterfaceNumber << "]" << std::endl;
#else
	ptpConf << "[eth" << (unsigned int)mEthInterfaceNumber << "]" << std::endl;
#endif
	ptpConf << "network_transport\tL2" << std::endl;
	ptpConf << "ptp_dst_mac\t" << mMultiMacAddr << std::endl;
	ptpConf << "announceReceiptTimeout\t20" << std::endl;

	ptpConf.close();

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::sendPmcCommands(void)
{
	std::string cmd;
	std::ifstream pmcResponse;

	// Create the pmc command and redirect output to a file
	cmd = mPmcCommand + " -u -i " + mEthbbInterfaceName + " -d " + std::to_string(mDomainNumber);

	for (auto & commandName : mPmcCommandsToSend)
	{
		// Create the pmc command and redirect output to a file
		cmd += " 'GET " + commandName + "' ";
	}

	cmd += " > " + mPmcResponseTxtStr;

	int processReturn = system(cmd.c_str());

	// Check to see if the command was successful
	if (processReturn == 0)
	{
		// Open the file that contains the pmc response
		pmcResponse.open(mPmcResponseTxtStr, std::ios::in);
		if (pmcResponse.is_open())
		{
			// Parse each line in the response
			std::string line;
			while (std::getline(pmcResponse, line))
			{
				// Separate the line with whitespace as delimiter
				std::vector<std::string> fields(splitStr(line));

				// If 2 strings are found, then add them to the map
				if (fields.size() == 2)
				{
					mPtpResponseData[fields[0]] = fields[1];
				}

				fields.clear();
			}

			// Close the file
			pmcResponse.close();
		}
	}
	// Remove the temporary file
	std::remove(mPmcResponseTxtStr.c_str());

	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int LinuxPtp::getRmsValue(void)
{
	std::string line;

	while (std::getline(mPtpProcessResult, line))
	{
		size_t pos = line.find(mRmsStr);
		if (pos != std::string::npos)
		{
			std::string rmsLine = line.substr(pos);
			std::vector<std::string> fields(splitStr(rmsLine));
			// Skip big numbers
			if (fields.size() >= 2 && fields[1].size() <= 4)
			{
				int rmsValue = std::stoi(fields[1]);
				eventInfo("rms value = %i", rmsValue);
				return rmsValue;
			}
			else
			{
				return -1;
			}
		}
	}

	mPtpProcessResult.clear();
	return -1;
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::prelockRmsValueCheck(void)
{
	int rmsValue;

	do
	{
		rmsValue = getRmsValue();
		if (rmsValue < 0)
		{
			return false;
		}
		else
		{
			// Look for three consecutive rms values less
			// than or equal to the threshold
			if (rmsValue <= mPtpRmsThreshold)
			{
				if (++mNumRmsChecksPassed == mNumConsecutiveRmsChecks)
				{
					eventInfo( "3 consecutive rms values below 20 ns found ");
					return true;
				}
			}
			else
			{
				mNumRmsChecksPassed = 0;
			}
		}
	} while (rmsValue >= 0); // end while

	return false;

}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::updateParams(bool force)
{
	// Check the last time the parameters were read
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// If the values are old or the force flag is true, then
	// Get all parameters using the pmc command
	if (mParamsReadOnce == false || force == true ||
		(std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastUpdate).count() >= mParamsRefreshMs &&
		 isPtpRunning() == true))
	{
		eventInfo("PTP parameters read, flag : %s", force ? "1" : "0");

		mParamsReadOnce = true;
		mLastUpdate = now;

		mPtpResponseData.clear();
		sendPmcCommands();

		for (auto & elem : mPmcResponseInfo)
		{
			// Populate element
			if (mPtpResponseData.find(elem.mKeyword) != mPtpResponseData.end())
			{
				try
				{
					switch (elem.mType)
					{
					case PmcParamType_E::UINT8_DEC:
						*(static_cast<uint8_t*>(elem.mData)) = std::stoul(mPtpResponseData[elem.mKeyword]);
						break;

					case PmcParamType_E::UINT8_HEX:
						*(static_cast<uint8_t*>(elem.mData)) = std::stoul(mPtpResponseData[elem.mKeyword], 0, 16);
						break;

					case PmcParamType_E::UINT16_DEC:
						*(static_cast<uint16_t*>(elem.mData)) = std::stoul(mPtpResponseData[elem.mKeyword]);
						break;

					case PmcParamType_E::UINT16_HEX:
						*(static_cast<uint16_t*>(elem.mData)) = std::stoul(mPtpResponseData[elem.mKeyword], 0, 16);
						break;

					case PmcParamType_E::STRING:
						*(static_cast<std::string*>(elem.mData)) = mPtpResponseData[elem.mKeyword];
						break;

					case PmcParamType_E::BOOL:
						*(static_cast<bool*>(elem.mData)) = ((std::stoul(mPtpResponseData[elem.mKeyword]) != 0) ? true : false);
						break;
					}
				}
				catch(const std::exception &ex)
				{
					std::cerr << "Cannot read " << elem.mKeyword << " : " << ex.what() << std::endl;
				}
			}
		}

		// Populate source-port-number
		// TODO populated as 0 for now. Need to find out which field to use for this.
		mPtpSourceStatus.mSourcePortNumber = 0;
	}

	// Set the PTP source state
	if (mServiceState == LinuxPtpServiceState::AIRFRAME_LOCKED)
	{
		if (mPtpSourceStatus.mClockClass <= mMaxAcceptableClockClass)
		{
			mPtpSourceStatus.mState = SourceState_T::PARENT;
		}
		else
		{
			mPtpSourceStatus.mState = SourceState_T::NOK;
		}
	}
	else
	{
		mPtpSourceStatus.mState = SourceState_T::DISABLED;
	}
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::packetCallback(const struct pcap_pkthdr * header, const unsigned char* packet, unsigned int len)
{
	if (len >= IPacketSniffer::SIZE_ETHERNET + ITU_HEADER_LEN + QL_TLV_LEN)
	{
		// Check if the destination ethernet address is the multicast MAC address for alow protocols
		const IPacketSniffer::sniff_ethernet *eth;
		eth = (IPacketSniffer::sniff_ethernet*) packet;
		if (eth->ether_dhost[0] == ESMC_PDU_DA[0] &&
			eth->ether_dhost[1] == ESMC_PDU_DA[1] &&
			eth->ether_dhost[2] == ESMC_PDU_DA[2] &&
			eth->ether_dhost[3] == ESMC_PDU_DA[3] &&
			eth->ether_dhost[4] == ESMC_PDU_DA[4] &&
			eth->ether_dhost[5] == ESMC_PDU_DA[5] &&
			eth->ether_type[0] == ESMC_PDU_ETHER_TYPE[0] &&
			eth->ether_type[1] == ESMC_PDU_ETHER_TYPE[1])
		{
			const itu_t_header *ituHeader;
			ituHeader = (itu_t_header*) (packet + IPacketSniffer::SIZE_ETHERNET);

			// Check if the ITU header is as expected for the ESMC PDU
			if (ituHeader->slow_protocol_subtype == ESMC_PDU_SLOW_PROTOCOL_SUBTYPE &&
			    ituHeader->itu_oui[0] == ESMC_PDU_ITU_OUI[0] &&
				ituHeader->itu_oui[1] == ESMC_PDU_ITU_OUI[1] &&
				ituHeader->itu_oui[2] == ESMC_PDU_ITU_OUI[2])
			{
				std::unique_lock<std::mutex> guard1(mSsmMutex);

				const unsigned char* data = packet + IPacketSniffer::SIZE_ETHERNET + ITU_HEADER_LEN;

				// Check if QL TLV is received
				if (data[0] == QL_TYPE &&
					data[1] == 0x00 &&
					data[2] == QL_LEN)
				{
					// Get the SSM code
					mSynceSourceStatus.mQualityLevel = data[3] & SSM_CODE_MASK;

					// Check if the SSM code is found in the SSM mapping table
					if (mSSMMapping.find(mSynceSourceStatus.mQualityLevel) != mSSMMapping.end())
					{
						mReceivedSsmCode = mSSMMapping.at(mSynceSourceStatus.mQualityLevel);
						mSsmStatus = SSM_CODE_RECEIVED;
					}
					else
					{
						mSsmStatus = SSM_CODE_INVALID;
					}

					// Record the timestamp
					mLastEsmcReceived = std::chrono::system_clock::now();
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::monitorSynceStatus(void)
{
	if (mServiceState != WAIT_FOR_INTERFACE &&
		mServiceState != WAIT_FOR_ESMC)
	{
		std::unique_lock<std::mutex> guard1(mSsmMutex);

		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		// Check if the ESMC PDU timed out
		if (std::chrono::duration_cast<std::chrono::seconds>(now -
				mLastEsmcReceived).count() >= ESMC_PDU_TIMEOUT_SEC)
		{
			eventWarning("ESMC PDU timeout, SYNCE will be unlocked");
			mSsmStatus = SSM_CODE_TIMEOUT;

			// set syncelockstatus as not locked
			mSynceLockStatus = LockStatus_T::NOT_LOCKED;
		}

		// Check if SSM code is received and accepted
		// Any change in the condition for SSM code acceptance causes the Lock lost timer to start
		if (isSsmCodeAccepted() == false)
		{
			// If timer not started, then start timer
			if (mSsmMismatchDetected == false)
			{
				eventWarning("SSM code invalid, %s second timer started", std::to_string(mSsmTimeoutSec).c_str());
				mSsmMismatchDetected = true;
				mSsmLockLostStartTime = now;
			}
			else
			{
				// If timer elapses then set syncelockstatus as not locked
				if (std::chrono::duration_cast<std::chrono::seconds>(now -
						mSsmLockLostStartTime).count() >= mSsmTimeoutSec)
				{
					eventWarning("SSM code invalid for %s seconds, SYNCE will be unlocked", std::to_string(mSsmTimeoutSec).c_str());

					mSynceLockStatus = LockStatus_T::NOT_LOCKED;
				}
			}
		}
		else
		{
			mSsmMismatchDetected = false;
		}
	}

#ifdef TEST_PTP_NOTIFICATION
	if (mTestLockStatus == LockStatus_T::LOCKED)
	{
		mSynceLockStatus = LockStatus_T::LOCKED;
	}
	else
	{
		mSynceLockStatus = LockStatus_T::NOT_LOCKED;
	}
#endif

	// Check if the synce lock status has changed
	if (mSynceLockStatus != mPrevSynceLockStatus)
	{
		// notify any callbacks
		for (auto func : mSynceLockChangeFunc)
		{
			if (!func)
				continue ;

			func(mSynceLockStatus) ;
		}

		mPrevSynceLockStatus = mSynceLockStatus;
	}
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::monitorPtpStatus(void)
{
	// Write the PTP status
	if ((mSynceLockStatus == LockStatus_T::LOCKED &&
		(mServiceState == LinuxPtpServiceState::PTP_LOCKED ||
		 mServiceState == LinuxPtpServiceState::CHECK_POST_PTP_LOCK_STATUS ||
		 mServiceState == LinuxPtpServiceState::AIRFRAME_LOCKED))
#ifdef TEST_PTP_NOTIFICATION
		|| mTestLockStatus == LockStatus_T::LOCKED
#endif
		)
	{
		mPtpLockStatus = LockStatus_T::LOCKED;
	}
	else
	{
		mPtpLockStatus = LockStatus_T::NOT_LOCKED;
	}

	// Check if the PTP lock status has changed
	if (mPtpLockStatus != mPrevPtpLockStatus)
	{
		// notify any callbacks
		for (auto func : mPtpLockChangeFunc)
		{
			if (!func)
				continue ;

			func(mPtpLockStatus) ;
		}

		mPrevPtpLockStatus = mPtpLockStatus;
	}
}

//-------------------------------------------------------------------------------------------------------------
void LinuxPtp::monitorAirframeStatus(void)
{
	// Write the airframe lock status
	if ((mSynceLockStatus == LockStatus_T::LOCKED &&
		 mServiceState == LinuxPtpServiceState::AIRFRAME_LOCKED)
#ifdef TEST_PTP_NOTIFICATION
			|| mTestLockStatus == LockStatus_T::LOCKED
#endif
		)
	{
		mAirframeLockStatus = LockStatus_T::LOCKED;
	}
	else
	{
		mAirframeLockStatus = LockStatus_T::NOT_LOCKED;
	}

	// Check if the airframe lock status has changed
	if (mAirframeLockStatus != mPrevAirframeLockStatus)
	{
		// notify any callbacks
		for (auto func : mAirframeLockChangeFunc)
		{
			if (!func)
				continue ;

			func(mAirframeLockStatus) ;
		}

		mPrevAirframeLockStatus = mAirframeLockStatus;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool LinuxPtp::isSsmCodeAccepted(void)
{
	bool ret = false;

	// In case of PLL alarm, SYNCE status become unlocked
	std::shared_ptr<IAlarmsList> alarmList = IAlarmsList::getInstance();
	std::shared_ptr<IAlarm> pllAlarm = alarmList->getAlarm(Mplane::PllMajorAlarm::NAME);

	// If the configured SSM code is NONE, then the synce will never lock
	// If the configured SSM code is DNU, then any SSM code will be accepted
	// Else it has to match the received SSM code
	if (mConfiguredSsmCode.find(ILinuxPtpConfig::NONE) == mConfiguredSsmCode.end() &&
		mSsmStatus == SSM_CODE_RECEIVED &&
		(mConfiguredSsmCode.find(mReceivedSsmCode) != mConfiguredSsmCode.end() ||
				mConfiguredSsmCode.find(ILinuxPtpConfig::DNU) != mConfiguredSsmCode.end()) &&
		 pllAlarm->isAlarmActive() == false)
	{
		ret = true;
	}

	return ret;
}
