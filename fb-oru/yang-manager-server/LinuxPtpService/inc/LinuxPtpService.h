/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LinuxPtpService.h
 * \brief     Virtual interface to the Linux PTP application
 *
 *
 * \details   The virtual interface is responsible for starting Linux PTP application,
 *            monitoring it, configuring data to be used by the PTP application and reading
 *            the the PTP synchronisation status
 *
 */


#ifndef VHI_INC_LINUXPTPSERVICE_H_
#define VHI_INC_LINUXPTPSERVICE_H_

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <cstdint>
#include <mutex>
#include <fstream>
#include <chrono>
#include "ILinuxPtpService.h"
#include "Service.h"
#include "IFpgaMgr.h"
#include "YangTypes.h"
#include <pcap.h>
#include "IAlarmsList.h"
#include "PllMajorAlarm.h"

//#define TEST_PTP_NOTIFICATION

namespace Mplane {

/*!
 * \class  ILinuxPtp
 * \brief
 * \details
 *
 */
class LinuxPtp : public Service, public virtual ILinuxPtp{
public:

	enum LinuxPtpServiceState
	{
		WAIT_FOR_INTERFACE,
		WAIT_FOR_ESMC,
		PTP_START,
		DETECT_PTP_LOCK_STATUS,
		PTP_LOCKED,
		DETECT_AIRFRAME_LOCK,
		CHECK_POST_PTP_LOCK_STATUS,
		AIRFRAME_LOCKED,
		PTP_FAILED
	};

	struct PtpSourceStatus                                       //!> Status of the PTP source
	{
		SourceState_T mState;
		bool mTwoStepFlag;
		bool mLeap61;
		bool mLeap59;
		bool mCurrentUtcOffsetValid;
		bool mPtpTimescale;
		bool mTimeTraceable;
		bool mFreqTraceable;
		std::string mSourceClockIdentity;
		uint16_t mSourcePortNumber;
		uint16_t mCurrentUtcOffset;
		uint8_t mPriority1;
		uint8_t mClockClass;
		uint8_t mClockAccuracy;
		uint16_t mOffsetScaledLogVariance;
		uint8_t mPriority2;
		std::string mGrandmasterIdentity;
		uint16_t mStepsRemoved;
		uint8_t mTimeSource;
	};

	struct SynceSourceStatus                                       //!> Status of the SYNCE source
	{
		SourceState_T mState;
		uint8_t mQualityLevel;
	};

	enum SSMStatus
	{
		SSM_CODE_NOT_RECEIVED,
		SSM_CODE_TIMEOUT,
		SSM_CODE_INVALID,
		SSM_CODE_RECEIVED
	};

	static const std::string mPmcCommand;                       //!> PMC command string
	static const std::string mPtpStartCommand;                  //!> PTP start command string
	static const std::string mPtpConfFile;                      //!> Path to store the Linux PTP configuration file
	static const std::string mPtpProcessOutputFile;             //!> Linux PTP process output container
	static const std::string mQuickFindLinuxPtpProcessStr;		//!> Linux PTP quick find string container
	static const std::string mFindLinuxPtpProcessStr;			//!> Linux PTP find process string container
	static const std::string mServerProcessTxtStr;				//!> Temporary file string container
	static const std::string mPmcResponseTxtStr;				//!> Temporary file string container
	static const std::string mRmsStr;                           //!> Linux PTP RMS string
	static const int mPtpRmsThreshold;                          //!> RMS value threshold for PTP lock detection
    static const unsigned int mNumConsecutiveRmsChecks;         //!> Number of times the RMS value check should pass consecutively
    static const unsigned int mParamsRefreshMs;                 //!> Time in ms after which Pmc params need to be refreshed
    static const std::map<MulticastMACAddr_T, std::string> mMacAddr; //!> Map of MAC address enum to string
    static const unsigned int mPtpTimeoutMs;                    //!> Max Time in ms for PTP to sync
    static const unsigned int mAirframeLockTimeoutMs;           //!> Max Time in ms for airframe to lock
    static const std::vector<std::string> mPmcCommandsToSend;   //!> List of pmc commands
	LinuxPtp();
	virtual ~LinuxPtp();

#ifdef TEST_PTP_NOTIFICATION
	bool mTestLockStatus;
	void setLockStatus(LockStatus_T lockStatus)
	{
		mTestLockStatus = lockStatus;
	};
#endif

