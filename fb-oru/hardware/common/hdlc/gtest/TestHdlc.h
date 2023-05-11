/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestHdlc.h
 * \brief     HDLC test class
 *
 *
 * \details   HDLC test class.
 *
 */

#ifndef TESTHDLC_H_
#define TESTHDLC_H_

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "Hdlc.h"

using namespace Mplane;

namespace Mplane
{

static unsigned char mFlag(0);
static unsigned int mNumOctets(0);
static std::vector<unsigned char> mResponse(0);

class TestHdlc : public Hdlc
{
public :
	TestHdlc(std::shared_ptr<IBus> phy);
	virtual ~TestHdlc(){};

	bool run_once(void);

    static void responseCallback(unsigned char flag, unsigned int numOctets, std::vector<unsigned char> response)
    {
    	mFlag = flag;
    	mNumOctets = numOctets;
    	mResponse = response;
    }

    bool isTxErr()
    {
    	return (mFlag | Hdlc::COMM_TX_ERROR_MASK);
    }

    bool isRxErr()
	{
		return (mFlag | Hdlc::COMM_RX_ERROR_MASK);
	}

    bool isStartFlagErr()
	{
		return (mFlag | Hdlc::NO_START_FLAG_MASK);
	}

    bool isStopFlagErr()
	{
		return (mFlag | Hdlc::NO_STOP_FLAG_MASK);
	}

    bool isFCSErr()
	{
		return (mFlag | Hdlc::INCORRECT_FCS_MASK);
	}

    bool isTimeoutErr()
	{
		return (mFlag | Hdlc::RESP_TIMEOUT_MASK);
	}

    unsigned char getFlag(void)
    {
    	return mFlag;
    }

    unsigned int getNumOctets(void)
    {
    	return mNumOctets;
    }

    void getResp(std::vector<unsigned char>& resp)
    {
    	resp = mResponse;
    }

};
}

#endif
