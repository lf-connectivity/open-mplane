/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestLinuxPtp.h
 * \brief     LinuxPtp test class
 *
 *
 * \details   LinuxPtp test class.
 *
 */

#ifndef TESTLINUXPTP_H_
#define TESTLINUXPTP_H_

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "ILinuxPtpService.h"
#include "LinuxPtpService.h"
#include "IAppOptions.h"
#include "INetworkingService.h"
#include "NetworkingService.h"
#include "NetAddrPolicyMock.h"

using namespace Mplane;

namespace Mplane
{

class TestLinuxPtp : public LinuxPtp
{
public :
	TestLinuxPtp();
	virtual ~TestLinuxPtp(){};

	/*
	 * Method to start Linux PTP application
	 */
	virtual bool startPtp(void);

	/*
	 * Method to stop Linux PTP application
	 */
	virtual bool stopPtp(void);

	/*
	 * Get PTP parameters using pmc commands
	 */
	virtual bool sendPmcCommands(void);

	LinuxPtp::LinuxPtpServiceState getState(void);

	void serviceLinuxPtp(void);

	/*
	 * Method to set the clock class of the clock controlled by O-RU
	 */
	void setRuClockClass(uint8_t param) ;

	/*
	 * Method to set the clock identity of the clock controlled by O-RU
	 */
	void setRuClockIdentity(std::string param) ;

	/*
	 * Method to set the PTP source state
	 */
	void setPtpParams(PtpSourceStatus param) ;

	void setLockOutcome(bool outcome);

private:
	uint8_t ruClockClass;
	std::string ruClockIdentity;
	PtpSourceStatus ptpSourceStatus;
	bool lock;

};
}

#endif