	/*
	 * Method to initialise the PTP configuration
	 */
	virtual void initialise(void) override;

	/*
	 * Method to check if PTP application is running
	 */
	virtual bool isPtpRunning(void) override;

	/*
	 * Method to SFP ethernet interface port number
	 */
	virtual uint8_t getSfpEthPortNumber(void) override;

	/*
	 * Method to get the PTP lock status
	 */
	virtual LockStatus_T getPtpLockStatus(void) override;

	/*
	 * Method to get the Airframe lock status
	 */
	virtual LockStatus_T getAirframeLockStatus(void) override;

	/*
	 * Method to get the clock class of the clock controlled by O-RU
	 */
	virtual uint8_t getRuClockClass(void) override;

	/*
	 * Method to get the clock identity of the clock controlled by O-RU
	 */
	virtual std::string getRuClockIdentity(void) override;

	/*
	 * Method to get the PTP source state
	 */
	virtual SourceState_T getPtpSourceState(void) override;

	/*
	 * Method to convert the PTP/SYNCE source state to a string
	 */
	virtual std::string getSourceStateStr(SourceState_T state) override;

	/*
	 * Method to get the two step flag status
	 */
	virtual bool getTwoStepFlag(void) override;

	/*
	 * Method to get the leap61 flag status
	 */
	virtual bool getLeap61Flag(void) override;

	/*
	 * Method to get the leap59 flag status
	 */
	virtual bool getLeap59Flag(void) override;

	/*
	 * Method to get the current UTC offset valid flag
	 */
	virtual bool getCurrentUtcOffsetValidFlag(void) override;

	/*
	 * Method to get the ptp timescale flag
	 */
	virtual bool getPtpTimescaleFlag(void) override;

	/*
	 * Method to get the time traceable flag
	 */
	virtual bool getTimeTraceableFlag(void) override;

	/*
	 * Method to get the frequency traceable flag
	 */
	virtual bool getFrequencyTraceableFlag(void) override;

	/*
	 * Method to get the source clock identity of the PTP source
	 */
	virtual std::string getSourceClockIdentity(void) override;

	/*
	 * Method to get the source port number of the PTP source
	 */
	virtual uint16_t getSourcePortNumber(void) override;

	/*
	 * Method to get the current UTC offset
	 */
	virtual uint16_t getCurrentUtcOffset(void) override;

	/*
	 * Method to get the priotity1 attribute
	 */
	virtual uint8_t getPriority1(void) override;

	/*
	 * Method to get the clock class of the PTP source
	 */
	virtual uint8_t getSourceClockClass(void) override;

	/*
	 * Method to get the clock accuracy attribute
	 */
	virtual uint8_t getClockAccuracy(void) override;

	/*
	 * Method to get the offset scaled log variance attribute
	 */
	virtual uint16_t getoffsetScaledLogVariance(void) override;

	/*
	 * Method to get the priority 2 attribute status
	 */
	virtual uint8_t getPriority2(void) override;

	/*
	 * Method to get the Grand master clock identity
	 */
	virtual std::string getGMClockIdentity(void) override;

	/*
	 * Method to get the steps removed attribute that indicates the number of
	 * communication paths traversed between the local clock and the grand-master clock.
	 */
	virtual uint16_t getStepsRemoved(void) override;

	/*
	 * Method to get the time source attribute
	 */
	virtual uint8_t getTimeSource(void) override;

	/*
	 * Method to get the SYNCE lock status
	 */
	virtual LockStatus_T getSynceLockStatus(void) override;

	/*
	 * Method to get the SYNCE source state
	 */
	virtual SourceState_T getSynceSourceState(void) override;

	/*
	 * Method to get the SSM clock quality level
	 */
	virtual uint8_t getSsmQualityLevel(void) override;

