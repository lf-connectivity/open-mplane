/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILinuxPtpService.h
 * \brief     Virtual interface to the Linux PTP application
 *
 *
 * \details   The virtual interface is responsible for starting Linux PTP application,
 *            monitoring it, configuring data to be used by the PTP application and reading
 *            the the PTP synchronisation status
 *
 */


#ifndef VHI_INC_ILINUXPTPSERVICE_H_
#define VHI_INC_ILINUXPTPSERVICE_H_

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <functional>

namespace Mplane {

/*!
 * \class  ILinuxPtp
 * \brief
 * \details
 *
 */
class ILinuxPtpStatus {
public:
	ILinuxPtpStatus() {}
	virtual ~ILinuxPtpStatus() {}

	typedef enum
	{
		LOCKED,
		NOT_LOCKED
	} LockStatus_T;

	typedef enum
	{
		PARENT,
		NOK,
		OK,
		DISABLED
	} SourceState_T;

	/*
	 * Method to SFP ethernet interface port number
	 */
	virtual uint8_t getSfpEthPortNumber(void) = 0;

	/*
	 * Method to get the PTP lock status
	 */
	virtual LockStatus_T getPtpLockStatus(void) = 0;

	/*
	 * Method to get the Airframe lock status
	 */
	virtual LockStatus_T getAirframeLockStatus(void) = 0;

	/*
	 * Method to get the clock class of the clock controlled by O-RU
	 */
	virtual uint8_t getRuClockClass(void) = 0;

	/*
	 * Method to get the clock identity of the clock controlled by O-RU
	 */
	virtual std::string getRuClockIdentity(void) = 0;

	/*
	 * Method to get the PTP source state
	 */
	virtual SourceState_T getPtpSourceState(void) = 0;

	/*
	 * Method to convert the PTP/SYNCE source state to a string
	 */
	virtual std::string getSourceStateStr(SourceState_T state) = 0;

	/*
	 * Method to get the two step flag status
	 */
	virtual bool getTwoStepFlag(void) = 0;

	/*
	 * Method to get the leap61 flag status
	 */
	virtual bool getLeap61Flag(void) = 0;

	/*
	 * Method to get the leap59 flag status
	 */
	virtual bool getLeap59Flag(void) = 0;

	/*
	 * Method to get the current UTC offset valid flag
	 */
	virtual bool getCurrentUtcOffsetValidFlag(void) = 0;

	/*
	 * Method to get the ptp timescale flag
	 */
	virtual bool getPtpTimescaleFlag(void) = 0;

	/*
	 * Method to get the time traceable flag
	 */
	virtual bool getTimeTraceableFlag(void) = 0;

	/*
	 * Method to get the frequency traceable flag
	 */
	virtual bool getFrequencyTraceableFlag(void) = 0;

	/*
	 * Method to get the source clock identity of the PTP source
	 */
	virtual std::string getSourceClockIdentity(void) = 0;

	/*
	 * Method to get the source port number of the PTP source
	 */
	virtual uint16_t getSourcePortNumber(void) = 0;

	/*
	 * Method to get the current UTC offset
	 */
	virtual uint16_t getCurrentUtcOffset(void) = 0;

	/*
	 * Method to get the priotity1 attribute
	 */
	virtual uint8_t getPriority1(void) = 0;

	/*
	 * Method to get the clock class of the PTP source
	 */
	virtual uint8_t getSourceClockClass(void) = 0;

	/*
	 * Method to get the clock accuracy attribute
	 */
	virtual uint8_t getClockAccuracy(void) = 0;

	/*
	 * Method to get the offset scaled log variance attribute
	 */
	virtual uint16_t getoffsetScaledLogVariance(void) = 0;

	/*
	 * Method to get the priority 2 attribute status
	 */
	virtual uint8_t getPriority2(void) = 0;

	/*
	 * Method to get the Grand master clock identity
	 */
	virtual std::string getGMClockIdentity(void) = 0;

	/*
	 * Method to get the steps removed attribute that indicates the number of
	 * communication paths traversed between the local clock and the grand-master clock.
	 */
	virtual uint16_t getStepsRemoved(void) = 0;

	/*
	 * Method to get the time source attribute
	 */
	virtual uint8_t getTimeSource(void) = 0;

	/*
	 * Method to get the SYNCE lock status
	 */
	virtual LockStatus_T getSynceLockStatus(void) = 0;

	/*
	 * Method to get the SYNCE source state
	 */
	virtual SourceState_T getSynceSourceState(void) = 0;

	/*
	 * Method to get the SSM clock quality level
	 */
	virtual uint8_t getSsmQualityLevel(void) = 0;


} ;


/*!
 * \class  ILinuxPtpConfig
 * \brief
 * \details
 *
 */
class ILinuxPtpConfig{
public:
	ILinuxPtpConfig() {}
	virtual ~ILinuxPtpConfig() {}

	typedef enum
	{
		MAC_FORWARDABLE,
		MAC_NONFORWARDABLE
	} MulticastMACAddr_T;

	typedef enum
	{
		PRC,
		PRS,
		SSU_A,
		SSU_B,
		ST2,
		ST3,
		ST3E,
		EEC1,
		EEC2,
		DNU,
		NONE,
	} SsmCodes_T;

	/*
	 * Method to set the domain number
	 */
	virtual bool setDomainNumber(uint8_t domainNum) = 0;

	/*
	 * Method to set the multicast MAC address
	 */
	virtual bool setMulticastMac(MulticastMACAddr_T mac) = 0;

	/*
	 * Method to get the maximum acceptable clock class
	 */
	virtual uint8_t getMaxAcceptableClockClass(void) = 0;

	/*
	 * Method to set the acceptable SSM code
	 */
	virtual bool setAcceptableSsmCode(SsmCodes_T ssm, bool add) = 0;

	/*
	 * Method to set the SSM mismatch timeout
	 */
	virtual bool setSsmTimeout(uint16_t timeout) = 0;

	/*
	 * Method to convert the SSM code to a string
	 */
	virtual std::string getSsmStrFromCode(SsmCodes_T code) = 0;

	/*
	 * Method to convert the SSM str to code
	 */
	virtual SsmCodes_T getSsmCodeFromStr(std::string str) = 0;


} ;


/*!
 * \class  ILinuxPtp
 * \brief
 * \details
 *
 */
class ILinuxPtp : public virtual ILinuxPtpStatus, public virtual ILinuxPtpConfig{
public:
	ILinuxPtp() {}
	virtual ~ILinuxPtp() {}

	/*
	 * Create singleton
	 */
	static std::shared_ptr<ILinuxPtp> singleton(void);

	/*
	 * Method to initialise the PTP configuration
	 */
	virtual void initialise(void) = 0;

	/*
	 * Method to check if PTP application is running
	 */
	virtual bool isPtpRunning(void) = 0;

	/**
	 * Callback function for when the lock status changes
	 */
	using LockStatusChangeFunc = std::function<void(const LockStatus_T lockStatus)> ;


	/**
	 * Register a callback for when the PTP status changes
	 */
	virtual void registerPtpStatusFunc(LockStatusChangeFunc func) =0 ;

	/**
	 * Register a callback for when the Airframe status changes
	 */
	virtual void registerAirframeStatusFunc(LockStatusChangeFunc func) =0 ;

	/**
	 * Register a callback for when the SYNCE status changes
	 */
	virtual void registerSynceStatusFunc(LockStatusChangeFunc func) =0 ;

} ;

}

#endif /* VHI_INC_ILINUXPTPSERVICE_H_ */