	/*
	 * Method to set the domain number
	 */
	virtual bool setDomainNumber(uint8_t domainNum) override;

	/*
	 * Method to set the multicast MAC address
	 */
	virtual bool setMulticastMac(MulticastMACAddr_T mac) override;

	/*
	 * Method to get the maximum acceptable clock class
	 */
	virtual uint8_t getMaxAcceptableClockClass(void) override;

	/*
	 * Method to set the acceptable SSM code
	 */
	virtual bool setAcceptableSsmCode(SsmCodes_T ssm, bool add) override;

	/*
	 * Method to set the SSM mismatch timeout
	 */
	virtual bool setSsmTimeout(uint16_t timeout) override;

	/*
	 * Method to convert the SSM code to a string
	 */
	virtual std::string getSsmStrFromCode(SsmCodes_T code) override;

	/*
	 * Method to convert the SSM str to code
	 */
	virtual SsmCodes_T getSsmCodeFromStr(std::string str) override;

	/**
	 * Register a callback for when the PTP status changes
	 */
	virtual void registerPtpStatusFunc(LockStatusChangeFunc func) override ;

	/**
	 * Register a callback for when the Airframe status changes
	 */
	virtual void registerAirframeStatusFunc(LockStatusChangeFunc func) override ;

	/**
	 * Register a callback for when the SYNCE status changes
	 */
	virtual void registerSynceStatusFunc(LockStatusChangeFunc func) override ;

protected:
	/**
	 * Method defined by the Loggable interface must be implemented by all
	 * object to force the display of the objects current status.
	 */
	virtual void show();

	/**
	 * Method that MUST be implemented by the inheriting service. The work done
	 * by the service, is implemented by this method.
	 * @return
	 */
	virtual int service();

	/**
	 * Method called as a result of the radio control process calling reset
	 * in the service. By default the base class implementation does nothing.
	 */
	virtual void doReset();

	/*
	 * Method to start Linux PTP application
	 */
	virtual bool startPtp(void);

	/*
	 * Method to stop Linux PTP application
	 */
	virtual bool stopPtp(void);

	/*
	 * Write the PTP configuration file
	 */
	virtual bool writePtpConf(void);

	/*
	 * Get PTP parameters using pmc commands
	 */
	virtual bool sendPmcCommands(void);

private:


    enum class PmcParamType_E : uint8_t
    {
    	BOOL,
    	STRING,
    	UINT8_DEC,
    	UINT16_DEC,
    	UINT8_HEX,
		UINT16_HEX
    };

	struct PmcResponseInfo
	{
		std::string mKeyword;
		void* mData;
		PmcParamType_E mType;
	};
	std::vector<PmcResponseInfo> mPmcResponseInfo; //!> Information to set the parameters based on response data


	std::chrono::system_clock::time_point mGpsTickEnableTime;    //!> Time at which GPS tick is enabled in FPGA
	std::chrono::system_clock::time_point mPtpStartTime;         //!> Time at which PTP application is started
	std::mutex mSsmMutex;                                        //!> Mutex to protect the SSM variables
	std::mutex mDataMutex;                                       //!> Mutex to protect reading PTP parameters
	std::string mEthbbInterfaceName;                             //!> Interface name to use for LinuxPTP
	uint8_t mEthInterfaceNumber;                                 //!> Interface number to use for LinuxPTP
	bool mInterfaceReady;                                        //!> Flag indicating whether the interface is up
	uint8_t mDomainNumber;                                       //!> Domain number used in PTP configuration
	std::string mMultiMacAddr;                                   //!> Multicast MAC address used in PTP configuration
	uint8_t mMaxAcceptableClockClass;                            //!> Max acceptable GM clock class for acceptable radio operation
	bool mPtpConfUpdated;                                        //!> Flag indicating that the PTP configuration values are updated

	unsigned int mNumRmsChecksPassed;                              //!> Counter for consecutive rms values below threshold
	std::chrono::system_clock::time_point mLastUpdate;             //!> Timer that stores the last time the PTP params were read
	bool mParamsReadOnce;                                          //!> Flag that indicates whether the PTP params were ever read
	std::vector<LockStatusChangeFunc> mPtpLockChangeFunc;          //!> Vector to store the callback functions to notify change in PTP lock status
	std::vector<LockStatusChangeFunc> mAirframeLockChangeFunc;     //!> Vector to store the callback functions to notify change in Airframe lock status
	LockStatus_T mPtpLockStatus;
	LockStatus_T mPrevPtpLockStatus;
	LockStatus_T mAirframeLockStatus;
	LockStatus_T mPrevAirframeLockStatus;

	/*
	 * Structure for parsing ESMC PDU frame
	 */
	struct itu_t_header {
		u_char slow_protocol_subtype;
		u_char itu_oui[3];
		u_char itu_subtype[2];
		u_char ver_flags;
		u_char reserved[3];
	};__attribute__((packed, aligned(1)));

	static const int ITU_HEADER_LEN = 10;
	static const int QL_TLV_LEN = 4;
	static const unsigned char QL_TYPE = 1;
	static const unsigned char QL_LEN = 4;
	static const unsigned char SSM_CODE_MASK = 0x0F;
	static const uint16_t SSM_DEFAULT_TIMEOUT_SEC = 10;
	static const uint16_t ESMC_PDU_TIMEOUT_SEC = 5;
	static const unsigned char ESMC_PDU_DA[];
	static const unsigned char ESMC_PDU_ETHER_TYPE[];
	static const unsigned char ESMC_PDU_SLOW_PROTOCOL_SUBTYPE;
	static const unsigned char ESMC_PDU_ITU_OUI[];
	static const std::map<unsigned char, ILinuxPtpConfig::SsmCodes_T> mSSMMapping;
	static const std::map<ILinuxPtpConfig::SsmCodes_T, std::string> mSsmCodeToStr;

	ILinuxPtpConfig::SsmCodes_T mReceivedSsmCode;                        //!> Received SSM code from ESMC PDU
	std::set<ILinuxPtpConfig::SsmCodes_T> mConfiguredSsmCode;                      //!> Acceptance SSM code
	SSMStatus mSsmStatus;                                                //!> SSM code status
	std::chrono::system_clock::time_point mLastEsmcReceived;             //!> Time at which the last ESMC PDU was received
	std::chrono::system_clock::time_point mSsmLockLostStartTime;         //!> Time at which SSM value received in the ESMC was different than configured values
	bool mSsmMismatchDetected;

	std::vector<LockStatusChangeFunc> mSynceLockChangeFunc;              //!> Vector to store the callback functions to notify change in Synce lock status
	LockStatus_T mSynceLockStatus;                                       //!> Whether SYNCE is locked or not
	LockStatus_T mPrevSynceLockStatus;                                   //!> Previous value for SYNCE lock

	uint16_t mSsmTimeoutSec;                                             //!> Max duration in seconds for which the received SSM value may be different than configured values
	SynceSourceStatus mSynceSourceStatus;                                //!> SYNCE status information

	int getRmsValue(void);
	bool prelockRmsValueCheck(void);
	void updateParams(bool force);
	void packetCallback(const struct pcap_pkthdr *, const unsigned char*, unsigned int);
	void monitorSynceStatus(void);
	void monitorPtpStatus(void);
	void monitorAirframeStatus(void);
	bool isSsmCodeAccepted(void);

protected:

	uint8_t mRuClockClass;                                       //!> clock-class controlled by the O-RU
	std::string mRuClockIdentity;                                //!> clock-indentity of the clock controlled by the O-RU

	PtpSourceStatus mPtpSourceStatus;
	LinuxPtpServiceState mServiceState;                          //!> Linux PTP service state
	std::ifstream mPtpProcessResult;                               //!> File name that stores the output of the ptp4l process
	std::map<std::string, std::string> mPtpResponseData;           //!> Map that stores the PTP parameter attribute and its value

} ;

}

#endif /* VHI_INC_LINUXPTPSERVICE_H_ */
